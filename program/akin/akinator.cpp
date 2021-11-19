#include "akinator.h"

#define CHECK_ERROR_(name, type_error, ret)                                             \
        do{                                                                             \
            if ((name) == NULL)                                                         \
            {                                                                           \
                printf ("\nERROR in function : %s \n"                                   \
                        "%s have %s on line %d\n", __func__,                            \
                        #name, type_error, __LINE__);                                   \
                return ret;                                                             \
            }                                                                           \
        } while (0)

#define $ printf("\t\t\t---ON LINE %d IN FUNCTION %s---\n", __LINE__, __func__);

static int game_recursion (Tree* tree_node, char** game_answers);

static int answer_tree_add (Tree* tree_node, char** game_answers);

static int make_tree_recursion (Tree* tree_node, Onegin* line, int* ammount, const int amount_str);

static int definition_recurion (Tree* tree_node, Stack* stack, const char* name);

static int min (const int first_size, const int sec_size);

static void print_def_node_tree (Stack* st, int* ammount);

static int copy_string (char* str);

static void clear_stdin (void);


int ctr_array_answers_game (char*** game_answers)
{
    *game_answers = (char**) calloc (2, sizeof (char*));
    CHECK_ERROR_(game_answers, "NULL ADRES (HAVEN'T MEMORY)", -1);

    (*game_answers)[FIRST] = (char*)calloc (SIZE_ANSWER, sizeof (char));
    CHECK_ERROR_(game_answers[FIRST], "NULL ADRES (HAVEN'T MEMORY)", -1);

    (*game_answers)[SECOND] = (char*)calloc(SIZE_ANSWER, sizeof (char));
    CHECK_ERROR_(game_answers[SECOND], "NULL ADRES (HAVEN'T MEMORY)", -1);

    return 0;
}

int dtor_array_answers_game (char*** game_answers)
{
    free ((*game_answers)[FIRST]);
    free ((*game_answers)[SECOND]);
    free (*game_answers);

    return 0;
}


int game (Tree* tree_node, char** game_answers)
{
    printf ("\nHELLO, LET'S PLAY\n");
    
    game_recursion (tree_node, game_answers);

    printf ("I WISH THAT GAME WAS INTERESTING\n\n");
    return 0;
}

static int game_recursion (Tree* tree_node, char** game_answers)
{
    printf ("it's %s ?\n", tree_node->data);
    scanf ("%s", game_answers[FIRST]);
    if (*(game_answers[FIRST]) == 'y')
    {
        if (tree_node->left_ptr != NULL)
        {
            game_recursion (tree_node->left_ptr, game_answers);
        }
        else
        {
            answer_tree_add (tree_node, game_answers);
        }
        return 0;
    }
    if (*(game_answers[FIRST]) == 'n')
    {
        if (tree_node->right_ptr != NULL)
        {
            game_recursion (tree_node->right_ptr, game_answers);
        }
        else
        {
            answer_tree_add (tree_node, game_answers);
        }
        return 0;
    }

    printf ("Please repeat your answer\n");
    game_recursion (tree_node, game_answers);

    return 0;
}

static int answer_tree_add (Tree* tree_node, char** game_answers)
{
    if (*(game_answers[FIRST]) == 'y')
    {
        printf ("YES! I'M SO COOL\n");
    }
    else
    {
        printf ("OK! I DON'T KNOW THIS\n");
        printf ("WHAT IS YOUR WORD ?\n");
        //scanf ("%s", game_answers[FIRST]);
        clear_stdin ();
        copy_string (game_answers[FIRST]);

        char* save_name = tree_node->data;

        printf ("IN WHAT DIFFERENCE ?\n");
        //scanf ("%s", game_answers[SECOND]);
        copy_string (game_answers[SECOND]);

        tree_push (tree_node, RIGHT, save_name);
        tree_push (tree_node, LEFT, game_answers[FIRST]);
        tree_push (tree_node, IN, game_answers[SECOND]);
    }
    return 0;
}

static int copy_string (char* str)
{   
    int i = 0;

    for (int cur_symbol = 0; (((cur_symbol = getchar ()) != EOF) && (cur_symbol != '\n')); i++)
    {
        str[i] = cur_symbol;
    }
    
    return 0;
}

static void clear_stdin (void)
{
    char c = 0;
    while (((c = getchar()) != EOF) && (c != '\n'));

}

char* make_tree_from_library (Tree* tree_node)
{
    CHECK_ERROR_(tree_node, "NULL ADRESS", NULL);

    int amount_str = 0; 

    char* buffer = copy_in_buffer_from_file (&amount_str); 

    Onegin* line = (Onegin*) calloc (amount_str, sizeof (Onegin));
    CHECK_ERROR_(line, "NULL ADRESS (Not Enough Memory)", NULL);

    make_array_adress (buffer, amount_str, line);

    tree_push (tree_node, IN, line[1].adress);
    int ammount = 2;
    
    make_tree_recursion (tree_node, line, &ammount, amount_str);

    /*for (int i = 0; i < amount_str; i++)
    {
        printf ("%s\n", line[i].adress);
    }
    printf ("%d", amount_str);*/
    
    return buffer;
}

#define _pars_tree_def_(arg, side)                                              \
        do{                                                                     \
            if ((*(line[*ammount].adress) == '{') &&                            \
                (*(line[1 + *ammount].adress) != '}'))                          \
            {                                                                   \
                tree_push (tree_node, side, line[*ammount + 1].adress);         \
                *ammount = *ammount + 2;                                        \
                make_tree_recursion (tree_node->arg, line, ammount, amount_str);\
            }                                                                   \
            else                                                                \
            {                                                                   \
                *ammount = *ammount + 2;                                        \
            }                                                                   \
        }while(0)

static int make_tree_recursion (Tree* tree_node, Onegin* line, int* ammount, const int amount_str)
{   
    while (*ammount < amount_str)
    {
        if (*(line[*ammount].adress) == '}')
        {
            *ammount = *ammount + 1;
            return 0;
        }

        _pars_tree_def_(left_ptr, LEFT);

        _pars_tree_def_(right_ptr, RIGHT);

    }
    return 0;
}
#undef _pars_tree_def_

char *copy_in_buffer_from_file (int* amount_str)
{
    CHECK_ERROR_(amount_str, "NULL_ADRESS", NULL);

    char* buffer = NULL; 
   
    FILE* input_file = fopen ("../../output/tree_dump_text.txt", "r");
    CHECK_ERROR_(input_file, "NOT OPENED", NULL);

    buffer = remove_trash_and_copy_in_buffer (amount_str, input_file);

    if (ferror(input_file))
    {
        printf ("ERROR in function : %s \n"
                "reading file falled\n", __func__);
        return NULL;
    }
    fclose (input_file);

    return buffer;
}

int definition_tree_elem (Tree* tree_node, const char* name)
{
    CHECK_ERROR_(tree_node, "NULL ADRESS", -1);
    CHECK_ERROR_(name, "NULL ADRESS", -1);

    Stack st = {};
    stack_ctor (&st, BASIC_SIZE);

    printf ("%s IS:\n", name);

    if (definition_recurion (tree_node, &st, name) != 1)
    {
        printf ("WORD DIDN FINDED\n");
    }

    stack_dtor (&st);

    return 0;
}


#define _def_rec_(arg, side)                                                        \
        do{                                                                         \
            if (tree_node->arg != NULL)                                             \
            {                                                                       \
                if (side == RIGHT)                                                  \
                {                                                                   \
                    stack_push (stack, NULL);                                       \
                }                                                                   \
                if (definition_recurion (tree_node->arg, stack, name) == 1)         \
                {                                                                   \
                    return 1;                                                       \
                }                                                                   \
                else                                                                \
                {                                                                   \
                    char* trash = NULL;                                             \
                    stack_pop (stack, &trash);                                      \
                    if (side == RIGHT)                                              \
                    {                                                               \
                        stack_pop (stack, &trash);                                  \
                    }                                                               \
                }                                                                   \
            }                                                                       \
        }while (0)


static int definition_recurion (Tree* tree_node, Stack* stack, const char* name)
{
    int length = strlen (name);

    stack_push(stack, tree_node->data);

    _def_rec_(left_ptr, LEFT);

    _def_rec_(right_ptr, RIGHT);

    if (strncmp (tree_node->data, name, length) == 0)
    {
        for (int ammount = 0 ; ammount < stack->size - 1; ammount++)
        {
            print_def_node_tree (stack, &ammount);
        }
        return 1;
    }
    return 0;
}


int difference_definition (Tree* tree_node, const char* first_name, const char* sec_name)
{
    CHECK_ERROR_(tree_node, "NULL ADRESS", -1);
    CHECK_ERROR_(first_name, "NULL ADRESS", -1);

    Stack st_first = {};
    stack_ctor (&st_first, BASIC_SIZE);

    Stack st_sec = {};
    stack_ctor (&st_sec, BASIC_SIZE);

    printf ("%s IS:\n", first_name);

    if (definition_recurion (tree_node, &st_first, first_name) != 1)
    {
        printf ("\nFIRST WORD DIDNT FINDED\n");
        return -1;
    }

    printf ("\n\n%s IS:\n", sec_name);

    if (definition_recurion (tree_node, &st_sec, sec_name) != 1)
    {
        printf ("\nSECOND WORD DIDNT FINDED\n");
        return -1;
    }

    int limit = min (st_first.size, st_sec.size);
    int ammount = 0;


    printf ("\n\n%s and %s ARE SIMILAR IN: \n", first_name, sec_name);

    for (; ammount < limit - 1; ammount = ammount + 1)
    {
        if (st_first.data[ammount] == st_sec.data[ammount])
        {
            if (st_first.data[ammount + 1] == st_sec.data[ammount + 1])
            {
                print_def_node_tree (&st_sec, &ammount);
            }
        }
        else
        {
            break;
        }
    }

    stack_dtor (&st_first);
    stack_dtor (&st_sec);

    return 0;

}

static int min (const int first_size, const int sec_size)
{
    if (first_size <= sec_size)
    {
        return first_size;
    }
    else
    {
        return sec_size;
    }
}

static void print_def_node_tree (Stack* st, int* ammount)
{
    bool no_stat = 0;
    if (st->data[*ammount + 1] == NULL)
    {
        no_stat = 1;
        printf ("NO ");
    }
    printf ("%s\n", st->data[*ammount]);
    if (no_stat == 1)
    {
        *ammount = *ammount + 1;
    }
    return;
}

#undef _def_rec_

#undef CHECK_ERROR_

#undef $