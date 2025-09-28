#ifndef GRAPH_H_
#define GRAPH_H_

#include <stddef.h>
#include <stdbool.h>

/* Symbolic Constant */
#define DEF_VERTEX_CAPACITY 4
#define DEF_EDGE_CAPACITY   4
#define MAX_CSV_LINE_LENGTH 1024

/* Type Decleration */
typedef struct tagEDGE {
	struct tagVERTEX *v1;
	struct tagVERTEX *v2;

	/* EDGE INFO */
	double length;
} EDGE;

typedef struct tagVERTEX {
	EDGE **edges;
	size_t count;
	size_t capacity;
	size_t index;
	
	/* VERTEX INFO */
	char name[32];

} VERTEX;

typedef struct tagDGRAPH{
	VERTEX **vertices;
	size_t count;
	size_t capacity;
	size_t ecount;
} DGRAPH, *HDGRAPH;

/* Function Prototypes - Function Declerations */
HDGRAPH create_dgraph(void);
VERTEX *add_vertex(HDGRAPH hdgraph, VERTEX *vertex);
VERTEX *add_vertex_info(HDGRAPH hdgraph, const char *name);
EDGE *add_edge(HDGRAPH hdgraph, VERTEX *v1, VERTEX *v2, double length);
EDGE *add_edge_info(HDGRAPH hdgraph, const char *name1, const char *name2, double length);
DGRAPH *build_graph(const char *path);
bool traverse_depth_first_vertex(HDGRAPH hdgraph, VERTEX *vertex, bool (*proc)(VERTEX *));
bool traverse_depth_first_name(HDGRAPH hdgraph, const char *name, bool (*proc)(VERTEX *));
void clear_dgraph(HDGRAPH hdgraph);
void destroy_dgraph(HDGRAPH hdgraph);


/* Inline Function Definitions */
static inline size_t vertex_count(HDGRAPH hdgraph)
{
    return hdgraph->count;
}


#endif
