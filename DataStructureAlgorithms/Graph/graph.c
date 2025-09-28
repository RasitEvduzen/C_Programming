#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"


static VERTEX *find_vertex_name(HDGRAPH hdgraph, const char *name);
static EDGE *create_edge(VERTEX *v1, VERTEX *v2, double length);
static VERTEX *create_vertex(const char *name);
static bool traverse_depth_first_vertex_recur(VERTEX *vertex, int *visiteds, bool (*proc)(VERTEX *));

HDGRAPH create_dgraph(void)
{
	HDGRAPH hdgraph;

	if ((hdgraph = (HDGRAPH)malloc(sizeof(DGRAPH))) == NULL)
		return NULL;

	if ((hdgraph->vertices = (VERTEX **)malloc(DEF_VERTEX_CAPACITY * sizeof(VERTEX *))) == NULL) {
		free(hdgraph);
		return NULL;
	}
	hdgraph->count = 0;
	hdgraph->capacity = DEF_VERTEX_CAPACITY;
	hdgraph->ecount = 0;

	return hdgraph;
}

VERTEX *add_vertex(HDGRAPH hdgraph, VERTEX *vertex)
{
	VERTEX **new_vertices;

	if (find_vertex_name(hdgraph, vertex->name) != NULL)
		return NULL;

	if (hdgraph->count == hdgraph->capacity) {
		if ((new_vertices = realloc(hdgraph->vertices, hdgraph->capacity * sizeof(VERTEX *) * 2)) == NULL)
			return NULL;
		hdgraph->vertices = new_vertices;
		hdgraph->capacity *= 2;
	}
	vertex->index = hdgraph->count;
	hdgraph->vertices[hdgraph->count] = vertex;
	++hdgraph->count;

	return vertex;
}

VERTEX *add_vertex_info(HDGRAPH hdgraph, const char *name)
{
	VERTEX *vertex;
	VERTEX **new_vertices;

	if (find_vertex_name(hdgraph, name) != NULL)
		return NULL;

	if ((vertex = create_vertex(name)) == NULL)
		return NULL;

	if (hdgraph->count == hdgraph->capacity) {
		if ((new_vertices = realloc(hdgraph->vertices, hdgraph->capacity * sizeof(VERTEX *) * 2)) == NULL)
			return NULL;
		hdgraph->vertices = new_vertices;
		hdgraph->capacity *= 2;
	}
	vertex->index = hdgraph->count;
	hdgraph->vertices[hdgraph->count] = vertex;
	++hdgraph->count;

	return vertex;
}

EDGE *add_edge(HDGRAPH hdgraph, VERTEX *v1, VERTEX *v2, double length)
{
	EDGE *edge;
	EDGE **new_edges;

	if ((edge = create_edge(v1, v2, length)) == NULL)
		return NULL;

	if (v1->count == v1->capacity) {
		if ((new_edges = realloc(v1->edges, v1->capacity * 2 * sizeof(EDGE *))) == NULL) {
			free(edge);
			return NULL;
		}
		v1->capacity *= 2;
	}
	v1->edges[v1->count] = edge;
	++v1->count;

	++hdgraph->ecount;

	return edge;
}

EDGE *add_edge_info(HDGRAPH hdgraph, const char *name1, const char *name2, double length)
{
	VERTEX *v1, *v2;
	EDGE *edge;

	if ((v1 = find_vertex_name(hdgraph, name1)) == NULL) {
		if ((v1 = create_vertex(name1)) == NULL) 
			return NULL;
		if (add_vertex(hdgraph, v1) == NULL)
			goto EXIT1;
	}

	if ((v2 = find_vertex_name(hdgraph, name2)) == NULL) {
		if ((v2 = create_vertex(name2)) == NULL) 
			goto EXIT1;
		if (add_vertex(hdgraph, v2) == NULL)
			goto EXIT2;
	}

	if ((edge = add_edge(hdgraph, v1, v2, length)) == NULL) 
		goto EXIT2;

	return edge;

EXIT2:
	free(v2);
EXIT1:
	free(v1);

	return NULL;
}

