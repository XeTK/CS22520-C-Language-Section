/* 
 * File:   CLI.c
 * Author: THR2
 *
 * Created on 01 March 2013, 20:10
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

//Include are structs & functions
#include "CLI.h"
#include "Output.h"
#include "FileReader.h"
#include "FileWriter.h"

//Define are struct for file locking to get the type of lock on the file
struct flock* l_file_lock(short type, short whence)
{
		static struct flock ret;
		ret.l_type = type;
		ret.l_start = 0;
		ret.l_whence = whence;
		ret.l_len = 0;
		ret.l_pid = getpid();
		return &ret;
};

//Function that is called when the program is ran to lock files on execution and to load the menu
void run_program(struct Event_Global *e_global)
{
    (l_lock_file("data/name.txt") == -1)?printf("Failed to lock\n"):printf("Locked File\n");
    (l_lock_file("data/nodes.txt") == -1)?printf("Failed to lock\n"):printf("Locked File\n");
    (l_lock_file("data/tracks.txt") == -1)?printf("Failed to lock\n"):printf("Locked File\n");
    (l_lock_file("data/courses.txt") == -1)?printf("Failed to lock\n"):printf("Locked File\n");
    (l_lock_file("data/entrants.txt") == -1)?printf("Failed to lock\n"):printf("Locked File\n");
    int cont = 1;
    while(1)
    {
	//Print the menu dialog
        print_menu();
        int ret = 0;
        scanf(" %i", &ret);
        switch(ret)
        {
		//load the functions that apply to the menu called
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
                printf("Goodbye!\n");
                cont = 0;
                break;
            default:
                printf("That is not a selection please try again\n");
                break;
        }
        if (cont != 1)
            break;
    }
	//Unlock the files when we exit the program
    (l_unlock_file("data/name.txt") == -1)?printf("Failed to unlock\n"):printf("Locked File\n");
    (l_unlock_file("data/nodes.txt") == -1)?printf("Failed to unlock\n"):printf("Locked File\n");
    (l_unlock_file("data/tracks.txt") == -1)?printf("Failed to unlock\n"):printf("Locked File\n");
    (l_unlock_file("data/courses.txt") == -1)?printf("Failed to unlock\n"):printf("Locked File\n");
    (l_unlock_file("data/entrants.txt") == -1)?printf("Failed to unlock\n"):printf("Locked File\n");
}

//Print the menu 
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

//Dialog to add a new course 
void add_courses(struct Event_Global *e_global)
{
//Define are pointers to a struct
    struct Event_Course *temp_course, *incourse;
//Set are start node to the last node of the global decleration of the structs
    incourse = e_global->e_first_courses;
//Allocate some memory to the struct
    temp_course = malloc(sizeof(struct Event_Course));
    printf("\nEnter course identifier: ");
//Grab input from console and store it in are struct
    scanf(" %c",&temp_course->ident);
    
//Do the same against just with the number of nodes
    int num_cour = 0;
    printf("\nEnter number of nodes: ");
    scanf(" %i",&num_cour);
    temp_course->node_num = num_cour;
    
//Now we have to dynamicly add the number of nodes to the struct
    int i;
    struct Event_CNode *last_node, *temp_node;
    last_node = NULL;
    for (i = 0; i < num_cour;)
    {
	//Allocate a tempory Node to populate with the values we require
        temp_node = malloc(sizeof(struct Event_CNode));
        printf("\n%i of %i nodes filled in | Enter next node : ",(i + 1),num_cour);
	//take in the node number from the console and add it to the temp node
        scanf(" %i",&temp_node->node);
	//define a temporay node to check between
        struct Event_Node *temp_inode;
        temp_inode = e_global->e_first_nodes;
	//This section checks if the node is valid and it exists in the node list
	//have a flag to know when we have exited
        int bool = 0;
        while (temp_inode != NULL)
        {
        	if (temp_node->node == temp_inode->node)
        	{
				//If the last node is not null which would cause a seg fault 
				if (last_node != NULL)
				{
					//We add the node to the end of the list
					last_node->next_node = temp_node;
					temp_node->pre_node = last_node;
				}
				last_node = temp_node;
				//Set for us to go to the next node
				bool = 1;
				break;
        	}
        	temp_inode = temp_inode->pre_node;
        }
	//If valid node has been selected
        if (bool == 1) //Add to the number that has been filled in
        	i++;
        else
        	printf("Invalid Node\n");
    }
    temp_course->head_node = last_node;
    //If the last course isnt null then we add and link the last 2 nodes together
    if (incourse != NULL)
    {    
        temp_course->pre_course = incourse;
        incourse->next_course = temp_course;
    }
    incourse = temp_course;
    e_global->e_first_courses = incourse;
}
//Add entrant to the entrant list
void add_entrants(struct Event_Global *e_global)
{
//Define some temporary structs to hold are items
    struct Event_Entrant *temp_entrant, *inentrant;
//Set the pointer to the global entrants
    inentrant = e_global->e_first_entrants;
//Allocate some memory to are temporary structure
    temp_entrant = malloc(sizeof(struct Event_Entrant));
    printf("\nEntrants Name : ");
    scanf(" %80s",&temp_entrant->name);
    printf("\nEntrant Number : ");
    scanf(" %i",&temp_entrant->comp_num);
    printf("\nCourse Identifier : ");
    scanf(" %c",&temp_entrant->course);
//If the last entrant is not null then
    if (inentrant != NULL)
    {
	//we tie in the new node to the last node so we have doubly linked list
        temp_entrant->pre_entrant = inentrant;
        inentrant->next_entrant = temp_entrant;
    }
    inentrant = temp_entrant;
    e_global->e_first_entrants = inentrant;
}

//Setting the event name
void add_name(struct Event_Global *e_global)
{
//Define a tempory structure to hold are details
    struct Event_Name *temp_name;
    temp_name = malloc(sizeof(struct Event_Name));
//Take in info from the command line
    printf("\nEvent Name : ");
    scanf(" %79s",&temp_name->name);
    printf("\nDate : ");
    scanf(" %79s",&temp_name->date);
    printf("\nTime : ");
    scanf(" %79s",&temp_name->time);
    e_global->e_name = temp_name;
}
//Load in files from there directories
void load_files(struct Event_Global *e_global) 
{
//Load in each file and add it to the global struct
    get_event_name(e_global,"data/name.txt");
    get_event_nodes(e_global,"data/nodes.txt");
    get_event_tracks(e_global,"data/tracks.txt");
    get_event_courses(e_global,"data/courses.txt");
    get_event_entrants(e_global,"data/entrants.txt");
}
//Save are files back out the the files they came from
void save_files(struct Event_Global *e_global)
{
	set_event_name(e_global,"data/name.txt");
	set_event_courses(e_global,"data/courses.txt");
	set_event_entrants(e_global,"data/entrants.txt");
}
//Simple Debugging print out the structs so we can see what info has been entered
void print_structs(struct Event_Global *e_global)
{
	print_event_name(e_global);
	print_event_nodes(e_global);
	print_event_tracks(e_global);
	print_event_courses(e_global);
	print_event_entrants(e_global);
}
//Simple Method to lock the file taken from Neil Snook's Example
int l_lock_file(char *path)
{
	return fcntl(open(path, O_RDWR), F_SETLK, l_file_lock(F_WRLCK, SEEK_SET));
}
//Simple unlock Method to unlock the files that where previously locked, taken from Neil Snook's Example
int l_unlock_file(char *path)
{
	return fcntl(open(path, O_RDWR), F_SETLKW, l_file_lock(F_UNLCK, SEEK_SET));
}
