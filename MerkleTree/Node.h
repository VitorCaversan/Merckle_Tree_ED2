#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node
{
    int key;
    int value;
    struct node* left;
    struct node* right;
}Node;
/* this function creates an index corresponding
to the every given key */
int hashcode(int key, int maximumCapacity);


/* Used for adding a value together with a key int the Hash Tree*/
void add(int key, int value, int maximumCapacity, Node** indexTree, int* size);

/*
* this function finds the given key in the Binary Tree
* returns the node containing the key
* returns NULL in case key is not present
*/
Node* find(Node *tree, int key);

/* this function inserts the newly created node
in the existing Binary Tree */
Node* insert_element(Node *tree, Node *new_element);

/* displays the content of hash Tree */
void display(Node** indexTree, int maximumCapacity);

/* displays content of binary tree of
particular index */
void display_tree(Node *tree);

/* for initializing the hash Tree */
void init(Node** indexTree, int maximumCapacity);

/* deletes a key from hash Tree */
void del(int key, Node** indexTree, int maximumCapacity, int* size);

Node* remove_element(Node *tree, int key, int* size);

void freeTree(Node* tree);
void freeArrayTree(Node** indexTree, int maximumCapacity);