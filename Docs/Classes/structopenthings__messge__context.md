---
title: openthings_messge_context
summary: An openthings message context.  

---

# openthings_messge_context




An openthings message context.  [More...](#detailed-description)


`#include <openthings.h>`



















## Public Attributes

|                | Name           |
| -------------- | -------------- |
| uint8_t | **[buffer](Classes/structopenthings__messge__context.md#variable-buffer)**  |
| uint8_t | **[eom](Classes/structopenthings__messge__context.md#variable-eom)**  |







## Detailed Description

```cpp
struct openthings_messge_context;
```

An openthings message context. 


























The context used for reading and writing openthings message and records data. 















## Public Attributes Documentation

### variable buffer

```cpp
uint8_t buffer;
```



























The sequential byte buffer that a message is read and written too. 


### variable eom

```cpp
uint8_t eom;
```



























The current end of message marker. 






-------------------------------

Updated on 11 December 2020 at 15:08:38 GMT Standard Time