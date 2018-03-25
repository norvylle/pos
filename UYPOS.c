#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>

typedef struct nodetag{
	char name[30];
	char size[10];
	float base,combo,upgrade;
	int inventory;
	struct nodetag *next;
}NODE;

NODE *food_head = NULL;
NODE *drinks_head = NULL;
NODE *dessert_head = NULL;
NODE *receipt = NULL;

int inventory_count = 0,line = 0,inventory,item_count = 0,save_count = 0,saved = 0,load_count = 0,r=0;
char filename[20],password[36],password_input[36],n = 'a';
float pera,total=0,sukli,grand=0;

#include "UYPOS.h"

int main(){
	int choice = 0,choice2 = 0,choice3 = 0,choice4 = 0;
	char name[30];
	char size[10];
	char search[30];
	char clear[10] = "cls";
	float base,combo,upgrade;
	
	system(clear);
	printf("JOLLY DONALD'S Point-Of-Sale SYSTEM\n");
	printf("\t[1] INVENTORY\n\t[2] SALES\n\t[3] EXIT\n");
	printf("Enter choice:	");
	scanf("%d",&choice);
	if (choice == 1){
		if(inventory_count == 0){
			printf("Enter default INVENTORY count for the day:	");
			scanf("%d",&inventory);
			printf("Enter system password:	");
			scanf("\n%[^\n]s",password);
			inventory_count++;
		}
		do{
			system(clear);
			menuI();
			scanf("%d",&choice2);
			if(choice2 == 1){
				printf("ADD FOOD ITEM\n");
				printf("\t[1] Food\n\t[2] Drinks\n\t[3] Dessert\n");
				printf("Enter choice:	");
				scanf("%d",&choice3);
				if(choice3 == 1){
					printf("Enter Food NAME:	"); scanf("\n%[^\n]s",name);
					printf("Enter Food SIZE:	"); scanf("\n%[^\n]s",size);
					printf("Enter Food BASE PRICE:	"); scanf("%f",&base);
					printf("Enter Food COMBO PRICE:	"); scanf("%f",&combo);
					printf("Enter Food UPGRADE PRICE:	"); scanf("%f",&upgrade);
					addfT(&food_head,createf(name,size,base,combo,upgrade,inventory));
					item_count++;
				}
				else if(choice3 == 2){
					printf("Enter Drink NAME:	"); scanf("\n%[^\n]s",name);
					printf("Enter Drink SIZE:	"); scanf("\n%[^\n]s",size);
					printf("Enter Drink BASE PRICE:	"); scanf("%f",&base);
					printf("Enter Drink UPGRADE PRICE:	"); scanf("%f",&upgrade);
					addfT(&drinks_head,createf(name,size,base,0,upgrade,inventory));
					item_count++;
				}
				else if(choice3 == 3){
					printf("Enter Dessert NAME:	"); scanf("\n%[^\n]s",name);
					printf("Enter Dessert SIZE:	"); scanf("\n%[^\n]s",size);
					printf("Enter Dessert BASE PRICE:	"); scanf("%f",&base);
					addfT(&dessert_head,createf(name,size,base,0,0,inventory));
					item_count++;
				}
				else printf("INVALID CHOICE\n");
				pause();
			}
			else if(choice2 == 2){
				printf("EDIT FOOD ITEM\n");
				printf("\t[1] Food\n\t[2] Drinks\n\t[3] Dessert\n");
				printf("Enter choice:	");
				scanf("%d",&choice3);
				switch(choice3){
					case 1:editf(&food_head);
					break;
					case 2:editf(&drinks_head);
					break;
					case 3:editf(&dessert_head);
					break;
					default: printf("INVALID CHOICE\n");
				}
				pause();
			}
			else if(choice2 == 3){
				printf("DELETE FOOD ITEM\n");
				printf("\t[1] Food\n\t[2] Drinks\n\t[3] Dessert\n");
				printf("Enter choice:	");
				scanf("%d",&choice3);
				printf("ITEMS\n");
				switch(choice3){
					case 1: delf(&food_head);
					break;
					case 2: delf(&drinks_head);
					break;
					case 3: delf(&dessert_head);
					break;
					default: printf("INVALID CHOICE");
				}
				pause();
			}
			else if(choice2 == 4){
				printf("DISPLAY FOOD ITEMS \n");
				printf("[1] All [2] Category [3] Search\nEnter choice:	");
				scanf("%d",&choice3);
				switch(choice3){
					case 1:	printf("[Display All]\n");
							printf("%-25s | %-8s| BASE | COMBO |   UPGRADE   | INVENTORY \n","ITEM","SIZE");
							printf("----------FOOD----------\n");	disf(&food_head);
							printf("----------DRINKS----------\n");	disf(&drinks_head);
							printf("----------DESSERT----------\n");	disf(&dessert_head);
					break;
					case 2: printf("[Display Category]\n");
							printf("\t[1] Food\n\t[2] Drinks\n\t[3] Dessert\nEnter choice:	");
							scanf("%d",&choice4);
							printf("%-25s | %-8s| BASE | COMBO |   UPGRADE   | INVENTORY \n","ITEM","SIZE");
							switch(choice4){
								case 1: printf("----------FOOD----------\n");	disf(&food_head);
								break;
								case 2: printf("----------DRINKS----------\n");	disf(&drinks_head);
								break;
								case 3:	printf("----------DESSERT----------\n"); disf(&dessert_head);
								break;
								default:printf("INVALID\n");
							}
					break;
					case 3: printf("[Display Searched]\nEnter search:	");
							scanf("\n%[^\n]s",search);
							printf("%-25s | %-8s| BASE | COMBO |   UPGRADE   | INVENTORY \n","ITEM","SIZE");
							discat(&food_head,search);
							discat(&drinks_head,search);
							discat(&dessert_head,search);
					break;
					default:printf("DEFAULT\n");
				}
				pause();
			}
			else if(choice2 == 5){
				printf("DISPLAY RECEIPT\n");
				disr();
				pause();
			}
			else if(choice2 == 6){
				printf("COMPUTE SALES\n");
				printf("[1] Command Line [2] File\nEnter choice:	");
				scanf("%d",&choice3);
				switch(choice3){
					case 1: printf("[Command Line]\n");
							compC();
					break;
					case 2: printf("[File]\n");
							compF();
							printf("File generated!\n");
					break;
					default: printf("Invalid\n");
				}
				pause();
			}
			else if(choice2 == 7){
				printf("LOAD FILE\n");
				save_count = 0;
				if(food_head != NULL) cleanreceipt(&food_head);
				if(drinks_head != NULL) cleanreceipt(&drinks_head);
				if(dessert_head != NULL) cleanreceipt(&dessert_head);
				printf("\nEnter filename (w/o filename extension):	");
				scanf("\n%[^\n]s",filename);
				strcat(filename,".txt");
				load(filename);
				printf("-- INVENTORY UPDATED --\n");
				pause();
			}
			else if(choice2 == 8){
				FILE* fp;
				printf("SAVE FILE\n");
				save_count = 0;
				printf("Enter filename (w/o filename extension):	");
				scanf("\n%[^\n]s",filename);
				strcat(filename,".txt");
				fp = fopen(filename,"w");
				save(&food_head,filename,fp); save_count++;
				save(&drinks_head,filename,fp); save_count++;
				save(&dessert_head,filename,fp);
				printf("-- Inventory Saved --\n");
				pause();
			}
			else if(choice2 != 9){
				printf("INVALID CHOICE\n");
				pause();
			}
			else printf("EXIT TO MAIN MENU\n");
		}while(choice2 != 9);
		pause();
		return main();
	}
	else if (choice == 2){
		do{
			system(clear);
			menuS();
			scanf("%d",&choice2);
			if(choice2 == 1){
				printf("ORDER\n");
				printf("\t[1] Food\n\t[2] Drinks\n\t[3] Dessert\nEnter choice:	");
				scanf("%d",&choice3);
				switch(choice3){
					case 1: printf("FOOD\n");	order(&food_head);
					break;
					case 2: printf("DRINKS\n");	order(&drinks_head);
					break;
					case 3:	printf("DESSERT\n"); order(&dessert_head);
					break;
					default:printf("INVALID\n");
				}
				pause();
			}
			else if(choice2 == 2){
				printf("VOID\n");
				printf("Enter system password:	");
				scanf("\n%[^\n]s",password_input);
				if(strcmp(password,password_input) == 0){
					if(receipt != NULL ) voidO(&receipt);
					else printf("Empty Order List\n");
				}
				else printf("INVALID\n");
				pause();
			}
			else if(choice2 == 3){
				printf("CHECKOUT\n");
				if(receipt != NULL ) check(&receipt);
				else printf("Empty Order List\n");
				pause();
			}
			else if(choice2 != 4){
				printf("INVALID CHOICE\n");
				pause();
			}
			else printf("EXIT TO MAIN MENU\n");
		}while(choice2 != 4);
		pause();
		return main();
	}
	else if (choice == 3){
		printf("EXIT\n");
		pause();
		return 0;
	}
	else{
		printf("INVALID CHOICE\n");
		pause();
		return main();
	}
	return 0;
}