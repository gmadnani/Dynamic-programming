/*
 * Problem 2 in Assignment 2
 * COMP20007 Design of Algorithms
 * Semester 1 2019
 *
 * Written by: [ GIRISH MOHAN MADNANI ]
 * Student ID: [934130]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INT_MAX 2147483647
#define MAX 100005

/* --- DO NOT CHANGE THE CODE BELOW THIS LINE --- */

void problem_2_a();
void problem_2_b();
void print_usage_and_exit(char **argv);

int main(int argc, char **argv) {
  if (argc != 2) {
    print_usage_and_exit(argv);
  }

  /* If the argument provided is "a" then run problem_2_a(),
   * run problem_2_b() for "b", and fail otherwise. */
  if (strcmp(argv[1], "a") == 0) {
    problem_2_a();
  } else if (strcmp(argv[1], "b") == 0) {
    problem_2_b();
  } else {
    print_usage_and_exit(argv);
  }

  return 0;
}

/* Print the usage information and exit the program. */
void print_usage_and_exit(char **argv) {
  fprintf(stderr, "usage: %s [ab]\n", argv[0]);
  exit(EXIT_FAILURE);
}

/* --- DO NOT CHANGE THE CODE ABOVE THIS LINE --- */

struct AdjListNode {
    int dest;
    struct AdjListNode* next;
};

struct AdjList {
    struct AdjListNode *head;
};

struct Graph {
    int V;
    struct AdjList* array;
};

struct AdjListNode* newAdjListNode(int dest) {
    struct AdjListNode* newNode =
    (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int V) {
    struct Graph* graph =
    (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;

    graph->array =
    (struct AdjList*) malloc(V * sizeof(struct AdjList));
    int i;
    for (i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}


void recur(int lc[],int x,int c) {
    if(x==0)
    {
        printf("%d\n0\n",c);
        return;
    }
    recur(lc,lc[x],c+1);
    printf("%d\n",x);
}


/* TODO: Implement your solution to Problem 2.a. in this function. */
void problem_2_a() {
  int n;
  scanf("%d",&n);
  int size[n];
  int mat[n][n];

  for(int i=0;i<n;i++)
      for(int j=0;j<n;j++)
          mat[i][j]=-1;

  struct Graph* graph = createGraph(n);
  for(int i=0;i<n;i++)
  {
      scanf("%d",&size[i]);
      for(int j=0;j<size[i];j++)
      {
          int v,w;
          scanf("%d %d",&v,&w);
          addEdge(graph, i, v);
          mat[i][v]=w;
      }
  }

  int dist[n];
  int lc[n];
  for(int i=0;i<n;i++)
      lc[i]=0;
  for(int i=0;i<n;i++)
      dist[i]=INT_MAX;
  dist[0]=0;


  for(int j=0;j<n;j++)
  {
      if(size[j]!=0)
      if (dist[j] != INT_MAX)
      {
          struct AdjListNode* pCrawl = graph->array[j].head;
          while (pCrawl)
          {
              if(mat[j][pCrawl->dest]!=-1)
              {
                  int v=pCrawl->dest;
                  if (dist[v] > dist[j] + mat[j][v])
                  {
                      dist[v] = dist[j] + mat[j][v] ;
                      lc[v]=j;
                  }
              }
              pCrawl = pCrawl->next;
          }
      }
  }

  if(dist[n-1]==INT_MAX)
      printf("No Path\n");
  else
  {
      printf("%d\n",dist[n-1]);
      recur(lc,n-1,0);
  }
  return ;
}


/* TODO: Implement your solution to Problem 2.b. in this function. */
void problem_2_b() {
  int n,k;
  scanf("%d %d",&n,&k);
  int size[n];
  int mat[n][n];

  for(int i=0;i<n;i++)
      for(int j=0;j<n;j++)
          mat[i][j]=-1;

  struct Graph* graph = createGraph(n);
  for(int i=0;i<n;i++)
  {
      scanf("%d",&size[i]);
      for(int j=0;j<size[i];j++)
      {
          int v,w;
          scanf("%d %d",&v,&w);
          addEdge(graph, i, v);
          mat[i][v]=w;
      }
  }

  int dp[k+1][n];
  int prev[k+1][n];

  for(int i=0;i<k+1;i++)
      for(int j=0;j<n;j++)
          dp[i][j]=INT_MAX;

  for(int i=0;i<k+1;i++)
      for(int j=0;j<n;j++)
          prev[i][j]=-1;
  prev[0][0]=0;

  dp[0][0]=0;

  for(int i=0;i<k;i++)
  {
      for(int j=0;j<n;j++)
      {
          if(dp[i][j]!=INT_MAX)
          {
              struct AdjListNode* pCrawl = graph->array[j].head;
              while (pCrawl)
              {
                  if(mat[j][pCrawl->dest]!=-1 && (dp[i+1][pCrawl->dest]> dp[i][j]+mat[j][pCrawl->dest]))
                  {
                      dp[i+1][pCrawl->dest]=dp[i][j]+mat[j][pCrawl->dest];
                      prev[i+1][pCrawl->dest] = j;
                  }
                  pCrawl = pCrawl->next;
              }
          }
      }
  }
  int min=dp[k][n-1];
  int ans=k;
  for(int i=0;i<k;i++)
  {
      if(dp[i][n-1]<min)
      {
          min=dp[i][n-1];
          ans=i;
      }
  }
  if(min==INT_MAX)
      printf("No Path\n");
  else
  {
      printf("%d\n",min);
      int path[MAX];
      int cnt=0;
      int plen=ans;
      int curVertex = n-1;
      printf("%d\n",plen);
      while(plen>=0)
      {
          path[cnt++]=curVertex;
          curVertex=prev[plen][curVertex];
          plen--;
      }
      for(int i=cnt-1;i>=0;i--)
          printf("%d\n",path[i]);
  }
  return;
}
