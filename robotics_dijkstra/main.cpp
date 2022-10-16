#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <vector>

using namespace std;

#define Max 50
#define file "text3.txt"
#define INFINITY 9999

void print(int arr[Max][Max], int n);
void dijkstra(int maze[Max][Max], int nodes,int startnode);

#define up (data[cur_place->i - 1][cur_place->j])
#define right (data[cur_place->i][cur_place->j + 1])
#define down (data[cur_place->i + 1][cur_place->j])
#define left (data[cur_place->i][cur_place->j - 1])


typedef struct Block { // A block contains information about a cell of the array
   int i;
   int j;
   char state;
} Block;

int main( ){
    bool flag = false;
    int d = 0; //Counter for steps
    int paths ; //How many available paths for player
    char c;
    Block *cur_place; //Points to the current place of the player
    Block exit_place;
    int arr[Max][Max]; //Adjacency matrix
    arr[0][0] = 0;
    int k=1;

    //Constants
    const char empty = '-';
    const char passed = 'X';
    const char player = '@';
    const char exit = '!';
    const char node = 'O';

    vector<Block*> cur;
    vector<Block*> points;
    Block *prev_point;
    int prev_it, cur_it;

    //Reads the file
    FILE *fp;
    int N=2;
    int M=0;
    fp = fopen(file, "r");

    c = fgetc(fp);
    while(c  != '\n'){
      if( c != ' ')
        M++;
      c = fgetc(fp);
    }

    while( !feof(fp) ){
      if(fgetc(fp) == '\n')
        N++;
    }
    rewind(fp);

    Block data[N+1][M+1];  //Our labyrinth

    for (int i=0; i<= N; i++) {

        for (int j=0; j<= M; j++){
            data[i][j].i = i;
            data[i][j].j = j;

            c = fgetc(fp);
            while( c == ' ')
                c = fgetc(fp);

            data[i][j].state=c;

            if( data[i][j].state == player)
                cur_place = &data[i][j];
        }
    }

    fclose(fp);

     points.push_back(cur_place);
     cur.push_back(cur_place);
     c = node;

   while( !cur.empty() ){
     char b;
     paths = 0;
     scanf("%c",&b);
     if( b == 'k')
        break;

     system("cls"); //Clear screen

     // MOVES THE PLAYER

     if( up.state == empty || up.state == exit){ //Go up
         d++;
         cur_place -> state = c;
         c = (up.state==exit)? exit : passed;
         cur_place = &up;
         cur_place -> state = player;
     }

     else if( right.state == empty || right.state == exit){ //Go right
         d++;
         cur_place -> state = c;
         c = (right.state==exit)? exit : passed;
         cur_place = &right;
         cur_place -> state = player;
     }
     else if( down.state == empty || down.state == exit){ //Go down
         d++;
         cur_place -> state = c;
         c = (down.state==exit)? exit : passed;
         cur_place = &down;
         cur_place -> state = player;

     }
     else if( left.state == empty || left.state == exit){ //Go left
         d++;
         cur_place -> state = c;
         c = (left.state==exit)? exit : passed;
         cur_place = &left;
         cur_place -> state = player;
     }

     //If player cannot move

     else if( c==passed ){ //If we are in dead end
        flag = true;
        cur_place -> state = passed;
        c = node;
        cur_place = cur.back();
        cur_place -> state = player;
        d = 0;
      }
      else if(paths == 0 && c == node){ //If we are on node
        cur_place -> state = node;
        cur.pop_back();
        if( !cur.empty() ){
           cur_place = cur.back();
           cur_place -> state = player;
        }
        d = 0;
     }

     //DOES THINGS WITH NODES

     //Counts how many paths are available

     if( up.state == empty || up.state == exit)
            paths++;
     if( right.state == empty || right.state == exit)
            paths++;
     if( down.state == empty || down.state == exit)
            paths++;
     if( left.state == empty || left.state == exit)
            paths++;

     if((paths > 1 || c == exit) && !flag){ //We create a node
            c = node;
            prev_point = cur.back();
            points.push_back(cur_place);
            cur.push_back(cur_place);
            for(int i = 0; i < points.size();i++){
                arr[i][points.size()-1] = 0;
                arr[points.size()-1][i] = 0;
            }
            for(int i=points.size()-1; i>=0; i--){
                  if(prev_point == points[i])
                    prev_it = i;
            }
            for(int i=points.size()-1; i>=0; i--){
                  if(cur_place == points[i])
                     cur_it = i;
            }
            arr[prev_it][cur_it] = d;
            arr[cur_it][prev_it] = d;

            k++;
            d = 0;
         }
      else if(flag){ //
        flag = false;
      }

      //If we find the current node, then we put d=1

      if( cur.back() == &up || cur.back() == &right || cur.back() == &down || cur.back() == &left){
          d=1;
      }

      if( up.state == node){
          for(int i=points.size()-1; i>=0; i--){
                  if( &up == points[i])
                    prev_it = i;
            }
            for(int i=points.size()-1; i>=0; i--){
                  if(cur.back() == points[i])
                     cur_it = i;
            }
            if( (arr[prev_it][cur_it] > d + 1 || arr[prev_it][cur_it] == 0) && &up != cur.back()){
                arr[prev_it][cur_it] = d + 1;
                arr[cur_it][prev_it] = d + 1;
            }
      }
      else if( right.state == node){
          for(int i=points.size()-1; i>=0; i--){
                  if( &right == points[i])
                    prev_it = i;
            }
            for(int i=points.size()-1; i>=0; i--){
                  if(cur.back() == points[i])
                     cur_it = i;
            }
            if( (arr[prev_it][cur_it] > d + 1 || arr[prev_it][cur_it] == 0) && &right != cur.back()){
                arr[prev_it][cur_it] = d + 1;
                arr[cur_it][prev_it] = d + 1;
            }
      }
      else if( down.state == node){
          for(int i=points.size()-1; i>=0; i--){
                  if( &down == points[i])
                    prev_it = i;
            }
            for(int i=points.size()-1; i>=0; i--){
                  if(cur.back() == points[i])
                     cur_it = i;
            }
            if( (arr[prev_it][cur_it] > d + 1 || arr[prev_it][cur_it] == 0) && &down != cur.back()){
                arr[prev_it][cur_it] = d + 1;
                arr[cur_it][prev_it] = d + 1;
            }
      }
      else if( left.state == node){
          for(int i=points.size()-1; i>=0; i--){
                  if( &left == points[i])
                    prev_it = i;
            }
            for(int i=points.size()-1; i>=0; i--){
                  if(cur.back() == points[i])
                     cur_it = i;
            }
            if( (arr[prev_it][cur_it] > d + 1 || arr[prev_it][cur_it] == 0) && &left != cur.back()){
                arr[prev_it][cur_it] = d + 1;
                arr[cur_it][prev_it] = d + 1;
            }
      }

     for (int i=0; i< N; i++) {
        for (int j=0; j< M; j++) {
            printf("%c ",data[i][j].state);
        }
        printf("\n");
     }
       printf("\n We have %d points\n", points.size());
       printf("\n Distance is %d\n", d);
     }

     print(arr,points.size());
     dijkstra(arr, points.size(),0);


     return 0;
}

