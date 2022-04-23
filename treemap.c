#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
  TreeMap* new=(TreeMap*)malloc(sizeof(TreeMap));
  new->lower_than=lower_than;
  new->root=NULL;
  new->current=NULL;
  return new;
    new->lower_than = lower_than;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  TreeNode *aux = tree->root;
  while (aux != NULL) {
    if (is_equal(tree, aux->pair->key, key)== 1) 
      return;
    if ((aux->right == NULL) && (aux->left== NULL)) 
      break;
    if (tree->lower_than(aux->pair->key, key)== 1) {
      aux = aux -> right;
    }
    else {
      aux = aux -> left;
    }
  }
}
TreeNode * minimum(TreeNode* x){
  while (x->left != NULL) {
    x = x -> left;
  }
  return x;
}


void removeNode(TreeMap * tree, TreeNode* node){
  if (node->left == NULL && node->right == NULL){
    if (node == node->parent->left){
      node->parent->left= NULL;
    }
    else{
      node->parent->right= NULL;
    }
    free(node);
    return;
    }
    else{
      if (node->left!= NULL && node->right!= NULL){
        TreeNode *aux = minimum(node->right);
        node->key = aux->key;
        node->value = aux->value;
        if (aux->left != NULL) {
          aux->parent->right = aux->left;
          aux->left->parent = aux->parent;
        }else {
        aux->parent->right = NULL;
        }
        if (node -> parent == NULL) {
          tree->root = node;
          tree->root->key = node->key;
          tree->root->value = node->value;
        }
        removeNode(tree, aux);
        return;
      }
      else{
        if (node->right != NULL) {
          if (node == node->parent->left) {
            node->parent->left = node->right;
            node->right->parent = node->parent;
            free(node);
            return;
          } 
          else{
            node->parent->right = node->right;
            node->right->parent = node->parent;
            free(node);
            return;
          }
        } 
        else {
          if (node == node->parent->left) {
            node->parent->left = node->left;
            node->left->parent = node->parent;
            free(node);
            return;
            } 
          else {
            node->parent->right = node->left;
            node->left->parent = node->parent;
            free(node);
            return;
          }
        }
      }
    }
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
  return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    TreeNode *aux;
    aux=tree->root;
    do{
      aux=aux->left;
      if (aux)
        tree->current=aux;
    }while (aux);
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
