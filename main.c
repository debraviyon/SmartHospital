#include <stdio.h>
#include <string.h>

struct Patient {
    int id;
    char name[50];
    int age;
};

#define MAX_PATIENTS 100

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

int main()
{
    struct Patient patients[MAX_PATIENTS];
    int patientCount = 0;

    struct Doctor doctors[MAX_PATIENTS];
    int doctorCount = 0;

    struct Appointment appointments[MAX_PATIENTS];
    int appointmentCount = 0;

    while (1) {

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
    printf("3. Search Patient\n");
    printf("4. Back to Main Menu\n");

    printf("\nEnter your choice: ");
    int patientChoice;
    scanf("%d", &patientChoice);

    if (patientChoice == 1) {
    struct Patient patient;
    int idExists = 0;

    printf("\n--- ADD PATIENT ---\n");

    printf("Enter Patient ID: ");
    scanf("%d", &patient.id);

    for (int i = 0; i < patientCount; i++) {
       if (patients[i].id == patient.id) {
          idExists = 1;
          break;
       }
   }
   if (idExists == 1) {
      printf("\nPatient ID already exists!\n");
   }
   else {

    printf("Enter Patient Name: ");
    scanf(" %[^\n]", patient.name);

    printf("Enter Patient Age: ");
    scanf("%d", &patient.age);

    patients[patientCount] = patient;
    patientCount++;

    printf("\nPatient added successfully!\n");
    printf("Patient ID: %d\n", patient.id);
    printf("Patient Name: %s\n", patient.name);
    printf("Patient Age: %d\n", patient.age);
   }
}
    else if (patientChoice == 2) {
    printf("\n--- VIEW PATIENTS ---\n");

    for (int i = 0; i < patientCount; i++) {
        printf("\nPatient %d\n", i + 1);
        printf("Patient ID: %d\n", patients[i].id);
        printf("Patient Name: %s\n", patients[i].name);
        printf("Patient Age: %d\n", patients[i].age);
    }
}

    else if (patientChoice == 3) {
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
}
    else if (patientChoice == 4) {
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
    printf("3. Search Doctor\n");
    printf("4. Back to Main Menu\n");

    printf("\nEnter your choice: ");
    int doctorChoice;
    scanf("%d", &doctorChoice);

    if (doctorChoice == 1) {
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
   }
   else {

    printf("Enter Doctor Name: ");
    scanf(" %[^\n]", doctor.name);

    printf("Enter Specialization: ");
    scanf(" %[^\n]", doctor.specialization);

    doctors[doctorCount] = doctor;
    doctorCount++;

    printf("\nDoctor added successfully!\n");
    printf("Doctor ID: %d\n", doctor.id);
    printf("Doctor Name: %s\n", doctor.name);
    printf("Specialization: %s\n", doctor.specialization);
   }
}

    else if (doctorChoice == 2) {
    printf("\n--- VIEW DOCTORS ---\n");

    for (int i = 0; i < doctorCount; i++) {
        printf("\nDoctor %d\n", i + 1);
        printf("Doctor ID: %d\n", doctors[i].id);
        printf("Doctor Name: %s\n", doctors[i].name);
        printf("Specialization: %s\n", doctors[i].specialization);
    }
}


    else if (doctorChoice == 3) {
    int searchID;
    int found = 0;

    printf("\n--- SEARCH DOCTOR ---\n");
    printf("Enter Doctor ID: ");
    scanf("%d", &searchID);

    for (int i = 0; i < doctorCount; i++) {
        if (doctors[i].id == searchID) {
            printf("\nDoctor found!\n");
            printf("Doctor ID: %d\n", doctors[i].id);
            printf("Doctor Name: %s\n", doctors[i].name);
            printf("Specialization: %s\n", doctors[i].specialization);
            found = 1;
            break;
        }
    }

    if (found == 0) {
        printf("\nDoctor not found!\n");
    }
}
    else if (doctorChoice == 4) {
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
    printf("3. Search Appointment\n");
    printf("4. Back to Main Menu\n");

    printf("\nEnter your choice: ");
    int appointmentChoice;
    scanf("%d", &appointmentChoice);

    if (appointmentChoice == 1) {
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
  }
  else if (doctorFound == 0) {
    printf("\nDoctor ID does not exist!\n");
  }
  else {
    printf("Enter Date: ");
    scanf("%s", appointment.date);

    printf("Enter Time: ");
    scanf("%s", appointment.time);

    int conflict = 0;
    for (int i = 0; i < appointmentCount; i++) {
      if (appointments[i].doctorID == appointment.doctorID &&
        strcmp(appointments[i].date, appointment.date) == 0 &&
        strcmp(appointments[i].time, appointment.time) == 0) {
        conflict = 1;
        break;
      }
   }


    if (conflict == 1) {
        printf("\nDoctor is already booked at this date and time!\n");
    }
    else {
        appointments[appointmentCount] = appointment;
        appointmentCount++;

        printf("\nAppointment booked successfully!\n");
        printf("Patient ID: %d\n", appointment.patientID);
        printf("Doctor ID: %d\n", appointment.doctorID);
        printf("Date: %s\n", appointment.date);
        printf("Time: %s\n", appointment.time);
   }
   }
}
    else if (appointmentChoice == 2) {
    printf("\n--- VIEW APPOINTMENTS ---\n");

    for (int i = 0; i < appointmentCount; i++) {
        printf("\nAppointment %d\n", i + 1);
        printf("Patient ID: %d\n", appointments[i].patientID);
        printf("Doctor ID: %d\n", appointments[i].doctorID);
        printf("Date: %s\n", appointments[i].date);
        printf("Time: %s\n", appointments[i].time);
    }
    }

    else if (appointmentChoice == 3) {
    int searchID;
    int found = 0;

       printf("\n--- SEARCH APPOINTMENT ---\n");
       printf("Enter Patient ID or Doctor ID: ");
       scanf("%d", &searchID);

       for (int i = 0; i < appointmentCount; i++) {
        if (appointments[i].patientID == searchID ||
            appointments[i].doctorID == searchID) {

            printf("\nAppointment found!\n");
            printf("Patient ID: %d\n", appointments[i].patientID);
            printf("Doctor ID: %d\n", appointments[i].doctorID);
            printf("Date: %s\n", appointments[i].date);
            printf("Time: %s\n", appointments[i].time);

            found = 1;
        }
    }

       if (found == 0) {
           printf("\nAppointment not found!\n");
    }

    }
    else if (appointmentChoice == 4) {
        printf("\nReturning to Main Menu.\n");
    }
    else{
       printf("\nInvalid choice!\n");
    }

    break;
    case 4:
        printf("\nExiting Smart Hospital System...\n");
        break;

    default:
    printf("\nInvalid choice!\n");
}

}

return 0;
}
