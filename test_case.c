#include "test_case.h"

void run_test_case(){
	printf("===== TEST SUITE UNTUK ADT NON-BINARY TREE =====\n");
    
    // Jalankan test dasar
    test_create_tree();
    test_insert_node();
    test_simple_tree();
}

// Fungsi untuk mencetak header test
void print_test_header(const char* test_name) {
    printf("\n");
    printf("==================================\n");
    printf("= TEST: %s\n", test_name);
    printf("==================================\n");
}

// Fungsi untuk mencetak hasil test
void test_result(const char* test_name, bool success) {
    printf("Test %s: %s\n", test_name, success ? "SUCCESS" : "FAILED");
}

// Test untuk create_tree dan is_empty_tree
void test_create_tree() {
    print_test_header("CREATE TREE");
    
    isi_tree tree;
    create_tree(tree);
    
    bool is_empty = is_empty_tree(tree);
    printf("Tree kosong: %s\n", is_empty ? "Ya" : "Tidak");
    
    // Cetak isi awal array untuk debugging
    printf("Isi array setelah create_tree:\n");
    int i;
    for (i = 0; i <= 5; i++) {
        printf("tree[%d].info = %c, ps_fs = %d, ps_nb = %d\n", 
               i, tree[i].info, tree[i].ps_fs, tree[i].ps_nb);
    }
    
    test_result("Create Tree", tree[0].info == node_default && tree[0].ps_fs == Nil && tree[0].ps_nb == Nil);
}

// Test untuk insert_node
void test_insert_node() {
    print_test_header("INSERT NODE");
    
    isi_tree tree;
    create_tree(tree);
    
    // Insert root
    printf("Mencoba insert root 'A'...\n");
    insert_node(tree, 'A', node_default, kebawah);
    
    // Cetak status tree setelah insert root
    printf("Status tree setelah insert root:\n");
    printf("Root pointer (tree[0].ps_fs): %d\n", tree[0].ps_fs);
    if (tree[0].ps_fs != Nil) {
        printf("Root node (tree[%d].info): %c\n", tree[0].ps_fs, tree[tree[0].ps_fs].info);
    }
    
    // Insert first child
    printf("\nMencoba insert child 'B' ke 'A'...\n");
    insert_node(tree, 'B', 'A', kebawah);
    
    // Insert sibling
    printf("\nMencoba insert sibling 'C' di bawah 'A'...\n");
    insert_node(tree, 'C', 'B', kebawah);
    
    // Insert child dari B
    printf("\nMencoba insert child 'D' ke 'B'...\n");
    insert_node(tree, 'D', 'B', kebawah);
    
    printf("\nTree structure:\n");
    print_tree(tree);
    printf("\nArray representation:\n");
    print_tree_fa(tree);
    
    bool inserted_root = (tree[0].ps_fs != Nil && tree[tree[0].ps_fs].info == 'A');
    bool inserted_child = false;
    
    // Verify B is a child of A
    if (inserted_root) {
        address a_idx = tree[0].ps_fs;
        if (tree[a_idx].ps_fs != Nil) {
            inserted_child = (tree[tree[a_idx].ps_fs].info == 'B');
        }
    }
    
    test_result("Insert Node", inserted_root && inserted_child);
}

// Test sederhana
void test_simple_tree() {
    print_test_header("SIMPLE TREE");
    
    isi_tree tree;
    create_tree(tree);
    
    // Mencoba membuat tree sederhana
    printf("Membuat tree sederhana...\n");
    insert_node(tree, 'R', node_default, kebawah);
    insert_node(tree, 'A', 'R', kebawah);
    insert_node(tree, 'B', 'R', kebawah);
    insert_node(tree, 'C', 'A', kebawah);
    
    printf("\nTree structure:\n");
    print_tree(tree);
    
    printf("\nDetailed tree representation:\n");
    print_tree_fa(tree);
    
    printf("\nPre-order: ");
    pre_order(tree);
    printf("\n");
    
    printf("Post-order: ");
    post_order(tree);
    printf("\n");
    
    printf("In-order: ");
    in_order(tree);
    printf("\n");
    
    printf("Level-order: ");
    level_order(tree);
    printf("\n");
    
    int count = nb_Elmt(tree);
    int leaves = nb_Daun(tree);
    int depth = Depth(tree);
    
    printf("\nJumlah node: %d\n", count);
    printf("Jumlah daun: %d\n", leaves);
    printf("Depth: %d\n", depth);
    
    printf("\nLevel dari 'R': %d\n", Level(tree, 'R'));
    printf("Level dari 'A': %d\n", Level(tree, 'A'));
    printf("Level dari 'C': %d\n", Level(tree, 'C'));
    
    test_result("Simple Tree", count == 4 && leaves == 2 && depth == 2);
}

