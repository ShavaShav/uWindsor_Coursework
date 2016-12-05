#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1 // 1 for debug prints, 0 for clean
#define FREECHK 0 // 1 to display printouts verifying memory freed

// structure of binary tree node
struct btree
{
    int val;
    struct btree *leftChild, *rightChild;
};
// define type as "node"
typedef struct btree node;

node* createNode(int val);
void insertNode(node **root, int val);
void preorderTraversal(node *root);
void postorderTraversal(node *root);
void inorderTraversal(node *root);
void freeTree(node **root);
// lab-specific functions
node* searchTree(node *root, int key);
node* findMin(node *root);
node* findMax(node *root);
node* findKthNode(node *root, int k);
node* findSucessor(node *root, int key);
node* findPredecessor(node *root, int key);
void inorderTraversal_Ranged(node *root, int low, int high);
// aux functions
int findHeight(node *root);
int findSize(node *root);
node* findParent(node *root, node *child);

int main()
{
	node *root = NULL;	// root of binary tree
    // root will be passed by reference using pointer to a pointer
    // when function changes the tree

	// populate BST with user input keys
	int numNodes;
	printf("Number of nodes to add: ");
	scanf("%d", &numNodes);

	while (numNodes > 0)
	{
		int nodeValue;
		printf("Enter val of node to insert: ");
		scanf("%d", &nodeValue);

		insertNode(&root, nodeValue);

		numNodes--;
	}

	if (DEBUG) puts("\nInorder Traversal:");    // DEBUG printout of BST
	inorderTraversal(root);

    // Testing max, min and median functions
	if (root == NULL)
        puts("Empty tree, no statistical information.");
    else
    {
        printf("\nSize: %d\tHeight: %d\n", findSize(root), findHeight(root));
        // Find max, min and median
        node *minNode = findMin(root);
        node *maxNode = findMax(root);

        int median = (findSize(root)/2)+1;
        node *medianNode = findKthNode(root, median);

        printf("\nMin: %d\tMax: %d\tMedian: %d\n",
               minNode->val, maxNode->val, medianNode->val);
    }

    char option = 'n';
	do {
        // Testing search function
        int key;
        printf("Enter a key value to search for: ");
        scanf("%d", &key);

        node *matchingNode = searchTree(root, key);

        if (matchingNode == NULL)
            puts("Key not found.");
        else
            printf("Found %d.\n", matchingNode->val);

        printf("Enter a node's key value to find it's Sucessor: ");
        scanf("%d", &key);
        node *sucessor = findSucessor(root, key);
        if (sucessor ==  NULL)
            puts("No node found");
        else
            printf("%d is the sucessor to %d.\n", sucessor->val, key);

        printf("Enter a node's key value to find it's Predecessor: ");
        scanf("%d", &key);
        node *predecessor = findPredecessor(root, key);
        if (predecessor ==  NULL)
            puts("No node found");
        else
            printf("%d is the predecessor to %d.\n", predecessor->val, key);

        int low, high;
        puts("Enter range of key values to print\nLow: ");
        scanf("%d", &low);
        puts("High: ");
        scanf("%d", &high);
        inorderTraversal_Ranged(root, low, high);

        while (getchar() != '\n');  // consume stray input chars

        puts("Keep Testing (y/n) ?");
        scanf("%c", &option);
	} while (option == 'y' || option == 'Y');

	freeTree(&root);
	return 0;
}

// returns the max of two integers
int max(int a, int b)
{
    if (b > a)
        return b;
    else
        return a;
}

// searches for key value in tree, returns the node
// returns matching node or NULL if not found
node* searchTree(node *root, int key)
{
    // if hit empty (sub)tree or matching key value
    if (root == NULL || root->val == key)
        return root;
    else if (key < root->val)
        searchTree(root->leftChild, key);
    else if (key > root->val)
        searchTree(root->rightChild,key);
}

// finds the minimum node by key value
node* findMin(node *root)
{
    // if left child exists, run recursively on it
    if (root->leftChild != NULL)
        findMin(root->leftChild);
    else
        return root; // return leaf if no left child
            // empty tree returns null as root is null
}

// finds the maximum node by key value
node* findMax(node *root)
{
    // if right child exists, run recursively on it
    if (root->rightChild != NULL)
        findMax(root->rightChild);
    else
        return root; // return leaf if no right child
            // empty tree returns null as root is null
}

// finds a node by it's Kth position in-order in O(log n) time
node* findKthNode(node *root, int k)
{
    if (root == NULL) return NULL;  // empty tree, no kth node

    // current position is size of left subtree + 1
    int currentPosition = findSize(root->leftChild) + 1;

    if (currentPosition == k)
        return root;    // currently at the kth element
    else if (currentPosition < k)
    {
        k = k - currentPosition;    // update k relative to currentPosition before
        findKthNode(root->rightChild, k);   // repeating function on right subtree
    }
    else if (currentPosition > k)
        findKthNode(root->leftChild, k); // repeat on left subtree, k stays the same
}

