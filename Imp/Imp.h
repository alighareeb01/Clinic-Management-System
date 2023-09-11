#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "prototype.h"

#define MAX_SLOTS 5
int id_search;
int options;
int options_admin;
int options_user;
int num_of_patient;
int count = 0;
int choose;
int password;
int features;
char NAME[30];
int AGE;
char GENDER[70];
char YesOrNo[5];
int ID;
int idExist = 0;

int flag_i = 0;

enum main_menu
{
	ADMIN = 1,
	USER = 2,
	EXIT_SYSTEM = 3
};
enum admin_menu
{
	ADD_NEW_RECORD = 1,
	EDIT = 2,
	RESERVE_SLOT = 3,
	CANCEL_RESERVATION = 4,
	VIEW_ALL = 5,
	EXIT_ADMIN = 6
};
enum USER_MENU
{
	VIEW_PATIENT = 1,
	VIEW_TODAY_RESERVATION = 2,
	EXIT_USER = 3
};
node *root = NULL;
slot *slots[MAX_SLOTS];

void StringInout(char str[])
{
	fflush(stdin);
	char ch = 0;
	int i = 0;
	while (1)
	{
		scanf("%c", &ch);
		if (ch == '\n')
			break;
		str[i++] = ch;
	}
	str[i] = '\0';
}
int menu_choose(void)
{
	int falg = 0;
	printf("You Have Two Modes\n");
	printf("---------------------\n");
	printf("\t\t1-ADMIN MODE.\n\n");
	printf("\t\t2-USER MODE.\n\n");
	printf("\t\t3-Exit.\n\n");

	printf("Enter your choice: ");
	scanf("%d", &choose);
	system("cls");

	switch (choose)
	{
	case ADMIN:
		printf("\t\t\t------------------------------\n");
		printf("\t\t\tYOU ARE IN ADMIN MODE.\n");
		printf("\t\t\t------------------------------\n");

		break;
	case USER:
		printf("\t\t\t------------------------------\n");
		printf("\t\t\tYOU ARE IN USER MODE.\n");
		printf("\t\t\t------------------------------\n");

		break;
	case EXIT_SYSTEM:
		EXIT();
		break;
	default:
		printf("\t\t\t------------------------------\n");
		printf("\t\t\tYou Choosed The Wrong Choice\n");
		printf("\t\t\t------------------------------\n");
		break;
	}
	return choose;
}

int ADMIN_MENU()
{
	flag_i = 0;
	for (int i = 0; i < 3; i++)
	{
		printf("\tPassword: ");
		scanf("%d", &password);
		if (password == 1234)
		{
			flag_i = 1;
			break;
		}
	}
	system("cls");
	if (!flag_i)
	{
		printf("\t\t------------------------------------------------\n");
		fprintf(stderr, "\t\tYou Entered The Wrong Password Three Times.\n");
		// printf("\t\tYou Entered The Wrong Password Three Times.\n");
		printf("\t\tThe System Shall Close Now.\n");
		printf("\t\t-------------------------------------------------\n");
		exit(0);
	}
	if (flag_i)
	{
		printf("Choose:\n");
		printf("\t1-Add New Patient Record.\n");
		printf("\t2-Edit Patient Record.\n");
		printf("\t3-Reverse A Slot With The Doctor.\n");
		printf("\t4-Cancel Reservation.\n");
		printf("\t5-View All.\n");
		printf("\t6-Exit.\n");
		printf("Enter Your choice: ");
		scanf("%d", &options_admin);
		system("cls");
	}
	return options_admin;
}
int USER_MENU(void)
{
	printf("Choose:\n");
	printf("\t1-View Patient Record\n");
	printf("\t2-View todays reservations\n");
	printf("\t3-Exit\n");
	printf("Enter Your choice: ");
	scanf("%d", &options_user);
	system("cls");
	return options_user;
}
void Mess_Again(void)
{
	printf("\n");
	printf("=>>do you want the menu again: ");
	printf("Enter y/Y for yes and n/N for no: ");
	StringInout(YesOrNo);
	system("cls");
}
void EXIT(void)
{
	printf("\t\t\t------------------------------\n");
	printf("\t\t\tThe System Shall Close Now.\n");
	printf("\t\t\t------------------------------\n");
	exit(0);
}
void add_new_patient(node **root)
{
	printf("INFORMATION:\n");
	printf("------------\n");

	node *newnode = malloc(sizeof(node));
	if (newnode == NULL)
	{
		printf("Memory allocation failed.\n");
		return;
	}

	printf("\tName: ");
	StringInout(newnode->name);
	printf("\tAge: ");
	scanf("%d", &newnode->age);
	printf("\tGender: ");
	StringInout(newnode->gender);

	int newId;
	while (1)
	{
		printf("\tID: ");
		scanf("%d", &newId);

		// Check if the ID already exists
		node *curr = *root;
		int idExists = 0;
		while (curr != NULL)
		{
			if (curr->id == newId)
			{
				printf("ID already exists. Please enter a different ID.\n");
				idExists = 1;
				break;
			}
			curr = curr->next;
		}

		if (!idExists)
		{
			newnode->id = newId;
			break;
		}
	}

	newnode->next = NULL;

	if (*root == NULL)
	{
		*root = newnode;
		return;
	}
	node *curr = *root;
	while (curr->next != NULL)
	{
		curr = curr->next;
	}
	curr->next = newnode;
}
void travesre(node **root)
{
	node *curr = *root;
	if (*root == NULL)
	{
		printf("No One Is Enrolled In The System\n");
		return;
	}
	while (curr != NULL)
	{
		printf("---------------------------\n");
		printf("Name : %s\n", curr->name);
		printf("Age %d\n", curr->age);
		printf("Gender : %s\n", curr->gender);
		printf("ID %d\n", curr->id);
		curr = curr->next;
	}
}
void edit(node **root)
{
	node *curr = *root;
	int flag = 0;
	if (*root == NULL)
	{
		printf("No One Is Enrolled In The System\n");
		flag = 1;
	}
	if (!flag)
	{
		printf("Enter Id To Search For: ");
		scanf("%d", &id_search);
		while (curr != NULL && curr->id != id_search)
		{
			curr = curr->next;
		}

		if (curr == NULL)
		{
			printf("Not Enrolled In The System\n");
		}
		if (curr != NULL)
		{
			printf("New Name: ");
			StringInout(curr->name);
			printf("New Age: ");
			scanf("%d", &curr->age);
			printf("New Gender: ");
			StringInout(curr->gender);
			printf("New ID: ");
			scanf("%d", &curr->id);
		}
		printf("---------------------------\n");
		printf("New Record After Modification\n");
		printf("---------------------------\n");
		printf("Name : %s\n", curr->name);
		printf("Age %d\n", curr->age);
		printf("Gender : %s\n", curr->gender);
		printf("ID %d\n", curr->id);
	}
}
void view(node **root)
{
	node *curr = *root;
	int flag = 0;
	if (*root == NULL)
	{
		printf("No One Is Enrolled In The System\n");
		flag = 1;
	}
	if (!flag)
	{
		printf("Enter Id To Search For: ");
		scanf("%d", &id_search);
		while (curr != NULL && curr->id != id_search)
		{
			curr = curr->next;
		}
		if (curr == NULL)
		{
			printf("Not Enrolled In The System\n");
		}
		if (curr != NULL)
		{
			printf("---------------------------\n");
			printf("Name : %s\n", curr->name);
			printf("Age %d\n", curr->age);
			printf("Gender : %s\n", curr->gender);
			printf("ID %d\n", curr->id);
		}
	}
}

