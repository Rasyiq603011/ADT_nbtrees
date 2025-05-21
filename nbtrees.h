#ifndef NBTREES_H
#define NBTREES_H
#include <stdio.h>
#include "boolean.h"

// Maksimal node yang dapat ditampung dalam array
#define jml_maks 20

#define node_default '@'
#define kebawah 1
#define keatas 2
#define kekanan 3
#define Nil 0

// =============================================
// ========= DEFINISI DTRUKTUR DATA ============
// =============================================

typedef char infotype;
typedef int address;
typedef struct nbtrees
{
    infotype info;
    address ps_fs;
    address ps_nb;
}nbtree;

typedef nbtree isi_tree[jml_maks+1];

// =============================================
// ============== MAIN FUNCTION ================
// =============================================

// IS: R mungkin kosong 
// FS: membuat tree dengan node pertama adalah root
// DESCRIPTION: Membuat danmenginisialiasi tree
//              dengan node pertama adalah root
void create_tree(isi_tree R);


// IS: R mungkin kosong
// FS: Mengembalikan true jika tree kosong
//      dan false jika tree tidak kosong
// DESCRIPTION: 
boolean is_empty_tree(isi_tree R);

// =============================================
// =========== TRANVERSAL FUNCTION =============
// =============================================

// IS: R mungkin kosong
// FS: Menampilkan isi tree dengan pre-order
// DESCRIPTION: 
void pre_order(isi_tree R);

void pre_order_recursive(isi_tree R, address P);

// IS: R mungkin kosong
// FS: Menampilkan isi tree dengan post-order
// DESCRIPTION: 
void post_order(isi_tree R);

void post_order_recursive(isi_tree R, address P);

// IS: R mungkin kosong
// FS: Menampilkan isi tree dengan in-order
// DESCRIPTION: 
void in_order(isi_tree R);

void in_order_recursive(isi_tree R, address P);

// IS: R mungkin kosong
// FS: Menampilkan isi tree dengan level-order
// DESCRIPTION: 
void level_order(isi_tree R);

// =============================================
// =========== INSERTION FUNCTION ==============
// =============================================

// IS: R mungkin kosong
// FS: Menambahkan node baru ke dalam tree
// DESCRIPTION: function akan menambahkan node baru ke dalam tree
//              dengan parent yang ditentukan
//              jika parent sudah punya first son, maka node baru
//              akan menjadi next brother dari first son
void insert_node(isi_tree R, infotype X, infotype parent, int mode);

// IS: R mungkin kosong
// FS: Menambahkan beberapa node baru ke dalam tree
// DESCRIPTION: function akan melakukan looping untuk menambahkan
//              beberapa node baru ke dalam tree
void insert_some_node(isi_tree R);

// =============================================
// ============ DELETION FUNCTION ==============
// =============================================

// IS: R mungkin kosong dan node yang ingin dihapus belum pasti ada
// FS: Menghapus node dengan informasi X dan semua anaknya dari tree
// DESCRIPTION: function akan menghapus node dengan informasi X dari tree
void delete_node(isi_tree R, infotype X);

// IS: R mungkin kosong dan level yang ingin dihapus belum pasti ada
// FS: Menghapus semua node pada level tertentu dari tree
// DESCRIPTION: function akan menghapus semua node pada level tertentu
void delete_level(isi_tree R, int level);

// IS: R mungkin kosong dan root adalah alamat dari subtree yang ingin dihapus
// FS: Menghapus semua node dalam subtree dengan root yang diberikan
// DESCRIPTION: function akan menghapus seluruh subtree dimulai dari root
void delete_subtree(isi_tree R, address root);


// =============================================
// =========== ADDITIONAL FUNCTION =============
// =============================================

// IS: R mungkin kosong
// FS: menampilkan isi tree dengan indentasi
// DESCRIPTION: function akan mencetak isi tree dengan indentasi
void print_tree(isi_tree P);

// Fungsi helper untuk print_tree
void print_tree_rec(isi_tree R, address root, int level);

// IS: R mungkin kosong
// FS: menampilkan isi tree dengan format first child dan next brother
// DESCRIPTION: function akan mencetak isi tree dengan informasi first child dan next brother
void print_tree_fa(isi_tree R);

// IS: R mungkin kosong
// FS: Mengembalikan true jika ada node dari P yang bernilai X
// DESCRIPTION: Mengirimkan true jika ada node dari P yang bernilai X
boolean search(isi_tree R, infotype X);

// IS: R mungkin kosong
// FS: Mengembalikan banyak elemen (node) di pohon non biner P
int nb_Elmt(isi_tree R);

// IS: R mungkin kosong
// FS: Mengembalikan banyak daun (node) pohon non biner R
int nb_Daun (isi_tree R);

// Fungsi helper untuk Level()
int find_level(isi_tree R, address root, infotype X, int level);

// IS: R mungkin kosong
// FS: Mengembalikan level dari node X yang merupakan salah satu simpul
int Level(isi_tree R, infotype X);

// IS: R mungkin kosong
// FS: Mengembalikan tinggi dari pohon
// DESCRIPTION: Pohon Biner mungkin Kosong, mengirimkan 'depth' yaitu tinggi dari Pohon
int Depth(isi_tree R);

// Fungsi helper untuk height()
int height_recursive(isi_tree R, address root);

// IS: R mungkin kosong
// FS: Mengembalikan tinggi dari node P
// DESCRIPTION: Pohon Biner mungkin Kosong, mengirimkan 'height' yaitu tinggi dari node P
int height(isi_tree R, address P);

// Mengambil nilai maksimum dari 2 data
int Max(infotype Data1, infotype Data2);

#endif
