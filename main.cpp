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
struct Node {
  T value;
  Node *next;
};

Node *node__add(T data, Node *next) {
  Node *n = new Node;
  n->value = data;
  n->next = next;

  return n;
}

void node__free(Node *node) {
  Node *current = node;
  delete current;

  if (node->next == nullptr) {
    return;
  }

  node__free(node->next);
}

int _node__length_rec(Node *node, int current_index) {
  if (node->next == NULL) {
    return current_index + 1;
  }

  return _node__length_rec(node->next, current_index + 1);
}

int node__length(Node *node) { return _node__length_rec(node, 0); }

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

Node *node__insert_first(Node *node, T datawith) {
  return node__add(datawith, node);
}

Node *_node__insert_last_rec(Node *node, Node *head, T datawith) {
  if (node == nullptr) {
    return node__add(datawith, nullptr);
  }

  if (node->next != nullptr)
    return _node__insert_last_rec(node->next, head, datawith);

  Node *to_free = node->next;
  node->next = node__add(datawith, nullptr);

  delete to_free;

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

  delete to_free;

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

void node_book__print(Node *node) {
  if (node == nullptr) {
    cout << "Rak kosong." << endl;
    return;
  }

  cout << "===" << endl;
  cout << "Judul: " << node->value.title << endl;
  cout << "Penulis: " << node->value.author << endl << endl;

  if (node->next == nullptr) {
    return;
  }

  node_book__print(node->next);
}

Node *_node__delete_by_address_req(Node *node, Node *head, Node *target) {
  if (node == nullptr) {
    return nullptr;
  }

  if (node->next == nullptr) {
    return head;
  }

  if (node->next == target) {
    Node *to_delete = node->next;
    node->next = node->next->next;

    delete to_delete;
    return head;
  }

  return _node__delete_by_address_req(node->next, head, target);
}

Node *node__delete_by_address(Node *node, Node *target) {
  return _node__delete_by_address_req(node, node, target);
}

Node *node_book__find_by_title(Node *node, string title) {
  if (node == nullptr) {
    return nullptr;
  }

  if (node->value.title == title) {
    return node;
  }

  return node_book__find_by_title(node->next, title);
}

string ALERT;
int CHOICE_INPUT;

Node *BOOKSHELF = nullptr;

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

  Node *target_node = node_book__find_by_title(BOOKSHELF, title);

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
