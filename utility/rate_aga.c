/*
 * Name:     Monitor System
 * Author:   Stefano Viola ---> Esteban Sannin
 * Site:     http://esteban.homelinux.org
 * e-mail:   stefanoviola@sannioglug.org
 * License:  GPLv3
 *
 *
 *
 */


#include <stdio.h>
#include "monitor.h"
#include <time.h>


int main(int argc, char *argv[], char *envp[]){
	//Genera la pagina html
	printf("Content-type: text/html\n\n");

	int i;  
	for (i = 0; i < 1; i++){ 
		printf("<pre>");
		int first_value_down_br0 = stamp_rate("/sbin/ifconfig br0 | grep 'RX bytes' | cut -f 2 -d: | awk {'print $1'}");
		int first_value_up_br0 = stamp_rate("/sbin/ifconfig br0 | grep 'TX bytes' | awk {'print $6'} | cut -f 2 -d:");
		int first_value_down_wl0 = stamp_rate("/sbin/ifconfig br0 | grep 'RX bytes' | cut -f 2 -d: | awk {'print $1'}");
		int first_value_up_wl0 = stamp_rate("/sbin/ifconfig br0 | grep 'TX bytes' | awk {'print $6'} | cut -f 2 -d:");
		sleep(1);
		int second_value_down_br0= stamp_rate("/sbin/ifconfig br0 | grep 'RX bytes' | cut -f 2 -d: | awk {'print $1'}");
		int second_value_up_br0 = stamp_rate("/sbin/ifconfig br0 | grep 'TX bytes' | awk {'print $6'} | cut -f 2 -d:");
		int second_value_down_wl0 = stamp_rate("/sbin/ifconfig br0 | grep 'RX bytes' | cut -f 2 -d: | awk {'print $1'}");
		int second_value_up_wl0 = stamp_rate("/sbin/ifconfig br0 | grep 'TX bytes' | awk {'print $6'} | cut -f 2 -d:");

		//printf("\nfirst: %d second: %d\n", first_value, second_value); //for debug
		int difference_down_br0 = second_value_down_br0-first_value_down_br0;
		int difference_up_br0 = second_value_up_br0-first_value_up_br0;
		int difference_down_wl0 = second_value_down_wl0-first_value_down_wl0;
		int difference_up_wl0 = second_value_up_wl0-first_value_up_wl0;

		float rate_down_br0 = (difference_down_br0/1)/1024.00;
		float rate_up_br0 = (difference_up_br0/1)/1024.00;

		float rate_down_wl0 = (difference_down_wl0/1)/1024.00;
                float rate_up_wl0 = (difference_up_wl0/1)/1024.00;
		
		/*
		 * Stamp the result value
		 *
		 */
		
		printf("RATE ON br0 INTERFACE:");
		printf("Rate Download  RX: %.2fkB/sec",rate_down_br0);
		printf("<br>");
		printf("Rate Uploading TX: %.2fkB/sec",rate_up_br0);

		printf("RATE ON wl0 INTERFACE:");
		printf("Rate Download  RX: %.2fkB/sec",rate_down_wl0);
		printf("<br>");
		printf("Rate Uploading TX: %.2fkB/sec",rate_up_wl0);

		printf("</pre>");
	}  



	return 0;
}

int stamp_rate(char *string_command){
	int byte = command_number(string_command);
	return byte;

}

void stamp_command(char *string_title, char *string_command){

	printf("<p><b><font color='red'>%s</font></b></p>",string_title);
	printf("<pre>");
	command(string_command);
	printf("</pre><br>");

}

//test for read number
//
int command_number(char *command){
	FILE *fp;
	char line[1024];
	int iRet = 0;
	int number_byte;

	fp = popen(command, "r");
	if (fp != NULL) {
		while (fgets(line, sizeof(line), fp)) {
			number_byte = atoi(line);
		}
		pclose(fp);
		iRet = 0;
	} else {
		iRet = -1;
	}
	return number_byte;
}



///testing funzione per comandi da shell
int command(char *command){
	FILE *fp;
	char line[1024];
	int iRet = 0;
	fp = popen(command, "r");

	if (fp != NULL) {
		while (fgets(line, sizeof(line), fp)) {
			printf("%s", line);
		}
		pclose(fp);
		iRet = 0;
	} else {
		iRet = -1;
	}
	return iRet;

}



