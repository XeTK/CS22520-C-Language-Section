/* 
 * File:   FileWriter.c
 * Author: THR2
 *
 * Created on 04 March 2013, 17:30
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include "FileReader.h"
#include "EventStructs.h"

void get_file_contents(struct Text_Data **data, char *file_path)
{
	FILE *file;
    file = fopen(file_path, "rt");
    //flock(file, LOCK_EX);
    struct Text_Data *temp_line;
    char line[80];
    while (fgets(line, 80, file) != NULL) 
    {
        temp_line = malloc(sizeof (struct Text_Data));
        int strl = strlen(line);
        if (line[strl - 1] == '\n')
        	line[strl - 1] = '\0';
        strcpy(temp_line->line,line);
        if (data != NULL)
            temp_line->next_line = *data;
        *data = temp_line;
    }
    //flock(file, LOCK_UN);
    fclose(file);
}
void get_event_name(struct Event_Global *e_global, char *file_path)
{
    struct Text_Data *file;
    get_file_contents(&file,file_path);
    struct Event_Name *temp_name;
    temp_name = malloc(sizeof(struct Event_Name));

    strcpy(temp_name->time,file->line);
    file = file->next_line;
    strcpy(temp_name->date, file->line);
    file = file->next_line;
    strcpy(temp_name->name, file->line);

    e_global->e_name = temp_name;
    file = NULL;
}
void get_event_nodes(struct Event_Global *e_global, char *file_path)
{
    struct Text_Data *file, *temp;
    get_file_contents(&file,file_path);
    temp = file;
    struct Event_Node *last_node,*temp_node;
    last_node = NULL;
    while(temp != NULL)
    {
    	temp_node = malloc(sizeof(struct Event_Node));
    	sscanf(temp->line,"%i %s",&temp_node->node,&temp_node->node_type);
    	if (last_node != NULL)
    	{
    		last_node->next_node = temp_node;
    		temp_node->pre_node = last_node;
    	}
    	last_node = temp_node;
    	temp = temp->next_line;
    }
    e_global->e_first_nodes = last_node;
    file = NULL;
    temp = NULL;
}
void get_event_tracks(struct Event_Global *e_global, char *file_path)
{
    struct Text_Data *file, *temp;
    get_file_contents(&file,file_path);
    temp = file;
    struct Event_Track *last_track,*temp_track;
    last_track = NULL;
    while(temp != NULL)
    {
        temp_track = malloc(sizeof(struct Event_Track));
        sscanf(temp->line,"%i %i %i %i", &temp_track->number, &temp_track->start_node,&temp_track->end_node,&temp_track->expected_time);
        if(last_track != NULL)
        {
        	last_track->next_track = temp_track;
        	temp_track->pre_track = last_track;
        }
        last_track = temp_track;
        temp = temp->next_line;
    }
    e_global->e_first_tracks = last_track;
    file = NULL;
    temp = NULL;
}
void get_event_courses(struct Event_Global *e_global, char *file_path)
{
    struct Text_Data *file, *temp;
    get_file_contents(&file,file_path);
    temp = file;
    struct Event_Course *last_course, *temp_course;
    last_course = NULL;
    while(temp != NULL)
    {
    	temp_course = malloc(sizeof(struct Event_Course));
    	sscanf(temp->line,"%c %d",&temp_course->ident,&temp_course->node_num);
    	struct Event_CNode *last_cnode, *temp_cnode;
    	last_cnode = NULL;
		int i = 0, bi = 0, co = 0;
		char buf[3] = {};
		for (i =0; i <strlen(temp->line); i++)
		{
			if(temp->line[i] == ' '||temp->line[1] == NULL)
			{
				if (co >= 2)
				{
					temp_cnode = malloc(sizeof(struct Event_CNode));
					temp_cnode->node = atoi(buf);
					if (last_cnode != NULL)
					{
						last_cnode->next_node = temp_cnode;
						temp_cnode->pre_node = last_cnode;
					}
					last_cnode = temp_cnode;
				}
				bi = 0;
				co++;
				buf[0] = ' ';
				buf[1] = ' ';
				buf[2] = ' ';
			}
			else
			{
				buf[bi] = temp->line[i];
				bi++;
			}
		}
		temp_course->head_node = last_cnode;
		if (last_course != NULL)
		{
			last_course->next_course = temp_course;
			temp_course->pre_course = last_course;
		}
		last_course = temp_course;
        temp = temp->next_line;
    }
    e_global->e_first_courses = last_course;
    file = NULL;
    temp = NULL;
}
void get_event_entrants(struct Event_Global *e_global, char *file_path)
{
    struct Text_Data *file, *temp;
    get_file_contents(&file,file_path);
    temp = file;
    struct Event_Entrant *last_entrant, *temp_entrant;
    last_entrant = NULL;
    while(temp != NULL)
    {
    	temp_entrant = malloc(sizeof(struct Event_Entrant));
    	sscanf(temp->line,"%d %c %s",&temp_entrant->comp_num,&temp_entrant->course,&temp_entrant->name);
        if (last_entrant != NULL)
        {
        	last_entrant->next_entrant = temp_entrant;
        	temp_entrant->pre_entrant = last_entrant;
        }
        last_entrant = temp_entrant;
        temp = temp->next_line;
    }
    e_global->e_first_entrants = last_entrant;
    file = NULL;
    temp = NULL;
}

