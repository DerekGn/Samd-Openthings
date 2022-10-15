#include <string.h>

#include "unity.h"
#include "encrypt.c"
#include "openthings.h"

#define RECORD_SIZE(record)             \
    sizeof(enum openthings_parameter) + \
        sizeof(union openthings_type_description) + record.description.len

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*(x)))

void setUp(void)
{
}

void tearDown(void)
{
}

void write_test_record(
    struct openthings_messge_context *const context)
{
    struct openthings_message_record record;

    record.parameter = ALARM;
    record.description.len = 2;
    record.description.type = UNSIGNEDX0;
    record.data[0] = 0x55;
    record.data[0] = 0xAA;

    openthings_write_record(context, &record);
}

void open_context_and_assert_test_record(
    struct openthings_messge_context *const context)
{
    if (openthings_open_message(context) == STATUS_OK)
    {
        struct openthings_message_record record;

        if (openthings_read_record(context, &record))
        {
            TEST_ASSERT_EQUAL_HEX8(ALARM, record.parameter);
        }
        else
        {
            TEST_FAIL_MESSAGE("Record read failed");
        }
    }
    else
    {
        TEST_FAIL_MESSAGE("Message open failed");
    }
}

void test_openthings_init_message_eom(void)
{
    struct openthings_messge_context context;

    openthings_init_message(&context, 0xAA, 0x55, 0xDEADBEEF);

    TEST_ASSERT_EQUAL_HEX8(sizeof(struct openthings_message_header), context.eom);
}

void test_openthings_init_message_header(void)
{
    struct openthings_messge_context context;

    openthings_init_message(&context, 0xAA, 0x55, 0xDEADBEEF);

    struct openthings_message_header *header = (struct openthings_message_header *)&context.buffer;

    TEST_ASSERT_EQUAL_HEX8(0xAA, header->manu_id);
    TEST_ASSERT_EQUAL_HEX8(0x55, header->prod_id);
    TEST_ASSERT_EQUAL_HEX16(0, header->pip_0);
    TEST_ASSERT_EQUAL_HEX16(0, header->pip_1);
    TEST_ASSERT_EQUAL_HEX8(0xEF, header->sensor_id_0);
    TEST_ASSERT_EQUAL_HEX8(0xBE, header->sensor_id_1);
    TEST_ASSERT_EQUAL_HEX8(0xAD, header->sensor_id_2);
}

void test_openthings_write_record(void)
{
    struct openthings_messge_context context;

    context.eom = sizeof(struct openthings_message_header);

    struct openthings_message_record record;

    record.parameter = ALARM;
    record.description.len = 2;
    record.description.type = UNSIGNEDX0;
    record.data[0] = 0x55;
    record.data[0] = 0xAA;

    TEST_ASSERT_EQUAL_HEX8(1, openthings_write_record(&context, &record));

    TEST_ASSERT_EQUAL_HEX8(sizeof(struct openthings_message_header) + RECORD_SIZE(record), context.eom);
}

void test_openthings_write_record_no_space(void)
{
    struct openthings_messge_context context;

    context.eom = OPENTHINGS_MAX_MSG_SIZE;

    struct openthings_message_record record;

    TEST_ASSERT_EQUAL_HEX8(0, openthings_write_record(&context, &record));
}

void test_openthings_close_message(void)
{
    struct openthings_messge_context context;

    context.eom = sizeof(struct openthings_message_header);

    struct openthings_message_record record;

    record.description.len = 2;

    context.eom += RECORD_SIZE(record);

    openthings_close_message(&context);

    struct openthings_message_header *header =
        (struct openthings_message_header *)context.buffer;

    struct openthings_message_footer *footer =
        (struct openthings_message_footer *)context.buffer + context.eom;

    TEST_ASSERT_EQUAL_HEX8(
        sizeof(struct openthings_message_header) +
            RECORD_SIZE(record) +
            sizeof(struct openthings_message_footer) - 1,
        header->hdr_len);

    TEST_ASSERT_EQUAL_HEX8(0xFC, footer->crc_1);
    TEST_ASSERT_EQUAL_HEX8(0x7F, footer->crc_0);
}

