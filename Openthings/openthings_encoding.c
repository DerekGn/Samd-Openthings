/**
 * \file
 *
 * \brief Openthings encoding prototypes
 *
 * Copyright (c) 2021 Derek Goslin
 *
 * @author Derek Goslin
 *
 * \page License
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

#include <math.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "openthings.h"
#include "openthings_common.h"
#include "openthings_encoding.h"

static uint32_t get_encoding_bits( enum openthings_float_encoding encoding );

static int32_t encode_float_to_int( enum openthings_float_encoding encoding,
const float value );

static uint32_t pack_int_to_array( uint8_t *const data, int32_t value );

/*-----------------------------------------------------------*/
enum openthings_encoding_status openthings_encode_record_message_float(
    struct openthings_message_record *const record,
    enum openthings_float_encoding encoding, const float value )
{
    enum openthings_encoding_status result;
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
                encoded = encode_float_to_int( encoding, value );

                len = pack_int_to_array( record->data, encoded );

                record->description.len = len;
                record->description.type = encoding;

                result = ENCODING_OK;
            }
            break;
        case FLOAT_ENCODING_SIGNEDX8:
        case FLOAT_ENCODING_SIGNEDX16:
        case FLOAT_ENCODING_SIGNEDX24:
            encoded = encode_float_to_int( encoding, value );

            if(value < 0)
            {
                 int32_t bits = get_encoding_bits(encoding);
                 
                 bits = ((((float)bits-1)/8)+1)*8;
                 
                 encoded &= (uint32_t)pow(2,bits)-1;
            }
            
            len = pack_int_to_array( record->data, encoded );

            record->description.len = len;
            record->description.type = encoding;

            result = ENCODING_OK;
            break;
        case FLOAT_ENCODING_FLOATING_POINT:
            len = pack_int_to_array( record->data, value );

            record->description.len = len;
            record->description.type = encoding;

            result = ENCODING_OK;
            break;
        default:
            break;
    }

    return result;
}

/*-----------------------------------------------------------*/

enum openthings_encoding_status openthings_encode_record_message_int(
    struct openthings_message_record *const record, const int32_t *const value,
    const size_t len )
{
    enum openthings_encoding_status result;

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

enum openthings_encoding_status openthings_encode_record_message_string(
    struct openthings_message_record *const record, const char *string )
{
    enum openthings_encoding_status result;
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

enum openthings_encoding_status openthings_encode_record_message_uint(
    struct openthings_message_record *const record, const uint32_t *const value,
    const size_t len )
{
    enum openthings_encoding_status result;

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

uint32_t get_encoding_bits( enum openthings_float_encoding encoding )
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

/*-----------------------------------------------------------*/

int32_t encode_float_to_int( enum openthings_float_encoding encoding,
                             const float value )
{
    double encode = value;
    int32_t encoded;

    encode *= pow( 2, get_encoding_bits( encoding ) );
    encode = round( encode );
    encoded = encode;

    return encoded;
}

/*-----------------------------------------------------------*/

uint32_t pack_int_to_array( uint8_t *const data, int32_t value )
{
    uint32_t shift = 24;
    uint32_t len = 0;

    for ( uint32_t i = 0; i < 4; i++ ) {
        uint8_t v = ( value >> shift ) & 0xFF;
        shift -= 8;

        if ( v ) {
            data[len++] = v;
        }
    }

    return len;
}

/*-----------------------------------------------------------*/
