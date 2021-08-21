#include "Node.h"
/* this function creates an index corresponding
to the every given key */
int hashcode(int key, int maximumCapacity)
{
    return (key % maximumCapacity);
}

void add(int key, int value, int maximumCapacity, Node** indexTree, int* size)
{
    int index =  hashcode(key, maximumCapacity);

    Node* new_element = (Node*)malloc(sizeof(Node));
    new_element->key = key;
    new_element->value = value;
    new_element->left = NULL;
    new_element->right = NULL;

    //If the tree hasn't been initialized in the given index
    if (indexTree[index] == NULL)
    {
        indexTree[index] = new_element;
        (*size)++;
    }
    else
    {
        Node* temporary = find(indexTree[index], key);
        //If the key is not found in the tree
        if (temporary == NULL)
        {
            indexTree[index] = insert_element(indexTree[index], new_element);
            (*size)++;
        }
        //If it is found, then the value gets updated
        else
        {
            temporary->value = value;
        }
    }
}

/*
* this function finds the given key in the Binary Tree
* returns the node containing the key
* returns NULL in case key is not present
*/
Node* find(Node *tree, int key)
{
    if (tree == NULL)
        return NULL;
    if (tree->key == key)
        return tree;
    if (key < tree->key)
        return find(tree->left, key);
    else
        return find(tree->right, key);
}

/* this function inserts the newly created node
in the existing Binary Tree.*/
Node* insert_element(Node *tree, Node *new_element)
{
    if (tree ==  NULL)
    {
        tree = (Node*)malloc(sizeof(Node));
        tree = new_element;
    }

    else if(new_element->key < tree->key)
    {
        tree->left = insert_element(tree->left, new_element);
    }
    else if(new_element->key > tree->key)
    {
        tree->right = insert_element(tree->right, new_element);
    }

    return tree;
}

/* displays the content of hash Tree */
void display(Node** indexTree, int maximumCapacity)
{
    int i = 0;
    Node* aux = NULL;
    for (i=0 ; i<maximumCapacity ; i++)
    {
        aux = indexTree[i];
        if (aux == NULL)
            printf("tree[%d] has no keys\n", i);
        else
        {
            printf("the elements in tree[%d] are:\n", i);
            display_tree(aux);
        }
    }
}

/* displays content of binary tree of
particular index */
void display_tree(Node *tree)
{
    if (tree == NULL)
        return;

    printf("%d with %d\n", tree->key, tree->value);
    display_tree(tree->left);
    display_tree(tree->right);

    printf("\n");
}

/* for initializing the hash Tree */
void init(Node** indexTree, int maximumCapacity)
{
    int i = 0;
    for (i=0 ; i<maximumCapacity ; i++)
    {
        indexTree[i] = NULL;
    }
}

/* to del a key from hash Tree */
void del(int key, Node** indexTree, int maximumCapacity, int* size)
{
    int index = hashcode(key, maximumCapacity);
    Node* treeAux = indexTree[index];
    if (treeAux == NULL)
        printf("key %d not present\n", key);
    
    else
    {
        Node* temp = find(treeAux, key);
        if (temp == NULL)
            printf("key %d not present\n", key);
        else
        {
            treeAux = remove_element(treeAux, key, size);
            printf("%d has been removed from hash tree", key);
        }
    }
}

Node* remove_element(Node *tree, int key, int* size)
{
    if (tree == NULL)
        return NULL;
    else
    {
        if (key < tree->key)
            tree->left = remove_element(tree->left, key, size);
        else if (key > tree->key) 
            tree->right = remove_element(tree->right, key, size);
        else
        {
            if (tree->left == NULL && tree->right == NULL)
            {
                (*size)--;
                free(tree);
                tree = NULL;
            }
            else if (tree->left == NULL)
            {
                (*size)--;
                Node* temp = tree;
                tree = tree->right;
                free(temp);
            }
            else if (tree->right == NULL)
            {
                (*size)--;
                Node* temp = tree;
                tree = tree->left;
                free(temp);
            }
            else
            {
                Node *temp = tree->left;
                while (temp->right != NULL)
                    temp = temp->right;
                tree->key = temp->key;
                tree->value = temp->value;
                temp->key = key;
                tree->left = remove_element (tree->left, key, size);
            }
        }
        
        return tree;
    }
}

void freeTree(Node* tree)
{
    if (tree != NULL) 
    {
      freeTree (tree->left);
      freeTree (tree->right);
      free(tree);
   }
}
void freeArrayTree(Node** indexTree, int maximumCapacity)
{
    int i = 0;
    for (i=0 ; i<maximumCapacity ; i++)
    {
        Node* aux = indexTree[i];
        freeTree(aux);
    }
    free(indexTree);
}