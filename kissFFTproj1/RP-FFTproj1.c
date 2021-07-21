
#include <stdio.h>
#include <stdlib.h>
#include "rp.h"
#include <time.h>
#include <unistd.h>    //usleep is here.

#include "kiss_fft.h"  //for FFTs iFFTs.

#define Ar_PI 3.14159265359

int main( int argc, char ** argv){

	//int period=8;


	//creates a full period sine wave.
	float SINE[]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	int period = sizeof(SINE)/sizeof(float);
	//for(int i=0;i<period;i++){
		//SINE[i]=sin(2*Ar_PI*i/period);

	//}

	usleep(1000);

	//first the kissfft's buffer is configured/
	kiss_fft_cfg mycfg=kiss_fft_alloc(period,0,NULL,NULL);

	kiss_fft_cpx *fin;
	kiss_fft_cpx *fout;
	fin = (kiss_fft_cpx*) malloc(sizeof(kiss_fft_cpx) * period);
	fout = (kiss_fft_cpx*) malloc(sizeof(kiss_fft_cpx) *period);

	for(int i=0; i<period;i++){
			fin[i].r=SINE[i];
			fin[i].i=0;
	 }

	 kiss_fft(mycfg, fin, fout);

		printf("The input\n");
	 for(int i=0; i<period;i++){
		 printf("%f+%f j\n",fin[i].r,fin[i].i);

	 }
	 printf("The output\n");
	 for(int i=0; i<period;i++){
	 		 printf("%f+%f j\n",fout[i].r,fout[i].i);

	 	 }

	 free(fin);
	 free(fout);

	return 0;
}