void test_openthings_open_message(void)
{
    struct openthings_messge_context context;

    openthings_init_message(&context, 0xAA, 0x55, 0xDEADBEEF);

    write_test_record(&context);

    openthings_close_message(&context);

    TEST_ASSERT_EQUAL_HEX8(STATUS_OK, openthings_open_message(&context));
}

void test_openthings_read_record(void)
{
    struct openthings_messge_context context;

    openthings_init_message(&context, 0xAA, 0x55, 0xDEADBEEF);

    write_test_record(&context);

    openthings_close_message(&context);

    open_context_and_assert_test_record(&context);
}

void test_openthings_read_header()
{
    struct openthings_messge_context context;

    openthings_init_message(&context, 0xAA, 0x55, 0xDEADBEEF);

    struct openthings_message_header header;
    openthings_get_message_header(&context, &header);

    TEST_ASSERT_EQUAL_HEX8(0, header.hdr_len);
    TEST_ASSERT_EQUAL_HEX8(0xAA, header.manu_id);
    TEST_ASSERT_EQUAL_HEX8(0, header.pip_0);
    TEST_ASSERT_EQUAL_HEX8(0, header.pip_1);
    TEST_ASSERT_EQUAL_HEX8(0x55, header.prod_id);
    TEST_ASSERT_EQUAL_HEX8(0xEF, header.sensor_id_0);
    TEST_ASSERT_EQUAL_HEX8(0xBE, header.sensor_id_1);
    TEST_ASSERT_EQUAL_HEX8(0xAD, header.sensor_id_2);
}

void test_openthings_encrypt_decrypt()
{
    struct openthings_messge_context context;

    openthings_init_message(&context, 0xAA, 0x55, 0xDEADBEEF);

    write_test_record(&context);

    openthings_close_message(&context);

    openthings_encrypt_message(&context, 10, 0xF4);

    openthings_decrypt_message(&context, 10);

    open_context_and_assert_test_record(&context);
}

void test_openthings_random_payload()
{
    struct openthings_messge_context context = {
        {0x03, 0xd3, 0x92, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
         0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
         0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
         0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
         0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
         0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00},
        0};

    TEST_ASSERT_EQUAL_HEX8(1, openthings_open_message(&context));
}

void test_openthings_encode_record_message_float_invalid_unsigned_x4()
{
    struct openthings_message_record record;
    
    enum openthings_encode_record_status status = openthings_encode_record_message_float(&record, FLOAT_ENCODING_UNSIGNEDX4, -1.0);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_FAIL_OUTRANGE, status);
}

void test_openthings_encode_record_message_float_invalid_unsigned_x8()
{
    struct openthings_message_record record;
    
    enum openthings_encode_record_status status = openthings_encode_record_message_float(&record, FLOAT_ENCODING_UNSIGNEDX8, -1.0);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_FAIL_OUTRANGE, status);
}

void test_openthings_encode_record_message_float_invalid_unsigned_x16()
{
    struct openthings_message_record record;
    
    enum openthings_encode_record_status status = openthings_encode_record_message_float(&record, FLOAT_ENCODING_UNSIGNEDX16, -1.0);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_FAIL_OUTRANGE, status);
}

void test_openthings_encode_record_message_float_invalid_unsigned_x20()
{
    struct openthings_message_record record;
    
    enum openthings_encode_record_status status = openthings_encode_record_message_float(&record, FLOAT_ENCODING_UNSIGNEDX20, -1.0);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_FAIL_OUTRANGE, status);
}

void test_openthings_encode_record_message_float_invalid_unsigned_x24()
{
    struct openthings_message_record record;
    
    enum openthings_encode_record_status status = openthings_encode_record_message_float(&record, FLOAT_ENCODING_UNSIGNEDX24, -1.0);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_FAIL_OUTRANGE, status);
}

void test_openthings_encode_record_message_float_unsigned_x4()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0x12};

    enum openthings_encode_record_status status = openthings_encode_record_message_float(&record, FLOAT_ENCODING_UNSIGNEDX4, 1.12345);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(UNSIGNEDX4, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, 1);
}

