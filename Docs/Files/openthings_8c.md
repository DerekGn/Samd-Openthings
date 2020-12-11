---
title: openthings.c
summary: Openthings implementation.  

---

# openthings.c


Openthings implementation.  [More...](#detailed-description)










## Functions

|                | Name           |
| -------------- | -------------- |
| int16_t | **[crc](Files/openthings_8c.md#function-crc)**(const uint8_t const * buf, size_t size)  |
| void | **[openthings_init_message](Files/openthings_8c.md#function-openthings_init_message)**(struct [openthings_messge_context](Classes/structopenthings__messge__context.md) *const context, const uint8_t manufacturer_id, const uint8_t product_id, const uint32_t sensor_id) <br>Initalise an openthings message.  |
| bool | **[openthings_write_record](Files/openthings_8c.md#function-openthings_write_record)**(struct [openthings_messge_context](Classes/structopenthings__messge__context.md) *const context, struct [openthings_message_record](Classes/structopenthings__message__record.md) *const record) <br>Write an openthings record to a message context.  |
| bool | **[openthings_read_record](Files/openthings_8c.md#function-openthings_read_record)**(struct [openthings_messge_context](Classes/structopenthings__messge__context.md) *const context, const struct [openthings_message_record](Classes/structopenthings__message__record.md) * record) <br>Reads an openthings record from the context.  |
| void | **[openthings_encrypt_message](Files/openthings_8c.md#function-openthings_encrypt_message)**(struct [openthings_messge_context](Classes/structopenthings__messge__context.md) *const context, const uint8_t encryption_id, const uint16_t noise) <br>Encrypts the message bytes in the context. The encryption is based on simple linear shift encryption. In reality is it a form of encoding rather than encryption as it can be reversed relatively easily.  |
| void | **[openthings_decrypt_message](Files/openthings_8c.md#function-openthings_decrypt_message)**(struct [openthings_messge_context](Classes/structopenthings__messge__context.md) *const context, const uint8_t encryption_id) <br>Decrypt the message bytes in the context.  |
| void | **[openthings_close_message](Files/openthings_8c.md#function-openthings_close_message)**(struct [openthings_messge_context](Classes/structopenthings__messge__context.md) *const context) <br>Close an openthings message.  |
| void | **[openthings_reset_message_payload](Files/openthings_8c.md#function-openthings_reset_message_payload)**(struct [openthings_messge_context](Classes/structopenthings__messge__context.md) *const context) <br>Reset the message context.  |
| void | **[openthings_get_message_header](Files/openthings_8c.md#function-openthings_get_message_header)**(struct [openthings_messge_context](Classes/structopenthings__messge__context.md) *const context, struct [openthings_message_header](Classes/structopenthings__message__header.md) *const header) <br>Gets the openthings message context from the context.  |
| bool | **[openthings_open_message](Files/openthings_8c.md#function-openthings_open_message)**(struct [openthings_messge_context](Classes/structopenthings__messge__context.md) *const context) <br>Opens an openthings message context.  |


## Defines

|                | Name           |
| -------------- | -------------- |
|  | **[BYTE_0](Files/openthings_8c.md#define-byte_0)**(value)  |
|  | **[BYTE_1](Files/openthings_8c.md#define-byte_1)**(value)  |
|  | **[BYTE_2](Files/openthings_8c.md#define-byte_2)**(value)  |
|  | **[OPENTHINGS_CRC_START](Files/openthings_8c.md#define-openthings_crc_start)**  |
|  | **[RECORD_SIZE](Files/openthings_8c.md#define-record_size)**(record)  |



## Detailed Description

Openthings implementation. 








**Author**: Derek Goslin


















Copyright (c) 2020 Derek Goslin


MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 




## Functions Documentation

### function crc

```cpp
static int16_t crc(
    const uint8_t const * buf,
    size_t size
)
```





























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




## Macro Documentation

### define BYTE_0

```cpp
#define BYTE_0(
    value
)     ( (uint8_t)value & 0xff )
```



























Mask byte 0 from a value. 


### define BYTE_1

```cpp
#define BYTE_1(
    value
)     ( ( uint8_t )( value >> 8 ) & 0xff )
```



























Mask byte 1 from a value. 


### define BYTE_2

```cpp
#define BYTE_2(
    value
)     ( ( uint8_t )( value >> 16 ) & 0xff )
```



























Mask byte 2 from a value. 


### define OPENTHINGS_CRC_START

```cpp
#define OPENTHINGS_CRC_START     5
```



























The offset from the start of the openthings header that the CRC is \ calculated from 


### define RECORD_SIZE

```cpp
#define RECORD_SIZE(
    record
)     sizeof( enum [openthings_parameter](Files/openthings_8h.md#enum-openthings_parameter) ) +                                      \
        sizeof( union [openthings_type_description](Classes/unionopenthings__type__description.md) ) +                          \
        record->description.len
```



























A macro for calculating the total size of \ an openthings record. 




## Source code

```cpp

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "openthings.h"
#include "encrypt.h"

#define BYTE_0( value )                                                        \
    ( (uint8_t)value & 0xff ) 
#define BYTE_1( value )                                                        \
    ( ( uint8_t )( value >> 8 ) & 0xff ) 
#define BYTE_2( value )                                                        \
    ( ( uint8_t )( value >> 16 ) & 0xff ) 
#define OPENTHINGS_CRC_START                                                   \
    5 
#define RECORD_SIZE( record )                                                  \
    sizeof( enum openthings_parameter ) +                                      \
        sizeof( union openthings_type_description ) +                          \
        record->description.len 
static int16_t crc( const uint8_t const *buf, size_t size );

/*-----------------------------------------------------------*/
void openthings_init_message( struct openthings_messge_context *const context,
                              const uint8_t manufacturer_id,
                              const uint8_t product_id,
                              const uint32_t sensor_id )
{
    struct openthings_message_header
        *header = (struct openthings_message_header *)context->buffer;

    context->eom = 0;
    header->hdr_len = 0;
    header->manu_id = manufacturer_id;
    header->prod_id = product_id;
    header->pip_1 = 0;
    header->pip_0 = 0;
    header->sensor_id_0 = BYTE_0( sensor_id );
    header->sensor_id_1 = BYTE_1( sensor_id );
    header->sensor_id_2 = BYTE_2( sensor_id );

    context->eom += sizeof( struct openthings_message_header );
}
/*-----------------------------------------------------------*/
bool openthings_write_record( struct openthings_messge_context *const context,
                              struct openthings_message_record *const record )
{
    if ( context->eom + RECORD_SIZE( record ) +
             sizeof( struct openthings_message_footer ) <=
         OPENTHINGS_MAX_MSG_SIZE ) {
        memcpy( context->buffer + context->eom, record, RECORD_SIZE( record ) );

        context->eom += RECORD_SIZE( record );

        return true;
    }

    return false;
}
/*-----------------------------------------------------------*/
bool openthings_read_record( struct openthings_messge_context *const context,
                             const struct openthings_message_record *record )
{
    if ( context->buffer[context->eom] != 0 ) {
        struct openthings_message_record
            *current = (struct openthings_message_record *)( context->buffer +
                                                             context->eom );

        memcpy( (void *)record, current, RECORD_SIZE( current ) );

        context->eom += RECORD_SIZE( record );
        return true;
    }

    return false;
}
/*-----------------------------------------------------------*/
void openthings_encrypt_message(
    struct openthings_messge_context *const context,
    const uint8_t encryption_id, const uint16_t noise )
{
    struct openthings_message_header
        *header = (struct openthings_message_header *)context->buffer;

    size_t i = 0;
    uint16_t message_pip;

    randomise_seed( noise );
    message_pip = generate_pip( encryption_id );

    header->pip_0 = BYTE_0( message_pip );
    header->pip_1 = BYTE_1( message_pip );

    for ( i = OPENTHINGS_CRC_START; i <= header->hdr_len; ++i ) {
        context->buffer[i] = encrypt_decrypt( context->buffer[i] );
    }
}
/*-----------------------------------------------------------*/
void openthings_decrypt_message(
    struct openthings_messge_context *const context,
    const uint8_t encryption_id )
{
    struct openthings_message_header
        *header = (struct openthings_message_header *)context->buffer;

    uint16_t message_pip;
    size_t i;

    message_pip = ( ( ( (uint16_t)header->pip_1 ) << 8 ) | header->pip_0 );

    seed( encryption_id, message_pip );

    for ( i = OPENTHINGS_CRC_START; i <= header->hdr_len; ++i ) {
        context->buffer[i] = encrypt_decrypt( context->buffer[i] );
    }
}
/*-----------------------------------------------------------*/
void openthings_close_message( struct openthings_messge_context *const context )
{
    struct openthings_message_header
        *header = (struct openthings_message_header *)context->buffer;

    struct openthings_message_footer *footer =
        (struct openthings_message_footer *)( context->buffer + context->eom );

    footer->eod = 0;
    footer->crc = crc( &context->buffer[OPENTHINGS_CRC_START],
                       context->eom - OPENTHINGS_CRC_START );

    context->eom += sizeof( struct openthings_message_footer );

    header->hdr_len = context->eom - 1;
}
/*-----------------------------------------------------------*/
void openthings_reset_message_payload(
    struct openthings_messge_context *const context )
{
    context->eom = OPENTHINGS_CRC_START;
}
/*-----------------------------------------------------------*/
void openthings_get_message_header(
    struct openthings_messge_context *const context,
    struct openthings_message_header *const header )
{
    memcpy( header, context->buffer,
            sizeof( struct openthings_message_header ) );
}
/*-----------------------------------------------------------*/
bool openthings_open_message( struct openthings_messge_context *const context )
{
    bool result = false;

    struct openthings_message_header
        *header = (struct openthings_message_header *)context->buffer;

    uint8_t payload_len = header->hdr_len + 1;

    struct openthings_message_footer
        *footer = (struct openthings_message_footer
                       *)( ( context->buffer + payload_len ) -
                           sizeof( struct openthings_message_footer ) );

    int16_t calc_crc = crc(
        ( const uint8_t *const ) & context->buffer[OPENTHINGS_CRC_START],
        payload_len - OPENTHINGS_CRC_START -
            sizeof( struct openthings_message_footer ) );

    if ( footer->eod == 0 && footer->crc == calc_crc ) {
        context->eom = sizeof( struct openthings_message_header );

        result = true;
    }

    return result;
}
/*-----------------------------------------------------------*/
static int16_t crc( const uint8_t const *buf, size_t size )
{
    uint16_t rem = 0;
    size_t byte, bit;
    for ( byte = 0; byte < size; ++byte ) {
        rem ^= ( buf[byte] << 8 );
        for ( bit = 8; bit > 0; --bit ) {
            rem = ( ( rem & ( 1 << 15 ) ) ? ( ( rem << 1 ) ^ 0x1021 )
                                          : ( rem << 1 ) );
        }
    }
    return rem;
}
/*-----------------------------------------------------------*/
```


-------------------------------

Updated on 11 December 2020 at 15:08:38 GMT Standard Time
