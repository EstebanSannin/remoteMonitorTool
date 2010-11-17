/*
 *
 * AUTHOR:   Stefano Viola (aka) Esteban Sannin
 * CONTACT:  stefanoviola[at]sannioglug[dot]org
 * HOME:     http://esteban.homelinux.org   
 *
 *      Licenze GLPv3
 *      This program is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU General Public License
 *      as published by the Free Software Foundation; either version
 *      3 of the License, or (at your option) any later version.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "datatraffic.h"
#include <unistd.h>
#define NETWORK "/proc/net/dev"




/*
 * get_byte_received():
 * return the byte receved
 * */

long long int get_byte_received(char *interface){
        FILE *fp;
        char line[1024];
        char *tok;
        int i,j; 
        int control_token = 0;
        int count_string_token = 0;
        char *token_true;
        int token2; 
        long long int number_byte;
        char *final_down;
        
        int one_token = 0;
        fp = fopen(NETWORK, "r");
        if (fp != NULL) {
                while (fgets(line, sizeof(line), fp)) {
                        tok = strtok(line," ");
                        count_string_token = 0; 
                   if (one_token == 0){     
                        while(tok != NULL){
                                if(token2){
                                        token2 = 0;
                                        number_byte = atoll(tok);
                                }
                                count_string_token++;
                                if(strstr(tok,interface)){
                                        control_token=1;
                                        token_true = strstr(tok,interface);           //search the interface in the string
                                        final_down = strchr(tok,':');                 //cut the byte download oh the interface
                                        int equal_string = strcmp(final_down,":");
                                        if (equal_string == 0){
                                        token2 = 1;
                                        }else{
                                        char byte_down_temp[strlen(final_down)];      //array for temporary byte download
                                        strcpy(byte_down_temp, final_down);           //copy the string in to array byte_down
                                        i=1;                                          //for control
                                        j = 0;                                        //for control
                                        int dim = strlen(final_down);                 //computing the dimension for the array
                                        char byte_download[dim];
                                        for(j = 0; j<(dim-1); j++){                   //get byte clean
                                                one_token = 1;
                                                byte_download[j] = byte_down_temp[i];
                                                i++;
                                        }
                                        number_byte = atoll(byte_download);
                                        }
                                        }else{
                                                if(control_token !=1 ){
                                                number_byte = -1;
                                                }
                                        }
                tok = strtok(NULL, " ");
                }
                   }
                        }
                
                fclose(fp);
        } else {
                printf("Error!!\n\n");
        }
        return number_byte;
}     

/*
 * get_byte_trasmitted():
 * return the byte trasmitted
 * 
 * */

long long int get_byte_trasmitted(char *interface){
        int loop = 9;
        FILE *fp;
        char line[1024];
        char *tok;
        int control_token = 0;
        int count_string_token = 0;
        char *token_true; 
        long long int number_byte;
        char *final_down;
        int token2 = 0;
        
        fp = fopen(NETWORK, "r");
        if (fp != NULL) {
                while (fgets(line, sizeof(line), fp)) {
                        tok = strtok(line," ");
                        count_string_token = 0;      
                        while(tok != NULL){
                                count_string_token++;
                                if(strstr(tok,interface)){
                                        control_token=1;
                                        token_true = strstr(tok,interface);             //search the interface in the string
                                        final_down = strchr(tok,':');                 //cut the byte download oh the interface
                                        int equal_string = strcmp(final_down,":");
                                        if(equal_string == 0){
                                                token2 = 1;
                                        }
                                }
                                if (token2 == 1){
                                        loop++;
                                        token2 = 0;
                                }
                                if (count_string_token == loop && control_token == 1){
                                        control_token = 0;
                                        number_byte = atoll(tok);
                                }
                tok = strtok(NULL, " ");
                }
                        }
                
                fclose(fp);
        } else {
                printf("Error!!\n\n");
        }
      return number_byte; 
}


// calcola il data-rate in download
double calculate_data_rate_down(char *interface){
		
		long long int first = get_byte_received(interface);
		sleep(1); 
		long long int second = get_byte_received(interface);
		
		long long int difference = second - first;
		
		double rate_down = difference/1024.00;
		printf("Reception Rate: %lf    kB/s\n", rate_down);
	
	return rate_down;

}

// calcola il data rate in upload
double calculate_data_rate_up(char *interface){
	long long int first = get_byte_trasmitted(interface);
	sleep(1);
	long long int second = get_byte_trasmitted(interface);

	long long int difference = second - first;
	double rate_down = difference/1024.00;
	printf("Trasmission Rate: %lf    kB/s\n", rate_down);
	return rate_down;
}

//stampa il data rate in upload senza calcolare la media
int data_rate_up(char *interface){
	printf("Interface selected: %s\n",interface);
	printf("Stop the process with CTRL+C..\n\n");
	for(;;){
		calculate_data_rate_up(interface);
	}

}


//stampa il data rate in download senza calcolare la media
int data_rate_down(char *interface){
	printf("Interface selected: %s\n",interface);
        printf("Stop the process with CTRL+C..\n\n");
	for(;;){
		calculate_data_rate_down(interface);
	}
}

//se la mode e` errata ritorna 1
//se l'interfaccia e' errata ritorna 2
//se tutto e' corretto ritorna 0


int data_byte_rate(char *interface, char *mode){

int CLOCK = 10;

        int i;
        double array_rate[CLOCK];
        double total = 0;
        double rate_average;
        int control_valid_interface = 0;
        
	if(control_valid_interface == 0){
                if(strcmp(mode,"down")==0){
                        printf("Download mode on interface: %s\n\n",interface);
                        for(i = 0; i<CLOCK ; i++){
                                array_rate[i] = calculate_data_rate_down(interface);
                        }
                        for(i = 0; i<CLOCK; i++){
                                total = total+array_rate[i];
                        }
                        rate_average = total/10.00;
                        printf("\n\tAverage Reception-rate:  %lf kB/s\n\n",rate_average);
                
		}else if (strcmp(mode,"up")==0){
                        printf("Upload mode on interface: %s\n\n",interface);
                        for(i = 0; i<CLOCK ; i++){
                                array_rate[i] = calculate_data_rate_up(interface);
                        }
                        for(i = 0; i<CLOCK; i++){
                                total +=array_rate[i];
                        }
                        rate_average = total/CLOCK;
                        printf("\n\tAverage up-rate:  %lf kB/s\n\n",rate_average);
                }else{
                        return 1;
                }
        }else{
                return 2;
        }
        return 0;
}
