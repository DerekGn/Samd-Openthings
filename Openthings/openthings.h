/* MIT License

Copyright (c) 2020 DerekGn

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#ifndef OPENTHINGS_H_
#define OPENTHINGS_H_

#include <stdint.h>
#include <stdbool.h>

#include "openthings_message.h"


void openthings_close_message(struct openthings_messge_context *const context);

void openthings_reset_message(struct openthings_messge_context *const context);

bool openthings_open_message(struct openthings_messge_context *const context);

void openthings_init_message(struct openthings_messge_context *const context,
                             const uint8_t manufacturer_id,
                             const uint8_t product_id, const uint16_t pip,
                             const uint32_t sensor_id);

void openthings_write_record(struct openthings_messge_context *const context,
                             struct openthings_message_record *const record);

bool openthings_read_message(struct openthings_messge_context *const context,
                             const struct openthings_message_record *record);
#endif /* OPENTHINGS_H_ */
