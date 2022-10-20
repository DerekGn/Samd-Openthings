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

#include "openthings.h"
#include "openthings_common.h"
#include "openthings_decoding.h"

static bool float_encoded_signed( enum openthings_type type );

static uint32_t get_type_bits( enum openthings_type type );

/**
 * \brief Indicates if the type is a float encoded value
 *
 * \param type The type of encoding
 *
 * \return bool True of float encoded
 */
static bool float_encoded( enum openthings_type type );

/**
 * \brief Unpacks a buffer of bytes to an int value
 *
 * \param buf The data buffer to unpack
 * \param len The length of the data buffer to unpack
 *
 * \return uint32_t The unpacked value
 */
static uint32_t unpack_uint( uint8_t *const buf, uint32_t len );

/*-----------------------------------------------------------*/

enum openthings_decoding_status openthings_decode_record_message_float(
    struct openthings_message_record *const record, float *const value )
{
    enum openthings_decoding_status result = DECODING_OK;

    if ( float_encoded( record->description.type ) ) {
        uint32_t unpacked = unpack_uint( record->data,
                                         record->description.len );
        if ( float_encoded_signed( record->description.type ) ) {
            int32_t s = unpacked;

            if ( ( record->data[0] & 0x80 ) ) {
                uint8_t bits = record->description.len * 8;
                s = -( ( ( ~unpacked ) & generate_mask( bits/8 ) ) + 1 );
            }

            *value = (float)s /
                     pow( 2, get_type_bits( record->description.type ) );
        } else {
            *value = (float)unpacked /
                     pow( 2, get_type_bits( record->description.type ) );
        }
    } else {
        result = DECODING_INVALID_TYPE;
    }

    return result;
}

/*-----------------------------------------------------------*/

enum openthings_decoding_status openthings_decode_record_message_int(
    struct openthings_message_record *const record, int32_t *const value )
{
    enum openthings_decoding_status result = DECODING_OK;

    if ( record->description.type == SIGNEDX0 ) {
        uint32_t unpacked = unpack_uint( record->data,
                                         record->description.len );
        if ( record->data[0] & 0x80 ) {
            uint8_t bits = record->description.len * 8;
            *value = -( ( ( ~unpacked ) & generate_mask( bits/8 ) ) + 1 );
        } else {
            *value = unpacked;
        }
    } else {
        result = DECODING_INVALID_TYPE;
    }

    return result;
}

/*-----------------------------------------------------------*/

enum openthings_decoding_status openthings_decode_record_message_uint(
    struct openthings_message_record *const record, uint32_t *const value )
{
    enum openthings_decoding_status result = DECODING_OK;

    if ( record->description.type == UNSIGNEDX0 ) {
        *value = unpack_uint( record->data, record->description.len );
    } else {
        result = DECODING_INVALID_TYPE;
    }

    return result;
}

/*-----------------------------------------------------------*/

bool float_encoded( enum openthings_type type )
{
    bool result = false;

    switch ( type ) {
        case UNSIGNEDX0:
            break;
        case UNSIGNEDX4:
        case UNSIGNEDX8:
        case UNSIGNEDX12:
        case UNSIGNEDX16:
        case UNSIGNEDX20:
        case UNSIGNEDX24:
            result = true;
            break;
        case CHARS:
            break;
        case SIGNEDX0:
            break;
        case SIGNEDX8:
        case SIGNEDX16:
        case SIGNEDX24:
            result = true;
            break;
        case ENUMERATION:
            break;
        case RESERVED1:
            break;
        case RESERVED2:
            break;
        case FLOATING_POINT:
            result = true;
            break;
        default:
            break;
    }

    return result;
}

/*-----------------------------------------------------------*/

uint32_t get_type_bits( enum openthings_type type )
{
    uint32_t result = 0;

    switch ( type ) {
        case UNSIGNEDX0:
            break;
        case UNSIGNEDX4:
            result = 4;
            break;
        case UNSIGNEDX8:
        case SIGNEDX8:
            result = 8;
            break;
        case UNSIGNEDX12:
            result = 12;
            break;
        case UNSIGNEDX16:
        case SIGNEDX16:
            result = 16;
            break;
        case UNSIGNEDX20:
            result = 20;
            break;
        case UNSIGNEDX24:
        case SIGNEDX24:
            result = 24;
            break;
        case CHARS:
            break;
        case SIGNEDX0:
            break;
        case ENUMERATION:
            break;
        case RESERVED1:
            break;
        case RESERVED2:
            break;
        case FLOATING_POINT:
            break;
        default:
            break;
    }

    return result;
}

/*-----------------------------------------------------------*/

bool float_encoded_signed( enum openthings_type type )
{
    bool result = false;

    switch ( type ) {
        case UNSIGNEDX0:
        case UNSIGNEDX4:
        case UNSIGNEDX8:
        case UNSIGNEDX12:
        case UNSIGNEDX16:
        case UNSIGNEDX20:
        case UNSIGNEDX24:
            break;
        case CHARS:
            break;
        case SIGNEDX0:
        case SIGNEDX8:
        case SIGNEDX16:
        case SIGNEDX24:
            result = true;
            break;
        case ENUMERATION:
            break;
        case RESERVED1:
            break;
        case RESERVED2:
            break;
        case FLOATING_POINT:
            break;
        default:
            break;
    }

    return result;
}

/*-----------------------------------------------------------*/

uint32_t unpack_uint( uint8_t *const data, uint32_t len )
{
    uint32_t result = 0;

    for ( uint32_t i = 0; i < len; i++ ) {
        result <<= 8;
        result += data[i];
    }

    return result;
}
