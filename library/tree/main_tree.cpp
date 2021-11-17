#include "tree.h"

#define CHECK_ERROR_(name, type_error, ret)                                             \
        do{                                                                             \
            if (name == NULL)                                                           \
            {                                                                           \
                printf ("\nERROR in function : %s \n"                                   \
                        "%s have %s on line %d\n", __func__,                            \
                        #name, type_error, __LINE__);                                   \
                return ret;                                                             \
            }                                                                           \
        } while (0)


int main ()
{
    Tree *tree = {};
    tree_ctor (&tree);

    char name [] = "EBAL RIBKINU";
    
    tree_push (tree, IN, name );
    tree_push (tree, LEFT, name );
    tree_push (tree, RIGHT, name );

    tree_push (tree->left_ptr, LEFT, name );
    tree_push (tree->left_ptr, RIGHT, name );

    tree_push (tree->right_ptr, LEFT, name );
    tree_push (tree->right_ptr, RIGHT, name );

    tree_dump_visual (tree);
    //tree_dump_text (tree);

    tree_dtor (&tree);
    
    return 0;
}

#undef CHECK_ERROR_