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

#ifndef ENCODING_H_
#define ENCODING_H_

#include "openthings.h"

/**
 * The list of float encoding values
 */
enum openthings_float_encoding {
    FLOAT_ENCODING_UNSIGNEDX4 = 0x1,
    FLOAT_ENCODING_UNSIGNEDX8 = 0x2,
    FLOAT_ENCODING_UNSIGNEDX12 = 0x03,
    FLOAT_ENCODING_UNSIGNEDX16 = 0x04,
    FLOAT_ENCODING_UNSIGNEDX20 = 0x05,
    FLOAT_ENCODING_UNSIGNEDX24 = 0x06,
    FLOAT_ENCODING_SIGNEDX8 = 0x09,
    FLOAT_ENCODING_SIGNEDX16 = 0x0A,
    FLOAT_ENCODING_SIGNEDX24 = 0x0B,
    FLOAT_ENCODING_FLOATING_POINT = 0x0F
};

/**
 * The encoding operation status
 */
enum openthings_encoding_status {
    ENCODING_OK,        /**< The operation succeeded */
    ENCODING_FAIL_SIZE, /**< The operation failed to encode the data due to size
                           constraints */
    ENCODING_FAIL_OUTRANGE /**< The operation failed to encode as the value to
                              encode is out of range */
};

/**
 * \brief Encode a float value to a fixed point signed integer value
 *
 * \param record The record to write the signed int too.
 * \param encoding The encoding to use
 * \param value The float value to encode
 *
 * \return enum openthings_encode_record_status
 */
enum openthings_encoding_status openthings_encode_record_message_float(
    struct openthings_message_record *const record,
    enum openthings_float_encoding encoding, const float value );

/**
 * \brief Encode an signed int value to the message record. It is assumed that
 * the max integer size is 4 bytes long on 32 bit cpu
 *
 * \param[in] record The record to write the signed int too.
 * \param[in] value The signed int value
 * \param[in] len The length in bytes too encode the signed int
 *
 * \return enum openthings_encode_record_status The status of the encoding
 * operation
 */
enum openthings_encoding_status openthings_encode_record_message_int(
    struct openthings_message_record *const record, const int32_t value );

/**
 * \brief Encode the contents of a string to the message record.
 *
 * \param[in] record The record to write the string too.
 * \param[in] string The string to write
 *
 * \return enum openthings_encode_record_status Status of the encoding operation
 */
enum openthings_encoding_status openthings_encode_record_message_string(
    struct openthings_message_record *const record, const char *string );

/**
 * \brief Encode an unsigned int value to the message record. It is assumed that
 * the max integer size is 4 bytes long on 32 bit cpu
 *
 * \param[in] record The record to write the unsigned int too.
 * \param[in] value The unsigned int value
 * \param[in] len The length in bytes too encode the unsigned int
 *
 * \return enum openthings_encode_record_status The status of the encoding
 * operation
 */
enum openthings_encoding_status openthings_encode_record_message_uint(
    struct openthings_message_record *const record, const uint32_t value );

#endif /* ENCODING_H_ */
