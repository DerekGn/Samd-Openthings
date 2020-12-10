#include "unity.h"

#include "openthings.h"
#include "openthings_message.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_openthings_init_message_eom(void)
{
    struct openthings_messge_context context;

    openthings_init_message(&context, 0xAA, 0x55, 0xBEEF, 0xDE);

    TEST_ASSERT_EQUAL_HEX8(sizeof(struct openthings_message_header), context.eom);
}

void test_openthings_init_message_header(void)
{
    struct openthings_messge_context context;

    openthings_init_message(&context, 0xAA, 0x55, 0xBEEF, 0xDEADBEEF);

    struct openthings_message_header *header = (struct openthings_message_header *) &context.openthings_message_buffer;

    TEST_ASSERT_EQUAL_HEX8(0xAA, header->manu_id);
    TEST_ASSERT_EQUAL_HEX8(0x55, header->prod_id);
    TEST_ASSERT_EQUAL_HEX16(0xBEEF, header->pip);
    TEST_ASSERT_EQUAL_HEX8(0xEF, header->sensor_id_0);
    TEST_ASSERT_EQUAL_HEX8(0xBE, header->sensor_id_1);
    TEST_ASSERT_EQUAL_HEX8(0xAD, header->sensor_id_2);
}
