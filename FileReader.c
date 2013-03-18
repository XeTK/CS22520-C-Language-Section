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

//Reading in the files to make some sense of them

//Get the lines from the file
void get_file_contents(struct Text_Data **data, char *file_path)
{
//open the file we want to read
    FILE *file;
    file = fopen(file_path, "rt");
//Define the first link of a linked list
    struct Text_Data *temp_line;
//have a temporay buffer to hold are string before its transfered the final struct
    char line[80];
    while (fgets(line, 80, file) != NULL) 
    {
	//allocate the memory to the tempory struct we want to hold are data in
        temp_line = malloc(sizeof (struct Text_Data));
        int strl = strlen(line);
        if (line[strl - 1] == '\n')
        	line[strl - 1] = '\0';
	//copy the temp line to the final struct
        strcpy(temp_line->line,line);
	//if the passed in struct is not null then we can add a link to the linked list
        if (data != NULL)
            temp_line->next_line = *data;
	//set the head node to the new node
        *data = temp_line;
    }
//close are file reader
    fclose(file);
}
//get the event name read into a struct
void get_event_name(struct Event_Global *e_global, char *file_path)
{
//define are head pointer for the linked list holding the text data
    struct Text_Data *file;
//get the lines from the file
    get_file_contents(&file,file_path);
//define are struct that we are going to put are data in
    struct Event_Name *temp_name;
    temp_name = malloc(sizeof(struct Event_Name));
//copy the data from each line into the values within the struct
    strcpy(temp_name->time,file->line);
    file = file->next_line;
    strcpy(temp_name->date, file->line);
    file = file->next_line;
    strcpy(temp_name->name, file->line);
//set the global pointer to the struct we are working on
    e_global->e_name = temp_name;
//set the file to null as we get some strange strange errors otherwise... dont really know why
    file = NULL;
}
//Read the event file node
void get_event_nodes(struct Event_Global *e_global, char *file_path)
{
//temp node to hold are file that we are writting in
    struct Text_Data *file, *temp;
    get_file_contents(&file,file_path);
    temp = file;
    struct Event_Node *last_node,*temp_node;
    last_node = NULL;
//loop through the lines taken in and convert them to nodes
    while(temp != NULL)
    {
	//allocate the memory to the temporay node we are working on
    	temp_node = malloc(sizeof(struct Event_Node));
	//scan the data in from the line
    	sscanf(temp->line,"%i %s",&temp_node->node,&temp_node->node_type);
	//if the first node is null then we ignore it, if it isnt we implemnt are double linking
    	if (last_node != NULL)
    	{
    		last_node->next_node = temp_node;
    		temp_node->pre_node = last_node;
    	}
	//assign the node to the current one and then the next one
    	last_node = temp_node;
    	temp = temp->next_line;
    }
    e_global->e_first_nodes = last_node;
//set things to null as we get funny errors otherwise
    file = NULL;
    temp = NULL;
}
//Use the same method as above just for tracks instead of nodes
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
//for getting the courses we do something slightly different
void get_event_courses(struct Event_Global *e_global, char *file_path)
{
//usual define are temporay structure to hold are data
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
	//now we start to read the nodes dynamicly
		//set some registers to see how far we are through set stages
		int i = 0, bi = 0, co = 0;
		//have a buffer to hold are data between each node
		char buf[3] = {};
		//loop through the string length
		for (i =0; i <strlen(temp->line); i++)
		{
			//if the value is at the index is = to either a space or a null 
			if(temp->line[i] == ' '||temp->line[1] == NULL)
			{
				//ignore the first 2 bits of data from the line as they are the identifier and how many nodes we have we have that earlier one ^^
				if (co >= 2)
				{
					//define a new node to be added
					temp_cnode = malloc(sizeof(struct Event_CNode));
					//convert are buffer into a number for the node number
					temp_cnode->node = atoi(buf);
					//check if the first node is not null so we can implement are doubly linked list on the nodes
					if (last_cnode != NULL)
					{
						last_cnode->next_node = temp_cnode;
						temp_cnode->pre_node = last_cnode;
					}
					last_cnode = temp_cnode;
				}
				//set are buffer index to 0 to re fill it
				bi = 0;
				//increment are counter of how far we are through a line so we can ignore the first 2
				co++;
				//clear are buffer so we dont have any strange results
				buf[0] = ' ';
				buf[1] = ' ';
				buf[2] = ' ';
			}
			else
			{	
				//fille are buffer with the value we are currently at
				buf[bi] = temp->line[i];
				//increment the buffer index
				bi++;
			}
		}
		//Buisness as per usual and continue to add the courses normaly
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
//Same as nodes and courses, just with entrants this time
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

