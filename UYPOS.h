void pause(){
	printf("Press Any Key to Continue\n");
	getchar();
	_getch();
}

//INVENTORY
void menuI(){
	printf("\n*****************************\n");
	printf("Jolly Donald's INVENTORY\n");
	printf("\t[1] Add Food Item\n");
	printf("\t[2] Edit Food Item\n");
	printf("\t[3] Delete Food Item\n");
	printf("\t[4] Display Food Items\n");
	printf("\t[5] Display Receipt\n");
	printf("\t[6] Compute Sales\n");
	printf("\t[7] Load File\n");
	printf("\t[8] Save File\n");
	printf("\t[9] Exit to Main Menu\n");
	printf("*****************************\n\n");
	printf("Enter choice:	");
}

NODE* createf(char *name,char *size,float base,float combo,float upgrade,int inventory){
	NODE *newN;

	newN = (NODE *) malloc(sizeof(NODE));
	strcpy(newN->name,name);
	strcpy(newN->size,size);
	newN->base = base;
	newN->combo = combo;
	newN->upgrade = upgrade;
	newN->inventory = inventory;
	newN->next = NULL;
	//printf("IN:%s %s %f %f %f %d\n",newN->name,newN->size,newN->base,newN->combo,newN->upgrade,newN->inventory);

	return newN;
}

void addfH(NODE **head, NODE *node){
	if(*head != NULL){
		node->next = *head;
	}
	*head = node;
}

void addfT(NODE **head, NODE *node){
	NODE *tail = *head;
	if(*head == NULL) addfH(head,node);
	else{
		while(tail->next != NULL){
			tail = tail->next;
		}
		tail->next = node;
	}
}

void editf(NODE **head){
	NODE* temp = *head;
	char search[30];
	if(*head == NULL) printf("Empty inventory for food item.\n");
	else{
		printf("%-25s | %-8s| BASE | COMBO |   UPGRADE   | INVENTORY \n","ITEM","SIZE");
		while(temp!=NULL){
			printf("> %-25s %-8s  %.2f  %.2f\t%.2f\t\t%d\n",temp->name,temp->size,temp->base,temp->combo,temp->upgrade,temp->inventory);
			temp = temp->next;
		}
		temp = *head;
		printf("Enter search:	");
		scanf("\n%[^\n]s",search);
		while(temp!=NULL){
			if(strcmp(temp->name,search) == 0){
				printf("ITEM FOUND\n");
				if(*head == food_head){
					printf("Enter new FOOD NAME:	"); scanf("\n%[^\n]s",temp->name);
					printf("Enter new FOOD SIZE:	"); scanf("\n%[^\n]s",temp->size);
					printf("Enter new FOOD BASE PRICE:	"); scanf("%f",&temp->base);
					printf("Enter new FOOD COMBO PRICE:	"); scanf("%f",&temp->combo);
					printf("Enter new FOOD UPGRADE PRICE:	"); scanf("%f",&temp->upgrade);
					printf("-- ITEM EDITED --\n");
					pause();
				}
				else if(*head == drinks_head){
					printf("Enter new DRINK NAME:	"); scanf("\n%[^\n]s",temp->name);
					printf("Enter new DRINK SIZE:	"); scanf("\n%[^\n]s",temp->size);
					printf("Enter new DRINK BASE PRICE:	"); scanf("%f",&temp->base);
					printf("Enter new DRINK UPGRADE PRICE:	"); scanf("%f",&temp->upgrade);
					printf("-- ITEM EDITED --\n");
					pause();
				}
				else if(*head == dessert_head){
					printf("Enter new DESSERT NAME:	"); scanf("\n%[^\n]s",temp->name);
					printf("Enter new DESSERT SIZE:	"); scanf("\n%[^\n]s",temp->size);
					printf("Enter new DESSERT BASE PRICE:	"); scanf("%f",&temp->base);
					printf("-- ITEM EDITED --\n");
					pause();
				}
				break;
			}
			temp = temp->next;
		}
		if(temp == NULL) printf("INVALID\n");
	}
}

