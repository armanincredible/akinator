#include "akinator.h"

int main ()
{
    Tree *tree_node = {};
    tree_ctor (&tree_node);

    char* buffer = make_tree_from_library (tree_node);
    
    char** game_answers = NULL;
    if (ctr_array_answers_game (&game_answers) == -1)
    {
        return -1;
    }

    game (tree_node, game_answers);

    //definition_tree_elem (tree_node, "MARAT");

    //difference_definition (tree_node);

    tree_dump_visual (tree_node);
    tree_dump_text (tree_node);

    tree_dtor (&tree_node);

    dtor_array_answers_game (&game_answers);

    free (buffer);
    return 0;
}

