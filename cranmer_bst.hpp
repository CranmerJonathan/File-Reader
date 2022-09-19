/*                                                                                              
Author:Jonathan Cranmer
Date: June 30rd, 2022
Description: Welcome to the binary search tree template class. It is your run of the mill binary search tree
*/

#pragma once
#ifdef CRANMER_BST_TEMPLATE_H
#define CRANMER_BST_TEMPLATE_H

#endif

#include "cranmer_wordentry.h"
#include <iostream>

using std::cout;
using std::endl;

class Node;

//class declaring
template <class T>
class BST
{
public:

  //Node structor
class Node
{
 public:
  T value;
  Node* right;
  Node* left;
  Node()
    {
      right = nullptr;
      left = nullptr;
    }
};

//constructor & destructor
  BST();
 ~BST();

 //All the method guys
 int Insert(T);
 void PrintTree();
 int Remove(T);
 int ElementExist(T);
 Node* Find(T);
 T* ToArray();
 T* ArrayConverter(Node*, T*);
 int Count();
 void Empty();
 Node* getRoot();

private:

 //Variables
 int count;
 Node* root;

 //more method guys but shhhh theyre secret
 int add(Node**, T);
 void PrintTree(Node*);
 Node* Withdraw(Node*, T);
 Node* FindMin(Node*);
 int CheckElement(Node*, T);
 Node* Locate(Node*, T);
 void Clean(Node*);
};

//constructer
template<class T>
BST<T> :: BST ()
{
  this->root = nullptr;
  this->count=0;
}

//destructor
template<class T>
BST<T> :: ~BST()
{
  Empty();
  delete this->root;
}

//add nodes publicly
template<class T>
int BST<T> :: Insert(T value)
{
  return add(&root, value);
}

//add node privately
template<class T>
int BST<T> :: add(Node** root, T val)
{
  //checks if node is empty to fill it
  if(*root == nullptr)
    {
      *root = new Node();
      (*root)->value = val;
      (*root)->left = nullptr;
      (*root)->right = nullptr;


      this->count++;
      
      return 1;
    }
  //if node already exist return 0
  else if((*root)->value == val)
    {
      return 0;
    }
  //if less go left and if greater go right
  else
    {
      if (val > (*root)->value)
	{
          return 0 + add(&(*root)->right, val);
	}
      else
        {
          return 0 + add(&(*root)->left, val);
        }
    }
}

//J prints the tree
template <class T>
void BST<T> :: PrintTree() 
{
  PrintTree(this->root);
}

//prints tree recursively
template <class T>
void BST<T> :: PrintTree(Node* root)
{
  if(root == nullptr)
    {
      return;
    }
  else 
    {
      if(root->left != nullptr)
	{
	  PrintTree(root->left);
	}

      cout << root->value << endl;

      if(root->right != nullptr)
        {
          PrintTree(root->right);
        }

    }
}

//Removes desire node
template <class T>
int BST<T> :: Remove(T value)
{
  if(Withdraw(this->root, value) == nullptr)
    {
      return 0;
    }
  else
    {
      count--;
      return 1;
    }
}

//removes desired node recursively
template <class T>
typename BST<T>::Node* BST<T>::Withdraw(Node* root, T val)
{
  //if node is empty bottom of the tree value not found
  if(root == nullptr)
    {
      return root;
    }
  //if value less than current node go left
  else if(val < root->value)
    {
      Withdraw(root->left, val);
    }
  //if value more than current node go right
  else if(val > root->value)
    {
      Withdraw(root->right, val);
    }
  //if equal to we begin delete >:)
  else
    {
      //if node has no leaf ez we just delete it 
      if(root->left == nullptr && root->right == nullptr)
        {
          root = nullptr;
          delete root;
        }
      //if has one leaf that leaf replaces the node
      else if(root->left == nullptr)
        {
          struct node *temp = root;
          root = root->right;
          delete temp;
        }
      else if (root->right == nullptr)
        {
          struct node *temp = root;
          root = root->left;
          delete temp;
        }
      //if two nodes, we find the minimum to the right and replace the node because it will be greater than all on the left and less than all on the right so it fits right in.
      else
	{
	  struct node* temp = FindMin(root->right);
	  root->value = temp->value;
	  root->right = Withdraw(root->right, temp->value);
	}
    }
  return root;
}

//find min
template <class T>
typename BST<T>::Node* BST<T>::FindMin(Node* root)
{
  //Just finds the left most root and returns it
  if(root->left == nullptr)
    {
      return root;
    }
  else
    {
      return FindMin(root->left);
    }
}

//checks if element exists
template <class T>
int BST<T> :: ElementExist(T value)
{
  return CheckElement(this->root, value);
}

//checks if element exists recursively
template<class T>
int BST<T> :: CheckElement(Node* root, T val)
{
  //Bottom of tree doesnt exists
  if(root == nullptr)
    {
      return 0;
    }
  //does exist pog
  if(root->value == val)
    {
      return 1;
    }
  //going right if greater than going left is less than
  else
    {
      if(val > root->value)
        {
          return 0 + CheckElement(root->right, val);
        }
      else
        {
          return 0 + CheckElement(root->left, val);
        }
    }
}

//find node
template<class T>
typename BST<T>::Node* BST<T> :: Find(T value)
{
  return Locate(this->root, value);
}

//find node recursively
template<class T>
typename BST<T>::Node* BST<T> :: Locate(Node* root, T val)
{
  //node not found
  if(root == nullptr)
    {
      return root;
    }
  //node found
  else if(root->value == val)
    {
      return root;
    }
  //go right if greater than
  else if(root->value < val)
    {
      return Locate(root->right, val);
    }
  //go left if less than
  else
    {
      return Locate(root->left, val);
    }
}

//converts to array
template<class T>
T* BST<T> :: ToArray()
{
  T* array = new T[count];
  return ArrayConverter(this->root, array);
}

//converts to array recursively
template<class T>
T* BST<T> :: ArrayConverter(Node* root, T* array)
{
  static int index = 0;
  //nothing in tree
  if(root == nullptr)
    {
      return array;
    }

  //go left most thats the first guy go up second go right third rince and repeat
  ArrayConverter(root->left, array);
  array[index++] = (root->value);
  ArrayConverter(root->right, array);

  return array;
}

//just returns the counter of number of nodes in tree
template <class T>
int BST <T> :: Count()
{
  return this->count;
}

//empty tree
template<class T>
void BST<T> :: Empty()
{
  Clean(this->root);
}

//empty tree recursively
template<class T>
void BST<T> :: Clean(Node* root)
{
  //if no node we done
  if(root == nullptr)
    {
      return;
    }
  //if has no roots we j delete the node
  else if(root->left == nullptr && root->right == nullptr)
    {
      root = nullptr;
      delete root;
    }
  //if one leaf delete that leaf and its leaves
  else if (root-> left != nullptr && root->right != nullptr)
    {
      Clean(root->left);
      Clean(root->right);
      root = nullptr;
      delete root;
    }
  //if two leafs delete both those guys than delete root
  else
    {
      if(root->left == nullptr)
	{
	  Clean(root->right);
	  root = nullptr;
	  delete root;
	}
      else if(root->right == nullptr)
	{
	  Clean(root->left);
	  root = nullptr;
	  delete root;
	}
    }
}

template<class T>
typename BST<T>::Node* BST<T>::getRoot()
{
  return root;
}
