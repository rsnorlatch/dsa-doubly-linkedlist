#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

struct Book {
  string title;
  string author;
};

const Book NULL_BOOK = Book{};

bool book_is_null(Book book) {
  return (book.title == NULL_BOOK.title && book.author == NULL_BOOK.author);
}

#define T Book // we have generics at home
struct Node2 {
  T value;
  Node2 *left;
  Node2 *right;
};

Node2 *node__add(T data, Node2 *left, Node2 *right) {
  Node2 *n = new Node2;
  n->value = data;
  n->left = left;
  n->right = right;

  return n;
}

void node__free(Node2 *node) {
  Node2 *current = node;
  delete current;

  if (node->right == nullptr) {
    return;
  }

  node__free(node->right);
}

int _node__length_rec(Node2 *node, int current_index) {
  if (node->right == NULL) {
    return current_index + 1;
  }

  return _node__length_rec(node->right, current_index + 1);
}

int node__length(Node2 *node) { return _node__length_rec(node, 0); }

/*// NOTE: only uncomment if T is not a struct*/
/*// TODO: don't forget to free node->next to avoid memory leak*/
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

Node2 *node__insert_first(Node2 *node, T datawith) {
  Node2 *new_node = node__add(datawith, nullptr, node);

  if (node != nullptr) {
    node->left = new_node;
  }

  return new_node;
}

Node2 *_node__insert_last_rec(Node2 *node, Node2 *head, T datawith) {
  if (node == nullptr) {
    return node__add(datawith, node, nullptr);
  }

  if (node->right != nullptr)
    return _node__insert_last_rec(node->right, head, datawith);

  Node2 *to_free = node->right;
  node->right = node__add(datawith, node, nullptr);

  delete to_free;

  return head;
}

Node2 *node__insert_last(Node2 *node, T datawith) {
  return _node__insert_last_rec(node, node, datawith);
}

Node2 *_node__insert_by_index_rec(Node2 *node, Node2 *head, int at_index,
                                  int current, T datawith) {
  if (current != at_index)
    return _node__insert_by_index_rec(node->right, node, at_index, current + 1,
                                      datawith);

  Node2 *to_free = node->right;
  node->right = node__add(datawith, node->right, node->right->right);

  delete to_free;

  return head;
}

Node2 *node__insert_by_index(Node2 *node, int at_index, T datawith) {
  return _node__insert_by_index_rec(node, node, at_index, 0, datawith);
}

Node2 *node__delete_first(Node2 *node) { return node->right; }

Node2 *_node__delete_last_rec(Node2 *node, Node2 *head) {
  if (node->right->right != NULL)
    return _node__delete_last_rec(node->right, head);

  node->right = NULL;

  return head;
}

Node2 *node__delete_last(Node2 *node) {
  return _node__delete_last_rec(node, node);
}

Node2 *_node__delete_by_index_rec(Node2 *node, Node2 *head, int at_index,
                                  int current) {
  if (at_index == node__length(node) - 1) {
    return node__delete_last(node);
  }

  if (at_index == 0) {
    return node__delete_first(node);
  }

  if (current + 1 != at_index)
    return _node__delete_by_index_rec(node->right, node, at_index, current + 1);

  node->right = node->right->right;

  return head;
}

Node2 *node__delete_by_index(Node2 *node, int at_index) {
  return _node__delete_by_index_rec(node, node, at_index, 0);
}

void node_book__print(Node2 *node) {
  if (node == nullptr) {
    cout << "Rak kosong." << endl;
    return;
  }

  cout << "===" << endl;
  cout << "Judul: " << node->value.title << endl;
  cout << "Penulis: " << node->value.author << endl << endl;

  if (node->right == nullptr) {
    return;
  }

  node_book__print(node->right);
}