void delf(NODE **head){
	NODE* temp = *head;
	NODE* h = *head;
	NODE* toDelete = NULL;
	char search[30];
	if(*head == NULL) printf("Empty inventory for food item.\n");
	else{
		printf("%-25s | %-8s| BASE | COMBO |   UPGRADE   | INVENTORY \n","ITEM","SIZE");
		while(temp!=NULL){
			printf("> %-25s %-8s  %.2f  %.2f\t%.2f\t\t%d\n",temp->name,temp->size,temp->base,temp->combo,temp->upgrade,temp->inventory);
			temp = temp->next;
		}
		temp = *head;
		printf("Enter search:	");
		scanf("\n%[^\n]s",search);
		while(temp!=NULL){
			if(strcmp(temp->next->name,search) == 0){
				if(h->next == NULL){
					free(temp);
					*head = NULL;
					printf("-- ITEM DELETED --\n");
					pause();
				}
				else{
					toDelete = temp->next;
					temp->next = toDelete->next;
					free(toDelete);
					printf("-- ITEM DELETED --\n");
					pause();
				}
				break;
			}
			temp = temp->next;
		}
	}
}

void disf(NODE **head){
	NODE* temp = *head;
	if(*head == NULL) printf("-- Empty inventory for food item. --\n");
	else{
		while(temp!=NULL){
			printf("> %-25s %-8s  %.2f  %.2f\t%.2f\t\t%d\n",temp->name,temp->size,temp->base,temp->combo,temp->upgrade,temp->inventory);
			temp = temp->next;
		}
	}
}

void discat(NODE **head,char *search){
	NODE* temp = *head;
	if(*head == NULL);
	else{
		while(temp!=NULL){
			if(strcmp(temp->name,search) == 0){
				printf("> %-25s %-8s  %.2f  %.2f\t%.2f\t\t%d\n",temp->name,temp->size,temp->base,temp->combo,temp->upgrade,temp->inventory);
				break;
			}
			temp = temp->next;
		}
	}
}

void disr(){
	FILE* fp;
	char receiptname[15];
	char item[30];
	float item_cost,total,change;
	int i,n;

	printf("Enter receipt number:	");
	scanf("\n%[^\n]s",receiptname);
	strcat(receiptname,".txt");
	fp = fopen(receiptname,"r");
	if(fp == NULL){
		printf("Receipt Not Found!\n");
	}
	else{
		printf("Receipt Found!\n");
		fscanf(fp,"%d\n",&n);
		for(i=0;i<n;i++){
			fscanf(fp,"%[^\n]s\n",item);
			fscanf(fp,"%f\n",&item_cost);
			printf("%d)\t%s\t\t%.2f\n",i+1,item,item_cost);
		}
		fscanf(fp,"%f\n",&total);
		fscanf(fp,"%f\n",&change);
		printf("Total:\t\t\t\t%.2f\nChange Due:\t\t\t%.2f\n",total,change);
	}
	fclose(fp);
}

void compCitems(NODE **head){
	NODE* temp = *head;
	float grand_item=0;

	while(temp!=NULL){
		grand_item = temp->base * (inventory - temp->inventory);
		printf("%-25s %-8s\t\t%f (%d)\n",temp->name,temp->size,grand_item,(inventory - temp->inventory));
		temp = temp->next;
	}
}

void compC(){
	printf("Grand Total:	%f\n",grand);
	printf("%-25s|%-8s|\t\tPhp (qty)\n","ITEM","SIZE");
	compCitems(&food_head);
	compCitems(&drinks_head);
	compCitems(&dessert_head);
}

void compFitems(FILE* fp,NODE **head){
	NODE* temp = *head;
	float grand_item=0;

	while(temp!=NULL){
		grand_item = temp->base * (inventory - temp->inventory);
		fprintf(fp,"%-25s %-8s\t\t%f (%d)\n",temp->name,temp->size,grand_item,(inventory - temp->inventory));
		temp = temp->next;
	}
}
void compF(){
	FILE* fp;
	fp = fopen("computation.txt","w");

	fprintf(fp,"Grand Total:	Php %f\n",grand);
	fprintf(fp,"%-25s|%-8s|\t\tPhp (qty)\n","ITEM","SIZE");
	compFitems(fp,&food_head);
	compFitems(fp,&drinks_head);
	compFitems(fp,&dessert_head);
	fclose(fp);
}