void test_openthings_encode_record_message_float_unsigned_x8()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0x12, 0x2};

    enum openthings_encode_record_status status = openthings_encode_record_message_float(&record, FLOAT_ENCODING_UNSIGNEDX8, 1.12345678);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(UNSIGNEDX8, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, 1);
}

void test_openthings_encode_record_message_int_invalid_size_greater_than()
{
    struct openthings_message_record record;
    int8_t value = 0xFF;

    enum openthings_encode_record_status status = openthings_encode_record_message_int(&record, (const int32_t *const)&value, 5);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_FAIL_SIZE, status);
}

void test_openthings_encode_record_message_int_invalid_size()
{
    struct openthings_message_record record;
    
    enum openthings_encode_record_status status = openthings_encode_record_message_int(&record, 0, 3);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_FAIL_SIZE, status);
}

void test_openthings_encode_record_message_int_byte()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0xFF};
    int8_t value = 0xFF;

    enum openthings_encode_record_status status = openthings_encode_record_message_int(&record, (const int32_t *const)&value, sizeof(int8_t));

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(SIGNEDX0, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, sizeof(int8_t));
}

void test_openthings_encode_record_message_int_short()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0xAA, 0x55};
    int16_t value = 0xAA55;

    enum openthings_encode_record_status status = openthings_encode_record_message_int(&record, (const int32_t *const)&value, sizeof(int16_t));

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(SIGNEDX0, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, sizeof(int16_t));
}

void test_openthings_encode_record_message_int()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0xAA, 0x55, 0xFE, 0xED};
    int32_t value = 0xAA55FEED;

    enum openthings_encode_record_status status = openthings_encode_record_message_int(&record, &value, sizeof(int32_t));

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(SIGNEDX0, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, sizeof(int32_t));
}

void test_openthings_encode_record_message_string_too_long()
{
    struct openthings_message_record record;
    char string[] = "XXXXXXXXXXXXXXXXXXXX";

    enum openthings_encode_record_status status = openthings_encode_record_message_string(&record, string);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_FAIL_SIZE, status);
}

void test_openthings_encode_record_message_string_ok()
{
    struct openthings_message_record record;
    char string[] = "TEST";

    enum openthings_encode_record_status status = openthings_encode_record_message_string(&record, string);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(4, record.description.len);
    TEST_ASSERT_EQUAL_HEX8(CHARS, record.description.type);
    TEST_ASSERT_EQUAL_STRING("TEST", record.data );
}

void test_openthings_encode_record_message_uint_invalid_size_greater_than()
{
    struct openthings_message_record record;
    int8_t value = 0xFF;

    enum openthings_encode_record_status status = openthings_encode_record_message_int(&record, (const int32_t *const)&value, 5);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_FAIL_SIZE, status);
}

void test_openthings_encode_record_message_uint_invalid_size()
{
    struct openthings_message_record record;
    
    enum openthings_encode_record_status status = openthings_encode_record_message_int(&record, 0, 3);

    TEST_ASSERT_EQUAL_HEX8(ENCODING_FAIL_SIZE, status);
}

void test_openthings_encode_record_message_uint_byte()
{
    struct openthings_message_record record;
    uint8_t expected[] = {0xFF};
    uint8_t value = 0xFF;

    enum openthings_encode_record_status status = openthings_encode_record_message_uint(&record, (const uint32_t *const)&value, sizeof(uint8_t));

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

    enum openthings_encode_record_status status = openthings_encode_record_message_uint(&record, (const uint32_t *const)&value, sizeof(uint16_t));

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

    enum openthings_encode_record_status status = openthings_encode_record_message_uint(&record, &value, sizeof(uint32_t));

    TEST_ASSERT_EQUAL_HEX8(ENCODING_OK, status);
    TEST_ASSERT_EQUAL_HEX8(ARRAY_SIZE(expected), record.description.len);
    TEST_ASSERT_EQUAL_HEX8(UNSIGNEDX0, record.description.type);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, record.data, sizeof(uint32_t));
}