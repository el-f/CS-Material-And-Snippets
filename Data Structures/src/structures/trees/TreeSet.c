#include <stdlib.h>
#include <stdio.h>

typedef int   (*Comparator)(const void *, const void *);

typedef char *(*Stringizer)(const void *);

typedef struct BST {
    const void *data;
    struct BST *left;
    struct BST *right;
    Comparator comparator;
    Stringizer tostr;
} BST;

BST *set_initialize(Comparator comparator, Stringizer tostr) {
    BST *set = (BST *) malloc(sizeof(BST));
    set->data = NULL;
    set->left = NULL;
    set->right = NULL;
    set->comparator = comparator;
    set->tostr = tostr;
    return set;
}

BST *init_set() {
    return set_initialize(NULL, NULL);
}

BST *insert(BST *root, const void *x, Comparator comparator) {
    if (root->data == NULL) {
        root->data = x;
        root->left = init_set();
        root->right = init_set();
    } else if (comparator(x, root->data) < 0) {
        root->left = insert(root->left, x, comparator);
    } else if (comparator(x, root->data) > 0) {
        root->right = insert(root->right, x, comparator);
    }
    return root;
}

const BST *find(const BST *root, const void *x, Comparator comparator) {
    if (root == NULL || root->data == NULL) return NULL;
    else if (comparator(x, root->data) < 0) return find(root->left, x, comparator);
    else if (comparator(x, root->data) > 0) return find(root->right, x, comparator);
    return root;
}

BST *find_min(BST *root) {
    if (root == NULL) return NULL;
    else if (root->data == NULL || root->left == NULL || root->left->data == NULL) return root;
    return find_min(root->left);
}

BST *delete(BST *root, const void *x, Comparator comparator) {
    BST *temp;
    if (root == NULL || root->data == NULL) return NULL;
    else if (comparator(x, root->data) < 0)
        root->left = delete(root->left, x, comparator);
    else if (comparator(x, root->data) > 0)
        root->right = delete(root->right, x, comparator);
    else if (root->left->data && root->right->data) {
        temp = find_min(root->right);
        root->data = temp->data;
        root->right = delete(root->right, root->data, comparator);
    } else {
        if (root->left->data == NULL) root = root->right;
        else if (root->right->data == NULL) root = root->left;
    }
    return root;
}

void inorder(BST *root, Stringizer tostr) {
    if (root != NULL && root->data != NULL) {
        inorder(root->left, tostr);
        puts(tostr(root->data));
        fflush(stdout);
        inorder(root->right, tostr);
    }
}

void set_print(BST *root) {
    inorder(root, root->tostr);
}

void set_destroy(BST *root) {
    if (root != NULL) {
        set_destroy(root->left);
        set_destroy(root->right);
        free(root);
    }
}

void set_insert(BST *root, const void *x) {
    insert(root, x, root->comparator);
}


int set_includes(const BST *root, const void *x) {
    return find(root, x, root->comparator) != NULL;
}

size_t set_size(const BST *s) {
    if (s == NULL || s->data == NULL) return 0;
    return (set_size(s->left) + 1 + set_size(s->right));
}

void set_remove(BST *root, const void *x) {
    if (root == NULL || root->data == NULL) return;
    if ((root->left == NULL || root->left->data == NULL) &&
        (root->right == NULL || root->right->data == NULL) &&
        (root->comparator(root->data, x) == 0)) {
        root->data = NULL;
        return;
    }
    BST *temp = delete(root, x, root->comparator);
    root->data = temp->data;
    root->left = temp->left;
    root->right = temp->right;
}