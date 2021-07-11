#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "rp.h"


unsigned int  init_key[64];// 64 bit array size for init_key.
unsigned int bit_period_low=560;//in uS.
unsigned int bit_period_high=595;//in uS.
unsigned int sample_size=105;
unsigned int array_size=105;


rp_pinState_t state; //acquired array of states from input pin
int unsigned period=100;//uS
int unsigned count=0; //sampled value count.

void ir_input_buffer();

int main (int argc, char **argv) {

    // Initialization of API
    if (rp_Init() != RP_OK) {
        fprintf(stderr, "Red Pitaya API init failed!\n");
        return EXIT_FAILURE;
    }


    int state_arr[array_size];

    // configure DIO[0]_N to outputs
    rp_DpinSetDirection (RP_DIO0_N, RP_OUT);
    rp_DpinSetDirection (RP_DIO1_N, RP_OUT);
    rp_DpinSetDirection (RP_DIO2_N,RP_OUT);

    //input pin for ir_bits.
    rp_DpinSetDirection (RP_DIO7_N,RP_IN);



    int unsigned i=1;
    // transfer each input state to the corresponding LED state
    while (1) {


    	ir_input_buffer(state_arr);

    	rp_DpinSetState (RP_DIO2_N, RP_HIGH);
        rp_DpinSetState (RP_DIO0_N, RP_HIGH);
        if(i%8==0){
        	rp_DpinSetState(RP_DIO1_N,RP_HIGH);
        }
        else{
        	rp_DpinSetState(RP_DIO1_N,RP_LOW);
        }

        usleep(period/2);

        rp_DpinSetState (RP_DIO0_N, RP_LOW);
        rp_DpinSetState(RP_DIO1_N,RP_LOW);

        usleep(period/2);

        i++;
        //printf("This is working %u \n ",i);
    }

    // Releasing resources
    rp_Release();

    return EXIT_SUCCESS;
}

void ir_input_buffer(int *state_arr){

    rp_pinState_t init_state;
    while(1){
    	rp_DpinGetState(RP_DIO7_N,&init_state);
    	 //printf("\ninit_state: %d",init_state);
    	if(init_state==RP_LOW){
    		usleep(bit_period_low/2);
    		break;}
    	//printf("state is HIGH\n");
    	//printf("please press a button!!\n");
    }

    for(int i=0;i<sample_size;i++){
    	rp_DpinGetState(RP_DIO7_N,&state);
    	 //printf("\nstate:%d %d",i,state);

    		if(state==RP_LOW)
    		{
    			state_arr[i]=0;
    			usleep(bit_period_low);

    		}
    		else {
    			state_arr[i]=1;
    			usleep(bit_period_high);
    		}


    }
    printf("\nsignal successfully acquired!!\n");

    for(int i=0;i<array_size;i++){
    	    	printf("%d",state_arr[i]);
    }
    printf("\n");

}
