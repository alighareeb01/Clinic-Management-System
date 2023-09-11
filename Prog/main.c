#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#include "../Imp/Imp.h"

int main(void)
{
	system("cls");
	intializeslot();
	do
	{
		options = menu_choose();
		switch (options)
		{
		case ADMIN: // admin mode
			options_admin = ADMIN_MENU();
			switch (options_admin)
			{
			case ADD_NEW_RECORD: // Add new patient record
				add_new_patient(&root);
				break;
			case EDIT: // Edit patient record
				edit(&root);
				break;
			case RESERVE_SLOT: // 3. Reserve a slot with the docto
				reserveSlot(&root, slots);
				break;
			case CANCEL_RESERVATION: // Cancel reservation
				cancelReservation();
				break;
			case VIEW_ALL: // view all
				travesre(&root);
				break;
			case EXIT_ADMIN:
				EXIT();	
			}
			break;
		case USER: // user mode
			options_user = USER_MENU();
			switch (options_user)
			{
			case VIEW_PATIENT: // view patient
				view(&root);
				break;
			case VIEW_TODAY_RESERVATION: // view reservation
				viewTodaysReservations(slots);
				break;
			case EXIT_USER:
			EXIT();
				break;
			}
			break;
		}
		Mess_Again();
	} while ((!strcmp(YesOrNo, "y")) || (!strcmp(YesOrNo, "Y")));
	deallocate(&root);
	deallocate_slot(slots);
}
