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

enum ANSWER_NUM
{
    FIRST,
    SECOND
};

const int SIZE_ANSWER = 25;

int ctr_array_answers_game (char*** game_answers);

int dtor_array_answers_game (char*** game_answers);

int game (Tree* tree_node, char** game_answers);
char *copy_in_buffer_from_file (int* amount_str);

char* make_tree_from_library (Tree* tree_node);

int definition_tree_elem (Tree* tree_node, const char* name);

int difference_definition (Tree* tree_node, const char* first_name, const char* sec_name);


#endif
