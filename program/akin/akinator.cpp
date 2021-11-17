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

static int game_recursion (Tree* tree, char* answer);

static int answer_library_add (Tree* tree, const int side, char* answer);

static int make_tree_recursion (Tree* tree, Onegin* line, int* ammount, const int amount_str);

static int definition_recurion (Tree* tree, Stack* stack, const char* name, int* ammount);

int game (Tree* tree)
{
    printf ("HELLO, LET'S PLAY\n");
    char answer [5] = {};
    game_recursion (tree, answer);
    printf ("I WISH THAT GAME WAS INTERESTING\n");
    return 0;
}

static int game_recursion (Tree* tree, char* answer)
{
    printf ("it's %s ?\n", tree->data);
    scanf ("%s", answer);
    if (*answer == 'y')
    {
        if (tree->left_ptr != NULL)
        {
            game_recursion (tree->left_ptr, answer);
        }
        else
        {
            answer_library_add (tree, LEFT, answer);
        }
        return 0;
    }
    if (*answer == 'n')
    {
        if (tree->right_ptr != NULL)
        {
            game_recursion (tree->right_ptr, answer);
        }
        else
        {
            answer_library_add (tree, RIGHT, answer);
        }
        return 0;
    }

    printf ("Please repeat your answer\n");
    game_recursion (tree, answer);

    return 0;
}

static int answer_library_add (Tree* tree, const int side, char* answer)
{
    /*if (side == RIGHT)
    {
        printf ("Your answer is %s\n", tree->right_ptr);
    }
    if (side == LEFT)
    {
        printf ("Your answer is %s\n", tree->left_ptr);
    }
    scanf ("%s", answer);*/

    if (*answer == 'y')
    {
        printf ("YES! I'M SO COOL\n");
    }
    else
    {
        printf ("OK! I DON'T KNOW THIS\n");
        printf ("WHAT IS YOUR WORD ?\n");
        scanf ("%s", answer);

        char question [15] = {};
        char save_name [NAME_LENGTH] = {0};
        strcpy(save_name, tree->data);

        printf ("IN WHAT DIFFERENCE ?\n");
        scanf ("%s", question);

        /*if (strncmp (question, "NO", 2) == 0)
        {
            tree_push (tree, LEFT, save_name);
            tree_push (tree, RIGHT, answer);
            tree_push (tree, IN, question + 3);
        }
        else
        {
            tree_push (tree, RIGHT, save_name);
            tree_push (tree, LEFT, answer);
            tree_push (tree, IN, question);
        }*/

        tree_push (tree, RIGHT, save_name);
        tree_push (tree, LEFT, answer);
        tree_push (tree, IN, question);
    }
    return 0;
}

int make_tree_from_library (Tree* tree)
{
    CHECK_ERROR_(tree, "NULL ADRESS", -1);

    int amount_str = 0; 
    char* buffer = copy_in_buffer_from_file (&amount_str); 
    Onegin* line = (Onegin*) calloc (amount_str, sizeof (Onegin));
    CHECK_ERROR_(line, "NULL ADRESS (Not Enough Memory)", -1);
    make_array_adress (buffer, amount_str, line);

    char name[NAME_LENGTH] = {0};
    sscanf (line[1].adress, "%s", name);
    tree_push (tree, IN, name);
    int ammount = 2;
    
    make_tree_recursion (tree, line, &ammount, amount_str);
    
    return 0;
}

#define _pars_tree_def_(arg, side)                                              \
        do{                                                                     \
            if ((*(line[*ammount].adress) == '{') &&                            \
                (*(line[1 + *ammount].adress) != '}'))                          \
            {                                                                   \
                char name[NAME_LENGTH] = {0};                                   \
                sscanf (line[*ammount + 1].adress, "%s\n", name);               \
                *ammount = *ammount + 2;                                        \
                tree_push (tree, side, name);                                   \
                make_tree_recursion (tree->arg, line, ammount, amount_str);     \
            }                                                                   \
            else                                                                \
            {                                                                   \
                *ammount = *ammount + 2;                                        \
            }                                                                   \
        }while(0)

static int make_tree_recursion (Tree* tree, Onegin* line, int* ammount, const int amount_str)
{   
    for (; *ammount < amount_str; ammount++)
    {
        if (*(line[*ammount].adress) == '}')
        {
            *ammount = *ammount + 1;
            return 0;
        }

        _pars_tree_def_(left_ptr, LEFT);

        _pars_tree_def_(right_ptr, RIGHT);

        if (*(line[*ammount].adress) == '}')
        {
            *ammount = *ammount + 1;
        }
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

int definition_tree_elem (Tree* tree, const char* name)
{

    CHECK_ERROR_(tree, "NULL ADRESS", -1);

    Stack st = {};
    stack_ctor (&st, BASIC_SIZE);

    st.data[0] = tree->data;

    int i = 0;

    definition_recurion (tree, &st, name, &i);
    
    //stack_dump (&st, __FILE__, __func__, __LINE__);

    stack_dtor (&st);

    return 0;
}

static int definition_recurion (Tree* tree, Stack* stack, const char* name, int* i)
{
    int length = strlen (name);
    if (tree->left_ptr != NULL)
    {
        stack->data[*i] = tree->data;
        *i = *i + 1;
        if (definition_recurion (tree->left_ptr, stack, name, i) == 1)
        {
            return 1;
        }
    }

    if (tree->right_ptr != NULL)
    {
        stack->data[*i] = tree->data;
        *i = *i + 1;
        if (definition_recurion (tree->right_ptr, stack, name, i) == 1)
        {
            return 1;
        }
    }

    stack->data[*i] = tree->data;
    *i = *i + 1;
    if (strncmp (tree->data, name, length) == 0)
    {
        for (int k = 0; k < *i - 1; k++)
        {
            printf ("%s ", stack->data[k]);
        }
        return 1;
    }
    return 0;
}

#undef CHECK_ERROR_

#undef $