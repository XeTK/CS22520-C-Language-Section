/* 
 * File:   FileWriter.c
 * Author: THR2
 *
 * Created on 01 March 2013, 21:16
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include "EventStructs.h"
#include "FileWriter.h"
#include "EventStructs.h"
//Set the event file up correctly writting the correct info to the file
void set_event_name(struct Event_Global *e_global, char *file_path)
{
	//Create a pointer to the file we want to manipulate
	FILE *file;
	//Open the file in a mode that we can write to it
	file = fopen(file_path,"w+");
	//get the struct from the global holding pen
	struct Event_Name *temp_name;
	temp_name = e_global->e_name;
	//write each value to its own line
	fprintf(file,"%s\n",temp_name->name);
	fprintf(file,"%s\n",temp_name->date);
	fprintf(file,"%s\n",temp_name->time);
	fclose(files);
}
//Write the values of the course to a file
void set_event_courses(struct Event_Global *e_global, char *file_path)
{
	//Open are file
	FILE *file;
	file = fopen(file_path,"w+");
	//define a temp struct to hold are global object
	struct Event_Course *temp_course;
	temp_course = e_global->e_first_courses;
	//loop through the nodes till we hit the end of the file
	while (temp_course != NULL )
	{
		//print the first bits of the line
		fprintf(file,"%c %i ", temp_course->ident,temp_course->node_num);
		//grab the nodes from the current course we are printing out
		struct Event_CNode *temp_cnode;
		temp_cnode = temp_course->head_node;
		//flip the node list so they will print out in order
		while (temp_cnode->pre_node != NULL)
			temp_cnode = temp_cnode->pre_node;

		//print the nodes out in order
		while (temp_cnode != NULL )
		{
			fprintf(file,"%i ", temp_cnode->node);
			temp_cnode = temp_cnode->next_node;
		}
		//end the line once we have finished printing out the nodes
		fprintf(file,"\n");
		temp_course = temp_course->pre_course;
	}
	//close the file we are working on
	fclose(file);
}
//Write are entrants back to the file using the same method mentioned above
void set_event_entrants(struct Event_Global *e_global, char *file_path)
{
	//Open the file
	FILE *file;
	file = fopen(file_path,"w+");
	//Define some temporary structs
	struct Event_Entrant *temp_entrant;
	temp_entrant = e_global->e_first_entrants;
	//Write are entrants to the file
	while (temp_entrant != NULL )
	{
		fprintf(file,"%i %c %s\n",temp_entrant->comp_num, temp_entrant->course,temp_entrant->name);
		temp_entrant = temp_entrant->pre_entrant;
	}
	//Close the file
	fclose(file);
}
