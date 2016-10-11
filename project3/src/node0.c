#include <stdio.h>
#include <stdlib.h>
#include "project3.h"

extern int TraceLevel;
extern float clocktime;

struct distance_table {
  int costs[MAX_NODES][MAX_NODES];
};
struct distance_table dt0;
struct NeighborCosts* neighbor0;

//Forward declaration
void printdt0( int MyNodeNumber, struct NeighborCosts *neighbor, struct distance_table *dtptr);

//Initalize the table
void rtinit0() {
  //Convenience for copy/paste between nodeN.c files
  int self_index = 0;
  struct distance_table dt = dt0;
  struct NeighborCosts* neighbor = neighbor0;
  void (*print_func)(int, struct NeighborCosts*, struct distance_table*) = printdt0;

  //Initialize to INFINITY
  for(int i = 0; i < MAX_NODES; i++) {
    for(int j = 0; j < MAX_NODES; j++) {
      dt.costs[i][j] = INFINITY;
    }
  }

  //Get direct neighbor costs
  int init_costs[MAX_NODES];
  neighbor = getNeighborCosts(self_index);
  for(int i = 0; i < neighbor->NodesInNetwork; i++) {
    dt.costs[i][i] = neighbor->NodeCosts[i];
    init_costs[i] = neighbor->NodeCosts[i];
  }

  //Print the current costs table
  print_func(self_index, neighbor, &dt);

  //Send to rest of network
  for(int i = 0; i < neighbor->NodesInNetwork; i++) {
    //Skip self, nodes that are not connected
    if(i == self_index || init_costs[i] == INFINITY) {
      continue;
    }

    //Specified output
    printf("At time t=%f, node %d sends packet to node %d with:", clocktime, self_index, i);

    //Make the packet
    struct RoutePacket* packet = malloc(sizeof(struct RoutePacket));
    packet->sourceid = self_index;
    packet->destid = i;

    //Find the min distance for each node
    for(int j = 0; j < MAX_NODES; j++) {
      int min = INFINITY;
      for(int k = 0; k < MAX_NODES; k++) {
        int temp_cost = dt.costs[j][k];
        if(temp_cost < min) {
          min = temp_cost;
        }
      }
      printf(" %d", min);
      packet->mincost[j] = min;
    }
    printf("\n");

    //send packet
    toLayer2(*packet);
  }

  //Specified output
  printf("At time t=%f, rtinit%d() called.\n", clocktime, self_index);
}


void rtupdate0( struct RoutePacket *rcvdpkt ) {

}


/////////////////////////////////////////////////////////////////////
//  printdt
//  This routine is being supplied to you.  It is the same code in
//  each node and is tailored based on the input arguments.
//  Required arguments:
//  MyNodeNumber:  This routine assumes that you know your node
//                 number and supply it when making this call.
//  struct NeighborCosts *neighbor:  A pointer to the structure
//                 that's supplied via a call to getNeighborCosts().
//                 It tells this print routine the configuration
//                 of nodes surrounding the node we're working on.
//  struct distance_table *dtptr: This is the running record of the
//                 current costs as seen by this node.  It is
//                 constantly updated as the node gets new
//                 messages from other nodes.
/////////////////////////////////////////////////////////////////////
void printdt0( int MyNodeNumber, struct NeighborCosts *neighbor,
		struct distance_table *dtptr ) {
    int       i, j;
    int       TotalNodes = neighbor->NodesInNetwork;     // Total nodes in network
    int       NumberOfNeighbors = 0;                     // How many neighbors
    int       Neighbors[MAX_NODES];                      // Who are the neighbors

    // Determine our neighbors
    for ( i = 0; i < TotalNodes; i++ )  {
        if (( neighbor->NodeCosts[i] != INFINITY ) && i != MyNodeNumber )  {
            Neighbors[NumberOfNeighbors] = i;
            NumberOfNeighbors++;
        }
    }
    // Print the header
    printf("                via     \n");
    printf("   D%d |", MyNodeNumber );
    for ( i = 0; i < NumberOfNeighbors; i++ )
        printf("     %d", Neighbors[i]);
    printf("\n");
    printf("  ----|-------------------------------\n");

    // For each node, print the cost by travelling thru each of our neighbors
    for ( i = 0; i < TotalNodes; i++ )   {
        if ( i != MyNodeNumber )  {
            printf("dest %d|", i );
            for ( j = 0; j < NumberOfNeighbors; j++ )  {
                    printf( "  %4d", dtptr->costs[i][Neighbors[j]] );
            }
            printf("\n");
        }
    }
    printf("\n");
}    // End of printdt0
