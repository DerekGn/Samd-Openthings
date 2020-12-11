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
| enum [openthings_parameter](/doxybook2/mkdocs-readthedocs/Files/openthings_8h/#enum-openthings_parameter) | **[parameter](/doxybook2/mkdocs-readthedocs/Classes/structopenthings__message__record/#variable-parameter)**  |
| union [openthings_type_description](/doxybook2/mkdocs-readthedocs/Classes/unionopenthings__type__description/) | **[description](/doxybook2/mkdocs-readthedocs/Classes/structopenthings__message__record/#variable-description)**  |
| uint8_t | **[data](/doxybook2/mkdocs-readthedocs/Classes/structopenthings__message__record/#variable-data)**  |







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

Updated on 11 December 2020 at 15:36:12 GMT Standard Time