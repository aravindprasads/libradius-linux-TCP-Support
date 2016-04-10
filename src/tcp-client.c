/*
 * example RADIUS client
 *
 * Send a message to a local RADIUS server for Authentication
 *
 */
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "include/radlib.h"
#include <sys/socket.h>
#include <sys/select.h>

int main() {

	struct rad_handle *rad_h = NULL;
	int rc = 0;
	
	if (!(rad_h = rad_auth_open())) {
		fprintf(stderr, "failed to create radius lib handle\n");
		return -1;	
	}

    /** Read the configuration data from radius.conf file */
    if (rad_config (rad_h, NULL) != 0)
    {
        fprintf(stderr, "Authentication configuration "
                "failure");
        rad_h = NULL;
        return -1;
    }

    if (rad_create_request(rad_h, RAD_ACCESS_REQUEST)) {
    	fprintf(stderr, "failed to add server: %s\n", rad_strerror(rad_h));
		return -1;	
    }

    rad_put_string(rad_h, RAD_USER_NAME, "admin");
    rad_put_string(rad_h, RAD_USER_PASSWORD, "admin");
    rad_put_int(rad_h, RAD_NAS_PORT, 4223);	

    switch((rc = rad_send_request(rad_h))) {
    case RAD_ACCESS_ACCEPT:
    	printf("Server - authentication sucess\n");
    	rc = 0;
    	break;

    case RAD_ACCESS_REJECT:
    	printf("Server - authentication failed\n");
    	rc = 0;
    	break;

    case -1:
    	fprintf(stderr, "Error while receiving response: %s\n", rad_strerror(rad_h));
    	break;

	default:
		fprintf(stderr, "Invalid message type in response: %d\n", rc);
		rc = -1;
    }

    rad_close(rad_h);
    return rc;
}
