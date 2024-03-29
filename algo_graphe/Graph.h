/**
 *  @author		:	ZHOU Xiong
 *  @file		:	Graph.h
 *  @version	:	1.0
 *  @date		:	2012 L3 INFO Paris 13
*/

#ifndef Graph_H_INCLUDED
#define Graph_H_INCLUDED

/* Includes */
#include <stdlib.h>
#include <stdio.h>

#include "BbQueue.h"

/*
    Note pour les structures suivantes :

        _impl_data est destin� � recueillir des informations li�es � l'impl�mentation
        de diff�rents algorithmes de la th�orie des graphes ; Il n'est pas conseill�
        d'y toucher lors d'une utilisation de la librairie. user_data est l� pour �a.
*/

typedef
struct _Vertex
{
    /* Chaque Vertex peut �tre reli� de [0..*] Arcs */
    BbQueue *arcs;

    void *_impl_data;
    void *user_data;

}   GraphVertex;

typedef
struct _Arc
{
    /* Un Arc est situ� entre deux vertices */
    GraphVertex *from,
                *to;

    void *_impl_data;
    void *user_data;

}   GraphArc;

typedef
struct _Graph
{
    /* Un Graph est un ensemble de Vertices */
    BbQueue *vertices;

}	Graph;


	/**=================
		@Constructors
	===================*/

Graph *
graph_new 				(void);

GraphArc *
graph_arc_new           (GraphVertex *from, GraphVertex *to);

GraphVertex *
graph_vertex_new        (void);


	/**=================
		  @Methods
	===================*/

GraphArc *
graph_add_arc           (Graph *g, GraphVertex *from, GraphVertex *to);

void
graph_debug             (Graph *g);

GraphArc *
graph_vertex_get_arc    (GraphVertex *from, GraphVertex *to);

	/**=================
		@Destructors
	===================*/

void
graph_unref 			(Graph *p);

#endif
