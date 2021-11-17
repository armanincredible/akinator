#include "tree.h"

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


static int write_tree_element_vis (Tree* tree, FILE* output_file);

static int write_tree_element_text (Tree* tree, FILE* output_file);

int tree_ctor (Tree** tree)
{
    *tree = (Tree*) calloc (1, sizeof (Tree));
    CHECK_ERROR_(*tree, "NULL ADRESS (NOT FREE MEMORY)", -1);

    (*tree)->data = (char*) calloc (NAME_LENGTH, sizeof(char));
    CHECK_ERROR_((*tree)->data, "NULL ADRESS (NOT FREE MEMORY)", -1);

    (*tree)->left_ptr =  NULL;
    (*tree)->right_ptr = NULL;

    return 0;
}

#define _tree_dtor_elem_(name)                                      \
        do {                                                        \
            if ((*tree)->name != NULL)                              \
            {                                                       \
                tree_dtor (&((*tree)->name));                       \
            }                                                       \
            (*tree)->name = NULL;                                   \
        }while (0)

int tree_dtor (Tree** tree)
{
    CHECK_ERROR_(*tree, "NULL ADRESS", -1);

    memset ((*tree)->data, 0, NAME_LENGTH);

    _tree_dtor_elem_(left_ptr);

    _tree_dtor_elem_(right_ptr);

    free (*tree);
    free ((*tree)->data);

    return 0;
}

#undef _tree_dtor_elem_

int tree_push (Tree* tree, int side, char* name)
{
    if (side == IN)
    {
        CHECK_ERROR_(tree, "NULL ADRESS", -1);
        strncpy (tree->data, name, sizeof (name));
    }

    if (side == LEFT)
    {
        tree_ctor (&(tree->left_ptr));
        strncpy (tree->left_ptr->data, name, sizeof (name));
    }
    
    if (side == RIGHT)
    {
        tree_ctor (&(tree->right_ptr));
        strncpy (tree->right_ptr->data, name, sizeof (name));
    }

    return 0;
}

int tree_dump_visual (Tree* tree)
{
    CHECK_ERROR_(tree, "NULL ADRESS", -1);

    FILE* output_file = fopen ("../../output/tree_dump_vis.dot", "w");

    //FILE* output_file = fopen ("tree_dump.dot", "w");

    CHECK_ERROR_(output_file, "NOT CREATED", -1);

    fprintf (output_file, "\tdigraph dump_graph{\n"
                          "\trankdir=HR;\n");


    fprintf (output_file, "\tINFO%p [shape = record, label = \" <left> LEFT | <name> %s | <right> RIGHT\"];\n", tree, tree->data);

    write_tree_element_vis (tree, output_file);

    fprintf(output_file, "\t}");


    if (ferror(output_file))
    {
        printf ("ERROR in function : %s \n"
                "writing file falled\n", __func__);
        return -1;
    }
    
    fclose (output_file);


    system ("\"C:/Program Files/Graphviz/bin/dot.exe\" -Tpng ../../output/tree_dump_vis.dot -o ../../output/tree_graph.png");


    return 0;
}

static int write_tree_element_vis (Tree* tree, FILE* output_file)
{
    if (tree->left_ptr != NULL)
    {
        fprintf (output_file, "\tINFO%p [shape = record, label = \" <left> LEFT | <name> %s | <right> RIGHT\"];\n", tree->left_ptr, tree->left_ptr->data);
        fprintf (output_file, "\tINFO%p: <left> -> INFO%p: <name> [label = \"yes\"]\n", tree, tree->left_ptr);
        write_tree_element_vis (tree->left_ptr, output_file);
    }
    if (tree->right_ptr != NULL)
    {
        fprintf (output_file, "\tINFO%p [shape = record, label = \" <left> LEFT | <name> %s | <right> RIGHT\"];\n", tree->right_ptr, tree->right_ptr->data);
        fprintf (output_file, "\tINFO%p: <right> -> INFO%p: <name> [label = \"no\"]\n", tree, tree->right_ptr);
        write_tree_element_vis (tree->right_ptr, output_file);
    }
    return 0;
}

int tree_dump_text (Tree* tree)
{
    CHECK_ERROR_(tree, "NULL ADRESS", -1);

    FILE* output_file = fopen ("../../output/tree_dump_text.txt", "w");

    fprintf (output_file, "{\n");
    fprintf (output_file, "%s\n", tree->data);
    write_tree_element_text (tree, output_file);
    fprintf (output_file, "}\n");

    if (ferror(output_file))
    {
        printf ("ERROR in function : %s \n"
                "writing file falled\n", __func__);
        return -1;
    }
    
    fclose (output_file);

    return 0;
}

#define _write_tree_elem_(name)                                       \
        do {                                                          \
            fprintf (output_file, "{\n");                             \
            if (tree->name != NULL)                                   \
            {                                                         \
                fprintf (output_file, "%s\n", tree->name->data);      \
                write_tree_element_text (tree->name, output_file);    \
            }                                                         \
            fprintf (output_file, "}\n");                             \
        }while (0)

static int write_tree_element_text (Tree* tree, FILE* output_file)
{
    _write_tree_elem_(left_ptr);
    _write_tree_elem_(right_ptr);
    return 0;
}

#undef _write_tree_elem_

#undef CHECK_ERROR_

#undef $