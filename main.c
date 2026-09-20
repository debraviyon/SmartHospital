#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PATIENTS 100

struct Patient {
    int id;
    char name[50];
    int age;
    int urgencyLevel;
    int specialtyID;
    int admitted;
    int wardID;
    int bedNumber;
    int daysAdmitted;
    float baseFee;
    float surcharge;
    float wardCost;
    float grossTotal;
    float discount;
    float finalAmount;
    float waitingTime;
};

struct Doctor {
    int id;
    char name[50];
    char specialization[50];
};

struct Appointment {
    int patientID;
    int doctorID;
    char date[20];
    char time[20];
};

struct Specialty {
    int id;
    char name[50];
    float baseFee;
    int consultationTime;
    int dailyPatientCap;
};

struct Ward {
    int id;
    char name[50];
    float dailyRate;
    int bedCapacity;
};

struct Specialty specialties[4] = {
    {1, "General Practice (OPD)", 1500.00, 15, 30},
    {2, "Paediatrics", 2500.00, 20, 20},
    {3, "Cardiology", 4500.00, 30, 12},
    {4, "Neurology", 5000.00, 30, 10}
};

struct Ward wards[4] = {
    {1, "General Ward", 3000.00, 20},
    {2, "Paediatric Ward", 6000.00, 10},
    {3, "Surgical Ward", 12000.00, 10},
    {4, "ICU (Intensive Care Unit)", 25000.00, 5}
};

int bedOccupancy[4][20] = {0};
int specialtyQueue[4] = {0};

void displaySpecialties(void)
{
    printf("\n--- AVAILABLE SPECIALTIES ---\n");

    for (int i = 0; i < 4; i++) {
        printf("%d. %s - LKR %.2f - %d mins - Daily Cap: %d\n",
               specialties[i].id,
               specialties[i].name,
               specialties[i].baseFee,
               specialties[i].consultationTime,
               specialties[i].dailyPatientCap);
    }
}

void displayWards(void)
{
    printf("\n--- AVAILABLE HOSPITAL WARDS ---\n");

    for (int i = 0; i < 4; i++) {
        printf("%d. %s - LKR %.2f/day - %d beds\n",
               wards[i].id,
               wards[i].name,
               wards[i].dailyRate,
               wards[i].bedCapacity);
    }
}

float calculateWaitingTime(int specialtyID)
{
    int index = specialtyID - 1;
    return specialtyQueue[index] * specialties[index].consultationTime;
}

float calculateEmergencySurcharge(float baseFee, int urgencyLevel)
{
    if (urgencyLevel == 1) {
        return 0;
    } else if (urgencyLevel == 2) {
        return baseFee * 0.20;
    } else if (urgencyLevel == 3) {
        return baseFee * 0.50;
    } else {
        return 0;
    }
}

float calculateWardCost(int wardID, int daysAdmitted)
{
    if (daysAdmitted <= 0) {
        return 0;
    }

    int index = wardID - 1;
    return daysAdmitted * wards[index].dailyRate;
}

float calculateDiscount(float grossTotal, int age)
{
    if (age < 5 || age > 65) {
        return grossTotal * 0.15;
    } else {
        return 0;
    }
}

float calculateGrossTotal(float baseFee, float surcharge, float wardCost)
{
    return baseFee + surcharge + wardCost;
}

float calculateFinalAmount(float grossTotal, float discount)
{
    return grossTotal - discount;
}

int allocateBed(int wardID)
{
    int index = wardID - 1;

    for (int i = 0; i < wards[index].bedCapacity; i++) {
        if (bedOccupancy[index][i] == 0) {
            bedOccupancy[index][i] = 1;
            return i + 1;
        }
    }

    return 0;
}

void sortPatientsByPriority(struct Patient patients[], int patientCount)
{
    for (int i = 0; i < patientCount - 1; i++) {
        for (int j = 0; j < patientCount - i - 1; j++) {
            if (patients[j].urgencyLevel < patients[j + 1].urgencyLevel) {
                struct Patient temp = patients[j];
                patients[j] = patients[j + 1];
                patients[j + 1] = temp;
            }
        }
    }
}

