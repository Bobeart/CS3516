#include <stdio.h>
#include <stdlib.h>
#include "project3.h"

extern int TraceLevel;
extern float clocktime;

struct distance_table {
  int costs[MAX_NODES][MAX_NODES];
};
struct distance_table dt2;
struct NeighborCosts* neighbor2;

//Forward declaration
void printdt2(int MyNodeNumber, struct NeighborCosts *neighbor, struct distance_table *dtptr);
void sendUpdates(int self, int init_costs[], struct distance_table dt, struct NeighborCosts* neighbor);

//Initalize the table
void rtinit2() {
  //Convenience for copy/paste between nodeN.c files
  int self_index = 2;
  struct distance_table* dt = &dt2;
  struct NeighborCosts* neighbor = neighbor2;
  void (*print_func)(int, struct NeighborCosts*, struct distance_table*) = printdt2;

  //Initialize to INFINITY
  for(int i = 0; i < MAX_NODES; i++) {
    for(int j = 0; j < MAX_NODES; j++) {
      dt->costs[i][j] = INFINITY;
    }
  }

  //Get direct neighbor costs
  int init_costs[MAX_NODES];
  neighbor = getNeighborCosts(self_index);
  for(int i = 0; i < neighbor->NodesInNetwork; i++) {
    dt->costs[i][i] = neighbor->NodeCosts[i];
    init_costs[i] = neighbor->NodeCosts[i];
  }

  //Print the current costs table
  print_func(self_index, neighbor, dt);

  //Send to rest of network
  sendUpdates(self_index, init_costs, *dt, neighbor);

  //Specified output
  printf("At time t=%f, rtinit%d() called.\n", clocktime, self_index);
}

void rtupdate2( struct RoutePacket *rcvdpkt ) {
  //Convenience for copy/paste between nodeN.c files
  int self_index = 2;
  struct distance_table* dt = &dt2;
  struct NeighborCosts* neighbor = neighbor2;
  void (*print_func)(int, struct NeighborCosts*, struct distance_table*) = printdt2;

  int rcvd_sourceid = rcvdpkt->sourceid;
  int updates = NO;

  for(int i = 0; i < MAX_NODES; i++) {
    //Check for a new minimum
    int current_cost = dt->costs[rcvd_sourceid][rcvd_sourceid] + rcvdpkt->mincost[i];
    int old_cost = dt->costs[i][rcvd_sourceid];
    if(current_cost < old_cost) {
      dt->costs[i][rcvd_sourceid] = current_cost;
      updates = YES;
    }
  }

  if(updates == YES) {
    neighbor = getNeighborCosts(self_index);
    print_func(self_index, neighbor, dt);

    int init_costs[MAX_NODES];
    for(int i = 0; i < neighbor->NodesInNetwork; i++) {
      init_costs[i] = neighbor->NodeCosts[i];
    }
    sendUpdates(self_index, init_costs, *dt, neighbor);
  }

  //Specified output
  printf("At time t=%f, rtupdate%d() called.\n", clocktime, self_index);
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
void printdt2( int MyNodeNumber, struct NeighborCosts *neighbor,
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
}    // End of printdt2
