#include "test_case.h"
#include "controller.h"


int main() {
	for(;;){
		system("cls");
		int pilihan;
		printf("====== Pilih proses ======\n");
		printf("1. mulai test_case\n");
		printf("2. jalankan_menu\n");
		printf("3. quit\n");
		printf("Masukan Pilihan:");
		scanf("%d", &pilihan);
	
		switch (pilihan)
		{
		case 1:
			system("cls");
			run_test_case();
			break;
		case 2:
			system("cls");
			run_menu();
			break;
		case 3:
			system("cls");
			return;
		default:
			printf ("pilihan yang anda masukan salah");
			break;
		}
	}

	return 0;
}
