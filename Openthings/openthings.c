/**
 * \file
 *
 * \brief Openthings implementation
 *
 * Copyright (c) 2020 Derek Goslin
 *
 * @author Derek Goslin
 *
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "openthings.h"
#include "encrypt.h"

#define BYTE_0( value )                                                        \
    ( (uint8_t)value & 0xff ) /**< Mask byte 0 from a value. */
#define BYTE_1( value )                                                        \
    ( ( uint8_t )( value >> 8 ) & 0xff ) /**< Mask byte 1 from a value. */
#define BYTE_2( value )                                                        \
    ( ( uint8_t )( value >> 16 ) & 0xff ) /**< Mask byte 2 from a value. */
#define BYTE_3( value )                                                        \
    ( ( uint8_t )( value >> 24 ) & 0xff ) /**< Mask byte 3 from a value. */

#define OPENTHINGS_CRC_START                                                   \
    5 /**< The offset from the start of the openthings header that the CRC is  \
        \ calculated from */

#define RECORD_SIZE( record )                                                  \
    sizeof( enum openthings_parameter ) +                                      \
        sizeof( union openthings_type_description ) +                          \
        record->description.len /**< A macro for calculating the total size of \
                                   \ an openthings record.  */

static int16_t crc( const uint8_t const *buf, size_t size );

static int32_t get_encoding_bits( enum openthings_float_encoding encoding );

/*-----------------------------------------------------------*/

void openthings_init_message( struct openthings_messge_context *const context,
                              const uint8_t manufacturer_id,
                              const uint8_t product_id,
                              const uint32_t sensor_id )
{
    struct openthings_message_header
        *header = (struct openthings_message_header *)context->buffer;

    context->eom = 0;
    header->hdr_len = 0;
    header->manu_id = manufacturer_id;
    header->prod_id = product_id;
    header->pip_1 = 0;
    header->pip_0 = 0;
    header->sensor_id_0 = BYTE_0( sensor_id );
    header->sensor_id_1 = BYTE_1( sensor_id );
    header->sensor_id_2 = BYTE_2( sensor_id );

    context->eom += sizeof( struct openthings_message_header );
}

/*-----------------------------------------------------------*/

bool openthings_write_record( struct openthings_messge_context *const context,
                              struct openthings_message_record *const record )
{
    if ( context->eom + RECORD_SIZE( record ) +
             sizeof( struct openthings_message_footer ) <=
         OPENTHINGS_MAX_MSG_SIZE ) {
        memcpy( context->buffer + context->eom, record, RECORD_SIZE( record ) );

        context->eom += RECORD_SIZE( record );

        return true;
    }

    return false;
}

/*-----------------------------------------------------------*/

bool openthings_read_record( struct openthings_messge_context *const context,
                             const struct openthings_message_record *record )
{
    if ( context->buffer[context->eom] != 0 ) {
        struct openthings_message_record
            *current = (struct openthings_message_record *)( context->buffer +
                                                             context->eom );

        memcpy( (void *)record, current, RECORD_SIZE( current ) );

        context->eom += RECORD_SIZE( record );
        return true;
    }

    return false;
}

/*-----------------------------------------------------------*/

void openthings_encrypt_message(
    struct openthings_messge_context *const context,
    const uint8_t encryption_id, const uint16_t noise )
{
    struct openthings_message_header
        *header = (struct openthings_message_header *)context->buffer;

    size_t i = 0;
    uint16_t message_pip;

    randomise_seed( noise );
    message_pip = generate_pip( encryption_id );

    header->pip_0 = BYTE_0( message_pip );
    header->pip_1 = BYTE_1( message_pip );

    for ( i = OPENTHINGS_CRC_START; i <= header->hdr_len; ++i ) {
        context->buffer[i] = encrypt_decrypt( context->buffer[i] );
    }
}

/*-----------------------------------------------------------*/

void openthings_decrypt_message(
    struct openthings_messge_context *const context,
    const uint8_t encryption_id )
{
    struct openthings_message_header
        *header = (struct openthings_message_header *)context->buffer;

    uint16_t message_pip;
    size_t i;

    message_pip = ( ( ( (uint16_t)header->pip_1 ) << 8 ) | header->pip_0 );

    if ( message_pip != 0 ) {
        seed( encryption_id, message_pip );

        for ( i = OPENTHINGS_CRC_START; i <= header->hdr_len; ++i ) {
            context->buffer[i] = encrypt_decrypt( context->buffer[i] );
        }
    }
}

