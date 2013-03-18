/*
 * Output.c
 *
 *  Created on: 5 Mar 2013
 *      Author: THR2
 */
#include <stdio.h>
#include <stdlib.h>
#include "Output.h"
//Simple Debug class to print out the infor from are structs
void print_event_name(struct Event_Global *e_global)
{
	//load the values from the global struct into a temporay
	struct Event_Name *temp_name;
	temp_name = e_global->e_name;
	//Print each value from the constructor
	printf("Event Name : %s \n",temp_name->name);
	printf("Event Date : %s \n",temp_name->date);
	printf("Event Time : %s \n",temp_name->time);
}
//same again just for nodes
void print_event_nodes(struct Event_Global *e_global)
{
	struct Event_Node *temp_node;
	temp_node = e_global->e_first_nodes;
	while (temp_node != NULL)
	{
		printf("Node Number: %i | Node Type: %s\n",temp_node->node,temp_node->node_type);
		temp_node = temp_node->pre_node;
	}
}
//same again we just print out the tracks this time
void print_event_tracks(struct Event_Global *e_global)
{
	struct Event_Track *temp_track;
	temp_track = e_global->e_first_tracks;
	while (temp_track != NULL)
	{
		printf("Track No: %i | Start Node: %i | End Node: %i | Expected Time: %i\n",temp_track->number,temp_track->start_node,temp_track->end_node,temp_track->expected_time);
		temp_track = temp_track->pre_track;
	}
}
//^^
void print_event_courses(struct Event_Global *e_global)
{
	struct Event_Course *temp_course;
	temp_course = e_global->e_first_courses;
	while (temp_course != NULL)
	{
		printf("Course No: %c | Number of nodes %i ",temp_course->ident,temp_course->node_num);
		struct Event_CNode *temp_cnode;
		temp_cnode = temp_course->head_node;
		while (temp_cnode != NULL)
		{
			printf("| Node: %i ",temp_cnode->node);
			temp_cnode = temp_cnode->pre_node;
		}
		printf("\n");
		temp_course = temp_course->pre_course;
	}
}
void print_event_entrants(struct Event_Global *e_global)
{
	struct Event_Entrant *temp_entrant;
	temp_entrant = e_global->e_first_entrants;
	while (temp_entrant != NULL)
	{
		printf("Competitor No: %i | Course: %c | Name: %s\n",temp_entrant->comp_num,temp_entrant->course,temp_entrant->name);
		temp_entrant = temp_entrant->pre_entrant;
	}
}
