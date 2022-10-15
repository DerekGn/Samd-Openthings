/**
 * \file
 *
 * \brief Openthings prototypes
 *
 * Copyright (c) 2020 Derek Goslin
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

#ifndef OPENTHINGS_H_
#define OPENTHINGS_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "crosscompile.h"

#define OPENTHINGS_LIB_VERSION "1.0"

#define OPENTHINGS_MAX_MSG_SIZE                                                \
    255 /**< The maximum size of an openthings message. */
#define OPENTHINGS_MAX_REC_SIZE                                                \
    16 /**< The maximum size of an openthings message record. */

/**
 * The default list of parameter identifiers.
 */
enum openthings_parameter {
    ALARM = 0x21,
    DBG = 0x2D,
    IDENTIFY = 0x3F,
    SOURCE_SELECTOR = 0xC0,
    WATER_DETECTOR = 0x41,
    GLASS_BREAKAGE = 0x42,
    CLOSURES = 0x43,
    DOOR_BELL = 0x44,
    ENERGY = 0x45,
    FALL_SENSOR = 0x46,
    GAS_VOLUME = 0x47,
    AIR_PRESSURE = 0x48,
    ILLUMINANCE = 0x49,
    LEVEL = 0x4C,
    RAINFALL = 0x4D,
    APPARENT_POWER = 0x50,
    POWER_FACTOR = 0x51,
    REPORT_PERIOD = 0x52,
    SMOKE_DETECTOR = 0x53,
    TIME_DATE = 0x54,
    VIBRATION = 0x56,
    WATER_VOLUME = 0x57,
    WIND_SPEED = 0x58,
    GAS_PRESSURE = 0x61,
    BATTERY_LEVEL = 0x62,
    CO_DETECTOR = 0x63,
    DOOR_SENSOR = 0x64,
    EMERGENCY_PANIC_BUTTON = 0x65,
    FREQUENCY = 0x66,
    GAS_FLOW_RATE = 0x67,
    RELATIVE_HUMIDITY = 0x68,
    CURRENT = 0x69,
    JOIN = 0x6A,
    RF_QUALITY = 0x6B,
    LIGHT_LEVEL = 0x6C,
    MOTION_DETECTOR = 0x6D,
    OCCUPANCY = 0x6F,
    REAL_POWER = 0x70,
    REACTIVE_POWER = 0x71,
    ROTATION_SPEED = 0x72,
    SWITCH_STATE = 0x73,
    TEMPERATURE = 0x74,
    VOLTAGE = 0x76,
    WATER_FLOW_RATE = 0x77,
    WATER_PRESSURE = 0x78,
    PHASE1_POWER = 0x79,
    PHASE2_POWER = 0x7A,
    PHASE3_POWER = 0x7B,
    THREE_PHASE_TOTAL_POWER = 0x7C,
    VOC_INDEX = 0x7D,
    CURRENT_L = 0x7E,
    PHASE_ANGLE_L = 0x7F,
    ACTIVE_POWER_L = 0x80,
    POWER_FACTOR_L = 0x81,
    REACTIVE_POWER_L = 0x82,
    APPARENT_POWER_L = 0x83,
    CURRENT_N = 0x84,
    PHASE_ANGLE_N = 0x85,
    ACTIVE_POWER_N = 0x86,
    POWER_FACTOR_N = 0x87,
    REACTIVE_POWER_N = 0x88,
    APPARENT_POWER_N = 0x89,
    FWD_ACTIVE_ENERGY = 0x8A,
    REV_ACTIVE_ENERGY = 0x8B,
    ABS_ACTIVE_ENERGY = 0x8C,
    FWD_REACTIVE_ENERGY = 0x8D,
    REV_REACTIVE_ENERGY = 0x8E,
    ABS_REACTIVE_ENERGY = 0x8F
};

/**
 * The list of types supported.
 */
