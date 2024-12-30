#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define MAX 100

typedef struct{
int src, dest, weight;
}Edge;

typedef struct{
int parent;
int rank;
}Subset;

int numVertices, numEdges;
Edge edges[MAX];
int labels[MAX];

int compare(const void *a, const void *b){
return((Edge*)a)->weight - ((Edge*)b)->weight;
}

int find(Subset subsets[], int i){
if(subsets[i].parent != i){
subsets[i].parent = find(subsets, subsets[i].parent);
}
return subsets[i].parent;
}

void UnionSubsets(Subset subsets[],int x,int y){
int xRoot = find(subsets, x);
int yRoot = find(subsets, y);

if(subsets[xRoot].parent < subsets[yRoot].parent){
subsets[xRoot].parent = yRoot;
} else if(subsets[xRoot].parent > subsets[yRoot].parent){
subsets[yRoot].parent = xRoot;
} else{
subsets[yRoot].parent = xRoot;
subsets[xRoot].rank++;
}
}

void Kruskals(int startIndex){
Edge result[MAX];
int e = 0;
int i = 0;
int j = 0;

qsort(edges, numEdges, sizeof(Edge), compare);

Subset *subsets = (Subset *)malloc(numVertices * sizeof(Subset));

for(int i = 0; i < numVertices; i++){
subsets[i].parent = i;
subsets[i].rank = 0;
}

while( e < numVertices - 1){
Edge nextEdge = edges[j++];

int x = find(subsets, nextEdge.src);
int y = find(subsets, nextEdge.dest);

if(x != y){
result[e++] = nextEdge;
UnionSubsets(subsets, x, y);
}
}

printf("Edge \tWeight\n");
for(int i = 0; i < e; i++){
printf("%d - %d \t%d\n",labels[result[i].src], labels[result[i].dest], result[i].weight);
}
free(subsets);
}

int main(){
int src, dest, weight, startVertex;

printf("ENter the number of vertices : \n");
scanf("%d", &numVertices);

printf("ENter the number of edges : \n");
scanf("%d", &numEdges);

printf("eNTER THE LABELS of the vertices : \n");
for(int i = 0; i < numVertices; i++){
scanf("%d", &labels[i]);
}

printf("Enter the edges (source, destination, weight):\n");

for(int i = 0; i < numEdges; i++){
int srcLabel, destLabel;
scanf("%d %d %d",&srcLabel, &destLabel, &weight);
for(int j = 0; j < numVertices; j++){
if(labels[j]==srcLabel) src = j;
if(labels[j]==destLabel) dest = j;
}
edges[i].src = src;
edges[i].dest = dest;
edges[i].weight = weight;
}

printf("Enter the starting vertex: \n");
scanf("%d", &startVertex);

int startIndex = -1;
for(int i = 0; i < numVertices; i++){
if(labels[i] == startVertex){
startIndex = i;
break;
}
}
if(startIndex == -1) {
printf("Invalid starting vertex!\n");
return 1;
}

return 0;
Kruskals(startIndex);
}

