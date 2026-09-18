#include <stdio.h>

struct Patient {
    int id;
    char name[50];
    int age;
};

int main()
{
    printf("====================================\n");
    printf("        SMART HOSPITAL SYSTEM        \n");
    printf("====================================\n");

    printf("\n1. Patient Management\n");
    printf("2. Doctor Management\n");
    printf("3. Appointment Management\n");
    printf("4. Exit\n");

    printf("\nEnter your choice: ");
    int choice;
    scanf("%d", &choice);

    switch(choice) {
    case 1:
    printf("\n--- PATIENT MANAGEMENT ---\n");
    printf("1. Add Patient\n");
    printf("2. View Patients\n");
    printf("3. Back to Main Menu\n");

    printf("\nEnter your choice: ");
    int patientChoice;
    scanf("%d", &patientChoice);

    if (patientChoice == 1) {
    struct Patient patient;

    printf("\n--- ADD PATIENT ---\n");

    printf("Enter Patient ID: ");
    scanf("%d", &patient.id);

    printf("Enter Patient Name: ");
    scanf(" %[^\n]", patient.name);

    printf("Enter Patient Age: ");
    scanf("%d", &patient.age);

    printf("\nPatient added successfully!\n");
    printf("Patient ID: %d\n", patient.id);
    printf("Patient Name: %s\n", patient.name);
    printf("Patient Age: %d\n", patient.age);
}
    else if (patientChoice == 2) {
        printf("\nView Patients selected.\n");
    }
    else if (patientChoice == 3) {
        printf("\nReturning to Main Menu.\n");
    }
    else {
        printf("\nInvalid choice!\n");
    }

    break;
    case 2:
    printf("\n--- DOCTOR MANAGEMENT ---\n");
    printf("1. Add Doctor\n");
    printf("2. View Doctors\n");
    printf("3. Back to Main Menu\n");

    printf("\nEnter your choice: ");
    int doctorChoice;
    scanf("%d", &doctorChoice);

    if (doctorChoice == 1) {
    int doctorID;
    char doctorName[50];
    char specialization[50];

    printf("\n--- ADD DOCTOR ---\n");

    printf("Enter Doctor ID: ");
    scanf("%d", &doctorID);

    printf("Enter Doctor Name: ");
    scanf(" %[^\n]", doctorName);

    printf("Enter Specialization: ");
    scanf(" %[^\n]", specialization);

    printf("\nDoctor added successfully!\n");
    printf("Doctor ID: %d\n", doctorID);
    printf("Doctor Name: %s\n", doctorName);
    printf("Specialization: %s\n", specialization);
}
    else if (doctorChoice == 2) {
        printf("\nView Doctors selected.\n");
    }
    else if (doctorChoice == 3) {
        printf("\nReturning to Main Menu.\n");
    }
    else {
        printf("\nInvalid choice!\n");
    }

    break;
    case 3:
    printf("\n--- APPOINTMENT MANAGEMENT ---\n");
    printf("1. Book Appointment\n");
    printf("2. View Appointments\n");
    printf("3. Back to Main Menu\n");

    printf("\nEnter your choice: ");
    int appointmentChoice;
    scanf("%d", &appointmentChoice);

    if (appointmentChoice == 1) {
    int patientID;
    int doctorID;
    char date[20];
    char time[20];

    printf("\n--- BOOK APPOINTMENT ---\n");

    printf("Enter Patient ID: ");
    scanf("%d", &patientID);

    printf("Enter Doctor ID: ");
    scanf("%d", &doctorID);

    printf("Enter Date: ");
    scanf("%s", date);

    printf("Enter Time: ");
    scanf("%s", time);

    printf("\nAppointment booked successfully!\n");
    printf("Patient ID: %d\n", patientID);
    printf("Doctor ID: %d\n", doctorID);
    printf("Date: %s\n", date);
    printf("Time: %s\n", time);
}
    else if (patientChoice == 2) {
    printf("\n--- VIEW PATIENTS ---\n");
    printf("Patient records will be displayed here.\n");
}
    else if (appointmentChoice == 3) {
        printf("\nReturning to Main Menu.\n");
    }
    else {
        printf("\nInvalid choice!\n");
    }

    break;
    case 4:
        printf("\nExiting Smart Hospital System...\n");
        break;

    default:
        printf("\nInvalid choice!\n");
}

    return 0;
}
