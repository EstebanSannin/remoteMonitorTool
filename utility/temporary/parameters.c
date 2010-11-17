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
#include "include/parameters.h"

//if the parser terminat correctly return 1
//ritorna 2 se l'interfaccia di rete e' corretta


//prova..
int mode_ctl(char *mode);
int controller(int argc, char *argv[]){
	int i, equal_interface=0;
	int equal_mode=0;
	int equal_nomedia=0;
	int interface_flag_position = 0;
	int mode_flag_position = 0;
	int nomedia_flag_position = 0;
	if(argc==5 || argc==6){
		for (i=1; i<argc; i++){
			equal_interface=strcmp(argv[i],"-i");
			equal_mode=strcmp(argv[i],"-m");
			equal_nomedia=strcmp(argv[i],"-t");
			if(equal_interface==0){
				interface_flag_position = i;
			}else if(equal_mode==0){
				mode_flag_position = i;
			}else if(equal_nomedia==0){
				nomedia_flag_position=i;
			}
		}
		if(interface_flag_position != 0 && mode_flag_position != 0){

			char *interface = argv[interface_flag_position+1];
			int interface_ctl=device(interface,0);
			
			if (interface_ctl == 0){
				if(mode_ctl(argv[mode_flag_position+1])==0){
					if(nomedia_flag_position !=0){
						if(!strcmp(argv[mode_flag_position+1],"down")){
							data_rate_down(interface);
						}else if(!strcmp(argv[mode_flag_position+1],"up")){
							data_rate_up(interface);
						}
					}
							data_byte_rate(interface,argv[mode_flag_position+1]);
					
				}else{
					printf("mode error! The correct value is:\n"
							"---> down\n"
							"---> up\n\n");
					return 1;
				}
			}else{
				printf("Interface is wrong!\n");
				device("",1);
				return 1;
			}
		}else{
			printf("Error flags!\n");
			usage();
		}
		
	}else{
		printf("\nError parms!\n\n");
		usage();
	}
	return 1;
}

int mode_ctl(char *mode){
	if(!strcmp(mode,"down") || !strcmp(mode,"up")){
		return 0;
	}else
		return 1;

}
int control_parameters(int argc, char *argv[]){
	int status;
	if(!strcmp(argv[1],"-i") && !strcmp(argv[3],"-m")){
		
		int control_interface = device(argv[2],0);
		
		if(control_interface == 0){
			status = 2; //interfaccia esatta
		}else{  
			status = 0;
			printf("\n  [ERROR]: Wrong Interface! \n\n");
			list_device();
		}
	}else{
		usage();
		status = 0;
		printf("\n  [ERROR]: Missing Parameters! \n\n");
	}
    return status;	
}



int parse_line_parameters(int argc, char *argv[]){
        int status;
        if (argc == 2){
                if(!strcmp(argv[1],"-h")){
                        usage();
                        status = 1;
                }else if(!strcmp(argv[1],"-l")){
                        list_device();
                        status = 1;

                }else{
                        printf("\n  [ERROR]: Missing Parameters! \n\n");
                        usage();
                        status = 0;
                }
        }else{

        if (argc == 5){
		status = control_parameters(argc, argv);
        
        }else if(argc == 6){
		printf("parametro 6: %s\n\n",argv[5]);
		status = control_parameters(argc, argv);
	}else{
                printf("\n  [ERROR]: Missing Parameters! \n\n");
                usage();
                status = 0;
        }
        }
        return status;

}
void usage(){
        fprintf(stderr,"\n  [USAGE]:  dtraffic -i [interface] -m [mode]\n"
                        "\t    -i  <interface> set the interface to calculate the traffic rate\n"
                        "\t    -m  <mode> set the mode for scanning interface: [ down | up ]\n"
                        "\t    -l  Print the list of network interfaces\n"
                        "\t    -h  Print this help message.\n\n"  
                       "  [EXAMPLE]: dtraffic -i wlan0 -m down\n"
                       "             drtaffic -l\n\n");
}

void version(){
        fprintf(stderr,"\n Data-Traffic v0.9 \n"
                        " Date Build: may 2010\n"
                        " (C) 2010 - Stefano Viola\n\n");

}
void list_device(){
        printf("\tList Network Interface:\n\n");
        device("void",1);
        printf("\n");
}
