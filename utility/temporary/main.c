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
#include "datatraffic.h"

int main(int argc, char *argv[]){

printf("RATE: %lld\n\n",get_byte_trasmitted("wlan0"));


}

