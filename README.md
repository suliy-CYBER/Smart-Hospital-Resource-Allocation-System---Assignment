# Smart Hospital & Resource Allocation System

**Student Name:** G D S Manodya
**Student ID:** [AS20250652]


## Project Description


The system is designed to manage basic hospital operations through a menu-driven console application. It allows users to register patients, assign medical specialties, manage urgency levels, allocate hospital beds, calculate waiting times, calculate patient bills, search for patients, display patient priority order, and generate hospital reports.

The project demonstrates fundamental C programming concepts including arrays, functions, conditional statements, loops, searching, sorting, file handling, and modular program organization.

---

## Project Objectives

The main objectives of this project are:

* To develop a practical hospital management system using C.
* To apply fundamental C programming concepts to a real-world situation.
* To manage patient information using arrays.
* To handle patients according to their urgency level.
* To allocate available hospital beds.
* To calculate estimated waiting times.
* To calculate hospital bills.
* To provide patient searching facilities.
* To generate basic hospital reports.
* To demonstrate functions and modular programming.
* To demonstrate basic file handling using C.
* To use Git and GitHub to manage the project development process.

---

## Main Features

### 1. Patient Registration

The system allows the user to register a new patient by entering:

* Patient name
* Patient age
* Urgency level
* Medical specialty
* Admission status
* Ward, if admitted
* Number of admission days, if admitted

The system supports up to **100 patients**.

---

### 2. Medical Specialties

The system contains four medical specialties:

1. General Practice
2. Paediatrics
3. Cardiology
4. Neurology

Each specialty has its own consultation fee, consultation time, and daily patient capacity defined in the program.

| Specialty        | Consultation Fee (LKR) | Consultation Time |
| ---------------- | ---------------------: | ----------------: |
| General Practice |               1,500.00 |        15 minutes |
| Paediatrics      |               2,500.00 |        20 minutes |
| Cardiology       |               4,500.00 |        30 minutes |
| Neurology        |               5,000.00 |        30 minutes |

---

### 3. Patient Urgency Levels

Patients can be registered under three urgency levels:

```text
1. Normal
2. Urgent
3. Critical
```

The system uses the urgency level when displaying the patient priority order.

The numerical priority used by the program is:

```text
Critical → Urgent → Normal
```

For patients with the same urgency level, the existing registration order is maintained by the priority-ordering algorithm.

---

### 4. Waiting-Time Calculation

The system estimates the waiting time for a patient based on:

* The number of patients already waiting for the selected specialty.
* The consultation time associated with that specialty.

The calculation used is:

```text
Estimated Waiting Time =
Number of Patients in Specialty Queue × Consultation Time
```

For example, if three patients are already in a specialty queue and the consultation time is 20 minutes:

```text
3 × 20 = 60 minutes
```

The estimated waiting time is therefore 60 minutes.

---

### 5. Ward Management

The system contains four wards:

1. General Ward
2. Paediatric Ward
3. Surgical Ward
4. ICU

Each ward has a defined daily rate and bed capacity.

| Ward            | Daily Rate (LKR) | Bed Capacity |
| --------------- | ---------------: | -----------: |
| General Ward    |         3,000.00 |           20 |
| Paediatric Ward |         6,000.00 |           10 |
| Surgical Ward   |        12,000.00 |           10 |
| ICU             |        25,000.00 |            5 |

---

### 6. Bed Allocation

When a patient is admitted, the system checks the selected ward for an available bed.

The `assignAvailableBed()` function searches through the beds in the selected ward.

If an available bed is found:

```text
Available Bed → Assigned to Patient
```

If there is no available bed, the system displays:

```text
No bed available in this ward.
```

The bed occupancy information is stored using a two-dimensional array.

---

### 7. Bed Status Display

The system allows the user to view the status of all beds.

Each bed is displayed as either:

```text
Bed 01 : Available
```

or:

```text
Bed 01 : Occupied
```

The bed status is maintained separately for each ward.

---

### 8. Billing System

The system calculates the final patient bill using several components:

* Specialty consultation fee
* Emergency/urgency surcharge
* Ward cost
* Age-based discount

The calculation follows this general process:

```text
Base Fee
   +
Emergency Surcharge
   +
Ward Cost
   =
Gross Bill

Gross Bill
   -
Age Discount
   =
Final Bill
```

---

### 9. Emergency Surcharge

An additional surcharge is applied according to the urgency level.

The current implementation uses:

| Urgency  |       Surcharge |
| -------- | --------------: |
| Normal   |              0% |
| Urgent   | 20% of base fee |
| Critical | 50% of base fee |

The surcharge is calculated by the:

```c
calculateEmergencySurcharge()
```

function.

---

### 10. Ward Cost Calculation

For admitted patients, the ward cost is calculated using:

