#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
    int data;
    struct node *rc, *lc;
};

int item;
int se_item;
int del_element;
int count=0;
int lheight = 0;
int rheight = 0;
int Height;
int result = 0;
int node_value;
int sum_left_sub = 0;
int sum_right_sub = 0;
int k = 0;

void Insertion(struct node *, struct node *);
bool Search(int, struct node *);
void Inorder(struct node *);
void delete(int, struct node **);
struct node *succ(struct node *);
void Preorder(struct node *);
void Postorder(struct node *);
void deleteTree(struct node *);
int height(struct node *);

struct node *succ(struct node *ptr) {
    ptr = ptr->rc;
    while (ptr->lc != NULL) {
        ptr = ptr->lc;
    }
    return ptr;
}

void Insertion(struct node *ptr, struct node *p) {
    struct node *parent;
    while (ptr != NULL) {
        parent = ptr;
        if (item < ptr->data) {
            ptr = ptr->lc;
        } else if (item > ptr->data) {
            ptr = ptr->rc;
        }
    }

    if (item < parent->data) {
        parent->lc = p;
    } else if (item > parent->data) {
        parent->rc = p;
    }
}

bool Search(int se_item, struct node *ptr) {
    while (ptr != NULL) {
        if (se_item < ptr->data) {
            ptr = ptr->lc;
        } else if (se_item > ptr->data) {
            ptr = ptr->rc;
        } else {
            return true;
        }
    }
    return false;
}

void Inorder(struct node *ptr) {
    if (ptr != NULL) {
        Inorder(ptr->lc);
        printf("  %d  ", ptr->data);
        Inorder(ptr->rc);
    }
}

void Preorder(struct node *ptr) {
    if (ptr != NULL) {
        printf("  %d  ", ptr->data);
        Preorder(ptr->lc);
        Preorder(ptr->rc);
    }
}

void Postorder(struct node *ptr) {
    if (ptr != NULL) {
        Postorder(ptr->lc);
        Postorder(ptr->rc);
        printf("  %d  ", ptr->data);
    }
}

void delete(int de_item, struct node **ptr) {
    struct node *parent = NULL;
    struct node *current = *ptr;
    bool found = false;

    while (current != NULL) {
        if (de_item < current->data) {
            parent = current;
            current = current->lc;
        } else if (de_item > current->data) {
            parent = current;
            current = current->rc;
        } else {
            found = true;
            break;
        }
    }

    if (!found) {
        printf("Deletion not possible, no such node in the tree!\n");
        return;
    }

    if (current->lc == NULL && current->rc == NULL) {
        if (parent == NULL) {
            *ptr = NULL;
        } else if (parent->lc == current) {
            parent->lc = NULL;
        } else {
            parent->rc = NULL;
        }
        free(current);
    } else if (current->lc != NULL && current->rc != NULL) {
        struct node *successor = succ(current);
        int successor_data = successor->data;
        delete(successor->data, ptr);
        current->data = successor_data;
    } else {
        struct node *child = (current->lc != NULL) ? current->lc : current->rc;

        if (parent == NULL) {
            *ptr = child;
        } else if (parent->lc == current) {
            parent->lc = child;
        } else {
            parent->rc = child;
        }
        free(current);
    }
    printf("Node with value %d deleted successfully.\n", de_item);
}

void deleteTree(struct node *ptr) {
    if (ptr != NULL) {
        deleteTree(ptr->lc);
        deleteTree(ptr->rc);
        free(ptr);
    }
}

void  LeafNode(struct node *ptr){
    if(ptr != NULL){
        if(ptr -> lc == NULL && ptr -> rc == NULL){
            count = count + 1;
        }
        LeafNode(ptr -> lc);
        LeafNode(ptr -> rc);
    }
}
//To find the sum of subtree depts

int i = 1;
void dept(struct node * ptr){
    //to allocate the ptr to the required node
    while(i == 1 && ptr != NULL){ //make sure the recursice call dosent execute this while loop (i var is used)
        if(node_value < ptr -> data){
            ptr = ptr -> lc;
        }
        else if (node_value > ptr -> data){
            ptr = ptr -> rc;
        }

        if(ptr -> data == node_value){
            i = 0;
            break;
        }
        else{
            continue;
        }
    }
//to find the sum fo depts
    if(ptr -> lc != NULL){
        dept(ptr ->lc);
        k = k + 1;
        result = result + k;
    }
    k = 0;
    if(ptr -> rc != NULL){
        dept(ptr -> rc);
        k = k + 1;
        result = result + k;
    }
    
}

int height(struct node * ptr){
    if(ptr == NULL){
        return 0;
    }

    rheight = height(ptr -> rc);
    lheight = height(ptr -> lc);

    if(lheight > rheight){
        return lheight + 1;
    }
    else{
        return rheight + 1;
    }
}

int main() {
    struct node *root = NULL;
    int choice;

    printf("1. Insertion\n2. Search\n3. Inorder\n4. Preorder\n5. PostOrder\n6. Delete a Node\n7. Exit\n8. Count the Number of Leaf Nodes\n9.Height\n10.Level Order\n");
    do {
        printf("Enter choice: ");
        scanf("%d", &choice);
        struct node *p;
        switch (choice) {
            case 1:
                printf("Enter the Value: ");
                scanf("%d", &item);
                p = (struct node *)malloc(sizeof(struct node));
                p->data = item;
                p->rc = NULL;
                p->lc = NULL;

                if (root == NULL) {
                    root = p;
                } else {
                    Insertion(root, p);
                }
                break;
            case 2:
                printf("Enter the Data to be Searched: ");
                scanf("%d", &se_item);
                if (Search(se_item, root)) {
                    printf("Element is present\n");
                } else {
                    printf("Element is not present\n");
                }
                break;
            case 3:
                printf("The Data InOrder: \n");
                Inorder(root);
                printf("\n");
                break;
            case 4:
                printf("The Data in PreOrder: \n");
                Preorder(root);
                printf("\n");
                break;
            case 5:
                printf("The Data in PostOrder: \n");
                Postorder(root);
                printf("\n");
                break;
            case 6:
                printf("Enter the Data to be Deleted: ");
                scanf("%d", &del_element);
                delete(del_element, &root);
                break;
            case 7:
                printf("Exiting...\n");
                deleteTree(root);
                root = NULL;
                break;
            default:
                printf("Invalid choice! Please try again.\n");

            /*case 8:
                LeafNode(root);
                printf("The Number of leaf nodes: ");
                printf("%d\n",count);
                count = 0;
                break;*/

            case 8:
                printf("Enter the Node value to find the sum of the subtree depts: ");
                scanf("%d",&node_value);
                dept(root);
                printf("The Sum of SubTre Dept of The Binary Tree:  %d\n",result);
                result = 0;
                k = 0;
            break;

            case 9:
                Height = height(root);
                printf("The Height of the Binary Search Tree: \n");
                printf(" %d ",Height);
            break;
            case 10:    
                printf("Level Order: ");
                
        }
    } while (choice != 11);

    return 0;
}
