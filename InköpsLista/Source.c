#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myInputManager.h"


/*
	Struct som innehåller parametrar för 
	att beskriva en matvara
*/
typedef struct
{
	int id;
	float amount;
	char unit[10];
	char name[50];
} Matvara;


/*
	Struct som innehåller:
	Lista av structen matvaror
	Längden av listan av matvaror
*/
typedef struct
{
	int length;
	Matvara* varor;
} ShoppingList;


/*
	Tar input från användaren, och lägger till den i 
	i struct Matvara
*/
void addToList(Matvara *mItem, int *index)
{
	/*
	Variabler för 
	*/
	char tempName[50], tempUnit[50];
	float tempAmount = 0;
	

	for (int i = 0; i < 3; i++)
	{
		switch (i)
		{
			case 0:
				printf("Whats the name of the food?: ");
				scanString(tempName, 50);
				break;
			case 1:
				printf("Whats the unit of the food?(L, grams, dl): ");
				scanString(tempUnit, 50);
				break;
			case 2:
				printf("What is the amount of food?: ");
				if (!scanFloat(&tempAmount) || tempAmount < 0)
				{
					printf("That is not a valid amount\n");
					i--;
				}
				break;
		}
	}
	

	// Copy values to the item members
	strcpy(mItem->name, tempName);
	strcpy(mItem->unit, tempUnit);
	mItem->amount = tempAmount;
	mItem->id = *index + 1;

	// Increment length of list
	*index += 1;
}



/*
	Prints out the entire list
	
*/
void printList(Matvara *list, int length)
{
	printf("\n*****Shopping List*****");
	printf("\n-----------------------\n");

	for (int i = 0; i < length; i++)
	{
		printf("#%d  %s          %.1f%s\n", list[i].id, list[i].name, list[i].amount, list[i].unit);
	}
	printf("-----------------------\n\n");
}



/*
Change a item on the shopping list
*/
void changeItem(ShoppingList *mShoppingList)
{
	int idToChange = 0;
	float newVal = 0;

	printList(mShoppingList->varor, mShoppingList->length);
	printf("Which item do you want to change the amount of?: ");
	idToChange = chooseId(mShoppingList->length);

	printf("What's the new amount of food?: ");
	while (!scanFloat(&newVal) || newVal < 0)
	{
		printf("That is not a valid amount\n");
	}

	mShoppingList->varor[idToChange - 1].amount = newVal;

	printf("Here's the complete list again: \n");

	printList(mShoppingList->varor, mShoppingList->length);
}




/*
	Delete a item from the shopping list
*/
void delFromList(ShoppingList *mShoppingList)
{
	int idToDel = 0;



	printList(mShoppingList->varor, mShoppingList->length);						// Printar listan innan vi frågar vilket item som ska tas bort
	printf("Which item do you want to delete? Please input the items id: ");	
	idToDel = chooseId(mShoppingList->length);									// Funktionen som frågar användaren vilket id vi ska ändra/tas bort
																				// används på flera ställen, och ligger därför i en egen funktion
	
	// Vi flyttar ner alla items i listan en plats, 
	// så att id som användaren valt blir överskrivet
	for (int i = idToDel; i < mShoppingList->length; i++)
	{
		mShoppingList->varor[i - 1] = mShoppingList->varor[i];					// Overwrite the item user choose to delete
		mShoppingList->varor[i - 1].id = i;										// and move items downward
	}

	mShoppingList->length --;													// Minskar längden på listan
		
	printList(mShoppingList->varor, mShoppingList->length);
	
}



/*
	Takes user input, and checks if input is in valid range
*/
int chooseId(int length)
{
	int chosenId = 0;
	int goodAnswer = 0;

	while (!goodAnswer)
	{
		if (!scanInt(&chosenId) || chosenId < 1 || chosenId > length)
		{
			printf("There's no item with that id. Please enter another id: ");
		}
		else
		{
			goodAnswer = 1;
		}
	}
	return chosenId;
}



/*
	Checks if we need to allocate, 
	or reallocate memory for the list of "Matvara" in ShoppingList struct

	I denna funktion tar vi en "pointer" till "pointern" av matlistan, dvs. "Matvara **mList"
*/
void defineList(Matvara **mList, int nrOfItems)
{
	int len = 0;

	// Första gången kommer mList vara NULL,
	// då vet vi att vi ska köra memory allocate(malloc)
	if (*mList == NULL)
	{
		// Allokera plats i minnet för 1 struct Matvara
		*mList = (Matvara*)malloc((nrOfItems + 1) * sizeof(Matvara));
		
		// Om mList returnar NULL så kunde vi inte allokera minne för listan
		if (*mList == NULL)
		{
			printf("Could not allocate initial memory.\n");
		}
		else
		{
			printf("Allocated memory for first struct.\n");
		}
	}
	// Om mList inte är NULL, så vet vi att vi måste
	// reallokera minne för listan(realloc)
	else
	{
		len = nrOfItems;
		// När vi reallokerar minne, så allokerar vi dubbelt så mycket minne.
		Matvara *tmp = realloc(*mList, (len * 2) * sizeof(Matvara));
		if (tmp == NULL)
		{
			printf("Cannot allocate more memory.\n");
		}
		else
		{
			*mList = tmp;
			printf("Allocated memory for more structs.\n");
		}
	}
}


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
		printf("5 - Exit\n");
		printf("Please write your answer(1..5): ");
		scanInt(&userAnswer);


		switch (userAnswer)
		{
			case 1:
				
				defineList(&mList->varor, mList->length);				
				addToList(&mList->varor[mList->length], &mList->length);	// Fill newly added "Matvara" with input from user
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
				exit = 1;
				break;
			default:
				printf("I didn't understand that, please try again.\n");
		} 
	}
	printf("Gooodbye!\n");
	return 0;
}