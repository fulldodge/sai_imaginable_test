#include "sai.h"
#include <stdio.h>

// Global port API table
static sai_port_api_t g_port_api;

// Helper function: set_port_attribute
static sai_status_t _set_port_attribute(sai_object_id_t port_id, const sai_attribute_t *attr) {
    if (!attr) return SAI_STATUS_FAILURE;

    if (attr->id == SAI_PORT_ATTR_ADMIN_STATE) {
        printf("[SAI] Port 0x%llx set ADMIN_STATE = %s\n", port_id, attr->value.booldata ? "UP" : "DOWN");
        return SAI_STATUS_SUCCESS;
    }
    if (attr->id == SAI_PORT_ATTR_MTU) {
        printf("[SAI] Port 0x%llx set MTU = %u\n", port_id, attr->value.u32);
        return SAI_STATUS_SUCCESS;
    }
    return SAI_STATUS_FAILURE;
}

// sai_api_initialize implementation
sai_status_t sai_api_initialize(uint64_t flags, const void *services) {
    printf("[SAI] Initialized (mock)\n");
    return SAI_STATUS_SUCCESS;
}

//  sai_api_uninitialize implementation
sai_status_t sai_api_uninitialize(void) {
    printf("[SAI] Uninitialized (mock)\n");
    return SAI_STATUS_SUCCESS;
}

//  sai_api_query implementation
sai_status_t sai_api_query(sai_api_t api_id, void **api_method_table) {
    if (!api_method_table) return SAI_STATUS_FAILURE;

    if (api_id == SAI_API_PORT) {
        g_port_api.set_port_attribute = _set_port_attribute;
        *api_method_table = &g_port_api;
        return SAI_STATUS_SUCCESS;
    }
    return SAI_STATUS_FAILURE;
}