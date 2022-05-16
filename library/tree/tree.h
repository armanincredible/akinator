#ifndef TREEHEADER
#define TREEHEADER

#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <string.h> 

typedef char* node_t;

struct Tree
{
    node_t data;
    Tree* left_ptr;
    Tree* right_ptr;
    int level;
};

enum Orientation
{
    LEFT,
    RIGHT,
    IN
};

const int NAME_LENGTH = 16;

int tree_verificate (Tree* tree_node);

int tree_ctor (Tree** tree_node);

int tree_dtor (Tree** tree_node);

int tree_push (Tree* tree_node, int side, char* name);

int tree_dump_visual (Tree* tree_node);

int tree_dump_text (Tree* tree_node);
/*
int tree_deletr (Tree* )
*/
//int tree_traverse ()


#endif