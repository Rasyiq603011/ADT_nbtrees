#include "controller.h"
#include "nbtrees.h"
#include "user_interface.h"
#include <stdio.h>

void run_menu() {
    isi_tree tree;
    create_tree(tree);
    int choice;
    infotype node, node1, node2;

    do {
        system("cls");
        display_menu();
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("\nPre-order Traversal: ");
                pre_order(tree);
                printf("\n");
                break;
            case 2:
                printf("\nIn-order Traversal: ");
                in_order(tree);
                printf("\n");
                break;
            case 3:
                printf("\nPost-order Traversal: ");
                post_order(tree);
                printf("\n");
                break;
            case 4:
                printf("\nLevel-order Traversal: ");
                level_order(tree);
                printf("\n");
                break;
            case 5:
                print_tree_detailed(tree);
                break;
            case 6:
                printf("Masukkan node yang dicari: ");
                scanf("%c", &node);
                getchar();
                printf("Node %c %s dalam tree\n", node, search(tree, node) ? "ditemukan" : "tidak ditemukan");
                break;
            case 7:
                printf("\nJumlah daun: %d\n", nb_Daun(tree));
                break;
            case 8:
                printf("Masukkan node untuk mencari level: ");
                scanf("%c", &node);
                getchar();
                int level = Level(tree, node);
                if (level != -1)
                    printf("Level dari node %c adalah: %d\n", node, level);
                else
                    printf("Node %c tidak ditemukan\n", node);
                break;
            case 9:
                printf("\nKedalaman tree: %d\n", Depth(tree));
                break;
            case 10:
                printf("Masukkan node pertama: ");
                scanf("%c", &node1);
                getchar();
                printf("Masukkan node kedua: ");
                scanf("%c", &node2);
                getchar();
                printf("Perbandingan: %c %s %c\n", node1, node1 > node2 ? ">" : (node1 < node2 ? "<" : "="), node2);
                break;
            case 11:
                printf("Keluar dari program\n");
                return;
            default:
                printf("Pilihan tidak valid!\n");
        }

        if (choice != 11) {
            printf("\nIngin menambahkan node? (y/n): ");
            char add_node;
            scanf("%c", &add_node);
            getchar();
            if (add_node == 'y' || add_node == 'Y') {
                insert_some_node(tree);
            }
        }

    } while (choice != 11);
}
