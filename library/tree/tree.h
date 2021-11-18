#ifndef TREEHEADER
#define TREEHEADER

#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <string.h> 

struct Tree
{
    char* data;
    Tree* left_ptr;
    Tree* right_ptr;
};

enum Orientation
{
    LEFT,
    RIGHT,
    IN
};

const int NAME_LENGTH = 16;

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