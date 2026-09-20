#include <stdio.h>
#include <string.h>

#ifndef HOSPITAL_H
#define HOSPITAL_H

#define MAX_PATIENTS 100
#define NUMBER_OF_SPECIALTIES 4
#define NUMBER_OF_WARDS 4
#define MAX_BEDS 20

#endif

//HOSPITAL DATA

/* Specialty information */
char specialtyNames[NUMBER_OF_SPECIALTIES][30] = {
    "General Practice",
    "Paediatrics",
    "Cardiology",
    "Neurology"
};

float specialtyFees[NUMBER_OF_SPECIALTIES] = {
    1500.00,
    2500.00,
    4500.00,
    5000.00
};

int consultationTimes[NUMBER_OF_SPECIALTIES] = {
    15,
    20,
    30,
    30
};

int dailyPatientCapacities[NUMBER_OF_SPECIALTIES] = {
    30,
    20,
    12,
    10
};

int specialtyQueueCounts[NUMBER_OF_SPECIALTIES] = {0};

/* Ward information */
char wardNames[NUMBER_OF_WARDS][30] = {
    "General Ward",
    "Paediatric Ward",
    "Surgical Ward",
    "ICU"
};

float wardDailyRates[NUMBER_OF_WARDS] = {
    3000.00,
    6000.00,
    12000.00,
    25000.00
};

int wardBedCapacities[NUMBER_OF_WARDS] = {
    20,
    10,
    10,
    5
};

/* 2D bed occupancy matrix */
int bedOccupancyStatus[NUMBER_OF_WARDS][MAX_BEDS] = {0};

 //PATIENT DATA
char patientNames[MAX_PATIENTS][50];
int patientAges[MAX_PATIENTS];
int patientUrgencyLevels[MAX_PATIENTS];
int patientSpecialtyIds[MAX_PATIENTS];
int patientAdmissionStatus[MAX_PATIENTS];
int patientWardIds[MAX_PATIENTS];
int patientAdmissionDays[MAX_PATIENTS];
int patientAssignedBeds[MAX_PATIENTS];

int totalPatients = 0;

float patientBaseFees[MAX_PATIENTS];
float patientSurcharges[MAX_PATIENTS];
float patientWardCosts[MAX_PATIENTS];
float patientGrossBills[MAX_PATIENTS];
float patientDiscounts[MAX_PATIENTS];
float patientFinalBills[MAX_PATIENTS];



// FUNCTION PROTOTYPES

/* Main hospital functions */
void displayBedStatus(void);
void registerPatient(void);
void displayPatients(void);
void searchPatient(void);
void displayPriorityOrder(void);

/* Reports */
void generateHospitalReport(void);

/* File handling */
void saveBedStatus(void);
void loadBedStatus(void);
void savePatientRecord(int patientIndex);

/* Bed allocation */
int assignAvailableBed(int wardId);

/* Billing functions */
float calculateEmergencySurcharge(float baseFee, int urgencyLevel);
float calculateWaitingTime(int specialtyId);
float calculateWardCost(int wardId, int numberOfDays);
float calculateAgeDiscount(float grossBill, int patientAge);
float calculateFinalAmount(float grossBill, float discount);
void calculatePatientBill(int patientIndex);


// MAIN FUNCTION
int main(void)
{
    int menuChoice;

    do
    {
        printf("\n==================================================\n");
        printf("        SMART HOSPITAL RESOURCE SYSTEM\n");
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
                registerPatient();
                break;

            case 2:
                displayBedStatus();
                break;

            case 3:
                displayPatients();
                break;

            case 4:
                searchPatient();
                break;

            case 5:
                displayPriorityOrder();
                break;

            case 6:
                generateHospitalReport();
                break;

            case 7:
                saveBedStatus();
                printf("\nData saved successfully.\n");
                printf("Thank you for using Smart Hospital System.\n");
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }

    } while (menuChoice != 7);

    return 0;
}


//BED ALLOCATION

int assignAvailableBed(int wardId)
{
    if (wardId < 1 || wardId > NUMBER_OF_WARDS)
    {
        return 0;
    }

    for (int bedIndex = 0; bedIndex < wardBedCapacities[wardId - 1]; bedIndex++)
    {
        if (bedOccupancyStatus[wardId - 1][bedIndex] == 0)
        {
            bedOccupancyStatus[wardId - 1][bedIndex] = 1;

            return bedIndex + 1;
        }
    }

    return 0;
}


