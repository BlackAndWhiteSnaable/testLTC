/*******************
 defs.h
*******************/
#include <stdio.h>      // Needed for printf
#include <stdlib.h>     // Needed for malloc

#define TRUE 1
#define FALSE 0
#define MAP_FILENAME "testmap.txt"  // Map to load

#define North     0x01
#define East      0x02
#define South     0x04
#define West      0x08
#define NorthEast 0x10
#define SouthEast 0x20
#define SouthWest 0x40
#define NorthWest 0x80

typedef struct {
  int x,y;
} Point;                        // A point, consisting of two integers

typedef struct Node {
  Point position;               // Nodes own x,y position on node map
  struct Node *n,*e,*s,*w;      // Pointers to neighbors straight
  struct Node *nw,*ne,*se,*sw;  // Pointers to neighbors diagonal
  struct Node *parent;          // Pointer to parent node
  unsigned char walls;          // Byte value for the 8 walls
  int movecost;                 // Steps needed to get here
} Nodes;

typedef struct {
  Point start;                  // Starting position
  Point finish;                 // Finish position
  Point size;                   // Amount of segments in the map
  //Point num_nodes;            // Number of nodes in the map
  unsigned char **segments;     // 2D array of the map data from file
  Nodes **node;                 // 2D array of nodes
} Maps;

typedef struct element {
  Nodes *node;                  // Pointer to the map node
	struct element *next;       // Next element in queue
} Queue, Stack;

typedef struct {
  Point pos;
  Maps map;
  Queue *unchecked;             // Head of queue for unchecked nodes
  Queue *checked;               // Head of stack for checked nodes
} Robot;

//---------------------------- FUNCTIONS----------------------------//

// Robot
void go();
Robot *init_robot();

// Map
void map_load(Robot *robot);
void map_save(Robot *robot);
void map_check(Robot *robot);
void map_update(Robot *robot, char hex);
void node_map_load(Robot *robot);
int robot_finished(Robot *robot);
void test_node_array(Robot *robot);

// Scan
unsigned char scan();

// Move
void move_next(Robot *robot);

// Priority queue
void pushQ(Queue **HoQ, Nodes *new_node); // Add element on the stack
void pop(Queue *tq);                      // Pops element from stack
void printQueue(Queue *tq);               // Prints stack
void emptyQueue(Queue *tq);               // Pops whole stack

// Pathfinding
void path_test(Robot *robot);
void path_set_neighbors(Robot *robot);
void path_calculate(Robot *robot);
