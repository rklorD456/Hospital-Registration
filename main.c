#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "stdtypes.h"
#include "LINKEDLIST.h"

#define MAX_SLOTS 5
#define MAX_INVALID_ATTEMPTS 3

void admin_mode();
void user_mode();
u32 check_admin_password();
void add_patient();
void edit_patient();
void reserve_slot();
void cancel_reservation();
char get_valid_gender();
u32 get_valid_age();
void display_available_slots();
void view_patient_record();
void view_todays_reservations();

u32 reserved_slots[MAX_SLOTS] = {0, 0, 0, 0, 0};

u32 main(void)
{
    char choice;
    bool isRunning = true;
    u32 invalidAttempts = 0;
    printf("\n|-----------------------------------------------------------------|\n");
	printf("|-------------------- Welcome to clinic --------------------------|\n");
	printf("|-----------------------------------------------------------------|\n\n");
    while (isRunning)
    {
		//the starter of show of the programm
        printf("\n\n\n*******************************************************************\n");
        printf("Select The Mode:\n");
        printf("1. Admin Mode\n");
        printf("2. User Mode\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        printf("\n*******************************************************************\n\n\n");

        switch (choice)
        {
            case '1':
                printf("\n********************** \"Welcome to Admin mode\" ****************************\n\n");
                admin_mode();
                break;

            case '2':
                printf("\n********************** \"Welcome to User Mode\" ****************************\n\n");
                user_mode();
                break;

            case '3':
                printf("Exiting the system\n");
                isRunning = false;
                break;
			//to shutdown the program if the user attempt many times ivalid
            default:
                invalidAttempts++;
                printf("Invalid choice. Please enter a valid option.\n");
                if (invalidAttempts >= MAX_INVALID_ATTEMPTS)
                {
                    printf("Invalid many times error. The program will now shut down.\n");
                    exit(1);
                }
                else
                {
                    printf("Please select again a valid choice from 1 to 3.\n");
                }
                break;
        }
    }

    printf("Thanks for using our clinical!\n");
    return 0;
}

void admin_mode()
{
    char choice;
    bool isRunning = true;
    u32 invalidAttempts = 0;
    if (check_admin_password() == 1)
    {
        printf("You entered the wrong password too many times. Exiting Admin Mode.\n");
        return;
    }
    printf("\n\n\t\tSuccessful Enter to the Admin mode");
    while (isRunning)
    {
        printf("\n*******************************************************************\n\n");
        printListAsTable();
        printf("\nSelect The operation you want to perform:\n");
        printf("1. Add new patient\n");
        printf("2. Edit existing patient\n");
        printf("3. Reserve a slot\n");
        printf("4. Cancel a reservation\n");
        printf("5. Exit Admin Mode\n\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        printf("\n*******************************************************************\n");

        switch (choice)
        {
            case '1':
                add_patient();
                break;

            case '2':
                edit_patient();
                break;

            case '3':
                reserve_slot();
                break;

            case '4':
                cancel_reservation();
                break;

            case '5':
                printf("Exiting Admin Mode\n");
                isRunning = false;
                break;

            default:
                invalidAttempts++;
                printf("Invalid choice.\n");
                if (invalidAttempts >= MAX_INVALID_ATTEMPTS)
                {
                    printf("Invalid many times error. Exiting Admin Mode.\n");
                    isRunning = false;
                }
                else
                {
                    printf("Please select a valid operation (1-5).\n");
                }
                break;
        }
    }
}

void user_mode()
{
    char choice;
    bool isRunning = true;
    u32 invalidAttempts = 0;
    while (1) {
        printf("1. View patient record\n");
        printf("2. View today's reservations\n");
        printf("3. Exit User Mode\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
        printf("\n");
        switch (choice) {
            case 1:
                view_patient_record();
                break;
            case 2:
                view_todays_reservations();
                break;
            case 3:
                printf("Exiting User Mode.\n");
                isRunning = false;
                return;
            default:
                invalidAttempts++;
                printf("Invalid choice.\n");
                if (invalidAttempts >= MAX_INVALID_ATTEMPTS)
                {
                    printf("Invalid many times error. Exiting Admin Mode.\n");
                    isRunning = false;
                }
                else
                {
                    printf("Please select a valid operation (1-3).\n");
                }
                break;
        }
    }
}


void add_patient() {
    u32 id, age;
    char gender, name[50];
    printf("Enter ID: ");
    scanf("%u", &id);
	//to search if the user with id is already found in system or no
    if(searchByID(id) == 1)
    {
        printf("The patient with ID %u is already in .\n",id);
        return;
    }

    age = get_valid_age();
    gender = get_valid_gender();

    printf("Enter Name: ");
    scanf(" %[^\n]", name);
    getchar(); 
    insertFirst(id, age, gender, name); //to add the patient to the base data
    printf("\n\t\tsuccessful adding the patient %s with ID %u",name,id);
}

void edit_patient()
{
    u32 id, new_age;
    char new_gender, new_name[50];
    printf("Enter Patient ID to edit: ");
    scanf("%u", &id);

    node* current = searchNodeByID(id); // Declare and assign current in linkedlist data
	//to search if the user with id is already found in system or no
    if (current == NULL) {
        printf("The patient with ID %u is not found.\n", id);
        return;
    }

    printf("Enter New Age: ");
    scanf("%u", &new_age);

    if (new_age < 0 || new_age > 150) {
        printf("Invalid age. Please enter a valid age (0-150).\n");
        return;
    }

    printf("Enter New Gender (M/F): ");
    scanf(" %c", &new_gender);

    if (new_gender != 'M' && new_gender != 'F' && new_gender != 'm' && new_gender != 'f') {
        printf("Invalid gender. Please enter 'M' or 'F'.\n");
        return;
    }

    printf("Enter New Name: ");
    scanf(" %[^\n]", new_name);
    getchar();

    // Update the patient's information using the current pointer
    current->data.age = new_age;
    current->data.gender = new_gender;
    strcpy(current->data.name, new_name);

    printf("\n\t\tPatient with ID %u has been updated successful.\n", id);
}


void reserve_slot()
{
    u32 patient_id;
    int slot_choice;
    
    printf("Enter Patient ID: ");
    scanf("%u", &patient_id);
    if(searchByID(patient_id) == 0)
    {
        printf("The patient with ID %u is not found.\n",patient_id);
        return;
    }
	for( u32 search; search<5; search++)
	{
		if(reserved_slots[search] == patient_id)
		{
			printf("The Patient with ID %d already has reservation ",patient_id);
			return ;
		}
	}
    // Display available slots
    printf("--------------------------------------------------------------------\n");
    display_available_slots();
    printf("Enter Slot Choice (1-5): ");
    scanf("%d", &slot_choice);

    // Validate slot choice
    if (slot_choice < 1 || slot_choice > 5 || reserved_slots[slot_choice - 1] != 0)
    {
        printf("Invalid slot choice or slot is already reserved.\n");
        return;
    }

    // Reserve the selected slot
    reserved_slots[slot_choice - 1] = patient_id;
    printf("Slot %d reserved for patient with ID %u successful .\n", slot_choice, patient_id);
}

void cancel_reservation()
{
    u32 patient_id;
    printf("Enter patient ID to cancel reservation: ");
    scanf("%d", &patient_id);
    if(searchByID(patient_id) == 0)
    {
        printf("The patient with ID %u is not found.\n",patient_id);
        return;
    }

    for (int i = 0; i < MAX_SLOTS; i++) {
        if (reserved_slots[i] == patient_id) {
            reserved_slots[i] = 0;
            printf("Reservation canceled for patient ID %d in slot %d.\n", patient_id, i + 1);
            return;
        }
    }

    printf("No reservation found for patient ID %d.\n", patient_id);
}

void display_available_slots()
{
    printf("Available Slots:\n");
    for (int i = 0; i < 5; i++) {
        if (reserved_slots[i] == 0) {
            printf("%d. ", i + 1);
            switch (i) {
                case 0:
                    printf("\t2:00 PM - 2:30 PM\n");
                    break;
                case 1:
                    printf("\t2:30 PM - 3:00 PM\n");
                    break;
                case 2:
                    printf("\t3:00 PM - 3:30 PM\n");
                    break;
                case 3:
                    printf("\t4:00 PM - 4:30 PM\n");
                    break;
                case 4:
                    printf("\t4:30 PM - 5:00 PM\n");
                    break;
            }
        }
    }
}

u32 check_admin_password()
{
    u32 adminPassword = 1234;
    u32 passwordCheck;
    u32 numAttempts = 0;

    while (numAttempts < 3)
    {
        printf("Please Enter the admin password: ");
        scanf("%d", &passwordCheck);

        if (passwordCheck == adminPassword)
        {
            return 0; // Password is correct
        }
        else
        {
            numAttempts++;
            printf("Incorrect password. Attempt %d of 3.\n", numAttempts);
        }
    }

    return 1; // Exceeded maximum attempts
}

char get_valid_gender()
{
    char gender;
    char buffer[100];  // Input buffer for handling extra characters

    while (1)
    {
        printf("Enter Gender (M/F): ");
        if (scanf(" %c", &gender) != 1)
        {
            // Invalid input (more than one character)
            printf("Invalid input. Please enter 'M' or 'F'.\n");
            scanf("%s", buffer);  // Consume the invalid input
        }
        else if (gender != 'M' && gender != 'F' && gender != 'm' && gender != 'f')
        {
            printf("Invalid gender. Please enter 'M' or 'F'.\n");
        }
        else
        {
            break;  // Valid gender input
        }
    }

    return gender;
}

u32 get_valid_age() {
    u32 age;
    char buffer[100];  // Input buffer for handling non-integer input

    while (1) {
        printf("Enter Age: ");
        if (scanf("%u", &age) != 1)
        {
            // Invalid input (non-integer)
            printf("Invalid input. Please enter a valid age (0-150).\n");
            scanf("%s", buffer);  // Consume the invalid input
            continue;  // Repeat the loop to get valid input
        }

        if (age < 0 || age > 150)
        {
            printf("Invalid age. Please enter a valid age (0-150).\n");
        }
        else
        {
            break;  // Valid age input
        }
    }

    return age;
}


void view_patient_record()
{
    u32 id_to_print;
    printf("Enter the ID of the patient you want: ");
    scanf("%u", &id_to_print);
    printf("\n");
    printPatientByID(id_to_print);
}
void view_todays_reservations()
{
    printf("-----------------------------------------------\n");
    printf("Today's Reservations:\n");
    
    int noReservations = 1;
    for (int i = 0; i < 5; i++)
    {
        if (reserved_slots[i] !=0 )
        {
            noReservations = 0;
            printf("Slot %d (", i + 1);
            
            switch (i) {
                case 0:
                    printf("2:00 PM - 2:30 PM");
                    break;
                case 1:
                    printf("2:30 PM - 3:00 PM");
                    break;
                case 2:
                    printf("3:00 PM - 3:30 PM");
                    break;
                case 3:
                    printf("4:00 PM - 4:30 PM");
                    break;
                case 4:
                    printf("4:30 PM - 5:00 PM");
                    break;
            }
            
            printf(") is reserved for patient with ID %u\n", reserved_slots[i]);
        }
    }
    if (noReservations)
    {
        printf("No reservations for today.\n");
    }

    printf("-----------------------------------------------\n");
}
