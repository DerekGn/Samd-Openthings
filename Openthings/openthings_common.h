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

#ifndef OPENTHINGS_COMMON_H_
#define OPENTHINGS_COMMON_H_

#define BYTE_0( value )                                                        \
( (uint8_t)value & 0xff ) /**< Mask byte 0 from a value. */
#define BYTE_1( value )                                                        \
( ( uint8_t )( value >> 8 ) & 0xff ) /**< Mask byte 1 from a value. */
#define BYTE_2( value )                                                        \
( ( uint8_t )( value >> 16 ) & 0xff ) /**< Mask byte 2 from a value. */
#define BYTE_3( value )                                                        \
( ( uint8_t )( value >> 24 ) & 0xff ) /**< Mask byte 3 from a value. */

int64_t generate_mask(uint32_t bits);

#endif /* OPENTHINGS_COMMON_H_ */