#include "nbtrees.h"
 
void create_tree(isi_tree R){
    // Initialize all nodes to empty
    int i;
    for (i = 0; i <= jml_maks; i++) {
        R[i].info = node_default;
        R[i].ps_fs = Nil;
        R[i].ps_nb = Nil;
    }
}

boolean is_empty_tree(isi_tree R){
    return (R[0].ps_fs == Nil);
}

// =============================================
// =========== TRANVERSAL FUNCTION =============
// =============================================

void pre_order(isi_tree R){
    pre_order_recursive(R, 0);
}
void pre_order_recursive(isi_tree R, address P){
    if (P != Nil){
        printf("%c ", R[P].info);
        pre_order_recursive(R, R[P].ps_fs);
        pre_order_recursive(R, R[P].ps_nb);
    }
}

void post_order(isi_tree R){
    post_order_recursive(R, 0);
}
void post_order_recursive(isi_tree R, address P){
    if (P != Nil){
        post_order_recursive(R, R[P].ps_fs);
        printf("%c ", R[P].info);
        post_order_recursive(R, R[P].ps_nb);
    }
}

void in_order(isi_tree R){
    in_order_recursive(R, 0);
}

void in_order_recursive(isi_tree R, address P){
    if (P != Nil){
        in_order_recursive(R, R[P].ps_fs);
        printf("%c ", R[P].info);
        in_order_recursive(R, R[P].ps_nb);
    }
}

void level_order(isi_tree R){
    printf("[ ");
    int i;
    for (i = 0; i <= jml_maks; i++) {
        if (R[i].info != node_default) {
            printf("%c ", R[i].info);
        }
    }
    printf("]");
}

// =============================================
// =========== INSERTION FUNCTION ==============
// =============================================

void insert_node(isi_tree R, infotype X, infotype parent, int mode) {
    int index;
    address idx_parent = 0; // bila belum ditemukan nilai defaultnya 0
    
    // Cari indeks parent
    if (parent != node_default) {
        index = 1; 
        while (index <= jml_maks && idx_parent == 0) {
            if (R[index].info == parent) {
                idx_parent = index;
                break; // keluar ketika parent ditemukan
            }
            index++;
        }
    }
    
    // Jika parent ditemukan atau insert ke root
    if (idx_parent != 0 || parent == node_default) {
        // Cari slot kosong untuk node baru
        index = 1;
        while (index <= jml_maks && R[index].info != node_default) {
            index++;
        }
        
        if (index <= jml_maks) {
            // Set informasi node baru
            R[index].info = X;
            R[index].ps_fs = Nil;
            R[index].ps_nb = Nil;
            
            // Tentukan posisi insert berdasarkan mode
            if (parent == node_default) {
                // Insert sebagai root
                R[0].ps_fs = index;
                printf("Root berhasil dibuat: %c pada indeks %d\n", X, index);
            } else if (mode == kebawah) {
                // Insert sebagai first child
                if (R[idx_parent].ps_fs == Nil) {
                    R[idx_parent].ps_fs = index;
                    printf("Node %c berhasil dibuat sebagai first child dari %c\n", X, parent);
                } else {
                    // Cari last next brother dari first child
                    address sibling = R[idx_parent].ps_fs;
                    while (R[sibling].ps_nb != Nil) {
                        sibling = R[sibling].ps_nb;
                    }
                    R[sibling].ps_nb = index;
                    printf("Node %c berhasil dibuat sebagai next brother dari first child %c\n", X, R[sibling].info);
                }
            } else if (mode == kekanan) {
                // Insert sebagai next brother
                if (R[idx_parent].ps_nb == Nil) {
                    R[idx_parent].ps_nb = index;
                    printf("Node %c berhasil dibuat sebagai next brother dari %c\n", X, parent);
                } else {
                    address sibling = R[idx_parent].ps_nb;
                    while (R[sibling].ps_nb != Nil) {
                        sibling = R[sibling].ps_nb;
                    }
                    R[sibling].ps_nb = index;
                    printf("Node %c berhasil dibuat sebagai last next brother dari %c\n", X, parent);
                }
            }
        } else {
            printf("Tree penuh, tidak bisa menambahkan node.\n");
        }
    } else {
        printf("Parent '%c' tidak ditemukan.\n", parent);
    }
}

