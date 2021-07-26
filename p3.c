/*
 * Problem 3 in Assignment 2
 * COMP20007 Design of Algorithms
 * Semester 1 2019
 *
 * Written by: [ GIRISH MOHAN MADNANI ]
 * Student ID: [934130]
 */


 #include<stdio.h>
 #include<stdlib.h>

 #define MAX 100000

/* --- DO NOT CHANGE THE CODE BELOW THIS LINE --- */

void problem_3();

int main(int argc, char **argv) {
  problem_3();
  return 0;
}

/* --- DO NOT CHANGE THE CODE ABOVE THIS LINE --- */

int ans[MAX],cnt[MAX],g[MAX],a[MAX],b[MAX];
int p=0,e=0,r=0;

struct node{
    int key;
    int count;
    struct node *left, *right;
};

// A utility function to create a new BST node
struct node *newNode(int item){
    struct node *temp =  (struct node *)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    temp->count = 1;
    return temp;
}

//inorder traversal
void printInorder(struct node* node){
    if (node == NULL)
        return;
    printInorder(node->left);
    g[e++]=node->key;
    printInorder(node->right);
}


//levelorder traversal

struct node** createQueue(int *, int *);
void enQueue(struct node **, int *, struct node *);
struct node *deQueue(struct node **, int *);

void printLevelOrder(struct node* root){
    int rear, front;
    struct node **queue = createQueue(&front, &rear);
    struct node *temp_node = root;
    if(root==NULL)return ;
    ans[p++]=root->key;
    while (temp_node)
    {
        int flag1=0,flag2=0;
        /*Enqueue left child */
        if (temp_node->left)
            enQueue(queue, &rear, temp_node->left);
        else
            flag1=1;

        /*Enqueue right child */
        if (temp_node->right)
            enQueue(queue, &rear, temp_node->right);
        else
            flag2=1;

        if(flag1 && flag2)
        {

        }
        else if(flag1==0 && flag1)
        {
            ans[p++]=temp_node->left->key;
            ans[p++]=-1;
        }
        else if(flag1 && flag2==0)
        {
            ans[p++]=-1;
            ans[p++]=temp_node->right->key;
        }
        else
        {
            ans[p++]=temp_node->left->key;
            ans[p++]=temp_node->right->key;
        }
        /*Dequeue node and make it temp_node*/
        temp_node = deQueue(queue, &front);
    }
}

/*UTILITY FUNCTIONS*/
struct node** createQueue(int *front, int *rear){
    struct node **queue =(struct node **)malloc(sizeof(struct node*)*MAX);
    *front = *rear = 0;
    return queue;
}

void enQueue(struct node **queue, int *rear, struct node *new_node){
    queue[*rear] = new_node;
    (*rear)++;
}

struct node *deQueue(struct node **queue, int *front){
    (*front)++;
    return queue[*front - 1];
}


/* A utility function to insert a new node with given key in BST */
struct node* insert(struct node* node, int key){
    /* If the tree is empty, return a new node */
    if (node == NULL) return newNode(key);

    // If key already exists in BST, icnrement count and return
    if (key == node->key)
    {
        (node->count)++;
        return node;
    }

    /* Otherwise, recur down the tree */
    if (key < node->key)
        node->left  = insert(node->left, key);
    else
        node->right = insert(node->right, key);

    /* return the (unchanged) node pointer */
    return node;
}

int maxDepth(struct node* node){
    if (node == NULL)
        return 0;
    else
    {
        int lDepth = maxDepth(node->left);
        int rDepth = maxDepth(node->right);
        if (lDepth > rDepth)
            return(lDepth + 1);
        else return(rDepth + 1);
    }
}
struct node* sortedArrayToBST(int arr[],
                              int start, int end){
    if (start > end)
        return NULL;

    int mid = (start + end)/2;
    struct node *root = newNode(arr[mid]);

    root->left = sortedArrayToBST(arr, start,
                                  mid - 1);

    root->right = sortedArrayToBST(arr, mid + 1, end);

    return root;
}

/* TODO: Implement your solution to Problem 3 in this function. */
void problem_3() {
  struct node *root = NULL;
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);

  root = insert(root, a[0]);
  for(int i=1;i<n;i++)
  {
      insert(root,a[i]);
  }
  int q=maxDepth(root);
  printInorder(root);
  printf("%d\n",e);
  printf("%d\n",q);
  struct node *y = sortedArrayToBST(g,0,e-1);
  printLevelOrder(y);
  printf("%d\n",p);
  for(int i=0;i<p;i++)
      printf("%d\n",ans[i]);
  printf("\n");
}
