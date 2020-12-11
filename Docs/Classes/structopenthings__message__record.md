---
title: openthings_message_record
summary: An openthings record.  

---

# openthings_message_record




An openthings record.  [More...](#detailed-description)


`#include <openthings.h>`



















## Public Attributes

|                | Name           |
| -------------- | -------------- |
| enum [openthings_parameter](Files/openthings_8h.md#enum-openthings_parameter) | **[parameter](Classes/structopenthings__message__record.md#variable-parameter)**  |
| union [openthings_type_description](Classes/unionopenthings__type__description.md) | **[description](Classes/structopenthings__message__record.md#variable-description)**  |
| uint8_t | **[data](Classes/structopenthings__message__record.md#variable-data)**  |







## Detailed Description

```cpp
struct openthings_message_record;
```

An openthings record. 


























Represents an openthings record. 















## Public Attributes Documentation

### variable parameter

```cpp
enum openthings_parameter parameter;
```



























The record parameter. 


### variable description

```cpp
union openthings_type_description description;
```



























The record type description. 


### variable data

```cpp
uint8_t data;
```



























The parameter value. 






-------------------------------

Updated on 11 December 2020 at 15:08:38 GMT Standard Time