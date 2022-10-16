#include "unity.h"
#include "openthings_encoding.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*(x)))

void setUp(void)
{
}

void tearDown(void)
{
}

void test_openthings_encode_record_message_float_invalid_unsigned_x4()
{
    struct openthings_message_record record;
    
    enum openthings_encoding_status status = openthings_encode_record_message_float(&record, FLOAT_ENCODING_UNSIGNEDX4, -1.0);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_FAIL_OUTRANGE, status);
}

void test_openthings_encode_record_message_float_invalid_unsigned_x8()
{
    struct openthings_message_record record;
    
    enum openthings_encoding_status status = openthings_encode_record_message_float(&record, FLOAT_ENCODING_UNSIGNEDX8, -1.0);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_FAIL_OUTRANGE, status);
}

void test_openthings_encode_record_message_float_invalid_unsigned_x16()
{
    struct openthings_message_record record;
    
    enum openthings_encoding_status status = openthings_encode_record_message_float(&record, FLOAT_ENCODING_UNSIGNEDX16, -1.0);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_FAIL_OUTRANGE, status);
}

void test_openthings_encode_record_message_float_invalid_unsigned_x20()
{
    struct openthings_message_record record;
    
    enum openthings_encoding_status status = openthings_encode_record_message_float(&record, FLOAT_ENCODING_UNSIGNEDX20, -1.0);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_FAIL_OUTRANGE, status);
}

void test_openthings_encode_record_message_float_invalid_unsigned_x24()
{
    struct openthings_message_record record;
    
    enum openthings_encoding_status status = openthings_encode_record_message_float(&record, FLOAT_ENCODING_UNSIGNEDX24, -1.0);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_FAIL_OUTRANGE, status);
}

void test_openthings_encode_record_message_float_unsigned_x4()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0x12};

    enum openthings_encoding_status status = openthings_encode_record_message_float(&record, FLOAT_ENCODING_UNSIGNEDX4, 1.12345);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(UNSIGNEDX4, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_float_unsigned_x8()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0x01, 0x20};

    enum openthings_encoding_status status = openthings_encode_record_message_float(&record, FLOAT_ENCODING_UNSIGNEDX8, 1.12345678);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(UNSIGNEDX8, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_float_unsigned_x12()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0x11, 0xFA};

    enum openthings_encoding_status status = openthings_encode_record_message_float(&record, FLOAT_ENCODING_UNSIGNEDX12, 1.123456789123456);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(UNSIGNEDX12, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_float_unsigned_x16()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0x01, 0x1F, 0x9B};

    enum openthings_encoding_status status = openthings_encode_record_message_float(&record, FLOAT_ENCODING_UNSIGNEDX16, 1.123456789123456);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(UNSIGNEDX16, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_float_unsigned_x20()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0x11, 0xF9, 0xAE};

    enum openthings_encoding_status status = openthings_encode_record_message_float(&record, FLOAT_ENCODING_UNSIGNEDX20, 1.123456789123456);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(UNSIGNEDX20, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_float_unsigned_x24()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0x01, 0x1F, 0x9A, 0xDE};

    enum openthings_encoding_status status = openthings_encode_record_message_float(&record, FLOAT_ENCODING_UNSIGNEDX24, 1.123456789123456);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(UNSIGNEDX24, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_float_signed_x8_neg_value()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0x7E, 0xE0};

    enum openthings_encoding_status status = openthings_encode_record_message_float(&record, FLOAT_ENCODING_SIGNEDX8, -1.123456789123456);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(SIGNEDX8, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_float_signed_x8_pos_value()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0x01, 0x20};

    enum openthings_encoding_status status = openthings_encode_record_message_float(&record, FLOAT_ENCODING_SIGNEDX8, 1.123456789123456);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(SIGNEDX8, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_float_signed_x16_neg_value()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0x7E, 0xE0, 0x65};

    enum openthings_encoding_status status = openthings_encode_record_message_float(&record, FLOAT_ENCODING_SIGNEDX16, -1.123456789123456);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(SIGNEDX16, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_float_signed_x16_pos_value()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0x01, 0x1F, 0x9B};

    enum openthings_encoding_status status = openthings_encode_record_message_float(&record, FLOAT_ENCODING_SIGNEDX16, 1.123456789123456);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(SIGNEDX16, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_int_invalid_size_greater_than()
{
    struct openthings_message_record record;
    int8_t value = 0xFF;

    enum openthings_encoding_status status = openthings_encode_record_message_int(&record, (const int32_t *const)&value, 5);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_FAIL_SIZE, status);
}

