#include "defs.h"

/// Testing examples of queue push/pop functions
void path_test(Robot *robot) {

  // Set some dummy movecost values for testing
  robot->map.node[0][0].movecost = 5;
  robot->map.node[0][1].movecost = 10;
  robot->map.node[0][2].movecost = 20;
  robot->map.node[0][3].movecost = 4;

  // Push some nodes to queue
  printf("\n[INFO]\tPushing 4 node elements to queue\n");
  push_queue(&robot->unchecked, &robot->map.node[0][0]);
  push_queue(&robot->unchecked, &robot->map.node[0][1]);
  push_queue(&robot->unchecked, &robot->map.node[0][2]);
  push_queue(&robot->unchecked, &robot->map.node[0][3]);

  Nodes *node; // Empty pointer used for nodes returned when popping

  // Pop 2 of the 4 elements in the queue
  node = pop(&robot->unchecked);
  printf("\n[INFO]\tPopped queue element, node returned: node->movecost=%d\n", node->movecost);

  node = pop(&robot->unchecked);
  printf("[INFO]\tPopped queue element, node returned: node->movecost=%d\n", node->movecost);

  // Print what is in the queue
  printf("\n\tUnchecked queue:\n");
  print_queue(robot->unchecked);

  printf("\n[INFO]\tPushing 4 node elements to stack\n");
  push_stack(&robot->checked, &robot->map.node[0][0]);
  push_stack(&robot->checked, &robot->map.node[0][1]);
  push_stack(&robot->unchecked, &robot->map.node[0][2]);
  push_stack(&robot->unchecked, &robot->map.node[0][3]);

  node = pop(&robot->checked);
  printf("\n[INFO]\tPopped stack element, node returned: node->movecost=%d\n", node->movecost);


  printf("\nChecked stack:\n");
  print_stack(robot->checked);

}

///finds all neighbors of a node and sets them as pointers
void path_set_neighbors(Robot *robot) {
  printf("\n[INFO]\tStarted linking nodes to neighbors\n");
  for (int i = 0; i<(robot->map.size.x-1)/2; i++){
    for (int j=0; j<(robot->map.size.y-1)/2; j++){
      //printf("[INFO]\tlinking\t[%2i][%2i]\n",i,j);
      if (!(robot->map.node[i][j].walls & N)){
        robot->map.node[i][j].n=&robot->map.node[i-1][j];
      } else {
        robot->map.node[i][j].n=NULL;
      }
      if (!(robot->map.node[i][j].walls & E)){
        robot->map.node[i][j].e=&robot->map.node[i][j+1];
      } else {
        robot->map.node[i][j].e=NULL;
      }
      if (!(robot->map.node[i][j].walls & S)){
        robot->map.node[i][j].s=&robot->map.node[i+1][j];
      } else {
        robot->map.node[i][j].s=NULL;
      }
      if (!(robot->map.node[i][j].walls & W)){
        robot->map.node[i][j].w=&robot->map.node[i][j-1];
      } else {
        robot->map.node[i][j].w=NULL;
      }

      if (!(robot->map.node[i][j].walls & NE)){
        robot->map.node[i][j].ne=&robot->map.node[i-1][j+1];
      } else {
        robot->map.node[i][j].ne=NULL;
      }
      if (!(robot->map.node[i][j].walls & SE)){
        robot->map.node[i][j].se=&robot->map.node[i+1][j+1];
      } else {
        robot->map.node[i][j].se=NULL;
      }
      if (!(robot->map.node[i][j].walls & SW)){
        robot->map.node[i][j].sw=&robot->map.node[i+1][j-1];
      } else {
        robot->map.node[i][j].sw=NULL;
      }
      if (!(robot->map.node[i][j].walls & NW)){
        robot->map.node[i][j].nw=&robot->map.node[i-1][j-1];
      } else {
        robot->map.node[i][j].nw=NULL;
      }

      robot->map.node[i][j].movecost = 0xFFF; //set movecost to something high
                                              //reset to 0 for start later
      robot->map.node[i][j].parent = NULL;    //set parent pointer to NULL

      //map_print_node(&robot->map.node[i][j]);

      //printf("[INFO]\t[%2i][%2i] has been linked\n\n\n",i,j);
    }
  //printf("\n");
  }
  robot->map.node[robot->map.start.x][robot->map.start.y].movecost = 0;
  printf("[INFO]\tDone linking nodes to neighbors\n");
}