DGRAPH *build_graph(const char *path)
{
	FILE *f;
	HDGRAPH hdgraph;
	char buf[MAX_CSV_LINE_LENGTH + 2];
	const char *name1, *name2, *length;
	char *str;

	if ((f = fopen(path, "r")) == NULL)
		goto EXIT1;

	if ((hdgraph = create_dgraph()) == NULL)
		goto EXIT2;

	while (fgets(buf, MAX_CSV_LINE_LENGTH + 2, f) != NULL) {
		if ((name1 = strtok(buf, ",\n")) == NULL)
			continue;
		if ((name2 = strtok(NULL, ",\n")) == NULL)
			goto EXIT3;
		if ((length = strtok(NULL, ",\n")) == NULL)
			goto EXIT3;
		if (strtok(NULL, ",\n") != NULL)
			goto EXIT3;
		if (add_edge_info(hdgraph, name1, name2, atof(length)) == NULL)
			goto EXIT3;
	}

	return hdgraph;

EXIT3:
	destroy_dgraph(hdgraph);
EXIT2:
	fclose(f);
EXIT1:
	return NULL;
}

bool traverse_depth_first_vertex(HDGRAPH hdgraph, VERTEX *vertex, bool (*proc)(VERTEX *))
{
	int *visiteds;
	bool result;

	if (!proc(vertex))
		return false;

	if ((visiteds = (int *)calloc(hdgraph->count, sizeof(int))) == NULL)
		return false;

	result = traverse_depth_first_vertex_recur(vertex, visiteds, proc);

	free(visiteds);

	return result;
}

bool traverse_depth_first_name(HDGRAPH hdgraph, const char *name, bool (*proc)(VERTEX *))
{
	VERTEX *vertex;

	if ((vertex = find_vertex_name(hdgraph, name)) == NULL)
		return false;

	return traverse_depth_first_vertex(hdgraph, vertex, proc);
}

void clear_dgraph(HDGRAPH hdgraph)
{
	for (size_t v = 0; v < hdgraph->count; ++v) {
		for (size_t e = 0; e < hdgraph->vertices[v]->count; ++e)
			free(hdgraph->vertices[v]->edges[e]);
		hdgraph->vertices[v]->count = 0;
		free(hdgraph->vertices[v]);
	}
	hdgraph->count = 0;
}

void destroy_dgraph(HDGRAPH hdgraph)
{
	for (size_t v = 0; v < hdgraph->count; ++v) {
		for (size_t e = 0; e < hdgraph->vertices[v]->count; ++e)
			free(hdgraph->vertices[v]->edges[e]);
		free(hdgraph->vertices[v]->edges);
	
	}
	free(hdgraph->vertices);
	free(hdgraph);
}

static VERTEX *create_vertex(const char *name)
{
	VERTEX *vertex;

	if ((vertex = (VERTEX *)malloc(sizeof(VERTEX))) == NULL)
		return NULL;

	if ((vertex->edges = (EDGE **)malloc(DEF_EDGE_CAPACITY * sizeof(EDGE *))) == NULL) {
		free(vertex);
		return NULL;
	}
	vertex->count = 0;
	vertex->capacity = DEF_EDGE_CAPACITY;
	strcpy(vertex->name, name);

	return vertex;
}

static VERTEX *find_vertex_name(HDGRAPH hdgraph, const char *name)
{
	for (size_t i = 0; i < hdgraph->count; ++i)
		if (!strcmp(name, hdgraph->vertices[i]->name))
			return hdgraph->vertices[i];

	return NULL;
}

static EDGE *create_edge(VERTEX *v1, VERTEX *v2, double length)
{
	EDGE *edge;

	if ((edge = (EDGE *)malloc(sizeof(EDGE))) == NULL)
		return NULL;

	edge->v1 = v1;
	edge->v2 = v2;
	edge->length = length;

	return edge;
}

static bool traverse_depth_first_vertex_recur(VERTEX *vertex, int *visiteds, bool (*proc)(VERTEX *))
{
	VERTEX *v;

	visiteds[vertex->index] = 1;
	for (size_t e = 0; e < vertex->count; ++e) {
		v = vertex->edges[e]->v2;
		if (visiteds[v->index])
			continue;
		if (!proc(v))
			return false;
		if (!traverse_depth_first_vertex_recur(v, visiteds, proc))
			return false;
	}

	return true;
}