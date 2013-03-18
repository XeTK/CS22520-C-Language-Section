/* 
 * File:   FileReader.h
 * Author: THR2
 *
 * Created on 01 March 2013, 20:37
 */
#include "EventStructs.h"
#ifndef FILEREADER_H
#define	FILEREADER_H

#ifdef	__cplusplus
extern "C" {
#endif
//Struct to hold text data before it is pharsed, rather than duplicating code in each method
    struct Text_Data
    {
        char line[256];
        struct TextData *next_line;
    };
//Fuction Prototypes declerations for converting text files into structs
    void get_file_contents(struct Text_Data **data,char *file_path);
    void get_event_name(struct Event_Global *e_global, char *file_path);
    void get_event_nodes(struct Event_Global *e_global, char *file_path);
    void get_event_tracks(struct Event_Global *e_global, char *file_path);
    void get_event_courses(struct Event_Global *e_global, char *file_path);
    void get_event_entrants(struct Event_Global *e_global, char *file_path);


#ifdef	__cplusplus
}
#endif

#endif	/* FILEREADER_H */

