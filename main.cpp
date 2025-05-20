#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

struct Book {
  string title;
  string author;
};

const Book NULL_BOOK = Book{};

#define T Book // we have generics at home
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

int _node__length_rec(Node *node, int current_index) {
  if (node->next == NULL) {
    return current_index + 1;
  }

  return _node__length_rec(node->next, current_index + 1);
}

int node__length(Node *node) { return _node__length_rec(node, 0); }

// NOTE: only uncomment if T is not a struct
// TODO: don't forget to free node->next to avoid memory leak
/*void node__print(Node *node) {*/
/*  cout << node->value << "->";*/
/**/
/*  if (node->next == NULL) {*/
/*    cout << "NULL";*/
/*    return;*/
/*  }*/
/**/
/*  node__print(node->next);*/
/*}*/

Node *node__insert_first(Node *node, T datawith) {
  return node__add(datawith, node);
}

Node *_node__insert_last_rec(Node *node, Node *head, T datawith) {
  if (node->next != NULL)
    return _node__insert_last_rec(node->next, head, datawith);

  node->next = node__add(datawith, NULL);

  return head;
}

Node *node__insert_last(Node *node, T datawith) {
  return _node__insert_last_rec(node, node, datawith);
}

Node *_node__insert_by_index_rec(Node *node, Node *head, int at_index,
                                 int current, T datawith) {
  if (current != at_index)
    return _node__insert_by_index_rec(node->next, node, at_index, current + 1,
                                      datawith);

  Node *to_free = node->next;
  node->next = node__add(datawith, node->next->next);

  free(to_free);

  return head;
}

Node *node__insert_by_index(Node *node, int at_index, T datawith) {
  return _node__insert_by_index_rec(node, node, at_index, 0, datawith);
}

Node *node__delete_first(Node *node) { return node->next; }

Node *_node__delete_last_rec(Node *node, Node *head) {
  if (node->next->next != NULL)
    return _node__delete_last_rec(node->next, head);

  node->next = NULL;

  return head;
}

Node *node__delete_last(Node *node) {
  return _node__delete_last_rec(node, node);
}

Node *_node__delete_by_index_rec(Node *node, Node *head, int at_index,
                                 int current) {
  if (at_index == node__length(node) - 1) {
    return node__delete_last(node);
  }

  if (at_index == 0) {
    return node__delete_first(node);
  }

  if (current + 1 != at_index)
    return _node__delete_by_index_rec(node->next, node, at_index, current + 1);

  node->next = node->next->next;

  return head;
}

Node *node__delete_by_index(Node *node, int at_index) {
  return _node__delete_by_index_rec(node, node, at_index, 0);
}

Book node_book__search_by_title(Node *node, string title) {
  Node *current = node;

  while (current->next == NULL) {
    if (current->value.title == title) {
      return current->value;
    }
  }

  return NULL_BOOK;
}

string INPUT_ERROR;
int CHOICE_INPUT;
string STRING_INPUT;

void page__utama();
void page__tambah_buku_depan();
void page__tambah_buku_belakang();
void page__hapus_buku();
void page__tampilkan_buku();

void page__tambah_buku_depan() {}
void page__tambah_buku_belakang() {}

void page__hapus_buku() {}

void page__tampilkan_buku() {}

void page__utama() {
  do {
    system("clear");

    if (INPUT_ERROR != "") {
      cout << INPUT_ERROR << endl << endl;
    }

    INPUT_ERROR = "";

    cout << "=== menu manajemen daftar buku ===" << endl
         << "1. Tambah buku di depan" << endl
         << "2. Tambah buku di belakang" << endl
         << "3. Hapus buku berdasarkan judul" << endl
         << "4. Tampilkan daftar buku" << endl
         << "5. Keluar" << endl
         << endl;

    cout << "pilih: ";
    cin >> CHOICE_INPUT;

    switch (CHOICE_INPUT) {
    case 1:
      page__tambah_buku_depan();
      break;
    case 2:
      page__tambah_buku_belakang();
      break;
    case 3:
      page__hapus_buku();
      break;
    case 4:
      page__hapus_buku();
      break;
    case 5:
      cout << "bye bye." << endl;
      system("exit");
      break;
    default:
      INPUT_ERROR = "Pilihan tidak valid. Silahkan masukkan no 1-5!!";

      break;
    }
  } while (INPUT_ERROR != "");
}

int main() {
  page__utama();
  return 0;
}
