/*
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

int data_byte_rate(char *interface, char *mode, char *flags);
int get_byte_received(char *interface);
void device();
void list_device();
int parse_line_parameters(int argc, char *argv[]);
void usage();
void version();
int data_rate_down(char *interface);
int controller(int argc, char *argv[]);
