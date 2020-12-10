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

#ifndef OPENTHINGS_MESSAGE_H_
#define OPENTHINGS_MESSAGE_H_

#define OPENTHINGS_MAX_MSG 256
#define OPENTHINGS_MAX_REC 16

enum openthings_parameter {
    ALARM = 0x21,
    DBG = 0x2D,
    IDENTIFY = 0x3F,
    SOURCE_SELECTOR = 0xC0,
    WATER_DETECTOR = 0x41,
    GLASS_BREAKAGE = 0x42,
    CLOSURES = 0x43,
    DOOR_BELL = 0x44,
    ENERGY = 0x45,
    FALL_SENSOR = 0x46,
    GAS_VOLUME = 0x47,
    AIR_PRESSURE = 0x48,
    ILLUMINANCE = 0x49,
    LEVEL = 0x4C,
    RAINFALL = 0x4D,
    APPARENT_POWER = 0x50,
    POWER_FACTOR = 0x51,
    REPORT_PERIOD = 0x52,
    SMOKE_DETECTOR = 0x53,
    TIME_DATE = 0x54,
    VIBRATION = 0x56,
    WATER_VOLUME = 0x57,
    WIND_SPEED = 0x58,
    GAS_PRESSURE = 0x61,
    BATTERY_LEVEL = 0x62,
    CO_DETECTOR = 0x63,
    DOOR_SENSOR = 0x64,
    EMERGENCY_PANIC_BUTTON = 0x65,
    FREQUENCY = 0x66,
    GAS_FLOW_RATE = 0x67,
    RELATIVE_HUMIDITY = 0x68,
    CURRENT = 0x69,
    JOIN = 0x6A,
    RF_QUALITY = 0x6B,
    LIGHT_LEVEL = 0x6C,
    MOTION_DETECTOR = 0x6D,
    OCCUPANCY = 0x6F,
    REAL_POWER = 0x70,
    REACTIVE_POWER = 0x71,
    ROTATION_SPEED = 0x72,
    SWITCH_STATE = 0x73,
    TEMPERATURE = 0x74,
    VOLTAGE = 0x76,
    WATER_FLOW_RATE = 0x77,
    WATER_PRESSURE = 0x78,
    PHASE1_POWER = 0x79,
    PHASE2_POWER = 0x7A,
    PHASE3_POWER = 0x7B,
    THREE_PHASE_TOTAL_POWER = 0x7C
};

enum openthings_type {
    UNSIGNEDX0,
    UNSIGNEDX4,
    UNSIGNEDX8,
    UNSIGNEDX12,
    UNSIGNEDX16,
    UNSIGNEDX20,
    UNSIGNEDX24,
    CHARS,
    SIGNEDX0,
    SIGNEDX8,
    SIGNEDX12,
    SIGNEDX16,
    SIGNEDX24,
    ENUMERATION,
    RESERVED1,
    RESERVED2,
    FLOATING_POINT = 0x0F
};

struct openthings_messge_context {
    uint8_t openthings_message_buffer[OPENTHINGS_MAX_MSG];
    uint8_t eom;
};

struct openthings_message_header {
    uint8_t hdr_len;
    uint8_t manu_id;
    uint8_t prod_id;
    uint16_t pip;
    uint8_t sensor_id_2;
    uint8_t sensor_id_1;
    uint8_t sensor_id_0;
};

union openthings_type_description {
    uint8_t value;
    struct {
        uint8_t len : 4;
        enum openthings_type type : 4;
    };
};

struct openthings_message_record {
    enum openthings_parameter parameter;
    union openthings_type_description description;
    uint8_t data[OPENTHINGS_MAX_REC];
};

struct openthings_message_footer {
    uint8_t eod;
    uint16_t crc;
};
#endif /* OPENTHINGS_MESSAGE_H_ */
