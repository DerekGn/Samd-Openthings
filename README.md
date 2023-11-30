# SAMD Openthings

A library for the serializing and deserializing of [Openthings](http://www.o-things.com/) compliant messages targeting the Microchip SAMD21 series of Arm® Cortex®-M0+ CPU's.

The openthings protocol is used in a number of Energenie mihome products.

The library has no external dependencies and can be re-targeted to other classes of mcu.

The library implements read,write and encrypt and decrypt of openthings messages.

Note the encryption as defined in the openthings specification is not really encryption more specifically it is a form of encoding. The encryption is based around linear shift encryption. It is therefore not advisable to use it for communications that require security from eavesdropping or tampering of messages. It has been included in the library so that it is compatible with existing sensors etc.

It is preferable to use other secure transport mechanisms than rely on the linear shift mechanism.

## Compatiblity

This library is compatible with the python library [whaleygeek pyenergenie](https://github.com/whaleygeek/pyenergenie)

## Code Size

### Release

text | data | bss | dec | hex | filename | build
---------|----------|---------|---------|---------|---------|---------
390 | 0 | 0 | 390 | 186 | openthings_decoding.o (ex libopenthings.a) | release
683 | 0 | 0 | 683 | 2ab | encrypt.o (ex libopenthings.a) | release
112 | 0 | 2 | 114 | 72 | openthings_encoding.o (ex libopenthings.a) | release
452 | 0 | 0 | 436 | 1c4 | openthings.o (ex libopenthings.a) | release

## Using the library

### Write Openthings Context

``` C
    struct openthings_message_context context;
    
    // Init the context
    openthings_init_message( &context, 0xAA, 0x55, 0xDEADBEEF );

    struct openthings_message_record record;

    record.parameter = ALARM;
    record.description.len = 2;
    record.description.type = UNSIGNEDX0;
    record.data[0] = 0x1;
    record.data[1] = 0x2;

    // Add a record
    openthings_write_record( &context, &record );

    record.parameter = REAL_POWER;
    record.description.len = 1;
    record.description.type = UNSIGNEDX0;
    record.data[0] = 0xAA;

    openthings_write_record( &context, &record );

    // Close the message
    openthings_close_message( &context );
```

### Read Openthings Context

``` c

uint8_t i = 0;

if ( openthings_open_message( &context ) ) {
    struct openthings_message_record record;

    while ( openthings_read_record( &context, &record ) ) {
        if ( i == 0 ) {
            if ( record.parameter != ALARM ) {
                // process record
            }
        }

        if ( i == 1 ) {
            if ( record.parameter != REAL_POWER ) {
                // process record
            }
        }

        i++;
    };
}
```

### Encrypt Openthings Context

``` c
// Encrypt the context passing encryption id and noise seed
openthings_encrypt_message( &context, 10, 0xF4 );

```

### Decrypt Openthings Context

``` c
// Decrypt the context passing encryption id
openthings_decrypt_message( &context, 10 );
```

## Optional Encoding and Decoding Openthings Message Records

In most cases it is trivial to encode openthings_message_record. However the SAMD openthings library includes an additional module to support encoding and decoding of various types to openthings_message_record instances. This module is optional.

### Encode Float

Encoded floats may be either signed or unsigned.

```c
struct openthings_message_record record;

// Set parameter type
record.parameter = GAS_VOLUME;

enum openthings_encoding_status status;

status = openthings_encode_record_message_float(&record, FLOAT_ENCODING_UNSIGNEDX4, 1.45 );
```

### Encode Int

Encoded integers may be either signed or unsigned.

```c
struct openthings_message_record record;

// Set parameter type
record.parameter = LEVEL;

enum openthings_encoding_status status;

status = openthings_encode_record_message_int(&record, -203);
```

## Encode String

```c
struct openthings_message_record record;

// Set parameter type
record.parameter = DBG;

enum openthings_encoding_status status;

status = openthings_encode_record_message_string(&record, "TEST MESSAGE");
```

## Encode Unsigned Int

```c
struct openthings_message_record record;

// Set parameter type
record.parameter = LEVEL;

enum openthings_encoding_status status;

status = openthings_encode_record_message_uint(&record, 2837);
```

## Decoding Float

The openthings_decode_record_message_float function will validate the record type and decode any float value that it can find in the record. The float value can be signed or unsigned.

```c
struct openthings_message_record record;

// Read record from context
openthings_read_record( &context, &record);

float value;

enum openthings_decoding_status status = openthings_decode_record_message_float(&record, &value);
```

## Decode Intger

```c
struct openthings_message_record record;

// Read record from context
openthings_read_record( &context, &record);

int32_t value;

enum openthings_decoding_status status = openthings_decode_record_message_int(&record, &value);
```

## Decode Unsigned Integer

```c
struct openthings_message_record record;

// Read record from context
openthings_read_record( &context, &record);

uint32_t value;

enum openthings_decoding_status status = openthings_decode_record_message_uint(&record, &value);
```

## Unit Tests

The library has been unit tested using the [ceedling](https://github.com/ThrowTheSwitch/Ceedling) build/test system for c. Once ceedling has been installed the tests can be compiled and executed from \SamdOpenthings\Openthings.Tests

Execute _ceedling test:all_ to run the tests.