Node2 *_node__delete_by_address_req(Node2 *node, Node2 *head, Node2 *target) {
  if (node == nullptr) {
    return nullptr;
  }

  if (node->right == nullptr) {
    return head;
  }

  if (node->right == target) {
    Node2 *to_delete = node->right;
    node->right = node->right->right;

    delete to_delete;
    return head;
  }

  return _node__delete_by_address_req(node->right, head, target);
}

Node2 *node__delete_by_address(Node2 *node, Node2 *target) {
  return _node__delete_by_address_req(node, node, target);
}

Node2 *node_book__find_by_title(Node2 *node, string title) {
  if (node == nullptr) {
    return nullptr;
  }

  if (node->value.title == title) {
    return node;
  }

  return node_book__find_by_title(node->right, title);
}

string ALERT;
int CHOICE_INPUT;

Node2 *BOOKSHELF = nullptr;

void page__utama();

void page__tambah_buku_depan() {
  system("clear");
  string title, author;
  ALERT = "";

  do {
    system("clear");
    if (ALERT != "") {
      cout << ALERT << endl;
    }

    cout << "Judul Buku: ";
    cin.ignore();
    getline(cin, title);

    cout << "Penulis: ";
    cin.ignore();
    getline(cin, author);

    if (title == "" || author == "") {
      ALERT = "tolong cantumkan judul atau penulis!";
      system("clear");
    }

  } while (title == "" && author == "");
  ALERT = "";

  BOOKSHELF = node__insert_first(BOOKSHELF, Book{title, author});

  cout << "Berhasil menambahkan buku berjudul " << title
       << " yang ditulis oleh " << author << "ke depan rak" << endl;
  cout << "tekan tombol sembarang untuk kembali ke halaman awal..." << endl;

  getchar();

  page__utama();
}

void page__tambah_buku_belakang() {
  system("clear");
  string title, author;
  ALERT = "";

  do {
    if (ALERT != "") {
      cout << ALERT << endl << endl;
    }
    ALERT = "";

    cout << "Judul Buku: ";
    cin.ignore();
    getline(cin, title);

    cout << "Penulis: ";
    cin.ignore();
    getline(cin, author);

    if (title == "" || author == "") {
      ALERT = "tolong cantumkan judul atau penulis!";
      system("clear");
    }

  } while (title == "" && author == "");
  ALERT = "";

  BOOKSHELF = node__insert_last(BOOKSHELF, Book{title, author});

  cout << "Berhasil menambahkan buku berjudul " << title
       << " yang ditulis oleh " << author << "ke belakang rak" << endl;
  cout << "tekan tombol sembarang untuk kembali ke halaman awal..." << endl;

  getchar();

  page__utama();
}

void page__hapus_buku() {
  system("clear");
  string title;

  cout << "masukkan judul buku yang ingin dihapus: ";
  cin.ignore();
  getline(cin, title);

  Node2 *target_node = node_book__find_by_title(BOOKSHELF, title);

  if (target_node == nullptr) {
    cout << "buku tidak ditemukkan" << endl;
  } else {
    BOOKSHELF = node__delete_by_address(BOOKSHELF, target_node);

    cout << "Buku dengan judul " << title << "berhasil dihapus" << endl;
  }

  cout << "tekan sembarang tombol untuk kembali ke halaman awal" << endl;
  getchar();

  page__utama();
}

void page__tampilkan_buku() {
  system("clear");

  cout << "Koleksi buku anda: " << endl;

  node_book__print(BOOKSHELF);

  cout << "Tekan tombol sembarang untuk kembali ke halaman awal..." << endl;
  getchar();

  page__utama();
}

void page__utama() {
  do {
    system("clear");

    if (ALERT != "") {
      cout << ALERT << endl << endl;
    }

    ALERT = "";

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
      page__tampilkan_buku();
      break;
    case 5:
      cout << "bye bye." << endl;
      system("exit");
      break;
    default:
      ALERT = "Pilihan tidak valid. Silahkan masukkan no 1-5!!";

      break;
    }
  } while (ALERT != "");
}

int main() {
  page__utama();
  node__free(BOOKSHELF);
}
