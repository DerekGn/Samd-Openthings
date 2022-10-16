/*
 * openthings_common.h
 *
 * Created: 16/10/2022 12:46:40
 *  Author: Dg893
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

#endif /* OPENTHINGS_COMMON_H_ */