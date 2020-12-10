#include "..\Openthings\openthings.h"
#include "..\Openthings\openthings_message.h"
#include "sam.h"

void write_message( struct openthings_messge_context *context )
{
    openthings_init_message( context, 0xAA, 0x55, 0xDEADBEEF );

    struct openthings_message_record record;

    record.parameter = ALARM;
    record.description.len = 2;
    record.description.type = UNSIGNEDX0;
    record.data[0] = 0x1;
    record.data[1] = 0x2;

    openthings_write_record( context, &record );

    record.parameter = REAL_POWER;
    record.description.len = 1;
    record.description.type = UNSIGNEDX0;
    record.data[0] = 0xAA;

    openthings_write_record( context, &record );

    openthings_close_message( context );
}

void read_message( struct openthings_messge_context *context )
{
    if ( openthings_open_message( context ) ) {
        struct openthings_message_record record;

        while ( openthings_read_record( context, &record ) ) {
        };
    }
}

int main( void )
{
    struct openthings_messge_context context;

    write_message( &context );

    read_message( &context );

    while ( 1 )
        ;
}
