typedef struct node
{
	char name[30];
	int age;
	char gender[30];
	int id;
	struct node *next;
} node;
typedef struct slot
{
	int patientId;
	int reserved;
	struct slot *next;
} slot;

int menu_choose(void);
int ADMIN_MENU(void);
int USER_MENU(void);
void Mess_Again(void);
void EXIT(void);
void StringInout(char str[]);

void add_new_patient(node **root);
void travesre(node **root);
void edit(node **root);
void view(node **root);
void reserveSlot(node **root, slot **slots);
void cancelReservation();
void viewTodaysReservations(slot **slots);
void intializeslot(void);
void deallocate(node **root);
void deallocate_slot(slot **slot);