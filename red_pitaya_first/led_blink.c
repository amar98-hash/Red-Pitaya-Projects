#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "rp.h"

int main (int argc, char **argv) {
    int unsigned period = 50000; // uS
    int unsigned led0,led1,led2,led3,led4,led5,led6,led7;

    // index of blinking LED can be provided as an argument
    if (argc > 1) {
        led0 = atoi(argv[1]);
        led1 = atoi(argv[2]);
        led2 = atoi(argv[3]);
        led3 = atoi(argv[4]);
        
    // otherwise LED 0 will blink
    } else {
        led0 = 0;
        led1= 1;
        led2=2;
        led3=3;
        led4 = 4;
        led5= 5;
        led6=6;
        led7=7;
    }
    
    printf("Blinking LED[%u]\n", led0);
    led0 = RP_LED0;
    led1 = RP_LED1;
    led2 = RP_LED2;
    led3 = RP_LED3;
    led4 = RP_LED4;
    led5 = RP_LED5;
    led6 = RP_LED6;
    led7 = RP_LED7;
    
    
 // Initialization of API
    if (rp_Init() != RP_OK) {
        fprintf(stderr, "Red Pitaya API init failed!\n");
        return EXIT_FAILURE;
    }

//-----------------------------------------



    int unsigned retries = 1000;
    while (retries--){
        rp_DpinSetState(led0, RP_HIGH);
     	usleep(period/2-period/8);
     	rp_DpinSetState(led1, RP_HIGH);
     	usleep(period/8);
        rp_DpinSetState(led0, RP_LOW);
        
    	usleep(period/2-period/8);        
        rp_DpinSetState(led2, RP_HIGH);
     	usleep(period/8);
     	rp_DpinSetState(led1, RP_LOW);
     	
     	usleep(period/2-period/8);        
        rp_DpinSetState(led3, RP_HIGH);
     	usleep(period/8);
     	rp_DpinSetState(led2, RP_LOW);
     	
     	usleep(period/2-period/8);        
        rp_DpinSetState(led4, RP_HIGH);
     	usleep(period/8);
     	rp_DpinSetState(led3, RP_LOW);
     	
        usleep(period/2-period/8);        
        rp_DpinSetState(led5, RP_HIGH);
     	usleep(period/8);
     	rp_DpinSetState(led4, RP_LOW);
        
        usleep(period/2-period/8);        
        rp_DpinSetState(led6, RP_HIGH);
     	usleep(period/8);
     	rp_DpinSetState(led5, RP_LOW);
     	
     	usleep(period/2-period/8);        
        rp_DpinSetState(led7, RP_HIGH);
     	usleep(period/8);
     	rp_DpinSetState(led6, RP_LOW);
     	
     	usleep(period/2);
     	rp_DpinSetState(led7, RP_LOW);
     	
    }

    // Releasing resources
    rp_Release();

    return EXIT_SUCCESS;
}

    