enum openthings_type {
    UNSIGNEDX0,
    UNSIGNEDX4,
    UNSIGNEDX8,
    UNSIGNEDX12,
    UNSIGNEDX16,
    UNSIGNEDX20,
    UNSIGNEDX24,
    CHARS,
    SIGNEDX0,
    SIGNEDX8,
    SIGNEDX12,
    SIGNEDX16,
    SIGNEDX24,
    ENUMERATION,
    RESERVED1,
    RESERVED2,
    FLOATING_POINT = 0x0F
};

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
    FLOAT_ENCODING_SIGNEDX8 = 0x08,
    FLOAT_ENCODING_SIGNEDX12 = 0x09,
    FLOAT_ENCODING_SIGNEDX16 = 0x0A,
    FLOAT_ENCODING_SIGNEDX24 = 0x0B,
    FLOAT_ENCODING_FLOATING_POINT = 0x0F
};

/**
 * The message function status result
 */
enum openthings_status {
    STATUS_OK,         /**< The operation succeeded */
    STATUS_HEADER_LEN, /**< The operation failed due to invalid header length */
    STATUS_CRC_INVALID /**< The operation failed due to invalid crc */
};

/**
 * The encoding operation status
 */
enum openthings_encode_record_status {
    ENCODING_OK,        /**< The operation succeeded */
    ENCODING_FAIL_SIZE, /**< The operation failed to encode the data due to size
                           constraints */
    ENCODING_FAIL_OUTRANGE /**< The operation failed to encode as the value to
                              encode is out of range */
};

/**
 * @brief An openthings message context.
 *
 * The context used for reading and writing openthings message and records data.
 */
struct openthings_messge_context {
    uint8_t
        buffer[OPENTHINGS_MAX_MSG_SIZE]; /**< The sequential byte buffer that a
                                            message is read and written too. */
    uint8_t eom; /**< The current end of message marker. */
};

/**
 * @brief An openthings message header.
 *
 * Represents an openthings message header
 */
struct __CROSS_ATTR_PACKED openthings_message_header {
    uint8_t hdr_len; /**< The message header length. Number of bytes in whole
                        message excluding this byte. */
    uint8_t manu_id; /**< The manufacturer Id. */
    uint8_t prod_id; /**< The product Id. */
    uint8_t pip_1;   /**< Reserved bytes. Used for encryption seed byte 1. */
    uint8_t pip_0;   /**< Reserved bytes. Used for encryption seed byte 0. */
    uint8_t sensor_id_2; /**< Byte 2 of the sensor Id. */
    uint8_t sensor_id_1; /**< Byte 1 of the sensor Id. */
    uint8_t sensor_id_0; /**< Byte 0 of the sensor Id. */
};

/**
 * @brief An openthings type description.
 *
 * Represents an openthings type description. The first 4 bits of a
 * recordtype description byte define the type of the data value being sent
 * (e.g. integer, float). The last 4 bits define the length of the data value
 * being sent (in bytes)
 */
union __CROSS_ATTR_PACKED openthings_type_description {
    uint8_t value; /**< The value of the openthings type description. */
    struct {
        uint8_t len : 4;               /**< The length of the data. */
        enum openthings_type type : 4; /**< The type of the data. */
    };
};

/**
 * @brief An openthings record.
 *
 * Represents an openthings record.
 */
struct __CROSS_ATTR_PACKED openthings_message_record {
    enum openthings_parameter parameter; /**< The record parameter. */
    union openthings_type_description
        description;                       /**< The record type description. */
    uint8_t data[OPENTHINGS_MAX_REC_SIZE]; /**< The parameter value. */
};

/**
 * @brief An openthings message footer.
 *
 * Represents an openthings record.
 */
struct __CROSS_ATTR_PACKED openthings_message_footer {
    uint8_t eod;   /**< The end of message marker. */
    uint8_t crc_1; /**< Byte 1 of the crc of the message. */
    uint8_t crc_0; /**< Byte 0 of the crc of the message. */
};

/**
 * \brief Close an openthings message.
 *
 * \param[in] context The openthings message context.
 *
 * The context must be allocated by the caller.
 *
 * \return void
 */
void openthings_close_message(
    struct openthings_messge_context *const context );

