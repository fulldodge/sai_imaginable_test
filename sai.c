#include <stdio.h>
#include "sai.h"
#include <stdbool.h>

int main() 
{
    // 1. Sai initializate. Return SAI_STATUS_SUCCESS if succeed. Return -1 if init failed.
    if (sai_api_initialize(0, NULL) != SAI_STATUS_SUCCESS) {
        printf("INIT ERROR\n");
        return -1;
    }

    // 2. Get API port. Return func table for managing ports.
    sai_port_api_t *port_api;
    if (sai_api_query(SAI_API_PORT, (void**)&port_api) != SAI_STATUS_SUCCESS) {
        printf("Cant receive API port\n");
        sai_api_uninitialize();
        return -1;
    }

    // 3. Create attribute: id = attribute type; Value.booldata = turn on/turn off(true/false);
    // Turn on port. 
    sai_attribute_t attr;
    attr.id = SAI_PORT_ATTR_ADMIN_STATE;
    attr.value.booldata = true;

    // 4. Apply ID on port (0x1000000000001 example).
    sai_object_id_t port_id = 0x1000000000001;
    if (port_api->set_port_attribute(port_id, &attr) == SAI_STATUS_SUCCESS) {
        printf("Port enabled\n");
    } else {
        printf("Port cannot be enabled\n");
    }

    // 5. Port uninitialize.
    sai_api_uninitialize();
    return 0;
}
