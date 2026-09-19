#include <stdio.h>

#ifndef HOSPITAL_H
#define HOSPITAL_H

#define MAX_PATIENTS 100
#define NUMBER_OF_SPECIALTIES 4
#define NUMBER_OF_WARDS 4
#define MAX_BEDS 20

#endif

int main()
{
    int menuChoice;

    do
    {
        printf("\n");
        printf("==================================================\n");
        printf("       SMART HOSPITAL RESOURCE SYSTEM\n");
        printf("==================================================\n");
        printf("1. Register New Patient\n");
        printf("2. Display Bed Status\n");
        printf("3. Display Patients\n");
        printf("4. Search Patient\n");
        printf("5. Display Patient Priority Order\n");
        printf("6. Generate Reports\n");
        printf("7. Save Data and Exit\n");
        printf("--------------------------------------------------\n");

        printf("Enter your choice: ");
        scanf("%d", &menuChoice);

        switch (menuChoice)
        {
            case 1:
                printf("\nPatient registration selected.\n");
                break;

            case 2:
                printf("\nBed status selected.\n");
                break;

            case 3:
                printf("\nPatient display selected.\n");
                break;

            case 4:
                printf("\nPatient search selected.\n");
                break;

            case 5:
                printf("\nPriority order selected.\n");
                break;

            case 6:
                printf("\nHospital reports selected.\n");
                break;

            case 7:
                printf("\nSaving data and exiting...\n");
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }

    } while (menuChoice != 7);

    return 0;
}
