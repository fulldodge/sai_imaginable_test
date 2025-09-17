#ifndef __SAI_H_
#define __SAI_H_

#include <stdint.h>  // Required for uint64_t, int32_t, etc.

typedef enum _sai_status_t {
    SAI_STATUS_SUCCESS = 0,
    SAI_STATUS_FAILURE = -1
} sai_status_t;

typedef uint64_t sai_object_id_t;
typedef uint32_t sai_uint32_t;
typedef int32_t sai_int32_t;
typedef uint8_t sai_uint8_t;
typedef unsigned char bool;

// sai_attribute_t declaration
struct _sai_attribute_t;

// Port API structure
typedef struct _sai_port_api_t {
    sai_status_t (*set_port_attribute)(sai_object_id_t port_id, const struct _sai_attribute_t *attr);
} sai_port_api_t;

// Initialize SAI
sai_status_t sai_api_initialize(uint64_t flags, const void *services);

// Uninitialize SAI
sai_status_t sai_api_uninitialize(void);

// Query API to get method table
typedef enum _sai_api_t {
    SAI_API_PORT = 0x00000001
} sai_api_t;

sai_status_t sai_api_query(sai_api_t api_id, void **api_method_table);

// Port attribute IDs
typedef enum _sai_port_attr_t {
    SAI_PORT_ATTR_ADMIN_STATE = 0x10000000,
    SAI_PORT_ATTR_MTU = 0x10000001
} sai_port_attr_t;

// Attribute value union
typedef struct _sai_attribute_value_t {
    bool booldata;
    sai_uint32_t u32;
} sai_attribute_value_t;

// Attribute structure
typedef struct _sai_attribute_t {
    sai_int32_t id;
    sai_attribute_value_t value;
} sai_attribute_t;

#endif