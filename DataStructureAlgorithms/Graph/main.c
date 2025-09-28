#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph.h"

void err_exit(const char *msg);
bool disp_vertex(VERTEX *v);

int main(void)  
{
	HDGRAPH hdgraph;

	if ((hdgraph = build_graph("graph.csv")) == NULL) {
		fprintf(stderr, "cannot build graph!..\n");
		exit(EXIT_FAILURE);
	}

	traverse_depth_first_name(hdgraph, "A", disp_vertex);

	destroy_dgraph(hdgraph);

	return 0;
}

void err_exit(const char *msg)
{
	fprintf(stderr, "%s\n", msg);

	exit(EXIT_FAILURE);
}

bool disp_vertex(VERTEX *v)
{
	printf("%s\n", v->name);

	return true;
}