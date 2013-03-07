/* 
 * File:   CLI.c
 * Author: THR2
 *
 * Created on 01 March 2013, 20:10
 */
#include <stdio.h>
#include <stdlib.h>
#include "CLI.h"
#include "Output.h"
#include "FileReader.h"
#include "FileWriter.h"

void run_program(struct Event_Global *e_global)
{
    int cont = 1;
    while(1)
    {
        print_menu();
        int ret = 0;
        scanf(" %i", &ret);
        switch(ret)
        {
            case 1:
                load_files(e_global);
                break;
            case 2:
                add_name(e_global);
                break;
            case 3:
                add_courses(e_global);
                break;
            case 4:
                add_entrants(e_global);
                break;
            case 5:
                save_files(e_global);
                break;
            case 6:
            	print_structs(e_global);
            	break;
            case 7:
                printf("Goodbye!");
                cont = 0;
                break;
            default:
                printf("That is not a selection please try again\n");
                break;
        }
        if (cont != 1)
            break;
    }
}

void print_menu()
{
    printf( "1: Load Files \n"
            "2: Add Name \n"
            "3: Add Courses \n"
            "4: Add Entrants \n"
            "5: Save Files \n"
    		"6: Print Data \n"
            "7: Exit\n"
            );
}

void add_courses(struct Event_Global *e_global)
{
    struct Event_Course *temp_course, *incourse;
    incourse = e_global->e_first_courses;
    temp_course = malloc(sizeof(struct Event_Course));
    printf("\nEnter course identifier: ");
    scanf(" %c",&temp_course->ident);
    
    int num_cour = 0;
    printf("\nEnter number of nodes: ");
    scanf(" %i",&num_cour);
    temp_course->node_num = num_cour;
    
    int i;
    struct Event_CNode *last_node, *temp_node;
    last_node = NULL;
    for (i = 0; i < num_cour;)
    {
        temp_node = malloc(sizeof(struct Event_CNode));
        printf("\n%i of %i nodes filled in | Enter next node : ",(i + 1),num_cour);
        scanf(" %i",&temp_node->node);
        struct Event_Node *temp_inode;
        temp_inode = e_global->e_first_nodes;
        int bool = 0;
        while (temp_inode != NULL)
        {
        	if (temp_node->node == temp_inode->node)
        	{
				if (last_node != NULL)
				{
					last_node->next_node = temp_node;
					temp_node->pre_node = last_node;
				}
				last_node = temp_node;
				bool = 1;
				break;
        	}
        	temp_inode = temp_inode->pre_node;
        }
        if (bool == 1)
        	i++;
        else
        	printf("Invalid Node\n");
    }
    temp_course->head_node = last_node;
    
    if (incourse != NULL)
    {    
        temp_course->pre_course = incourse;
        incourse->next_course = temp_course;
    }
    incourse = temp_course;
    e_global->e_first_courses = incourse;
}

void add_entrants(struct Event_Global *e_global)
{
    struct Event_Entrant *temp_entrant, *inentrant;
    inentrant = e_global->e_first_entrants;
    temp_entrant = malloc(sizeof(struct Event_Entrant));
    printf("\nEntrants Name : ");
    scanf(" %80s",&temp_entrant->name);
    printf("\nEntrant Number : ");
    scanf(" %i",&temp_entrant->comp_num);
    printf("\nCourse Identifier : ");
    scanf(" %c",&temp_entrant->course);
    if (inentrant != NULL)
    {
        temp_entrant->pre_entrant = inentrant;
        inentrant->next_entrant = temp_entrant;
    }
    inentrant = temp_entrant;
    e_global->e_first_entrants;
}

void add_name(struct Event_Global *e_global)
{
    struct Event_Name *temp_name;
    temp_name = malloc(sizeof(struct Event_Name));
    printf("\nEvent Name : ");
    scanf(" %79s",&temp_name->name);
    printf("\nDate : ");
    scanf(" %79s",&temp_name->date);
    printf("\nTime : ");
    scanf(" %79s",&temp_name->time);
    e_global->e_name = temp_name;
}

void load_files(struct Event_Global *e_global) 
{
    get_event_name(e_global,"data/name.txt");
    get_event_nodes(e_global,"data/nodes.txt");
    get_event_tracks(e_global,"data/tracks.txt");
    get_event_courses(e_global,"data/courses.txt");
    get_event_entrants(e_global,"data/entrants.txt");
}

void save_files(struct Event_Global *e_global)
{
	set_event_name(e_global,"data/name.txt");
	set_event_courses(e_global,"data/courses.txt");
	set_event_entrants(e_global,"data/entrants.txt");
}
void print_structs(struct Event_Global *e_global)
{
	print_event_name(e_global);
	print_event_nodes(e_global);
	print_event_tracks(e_global);
	print_event_courses(e_global);
	print_event_entrants(e_global);
}
