#ifndef ShoppingList_C
#define ShoppingList_C

typedef struct
{
	int id;
	float amount;
	char unit[10];
	char name[50];
} Matvara;

typedef struct
{
	int length;
	Matvara* varor;
} ShoppingList;

void defineList(Matvara **mList, int nrOfItems);
void addToList(ShoppingList *mShoppingList, int *index);
void printList(Matvara *list, int length);
void changeItem(ShoppingList *mShoppingList);
void delFromList(ShoppingList *mShoppingList);
int chooseId(int length);
void saveList(Matvara *mList, int length);
void readFromFile(ShoppingList *mList);
#endif // !ShoppingList

