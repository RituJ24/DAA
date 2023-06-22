#include<iostream>
#define NODE 4
using namespace std;

int graph[NODE][NODE] = {
   {0, 1, 1, 0},
   {1, 0, 1, 0},
   {1, 1, 0, 1},
   {0, 0, 1, 0}
};

void graphColoring() {
   int color[NODE];
   color[0] = 0; //first color to first node
   bool colorUsed[NODE]; //check if color used

   for(int i = 1; i<NODE; i++)
      color[i] = -1; //intially no colors assigned to any node

   for(int i = 0; i<NODE; i++)
      colorUsed[i] = false; //no color used intially
         
   for(int u = 1; u<NODE; u++) {
      for(int v = 0; v<NODE; v++) {
         if(graph[u][v]){
            if(color[v] != -1) //color used make it unavailable    
               colorUsed[color[v]] = true;
         }
     }

     int col;//for color
     for(col = 0; col<NODE; col++)
        if(!colorUsed[col])//find color which is not used
           break;
         
     color[u] = col;//assign the found color from the list
         
     for(int v = 0; v<NODE; v++) {//iterate to next node; set color availibility to false; re visit palette
        if(graph[u][v]) {
           if(color[v] != -1)
              colorUsed[color[v]] = false;
        }
     }  
  }
   
  for(int u = 0; u<NODE; u++)
     cout <<"Vertex " << u << " Assigned with Color : " <<color[u] <<endl;
}                                                                                                                                                                                                                                                                                                              

main() {
   graphColoring();
   return 0;
}
