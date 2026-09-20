#include <stdio.h>

#ifndef HOSPITAL_H
#define HOSPITAL_H

#define MAX_PATIENTS 100
#define NUMBER_OF_SPECIALTIES 4
#define NUMBER_OF_WARDS 4
#define MAX_BEDS 20

#endif

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

int bedOccupancyStatus[NUMBER_OF_WARDS][MAX_BEDS] = {0};


char patientNames[MAX_PATIENTS][50];
int patientAges[MAX_PATIENTS];
int patientUrgencyLevels[MAX_PATIENTS];
int patientSpecialtyIds[MAX_PATIENTS];
int patientAdmissionStatus[MAX_PATIENTS];
int patientWardIds[MAX_PATIENTS];
int patientAdmissionDays[MAX_PATIENTS];
int patientAssignedBeds[MAX_PATIENTS];

int totalPatients = 0;


float calculateEmergencySurcharge(float baseFee, int urgencyLevel);
float calculateWaitingTime(int specialtyId);
void displayBedStatus(void);
void registerPatient(void);
int assignAvailableBed(int wardId);

float calculateWaitingTime(int specialtyId)
{
    int specialtyIndex;

    specialtyIndex = specialtyId - 1;

    return specialtyQueueCounts[specialtyIndex]
           * consultationTimes[specialtyIndex];
}

int main(void) {
    int menuChoice;

    do {
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

        switch (menuChoice) {
            case 1:
                registerPatient();
                break;
            case 2:
                displayBedStatus();
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

int assignAvailableBed(int wardId) {
    if (wardId < 1 || wardId > NUMBER_OF_WARDS) {
        return 0;
    }

    for (int bedIndex = 0; bedIndex < wardBedCapacities[wardId - 1]; bedIndex++) {
        if (bedOccupancyStatus[wardId - 1][bedIndex] == 0) {
            bedOccupancyStatus[wardId - 1][bedIndex] = 1;
            return bedIndex + 1;
        }
    }

    return 0;
}

void displayBedStatus(void) {
    printf("\n==================================================\n");
    printf("                  BED STATUS\n");
    printf("==================================================\n");

    for (int wardIndex = 0; wardIndex < NUMBER_OF_WARDS; wardIndex++) {
        printf("\n%s\n", wardNames[wardIndex]);
        for (int bedIndex = 0; bedIndex < wardBedCapacities[wardIndex]; bedIndex++) {
            if (bedOccupancyStatus[wardIndex][bedIndex] == 0) {
                printf("Bed %02d : Available\n", bedIndex + 1);
            } else {
                printf("Bed %02d : Occupied\n", bedIndex + 1);
            }
        }
    }
}

void registerPatient(void) {
    if (totalPatients >= MAX_PATIENTS) {
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

    printf("\nUrgency Level\n1. Normal\n2. Urgent\n3. Critical\nEnter urgency level: ");
    scanf("%d", &patientUrgencyLevels[patientIndex]);

    printf("\nSpecialties\n");
    for (int i = 0; i < NUMBER_OF_SPECIALTIES; i++) {
        printf("%d. %s\n", i + 1, specialtyNames[i]);
    }
    printf("Enter specialty: ");
    scanf("%d", &patientSpecialtyIds[patientIndex]);

    if (patientSpecialtyIds[patientIndex] >= 1 && patientSpecialtyIds[patientIndex] <= NUMBER_OF_SPECIALTIES) {
        int specId = patientSpecialtyIds[patientIndex];
        float estWaitTime = calculateWaitingTime(specId);
        printf("Estimated waiting time: %.0f minutes\n", estWaitTime);
        specialtyQueueCounts[specId - 1]++;
    }

    printf("\nIs the patient admitted to a ward?\n1. Yes\n0. No\nEnter choice: ");
    scanf("%d", &patientAdmissionStatus[patientIndex]);

    if (patientAdmissionStatus[patientIndex] == 1) {
        printf("\nWards\n");
        for (int i = 0; i < NUMBER_OF_WARDS; i++) {
            printf("%d. %s\n", i + 1, wardNames[i]);
        }
        printf("Enter ward: ");
        scanf("%d", &patientWardIds[patientIndex]);

        printf("Enter number of days: ");
        scanf("%d", &patientAdmissionDays[patientIndex]);

        int assignedBedNumber = assignAvailableBed(patientWardIds[patientIndex]);

        if (assignedBedNumber == 0) {
            printf("\nNo bed available in this ward. Reverting admission status.\n");
            patientAdmissionStatus[patientIndex] = 0;
            patientWardIds[patientIndex] = 0;
            patientAdmissionDays[patientIndex] = 0;
            patientAssignedBeds[patientIndex] = 0;
        } else {
            patientAssignedBeds[patientIndex] = assignedBedNumber;
            printf("Bed assigned successfully: Bed %02d\n", assignedBedNumber);
        }
    } else {
        patientWardIds[patientIndex] = 0;
        patientAdmissionDays[patientIndex] = 0;
        patientAssignedBeds[patientIndex] = 0;
    }

    totalPatients++;
    printf("\nPatient registered successfully.\n");
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
