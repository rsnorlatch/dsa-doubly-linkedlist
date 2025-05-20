#include <iostream>

using namespace std;

struct Book {
  string judul;
  string penulis;
};

#define T int // we have generics at home
struct Node {
  T value;
  Node *next;
};

Node *node__add(T data, Node *next) {
  Node *n = (Node *)malloc(sizeof(Node));
  n->value = data;
  n->next = next;

  return n;
}

// TODO: don't forget to free node->next to avoid memory leak
void node__print(Node *node) {
  cout << node->value << "->";

  if (node->next == NULL) {
    cout << "NULL";
    return;
  }

  node__print(node->next);
}

Node *node__insert_first(Node *node, T datawith) {
  return node__add(datawith, node);
}

Node *node__insert_last_rec(Node *node, Node *head, T datawith) {
  if (node->next != NULL)
    return node__insert_last_rec(node->next, head, datawith);

  node->next = node__add(datawith, NULL);

  return head;
}

Node *node__insert_last(Node *node, T datawith) {
  return node__insert_last_rec(node, node, datawith);
}

Node *node__insert_by_index_rec(Node *node, Node *head, int at_index,
                                int current, T datawith) {
  if (current != at_index)
    return node__insert_by_index_rec(node->next, node, at_index, current + 1,
                                     datawith);

  Node *to_free = node->next;
  node->next = node__add(datawith, node->next->next);

  free(to_free);

  return head;
}

Node *node__insert_by_index(Node *node, int at_index, T datawith) {
  return node__insert_by_index_rec(node, node, at_index, 0, datawith);
}

Node *node__delete_first(Node *node) { return node->next; }

Node *node__delete_last_rec(Node *node, Node *head) {
  if (node->next->next != NULL)
    return node__delete_last_rec(node->next, head);

  node->next = NULL;

  return head;
}

Node *node__delete_last(Node *node) {
  return node__delete_last_rec(node, node);
}

Node *node__delete_by_index_rec(Node *node, Node *head, int at_index,
                                int current) {
  if (current != at_index)
    return node__delete_by_index_rec(node->next, node, at_index, current + 1);

  node->next = node->next->next;

  return head;
}

Node *node__delete_by_index(Node *node, int at_index) {
  return node__delete_by_index_rec(node, node, at_index, 0);
}

int main() {
  Node *n = node__add(1, node__add(2, node__add(3, NULL)));
  node__print(n);
}
