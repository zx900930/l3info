#include <stdio.h>

typedef struct {
	int u, v, w;
} arete;

int s; /* nb des sommets */
int a; /* nb des aretes */
arete aretes[1024]; /*  s <= 2^5=32 */
int d[32]; /*minimum distance de sommets s -> i */

#define INFINITY 10000

void printDist() {
	int i;

	printf("Distances:\n");

	for (i = 0; i < s; ++i)
		printf("to %d\t", i + 1);
	printf("\n");

	for (i = 0; i < s; ++i)
		printf("%d\t", d[i]);

	printf("\n\n");
}

void bellman_ford(int s) {
	int i, j;

	for (i = 0; i < s; ++i)
		d[i] = INFINITY;

	d[s] = 0;

	for (i = 0; i < s - 1; ++i)
		for (j = 0; j < a; ++j)
			if (d[aretes[j].u] + aretes[j].w < d[aretes[j].v])
				d[aretes[j].v] = d[aretes[j].u] + aretes[j].w;
}

int main(int argc, char *argv[]) {
	int i, j;
	int w;

	FILE *fin = fopen("dist.txt", "r");
	fscanf(fin, "%d", &s);
	a = 0;

	for (i = 0; i < s; ++i)
		for (j = 0; j < s; ++j) {
			fscanf(fin, "%d", &w);
			if (w != 0) {
				aretes[a].u = i;
				aretes[a].v = j;
				aretes[a].w = w;
				++a;
			}
		}
	fclose(fin);

	bellman_ford(0);

	printDist();

	return 0;
}