void savePatientsToFile(struct Patient patients[], int patientCount)
{
    FILE *file = fopen("patients.txt", "w");

    if (file == NULL) {
        printf("\nError: Could not open file.\n");
        return;
    }

    for (int i = 0; i < patientCount; i++) {
        fprintf(file, "Patient ID: PAT-%d\n", patients[i].id);
        fprintf(file, "Name: %s\n", patients[i].name);
        fprintf(file, "Age: %d\n", patients[i].age);
        fprintf(file, "Urgency Level: %d\n", patients[i].urgencyLevel);
        fprintf(file, "Specialty: %s\n",
                specialties[patients[i].specialtyID - 1].name);
        fprintf(file, "Final Amount: LKR %.2f\n", patients[i].finalAmount);
        fprintf(file, "Waiting Time: %.2f minutes\n",
                patients[i].waitingTime);
        fprintf(file, "-----------------------------\n");
    }

    fclose(file);
    printf("\nPatient information saved successfully to patients.txt.\n");
}

int main(void)
{
    struct Patient patients[MAX_PATIENTS];
    int patientCount = 0;

    struct Doctor doctors[MAX_PATIENTS];
    int doctorCount = 0;

    struct Appointment appointments[MAX_PATIENTS];
    int appointmentCount = 0;

    while (1) {
        printf("\n====================================\n");
        printf("        SMART HOSPITAL SYSTEM\n");
        printf("====================================\n");
        printf("1. Patient Management\n");
        printf("2. Doctor Management\n");
        printf("3. Appointment Management\n");
        printf("4. Hospital Resource Summary\n");
        printf("5. Exit\n");

        printf("\nEnter your choice: ");
        int choice;
        scanf("%d", &choice);

        switch (choice) {

        case 1: {
            int patientChoice;

            printf("\n--- PATIENT MANAGEMENT ---\n");
            printf("1. Add Patient\n");
            printf("2. View Patients\n");
            printf("3. Search Patient\n");
            printf("4. View Patients by Priority\n");
            printf("5. Save Patients to File\n");
            printf("6. Back to Main Menu\n");

            printf("\nEnter your choice: ");
            scanf("%d", &patientChoice);

            if (patientChoice == 1) {
                if (patientCount >= MAX_PATIENTS) {
                    printf("\nPatient limit reached!\n");
                    break;
                }

                struct Patient patient;

                printf("\n--- REGISTER PATIENT ---\n");

                patient.id = 1001 + patientCount;
                printf("Patient ID: PAT-%d\n", patient.id);

                printf("Enter Patient Name: ");
                scanf(" %[^\n]", patient.name);

                printf("Enter Patient Age: ");
                scanf("%d", &patient.age);

                printf("\n--- EMERGENCY / TRIAGE LEVEL ---\n");
                printf("1. Normal\n");
                printf("2. Urgent\n");
                printf("3. Critical\n");

                printf("Enter Urgency Level: ");
                scanf("%d", &patient.urgencyLevel);

                while (patient.urgencyLevel < 1 ||
                       patient.urgencyLevel > 3) {
                    printf("Invalid level! Enter 1, 2 or 3: ");
                    scanf("%d", &patient.urgencyLevel);
                }

                displaySpecialties();

                printf("\nEnter Specialty ID: ");
                scanf("%d", &patient.specialtyID);

                while (patient.specialtyID < 1 ||
                       patient.specialtyID > 4) {
                    printf("Invalid Specialty ID! Enter 1-4: ");
                    scanf("%d", &patient.specialtyID);
                }

                patient.baseFee =
                    specialties[patient.specialtyID - 1].baseFee;

                patient.waitingTime =
                    calculateWaitingTime(patient.specialtyID);

                specialtyQueue[patient.specialtyID - 1]++;

                printf("\nIs the patient admitted to a ward?\n");
                printf("1. Yes\n");
                printf("0. No\n");
                printf("Enter choice: ");
                scanf("%d", &patient.admitted);

                while (patient.admitted != 0 &&
                       patient.admitted != 1) {
                    printf("Invalid choice! Enter 1 for Yes or 0 for No: ");
                    scanf("%d", &patient.admitted);
                }

                patient.wardID = 0;
                patient.bedNumber = 0;
                patient.daysAdmitted = 0;

                if (patient.admitted == 1) {
                    displayWards();

                    printf("\nEnter Ward ID: ");
                    scanf("%d", &patient.wardID);

                    while (patient.wardID < 1 ||
                           patient.wardID > 4) {
                        printf("Invalid Ward ID! Enter 1-4: ");
                        scanf("%d", &patient.wardID);
                    }

                    printf("Enter Days Admitted: ");
                    scanf("%d", &patient.daysAdmitted);

                    while (patient.daysAdmitted <= 0) {
                        printf("Days must be greater than 0. Enter again: ");
                        scanf("%d", &patient.daysAdmitted);
                    }

                    patient.bedNumber = allocateBed(patient.wardID);

                    if (patient.bedNumber == 0) {
                        printf("\nNo beds are available in the selected ward!\n");
                        printf("Patient will be registered as an outpatient.\n");

                        patient.admitted = 0;
                        patient.wardID = 0;
                        patient.daysAdmitted = 0;
                    } else {
                        printf("\nBed allocated successfully!\n");
                        printf("Ward: %s\n",
                               wards[patient.wardID - 1].name);
                        printf("Bed Number: %d\n", patient.bedNumber);
                    }
                }

                patient.surcharge =
                    calculateEmergencySurcharge(patient.baseFee,
                                                patient.urgencyLevel);

                patient.wardCost =
                    calculateWardCost(patient.wardID,
                                      patient.daysAdmitted);

                patient.grossTotal =
                    calculateGrossTotal(patient.baseFee,
                                        patient.surcharge,
                                        patient.wardCost);

                patient.discount =
                    calculateDiscount(patient.grossTotal,
                                      patient.age);

                patient.finalAmount =
                    calculateFinalAmount(patient.grossTotal,
                                         patient.discount);

                patients[patientCount] = patient;
                patientCount++;

                printf("\nPatient registered successfully!\n");
                printf("Patient ID: PAT-%d\n", patient.id);
                printf("Patient Name: %s\n", patient.name);
                printf("Patient Age: %d\n", patient.age);

                printf("\n====================================================\n");
                printf("        SMART HOSPITAL ADMISSION & BILL\n");
                printf("====================================================\n");

                printf("Patient ID       : PAT-%d\n", patient.id);
                printf("Patient Name     : %s\n", patient.name);
                printf("Age              : %d Years", patient.age);

                if (patient.age < 5 || patient.age > 65) {
                    printf(" (15%% Subsidy Eligible)\n");
                } else {
                    printf("\n");
                }

                printf("Specialty        : %s\n",
                       specialties[patient.specialtyID - 1].name);

                if (patient.admitted == 1) {
                    printf("Assigned Ward    : %s\n",
                           wards[patient.wardID - 1].name);
                    printf("Assigned Bed     : #%02d\n",
                           patient.bedNumber);
                } else {
                    printf("Assigned Ward    : Outpatient / OPD\n");
                }

                if (patient.urgencyLevel == 1) {
                    printf("Urgency Level    : Level 1 (Normal)\n");
                } else if (patient.urgencyLevel == 2) {
                    printf("Urgency Level    : Level 2 (Urgent)\n");
                } else {
                    printf("Urgency Level    : Level 3 (Critical)\n");
                }

                printf("----------------------------------------------------\n");
                printf("Base Consultation Fee : LKR %.2f\n",
                       patient.baseFee);
                printf("Emergency Surcharge   : LKR %.2f\n",
                       patient.surcharge);
                printf("Ward Stay Cost (%d Days) : LKR %.2f\n",
                       patient.daysAdmitted, patient.wardCost);
                printf("----------------------------------------------------\n");
                printf("Gross Total Bill      : LKR %.2f\n",
                       patient.grossTotal);
                printf("Age Subsidy Discount  : LKR -%.2f\n",
                       patient.discount);
                printf("----------------------------------------------------\n");
                printf("Final Amount Payable  : LKR %.2f\n",
                       patient.finalAmount);
                printf("Estimated Waiting Time: %.2f mins\n",
                       patient.waitingTime);
                printf("====================================================\n");

            } else if (patientChoice == 2) {
                printf("\n--- VIEW PATIENTS ---\n");

                if (patientCount == 0) {
                    printf("\nNo patients available.\n");
                } else {
                    for (int i = 0; i < patientCount; i++) {
                        printf("\n----------------------------------------\n");
                        printf("Patient %d\n", i + 1);
                        printf("Patient ID: PAT-%d\n",
                               patients[i].id);
                        printf("Patient Name: %s\n",
                               patients[i].name);
                        printf("Patient Age: %d\n",
                               patients[i].age);

                        if (patients[i].urgencyLevel == 1) {
                            printf("Urgency Level: Level 1 (Normal)\n");
                        } else if (patients[i].urgencyLevel == 2) {
                            printf("Urgency Level: Level 2 (Urgent)\n");
                        } else {
                            printf("Urgency Level: Level 3 (Critical)\n");
                        }

                        printf("Specialty: %s\n",
                               specialties[patients[i].specialtyID - 1].name);

                        if (patients[i].admitted == 1) {
                            printf("Ward: %s\n",
                                   wards[patients[i].wardID - 1].name);
                            printf("Bed Number: %d\n",
                                   patients[i].bedNumber);
                            printf("Days Admitted: %d\n",
                                   patients[i].daysAdmitted);
                        } else {
                            printf("Ward: Outpatient / OPD\n");
                        }

                        printf("Final Amount: LKR %.2f\n",
                               patients[i].finalAmount);
                        printf("Waiting Time: %.2f minutes\n",
                               patients[i].waitingTime);
                    }
                }

            } else if (patientChoice == 3) {
                int searchID;
                int found = 0;

                printf("\n--- SEARCH PATIENT ---\n");
                printf("Enter Patient ID: ");
                scanf("%d", &searchID);

                for (int i = 0; i < patientCount; i++) {
                    if (patients[i].id == searchID) {
                        printf("\nPatient found!\n");
                        printf("Patient ID: %d\n", patients[i].id);
                        printf("Patient Name: %s\n", patients[i].name);
                        printf("Patient Age: %d\n", patients[i].age);
                        found = 1;
                        break;
                    }
                }

                if (found == 0) {
                    printf("\nPatient not found!\n");
                }

            } else if (patientChoice == 4) {
                printf("\n--- PATIENTS BY PRIORITY ---\n");

                if (patientCount == 0) {
                    printf("\nNo patients available.\n");
                } else {
                    sortPatientsByPriority(patients, patientCount);

                    for (int i = 0; i < patientCount; i++) {
                        printf("\n----------------------------------------\n");
                        printf("Patient ID: PAT-%d\n",
                               patients[i].id);
                        printf("Patient Name: %s\n",
                               patients[i].name);
                        printf("Waiting Time: %.2f minutes\n",
                               patients[i].waitingTime);

                        if (patients[i].urgencyLevel == 1) {
                            printf("Urgency: Level 1 (Normal)\n");
                        } else if (patients[i].urgencyLevel == 2) {
                            printf("Urgency: Level 2 (Urgent)\n");
                        } else {
                            printf("Urgency: Level 3 (Critical)\n");
                        }
                    }
                }

            } else if (patientChoice == 5) {
                savePatientsToFile(patients, patientCount);

            } else if (patientChoice == 6) {
                printf("\nReturning to Main Menu.\n");

            } else {
                printf("\nInvalid choice!\n");
            }

            break;
        }

        case 2: {
            int doctorChoice;

            printf("\n--- DOCTOR MANAGEMENT ---\n");
            printf("1. Add Doctor\n");
            printf("2. View Doctors\n");
            printf("3. Search Doctor\n");
            printf("4. Check Doctor Availability\n");
            printf("5. Back to Main Menu\n");

            printf("\nEnter your choice: ");
            scanf("%d", &doctorChoice);

            if (doctorChoice == 1) {
                if (doctorCount >= MAX_PATIENTS) {
                    printf("\nDoctor limit reached!\n");
                    break;
                }

                struct Doctor doctor;
                int idExists = 0;

                printf("\n--- ADD DOCTOR ---\n");
                printf("Enter Doctor ID: ");
                scanf("%d", &doctor.id);

                for (int i = 0; i < doctorCount; i++) {
                    if (doctors[i].id == doctor.id) {
                        idExists = 1;
                        break;
                    }
                }

                if (idExists == 1) {
                    printf("\nDoctor ID already exists!\n");
                } else {
                    printf("Enter Doctor Name: ");
                    scanf(" %[^\n]", doctor.name);

                    printf("Enter Specialization: ");
                    scanf(" %[^\n]", doctor.specialization);

                    doctors[doctorCount] = doctor;
                    doctorCount++;

                    printf("\nDoctor added successfully!\n");
                    printf("Doctor ID: %d\n", doctor.id);
                    printf("Doctor Name: %s\n", doctor.name);
                    printf("Specialization: %s\n",
                           doctor.specialization);
                }

            } else if (doctorChoice == 2) {
                printf("\n--- VIEW DOCTORS ---\n");

                if (doctorCount == 0) {
                    printf("\nNo doctors available.\n");
                } else {
                    for (int i = 0; i < doctorCount; i++) {
                        int doctorAppointments = 0;

                        for (int j = 0; j < appointmentCount; j++) {
                            if (appointments[j].doctorID == doctors[i].id) {
                                doctorAppointments++;
                            }
                        }

                        printf("\nDoctor %d\n", i + 1);
                        printf("Doctor ID: %d\n", doctors[i].id);
                        printf("Doctor Name: %s\n", doctors[i].name);
                        printf("Specialization: %s\n",
                               doctors[i].specialization);
                        printf("Appointments: %d\n",
                               doctorAppointments);
                    }

                    printf("\n--- DOCTOR WORKLOAD SUMMARY ---\n");

                    for (int i = 0; i < doctorCount; i++) {
                        int doctorAppointments = 0;

                        for (int j = 0; j < appointmentCount; j++) {
                            if (appointments[j].doctorID == doctors[i].id) {
                                doctorAppointments++;
                            }
                        }

                        printf("Dr. %s : %d appointment(s)\n",
                               doctors[i].name,
                               doctorAppointments);
                    }
                }

            } else if (doctorChoice == 3) {
                int searchID;
                int found = 0;

                printf("\n--- SEARCH DOCTOR ---\n");
                printf("Enter Doctor ID: ");
                scanf("%d", &searchID);

                for (int i = 0; i < doctorCount; i++) {
                    if (doctors[i].id == searchID) {
                        printf("\nDoctor found!\n");
                        printf("Doctor ID: %d\n", doctors[i].id);
                        printf("Doctor Name: %s\n",
                               doctors[i].name);
                        printf("Specialization: %s\n",
                               doctors[i].specialization);
                        found = 1;
                        break;
                    }
                }

                if (found == 0) {
                    printf("\nDoctor not found!\n");
                }

            } else if (doctorChoice == 4) {
                int searchDoctorID;
                int hasAppointment = 0;
                int doctorFound = 0;
                char checkDate[20];
                char checkTime[20];

                printf("\n--- CHECK DOCTOR AVAILABILITY ---\n");
                printf("Enter Doctor ID: ");
                scanf("%d", &searchDoctorID);

                printf("Enter Date: ");
                scanf("%19s", checkDate);

                printf("Enter Time: ");
                scanf("%19s", checkTime);

                for (int i = 0; i < doctorCount; i++) {
                    if (doctors[i].id == searchDoctorID) {
                        doctorFound = 1;
                        break;
                    }
                }

                if (doctorFound == 0) {
                    printf("\nDoctor not found!\n");
                } else {
                    for (int i = 0; i < appointmentCount; i++) {
                        if (appointments[i].doctorID == searchDoctorID &&
                            strcmp(appointments[i].date, checkDate) == 0 &&
                            strcmp(appointments[i].time, checkTime) == 0) {
                            hasAppointment = 1;
                            break;
                        }
                    }

                    if (hasAppointment == 1) {
                        printf("\nDoctor has existing appointment.\n");
                        printf("Please check the appointment schedule.\n");
                    } else {
                        printf("\nDoctor is currently available.\n");
                    }
                }

            } else if (doctorChoice == 5) {
                printf("\nReturning to Main Menu.\n");

            } else {
                printf("\nInvalid choice!\n");
            }

            break;
        }

        case 3: {
            int appointmentChoice;

            printf("\n--- APPOINTMENT MANAGEMENT ---\n");
            printf("1. Book Appointment\n");
            printf("2. View Appointments\n");
            printf("3. Search Appointment\n");
            printf("4. Back to Main Menu\n");

            printf("\nEnter your choice: ");
            scanf("%d", &appointmentChoice);

            if (appointmentChoice == 1) {
                if (appointmentCount >= MAX_PATIENTS) {
                    printf("\nAppointment limit reached!\n");
                    break;
                }

                struct Appointment appointment;

                printf("\n--- BOOK APPOINTMENT ---\n");

                printf("Enter Patient ID: ");
                scanf("%d", &appointment.patientID);

                printf("Enter Doctor ID: ");
                scanf("%d", &appointment.doctorID);

                int patientFound = 0;
                int doctorFound = 0;

                for (int i = 0; i < patientCount; i++) {
                    if (patients[i].id == appointment.patientID) {
                        patientFound = 1;
                        break;
                    }
                }

                for (int i = 0; i < doctorCount; i++) {
                    if (doctors[i].id == appointment.doctorID) {
                        doctorFound = 1;
                        break;
                    }
                }

                if (patientFound == 0) {
                    printf("\nPatient ID does not exist!\n");
                } else if (doctorFound == 0) {
                    printf("\nDoctor ID does not exist!\n");
                } else {
                    printf("Enter Date: ");
                    scanf("%19s", appointment.date);

                    printf("Enter Time: ");
                    scanf("%19s", appointment.time);

                    int conflict = 0;

                    for (int i = 0; i < appointmentCount; i++) {
                        if (appointments[i].doctorID == appointment.doctorID &&
                            strcmp(appointments[i].date,
                                   appointment.date) == 0 &&
                            strcmp(appointments[i].time,
                                   appointment.time) == 0) {
                            conflict = 1;
                            break;
                        }
                    }

                    if (conflict == 1) {
                        printf("\nDoctor is already booked at this date and time!\n");
                    } else {
                        appointments[appointmentCount] = appointment;
                        appointmentCount++;

                        printf("\nAppointment booked successfully!\n");
                        printf("Patient ID: %d\n", appointment.patientID);
                        printf("Doctor ID: %d\n", appointment.doctorID);
                        printf("Date: %s\n", appointment.date);
                        printf("Time: %s\n", appointment.time);
                    }
                }

            } else if (appointmentChoice == 2) {
                printf("\n--- VIEW APPOINTMENTS ---\n");

                if (appointmentCount == 0) {
                    printf("\nNo appointments available.\n");
                } else {
                    for (int i = 0; i < appointmentCount; i++) {
                        printf("\nAppointment %d\n", i + 1);
                        printf("Patient ID: %d\n",
                               appointments[i].patientID);
                        printf("Doctor ID: %d\n",
                               appointments[i].doctorID);
                        printf("Date: %s\n", appointments[i].date);
                        printf("Time: %s\n", appointments[i].time);
                    }
                }

            } else if (appointmentChoice == 3) {
                int searchID;
                int found = 0;

                printf("\n--- SEARCH APPOINTMENT ---\n");
                printf("Enter Patient ID or Doctor ID: ");
                scanf("%d", &searchID);

                for (int i = 0; i < appointmentCount; i++) {
                    if (appointments[i].patientID == searchID ||
                        appointments[i].doctorID == searchID) {

                        printf("\nAppointment found!\n");
                        printf("Patient ID: %d\n",
                               appointments[i].patientID);
                        printf("Doctor ID: %d\n",
                               appointments[i].doctorID);
                        printf("Date: %s\n", appointments[i].date);
                        printf("Time: %s\n", appointments[i].time);

                        found = 1;
                    }
                }

                if (found == 0) {
                    printf("\nAppointment not found!\n");
                }

            } else if (appointmentChoice == 4) {
                printf("\nReturning to Main Menu.\n");

            } else {
                printf("\nInvalid choice!\n");
            }

            break;
        }

        case 4: {
            int normalPatients = 0;
            int urgentPatients = 0;
            int criticalPatients = 0;
            int admittedPatients = 0;
            int totalBeds = 0;
            int totalOccupiedBeds = 0;
            float totalRevenue = 0;
            float admissionRate = 0;
            float averageRevenue = 0;

            printf("\n====================================\n");
            printf("       HOSPITAL RESOURCE SUMMARY\n");
            printf("====================================\n");

            printf("\nTotal Registered Patients: %d\n", patientCount);
            printf("Total Doctors: %d\n", doctorCount);
            printf("Total Appointments: %d\n", appointmentCount);

            for (int i = 0; i < patientCount; i++) {
                totalRevenue += patients[i].finalAmount;

                if (patients[i].admitted == 1) {
                    admittedPatients++;
                }

                if (patients[i].urgencyLevel == 1) {
                    normalPatients++;
                } else if (patients[i].urgencyLevel == 2) {
                    urgentPatients++;
                } else if (patients[i].urgencyLevel == 3) {
                    criticalPatients++;
                }
            }

            int outpatientPatients = patientCount - admittedPatients;

            if (patientCount > 0) {
                admissionRate =
                    ((float)admittedPatients / patientCount) * 100;
                averageRevenue = totalRevenue / patientCount;
            }

            printf("\n--- PATIENT SUMMARY ---\n");
            printf("Total Patients       : %d\n", patientCount);
            printf("Admitted Patients    : %d\n", admittedPatients);
            printf("Outpatient Patients  : %d\n", outpatientPatients);
            printf("Admission Rate       : %.1f%%\n", admissionRate);

            if (patientCount > 0) {
                int highestPriority = 0;

                for (int i = 1; i < patientCount; i++) {
                    if (patients[i].urgencyLevel >
                        patients[highestPriority].urgencyLevel) {
                        highestPriority = i;
                    }
                }

                printf("\n--- HIGHEST PRIORITY PATIENT ---\n");
                printf("Patient ID: PAT-%d\n",
                       patients[highestPriority].id);
                printf("Patient Name: %s\n",
                       patients[highestPriority].name);

                if (patients[highestPriority].urgencyLevel == 1) {
                    printf("Urgency Level: Level 1 (Normal)\n");
                } else if (patients[highestPriority].urgencyLevel == 2) {
                    printf("Urgency Level: Level 2 (Urgent)\n");
                } else {
                    printf("Urgency Level: Level 3 (Critical)\n");
                }
            }

            printf("\n--- TRIAGE SUMMARY ---\n");
            printf("Normal Patients   : %d\n", normalPatients);
            printf("Urgent Patients   : %d\n", urgentPatients);
            printf("Critical Patients : %d\n", criticalPatients);

            printf("\n--- REVENUE SUMMARY ---\n");
            printf("Total Expected Revenue       : LKR %.2f\n",
                   totalRevenue);
            printf("Average Revenue per Patient  : LKR %.2f\n",
                   averageRevenue);

            printf("\n--- WARD BED OCCUPANCY ---\n");

            for (int i = 0; i < 4; i++) {
                int occupiedBeds = 0;

                for (int j = 0; j < wards[i].bedCapacity; j++) {
                    if (bedOccupancy[i][j] == 1) {
                        occupiedBeds++;
                    }
                }

                float occupancyRate =
                    ((float)occupiedBeds / wards[i].bedCapacity) * 100;

                printf("%s: %d / %d beds occupied (%.1f%%)\n",
                       wards[i].name,
                       occupiedBeds,
                       wards[i].bedCapacity,
                       occupancyRate);

                if (occupiedBeds == wards[i].bedCapacity) {
                    printf("Status: FULL\n");
                } else {
                    printf("Status: Beds Available\n");
                }

                totalBeds += wards[i].bedCapacity;
                totalOccupiedBeds += occupiedBeds;
            }

            printf("\n--- TOTAL BED SUMMARY ---\n");
            printf("Total Hospital Beds    : %d\n", totalBeds);
            printf("Occupied Hospital Beds : %d\n",
                   totalOccupiedBeds);
            printf("Available Hospital Beds: %d\n",
                   totalBeds - totalOccupiedBeds);

            float bedAvailabilityRate = 0;

            if (totalBeds > 0) {
                bedAvailabilityRate =
                    ((float)(totalBeds - totalOccupiedBeds) /
                     totalBeds) * 100;
            }

            printf("Bed Availability Rate  : %.1f%%\n",
                   bedAvailabilityRate);

            printf("\n--- SPECIALTY CAPACITY SUMMARY ---\n");

            for (int i = 0; i < 4; i++) {
                float capacityUsed =
                    ((float)specialtyQueue[i] /
                     specialties[i].dailyPatientCap) * 100;

                printf("\n%s\n", specialties[i].name);
                printf("Patients: %d / %d\n",
                       specialtyQueue[i],
                       specialties[i].dailyPatientCap);
                printf("Capacity Used: %.1f%%\n",
                       capacityUsed);

                if (specialtyQueue[i] >=
                    specialties[i].dailyPatientCap) {
                    printf("Status: DAILY CAP REACHED\n");
                } else {
                    printf("Status: Capacity Available\n");
                }
            }

            printf("\n====================================\n");
            break;
        }

        case 5:
            printf("\nExiting Smart Hospital System...\n");
            return 0;

        default:
            printf("\nInvalid choice!\n");
        }
    }

    return 0;
}
