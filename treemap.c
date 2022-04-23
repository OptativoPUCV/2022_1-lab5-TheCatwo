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
  TreeNode *aux= tree->root;
  TreeNode *parent=NULL;
  do{
    parent=aux;
    if (is_equal(tree, aux->pair->key, key)== 1) 
      return;
    if ((aux->right==NULL) && (aux->left==NULL)) 
      break;
    if (tree->lower_than(aux->pair->key, key)==1) {
      aux=aux->right;
    }
    else {
      aux=aux->left;
    }
  }while(aux);
  TreeNode *new= createTreeNode(key, value);
  new->parent=parent;
    if(parent==NULL){
      tree->root=new;
    }else{
      if(tree->lower_than(new->pair->key,parent->pair->key)){
        parent->left=new;
      }else{
        parent->right=new;
      }
      tree->current=new;
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
        node->pair->key = aux->pair->key;
        node->pair->value = aux->pair->value;
        if (aux->left != NULL) {
          aux->parent->right = aux->left;
          aux->left->parent = aux->parent;
        }else {
        aux->parent->right = NULL;
        }
        if (node -> parent == NULL) {
          tree->root = node;
          tree->root->pair->key = node->pair->key;
          tree->root->pair->value = node->pair->value;
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
  TreeNode* actual=tree->root;
  int flag;
  while(actual!=NULL){
    if(is_equal(tree,actual->pair->key,key)==1){
      tree->current=actual;
      return actual->pair;
    }
    flag=tree->lower_than(actual->pair->key,key);
    if(flag==1){
      actual=actual->right;
    }else{
      actual=actual->left;
    }
  }
  return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
  TreeNode* aux_ub=tree->root;
  TreeNode* rec=tree->root;//variable recorrer
  int ban=0;
  while(rec!=NULL){
    if(is_equal(tree,rec->pair->key,key)){
    return rec->pair->value;
    }
    if(tree->lower_than(key,rec->pair->key)==1){
      aux_ub=rec;
      ban=1;
    }
    if(tree->lower_than(rec->pair->key,key)==1){
      rec=rec->right;
    }else{
      rec=rec->left;
    }
  }
  if(ban==1){
    return aux_ub->pair->value;
  }else{
    return NULL;
  }
}

Pair * firstTreeMap(TreeMap * tree) {
    TreeNode *aux;
    aux=tree->root;
    do{
      aux=aux->left;
      if (aux)
        tree->current=aux;
    }while (aux);
    return tree->current->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
  TreeNode *aux;
  int flag= 0;
  if (tree->current->right==NULL) {
    aux = tree->current->parent;
    while (aux != NULL) {
      if (tree->lower_than(tree->current->pair->key, aux->pair->key) == 1) {
      flag = 1;
      break;
      }
      aux = aux->parent;
    }
    if (flag==0) 
      return NULL;
    tree->current = aux;
    return aux->pair;
  }else {
    aux = minimum(tree->current->right);
    tree->current = aux;
    return aux->pair;
  }
}
