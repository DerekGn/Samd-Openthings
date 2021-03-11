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

#include "sam.h"
#include "..\Openthings\openthings.h"

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
    uint8_t i = 0;

    if ( openthings_open_message( context ) ) {
        struct openthings_message_record record;

        while ( openthings_read_record( context, &record ) ) {
            if ( i == 0 ) {
                if ( record.parameter != ALARM ) {
                    while ( 1 )
                        ;
                }
            }

            if ( i == 1 ) {
                if ( record.parameter != REAL_POWER ) {
                    while ( 1 )
                        ;
                }
            }

            i++;
        };
    }
}

int main( void )
{
    struct openthings_messge_context context;

    write_message( &context );

    openthings_encrypt_message( &context, 10, 0xF4 );

    openthings_decrypt_message( &context, 10 );

    read_message( &context );

    while ( 1 )
        ;
}
