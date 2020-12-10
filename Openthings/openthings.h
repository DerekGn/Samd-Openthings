/*
 * Openthings v1.0.0
 * Copyright (C) Derek Goslin. All Rights Reserved.
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