void test_openthings_encode_record_message_int_invalid_size()
{
    struct openthings_message_record record;
    
    enum openthings_encoding_status status = openthings_encode_record_message_int(&record, 0, 3);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_FAIL_SIZE, status);
}

void test_openthings_encode_record_message_int_byte_upper()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0x7F};
    int8_t value = 127;

    enum openthings_encoding_status status = openthings_encode_record_message_int(&record, (const int32_t *const)&value, sizeof(int8_t));

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(SIGNEDX0, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, sizeof(int8_t));
}

void test_openthings_encode_record_message_int_byte_lower()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0x80};
    int8_t value = -128;

    enum openthings_encoding_status status = openthings_encode_record_message_int(&record, (const int32_t *const)&value, sizeof(int8_t));

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(SIGNEDX0, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, sizeof(int8_t));
}

void test_openthings_encode_record_message_int_short_upper()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0x7F, 0xFF};
    int16_t value = 32767;

    enum openthings_encoding_status status = openthings_encode_record_message_int(&record, (const int32_t *const)&value, sizeof(int16_t));

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(SIGNEDX0, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, sizeof(int16_t));
}

void test_openthings_encode_record_message_int_short_lower()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0x80, 0x00};
    int16_t value = -32768;

    enum openthings_encoding_status status = openthings_encode_record_message_int(&record, (const int32_t *const)&value, sizeof(int16_t));

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(SIGNEDX0, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, sizeof(int16_t));
}

void test_openthings_encode_record_message_int_upper()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0x7F, 0xFF, 0xFF, 0xFF};
    int32_t value = 2147483647;

    enum openthings_encoding_status status = openthings_encode_record_message_int(&record, &value, sizeof(int32_t));

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(SIGNEDX0, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, sizeof(int32_t));
}

void test_openthings_encode_record_message_int_lower()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0x80, 0x00, 0x00, 0x00};
    int32_t value = -2147483648;

    enum openthings_encoding_status status = openthings_encode_record_message_int(&record, &value, sizeof(int32_t));

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(SIGNEDX0, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, sizeof(int32_t));
}

void test_openthings_encode_record_message_string_too_long()
{
    struct openthings_message_record record;
    char string[] = "XXXXXXXXXXXXXXXXXXXX";

    enum openthings_encoding_status status = openthings_encode_record_message_string(&record, string);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_FAIL_SIZE, status);
}

void test_openthings_encode_record_message_string_ok()
{
    struct openthings_message_record record;
    char string[] = "TEST";

    enum openthings_encoding_status status = openthings_encode_record_message_string(&record, string);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(4, record.description.len);
    TEST_ASSERT_EQUAL_HEX8(CHARS, record.description.type);
    TEST_ASSERT_EQUAL_STRING("TEST", record.data );
}

void test_openthings_encode_record_message_uint_invalid_size_greater_than()
{
    struct openthings_message_record record;
    int8_t value = 0xFF;

    enum openthings_encoding_status status = openthings_encode_record_message_int(&record, (const int32_t *const)&value, 5);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_FAIL_SIZE, status);
}

void test_openthings_encode_record_message_uint_invalid_size()
{
    struct openthings_message_record record;
    
    enum openthings_encoding_status status = openthings_encode_record_message_int(&record, 0, 3);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_FAIL_SIZE, status);
}

void test_openthings_encode_record_message_uint_byte()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0xFF};
    uint8_t value = 0xFF;

    enum openthings_encoding_status status = openthings_encode_record_message_uint(&record, (const uint32_t *const)&value, sizeof(uint8_t));

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(UNSIGNEDX0, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, sizeof(uint8_t));
}

void test_openthings_encode_record_message_uint_short()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0xAA, 0x55};
    uint16_t value = 0xAA55;

    enum openthings_encoding_status status = openthings_encode_record_message_uint(&record, (const uint32_t *const)&value, sizeof(uint16_t));

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(UNSIGNEDX0, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, sizeof(uint16_t));
}

void test_openthings_encode_record_message_uint()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0xAA, 0x55, 0xFE, 0xED};
    uint32_t value = 0xAA55FEED;

    enum openthings_encoding_status status = openthings_encode_record_message_uint(&record, &value, sizeof(uint32_t));

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(UNSIGNEDX0, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, sizeof(uint32_t));
}