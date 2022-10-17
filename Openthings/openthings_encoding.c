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

static size_t pack_int_to_array( uint8_t *const data, int64_t value );

static uint32_t get_highest_clear_bit( const int64_t value );

static uint32_t get_value_bits( int64_t value );

/*-----------------------------------------------------------*/
enum openthings_encoding_status openthings_encode_record_message_float(
    struct openthings_message_record *const record,
    enum openthings_float_encoding encoding, const float value )
{
    enum openthings_encoding_status result;
    int32_t encoded = 0;
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
    struct openthings_message_record *const record, const int32_t value )
{
    if ( value < 0 ) {
        int64_t encoded = value;
        
        uint32_t bits = get_value_bits( value );

        bits = ( ( ( (float)bits - 1 ) / 8 ) + 1 ) * 8;

        encoded &= (int64_t)pow( 2, bits ) - 1;
        
        record->description.len = pack_int_to_array( record->data, encoded );
        record->description.type = SIGNEDX0;
    } else {
        record->description.len = pack_int_to_array( record->data, value );
        record->description.type = SIGNEDX0;
    }

    return ENCODING_OK;
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
    struct openthings_message_record *const record, const uint32_t value )
{
    record->description.len = pack_int_to_array( record->data, value );
    record->description.type = UNSIGNEDX0;

    return ENCODING_OK;
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
    int32_t encoded = 0;

    encode *= pow( 2, get_encoding_bits( encoding ) );
    encode = round( encode );
    encoded = encode;

    return encoded;
}

/*-----------------------------------------------------------*/

size_t pack_int_to_array( uint8_t *const data, int64_t value )
{
    uint64_t shift = 56;
    size_t len = 0;

    for ( uint32_t i = 0; i < sizeof( int64_t ); i++ ) {
        uint8_t v = ( value >> shift ) & 0xFF;
        shift -= 8;

        if ( v || len > 0 ) {
            data[len++] = v;
        }
    }

    return len;
}

/*-----------------------------------------------------------*/

static uint32_t get_value_bits( int64_t value )
{
    if ( value == -1 ) {
        return 2;
    } else {
        return get_highest_clear_bit( value ) + 2;
    }
}

static uint32_t get_highest_clear_bit( const int64_t value )
{
    uint64_t mask = 0x8000000000000000;
    uint32_t bit_num = 63;

    do {
        if ( ( value & mask ) == 0 ) {
            break;
        }

        mask >>= 1;
        bit_num--;
    } while ( mask );

    return bit_num;
}