void reserveSlot(node **root, slot **slots)
{
	int patientId, slotChoice;

	printf("Enter patient ID: ");
	scanf("%d", &patientId);

	// Check if the patient ID exists
	node *current = *root;
	while (current != NULL)
	{
		if (current->id == patientId)
		{
			if (current->age < 18)
			{
				printf("Patients under 18 cannot reserve slots.\n");
				return;
			}
			break;
		}
		current = current->next;
	}

	printf("Available slots:\n");
	for (int i = 0; i < MAX_SLOTS; i++)
	{
		printf("%d. Slot %d: %s\n", i + 1, i + 1, (slots[i]->reserved) ? "Occupied" : (i == 0) ? "2pm to 2:30pm"
																				  : (i == 1)   ? "2:30pm to 3pm"
																				  : (i == 2)   ? "3pm to 3:30pm"
																				  : (i == 3)   ? "4pm to 4:30pm"
																							   : "4:30pm to 5pm");
	}

	printf("Enter slot choice (1-%d): ", MAX_SLOTS);
	scanf("%d", &slotChoice);

	if (slotChoice >= 1 && slotChoice <= MAX_SLOTS)
	{

		if (slots[slotChoice - 1]->reserved == 1)
		{
			printf("Slot is already reserved. Please choose another slot.\n");
		}
		else
		{
			slots[slotChoice - 1]->patientId = patientId;
			slots[slotChoice - 1]->reserved = 1;
			printf("Slot reserved successfully.\n");
		}
	}
	else
	{
		printf("Invalid slot choice.\n");
	}
}
void intializeslot(void)
{
	for (int i = 0; i < MAX_SLOTS; i++)
	{
		slots[i] = malloc(sizeof(slot));
		slots[i]->patientId = 0; // Initialize patientId to 0
		slots[i]->reserved = 0;	 // Initialize reserved to 0
	}
}
void cancelReservation()
{
	int patientId;

	printf("Enter patient ID to cancel reservation: ");
	scanf("%d", &patientId);

	for (int i = 0; i < MAX_SLOTS; i++)
	{
		if (slots[i]->reserved && slots[i]->patientId == patientId)
		{
			slots[i]->reserved = 0;
			printf("Reservation cancelled successfully.\n");
			return;
		}
	}

	printf("Reservation not found.\n");
}
void viewTodaysReservations(slot **slots)
{
	int flag_res = 0;

	printf("Today's reservations:\n");
	printf("-------------------------\n");
	for (int i = 0; i < MAX_SLOTS; i++)
	{
		if (slots[i]->reserved)
		{
			printf("Slot %d: %s - Patient ID: %d\n", i + 1,
				   (i == 0) ? "2pm to 2:30pm" : (i == 1) ? "2:30pm to 3pm"
											: (i == 2)	 ? "3pm to 3:30pm"
											: (i == 3)	 ? "4pm to 4:30pm"
														 : "4:30pm to 5pm",
				   slots[i]->patientId);
			flag_res = 1;
		}
	}
	if (!flag_res)
	{
		printf("THERE ARE NO RESERVATIONS.\n");
	}
}
void deallocate(node **root)
{
	node *curr = *root;
	while (curr != NULL)
	{
		node *aux = curr;
		curr = curr->next;
		free(aux);
	}
	*root = NULL;
}
void deallocate_slot(slot **slot)
{
	for (int i = 0; i < 5; i++)
	{
		free(slot[i]);
	}
}