```text
Ward Cost = Ward Daily Rate × Number of Days
```

For example:

```text
General Ward = LKR 3,000 per day
Number of Days = 3

Ward Cost = 3,000 × 3
          = LKR 9,000
```

The calculation is performed by:

```c
calculateWardCost()
```

---

### 11. Age-Based Discount

The system applies a **15% discount** to the gross bill when the patient's age is:

* Below 5 years, or
* Above 65 years.

The calculation is performed by:

```c
calculateAgeDiscount()
```

The final bill is calculated using:

```text
Final Bill = Gross Bill - Discount
```

---

### 12. Patient Display

The system can display all registered patients.

For each patient, the system can display information such as:

* Patient name
* Age
* Urgency level
* Specialty
* Admission status
* Ward
* Assigned bed
* Stay duration
* Billing breakdown
* Final bill

---

### 13. Patient Search

The search function allows the user to search for a patient using the **patient's name**.

The system compares the entered name with the registered patient names.

If a matching patient is found, the patient's name and age are displayed.

If no matching patient is found, the system displays:

```text
Patient not found.
```

The search uses the C library function:

```c
strcmp()
```

to compare patient names.

---

### 14. Patient Priority Order

The system provides a separate option to display patients according to their urgency level.

The priority-ordering function uses an **insertion sort approach**.

The order is:

```text
Critical
Urgent
Normal
```

Patients with the same urgency level retain their registration order.

The function used for this feature is:

```c
displayPriorityOrder()
```

---

### 15. Hospital Report

The hospital report provides a basic summary of the registered patients and financial information.

The report displays:

### Patients by Urgency

* Number of Normal patients
* Number of Urgent patients
* Number of Critical patients

### Financial Summary

* Total Revenue
* Total Discounts

The report is generated using:

```c
generateHospitalReport()
```

---

## Data Structures Used

The project mainly uses arrays to store and process hospital information.

### 1. One-Dimensional Arrays

One-dimensional arrays are used to store information such as:

```c
int patientAges[MAX_PATIENTS];
int patientUrgencyLevels[MAX_PATIENTS];
int patientSpecialtyIds[MAX_PATIENTS];
int patientWardIds[MAX_PATIENTS];
int patientAdmissionDays[MAX_PATIENTS];
int patientAssignedBeds[MAX_PATIENTS];
```

These arrays store information for multiple patients.

---

### 2. Two-Dimensional Arrays

Two-dimensional arrays are used for information that has multiple rows and columns.

For example:

```c
int bedOccupancyStatus[NUMBER_OF_WARDS][MAX_BEDS];
```

This array stores the occupancy status of beds in each ward.

Another example is:

```c
char patientNames[MAX_PATIENTS][50];
```

which stores the names of multiple patients.

---

### 3. Parallel Arrays

The patient information is stored using parallel arrays.

For example, the same index represents the same patient:

```text
patientNames[0]
patientAges[0]
patientUrgencyLevels[0]
patientSpecialtyIds[0]
```

Therefore, all values at index `0` belong to the first registered patient.

---

### 4. Constants

The program uses constants to define system limits:

```c
#define MAX_PATIENTS 100
#define NUMBER_OF_SPECIALTIES 4
#define NUMBER_OF_WARDS 4
#define MAX_BEDS 20
```

These constants make the program easier to manage and modify.

---

## Main Functions

The program is divided into functions according to their responsibilities.

| Function                        | Purpose                                         |
| ------------------------------- | ----------------------------------------------- |
| `main()`                        | Displays the main menu and controls the program |
| `registerPatient()`             | Registers a new patient                         |
| `displayBedStatus()`            | Displays available and occupied beds            |
| `displayPatients()`             | Displays registered patient information         |
| `searchPatient()`               | Searches for a patient by name                  |
| `displayPriorityOrder()`        | Displays patients according to urgency          |
| `generateHospitalReport()`      | Generates the hospital report                   |
| `assignAvailableBed()`          | Finds and assigns an available bed              |
| `saveBedStatus()`               | Saves bed occupancy information to a file       |
| `calculateEmergencySurcharge()` | Calculates urgency-based surcharge              |
| `calculateWaitingTime()`        | Calculates estimated waiting time               |
| `calculateWardCost()`           | Calculates ward charges                         |
| `calculateAgeDiscount()`        | Calculates eligible age discount                |
| `calculateFinalAmount()`        | Calculates the final payable amount             |
| `calculatePatientBill()`        | Combines the billing calculations               |

---

## File Handling

The current implementation includes basic file handling for hospital bed information.

When the user selects:

```text
7. Save Data and Exit
```

the program calls:

```c
saveBedStatus();
```

The bed occupancy information is saved in:

```text
beds_status.txt
```

