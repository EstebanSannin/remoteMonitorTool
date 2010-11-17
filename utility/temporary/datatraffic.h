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

/*
 * get_byte_received():
 * return the byte receved
 * */
long long int get_byte_received(char *interface);

/*
 * get_byte_trasmitted():
 * return the byte trasmitted
 * 
 * */

long long int get_byte_trasmitted(char *interface);

// calcola il data-rate in download
double calculate_data_rate_down(char *interface);

// calcola il data rate in upload
double calculate_data_rate_up(char *interface);

//stampa il data rate in upload senza calcolare la media
int data_rate_up(char *interface);

//stampa il data rate in download senza calcolare la media
int data_rate_down(char *interface);

//se la mode e` errata ritorna 1
//se l'interfaccia e' errata ritorna 2
//se tutto e' corretto ritorna 0
int data_byte_rate(char *interface, char *mode);
