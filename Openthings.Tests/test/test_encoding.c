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
void test_openthings_encode_record_message_float_unsigned_x4_zero()
{
    struct openthings_message_record record;
    uint8_t expected[] = {};

    enum openthings_encoding_status status = openthings_encode_record_message_float(&record, FLOAT_ENCODING_UNSIGNEDX4, 0);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(UNSIGNEDX4, record.description.type);
 }

void test_openthings_encode_record_message_float_unsigned_x4()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0x12};

    enum openthings_encoding_status status = openthings_encode_record_message_float(&record, FLOAT_ENCODING_UNSIGNEDX4, 1.123456789);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(UNSIGNEDX4, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_float_unsigned_x8()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0x01, 0x20};

    enum openthings_encoding_status status = openthings_encode_record_message_float(&record, FLOAT_ENCODING_UNSIGNEDX8,1.123456789);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(UNSIGNEDX8, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_float_unsigned_x12()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0x11, 0xFA};

    enum openthings_encoding_status status = openthings_encode_record_message_float(&record, FLOAT_ENCODING_UNSIGNEDX12, 1.123456789);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(UNSIGNEDX12, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_float_unsigned_x16()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0x01, 0x1F, 0x9B};

    enum openthings_encoding_status status = openthings_encode_record_message_float(&record, FLOAT_ENCODING_UNSIGNEDX16, 1.123456789);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(UNSIGNEDX16, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_float_unsigned_x20()
{
    struct openthings_message_record record;
    uint8_t expected[] = {17, 249, 174};

    enum openthings_encoding_status status = openthings_encode_record_message_float(&record, FLOAT_ENCODING_UNSIGNEDX20, 1.123456789);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(UNSIGNEDX20, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_float_unsigned_x24()
{
    struct openthings_message_record record;
    uint8_t expected[] = {01, 31, 154, 222};

    enum openthings_encoding_status status = openthings_encode_record_message_float(&record, FLOAT_ENCODING_UNSIGNEDX24, 1.123456789);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(UNSIGNEDX24, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_float_signed_x8_neg_value()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0x7E, 224};

    enum openthings_encoding_status status = openthings_encode_record_message_float(&record, FLOAT_ENCODING_SIGNEDX8, -1.123456789);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(SIGNEDX8, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_float_signed_x8_pos_value()
{
    struct openthings_message_record record;
    uint8_t expected[] = {1, 32};

    enum openthings_encoding_status status = openthings_encode_record_message_float(&record, FLOAT_ENCODING_SIGNEDX8, 1.123456789);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(SIGNEDX8, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_float_signed_x16_neg_value()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0x7E, 224, 101};

    enum openthings_encoding_status status = openthings_encode_record_message_float(&record, FLOAT_ENCODING_SIGNEDX16, -1.123456789);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(SIGNEDX16, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_float_signed_x16_pos_value()
{
    struct openthings_message_record record;
    uint8_t expected[] = {1, 31, 155};

    enum openthings_encoding_status status = openthings_encode_record_message_float(&record, FLOAT_ENCODING_SIGNEDX16, 1.123456789);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(SIGNEDX16, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_float_signed_x24_neg_value()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0x7E, 0xE0, 0x65, 0x22};

    enum openthings_encoding_status status = openthings_encode_record_message_float(&record, FLOAT_ENCODING_SIGNEDX24, -1.123456789);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(SIGNEDX24, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_float_signed_x24_pos_value()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0x01, 0x1F, 0x9A, 0xDE};

    enum openthings_encoding_status status = openthings_encode_record_message_float(&record, FLOAT_ENCODING_SIGNEDX24, 1.123456789);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(SIGNEDX24, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_int_one()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0x01};
    int8_t value = 1;

    enum openthings_encoding_status status = openthings_encode_record_message_int(&record, value);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(SIGNEDX0, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_int_minus_one()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0x01, 0xFF};
    int8_t value = -1;

    enum openthings_encoding_status status = openthings_encode_record_message_int(&record, value);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(SIGNEDX0, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_int_minus_two()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0x01, 0xFE};
    int8_t value = -2;

    enum openthings_encoding_status status = openthings_encode_record_message_int(&record, value);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(SIGNEDX0, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_int_minus_three()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0x03, 0xFD};
    int8_t value = -3;

    enum openthings_encoding_status status = openthings_encode_record_message_int(&record, value);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(SIGNEDX0, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_int_minus_127()
{
    struct openthings_message_record record;
    uint8_t expected[] = {127, 129};
    int8_t value = -127;

    enum openthings_encoding_status status = openthings_encode_record_message_int(&record, value);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(SIGNEDX0, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_int_minus_128()
{
    struct openthings_message_record record;
    uint8_t expected[] = {127, 128};
    int8_t value = -128;

    enum openthings_encoding_status status = openthings_encode_record_message_int(&record, value);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(SIGNEDX0, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_int_minus_129()
{
    struct openthings_message_record record;
    uint8_t expected[] = {255, 127};
    int16_t value = -129;

    enum openthings_encoding_status status = openthings_encode_record_message_int(&record, value);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(SIGNEDX0, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_int_minus_32767()
{
    struct openthings_message_record record;
    uint8_t expected[] = {127, 128, 1};
    int16_t value = -32767;

    enum openthings_encoding_status status = openthings_encode_record_message_int(&record, value);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(SIGNEDX0, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_int_minus_32768()
{
    struct openthings_message_record record;
    uint8_t expected[] = {127, 128, 0};
    int32_t value = -32768;

    enum openthings_encoding_status status = openthings_encode_record_message_int(&record, value);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(SIGNEDX0, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_int_minus_2147483648()
{
    struct openthings_message_record record;
    uint8_t expected[] = {127, 128, 0, 0, 0};
    int32_t value = -2147483648;

    enum openthings_encoding_status status = openthings_encode_record_message_int(&record, value);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(SIGNEDX0, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_int_255()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0xFF};
    int16_t value = 255;

    enum openthings_encoding_status status = openthings_encode_record_message_int(&record, value);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(SIGNEDX0, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_int_256()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0x01, 0x00};
    int16_t value = 256;

    enum openthings_encoding_status status = openthings_encode_record_message_int(&record, value);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(SIGNEDX0, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_int_32767()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0x7F, 0xFF};
    int16_t value = 32767;

    enum openthings_encoding_status status = openthings_encode_record_message_int(&record, value);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(SIGNEDX0, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_int_32768()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0x80, 0x00};
    int32_t value = 32768;

    enum openthings_encoding_status status = openthings_encode_record_message_int(&record, value);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(SIGNEDX0, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_int_2147483647()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0x7F, 0xFF, 0xFF, 0xFF};
    int32_t value = 2147483647;

    enum openthings_encoding_status status = openthings_encode_record_message_int(&record, value);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(SIGNEDX0, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_int_zero()
{
    struct openthings_message_record record;
    uint8_t expected[] = {};
    int32_t value = 0;

    enum openthings_encoding_status status = openthings_encode_record_message_int(&record, value);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(SIGNEDX0, record.description.type);
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

void test_openthings_encode_record_message_uint_byte_lower()
{
    struct openthings_message_record record;
    uint8_t expected[] = {};
    uint8_t value = 0;

    enum openthings_encoding_status status = openthings_encode_record_message_uint(&record, value);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(0, record.description.len);
    TEST_ASSERT_EQUAL_HEX8(UNSIGNEDX0, record.description.type);
}

void test_openthings_encode_record_message_uint_byte_upper()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0xFF};
    uint8_t value = 255;

    enum openthings_encoding_status status = openthings_encode_record_message_uint(&record, value);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(UNSIGNEDX0, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_uint_short_lower()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0x01, 0x00};
    uint16_t value = 256;

    enum openthings_encoding_status status = openthings_encode_record_message_uint(&record, value);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(UNSIGNEDX0, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_uint_short_upper()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0xFF, 0xFF};
    uint16_t value = 65535;

    enum openthings_encoding_status status = openthings_encode_record_message_uint(&record, value);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(UNSIGNEDX0, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_uint_lower()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0x01, 0x00, 0x00};
    uint32_t value = 65536;

    enum openthings_encoding_status status = openthings_encode_record_message_uint(&record, value);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(UNSIGNEDX0, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}

void test_openthings_encode_record_message_uint_upper()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0xFF, 0xFF, 0xFF, 0xFF};
    uint32_t value = 4294967295;

    enum openthings_encoding_status status = openthings_encode_record_message_uint(&record, value);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(UNSIGNEDX0, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, ARRAY_SIZE(expected));
}