void insert_some_node(isi_tree R) {
    int n, i;
    infotype X, parent;
    int mode;
    
    printf("Masukkan jumlah node yang akan ditambahkan: ");
    scanf("%d", &n);
    getchar(); // Mengambil karakter newline
    
    for (i = 0; i < n; i++) {
        printf("Node ke-%d:\n", i+1);
        printf("Info: ");
        scanf("%c", &X);
        getchar();
        
        printf("Parent ('0' untuk root): ");
        scanf("%c", &parent);
        getchar();
        
        if (parent == '0') parent = node_default;
        
        printf("Mode (1:kebawah, 3:kekanan): ");
        scanf("%d", &mode);
        getchar();
        
        insert_node(R, X, parent, mode);
    }
}

void delete_node(isi_tree R, infotype X) {
    int i = 1;
    address idx_node = 0;
    
    // Cari node yang akan dihapus
    while (i <= jml_maks && idx_node == 0) {
        if (R[i].info == X) {
            idx_node = i;
        }
        i++;
    }
    
    if (idx_node == 0) {
        printf("Node tidak ditemukan.\n");
        return;
    }
    
    // Cari parent dari node
    address parent = 0;
    for (i = 0; i <= jml_maks; i++) {
        // Cek apakah node adalah first child
        if (R[i].ps_fs == idx_node) {
            parent = i;
            // Update pointer first child ke next brother dari node
            R[i].ps_fs = R[idx_node].ps_nb;
            break;
        } 
        // Cek apakah node adalah next brother
        else if (R[i].ps_fs != Nil) {
            address sibling = R[i].ps_fs;
            while (sibling != Nil && R[sibling].ps_nb != idx_node) {
                sibling = R[sibling].ps_nb;
            }
            
            if (sibling != Nil && R[sibling].ps_nb == idx_node) {
                parent = i;
                // Update pointer next brother
                R[sibling].ps_nb = R[idx_node].ps_nb;
                break;
            }
        }
    }
    
    // Hapus subtree dari node (semua children dan next brothers dari children)
    if (R[idx_node].ps_fs != Nil) {
        delete_subtree(R, R[idx_node].ps_fs);
    }
    
    // Hapus node
    R[idx_node].info = node_default;
    R[idx_node].ps_fs = Nil;
    R[idx_node].ps_nb = Nil;
}

void delete_level(isi_tree R, int level) {
    int i;
    
    for (i = 1; i <= jml_maks; i++) {
        if (R[i].info != node_default && Level(R, R[i].info) == level) {
            delete_node(R, R[i].info);
        }
    }
}

void delete_subtree(isi_tree R, address root){
    if (root != Nil) {

        if (R[root].ps_fs != Nil) {
            // Hapus semua first child
            delete_subtree(R, R[root].ps_fs);
        }
        if (R[root].ps_nb != Nil) {
            // Hapus semua next brother
            delete_subtree(R, R[root].ps_nb);
        }

        // Hapus node saat ini
        R[root].info = node_default;
        R[root].ps_fs = Nil;
        R[root].ps_nb = Nil;
    }
}

// =============================================
// =========== ADDITIONAL FUNCTION =============
// =============================================

void print_tree(isi_tree R) {
    if (is_empty_tree(R)) {
        printf("Tree kosong\n");
    } else {
        print_tree_rec(R, R[0].ps_fs, 0);
    }
}

// Fungsi rekursif untuk mencetak tree dengan indentasi
void print_tree_rec(isi_tree R, address root, int level) {
    int i;
    
    if (root != Nil) {
        // Cetak indentasi
        for (i = 0; i < level; i++) {
            printf("  ");
        }
        
        // Cetak info node
        printf("%c\n", R[root].info);
        
        // Cetak first child
        print_tree_rec(R, R[root].ps_fs, level + 1);
        
        // Cetak next next brother
        print_tree_rec(R, R[root].ps_nb, level);
    }
}

