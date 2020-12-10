#include "build/temp/_test_openthings.c"
#include "../Openthings/openthings_message.h"
#include "../Openthings/openthings.h"
#include "C:/Ruby27-x64/lib/ruby/gems/2.7.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"




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



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((sizeof(struct openthings_message_header))), (UNITY_INT)(UNITY_INT8 )((context.eom)), (

   ((void *)0)

   ), (UNITY_UINT)(20), UNITY_DISPLAY_STYLE_HEX8);

}



void test_openthings_init_message_header(void)

{

    struct openthings_messge_context context;



    openthings_init_message(&context, 0xAA, 0x55, 0xBEEF, 0xDEADBEEF);



    struct openthings_message_header *header = (struct openthings_message_header *) &context.openthings_message_buffer;



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((0xAA)), (UNITY_INT)(UNITY_INT8 )((header->manu_id)), (

   ((void *)0)

   ), (UNITY_UINT)(31), UNITY_DISPLAY_STYLE_HEX8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((0x55)), (UNITY_INT)(UNITY_INT8 )((header->prod_id)), (

   ((void *)0)

   ), (UNITY_UINT)(32), UNITY_DISPLAY_STYLE_HEX8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0xBEEF)), (UNITY_INT)(UNITY_INT16)((header->pip)), (

   ((void *)0)

   ), (UNITY_UINT)(33), UNITY_DISPLAY_STYLE_HEX16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((0xEF)), (UNITY_INT)(UNITY_INT8 )((header->sensor_id_0)), (

   ((void *)0)

   ), (UNITY_UINT)(34), UNITY_DISPLAY_STYLE_HEX8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((0xBE)), (UNITY_INT)(UNITY_INT8 )((header->sensor_id_1)), (

   ((void *)0)

   ), (UNITY_UINT)(35), UNITY_DISPLAY_STYLE_HEX8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((0xAD)), (UNITY_INT)(UNITY_INT8 )((header->sensor_id_2)), (

   ((void *)0)

   ), (UNITY_UINT)(36), UNITY_DISPLAY_STYLE_HEX8);

}
