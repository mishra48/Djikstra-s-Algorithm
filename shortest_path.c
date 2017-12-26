#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h> //DONT FORGET TO USE -lm FLAGWHILE COMPILING!!!!!!!
#include <string.h>
 
 
 
//typdef for node 
typedef struct Node
{
    int vertex_val;
    int weight;
	int x;
	int y;
    struct Node* next;
}Node;
 
//typedef for graph
typedef struct Graph
{
    int vertices;
    Node** list;
}Graph;

// typedef for heap node
typedef struct Heap_Node
{
    int  v;
    int distance;
	struct Heap_Node* parent; // to store the path of min.
}Heap_Node;
 
// typedef for Heap structure
typedef struct Heap
{
    int size;      
    Heap_Node **array;
	int capacity;  
    int *track; 
}Heap;
 
// create a new node with the given given vertex and the weight.
Node* create_node(int vertex_val, int weight) {
    Node* node =  malloc(sizeof(struct Node));
    node->weight = weight;
	node->next = NULL;
    node->vertex_val = vertex_val;
	node -> x = -1;
	node -> y = -1;
	return node;
}

//initializzing the map with the number of given nodes

Graph* init_map(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->list =  malloc(sizeof(Node*)* vertices);
	graph->vertices = vertices;
     int i;
    for (i = 0; i < vertices; i++)
        graph->list[i] = NULL;
 
    return graph;
}
 
// function to join two nodes with their given weight 
// by calculation the euclidean distance
void join_vertex(struct Graph* graph, int source, int vertex_val, int weight)
{
    Node* temp = create_node(vertex_val, weight);
    temp->next = graph->list[source];
    graph->list[source] = temp;
 
    temp = create_node(source, weight);
    temp->next = graph->list[vertex_val];
    graph->list[vertex_val] = temp;
}
 
// A function to create a heap node with given vertex and the weight
Heap_Node* create_heap_node(int vertex, int weight)
{
    Heap_Node* heap_node = malloc(sizeof(Heap_Node));
    heap_node->distance = weight;  
    heap_node->v = vertex;
    return heap_node;
}
 
//function to create heap of given capacity
Heap* create_heap(int capacity)
{
    Heap* heap = malloc(sizeof(Heap));
    heap->track = malloc(capacity * sizeof(int));
    heap->array = malloc(sizeof(Heap_Node*)*capacity);
    heap->capacity = capacity;
	heap->size = 0;
	return heap;
}
 
void swap(Heap_Node** first, Heap_Node** second)
{
    Heap_Node* temp;
	temp = *first;
    *first = *second;
    *second = temp;
}

// fnction ot heapify the tree
void heapify(Heap* heap, int index)
{
    //taken from lecture note
	int left = 2 * index + 1;
    int right = 2 * index + 2;
	int root = index;
 
    if (left < heap->size && heap->array[left]->distance < heap->array[root]->distance)
      root = left;
    if (right < heap->size && heap->array[right]->distance < heap->array[root]->distance)
      root = right;
    if (root != index)
    {
        swap(&heap->array[root], &heap->array[index]);
        heapify(heap, root);
    }
} 


// funtion to get min node from heap
Heap_Node* get_min(Heap* heap)
{
    Heap_Node* temp;
	Heap_Node* temp2;
	temp = heap->array[0];
	temp2 = heap -> array[heap -> size -1];
	heap -> array[0] = temp2;
	
    heap->track[temp -> v] = heap -> size -1;
	heap -> track[temp2 -> v] = 0;
    heap->size = heap -> size -1;
    heapify(heap, 0);
    return temp;
}
 
//function to find the node with the minimum distance from the destination
void min_distance( Heap* heap, int vertex, int distance)
{
    
    int i = heap->track[vertex];
    heap->array[i]->distance = distance;
	int temp = (i - 1)/2;
    
    while (heap->array[i]->distance < heap->array[(i-1)/2]->distance && i != 0)
    {
        
		temp = (i - 1)/2;
		// Swap this node with its parent
        heap->track[heap->array[i]->v] = (i - 1)/2;
        heap->track[heap->array[(i-1)/2]->v] = i;
        swap(&heap->array[i],  &heap->array[(i-1)/2]);
        i = i -1;
    	i = i /2;
    }
}


void print_path_util(Heap_Node *last)
{
    while (last != NULL)
    {
       // printf ("%d -> ", last->v);

        last = last->parent;
    }

   // printf ("NULL\n");
}

void print_path(long path[], int vertices, int destination) {
	long temp[vertices];
	int j = 0;
	int l;
	while( destination >= 0) {
			temp[j] = destination;
			destination = path[destination];
			j++;
	}
	for( l = j; l > 0; l --) {
	
		j--;
		printf("%ld ", temp[j]);
	}
	printf("\n");
}
void  add_coordinates(Node* node, int x, int y) {
	node -> x = x;
	node -> y = y;
}

bool is_vertex_present(int value, Graph* graph, int vertices) {
	int i; 
	bool g = false;
	for( i = 0 ; i < vertices ; i++ ) {
			if(graph -> list[0] -> vertex_val == value) {
				return true;
			}
	}
	return g;
}
	
		
 