// finds the successor to given key value
node* findSucessor(node *root, int key)
{
    node* current = searchTree(root, key);
    if (current == NULL) return NULL;   // key not found

    node* parent = NULL;

    // successor is either min of right child or right parent of leftmost parent
    if (current->rightChild != NULL)
        return findMin(current->rightChild);
    else
    {
        parent = findParent(root, current);
        while (parent != NULL && parent->rightChild == current)
        {
            current = parent;
            parent = findParent(root, parent);
        }
    }
    return parent;
}

// finds predecessor of a given key value and root of tree
node* findPredecessor(node *root, int key)
{
    node* current = searchTree(root, key);
    if (current == NULL) return NULL;   // key not found

    node* parent = NULL;

    // predecessor is either max of left subtree or left parent of rightmost parent
    if (current->leftChild != NULL)
        return findMax(current->leftChild);
    else
    {
        parent = findParent(root, current);
        while (parent != NULL && parent->leftChild == current)
        {
            current = parent;
            parent = findParent(root, parent);
        }
    }
    return parent;
}

// finds parents of given child, given root of tree
node* findParent(node *root, node *child)
{
    // if hit parent
    if (root->leftChild == child || root->rightChild == child)
        return root;
    else if (root == child || root ==  NULL)
        return NULL;
    else if (child->val < root->val)
        findParent(root->leftChild, child);
    else if (child->val > root->val)
        findParent(root->rightChild, child);
}

// prints portion of tree between low and high inclusively
void inorderTraversal_Ranged(node *root, int low, int high)
{
    // empty subtree
	if (root == NULL)
        return;
	else
	{
		// Run recursively on left subtree
		inorderTraversal_Ranged(root->leftChild, low, high);
        if(root->val >= low && root->val <= high)
            printf("%d ", root->val); // print root's val if in range
        // Run recursivelky on right subtree
		inorderTraversal_Ranged(root->rightChild, low, high);
	}
}

// returns height of the tree (number of edges)
int findHeight(node *root)
{
    if (root == NULL)
        return -1;  // empty tree has a height of -1
    else    // recursively find heights of left and right subtrees, pick max and add 1
        return max(findHeight(root->leftChild), findHeight(root->rightChild)) + 1;
}

// returns the size of the tree (number of nodes)
int findSize(node *root)
{
    if (root == NULL)
        return 0;   // empty tree has 0 nodes
    else    // recursively find sizes of left and right subtrees (each level adding 1)
        return findSize(root->leftChild) + findSize(root->rightChild) + 1;
}

// creates a binary search tree node given value
node* createNode(int val)
{
	node *new = malloc(sizeof(node));
	new->val = val;
	new->leftChild = NULL;
	new->rightChild = NULL;

	return new;
}

// free a tree, given address of root
void freeTree(node **root)
{
	if (*root == NULL)
		return;	// empty subtree, return

	// populated tree, free subtree recursively from leaf to root
	freeTree(&(*root)->rightChild);	// recursively free right subtree
	freeTree(&(*root)->leftChild);	// recursively free left subtree

	if (FREECHK) printf("Freeing %d...\n", (*root)->val);

	free(*root);	// free leaf
}

// Inserts node into binary tree, given address of root node and new node
void insertNode(node **root, int val)
{
	if (*root == NULL) // empty root/subtree
	{
		*root = createNode(val);	// place node
	}
	else
	{
		// recursively add to appropriate branch
		// If smaller than root, insert using left child as root
		// If larger, insert node using right child as root
		if (val < (*root)->val)
			insertNode(&(*root)->leftChild, val);
		else if (val > (*root)->val)
			insertNode(&(*root)->rightChild, val);
		else
            return; // duplicate so just return
	}
}

// Displays node information in preorder
void preorderTraversal(node *root)
{
	// empty subtree
	if (root == NULL)
        return;
	else
	{
        printf("%d ", root->val); // print root's val

		// Run recursively on left subtree, then right subtree (pre-order)
		preorderTraversal(root->leftChild);

		preorderTraversal(root->rightChild);
	}
}

// Displays node information in preorder
void postorderTraversal(node *root)
{
	// empty subtree
	if (root == NULL)
        return;
	else
	{
		// Run recursively on left subtree, then right subtree (pre-order)
		postorderTraversal(root->leftChild);
        postorderTraversal(root->rightChild);
		printf("%d ", root->val); // print root's val
	}
}

// Displays node information in preorder
void inorderTraversal(node *root)
{
	// empty subtree
	if (root == NULL)
        return;
	else
	{
		// Run recursively on left subtree
		inorderTraversal(root->leftChild);
        printf("%d ", root->val); // print root's val
        // Run recursivelky on right subtree
		inorderTraversal(root->rightChild);
	}
}
