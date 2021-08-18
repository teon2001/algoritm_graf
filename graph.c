#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "heap.h"

typedef int TCost;

typedef struct node
{
	int v;
	TCost c;
	struct node *next;
} TNode, *ATNode;

typedef struct
{
	int nn;
	ATNode *adl;
}	TGraphL;


void alloc_list(TGraphL * G, int n)
{
    int i;
    G->nn = n;
	G->adl = (ATNode*) malloc((n+1)*sizeof(ATNode));
	for(i = 0; i < n; i++)
		G->adl[i] = NULL;

}

void free_list(TGraphL *G)
{
    int i;
    ATNode it;
    for(i = 1; i < G->nn; i++){
		it = G->adl[i];
		while(it != NULL){
			ATNode aux = it;
			it = it->next;
			free(aux);
		}
		G->adl[i] = NULL;
	}
	G->nn = 0;
}

void insert_edge_list(TGraphL *G, int v1, int v2, int c)
{
 TNode *t;
 t=(ATNode)malloc(sizeof(TNode));
 t->v = v2; t->c=c; t->next = G->adl[v1]; G->adl[v1]=t;
 t=(ATNode)malloc(sizeof(TNode));
 t->v = v1;  t->c=c; t->next = G->adl[v2]; G->adl[v2]=t;
}

int get_edge(TGraphL G, int u, int v) {
	for(ATNode iter = G.adl[u]; iter!= NULL; iter = iter->next) 
		if(iter->v == v)
			return iter->c;
	return INT_MAX/3;
}

void dijkstra(TGraphL G, int s)
{
    MinHeap* h = newQueue(G.nn);
	for(int i=0; i<G.nn; i++) {
		insert(h, i, INT_MAX/3);
	}
	SiftUp(h, s, 0);
	while(!isEmpty(h)) {
		MinHeapNode* u = removeMin(h);
		//parcurge lista adl G->adl[u->v]
		for(int v = 0; v < G.nn; v++) {
			if(isInMinHeap(h, v) && get_dist(h, v) > u->d + get_edge(G,u->v,v)) {
				// d[v] = d[u]+cost(u,v);
				SiftUp(h, v, u->d + get_edge(G,u->v,v));
			}
		}
	} 
}

void Prim(TGraphL G)
{
	int parent[G.nn];
	MinHeap* h = newQueue(G.nn);
	for(int i=0; i<G.nn; i++) {
		insert(h, i, INT_MAX/3);
	}
	
	SiftUp(h, 0, 0);
	while(!isEmpty(h)) {
		MinHeapNode* u = removeMin(h);
		for(int v = 0; v < G.nn; v++) {
			if(isInMinHeap(h, v) && get_dist(h, v) > get_edge(G,u->v,v)) {
				SiftUp(h, v, get_edge(G,u->v,v));
				parent[v] = u->v;
			}
		}
	}
	for(int i = 1; i < G.nn; i++)
		printf("parent: %d ---> v %d\n", parent[i], i);
}

int main()
{
    int i,v1,v2,c;
	int V,E;
	TGraphL G;
	ATNode t;
	freopen ("graph.in", "r", stdin);
	scanf ("%d %d", &V, &E);
	alloc_list(&G, V);

	for (i=1; i<=E; i++)
	{
		scanf("%d %d %d", &v1, &v2, &c);
	    insert_edge_list(&G, v1,v2, c);
	}

	for(i=0;i<G.nn;i++)
	{
    	printf("%d : ", i);
    	for(t = G.adl[i]; t != NULL; t = t->next)
   			 printf("%d ",t->v);
    		 printf("\n");
	}
	dijkstra(G,0);
	Prim(G);

	return 0;
}