void load(char *filename){
	FILE* fp;
	NODE* temp = (NODE *) malloc(sizeof(NODE));
	char comp[100];
	int i;
	fp = fopen(filename,"r");
	if(fp == NULL) printf("FILE NOT FOUND\n");
	else{
			fscanf(fp, "%d\n",&inventory); //inventory for saved txt
		do{//FOOD
			fscanf(fp,"\n%[^\n]s\n",comp);
			temp->next = NULL;
			if(strcmp(comp,"#") != 0){
				strcpy(temp->name,comp);
				fscanf(fp,"\n%[^\n]s\n",temp->size);
				fscanf(fp,"%f\n",&temp->base);
				fscanf(fp,"%f\n",&temp->combo);
				fscanf(fp,"%f\n",&temp->upgrade);
				fscanf(fp,"%d\n",&temp->inventory);
				inventory = temp->inventory;
				addfT(&food_head,createf(temp->name,temp->size,temp->base,temp->combo,temp->upgrade,temp->inventory));
			}
			else break;
		}while(strcmp(comp,"#") != 0);
		do{//DRINKS
			fscanf(fp,"\n%[^\n]s\n",comp);
			temp->next = NULL;
			if(strcmp(comp,"#") != 0){
				strcpy(temp->name,comp);
				fscanf(fp,"\n%[^\n]s",temp->size);
				fscanf(fp,"%f\n",&temp->base);
				fscanf(fp,"%f\n",&temp->combo);
				fscanf(fp,"%f\n",&temp->upgrade);
				fscanf(fp,"%d\n",&temp->inventory);
				inventory = temp->inventory;
				addfT(&drinks_head,createf(temp->name,temp->size,temp->base,temp->combo,temp->upgrade,temp->inventory));
			}
		}while(strcmp(comp,"#") != 0);
		do{//DESSERT
			fscanf(fp,"\n%[^\n]s\n",comp);
			temp->next = NULL;
			if(strcmp(comp,"#") != 0){
				strcpy(temp->name,comp);
				fscanf(fp,"\n%[^\n]s",temp->size);
				fscanf(fp,"%f\n",&temp->base);
				fscanf(fp,"%f\n",&temp->combo);
				fscanf(fp,"%f\n",&temp->upgrade);
				fscanf(fp,"%d\n",&temp->inventory);
				inventory = temp->inventory;
				addfT(&dessert_head,createf(temp->name,temp->size,temp->base,temp->combo,temp->upgrade,temp->inventory));
			}
		}while(strcmp(comp,"#") != 0);
		fclose(fp);
	} 
}

void save(NODE **head,char *filename,FILE* fp){
	NODE* temp = *head;
	if(*head == NULL);
	else{
		fp = fopen(filename,"a");
		if(save_count == 0){
			fprintf(fp,"%d\n",inventory);
		}
		while(temp!=NULL){
			fprintf(fp,"%s\n%s\n%.2f\n%.2f\n%.2f\n%d\n",temp->name,temp->size,temp->base,temp->combo,temp->upgrade,temp->inventory);
			temp = temp->next;
		}
		fprintf(fp,"#\n");
		fclose(fp);
	}
}
//SALES
void menuS(){
	printf("\n*****************************\n");
	printf("Jolly Donald's SALES\n");
	printf("\t[1] Order\n");
	printf("\t[2] Void\n");
	printf("\t[3] Checkout\n");
	printf("\t[4] Exit to Main Menu\n");
	printf("*****************************\n\n");
	printf("Enter choice:	");
}

