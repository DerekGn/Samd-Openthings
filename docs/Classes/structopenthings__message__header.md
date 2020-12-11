---
title: openthings_message_header
summary: An openthings message header.  

---

# openthings_message_header




An openthings message header.  [More...](#detailed-description)


`#include <openthings.h>`



















## Public Attributes

|                | Name           |
| -------------- | -------------- |
| uint8_t | **[hdr_len](/doxybook2/mkdocs-readthedocs/Classes/structopenthings__message__header/#variable-hdr_len)**  |
| uint8_t | **[manu_id](/doxybook2/mkdocs-readthedocs/Classes/structopenthings__message__header/#variable-manu_id)**  |
| uint8_t | **[prod_id](/doxybook2/mkdocs-readthedocs/Classes/structopenthings__message__header/#variable-prod_id)**  |
| uint8_t | **[pip_1](/doxybook2/mkdocs-readthedocs/Classes/structopenthings__message__header/#variable-pip_1)**  |
| uint8_t | **[pip_0](/doxybook2/mkdocs-readthedocs/Classes/structopenthings__message__header/#variable-pip_0)**  |
| uint8_t | **[sensor_id_2](/doxybook2/mkdocs-readthedocs/Classes/structopenthings__message__header/#variable-sensor_id_2)**  |
| uint8_t | **[sensor_id_1](/doxybook2/mkdocs-readthedocs/Classes/structopenthings__message__header/#variable-sensor_id_1)**  |
| uint8_t | **[sensor_id_0](/doxybook2/mkdocs-readthedocs/Classes/structopenthings__message__header/#variable-sensor_id_0)**  |







## Detailed Description

```cpp
struct openthings_message_header;
```

An openthings message header. 


























Represents an openthings message header 















## Public Attributes Documentation

### variable hdr_len

```cpp
uint8_t hdr_len;
```



























The message header length. Number of bytes in whole message excluding this byte. 


### variable manu_id

```cpp
uint8_t manu_id;
```



























The manufacturer Id. 


### variable prod_id

```cpp
uint8_t prod_id;
```



























The product Id. 


### variable pip_1

```cpp
uint8_t pip_1;
```



























Reserved bytes. Used for encryption seed byte 1. 


### variable pip_0

```cpp
uint8_t pip_0;
```



























Reserved bytes. Used for encryption seed byte 0. 


### variable sensor_id_2

```cpp
uint8_t sensor_id_2;
```



























Byte 2 of the sensor Id. 


### variable sensor_id_1

```cpp
uint8_t sensor_id_1;
```



























Byte 1 of the sensor Id. 


### variable sensor_id_0

```cpp
uint8_t sensor_id_0;
```



























Byte 0 of the sensor Id. 






-------------------------------

Updated on 11 December 2020 at 15:36:12 GMT Standard Time