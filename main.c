/* 
 * File:   main.c
 * Author: THR2
 *
 * Created on 01 March 2013, 20:10
 */

#include <stdio.h>
#include <stdlib.h>
#include "CLI.h"
#include "EventStructs.h"
static struct Event_Global *e_global;
int main(int argc, char** argv) 
{
    e_global = malloc(sizeof(struct Event_Global));
    run_program(e_global);
    return (EXIT_SUCCESS);
}

