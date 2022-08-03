#include <stdio.h>
#include <stdlib.h>

//2440051574 - JASON LEONARDO SUTIOSO

struct node{
    int num;
    int height;
    struct node *left;
    struct node* right;
};

int getHeight(struct node *tnode){
    if(tnode == NULL) return 0;
    else return tnode-> height;
}

struct node* newNode(int num){
    struct node* tnode = (struct node*) malloc(sizeof(struct node));
    tnode->num = num;
    tnode->left = NULL;
    tnode->right = NULL;
    tnode->height = 1;
    return tnode;
}

int getMax(int num1, int num2){
    if(num1 >= num2) return num1;
    else return num2;
}

struct node *rotateRight(struct node *tnode){
    struct node *tar = tnode->left;
    struct node *temp = tar->right;
    tar->right = tnode;
    tnode->left = temp;
    tnode->height = (getMax(getHeight(tnode->left), getHeight(tnode->right))+ 1);
    tar->height = (getMax(getHeight(tar->left), getHeight(tar->right)) + 1);
    return tar;
};

struct node *rotateLeft(struct node *tnode){
    struct node *tar = tnode->right;
    struct node *temp = tar->left;
    tar->left = tnode;
    tnode->right = temp;
    tnode->height = (getMax(getHeight(tnode->left), getHeight(tnode->right))+ 1);
    tar->height = (getMax(getHeight(tar->left), getHeight(tar->right)) + 1);
    return tar;
};

int getBalance(struct node *tnode)
{
    if (tnode == NULL) return 0;
    return getHeight(tnode->left) - getHeight(tnode->right);
}

struct node* insertNode(struct node* tnode, int num)
{
    if(tnode == NULL) return newNode(num);

    if(num < tnode->num) tnode->left  = insertNode(tnode->left, num);
    else if(num > tnode->num) tnode->right = insertNode(tnode->right, num);
    else return tnode;

    tnode->height = (getMax(getHeight(tnode->left), getHeight(tnode->right)) + 1);

    int bal = getBalance(tnode);
    if(bal> 1 && num < tnode->left->num) return rotateRight(tnode);

    if(bal < -1 && num > tnode->right->num) return rotateLeft(tnode);

    if(bal > 1 && num > tnode->left->num){
        tnode->left =  rotateLeft(tnode->left);
        return rotateRight(tnode);
    }

    if (bal < -1 && num < tnode->right->num){
        tnode->right = rotateRight(tnode->right);
        return rotateLeft(tnode);
    }

    return tnode;
}

struct node *nodeMin(struct node* tar)
{
    struct node* currNode = tar;
    while(currNode->left != NULL) currNode = currNode->left;

    return currNode;
}

struct node* delNode(struct node* tnode, int num){
    if (tnode == NULL) return tnode;

    if(num < tnode->num) tnode->left = delNode(tnode->left, num);
    else if(num > tnode->num) tnode->right = delNode(tnode->right, num);
    else{
        if(tnode->left == NULL || tnode->right == NULL){
            struct node *temp = tnode->left ? tnode->left : tnode->right;
            if (temp == NULL){
                temp = tnode;
                tnode = NULL;
            }
            else *tnode = *temp;

            free(temp);
        }
        else{
            struct node* temp2 = nodeMin(tnode->right);
            tnode->num = temp2->num;
            tnode->right = delNode(tnode->right, temp2->num);
        }
    }

    if(tnode == NULL) return tnode;

    tnode->height = (getMax(getHeight(tnode->left), getHeight(tnode->right)) + 1);

    int bal = getBalance(tnode);

    if (bal > 1 && getBalance(tnode->left) >= 0) return rotateRight(tnode);

    if (bal > 1 && getBalance(tnode->left) < 0){
        tnode->left =  rotateLeft(tnode->left);
        return rotateRight(tnode);
    }

    if (bal< -1 && getBalance(tnode->right) <= 0) return rotateLeft(tnode);

    if (bal < -1 && getBalance(tnode->right) > 0){
        tnode->right = rotateRight(tnode->right);
        return rotateLeft(tnode);
    }

    return tnode;
}

void preorder(struct node * roots){
    if(roots != NULL){
        printf("%d ", roots->num);
        preorder(roots->left);
        preorder(roots->right);
    }
}

int main(){

    char inp;
    struct node *root = NULL;

    do{
        printf("AVL TREE PROGRAM\n\n");
        printf("Pre-order traversal:\n");
        preorder(root);

        printf("\n\n");
        printf("[1] Insert new node\n[2] Delete node\n[0] Quit program\n\nInput: ");
        scanf(" %c", &inp);
        if(inp == '1'){
            int num;
            do{
                printf("Enter number from 1 to 100: ");
                scanf("%d", &num);
            }while(num < 1 || num > 100);
            root = insertNode(root, num);
            printf("Node added.\n\n");
        }
        else if(inp == '2'){
            int num;
            printf("Delete which node: ");
            do{
                scanf("%d", &num);
            }while(num < 1 || num > 100);
            root = delNode(root, num);
            printf("Node deleted.\n\n");
        }


    }while(inp != '0');
}

