#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define COUNT_SEETS 12

struct Place{
	int identifi;
	int reserved;
	char name[40];
	char surname[40];
	
};
//This method compare two strings
int comparison(char name1[], char name2[]){
	for (int i = 0; i < fmin(strlen(name1), strlen(name2)); i++){
		if (name1[i] > name2[i])
			return 1;
		else if (name1[i] == name2[i])
			continue;
		else
			return -1;		
	}

	if (strlen(name1) == strlen(name2))
		return 0;
	else if (strlen(name1) > strlen(name2))
		return -1;
	else
		return 1;
}

void startInitial(struct Place places[]){
	for (int i = 0; i < COUNT_SEETS; i++){
		places[i].identifi = i;
		places[i].reserved = 0;
	}
}

int getcountAvailSeets(struct Place places[])
{
	int count = 0;
	for (int i = 0; i < COUNT_SEETS; i++){
		if (places[i].reserved == 0)
			count++;
	}
	printf("\n");
	return count;
}


void showReservdSeetsInOrd(struct Place places[]){
	struct Place resPlaces[COUNT_SEETS];
	int temp = 0;
	for (int i = 0; i < COUNT_SEETS; i++){
		if (places[i].reserved == 1)
			resPlaces[temp++] = places[i];
	}

	struct Place tempPlace;
	for (int i = 0; i < temp; i++){
		for (int j = i + 1; j < temp; j++){
			if (comparison(resPlaces[i].name, resPlaces[j].name) == 1){
				tempPlace = resPlaces[i];
				resPlaces[i] = resPlaces[j];
				resPlaces[j] = tempPlace;
			}				
		}
	}

	if (temp != 0){
		for (int i = 0; i < temp; i++)
			printf("Name: %s, Surname: %s, ID: %d \n", resPlaces[i].name, resPlaces[i].surname, resPlaces[i].identifi);
	}
	else
		printf("There are no reserved seets!\n");

	printf("\n");
}


void showAvailSeets(struct Place places[])
{
	for (int i = 0; i < COUNT_SEETS; i++){
		if (places[i].reserved == 0){
			printf("Seet id: %d \n", places[i].identifi);
		}
	}
	printf("\n");
}

void bookPlace(struct Place places[]){
	int id;
	while (1)
	{		
		char temp;
		printf("Input the id of seet (or -1 to quit): ");
		scanf("%d", &id);
		getchar();
		if (id == -1)
			return;
		if (id < 0 || id >= 12){
			printf("Invalid id, try again\n");
			continue;
		}
		if (places[id].reserved == 1){
			printf("This seet is already taken, try again");
			continue;
		}

		printf("Input your name: ");
		scanf("%s", places[id].name);
		printf("Input your surname: ");
		scanf("%s", places[id].surname);
		getchar();
		places[id].reserved = 1;
		break;
	}
}

void remResorv(struct Place places[]){
	int nomber;
	while (1){
		char temp;
		printf("Input the nomber of place (or -1 to quit): ");
		scanf("%d", &nomber);
		scanf("%c", &temp);
		if (nomber == -1)
			return;
		if (nomber < 0 || nomber >= COUNT_SEETS){
			printf("Invalid nomber, try again!\n");
			continue;
		}
		if (places[nomber].reserved == 1){
			places[nomber].reserved = 0;
			printf("SUCCESSFULLY\n");
			return;
		}
		else{
			printf("This seet is already free!\n");
			return;
		}
		printf("\n");
	}
}



int main(){
	char comand;
	struct Place places[COUNT_SEETS];
	int count;
	startInitial(places);
	FILE *output = NULL;//Tis is file, which we load and rewrite
	output = fopen("file.bin", "rb");
	if (output == NULL) {
		printf("Error opening file");
		startInitial(places);
	}
	else{
		fread(places, sizeof(struct Place) * COUNT_SEETS, 1, output);
	}
	fclose(output);

	while (1){		
		printf("a) Show the number of seats available\n");
		printf("b) Show the list of available seats\n");
		printf("c) Show the list of reserved seats in alphabetical order\n");
		printf("d) To book a place for the passenger\n");
		printf("e) To remove from place\n");
		printf("f) To exit the program\n");

		scanf("%c", &comand);
		getchar();
		

		switch (comand){
		case 'a':
			count = getcountAvailSeets(places);
			printf("Count available seets: %d\n", count);
			break;
		case 'b':
			showAvailSeets(places);
			break;
		case 'c':
			showReservdSeetsInOrd(places);
			break;
		case 'd':
			bookPlace(places);
			break;
		case 'e':
			remResorv(places);
			break;
		case 'f':		
			output = fopen("file.bin", "wb");
			if (output == NULL) {
				printf("Error opening file");
				return 1;
			}
			for (int i = 0; i < COUNT_SEETS; i++){}
			fwrite(places, sizeof(struct Place) * COUNT_SEETS, 1, output);
			fclose(output);
			return 1;
			break;
		}
	}
}
