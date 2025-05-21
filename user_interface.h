#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H
#include "windows.h"
#include "nbtrees.h"
#include "boolean.h"

HANDLE Out();

void gotoxy(int x, int y);

//Description: Fungsi untuk mencetak tree secara vertikal
//            dengan parent di ATAS dan anak di BAWAH   
void cetak_tree_VERTIKAL(isi_tree R, int x, int y);

//Description: Fungsi untuk mencetak tree secara horizontal
//              dengan parent di KANAN dan anak di KIRI
void cetak_tree_HORIZON(isi_tree R, int x, int y);

//Description: Fungsi untuk mencetak tree secara ARRAY
//              dengan parent di KANAN dan anak di KIRI
void cetak_tree_ARRAY(isi_tree R, int x, int y);

//Description: Fungsi untuk mencetak suatu level dari tree
void print_level(isi_tree R, int level);

#endif // USER_INTERFACE_H