/*-----------------------------------------------------------*/

enum openthings_encode_record_status openthings_encode_record_message_float(
    struct openthings_message_record *const record,
    enum openthings_float_encoding encoding, const float value )
{
    enum openthings_encode_record_status result;
    double encode = value;
    int32_t encoded;
    uint32_t len = 0;

    switch ( encoding ) {
        case FLOAT_ENCODING_UNSIGNEDX4:
        case FLOAT_ENCODING_UNSIGNEDX8:
        case FLOAT_ENCODING_UNSIGNEDX12:
        case FLOAT_ENCODING_UNSIGNEDX16:
        case FLOAT_ENCODING_UNSIGNEDX20:
        case FLOAT_ENCODING_UNSIGNEDX24:
            if ( value < 0 ) {
                result = ENCODING_FAIL_OUTRANGE;
            } else {
                encode *= pow( 2, get_encoding_bits( encoding ) );
                encode = round( encode );
                encoded = encode;

                uint32_t shift = 24;

                for ( uint32_t i = 0; i < 4; i++ ) {
                    uint8_t v = ( encoded >> shift ) & 0xFF;
                    shift -= 8;

                    if ( v ) {
                        record->data[len++] = v;
                    }
                }

                record->description.len = len;
                record->description.type = encoding;

                result = ENCODING_OK;
            }
            break;
        case FLOAT_ENCODING_SIGNEDX8:
        case FLOAT_ENCODING_SIGNEDX12:
        case FLOAT_ENCODING_SIGNEDX16:
        case FLOAT_ENCODING_SIGNEDX24:

            break;
        case FLOAT_ENCODING_FLOATING_POINT:
            break;
        default:
            break;
    }

    return result;
}

/*-----------------------------------------------------------*/

enum openthings_encode_record_status openthings_encode_record_message_int(
    struct openthings_message_record *const record, const int32_t *const value,
    const size_t len )
{
    enum openthings_encode_record_status result;

    if ( len <= sizeof( int32_t ) ) {
        record->description.len = len;
        record->description.type = SIGNEDX0;
        result = ENCODING_OK;
        switch ( len ) {
            case 1:
                record->data[0] = BYTE_0( *value );
                break;
            case 2:
                record->data[0] = BYTE_1( *value );
                record->data[1] = BYTE_0( *value );
                break;
            case 4:
                record->data[0] = BYTE_3( *value );
                record->data[1] = BYTE_2( *value );
                record->data[2] = BYTE_1( *value );
                record->data[3] = BYTE_0( *value );
                break;
            default:
                result = ENCODING_FAIL_SIZE;
                break;
        }
    } else {
        result = ENCODING_FAIL_SIZE;
    }

    return result;
}

/*-----------------------------------------------------------*/

enum openthings_encode_record_status openthings_encode_record_message_string(
    struct openthings_message_record *const record, const char *string )
{
    enum openthings_encode_record_status result;
    size_t len = strlen( string );

    if ( len < OPENTHINGS_MAX_REC_SIZE ) {
        record->description.len = len;
        record->description.type = CHARS;
        strcpy( record->data, string );
    } else {
        result = ENCODING_FAIL_SIZE;
    }

    return result;
}

/*-----------------------------------------------------------*/

enum openthings_encode_record_status openthings_encode_record_message_uint(
    struct openthings_message_record *const record, const uint32_t *const value,
    const size_t len )
{
    enum openthings_encode_record_status result;

    if ( len <= sizeof( uint32_t ) ) {
        record->description.len = len;
        record->description.type = UNSIGNEDX0;
        result = ENCODING_OK;
        switch ( len ) {
            case 1:
                record->data[0] = BYTE_0( *value );
                break;
            case 2:
                record->data[0] = BYTE_1( *value );
                record->data[1] = BYTE_0( *value );
                break;
            case 4:
                record->data[0] = BYTE_3( *value );
                record->data[1] = BYTE_2( *value );
                record->data[2] = BYTE_1( *value );
                record->data[3] = BYTE_0( *value );
                break;
            default:
                result = ENCODING_FAIL_SIZE;
                break;
        }
    } else {
        result = ENCODING_FAIL_SIZE;
    }

    return result;
}