The file contains the occupancy status of beds for each ward.

For example:

```text
0 1 0 0 1
0 0 0 1 0
1 1 0 0 0
0 0 1 0 0
```

where:

```text
0 = Available
1 = Occupied
```

### Current File Handling Limitation

The current version saves **bed occupancy information only**.

Patient records are not currently saved to a file.

---

## Program Menu

The main program provides the following menu:

```text
==================================================
        SMART HOSPITAL RESOURCE SYSTEM
==================================================
1. Register New Patient
2. Display Bed Status
3. Display Patients
4. Search Patient
5. Display Patient Priority Order
6. Generate Reports
7. Save Data and Exit
--------------------------------------------------
Enter your choice:
```

---

## System Workflow

The general workflow of the program is:

```text
Start
  |
  v
Display Main Menu
  |
  +----> Register New Patient
  |          |
  |          +--> Enter Patient Details
  |          |
  |          +--> Select Urgency
  |          |
  |          +--> Select Specialty
  |          |
  |          +--> Calculate Waiting Time
  |          |
  |          +--> Admission?
  |                 |
  |                 +--> Yes → Select Ward → Assign Bed
  |                 |
  |                 +--> No
  |          |
  |          +--> Calculate Bill
  |
  +----> Display Bed Status
  |
  +----> Display Patients
  |
  +----> Search Patient
  |
  +----> Display Patient Priority Order
  |
  +----> Generate Hospital Report
  |
  +----> Save Bed Status and Exit
  |
  v
End
```

---

## Project Structure

The project is organized into source, header, documentation, and supporting files.

```text
Smart-Hospital-Resource-Allocation-System---Assignment/
│
├── main.c
├── hospital.c
├── hospital.h
├── README.md
├── beds_status.txt
│
└── Project Report/
    └── Project_Report.pdf
```

The exact file structure may differ depending on the final version committed to the repository.

---

## Testing

The program should be tested using different inputs and situations.

### Test Case 1 – Register Normal Patient

**Input:**

* Valid patient name
* Valid age
* Normal urgency
* Valid specialty
* No ward admission

**Expected Result:**

The patient is successfully registered and the bill is calculated.

---

### Test Case 2 – Register Critical Patient

**Input:**

* Valid patient information
* Critical urgency
* Valid specialty

**Expected Result:**

The patient receives a 50% emergency surcharge on the specialty base fee and appears with higher priority in the priority-order display.

---

### Test Case 3 – Admit Patient

**Input:**

* Patient admission = Yes
* Valid ward
* Valid number of days
* Available bed

**Expected Result:**

The system assigns an available bed and includes the ward cost in the patient's bill.

---

### Test Case 4 – Search Patient

**Input:**

Enter the exact name of a registered patient.

**Expected Result:**

The system displays the matching patient's name and age.

---

### Test Case 5 – Search Non-Existing Patient

**Input:**

Enter a name that is not registered.

**Expected Result:**

```text
Patient not found.
```

---

### Test Case 6 – Bed Unavailable

**Input:**

Select a ward after all beds in that ward have been occupied.

**Expected Result:**

```text
No bed available in this ward.
```

The patient is not admitted and no bed is assigned.

---

### Test Case 7 – Hospital Report

**Input:**

Register several patients with different urgency levels.

**Expected Result:**

The report displays:

* Normal patient count
* Urgent patient count
* Critical patient count
* Total revenue
* Total discounts


## Repository

GitHub Repository:

**https://github.com/suliy-CYBER/Smart-Hospital-Resource-Allocation-System---Assignment**

---

## Project Limitations

The current system is a console-based academic project developed using C.

Some limitations of the current version are:

* Patient records are stored only while the program is running.
* Only bed occupancy information is saved to a file.
* There is no database.
* There is no graphical user interface.
* The system does not include doctor or staff management.
* Patient searching is based on patient name.
* The system uses fixed limits for patients, wards, specialties, and beds.
* Input validation can be further improved.

---

## Future Improvements

The system could be extended in the future by adding:

* Permanent patient record storage.
* Database integration.
* Patient ID generation.
* Doctor and staff management.
* More advanced search options.
* Improved input validation.
* User login and authentication.
* Graphical user interface.
* More detailed hospital reports.
* Complete loading and saving of patient records.
* More advanced resource allocation methods.

---

## Conclusion

The **Smart Hospital & Resource Allocation System** demonstrates how C programming concepts can be applied to a practical hospital resource management problem.

The system combines patient registration, urgency management, specialty selection, waiting-time estimation, bed allocation, billing, patient searching, priority ordering, reporting, and basic file handling.

The project provides practical experience in using arrays, functions, loops, conditional statements, searching, sorting, file handling, and modular programming. Git and GitHub are also used to manage and document the development of the project.


