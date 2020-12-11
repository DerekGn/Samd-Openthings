---
title: openthings_type_description
summary: An openthings type description.  

---

# openthings_type_description




An openthings type description.  [More...](#detailed-description)


`#include <openthings.h>`



















## Public Attributes

|                | Name           |
| -------------- | -------------- |
| uint8_t | **[value](/doxybook2/mkdocs-readthedocs/Classes/unionopenthings__type__description/#variable-value)**  |
| uint8_t | **[len](/doxybook2/mkdocs-readthedocs/Classes/unionopenthings__type__description/#variable-len)**  |
| enum [openthings_type](/doxybook2/mkdocs-readthedocs/Files/openthings_8h/#enum-openthings_type) | **[type](/doxybook2/mkdocs-readthedocs/Classes/unionopenthings__type__description/#variable-type)**  |
| struct openthings_type_description::@0 | **[@1](/doxybook2/mkdocs-readthedocs/Classes/unionopenthings__type__description/#variable-@1)**  |







## Detailed Description

```cpp
union openthings_type_description;
```

An openthings type description. 


























Represents an openthings type description. The first 4 bits of a recordtype description byte define the type of the data value being sent (e.g. integer, float). The last 4 bits define the length of the data value being sent (in bytes) 















## Public Attributes Documentation

### variable value

```cpp
uint8_t value;
```



























The value of the openthings type description. 


### variable len

```cpp
uint8_t len;
```



























The length of the data. 


### variable type

```cpp
enum openthings_type type;
```



























The type of the data. 


### variable @1

```cpp
struct openthings_type_description::@0 @1;
```

































-------------------------------

Updated on 11 December 2020 at 15:36:12 GMT Standard Time