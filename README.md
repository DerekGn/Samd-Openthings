# SAMD Openthings

A library for the serializing and deserializing of [Openthings](http://www.o-things.com/) compliant messages targeting the Microchip SAMD21 series of Arm® Cortex®-M0+ CPU's.

The openthings protocol is used in a number of energenie mihome products.

The library has no external dependencies and can be re targeted to other classes of mcu.

The library implements read,write and encrypt and decrypt of openthings messages.

Note the encryption as defined in the openthings specification is not really encryption more specifically it is a form of encoding. The encryption is based around linear shift encryption. It is therefore not advisable to use it for communications that require security from eavesdropping or tampering of messages. It has been included in the library so that it is compatible with existing sensors etc.

It is preferable to use other secure transport mechanisms than rely on the linear shift mechanism.

## Code Size

### Release

text | data | bss | dec | hex | filename | build
---------|----------|---------|---------|---------|---------|---------
112 | 0 | 2 | 114 | 72 | encrypt.o (ex libopenthings.a) | release
448 | 0 | 0 | 448 | 1c0 | openthings.o (ex libopenthings.a) | release


**encrypt.o   (ex libopenthings.a):**

section | size | addr
---------|----------|---------
.text | 0x0 | 0x0
.data | 0x0 | 0x0
.bss | 0x2 | 0x0
.text.randomise_seed | 0x18 | 0x0
.text.encrypt_decrypt | 0x38 | 0x0
.text.generate_pip | 0x10 | 0x0
.text.seed | 0x10 | 0x0
.comment | 0x5a | 0x0
.ARM.attributes | 0x32 | 0x0
Total || 0xfe

**openthings.o   (ex libopenthings.a):**

section | size | addr
---------|----------|---------
.text | 0x0 | 0x0
.data | 0x0 | 0x0
.bss | 0x0 | 0x0
.text.crc | 0x34 | 0x0
.text.openthings_init_message | 0x20 | 0x0
.text.openthings_write_record | 0x3c | 0x0
.text.openthings_read_record | 0x3c | 0x0
.text.openthings_encrypt_message | 0x3c | 0x0
.text.openthings_decrypt_message | 0x30 | 0x0
.text.openthings_close_message | 0x30 | 0x0
.text.openthings_reset_message_payload | 0x8 | 0x0
.text.openthings_get_message_header | 0x14 | 0x0
.text.openthings_open_message | 0x3c | 0x0
.comment | 0x5a | 0x0
.ARM.attributes | 0x32 | 0x0
Total || 0x24c

## Unit Tests

The library has been unit tested using the [ceedling](https://github.com/ThrowTheSwitch/Ceedling) build/test system for c. Once ceedling has been installed the tests can be compiled and executed from 