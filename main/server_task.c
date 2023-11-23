#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

#include "esp_log.h"
#include "config.h"
#include "address.h"
#include "bacdef.h"
#include "handlers.h"
#include "client.h"
#include "dlenv.h"
#include "bacdcode.h"
#include "npdu.h"
#include "apdu.h"
#include "iam.h"
#include "tsm.h"
#include "datalink.h"
#include "dcc.h"
#include "getevent.h"
#include "net.h"
#include "txbuf.h"
#include "version.h"
#include "device.h"
#include "bi.h"
#include "ai.h"
#include "bv.h"
#include "av.h"
#include "led.h"
#include "server_task.h"

static const char *TAG = "server";

/** Buffer used for receiving */
static uint8_t rx_buffer[MAX_MPDU] = { 0 };

void server_task(void *arg)
{
    BACNET_ADDRESS src = {
        0
    }; 
    
    uint16_t pdu_len = 0;
	
    for (;;) {
        pdu_len = datalink_receive(&src, &rx_buffer[0], MAX_MPDU, 5000);

        if (pdu_len) {
            npdu_handler(&src, &rx_buffer[0], pdu_len);

            if (Analog_Value_Present_Value(0) == 1)
            {
                led_on();
            }
            else
            {
                led_off();
            }
        }
    }
}

