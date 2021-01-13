#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
void clear(); 
int Menu();
int main() {
    Menu();
	return 0 ;
}
int Menu() {
	char c = "g"; 
	while(c!= 113 ) {
		clear() ;
		printf("Bonjour !!\n");
		printf("Choisissez nentre : \n");
		printf("1. Gestion adherant.\n");
		printf("2. Gestion livres.\n");
		printf("3. Gestion Emprunt.\n");
		c = getchar();
		//printf("%c" , c);
		switch(c) {
			case 49:
				printf("adherant\n");
				break;
			case 50: 
				printf("livres\n");
				break;
			case 51:
				printf("emprunt\n");
				break;
			default : 
				printf("rien\n");
		}
	}
	return 0 ;
}
void clear(){
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}