void print_tree_fa(isi_tree R) {
    if (is_empty_tree(R)) {
        printf("Tree kosong\n");
    } else {
        // Cetak info dan indeks setiap node yang valid
        int i;
        for (i = 0; i <= jml_maks; i++) {
            if (R[i].info != node_default) {
                printf("Node[%d]: %c", i, R[i].info);
                if (R[i].ps_fs != Nil) {
                    printf(", First Child: %c", R[R[i].ps_fs].info);
                }
                if (R[i].ps_nb != Nil) {
                    printf(", Next Brother: %c", R[R[i].ps_nb].info);
                }
                printf("\n");
            }
        }
    }
}

void print_tree_detailed(isi_tree R) {
    if (is_empty_tree(R)) {
        printf("Tree kosong\n");
        return;
    }

    printf("\nSeluruh Node pada Non Binary Tree:\n\n");
    int i;
    for (i = 1; i <= jml_maks; i++) {
        if (R[i].info != node_default) {
            int j, parent = 0;
            for (j = 0; j <= jml_maks; j++) {
                if (R[j].ps_fs == i) {
                    parent = j;
                    break;
                }
                address sibling = R[j].ps_fs;
                while (sibling != Nil) {
                    if (R[sibling].ps_nb == i) {
                        parent = j;
                        break;
                    }
                    sibling = R[sibling].ps_nb;
                }
            }

            printf("--> Indeks ke-%d\n", i);
            printf("-------------------------------------\n");
            printf("info array ke %d           : %c\n", i, R[i].info);
            printf("first son array ke %d      : %d\n", i, R[i].ps_fs);
            printf("next brother array ke %d   : %d\n", i, R[i].ps_nb);
            printf("parent array ke %d         : %d\n", i, parent);
            printf("-------------------------------------\n\n");
        }
    }
}

boolean search(isi_tree R, infotype X) {
    int i;
    
    for (i = 1; i <= jml_maks; i++) {
        if (R[i].info == X && R[i].info != node_default) {
            return true;
        }
    }

    return false;
}

int nb_Elmt(isi_tree R) {
    int count = 0;
    int i;
    for (i = 1; i <= jml_maks; i++) {
        if (R[i].info != node_default) {
            count++;
        }
    }
    return count;
}

int nb_Daun(isi_tree R) {
    int count = 0;
    int i;
    for (i = 1; i <= jml_maks; i++) {
        if (R[i].info != node_default && R[i].ps_fs == Nil) {
            count++;
        }
    }
    return count;
}

// Fungsi helper untuk mencari level dari suatu node
int find_level(isi_tree R, address root, infotype X, int level) {
    if (root == Nil) return -1;
    
    // Jika node ditemukan
    if (R[root].info == X) return level;
    
    // Cari di first child
    int found_level = find_level(R, R[root].ps_fs, X, level + 1);
    if (found_level != -1) return found_level;
    
    // Jika tidak ditemukan di first child, cari di next brother (pada level yang sama)
    return find_level(R, R[root].ps_nb, X, level);
}

int Level(isi_tree R, infotype X) {
    // Mulai pencarian dari root
    return find_level(R, R[0].ps_fs, X, 0);
}

int Depth(isi_tree R) {
    int max_depth = 0;
    int i;
    for (i = 1; i <= jml_maks; i++) {
        if (R[i].info != node_default) {
            int level = Level(R, R[i].info);
            if (level > max_depth) {
                max_depth = level;
            }
        }
    }
    return max_depth;
}

// Fungsi helper untuk menghitung tinggi dari suatu node
int height_recursive(isi_tree R, address root) {
    if (root == Nil) return 0;
    
    // Cari tinggi maksimum di antara semua children
    int max_height = 0;
    address child = R[root].ps_fs;
    
    // Iterasi melalui semua children
    while (child != Nil) {
        int child_height = height_recursive(R, child);
        if (child_height > max_height) {
            max_height = child_height;
        }
        child = R[child].ps_nb;
    }
    
    // Tinggi node adalah 1 (dirinya sendiri) + tinggi maksimum dari children
    return 1 + max_height;
}

int height(isi_tree R, address P) {
    if (P == Nil) return 0;
    return height_recursive(R, P);
}

int Max(infotype Data1, infotype Data2) {
    return (Data1 > Data2) ? Data1 : Data2;
}
