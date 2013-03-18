/* 
 * File:   CLI.h
 * Author: THR2
 *
 * Created on 01 March 2013, 20:11
 */
#include "EventStructs.h"
#ifndef CLI_H
#define	CLI_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    void run_program(struct Event_Global *e_global);
    void print_menu();
    void add_courses(struct Event_Global *e_global);
    void add_entrants(struct Event_Global *e_global);
    void add_name(struct Event_Global *e_global);
    void load_files(struct Event_Global *e_global);
    void save_files(struct Event_Global *e_global);
    void print_structs(struct Event_Global *e_global);
    int lock_file(char *path);
    int unlock_file(char *path);

#ifdef	__cplusplus
}
#endif

#endif	/* CLI_H */

