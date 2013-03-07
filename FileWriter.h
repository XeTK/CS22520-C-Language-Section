/* 
 * File:   FileWritter.h
 * Author: THR2
 *
 * Created on 01 March 2013, 20:57
 */
#include "EventStructs.h"

#ifndef FILEWRITTER_H
#define	FILEWRITTER_H

#ifdef	__cplusplus
extern "C" {
#endif

    void set_event_name(struct Event_Global *e_global, char *file_path);
    void set_event_courses(struct Event_Global *e_global, char *file_path);
    void set_event_entrants(struct Event_Global *e_global, char *file_path);


#ifdef	__cplusplus
}
#endif

#endif	/* FILEWRITTER_H */

