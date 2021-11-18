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


static int write_tree_element_vis (Tree* tree_node, FILE* output_file);

static int write_tree_element_text (Tree* tree_node, FILE* output_file);

int tree_ctor (Tree** tree_node)
{
    *tree_node = (Tree*) calloc (1, sizeof (Tree));
    CHECK_ERROR_(*tree_node, "NULL ADRESS (NOT FREE MEMORY)", -1);

    (*tree_node)->left_ptr =  NULL;
    (*tree_node)->right_ptr = NULL;

    return 0;
}

#define _tree_dtor_elem_(name)                                      \
        do {                                                        \
            if ((*tree_node)->name != NULL)                              \
            {                                                       \
                tree_dtor (&((*tree_node)->name));                       \
            }                                                       \
            (*tree_node)->name = NULL;                                   \
        }while (0)

int tree_dtor (Tree** tree_node)
{
    CHECK_ERROR_(*tree_node, "NULL ADRESS", -1);

    memset ((*tree_node)->data, 0, NAME_LENGTH);

    _tree_dtor_elem_(left_ptr);

    _tree_dtor_elem_(right_ptr);

    free (*tree_node);

    return 0;
}

#undef _tree_dtor_elem_

int tree_push (Tree* tree_node, int side, char* name)
{
    CHECK_ERROR_(tree_node, "NULL ADRESS", -1);

    if (side == IN)
    {
        tree_node->data = name;
    }

    if (side == LEFT)
    {
        tree_ctor (&(tree_node->left_ptr));
        tree_node->left_ptr->data = name;
    }
    
    if (side == RIGHT)
    {
        tree_ctor (&(tree_node->right_ptr));
        tree_node->right_ptr->data = name;
    }

    return 0;
}

int tree_dump_visual (Tree* tree_node)
{
    CHECK_ERROR_(tree_node, "NULL ADRESS", -1);

    FILE* output_file = fopen ("../../output/tree_dump_vis.dot", "w");

    //FILE* output_file = fopen ("tree_dump.dot", "w");

    CHECK_ERROR_(output_file, "NOT CREATED", -1);

    fprintf (output_file, "\tdigraph dump_graph{\n"
                          "\trankdir=HR;\n");


    fprintf (output_file, "\tINFO%p [shape = record, label = \" <left> LEFT :\\n%p | <name> %s | <right> RIGHT :\\n%p\"];\n",
                             (void*)tree_node, (void*)tree_node->left_ptr, tree_node->data, (void*)tree_node->right_ptr);

    write_tree_element_vis (tree_node, output_file);

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

static int write_tree_element_vis (Tree* tree_node, FILE* output_file)
{
    if (tree_node->left_ptr != NULL)
    {
        fprintf (output_file, "\tINFO%p [shape = record, label = \" <left> LEFT :\\n%p | <name> %s | <right> RIGHT :\\n%p\"];\n", 
                                (void*)tree_node->left_ptr, (void*)tree_node->left_ptr->left_ptr, tree_node->left_ptr->data, (void*)tree_node->left_ptr->right_ptr);
        fprintf (output_file, "\tINFO%p: <left> -> INFO%p: <name> [label = \"yes\"]\n", (void*)tree_node, (void*)tree_node->left_ptr);
        write_tree_element_vis (tree_node->left_ptr, output_file);
    }
    if (tree_node->right_ptr != NULL)
    {
        fprintf (output_file, "\tINFO%p [shape = record, label = \" <left> LEFT :\\n%p | <name> %s | <right> RIGHT :\\n%p\"];\n",
                                (void*)tree_node->right_ptr, (void*)tree_node->right_ptr->left_ptr, tree_node->right_ptr->data, (void*)tree_node->right_ptr->right_ptr);
        fprintf (output_file, "\tINFO%p: <right> -> INFO%p: <name> [label = \"no\"]\n", (void*)tree_node, (void*)tree_node->right_ptr);
        write_tree_element_vis (tree_node->right_ptr, output_file);
    }
    return 0;
}

int tree_dump_text (Tree* tree_node)
{
    CHECK_ERROR_(tree_node, "NULL ADRESS", -1);

    FILE* output_file = fopen ("../../output/tree_dump_text.txt", "w");

    fprintf (output_file, "{\n");
    fprintf (output_file, "%s\n", tree_node->data);
    write_tree_element_text (tree_node, output_file);
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
            if (tree_node->name != NULL)                                   \
            {                                                         \
                fprintf (output_file, "%s\n", tree_node->name->data);      \
                write_tree_element_text (tree_node->name, output_file);    \
            }                                                         \
            fprintf (output_file, "}\n");                             \
        }while (0)

static int write_tree_element_text (Tree* tree_node, FILE* output_file)
{
    _write_tree_elem_(left_ptr);
    _write_tree_elem_(right_ptr);
    return 0;
}

#undef _write_tree_elem_

#undef CHECK_ERROR_

#undef $