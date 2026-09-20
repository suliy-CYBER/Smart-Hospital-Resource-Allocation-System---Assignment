#include <stdio.h>

#ifndef HOSPITAL_H
#define HOSPITAL_H

#define MAX_PATIENTS 100
#define NUMBER_OF_SPECIALTIES 4
#define NUMBER_OF_WARDS 4
#define MAX_BEDS 20

#endif


char specialtyNames[NUMBER_OF_SPECIALTIES][30] =
{
    "General Practice",
    "Paediatrics",
    "Cardiology",
    "Neurology"
};

float specialtyFees[NUMBER_OF_SPECIALTIES] =
{
    1500.00,
    2500.00,
    4500.00,
    5000.00
};

int consultationTimes[NUMBER_OF_SPECIALTIES] =
{
    15,
    20,
    30,
    30
};

int dailyPatientCapacities[NUMBER_OF_SPECIALTIES] =
{
    30,
    20,
    12,
    10
};

char wardNames[NUMBER_OF_WARDS][30] =
{
    "General Ward",
    "Paediatric Ward",
    "Surgical Ward",
    "ICU"
};

float wardDailyRates[NUMBER_OF_WARDS] =
{
    3000.00,
    6000.00,
    12000.00,
    25000.00
};

int wardBedCapacities[NUMBER_OF_WARDS] =
{
    20,
    10,
    10,
    5
};

int bedOccupancyStatus[NUMBER_OF_WARDS][MAX_BEDS] = {0};


void displayBedStatus(void);

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


void displayBedStatus()
{
    int wardIndex;
    int bedIndex;

    printf("\n");
    printf("==================================================\n");
    printf("                 BED STATUS\n");
    printf("==================================================\n");

    for (wardIndex = 0; wardIndex < NUMBER_OF_WARDS; wardIndex++)
    {
        printf("\n%s\n", wardNames[wardIndex]);

        for (bedIndex = 0; bedIndex < wardBedCapacities[wardIndex]; bedIndex++)
        {
            if (bedOccupancyStatus[wardIndex][bedIndex] == 0)
            {
                printf("Bed %02d : Available\n", bedIndex + 1);
            }
            else
            {
                printf("Bed %02d : Occupied\n", bedIndex + 1);
            }
        }
    }
}
