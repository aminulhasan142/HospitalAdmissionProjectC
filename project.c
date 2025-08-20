#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 200

typedef struct
{
    char patient_id[10];
    char patient_name[50];
    char admission_date[11];
    int medical_history_flags[3];
} PatientAdmission;

PatientAdmission patients[MAX_PATIENTS];
int patient_count = 0;

void LoadRecords();
void SaveRecords();
void AddAdmission();
void ViewAdmissions();
void SearchAdmission();
void CountFlagPatients();
void Menu();

void LoadRecords()
{
    FILE *file = fopen("admissions.txt", "r");
    if (!file)
    {
        printf("No admissions.txt found. Starting with empty records.\n");
        return;
    }

    patient_count = 0;
    while (fscanf(file, "%9[^,],%49[^,],%10[^,],%d,%d,%d\n",
                  patients[patient_count].patient_id,
                  patients[patient_count].patient_name,
                  patients[patient_count].admission_date,
                  &patients[patient_count].medical_history_flags[0],
                  &patients[patient_count].medical_history_flags[1],
                  &patients[patient_count].medical_history_flags[2]) == 6)
    {
        patient_count++;
        if (patient_count >= MAX_PATIENTS)
            break;
    }

    fclose(file);
    printf("Loaded %d records from file.\n", patient_count);
}

void SaveRecords()
{
    FILE *file = fopen("admissions.txt", "w");
    if (!file)
    {
        printf("Error opening file for writing!\n");
        return;
    }

    for (int i = 0; i < patient_count; i++)
    {
        fprintf(file, "%s,%s,%s,%d,%d,%d\n",
                patients[i].patient_id,
                patients[i].patient_name,
                patients[i].admission_date,
                patients[i].medical_history_flags[0],
                patients[i].medical_history_flags[1],
                patients[i].medical_history_flags[2]);
    }

    fclose(file);
    printf("Saved %d records to file.\n", patient_count);
}

void AddAdmission()
{
    if (patient_count >= MAX_PATIENTS)
    {
        printf("Cannot add more patients (limit reached).\n");
        return;
    }

    PatientAdmission new_patient;

    printf("Enter Patient ID: ");
    scanf("%9s", new_patient.patient_id);

    printf("Enter Patient Name: ");
    getchar();
    fgets(new_patient.patient_name, sizeof(new_patient.patient_name), stdin);
    new_patient.patient_name[strcspn(new_patient.patient_name, "\n")] = 0;

    printf("Enter Admission Date (YYYY-MM-DD): ");
    scanf("%10s", new_patient.admission_date);

    for (int i = 0; i < 3; i++)
    {
        printf("Enter Flag %d (0=None, 1=Present): ", i + 1);
        scanf("%d", &new_patient.medical_history_flags[i]);
    }

    patients[patient_count++] = new_patient;
    printf("Patient admission added successfully!\n");
}

void ViewAdmissions()
{
    if (patient_count == 0)
    {
        printf("No patient records available.\n");
        return;
    }

    printf("\n--- All Admissions ---\n");
    for (int i = 0; i < patient_count; i++)
    {
        printf("ID: %s | Name: %s | Date: %s | Flags: [%d, %d, %d]\n",
               patients[i].patient_id,
               patients[i].patient_name,
               patients[i].admission_date,
               patients[i].medical_history_flags[0],
               patients[i].medical_history_flags[1],
               patients[i].medical_history_flags[2]);
    }
}

void SearchAdmission()
{
    char search_id[10];
    printf("Enter Patient ID to search: ");
    scanf("%9s", search_id);

    for (int i = 0; i < patient_count; i++)
    {
        if (strcmp(patients[i].patient_id, search_id) == 0)
        {
            printf("Patient Found!\n");
            printf("ID: %s | Name: %s | Date: %s | Flags: [%d, %d, %d]\n",
                   patients[i].patient_id,
                   patients[i].patient_name,
                   patients[i].admission_date,
                   patients[i].medical_history_flags[0],
                   patients[i].medical_history_flags[1],
                   patients[i].medical_history_flags[2]);
            return;
        }
    }

    printf("No patient found with ID %s.\n", search_id);
}

void CountFlagPatients()
{
    int flag_index;
    printf("Enter flag index (1-3): ");
    scanf("%d", &flag_index);

    if (flag_index < 1 || flag_index > 3)
    {
        printf("Invalid flag index!\n");
        return;
    }

    int count = 0;
    for (int i = 0; i < patient_count; i++)
    {
        if (patients[i].medical_history_flags[flag_index - 1] == 1)
        {
            count++;
        }
    }

    printf("Number of patients with Flag %d = 1: %d\n", flag_index, count);
}

void Menu()
{
    int choice;
    do
    {
        printf("\n--- Hospital Patient Admissions ---\n");
        printf("1. Load Records\n");
        printf("2. Save Records\n");
        printf("3. Add New Admission\n");
        printf("4. View All Admissions\n");
        printf("5. Search Admission\n");
        printf("6. Count Patients with Specific Flag\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            LoadRecords();
            break;
        case 2:
            SaveRecords();
            break;
        case 3:
            AddAdmission();
            break;
        case 4:
            ViewAdmissions();
            break;
        case 5:
            SearchAdmission();
            break;
        case 6:
            CountFlagPatients();
            break;
        case 7:
            printf("Exiting program...\n");
            break;
        default:
            printf("Invalid choice! Try again.\n");
        }
    } while (choice != 7);
}

int main()
{
    Menu();
    return 0;
}
