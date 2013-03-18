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
void set_event_name(struct Event_Global *e_global, char *file_path)
{
	FILE *file;
	file = fopen(file_path,"w+");
	struct Event_Name *temp_name;
	temp_name = e_global->e_name;
	fprintf(file,"%s\n",temp_name->name);
	fprintf(file,"%s\n",temp_name->date);
	fprintf(file,"%s\n",temp_name->time);
}
void set_event_courses(struct Event_Global *e_global, char *file_path)
{
	FILE *file;
	file = fopen(file_path,"w+");
	struct Event_Course *temp_course;
	temp_course = e_global->e_first_courses;
	while (temp_course != NULL )
	{
		fprintf(file,"%c %i ", temp_course->ident,temp_course->node_num);
		struct Event_CNode *temp_cnode;
		temp_cnode = temp_course->head_node;
		while (temp_cnode->pre_node != NULL)
			temp_cnode = temp_cnode->pre_node;

		while (temp_cnode != NULL )
		{
			fprintf(file,"%i ", temp_cnode->node);
			temp_cnode = temp_cnode->next_node;
		}
		fprintf(file,"\n");
		temp_course = temp_course->pre_course;
	}
	fclose(file);
}
void set_event_entrants(struct Event_Global *e_global, char *file_path)
{
	FILE *file;
	file = fopen(file_path,"w+");
	struct Event_Entrant *temp_entrant;
	temp_entrant = e_global->e_first_entrants;
	while (temp_entrant != NULL )
	{
		fprintf(file,"%i %c %s\n",temp_entrant->comp_num, temp_entrant->course,temp_entrant->name);
		temp_entrant = temp_entrant->pre_entrant;
	}
	fclose(file);
}
