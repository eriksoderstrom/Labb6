#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myInputManager.h"
#include "ShoppingList.h"

int main(void)
{
	int exit = 0,  userAnswer = 0;

	ShoppingList *mList = calloc(1, sizeof(ShoppingList));		// Allokera minne för en struct ShoppingList
	mList->length = 0;											// Sätt längden till 0
	mList->varor = NULL;										// Sätt listan till NULL


	while (!exit)
	{
		printf("Welcome to the shopping list!\n");
		printf("1 - Add grocery\n");
		printf("2 - Print shoppinglist\n");
		printf("3 - Delete a item from the shoppinglist\n");
		printf("4 - Change a item on the shoppinglist.\n");
		printf("5 - Save shopping list to file.\n");
		printf("6 - Read shopping list from file.\n");
		printf("7 - Exit\n");
		printf("Please write your answer(1..5): ");
		scanInt(&userAnswer);


		switch (userAnswer)
		{
			case 1:				
				addToList(mList, &mList->length);							// Fill newly added "Matvara" with input from user
				break;
			case 2:
				printList(mList->varor, mList->length);						// Print out the full list, in a nice format
				break;
			case 3:
				delFromList(mList);
				break;
			case 4:
				changeItem(mList);
				break;
			case 5:
				saveList(mList->varor, mList->length);
				break;
			case 6:
				readFromFile(mList);
				break;
			case 7:
				exit = 1;
				break;
			default:
				printf("I didn't understand that, please try again.\n");
		} 
	}
	printf("Gooodbye!\n");
	return 0;
}