//  DISPLAY BED STATUS

void displayBedStatus(void)
{
    printf("\n==================================================\n");
    printf("                  BED STATUS\n");
    printf("==================================================\n");

    for (int wardIndex = 0; wardIndex < NUMBER_OF_WARDS; wardIndex++)
    {
        printf("\n%s\n", wardNames[wardIndex]);

        for (int bedIndex = 0; bedIndex < wardBedCapacities[wardIndex]; bedIndex++)
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


 // PATIENT REGISTRATION

void registerPatient(void)
{
    if (totalPatients >= MAX_PATIENTS)
    {
        printf("\nPatient limit reached.\n");
        return;
    }

    int patientIndex = totalPatients;

    printf("\n==================================================\n");
    printf("               PATIENT REGISTRATION\n");
    printf("==================================================\n");

    printf("Enter patient name: ");
    scanf(" %[^\n]", patientNames[patientIndex]);

    printf("Enter patient age: ");
    scanf("%d", &patientAges[patientIndex]);

    printf("\nUrgency Level\n");
    printf("1. Normal\n");
    printf("2. Urgent\n");
    printf("3. Critical\n");
    printf("Enter urgency level: ");
    scanf("%d", &patientUrgencyLevels[patientIndex]);

    printf("\nSpecialties\n");
    for (int i = 0; i < NUMBER_OF_SPECIALTIES; i++)
    {
        printf("%d. %s\n", i + 1, specialtyNames[i]);
    }
    printf("Enter specialty: ");
    scanf("%d", &patientSpecialtyIds[patientIndex]);

    if (patientSpecialtyIds[patientIndex] >= 1 &&
        patientSpecialtyIds[patientIndex] <= NUMBER_OF_SPECIALTIES)
    {
        int specId = patientSpecialtyIds[patientIndex];

        float estWaitTime = calculateWaitingTime(specId);

        printf("Estimated waiting time: %.0f minutes\n", estWaitTime);

        specialtyQueueCounts[specId - 1]++;
    }

    printf("\nIs the patient admitted to a ward?\n");
    printf("1. Yes\n");
    printf("0. No\n");
    printf("Enter choice: ");
    scanf("%d", &patientAdmissionStatus[patientIndex]);

    if (patientAdmissionStatus[patientIndex] == 1)
    {
        printf("\nWards\n");
        for (int i = 0; i < NUMBER_OF_WARDS; i++)
        {
            printf("%d. %s\n", i + 1, wardNames[i]);
        }
        printf("Enter ward: ");
        scanf("%d", &patientWardIds[patientIndex]);

        printf("Enter number of days: ");
        scanf("%d", &patientAdmissionDays[patientIndex]);

        int assignedBedNumber = assignAvailableBed(patientWardIds[patientIndex]);

        if (assignedBedNumber == 0)
        {
            printf("\nNo bed available in this ward.\n");

            patientAdmissionStatus[patientIndex] = 0;
            patientWardIds[patientIndex] = 0;
            patientAdmissionDays[patientIndex] = 0;
            patientAssignedBeds[patientIndex] = 0;
        }
        else
        {
            patientAssignedBeds[patientIndex] = assignedBedNumber;

            printf("Bed assigned successfully: Bed %02d\n", assignedBedNumber);
        }
    }
    else
    {
        patientWardIds[patientIndex] = 0;
        patientAdmissionDays[patientIndex] = 0;
        patientAssignedBeds[patientIndex] = 0;
    }

    calculatePatientBill(patientIndex);

    totalPatients++;

    printf("\nPatient registered successfully.\n");

    printf("Base Fee      : LKR %.2f\n", patientBaseFees[patientIndex]);
    printf("Surcharge     : LKR %.2f\n", patientSurcharges[patientIndex]);
    printf("Ward Cost     : LKR %.2f\n", patientWardCosts[patientIndex]);
    printf("Gross Bill    : LKR %.2f\n", patientGrossBills[patientIndex]);
    printf("Discount      : LKR %.2f\n", patientDiscounts[patientIndex]);
    printf("Final Bill    : LKR %.2f\n", patientFinalBills[patientIndex]);
}



//  DISPLAY ALL PATIENTS
void displayPatients(void)
{
    if (totalPatients == 0)
    {
        printf("\nNo patients registered in the system yet.\n");
        return;
    }

    printf("\n================================================================================\n");
    printf("                                REGISTERED PATIENTS                             \n");
    printf("================================================================================\n");

    for (int i = 0; i < totalPatients; i++)
    {
        printf("\n--- Patient #%d ---\n", i + 1);
        printf("Name           : %s\n", patientNames[i]);
        printf("Age            : %d\n", patientAges[i]);

        printf("Urgency Level  : ");
        switch (patientUrgencyLevels[i])
        {
            case 1: printf("Normal\n"); break;
            case 2: printf("Urgent\n"); break;
            case 3: printf("Critical\n"); break;
            default: printf("Unknown\n"); break;
        }

        int specIndex = patientSpecialtyIds[i] - 1;
        if (specIndex >= 0 && specIndex < NUMBER_OF_SPECIALTIES)
        {
            printf("Specialty      : %s\n", specialtyNames[specIndex]);
        }

        if (patientAdmissionStatus[i] == 1)
        {
            int wardIndex = patientWardIds[i] - 1;
            printf("Admission      : Admitted\n");
            printf("Ward           : %s\n", wardNames[wardIndex]);
            printf("Bed Assigned   : Bed %02d\n", patientAssignedBeds[i]);
            printf("Stay Duration  : %d Days\n", patientAdmissionDays[i]);
        }
        else
        {
            printf("Admission      : Outpatient (Not Admitted)\n");
        }

        printf("Billing Breakdown:\n");
        printf("  - Base Fee    : LKR %.2f\n", patientBaseFees[i]);
        printf("  - Surcharge   : LKR %.2f\n", patientSurcharges[i]);
        printf("  - Ward Cost   : LKR %.2f\n", patientWardCosts[i]);
        printf("  - Gross Bill  : LKR %.2f\n", patientGrossBills[i]);
        printf("  - Discount    : LKR %.2f\n", patientDiscounts[i]);
        printf("  - Final Bill  : LKR %.2f\n", patientFinalBills[i]);
    }

    printf("================================================================================\n");
}



//  SEARCH PATIENT

void searchPatient()
{
    char searchPatientName[50];
    int patientIndex;
    int foundPatient = 0;

    printf("\nEnter patient name to search: ");
    scanf(" %[^\n]", searchPatientName);

    for (patientIndex = 0;
         patientIndex < totalPatients;
         patientIndex++)
    {
        if (strcmp(patientNames[patientIndex],
                   searchPatientName) == 0)
        {
            printf("\nPatient Found\n");
            printf("-----------------------------\n");
            printf("Name : %s\n",
                   patientNames[patientIndex]);
            printf("Age  : %d\n",
                   patientAges[patientIndex]);

            foundPatient = 1;
        }
    }

    if (foundPatient == 0)
    {
        printf("\nPatient not found.\n");
    }
}


// PATIENT PRIORITY ORDER

void displayPriorityOrder(void)
{
    int patientOrder[MAX_PATIENTS];

    int currentPosition;
    int previousPosition;
    int currentPatient;

    if (totalPatients == 0)
    {
        printf("\nNo patients are registered.\n");
        return;
    }

    for (currentPosition = 0; currentPosition < totalPatients; currentPosition++)
    {
        patientOrder[currentPosition] = currentPosition;
    }

    for (currentPosition = 1; currentPosition < totalPatients; currentPosition++)
    {
        currentPatient = patientOrder[currentPosition];
        previousPosition = currentPosition - 1;

        while (previousPosition >= 0 &&
               patientUrgencyLevels[patientOrder[previousPosition]] < patientUrgencyLevels[currentPatient])
        {
            patientOrder[previousPosition + 1] = patientOrder[previousPosition];
            previousPosition--;
        }

        patientOrder[previousPosition + 1] = currentPatient;
    }

    printf("\n==================================================\n");
    printf("               PATIENT PRIORITY ORDER\n");
    printf("==================================================\n");

    for (currentPosition = 0; currentPosition < totalPatients; currentPosition++)
    {
        currentPatient = patientOrder[currentPosition];

        printf("%d. %s - Urgency Level %d\n",
               currentPosition + 1,
               patientNames[currentPatient],
               patientUrgencyLevels[currentPatient]);
    }
}


//HOSPITAL REPORT

void generateHospitalReport()
{
    int patientIndex;
    int normalPatients = 0;
    int urgentPatients = 0;
    int criticalPatients = 0;

    float totalRevenue = 0.00;
    float totalDiscounts = 0.00;

    for (patientIndex = 0;
         patientIndex < totalPatients;
         patientIndex++)
    {
        if (patientUrgencyLevels[patientIndex] == 1)
        {
            normalPatients++;
        }
        else if (patientUrgencyLevels[patientIndex] == 2)
        {
            urgentPatients++;
        }
        else if (patientUrgencyLevels[patientIndex] == 3)
        {
            criticalPatients++;
        }

        totalRevenue += patientFinalBills[patientIndex];
        totalDiscounts += patientDiscounts[patientIndex];
    }

    printf("\n");
    printf("==================================================\n");
    printf("             HOSPITAL REPORT\n");
    printf("==================================================\n");

    printf("\nPatients by Urgency\n");
    printf("Normal   : %d\n", normalPatients);
    printf("Urgent   : %d\n", urgentPatients);
    printf("Critical : %d\n", criticalPatients);

    printf("\nFinancial Summary\n");
    printf("Total Revenue   : LKR %.2f\n", totalRevenue);
    printf("Total Discounts : LKR %.2f\n",
           totalDiscounts);
}


//SAVE BED STATUS TO FILE

void saveBedStatus()
{
    FILE *file;
    int wardIndex;
    int bedIndex;

    file = fopen("beds_status.txt", "w");

    if (file == NULL)
    {
        printf("Unable to save bed status.\n");
        return;
    }

    for (wardIndex = 0;
         wardIndex < NUMBER_OF_WARDS;
         wardIndex++)
    {
        for (bedIndex = 0;
             bedIndex < wardBedCapacities[wardIndex];
             bedIndex++)
        {
            fprintf(file, "%d ",
                    bedOccupancyStatus[wardIndex][bedIndex]);
        }

        fprintf(file, "\n");
    }

    fclose(file);

    printf("Bed status saved successfully.\n");
}


float calculateEmergencySurcharge(float baseFee, int urgencyLevel)
{
    if (urgencyLevel == 2)
    {
        return baseFee * 0.20;
    }
    else if (urgencyLevel == 3)
    {
        return baseFee * 0.50;
    }

    return 0.00;
}

float calculateWardCost(int wardId, int numberOfDays)
{
    if (wardId < 1 || wardId > NUMBER_OF_WARDS || numberOfDays <= 0)
    {
        return 0.00;
    }

    return wardDailyRates[wardId - 1] * numberOfDays;
}

float calculateAgeDiscount(float grossBill, int patientAge)
{
    if (patientAge < 5 || patientAge > 65)
    {
        return grossBill * 0.15;
    }

    return 0.00;
}

float calculateFinalAmount(float grossBill, float discount)
{
    return grossBill - discount;
}

void calculatePatientBill(int patientIndex)
{
    patientBaseFees[patientIndex] =
        specialtyFees[patientSpecialtyIds[patientIndex] - 1];

    patientSurcharges[patientIndex] =
        calculateEmergencySurcharge(
            patientBaseFees[patientIndex],
            patientUrgencyLevels[patientIndex]
        );

    patientWardCosts[patientIndex] =
        calculateWardCost(
            patientWardIds[patientIndex],
            patientAdmissionDays[patientIndex]
        );

    patientGrossBills[patientIndex] =
        patientBaseFees[patientIndex]
        + patientSurcharges[patientIndex]
        + patientWardCosts[patientIndex];

    patientDiscounts[patientIndex] =
        calculateAgeDiscount(
            patientGrossBills[patientIndex],
            patientAges[patientIndex]
        );

    patientFinalBills[patientIndex] =
        calculateFinalAmount(
            patientGrossBills[patientIndex],
            patientDiscounts[patientIndex]
        );
}

float calculateWaitingTime(int specialtyId)
{
    int specialtyIndex;

    specialtyIndex = specialtyId - 1;

    return specialtyQueueCounts[specialtyIndex]
           * consultationTimes[specialtyIndex];
}