void order(NODE **head){
	NODE* temp = *head;
	NODE* temp2 = NULL;
	NODE* temp3 = NULL;
	NODE* temp4 = NULL;
	char foodchoice[30],sizechoice[10],foodchoice1[30],sizechoice1[10];
	int qty,i,cuchoice2,cuchoice3,cuchoice;

	if(*head == NULL) printf("-- Empty inventory for food item. --\n");
	else{
		printf("Item                  |    Size/s\n");
		while(temp!=NULL){
			printf("> %-20s| %-10s\n",temp->name,temp->size);
			temp = temp->next;
		}
		printf("Enter item choice:	"); scanf("\n%[^\n]s",foodchoice);
		printf("Enter item size:	"); scanf("\n%[^\n]s",sizechoice);
		temp = *head;
		temp2 = temp;
		temp3 = temp2;
		strcpy(foodchoice1,foodchoice);
		strcpy(sizechoice1,sizechoice);
		while(temp!=NULL){
			if(strcmp(temp->name,foodchoice) == 0){
				if(strcmp(temp->size,sizechoice) == 0){
					printf("Enter quantity:	"); scanf("%d",&qty);
					temp4 = temp;
					for(i=0;i<qty;++i){
						if(temp->inventory == 0){
							printf("Empty Inventory for item\n");
							break;
						}
						if(*head == food_head || *head == drinks_head){
							printf("(%s)Avail Upgrade? [1]Yes [2] No:	",temp->name); scanf("%d",&cuchoice);
							switch(cuchoice){
								case 1: printf("UPGRADE\nSIZES\n");
										temp2 = temp3;
										while(temp2!=NULL){
											if(strcmp(temp2->name,foodchoice1) == 0 && strcmp(temp2->size,sizechoice1) != 0) printf("> %s\n",temp2->size);
											temp2 = temp2->next;
										}
										temp2 = temp3;
										printf("Enter item size:	"); scanf("\n%[^\n]s",sizechoice);
										while(temp2!=NULL){
											if(strcmp(temp2->size,sizechoice) == 0){
												if(temp2->inventory == 0){
													printf("Empty Inventory for item\n");
													break;
												}
												temp4 = temp2;
												//addfT(&receipt,createf(temp2->name,temp2->size,temp2->base,0,0,1));
												break;
											}
											temp2 = temp2->next;
										}
										if(temp2 == NULL) printf("Item not found\n");
								case 2: //continue
										
										if(*head == food_head){
										printf("(%s) Avail Combo? [1]Yes [2] No:	",temp->name); scanf("%d",&cuchoice2);
										temp2 = drinks_head;
										switch(cuchoice2){
											case 1: addfT(&receipt,createf(temp4->name,temp4->size,temp4->combo,0,0,1));
													temp2 = drinks_head;
													printf("Item               |\tSize/s\n");
													while(temp2!=NULL){
														printf("> %-25s|\t%s\n",temp2->name,temp2->size);
														temp2 = temp2->next;
													}
													temp2 = drinks_head;
													printf("Enter item choice:	"); scanf("\n%[^\n]s",foodchoice);
													printf("Enter item size:	"); scanf("\n%[^\n]s",sizechoice);
													while(temp2!=NULL){
														if(strcmp(temp2->name,foodchoice) == 0){
															if(strcmp(temp2->size,sizechoice) == 0){
																if(temp2->inventory == 0){
																	printf("Empty Inventory for item\n");
																	break;
																}
																printf("(%s) Avail Upgrade for Drink? [1]Yes [2]No:	", temp2->name); scanf("%d",&cuchoice3);
																switch(cuchoice3){
																	case 1: printf("UPGRADE\nSIZES\n");
																			temp2 = drinks_head;
																			while(temp2!=NULL){
																				if(strcmp(temp2->name,foodchoice) == 0 && strcmp(temp2->size,sizechoice) != 0) printf("> %s\n",temp2->size);
																				temp2 = temp2->next;
																			}
																			temp2 = drinks_head;
																			printf("Enter item size:	"); scanf("\n%[^\n]s",sizechoice);
																			while(temp2!=NULL){
																				if(strcmp(temp2->size,sizechoice) == 0){
																					if(temp2->inventory == 0){
																						printf("Empty Inventory for item\n");
																						break;
																					}
																					addfT(&receipt,createf(temp2->name,temp2->size,temp2->base,0,0,1));
																					break;
																				}
																				temp2 = temp2->next;
																			} if(temp2->next == NULL) addfT(&receipt,createf(temp2->name,temp2->size,temp2->base,0,0,1));
																	break;
																	case 2: addfT(&receipt,createf(temp2->name,temp2->size,temp2->base,0,0,1));
																	break;
																	default: printf("INVALID\n");
																}//switch
															break;
															}
														}
													temp2 = temp2->next;
													}
											break;
											case 2: if(cuchoice == 2 && *head == food_head) addfT(&receipt,createf(temp4->name,temp4->size,temp4->base,0,0,1));
											break;
											default: printf("INVALID\n");
										}
									break;
									}
								else{
									printf("Combo not available\n");
									addfT(&receipt,createf(temp->name,temp->size,temp->base,0,0,1));
								}
								break;
								default: printf("INVALID\n");
							}//switch cuchoice
						}//if
						else if(*head == dessert_head){
							addfT(&receipt,createf(temp->name,temp->size,temp->base,0,0,1));
						}//else
					}
					break;
				}
			}
			temp = temp->next;
		}
		if(temp == NULL) printf("INVALID\n");
		printf("ORDER SUBTOTAL:\n");
		disf(&receipt);
	}
}
void voidO(NODE **head){
	NODE* temp = *head;
	NODE* h = *head;
	NODE* toDelete = NULL;
	int i = 1,boyd;

	printf("RECEIPT ITEMS\n");
	while(temp!=NULL){
		printf("%d) %s\t|\t%f\n",i++,temp->name,temp->base);
		temp = temp->next;
	}
	temp = *head;
	printf("Enter number to be void:	");
	scanf("%d",&boyd);
	switch(boyd){
		case 1: printf("> %s\t|\t%f\n",temp->name,temp->base);
				toDelete = temp;
				if(toDelete->next != NULL) *head = toDelete->next;
				else *head = NULL;
				free(toDelete);
				printf("-- ITEM DELETED --\n");
		break;
		case 2: boyd--;
				while(boyd != 1){ // FIX HERE
					temp = temp->next;
					boyd--;
				}
				printf("> %s\t|\t%f\n",temp->next->name,temp->next->base);
				toDelete = temp->next;
				temp->next = toDelete->next;
				free(toDelete);
				printf("-- ITEM DELETED --\n");
		break;
		default: printf("INVALID\n");
	}
}

