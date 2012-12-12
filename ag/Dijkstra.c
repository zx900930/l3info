/**
 *	@author		:	ZHOU Xiong
 *	@file		:	Dijkstra.c
*/
#include <stdlib.h>
#include <stdio.h>
#include "Dijkstra.h"

Dijkstra *dijkstra = NULL;

/* Constructeurs */
void
dijkstra_new (Graph *graph)
{
	GraphVertex *g_vertex = NULL;
	GraphArc *g_arc = NULL;

	Dijkstra *d = (Dijkstra *) malloc (sizeof(Dijkstra));

	if (d == NULL)
		return;

    graph_set_to_dijkstra(graph, d);

    foreach_bbqueue_item(graph->vertices, g_vertex)
    {
        dijkstra_vertex_new(g_vertex);

        foreach_bbqueue_item(g_vertex->arcs, g_arc)
        {
            dijkstra_arc_new(g_arc);
        }
    }

	dijkstra = d;
}

void
dijkstra_vertex_new (GraphVertex *g_vertex)
{
    DijkstraVertex *d_vertex = (DijkstraVertex *) malloc (sizeof(DijkstraVertex));

    if (d_vertex == NULL)
        return;

    d_vertex->prev = NULL;
    d_vertex->ds = 0.0;
    d_vertex->mark = 0;

    dijkstra_herit_graph(d_vertex, g_vertex);
}

void
dijkstra_arc_new (GraphArc *g_arc)
{
    DijkstraArc *d_arc = (DijkstraArc *) malloc (sizeof(DijkstraArc));

    if (d_arc == NULL)
        return;

    d_arc->dist = -1;

    dijkstra_herit_graph(d_arc, g_arc);
}


DijkstraPath *
dijkstra_path_new ()
{
    DijkstraPath *path = (DijkstraPath *) malloc (sizeof(DijkstraPath));

    if (path == NULL)
        return NULL;

    path->vertices = bb_queue_new();
    path->dist = 0.0;

    return path;
}



/* Accesseurs */
void
dijkstra_arc_set_dist (DijkstraArc *d_arc, double dist)
{
    d_arc->dist = dist;
}

void
dijkstra_vertex_set_dist (DijkstraVertex *dv_from, DijkstraVertex *dv_to, double dist)
{
    DijkstraArc *d_arc = dijkstra_vertex_get_arc(dv_from, dv_to);
    dijkstra_arc_set_dist(d_arc, dist);
}

void
dijkstra_gvertex_set_dist (GraphVertex *gv_from, GraphVertex *gv_to, double dist)
{
    DijkstraVertex *d_v_from, *d_v_to;

    d_v_from = graph_to_dijkstra(gv_from);
    d_v_to   = graph_to_dijkstra(gv_to);

    dijkstra_vertex_set_dist(d_v_from, d_v_to, dist);
}


DijkstraArc *
dijkstra_vertex_get_arc (DijkstraVertex *dv_from, DijkstraVertex *dv_to)
{
    GraphArc *g_arc = graph_vertex_get_arc (
        dijkstra_to_graph(dv_from),
        dijkstra_to_graph(dv_to)
    );

    return graph_to_dijkstra(g_arc);
}

/* Méthodes */
void
dijkstra_add_arc (GraphVertex *a, GraphVertex *b, double dist)
{
    GraphArc *g_arc = graph_add_arc(dijkstra_to_graph(dijkstra), a, b);

    dijkstra_vertex_new(a);
    dijkstra_vertex_new(b);

    dijkstra_arc_new(g_arc);
    dijkstra_arc_set_dist(graph_to_dijkstra(g_arc), dist);
}


DijkstraPath *
dijkstra_do (GraphVertex *gv_from, GraphVertex *gv_to, DijkstraCallback compute_weight)
{
    DijkstraVertex *dv_from,
                   *dv_to,
                   *n1, *n2;

    GraphVertex *gv = NULL;
    GraphArc *arc = NULL;
    BbQueue *nodes = bb_queue_new();

    DijkstraPath *path = dijkstra_path_new();

    dv_from = graph_to_dijkstra(gv_from);
    dv_to   = graph_to_dijkstra(gv_to);

    foreach_bbqueue_item (dijkstra_to_graph(dijkstra)->vertices, gv)
    {
        n1 = graph_to_dijkstra(gv);
        n1->ds = INFINITY;
        n1->prev = NULL;
        bb_queue_add(nodes, n1);
    }

    dv_from->ds = 0;

    while (bb_queue_get_length(nodes) > 0)
    {
        n1 = dijkstra_vertex_get_nearest(nodes);
        bb_queue_remv(nodes, n1);

        foreach_bbqueue_item (dijkstra_to_graph(n1)->arcs, arc)
        {
            n2 = graph_to_dijkstra(arc->to);
            if (compute_weight(n1, n2))
            {
                n2->ds = n1->ds + dijkstra_vertex_get_arc(n1, n2)->dist;
                n2->prev = (struct DijkstraVertex *) n1;
            }
        }
    }

    n1 = graph_to_dijkstra(gv_to);

    while (n1 != graph_to_dijkstra(gv_from))
    {
        bb_queue_push(path->vertices, dijkstra_to_graph(n1));
        n1 = (DijkstraVertex *)n1->prev;
    }

    bb_queue_push(path->vertices, gv_from);

    return path;
}


DijkstraVertex *
dijkstra_vertex_get_nearest (BbQueue *nodes)
{
    DijkstraVertex *dv_node = NULL,
                   *dv_near = NULL;

    double ds_min = INFINITY;

    foreach_bbqueue_item (nodes, dv_node)
    {
        if (dv_node->ds < ds_min)
        {
            ds_min = dv_node->ds;
            dv_near = dv_node;
        }
    }

    return dv_near;
}

void
dijkstra_debug ()
{
    Graph *g = dijkstra_to_graph(dijkstra);
    GraphVertex *vertex;
    GraphArc *g_arc;
    int loop_counter = 0;

    foreach_bbqueue_item (g->vertices, vertex)
    {
        printf("- Arcs du vertex %c : \n", 'A' + loop_counter++);

        foreach_bbqueue_item (vertex->arcs, g_arc)
        {
            printf("(0x%x) -> 0x%x, distance : %.2lf\n", (int)g_arc->from, (int)g_arc->to, D_ARC(graph_to_dijkstra(g_arc))->dist);
        }

        printf("\n");
    }
}

void
dijkstra_arc_debug (DijkstraArc *d_arc)
{
    GraphArc *g_arc = dijkstra_to_graph(d_arc);
    printf("Distance : %.2lf, %2x->%2x \n", d_arc->dist, (int)g_arc->from, (int)g_arc->to);
}

void
dijkstra_vertex_debug (DijkstraVertex *dv)
{
    GraphArc *g_arc;
    GraphVertex *gv;
    DijkstraArc *d_arc;
    int counter = 1;

    printf("Debug vertex %x :\n", (int)dv);

    gv = dijkstra_to_graph(dv);

    printf("Nombre d'arcs : %d\n", bb_queue_get_length(gv->arcs));

    foreach_bbqueue_item(gv->arcs, g_arc)
    {
        d_arc = graph_to_dijkstra(g_arc);
        printf("%d : ", counter++);
        dijkstra_arc_debug(d_arc);
    }

    printf("\n");
}

void
dijkstra_unref (Dijkstra *p)
{
	if (p != NULL)
	{
		free(p);
	}
}