/**
 * \brief Gets the openthings message context from the context
 *
 * \param[in] context The openthings message context.
 * \param[in] header The openthings message header.
 *
 * The context must be allocated by the caller.
 * The header must be allocated by the caller.
 *
 * \return void
 */
void openthings_get_message_header(
    struct openthings_messge_context *const context,
    struct openthings_message_header *const header );

/**
 * \brief Opens an openthings message context.
 *
 * \param[in] context The openthings message context.
 *
 * The context must be allocated by the caller.
 *
 * This function performs validation of the message structure
 *
 * \return enum openthings_open_status	A return value of true indicates if the
 * open succeeded i.e. the integrity of the message is correct (CRC)
 */

enum openthings_status openthings_open_message(
    struct openthings_messge_context *const context );

/**
 * \brief Initalise an openthings message
 *
 * \param[in] context The openthings message context.
 * \param[in] manufacturer_id The manufacturer Id.
 * \param[in] product_id The product Id.
 * \param[in] sensor_id	The sensor Id.
 *
 * The context must be allocated by the caller.
 *
 * \return void
 */
void openthings_init_message( struct openthings_messge_context *const context,
                              const uint8_t manufacturer_id,
                              const uint8_t product_id,
                              const uint32_t sensor_id );

/**
 * \brief Write an openthings record to a message context.
 *
 * \param[in] context The openthings message context.
 * \param[in] record The openthings record to write to the context.
 *
 * \return bool	A return value of true indicates if the write succeeded i.e.
 * that there was enough room in the buffer
 */
bool openthings_write_record( struct openthings_messge_context *const context,
                              struct openthings_message_record *const record );

/**
 * \brief Reads an openthings record from the context.
 *
 * \param[in] context The openthings message context.
 * \param[in] record The openthings record to read from the context.
 *
 * The context must be allocated by the caller.
 * The record must be allocated by the caller.
 *
 * The record must be reused on each call to the openthings_read_record as it is
 * context for the next read from the message context.
 *
 * \return bool	A return value of true indicates that the read succeeded and
 * there are potentially more records contained within the context. A value of
 * false indicates that there are no more records to be read.
 */
bool openthings_read_record( struct openthings_messge_context *const context,
                             const struct openthings_message_record *record );

/**
 * \brief Encrypts the message bytes in the context. The encryption is based on
 * simple linear shift encryption. In reality is it a form of encoding rather
 * than encryption as it can be reversed relatively easily.
 *
 * \param[in] context The openthings message context.
 * \param[in] encryption_id The encryption id
 * \param[in] noise	The noise source value for randomizing encryption
 *
 * \return void
 */
void openthings_encrypt_message(
    struct openthings_messge_context *const context,
    const uint8_t encryption_id, const uint16_t noise );

/**
 * \brief Decrypt the message bytes in the context
 *
 * \param[in] context The openthings message context.
 * \param[in] encryption_id The encryption id
 *
 * \return void
 */
void openthings_decrypt_message(
    struct openthings_messge_context *const context,
    const uint8_t encryption_id );

///**
//* \brief
//*
//* \param record
//* \param value
//*
//* \return enum openthings_encode_record_status
//*/
// enum openthings_encode_record_status openthings_encode_record_message_enum(
// const struct openthings_message_record *record, const uint32_t *value );

/**
 * \brief
 *
 * \param record
 * \param encoding
 * \param value
 *
 * \return enum openthings_encode_record_status
 */
enum openthings_encode_record_status openthings_encode_record_message_float(
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
enum openthings_encode_record_status openthings_encode_record_message_int(
    struct openthings_message_record *const record, const int32_t *const value,
    const size_t len );

/**
 * \brief Encode the contents of a string to the message record.
 *
 * \param[in] record The record to write the string too.
 * \param[in] string The string to write
 *
 * \return enum openthings_encode_record_status Status of the encoding operation
 */
enum openthings_encode_record_status openthings_encode_record_message_string(
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
enum openthings_encode_record_status openthings_encode_record_message_uint(
    struct openthings_message_record *const record, const uint32_t *const value,
    const size_t len );

#endif /* OPENTHINGS_H_ */
