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

#ifndef OPENTHINGS_DECODE_H_
#define OPENTHINGS_DECODE_H_

#include "openthings.h"

/**
 * The decoding operation status
 */
enum openthings_decoding_status {
    DECODING_OK,          /**< The operation succeeded */
    DECODING_INVALID_TYPE /**< The operation failed due to the wrong type
                             encoded in the message record */
};

/**
 * \brief Decode an encoded float record
 *
 * \param record The record to decode
 * \param value The decoded value if decoding was successful
 *
 * \return enum openthings_decoding_status The decoding status
 */
enum openthings_decoding_status openthings_decode_record_message_float(
    struct openthings_message_record *const record, float *const value );

/**
 * \brief Decode an encoded int record
 *
 * \param record The record to decode
 * \param value The decoded value if decoding was successful
 *
 * \return enum openthings_decoding_status The decoding status
 */
enum openthings_decoding_status openthings_decode_record_message_int(
    struct openthings_message_record *const record, int32_t *const value );

/**
 * \brief Decode an encoded uin record
 *
 * \param record The record to decode
 * \param value The decoded value if decoding was successful
 *
 * \return enum openthings_decoding_status The decoding status
 */
enum openthings_decoding_status openthings_decode_record_message_uint(
    struct openthings_message_record *const record, uint32_t *const value );

#endif /* OPENTHINGS_DECODE_H_ */
