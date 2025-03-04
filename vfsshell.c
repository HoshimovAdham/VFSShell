#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node {
    char name[128];
    int is_file;
    int created_at; 
    struct Node *parent;
    struct Node *child;
    struct Node *next;
} Node;

char username[32];
Node *root;
Node *current;

// utils
void init();
void prompt();
Node *create_node(char name[], int is_file);
void insert_node(Node *node);
void print_node(Node *node);
Node *search_node(char name[]);
void path(Node *node);

// commands
void mkdir(char name[]);
void touch(char name[]);
void ls();
void enter(char name[]);
void back();
void pwd();
void find(Node *node, char name[]);
void quit();
void tree(Node *node, int level);

int main() {
    
    init();
    printf("enter username: "); scanf("%s", username);

    char command[64]; 
    char arg[128]; 

    while (1) {
        prompt();

        scanf("%s", command);

        if (strcmp(command, "mkdir") == 0) {
            scanf("%s", arg);
            mkdir(arg);
        } else if (strcmp(command, "touch") == 0) {
            scanf("%s", arg);
            touch(arg);
        } else if (strcmp(command, "ls") == 0) {
            ls();
        } else if (strcmp(command, "enter") == 0) {
            scanf("%s", arg);
            enter(arg);
        } else if (strcmp(command, "back") == 0) {
            back();
        } else if (strcmp(command, "pwd") == 0) {
            pwd();
        } else if (strcmp(command, "find") == 0) {
            scanf("%s", arg);
            find(current, arg);
        } else if (strcmp(command, "tree") == 0) {
            tree(current, 0);
        } else if (strcmp(command, "exit") == 0) {
            quit();
        }
    }

    return 0;
}

void init() {
    Node *node = malloc(sizeof(Node));

    strcpy(node->name, "root");
    node->is_file = 0;
    node->created_at = time(NULL);
    node->parent = NULL;
    node->child = NULL;
    node->next = NULL;

    root = node;
    current = root;
}

void prompt() {

    printf("%s:/", username);
    path(current);
    printf("$ ");
}

Node *create_node(char name[], int is_file) {
    Node *node = malloc(sizeof(Node));

    strcpy(node->name, name);
    node->is_file = is_file;
    node->created_at = time(NULL);
    node->parent = current;
    node->child = NULL;
    node->next = NULL;

    return node;
}

void insert_node(Node *node) {
    if (current->child == NULL) {
        current->child = node;
    }
    else {
        Node *temp = current->child;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = node;
    }
}

void print_node(Node *node) {
    if (node->is_file) {
        printf("%s\n", node->name);
    } else {
        printf("%s/\n", node->name);
    }
}

Node *search_node(char name[]) {
    Node *node = current->child;

    while (node != NULL) {
        if (strcmp(node->name, name) == 0) {
            return node;
        }
        node = node->next;
    }
    
    return NULL;
}

void path(Node *node) {
    if (node == root) {
        printf("%s/", node->name);
        return;
    }
    path(node->parent);
    printf("%s/", node->name);
}

void mkdir(char name[]) {
    Node *node = create_node(name, 0);
    insert_node(node);
}

void touch(char name[]) {
    Node *node = create_node(name, 1);
    insert_node(node);
}

void ls() {
    if (current->child != NULL) {
        Node *temp = current->child;
        print_node(temp);

        while (temp->next != NULL) {
            print_node(temp->next);
            temp = temp->next;
        }
    }
}

void enter(char name[]) {
    Node *node = search_node(name);
    
    if (node != NULL){
        current = node;
    } else {
        printf("enter: no such file or directory: %s\n", name);
    }
}

void back() {
    if (current != root) {
        current = current->parent;
    }
}

void pwd() {
    path(current);
    printf("\n");
}

void find(Node *node, char name[]) {
    if (strcmp(node->name, name) == 0) {
        path(node);
        printf("\n");
    }
    if (node->child != NULL) {
        find(node->child, name);
    }
    if (node->next != NULL) {
        find(node->next, name);
    }
}

void tree(Node *node, int level) {
    for (int i = 0; i < level; i++) {
        printf("\t");
    }
    print_node(node);
    if (node->child != NULL) {
        tree(node->child, level + 1);
    }
    if (node->next != NULL) {
        tree(node->next, level);
    }
}

void quit() {
    free(root);
    exit(0);
}
