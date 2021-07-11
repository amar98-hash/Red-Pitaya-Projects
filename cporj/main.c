#include<stdio.h>

#include<string.h>

int init_key[64];


void create_csv(char *,int ,int ,int a[][1]);


void init_key_LUT(){
	for(int i=0;i<64;i++){
		if(i<16){
			//0000000000000000 16-bit
			init_key[i]=0;
		}
		else if (i>=16 && i<24){
			//11111111  8-bit
			init_key[i]=1;

		}
		else if (i>=24 && i< 41){
			//01010101010101010 17-bit?
			if(i!=40){
			    init_key[i]=0;
			    i++;
			    init_key[i]=1;
			}
			else{init_key[40]=0;}
		}



		else {
			//11011011011011011011011

			init_key[i]=1;
			i++;
			init_key[i]=1;
			i++;
			init_key[i]=0;
		}
	}
}





int main()
{
    printf("Hello World\n");

    init_key_LUT();

    for(int i=0;i<64;i++){
        printf("%d",init_key[i]);
    }

    printf("\n");

    int a[64][1];
    for(int i=0;i<64;i++){
    	a[i][1]=init_key[i];
    }

    for(int i=0;i<64;i++){
            printf("%d",a[i][1]);
        }

        char str[100]="csv_file";



    create_csv(str,64,1,a);


    return 0;
}


void create_csv(char *filename,int n,int m,int a[63][1]){

printf("\n Creating %s.csv file",filename);

FILE *fp;

filename=strcat(filename,".csv");

fp=fopen(filename,"w+");

fprintf(fp,"index, digital_value");
//printf("%d",a[61][1]);


for(int i=0;i<n-1;i++){

    fprintf(fp,"\n%d,%d",i,a[i][1]);
    }
fprintf(fp,"\n%d,%d",63,1);

fclose(fp);

printf("\n %s file created",filename);

}

int check_store(int *in_bit_stream, int * out_bit_stream){

	for(int i=0;i<64;i++){
		if(in_bit_stream[i]==init_key[i]){
			//
		}
		else{
			printf("Signature does not match!!\n");
			return 0;
		}

	}
	for(int i=64;i<105;i++){
		out_bit_stream[i-64]=in_bit_stream[i];

	}

	printf(" data check and store successful!\n");
	return 1;
}


void ir_data_acquire(){




}