///calculates the path from the current position
void path_calculate(Robot *robot) {
  //declare all variable needed in scope
  int curx,cury;          //to keep track of your food/position on the map
                          //should not be necessary, but would clean up the code
  Nodes *currNode;        //the Node currently looked at

  //make sure that all nodes have the correct neighbors
  path_set_neighbors(robot);

  //start calculating from current position, not start
  curx = robot->pos.x;
  cury = robot->pos.y;

  //[DEV] checks where robot is
  if (curx==robot->map.start.x && cury==robot->map.start.y){
    printf("\n[DEV]\tRobot is at start position [%02i][%02i]\n",curx,cury);
  } else printf("\n[DEV]\tRobot is at position [%02i][%02i]\n",curx,cury);

  //pushes current node onto stack after setting movecost to 0
  if (robot->map.node[curx][cury].movecost != 0){
    robot->map.node[curx][cury].movecost = 0;
  }
  push_queue(&robot->unchecked, &robot->map.node[curx][cury]);


  //check whether queue is empty, if yes, push start on queue
  currNode=pop(&robot->unchecked);
  if (!currNode){
    printf("[WARNING]\tQueue was empty, putting robot position\n");
    currNode = &robot->map.node[curx][cury];
  } else printf("[DEV]\tCurrent node popped\n");

  while (curx!=robot->map.finish.x && cury!=robot->map.finish.y){   //do until we reach the finish
    if (currNode==NULL){
      printf("[WARNING]\tsomething went wrong\n");
      break;
    }/*
    printf("\n[DEV]\tCurrently calculating at [%02i][%02i]\n",curx,cury);
    printf("[DEV]\tCurrent node has movecost %i\n",currNode->movecost);
    printf("[DEV]\tCurrent neighbors:\n");

    */
    //explaining the if once
    //checks whether the neighbor exists, then if movecost is smaller
      //updates neighbor movecost
      //updates neighbor parent
      //remove parent as neighbor
      //prints neighbor (debugging)
      //pushes neighbor on queue
    //

    if (currNode->n && (currNode->n->movecost > currNode->movecost+10)){
      currNode->n->movecost = currNode->movecost+10;
      currNode->n->parent = currNode;
      currNode->n->s = NULL;
      //map_print_node(currNode->n);
      push_queue(&robot->unchecked, currNode->n);
    }
    if (currNode->e && (currNode->e->movecost > currNode->movecost+10)){
      currNode->e->movecost = currNode->movecost+10;
      currNode->e->parent = currNode;
      currNode->e->w = NULL;
      //map_print_node(currNode->e);
      push_queue(&robot->unchecked, currNode->e);
    }
    if (currNode->s && (currNode->s->movecost > currNode->movecost+10)){
      currNode->s->movecost = currNode->movecost+10;
      currNode->s->parent = currNode;
      currNode->s->n = NULL;
      //map_print_node(currNode->s);
      push_queue(&robot->unchecked, currNode->s);
    }
    if (currNode->w && (currNode->w->movecost > currNode->movecost+10)){
      currNode->w->movecost = currNode->movecost+10;
      currNode->w->parent = currNode;
      currNode->w->e = NULL;
      //map_print_node(currNode->w);
      push_queue(&robot->unchecked, currNode->w);
    }


    //printf("[INFO]\tNode computed!\n");
    push_stack(&robot->checked, currNode);
    //print_stack(robot->checked);
    //print_queue(robot->unchecked);

    currNode = pop(&robot->unchecked);
    curx = currNode->position.x;
    cury = currNode->position.y;
  }


  printf("\n[INFO]\tDone calculating path!\n");
  print_stack(robot->checked);
  print_queue(robot->unchecked);
  printf("\n[DEV]\tThis is how far I am programming --Daniel\n\n\n");
}