/*-----------------------------------------------------------*/

void openthings_close_message( struct openthings_messge_context *const context )
{
    struct openthings_message_header
        *header = (struct openthings_message_header *)context->buffer;

    struct openthings_message_footer *footer =
        (struct openthings_message_footer *)( context->buffer + context->eom );

    footer->eod = 0;

    int16_t msg_crc = crc( &context->buffer[OPENTHINGS_CRC_START],
                           ( context->eom - OPENTHINGS_CRC_START ) + 1 );

    footer->crc_0 = BYTE_0( msg_crc );
    footer->crc_1 = BYTE_1( msg_crc );

    context->eom += sizeof( struct openthings_message_footer );

    header->hdr_len = context->eom - 1;
}

/*-----------------------------------------------------------*/

void openthings_get_message_header(
    struct openthings_messge_context *const context,
    struct openthings_message_header *const header )
{
    memcpy( header, context->buffer,
            sizeof( struct openthings_message_header ) );
}

/*-----------------------------------------------------------*/

enum openthings_status openthings_open_message(
    struct openthings_messge_context *const context )
{
    enum openthings_status result = STATUS_OK;

    struct openthings_message_header
        *header = (struct openthings_message_header *)context->buffer;

    if ( header->hdr_len >= 10 && header->hdr_len < OPENTHINGS_MAX_MSG_SIZE ) {
        struct openthings_message_footer
            *footer = (struct openthings_message_footer
                           *)( ( context->buffer + header->hdr_len ) -
                               sizeof( struct openthings_message_footer ) + 1 );

        int16_t calc_crc = crc(
            ( const uint8_t *const ) & context->buffer[OPENTHINGS_CRC_START],
            ( (int)footer - (int)&context->buffer[OPENTHINGS_CRC_START] ) + 1 );

        int16_t exp_crc = ( ( ( (uint16_t)footer->crc_1 ) << 8 ) |
                            footer->crc_0 );
        if ( footer->eod == 0 && exp_crc == calc_crc ) {
            context->eom = sizeof( struct openthings_message_header );

            result = STATUS_OK;
        } else {
            result = STATUS_CRC_INVALID;
        }
    } else {
        result = STATUS_HEADER_LEN;
    }

    return result;
}

/*-----------------------------------------------------------*/

static int16_t crc( const uint8_t const *buf, size_t size )
{
    uint16_t rem = 0;
    size_t byte, bit;
    for ( byte = 0; byte < size; ++byte ) {
        rem ^= ( buf[byte] << 8 );
        for ( bit = 8; bit > 0; --bit ) {
            rem = ( ( rem & ( 1 << 15 ) ) ? ( ( rem << 1 ) ^ 0x1021 )
                                          : ( rem << 1 ) );
        }
    }
    return rem;
}

/*-----------------------------------------------------------*/

int32_t get_encoding_bits( enum openthings_float_encoding encoding )
{
    uint32_t result = 0;

    switch ( encoding ) {
        case FLOAT_ENCODING_UNSIGNEDX4:
            result = 4;
            break;
        case FLOAT_ENCODING_UNSIGNEDX8:
        case FLOAT_ENCODING_SIGNEDX8:
            result = 8;
            break;
        case FLOAT_ENCODING_UNSIGNEDX12:
        case FLOAT_ENCODING_SIGNEDX12:
            result = 12;
            break;
        case FLOAT_ENCODING_UNSIGNEDX16:
        case FLOAT_ENCODING_SIGNEDX16:
            result = 16;
            break;
        case FLOAT_ENCODING_UNSIGNEDX20:
            result = 20;
            break;
        case FLOAT_ENCODING_UNSIGNEDX24:
        case FLOAT_ENCODING_SIGNEDX24:
            result = 24;
            break;
        case FLOAT_ENCODING_FLOATING_POINT:
            break;
        default:
            break;
    }

    return result;
}