//function to get the shortest path
void dijkstra(Graph* graph, int source, int destination) {
	
    int vertices = graph->vertices;
    int dist[vertices];      
	int test;
	bool g = true;
	long path[vertices];
	bool h = is_vertex_present(source, graph, vertices);
	 h = is_vertex_present(destination, graph, vertices);
	if( g == false) {
		printf("INF\n");
		printf("%d %d\n", source, destination);
		return;
	}
	//long path2[vertices];
	//bool g = true;
    Heap* heap = create_heap(vertices);
	//long p;
	int i;
    for (i = 0; i < vertices; i++)
    {
        dist[i] = INT_MAX;
        heap->array[i] = create_heap_node(i, dist[i]);
        heap->track[i] = i;
		path[i] = -1;
    }
    
    heap->array[source] = create_heap_node(source, dist[source]);
    heap->track[source]   = source;
    dist[source] = 0;
	
    min_distance(heap, source, dist[source]);
 
    heap->size = vertices;
 	Heap_Node* prev = NULL;
	//bool g = true;
    while (g == true)
    {
        if(heap -> size == 0)  {
			g = false;
			break;
	    }
        Heap_Node* heap_node = get_min(heap);
		test = heap_node -> v;
		heap_node -> parent = prev;
		prev = heap_node;
			
        Node* temp = graph->list[heap_node->v];
		
		while (temp != NULL)
        {
           //printf("v = %d", v);
		   //check if the node isnt updates and the new distance is less than the old one
            if (heap->track[temp->vertex_val] < heap->size && dist[heap_node->v] != INT_MAX && temp->weight + dist[heap_node->v] < dist[temp->vertex_val])
            {
                dist[temp->vertex_val] = dist[heap_node->v] + temp->weight;
				path[temp -> vertex_val] = heap_node -> v;
				//printf("%d ", path[v]);
                 min_distance(heap, temp->vertex_val, dist[temp->vertex_val]);
            }
            temp = temp->next;
        
		}
	}
	//printArr(dist, V);
	 //p = destination;
	 
	/* for(int i = 0; i < V; i++) {
		printf("%d ", path[i]);
	}*/
	
	if(dist[destination] != INT_MAX) {
		printf("%d\n", dist[destination]);
		print_path(path, vertices, destination);
	}

		
	else {
		printf("INF\n");
		printf("%d %d\n", source, destination);
	}
	print_path_util(prev);
	
}


double calc_weight(int x1, int y1, int x2, int y2) {
	return(sqrt((y2-y1)*(y2-y1) + (x2-x1)*(x2-x1)));
}
 
// Driver program to test above functions
int main(int argc , char** argv){
    FILE* str = fopen(argv[1], "r");
	if(str == NULL) {
		printf("problem opening file\n");
	}
   	int vertices, edges; 
	int source;
	int vertex_val;
	int i;
	int g = 1;
	int number;
	int xc;
	int yc;
	int weight;
	fscanf(str, "%d", &vertices) ;
	//printf("vertices; %d", vertices);
	fscanf(str, "%d", &edges);
	int x_coor[vertices];
	int y_coor[vertices];
	for(i = 0; i < vertices; i++) {
			
			if(fscanf(str, "%d", &number) != 1) {
				g = 0;
				break;
			}
			if(fscanf(str, "%d", &xc) != 1) {
				g = 0;
				break;
			}
			if(fscanf(str, "%d", &yc) != 1) {
				g = 0;
				break;
			}
			x_coor[i] = xc;
			y_coor[i] = yc;
			//printf("coord of vertex %d  are %d %d \n", i, x_coor[i], y_coor[i]);
	}
	fseek ( str , 0, SEEK_SET );
	fscanf(str, "%d", &vertices) ;
	Graph* graph = init_map(vertices);
	fscanf(str, "%d", &edges);
	//struct Node* temp;
	while(g ) {
		for(i = 0; i < vertices; i++) {
			
			if(fscanf(str, "%d", &number) != 1) {
				g = 0;
				break;
			}
			if(fscanf(str, "%d", &xc) != 1) {
				g = 0;
				break;
			}
			if(fscanf(str, "%d", &yc) != 1) {
				g = 0;
				break;
			}
		}
		
		int h = 1;
		while(h){
			
			if(fscanf(str, "%d", &source) != 1) {
				h = 0;
				g = 0;
				break;
				
			}
			
			if(fscanf(str, "%d", &vertex_val) != 1) {
				h = 0;
				g = 0;
				break;
				 
			}
			
			weight = calc_weight(x_coor[source], y_coor[source], x_coor[vertex_val], y_coor[vertex_val]);
			//printf("checking the addedge func graph, %d, %d, %d\n", source, vertex_val, weight);
			join_vertex(graph, source, vertex_val, weight);
			//printf("weight between %d and %d = %lf\n",source, vertex_val,weight);
		}
	}
	FILE* str2 = fopen(argv[2], "r");
	int queries;
	int src;
	int destination;
	fscanf(str2, "%d", &queries);
	for(i = 0; i < queries; i++) {
			g = true;
			fscanf(str2, "%d", &src);
			fscanf(str2, "%d", &destination);
			bool h = is_vertex_present(src, graph, vertices);
			h = is_vertex_present(destination, graph, vertices);
			if( g == false) {
				printf("INF\n");
				printf("%d %d\n", source, destination);
				
			}
			else 
			dijkstra(graph, src, destination);	
	}			
	fclose(str);
	fclose(str2);
    return 0;
}