/* 
 * File:   EventStructs.h
 * Author: THR2
 *
 * Created on November 30, 2012, 5:52 PM / Refracted March 2, 2013, 1:01 PM
 */

#ifndef EVENTSTRUCTS_H
#define	EVENTSTRUCTS_H

#ifdef	__cplusplus
extern "C" {
#endif
//Structs to hold the data from each events
/*
 * Changes from origernal design, 
 * Made all structs doubly linked,
 * Cut Down on duplicate declerations
 * Added global Structure to hold the information rather than passing arround each indervidual structure 
 */
    struct Event_Name
    {
       char name[80], date[80], time[80];
    };
    struct Event_Node
    {
        int node;
        char node_type[2];
        struct Event_Node *next_node, *pre_node;
    };
    struct Event_Track
    {
        int number, start_node, end_node, expected_time;
        struct Event_Track *next_track, *pre_track;
    };
    struct Event_Course
    {
        char ident;
        int node_num;
        struct Event_Course_Node *head_node;
        struct Event_Course *next_course, *pre_course;
    };
    struct Event_CNode
    {
        int node;
        struct Event_CNode *next_node, *pre_node;
    };
    struct Event_Entrant
    {
        int comp_num;
        char course, name[51];
        struct Event_Entrant *next_entrant, *pre_entrant;
    };
    struct Event_Global
    {
        struct Event_name *e_name;
        struct Event_Node *e_first_nodes;
        struct Event_Track *e_first_tracks;
        struct Event_Course *e_first_courses;
        struct Event_Entrant *e_first_entrants;
    };

#ifdef	__cplusplus
}
#endif

#endif	/* EVENTSTRUCTS_H */

