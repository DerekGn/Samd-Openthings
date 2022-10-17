#include "unity.h"
#include "openthings_decoding.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_openthings_decode_record_message_float_invalid_type()
{
    struct openthings_message_record record;
    record.description.type = UNSIGNEDX0;
    float value;

    enum openthings_decoding_status status = openthings_decode_record_message_float(&record, &value);

    TEST_ASSERT_EQUAL_HEX8(DECODING_INVALID_TYPE, status);
}

void test_openthings_decode_record_message_float()
{
    struct openthings_message_record record;
    record.description.type = UNSIGNEDX4;
    record.description.len = 1;
    record.data[0] = 0x12;
    float value;

    enum openthings_decoding_status status = openthings_decode_record_message_float(&record, &value);

    TEST_ASSERT_EQUAL_HEX8(DECODING_OK, status);
    TEST_ASSERT_EQUAL_FLOAT(1.125, value);
}

void test_openthings_decode_record_message_int_invalid_type()
{
    struct openthings_message_record record;
    record.description.type = FLOATING_POINT;
    int32_t value;

    enum openthings_decoding_status status = openthings_decode_record_message_int(&record, &value);

    TEST_ASSERT_EQUAL_HEX8(DECODING_INVALID_TYPE, status);
}

void test_openthings_decode_record_message_int_byte_upper()
{
    int8_t value;
    struct openthings_message_record record;
    record.description.type = SIGNEDX0;
    record.description.len = 1;
    record.data[0] = 0x7F;

    enum openthings_decoding_status status = openthings_decode_record_message_int(&record, (uint32_t *const)&value);

    TEST_ASSERT_EQUAL_HEX8(DECODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(127, value);
}

void test_openthings_decode_record_message_int_byte_lower()
{
    int8_t value;
    struct openthings_message_record record;
    record.description.type = SIGNEDX0;
    record.description.len = 1;
    record.data[0] = 0x80;

    enum openthings_decoding_status status = openthings_decode_record_message_int(&record, (uint32_t *const)&value);

    TEST_ASSERT_EQUAL_HEX8(DECODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(-128, value);
}

void test_openthings_decode_record_message_int_short_upper()
{
    int16_t value;
    struct openthings_message_record record;
    record.description.type = SIGNEDX0;
    record.description.len = 2;
    record.data[0] = 0x7F;
    record.data[1] = 0xFF;

    enum openthings_decoding_status status = openthings_decode_record_message_int(&record, (uint32_t *const)&value);

    TEST_ASSERT_EQUAL_HEX8(DECODING_OK, status);
    TEST_ASSERT_EQUAL_INT16(32767, value);
}

void test_openthings_decode_record_message_int_short_lower()
{
    int16_t value;
    struct openthings_message_record record;
    record.description.type = SIGNEDX0;
    record.description.len = 2;
    record.data[0] = 0x80;
    record.data[1] = 0x00;

    enum openthings_decoding_status status = openthings_decode_record_message_int(&record, (uint32_t *const)&value);

    TEST_ASSERT_EQUAL_HEX8(DECODING_OK, status);
    TEST_ASSERT_EQUAL_INT16(-32768, value);
}

void test_openthings_decode_record_message_int_int_upper()
{
    int32_t value;
    struct openthings_message_record record;
    record.description.type = SIGNEDX0;
    record.description.len = 4;
    record.data[0] = 0x7F;
    record.data[1] = 0xFF;
    record.data[2] = 0xFF;
    record.data[3] = 0xFF;

    enum openthings_decoding_status status = openthings_decode_record_message_int(&record, &value);

    TEST_ASSERT_EQUAL_HEX8(DECODING_OK, status);
    TEST_ASSERT_EQUAL_INT32(2147483647, value);
}

void test_openthings_decode_record_message_int_int_lower()
{
    int32_t value;
    struct openthings_message_record record;
    record.description.type = SIGNEDX0;
    record.description.len = 4;
    record.data[0] = 0x80;
    record.data[1] = 0x00;
    record.data[2] = 0x00;
    record.data[3] = 0x00;

    enum openthings_decoding_status status = openthings_decode_record_message_int(&record, &value);

    TEST_ASSERT_EQUAL_HEX8(DECODING_OK, status);
    TEST_ASSERT_EQUAL_INT32(-2147483648, value);
}

void test_openthings_decode_record_message_uint_invalid_type()
{
    struct openthings_message_record record;
    record.description.type = FLOATING_POINT;
    uint32_t value;

    enum openthings_decoding_status status = openthings_decode_record_message_uint(&record, &value);

    TEST_ASSERT_EQUAL_HEX8(DECODING_INVALID_TYPE, status);
}

void test_openthings_decode_record_message_uint_byte()
{
    uint8_t value;
    struct openthings_message_record record;
    record.description.type = UNSIGNEDX0;
    record.description.len = 1;
    record.data[0] = 0xAA;

    enum openthings_decoding_status status = openthings_decode_record_message_uint(&record, (uint32_t *const)&value);

    TEST_ASSERT_EQUAL_HEX8(DECODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(0xAA, value);
}

void test_openthings_decode_record_message_uint_short()
{
    uint16_t value;
    struct openthings_message_record record;
    record.description.type = UNSIGNEDX0;
    record.description.len = 2;
    record.data[0] = 0x55;
    record.data[1] = 0xAA;

    enum openthings_decoding_status status = openthings_decode_record_message_uint(&record, (uint32_t *const)&value);

    TEST_ASSERT_EQUAL_HEX8(DECODING_OK, status);
    TEST_ASSERT_EQUAL_UINT16(0x55AA, value);
}

void test_openthings_decode_record_message_uint_uint()
{
    uint32_t value;
    struct openthings_message_record record;
    record.description.type = UNSIGNEDX0;
    record.description.len = 4;
    record.data[0] = 0x55;
    record.data[1] = 0xAA;
    record.data[2] = 0xFE;
    record.data[3] = 0xED;

    enum openthings_decoding_status status = openthings_decode_record_message_uint(&record, &value);

    TEST_ASSERT_EQUAL_HEX8(DECODING_OK, status);
    TEST_ASSERT_EQUAL_UINT16(0x55AAFEED, value);
}