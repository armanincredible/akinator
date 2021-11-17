#include "akinator.h"

int main ()
{
    Tree *tree = {};
    tree_ctor (&tree);

    /*char name[10] = {};

    strcpy (name, "ANIMAL");
    tree_push (tree, IN, name);

    strcpy (name, "MARAT");
    tree_push (tree, LEFT, name);

    strcpy (name, "GOD");
    tree_push (tree, RIGHT, name);*/

    make_tree_from_library (tree);

    game (tree);

    //definition_tree_elem (tree, "PETROVICH");


    tree_dump_visual (tree);
    /*tree_dump_text (tree);*/

    return 0;
}