void print(int arr[Max][Max], int n){
    for(int i = 0; i < n;i++){
        for(int j = 0; j < n;j++)
            printf("%d\t",arr[i][j]);
        printf("\n");
     }
}
void dijkstra(int maze[Max][Max], int nodes,int startnode)
{
    int cost[nodes][nodes],distance[nodes],pred[nodes];
    int visited[nodes],count,min_distance,next_node,i,j;

    for(i=0;i<nodes;i++)
    {
   	for(j=0;j<nodes;j++)
   	{
       	if(maze[i][j]==0)
   		{
           	cost[i][j]=INFINITY;
       	}
        	else
   		 {
        	cost[i][j]=maze[i][j];
        	}
      	}
    	}
    for(i=0;i<nodes;i++)
    {
   	 distance[i]=cost[startnode][i];
   	 pred[i]=startnode;
   	 visited[i]=0;
    }

    distance[startnode]=0;
    visited[startnode]=1;
    count=1;

    while(count<nodes-1)
    {
   	 min_distance=INFINITY;

   	 for(i=0;i<nodes;i++)
   	 {
   		 if(distance[i]<min_distance&&!visited[i])
   		 {
   			 min_distance=distance[i];
   			 next_node=i;
   		 }
   	 }

   	 visited[next_node]=1;

   	 for(i=0;i<nodes;i++)
   	 {
   		 if(!visited[i])
   		 {
   			 if(min_distance+cost[next_node][i]<distance[i])
   			 {
   				 distance[i]=min_distance+cost[next_node][i];
   				 pred[i]=next_node;
   			 }
   		 }

   	 }

   	 count++;
    }

    for(i=0;i<nodes;i++)
    {
   	 if(i!=startnode)
   	 {
   		 printf("\nDistance of node%d=%d",i,distance[i]);
   		 printf("\nPath=%d",i);

   		 j=i;
   		 do{
   			 j=pred[j];
   			 printf("<-%d",j);
   		 }while(j!=startnode);
   	 }
    }

}