void cleaninventory(NODE **head,NODE *temp){
	NODE* temph = *head;

	while(temph!=NULL){
		if(strcmp(temph->name,temp->name) == 0){
			if(strcmp(temph->size,temp->size) == 0){
				temph->inventory--;
			}
		}
		temph = temph->next;
	}
}

void cleanreceipt(NODE **head){
	NODE* toDelete = *head;
	while(*head != NULL){
			(*head) = toDelete->next;
			toDelete->next = NULL;
			free(toDelete); 
	}
}

void check(NODE **head){
	NODE* temp = *head;
	FILE* fp;
	char receiptname[15] ="receipt_";
	strcat(receiptname,&n);
	strcat(receiptname,".txt");
	++n;

	int i=1;

	total = 0;
	pera = 0;
	sukli = 0;
	printf("#|%-21s|%8s|\tPHP\n","ITEM","SIZE");
	while(temp!=NULL){
		printf("%d) %-20s|%8s|\t%.4f\n",i++,temp->name,temp->size,temp->base);
		total = total+temp->base;
		temp = temp->next;
	}
	printf("TOTAL:\t\t\t\t\t%.4f\n",total);
	do{
		printf("Enter Amount:	");
		scanf("%f",&pera);
		if(pera<total) printf("INSUFFICIENT AMOUNT\n");;
	}while(pera<total);
	sukli = pera - total;
	printf("Cash Tendered:\t\t\t\t%.4f\n",pera);
	printf("Change:\t\t\t\t\t%.4f\n",sukli);
	//print receipt
	fp = fopen(receiptname,"w");
	temp = *head;
	fprintf(fp,"%d\n",i-1);
	while(temp!=NULL){
		fprintf(fp,"%s\n%f\n",temp->name,temp->base);
		temp = temp->next;
	}
	fprintf(fp,"%f\n%f",total,sukli);
	fclose(fp);
	//clean inventory
	temp = *head;
	while(temp != NULL){
		cleaninventory(&food_head,temp);
		cleaninventory(&drinks_head,temp);
		cleaninventory(&dessert_head,temp);
		temp = temp->next;
	}
	//empty receipt
	printf("RECEIPT NAME: %s\n",receiptname);
	cleanreceipt(&receipt);
	grand = grand+total;
	pause();
}