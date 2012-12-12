/**
 *  @author		:	ZHOU Xiong
 *  @file		:	Dijkstra.h
 *  @version	:	1.0
 *  @date		:	2012 L3 INFO Paris 13
*/

#ifndef Dijkstra_H_INCLUDED
#define Dijkstra_H_INCLUDED

/* Includes */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "Graph.h"

/* Working Macros */
#define graph_to_dijkstra(graph_object) \
    (graph_object->_impl_data)

#define dijkstra_herit_graph(d_obj, g_obj)      \
do {                                            \
    graph_set_to_dijkstra(g_obj, d_obj);        \
    dijkstra_set_to_graph(d_obj, g_obj);        \
} while (0);                                    \

#define dijkstra_to_graph(dijkstra_object) \
    (dijkstra_object->_graph_object)

#define graph_set_to_dijkstra(graph_object, dijkstra_object) \
    (dijkstra_to_graph(dijkstra_object) = graph_object)     \

#define dijkstra_vertex_get_dest(graph_arc) \
    (graph_to_dijkstra(graph_arc->to))

#define dijkstra_set_to_graph(dijkstra_object,graph_object) \
    (graph_to_dijkstra(graph_object) = dijkstra_object)     \

#define D_ARC(x)    ((DijkstraArc *)x)
#define D_VERTEX(x) ((DijkstraVertex *)x)

#define S_D_ARC(x)    ((struct DijkstraArc *)x)
#define S_D_VERTEX(x) ((struct DijkstraVertex *)x)

typedef
struct _Dijkstra
{
    /* Dijkstra extends Graph */
    Graph *_graph_object;

}	Dijkstra;

typedef
struct _DijkstraVertex
{
    /* DijkstraVertex extends GraphVertex */
    GraphVertex *_graph_object;

    struct DijkstraVertex *prev;
    int mark;
    double ds;

}   DijkstraVertex;

typedef
struct _DijkstraArc
{
    /* DijkstraArc extends GraphArc */
    GraphArc *_graph_object;
    double dist;

}   DijkstraArc;

typedef
struct _DijkstraRoad
{
    BbQueue *vertices;
    double dist;

}   DijkstraPath;

typedef
int (*DijkstraCallback)     (DijkstraVertex *from, DijkstraVertex *to);

	/**=================
		@Constructors
	===================*/

void
dijkstra_new                (Graph *g);

void
dijkstra_arc_new            (GraphArc *a);

void
dijkstra_vertex_new         (GraphVertex *v);


	/**=================
		  @Methods
	===================*/

DijkstraArc *
dijkstra_vertex_get_arc     (DijkstraVertex *from, DijkstraVertex *to);


void
dijkstra_add_arc            (GraphVertex *a, GraphVertex *b, double dist);


void
dijkstra_debug              ();

void
dijkstra_vertex_debug       (DijkstraVertex *dv);

DijkstraPath *
dijkstra_do                 (GraphVertex *gv_from, GraphVertex *gv_to, DijkstraCallback compute_weight);

DijkstraVertex *
dijkstra_vertex_get_nearest (BbQueue *nodes);

	/**=================
		@Destructors
	===================*/

void
dijkstra_unref 			    (Dijkstra *p);

#endif
