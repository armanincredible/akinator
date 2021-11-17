#ifndef AKINATORHEADER
#define AKINATORHEADER

#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <string.h> 
#include "..\..\library\tree\tree.h"
#include "..\..\library\onegin\dora.h"
#include "..\..\library\stack\stack.h"

int game (Tree* tree);
char *copy_in_buffer_from_file (int* amount_str);
int make_tree_from_library (Tree* tree);

int definition_tree_elem (Tree* tree, const char* name);

/*
static int make_tree_recursion (Tree* tree, Onegin* line, int* i, const int amount_str)
{
    for (; *i < amount_str; i++)
    {
        int left = 0;
        int right = 0;

        if (*(line[*i].adress) == '}')
        {
            *i = *i + 1;
            return 0;
        }

        if (*(line[*i].adress) == '{')
        {
            $
            char name[NAME_LENGTH] = {0};
            sscanf (line[*i + 1].adress, "%s\n", name);
            *i = *i + 2;
            tree_push (tree, LEFT, name);
            left = 1;
            if (left == 1)
            {
                left = 0;
                make_tree_recursion (tree->left_ptr, line, i, amount_str);
            }
        }

        /*if (*(line[*i].adress) == '}')
        {
            *i = *i + 1;
        }*/

        /*if (*(line[*i].adress) == '{')
        {
            $
            char name[NAME_LENGTH] = {0};
            sscanf (line[*i + 1].adress, "%s", name);
            *i = *i + 2;
            tree_push (tree, RIGHT, name);
            right = 1;
            if (right == 1)
            {
                right = 0;
                make_tree_recursion (tree->right_ptr, line, i, amount_str);
            }
        }

        if (*(line[*i].adress) == '}')
        {
            *i = *i + 1;
        }*/

        /*if (left == 1)
        {
            left = 0;
            make_tree_recursion (tree->left_ptr, line, i, amount_str);
        }

        if (right == 1)
        {
            right = 0;
            make_tree_recursion (tree->right_ptr, line, i, amount_str);
        }*/
    //}
    //return 0;
//}

#endif

/*if ((*(line[*i].adress) == '{') && (*(line[1 + *i].adress) != '}')) \*/