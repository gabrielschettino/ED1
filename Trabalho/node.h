typedef struct Node
{
    int row;
    int col;
    float value;
    struct Node *next_row;
    struct Node *next_col;
} Node;