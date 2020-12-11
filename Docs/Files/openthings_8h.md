---
title: openthings.h
summary: Openthings prototypes.  

---

# openthings.h


Openthings prototypes.  [More...](#detailed-description)






## Classes

|                | Name           |
| -------------- | -------------- |
| struct | **[openthings_messge_context](Classes/structopenthings__messge__context.md)** <br>An openthings message context.  |
| struct | **[openthings_message_header](Classes/structopenthings__message__header.md)** <br>An openthings message header.  |
| union | **[openthings_type_description](Classes/unionopenthings__type__description.md)** <br>An openthings type description.  |
| struct | **[openthings_message_record](Classes/structopenthings__message__record.md)** <br>An openthings record.  |
| struct | **[openthings_message_footer](Classes/structopenthings__message__footer.md)** <br>An openthings message footer.  |

## Types

|                | Name           |
| -------------- | -------------- |
| enum | **[openthings_parameter](Files/openthings_8h.md#enum-openthings_parameter)** { ALARM = 0x21, DBG = 0x2D, IDENTIFY = 0x3F, SOURCE_SELECTOR = 0xC0, WATER_DETECTOR = 0x41, GLASS_BREAKAGE = 0x42, CLOSURES = 0x43, DOOR_BELL = 0x44, ENERGY = 0x45, FALL_SENSOR = 0x46, GAS_VOLUME = 0x47, AIR_PRESSURE = 0x48, ILLUMINANCE = 0x49, LEVEL = 0x4C, RAINFALL = 0x4D, APPARENT_POWER = 0x50, POWER_FACTOR = 0x51, REPORT_PERIOD = 0x52, SMOKE_DETECTOR = 0x53, TIME_DATE = 0x54, VIBRATION = 0x56, WATER_VOLUME = 0x57, WIND_SPEED = 0x58, GAS_PRESSURE = 0x61, BATTERY_LEVEL = 0x62, CO_DETECTOR = 0x63, DOOR_SENSOR = 0x64, EMERGENCY_PANIC_BUTTON = 0x65, FREQUENCY = 0x66, GAS_FLOW_RATE = 0x67, RELATIVE_HUMIDITY = 0x68, CURRENT = 0x69, JOIN = 0x6A, RF_QUALITY = 0x6B, LIGHT_LEVEL = 0x6C, MOTION_DETECTOR = 0x6D, OCCUPANCY = 0x6F, REAL_POWER = 0x70, REACTIVE_POWER = 0x71, ROTATION_SPEED = 0x72, SWITCH_STATE = 0x73, TEMPERATURE = 0x74, VOLTAGE = 0x76, WATER_FLOW_RATE = 0x77, WATER_PRESSURE = 0x78, PHASE1_POWER = 0x79, PHASE2_POWER = 0x7A, PHASE3_POWER = 0x7B, THREE_PHASE_TOTAL_POWER = 0x7C } |
| enum | **[openthings_type](Files/openthings_8h.md#enum-openthings_type)** { UNSIGNEDX0, UNSIGNEDX4, UNSIGNEDX8, UNSIGNEDX12, UNSIGNEDX16, UNSIGNEDX20, UNSIGNEDX24, CHARS, SIGNEDX0, SIGNEDX8, SIGNEDX12, SIGNEDX16, SIGNEDX24, ENUMERATION, RESERVED1, RESERVED2, FLOATING_POINT = 0x0F } |



## Functions

|                | Name           |
| -------------- | -------------- |
| void | **[openthings_close_message](Files/openthings_8h.md#function-openthings_close_message)**(struct [openthings_messge_context](Classes/structopenthings__messge__context.md) *const context) <br>Close an openthings message.  |
| void | **[openthings_reset_message_payload](Files/openthings_8h.md#function-openthings_reset_message_payload)**(struct [openthings_messge_context](Classes/structopenthings__messge__context.md) *const context) <br>Reset the message context.  |
| void | **[openthings_get_message_header](Files/openthings_8h.md#function-openthings_get_message_header)**(struct [openthings_messge_context](Classes/structopenthings__messge__context.md) *const context, struct [openthings_message_header](Classes/structopenthings__message__header.md) *const header) <br>Gets the openthings message context from the context.  |
| bool | **[openthings_open_message](Files/openthings_8h.md#function-openthings_open_message)**(struct [openthings_messge_context](Classes/structopenthings__messge__context.md) *const context) <br>Opens an openthings message context.  |
| void | **[openthings_init_message](Files/openthings_8h.md#function-openthings_init_message)**(struct [openthings_messge_context](Classes/structopenthings__messge__context.md) *const context, const uint8_t manufacturer_id, const uint8_t product_id, const uint32_t sensor_id) <br>Initalise an openthings message.  |
| bool | **[openthings_write_record](Files/openthings_8h.md#function-openthings_write_record)**(struct [openthings_messge_context](Classes/structopenthings__messge__context.md) *const context, struct [openthings_message_record](Classes/structopenthings__message__record.md) *const record) <br>Write an openthings record to a message context.  |
| bool | **[openthings_read_record](Files/openthings_8h.md#function-openthings_read_record)**(struct [openthings_messge_context](Classes/structopenthings__messge__context.md) *const context, const struct [openthings_message_record](Classes/structopenthings__message__record.md) * record) <br>Reads an openthings record from the context.  |
| void | **[openthings_encrypt_message](Files/openthings_8h.md#function-openthings_encrypt_message)**(struct [openthings_messge_context](Classes/structopenthings__messge__context.md) *const context, const uint8_t encryption_id, const uint16_t noise) <br>Encrypts the message bytes in the context. The encryption is based on simple linear shift encryption. In reality is it a form of encoding rather than encryption as it can be reversed relatively easily.  |
| void | **[openthings_decrypt_message](Files/openthings_8h.md#function-openthings_decrypt_message)**(struct [openthings_messge_context](Classes/structopenthings__messge__context.md) *const context, const uint8_t encryption_id) <br>Decrypt the message bytes in the context.  |


## Defines

|                | Name           |
| -------------- | -------------- |
|  | **[OPENTHINGS_MAX_MSG_SIZE](Files/openthings_8h.md#define-openthings_max_msg_size)**  |
|  | **[OPENTHINGS_MAX_REC_SIZE](Files/openthings_8h.md#define-openthings_max_rec_size)**  |



## Detailed Description

Openthings prototypes. 








**Author**: Derek Goslin 


















Copyright (c) 2020 Derek Goslin



## Types Documentation

### enum openthings_parameter


| Enumerator | Value | Description |
| ---------- | ----- | ----------- |
| ALARM | 0x21 |   |
| DBG | 0x2D |   |
| IDENTIFY | 0x3F |   |
| SOURCE_SELECTOR | 0xC0 |   |
| WATER_DETECTOR | 0x41 |   |
| GLASS_BREAKAGE | 0x42 |   |
| CLOSURES | 0x43 |   |
| DOOR_BELL | 0x44 |   |
| ENERGY | 0x45 |   |
| FALL_SENSOR | 0x46 |   |
| GAS_VOLUME | 0x47 |   |
| AIR_PRESSURE | 0x48 |   |
| ILLUMINANCE | 0x49 |   |
| LEVEL | 0x4C |   |
| RAINFALL | 0x4D |   |
| APPARENT_POWER | 0x50 |   |
| POWER_FACTOR | 0x51 |   |
| REPORT_PERIOD | 0x52 |   |
| SMOKE_DETECTOR | 0x53 |   |
| TIME_DATE | 0x54 |   |
| VIBRATION | 0x56 |   |
| WATER_VOLUME | 0x57 |   |
| WIND_SPEED | 0x58 |   |
| GAS_PRESSURE | 0x61 |   |
| BATTERY_LEVEL | 0x62 |   |
| CO_DETECTOR | 0x63 |   |
| DOOR_SENSOR | 0x64 |   |
| EMERGENCY_PANIC_BUTTON | 0x65 |   |
| FREQUENCY | 0x66 |   |
| GAS_FLOW_RATE | 0x67 |   |
| RELATIVE_HUMIDITY | 0x68 |   |
| CURRENT | 0x69 |   |
| JOIN | 0x6A |   |
| RF_QUALITY | 0x6B |   |
| LIGHT_LEVEL | 0x6C |   |
| MOTION_DETECTOR | 0x6D |   |
| OCCUPANCY | 0x6F |   |
| REAL_POWER | 0x70 |   |
| REACTIVE_POWER | 0x71 |   |
| ROTATION_SPEED | 0x72 |   |
| SWITCH_STATE | 0x73 |   |
| TEMPERATURE | 0x74 |   |
| VOLTAGE | 0x76 |   |
| WATER_FLOW_RATE | 0x77 |   |
| WATER_PRESSURE | 0x78 |   |
| PHASE1_POWER | 0x79 |   |
| PHASE2_POWER | 0x7A |   |
| PHASE3_POWER | 0x7B |   |
| THREE_PHASE_TOTAL_POWER | 0x7C |   |





























The default list of parameter identifiers. 


### enum openthings_type


| Enumerator | Value | Description |
| ---------- | ----- | ----------- |
| UNSIGNEDX0 |  |   |
| UNSIGNEDX4 |  |   |
| UNSIGNEDX8 |  |   |
| UNSIGNEDX12 |  |   |
| UNSIGNEDX16 |  |   |
| UNSIGNEDX20 |  |   |
| UNSIGNEDX24 |  |   |
| CHARS |  |   |
| SIGNEDX0 |  |   |
| SIGNEDX8 |  |   |
| SIGNEDX12 |  |   |
| SIGNEDX16 |  |   |
| SIGNEDX24 |  |   |
| ENUMERATION |  |   |
| RESERVED1 |  |   |
| RESERVED2 |  |   |
| FLOATING_POINT | 0x0F |   |





























The list of types supported. 



## Functions Documentation

### function openthings_close_message

```cpp
void openthings_close_message(
    struct openthings_messge_context *const context
)
```

Close an openthings message. 

**Parameters**: 

  * **context** The openthings message context.







**Return**: void 




















The context must be allocated by the caller.


### function openthings_reset_message_payload

```cpp
void openthings_reset_message_payload(
    struct openthings_messge_context *const context
)
```

Reset the message context. 

**Parameters**: 

  * **context** The openthings message context.







**Return**: void 



















The context must be allocated by the caller.


The context must be allocated by the caller.


### function openthings_get_message_header

```cpp
void openthings_get_message_header(
    struct openthings_messge_context *const context,
    struct openthings_message_header *const header
)
```

Gets the openthings message context from the context. 

**Parameters**: 

  * **context** The openthings message context. 
  * **header** The openthings message header.







**Return**: void 




















The context must be allocated by the caller. The header must be allocated by the caller.


### function openthings_open_message

```cpp
bool openthings_open_message(
    struct openthings_messge_context *const context
)
```

Opens an openthings message context. 

**Parameters**: 

  * **context** The openthings message context.







**Return**: bool A return value of true indicates if the open succeeded i.e. the integrity of the message is correct (CRC) 




















The context must be allocated by the caller.

This function performs validation of the message structure


### function openthings_init_message

```cpp
void openthings_init_message(
    struct openthings_messge_context *const context,
    const uint8_t manufacturer_id,
    const uint8_t product_id,
    const uint32_t sensor_id
)
```

Initalise an openthings message. 

**Parameters**: 

  * **context** The openthings message context. 
  * **manufacturer_id** The manufacturer Id. 
  * **product_id** The product Id. 
  * **sensor_id** The sensor Id.







**Return**: void 




















The context must be allocated by the caller.


### function openthings_write_record

```cpp
bool openthings_write_record(
    struct openthings_messge_context *const context,
    struct openthings_message_record *const record
)
```

Write an openthings record to a message context. 

**Parameters**: 

  * **context** The openthings message context. 
  * **record** The openthings record to write to the context.







**Return**: bool A return value of true indicates if the write succeeded i.e. that there was enough room in the buffer 





















### function openthings_read_record

```cpp
bool openthings_read_record(
    struct openthings_messge_context *const context,
    const struct openthings_message_record * record
)
```

Reads an openthings record from the context. 

**Parameters**: 

  * **context** The openthings message context. 
  * **record** The openthings record to read from the context.







**Return**: bool A return value of true indicates that the read succeeded and there are potentially more records contained within the context. A value of false indicates that there are no more records to be read. 




















The context must be allocated by the caller. The record must be allocated by the caller.

The record must be reused on each call to the openthings_read_record as it is context for the next read from the message context.


### function openthings_encrypt_message

```cpp
void openthings_encrypt_message(
    struct openthings_messge_context *const context,
    const uint8_t encryption_id,
    const uint16_t noise
)
```

Encrypts the message bytes in the context. The encryption is based on simple linear shift encryption. In reality is it a form of encoding rather than encryption as it can be reversed relatively easily. 

**Parameters**: 

  * **context** The openthings message context. 
  * **encryption_id** The encryption id 
  * **noise** The noise source value for randomizing encryption







**Return**: void 





















### function openthings_decrypt_message

```cpp
void openthings_decrypt_message(
    struct openthings_messge_context *const context,
    const uint8_t encryption_id
)
```

Decrypt the message bytes in the context. 

**Parameters**: 

  * **context** The openthings message context. 
  * **encryption_id** The encryption id







**Return**: void 























## Macro Documentation

### define OPENTHINGS_MAX_MSG_SIZE

```cpp
#define OPENTHINGS_MAX_MSG_SIZE     255
```



























The maximum size of an openthings message. 


### define OPENTHINGS_MAX_REC_SIZE

```cpp
#define OPENTHINGS_MAX_REC_SIZE     16
```



























The maximum size of an openthings message record. 




## Source code

```cpp

#ifndef OPENTHINGS_H_
#define OPENTHINGS_H_

#include <stdint.h>
#include <stdbool.h>

#include "crosscompile.h"

#define OPENTHINGS_MAX_MSG_SIZE                                                \
    255 
#define OPENTHINGS_MAX_REC_SIZE                                                \
    16 
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
    uint8_t
        buffer[OPENTHINGS_MAX_MSG_SIZE]; 
    uint8_t eom; 
};

struct __CROSS_ATTR_PACKED openthings_message_header {
    uint8_t hdr_len; 
    uint8_t manu_id; 
    uint8_t prod_id; 
    uint8_t pip_1;   
    uint8_t pip_0;   
    uint8_t sensor_id_2; 
    uint8_t sensor_id_1; 
    uint8_t sensor_id_0; 
};

union __CROSS_ATTR_PACKED openthings_type_description {
    uint8_t value; 
    struct {
        uint8_t len : 4;               
        enum openthings_type type : 4; 
    };
};

struct __CROSS_ATTR_PACKED openthings_message_record {
    enum openthings_parameter parameter; 
    union openthings_type_description
        description;                       
    uint8_t data[OPENTHINGS_MAX_REC_SIZE]; 
};

struct __CROSS_ATTR_PACKED openthings_message_footer {
    uint8_t eod; 
    int16_t crc; 
};

void openthings_close_message(
    struct openthings_messge_context *const context );

void openthings_reset_message_payload(
    struct openthings_messge_context *const context );

void openthings_get_message_header(
    struct openthings_messge_context *const context,
    struct openthings_message_header *const header );

bool openthings_open_message( struct openthings_messge_context *const context );

void openthings_init_message( struct openthings_messge_context *const context,
                              const uint8_t manufacturer_id,
                              const uint8_t product_id,
                              const uint32_t sensor_id );

bool openthings_write_record( struct openthings_messge_context *const context,
                              struct openthings_message_record *const record );

bool openthings_read_record( struct openthings_messge_context *const context,
                             const struct openthings_message_record *record );

void openthings_encrypt_message(
    struct openthings_messge_context *const context,
    const uint8_t encryption_id, const uint16_t noise );

void openthings_decrypt_message(
    struct openthings_messge_context *const context,
    const uint8_t encryption_id );
#endif /* OPENTHINGS_H_ */
```


-------------------------------

Updated on 11 December 2020 at 15:08:39 GMT Standard Time
