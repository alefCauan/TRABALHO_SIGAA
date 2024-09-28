#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int value;
    int height;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct AVL {
    Node *root;
} AVL;

void show(Node *root)
{
    if(root)
    {
        printf("Value: %d\n", root->value);
        show(root->left);
        show(root->right);
    }
}

int max(int a, int b) { return (a > b) ? a : b; }

int height(Node *root)
{
    int result = 0;

    if(root)
        result = root->height;

    return result;
}

int get_balance(Node *root)
{
    int result = 0;

    if(root)
        result = height(root->left) - height(root->right);

    return result;
}

Node *rotate_right(Node *ex_root)
{
    Node *new_root = ex_root->left;
    Node *leaf = new_root->right;

    // Realiza a rotação
    new_root->right = ex_root;
    ex_root->left = leaf;

    // Atualiza as alturas
    ex_root->height = 1 + max(height(ex_root->left), height(ex_root->right));
    new_root->height = 1 + max(height(new_root->left), height(new_root->right));

    // Retorna a nova raiz
    return new_root;
}

Node *rotate_left(Node *ex_root)
{
    Node *new_root = ex_root->right;
    Node *leaf = new_root->left;

    // Realiza a rotação
    new_root->left = ex_root;
    ex_root->right = leaf;

    // Atualiza as alturas
    ex_root->height = 1 + max(height(ex_root->left), height(ex_root->right));
    new_root->height = 1 + max(height(new_root->left), height(new_root->right));

    // Retorna a nova raiz
    return new_root;
}

Node *alloc_node()
{
    Node *new = (Node *)malloc(sizeof(Node));
    new->height = 1;
    new->left = NULL;
    new->right = NULL;

    return new;
}

Node *insertNode(Node* root, int value) 
{
    Node *result = &(*root); 

    if (root == NULL)
    {
        root = alloc_node();
        root->value = value;
        result = root;
    }
    else
    {
        if (value < root->value)
            root->left = insertNode(root->left, value);
        else if (value > root->value)
            root->right = insertNode(root->right, value);
        else 
            result = root;
        
        root->height = 1 + max(height(root->left), height(root->right));

        // 3. Obtém o fator de balanceamento deste nó ancestral
        int balance = get_balance(root);

        // 4. Se o nó se tornar desbalanceado, então existem 4 casos

        // Caso Esquerda-Esquerda
        if (balance > 1 && value < root->left->value)
            result = rotate_right(root);
            
        else if(balance < -1 && value > root->right->value)
            result = rotate_left(root);

        else if (balance > 1 && value > root->left->value)
        {
            root->left = rotate_left(root->left);
            result = rotate_right(root);
        }
        else if (balance < -1 && value < root->right->value)
        {
            root->right = rotate_right(root->right);
            result = rotate_left(root);
        }

    }

    return result;
}


int main()
{
    AVL *tree = (AVL *)malloc(sizeof(AVL));

    int values[] = {7,5, 6, 8, 9, 10, 11, 12, 4, 20, 21};
    int size = sizeof(values)/sizeof(values[0]);

    for(int i = 0; i < size; i++)
        tree->root = insertNode(tree->root, values[i]);    
    
    show(tree->root);

    free(tree);

    return 0;
}