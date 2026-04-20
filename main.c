/*
Name:Chithra M
Date:24-03-2026
Description:Inverted_Search_Project
*/
#include <stdio.h>
#include <stdlib.h>
#include "file_operations.h"

int main(int argc, char *argv[])
{
    FL_LST *head = NULL;
    if (argc < 2)
    {
        printf("Error: Please provide the required files as command-line arguments.\n");
        return FAILURE;
    }
    int create = 0;
    int update = 0;

    // Call the function for reading and validating the files
    read_and_validations(argc, argv, &head);
    print_list(head);
    hash_table arr[28];
    create_hashtable(arr, 28);

    while (1)
    {
        int num;
        printf("\n1. Create Database\n");
        printf("2. Display Database\n");
        printf("3. Search the Database\n");
        printf("4. Save the Database\n");
        printf("5. Update the Database\n");
        printf("6. Exit\n");
        printf("Please enter your choice (1-6): ");
        scanf("%d", &num);

        switch (num)
        {
        case 1:
        {
            if (create == 0 && update == 1)
            {
                duplicate(arr, &head);
                print_list(head);
                if (create_database(arr, head) == FAILURE)
                {
                    printf("Error: Failed to create the database for new files.\n");
                }
                else
                {
                    printf("Success: Database for new files created successfully.\n");
                    create = 1;
                }
            }
            else if (create == 0 && update == 0)
            {
                if (create_database(arr, head) == FAILURE)
                {
                    printf("Error: Failed to create the database.\n");
                }
                else
                {
                    create = 1;
                    printf("Success: Database created successfully.\n");
                }
            }
            else
            {
                printf("Info: Database has already been created. You cannot create it again.\n");
            }
            break;
        }
        case 2:
            display(arr);
            break;

        case 3:
            if (searchdatabase(arr) == SUCCESS)
            {
                printf("Success: Data found in the database.\n");
            }
            else
            {
                printf("Error: Data not found in the database.\n");
            }
            break;

        case 4:
            if (savefiles(arr) == FAILURE)
            {
                printf("Error: Database could not be saved.\n");
            }
            else
            {
                printf("Success: Database saved successfully.\n");
            }
            break;

        case 5:
            if (update == 0 && create == 0)
            {
                if (updatedatabase(arr) == SUCCESS)
                {
                    printf("Success: Database updated successfully.\n");
                    update = 1;
                }
                else
                {
                    printf("Error: Failed to update the database.\n");
                }
            }
            else
            {
                printf("Info: You cannot update the database after it has been created.\n");
            }
            break;

        case 6:
            printf("Exiting the program. Goodbye!\n");
            exit(0);
            break;

        default:
            printf("Error: Invalid choice. Please enter a number between 1 and 6.\n");
        }

        // Ask user if they want to continue after an operation
        char continue_choice;
        printf("\nDo you want to continue? (yes[Y/y]/no[N/n]): ");
        scanf(" %c", &continue_choice);  // Add space to skip any previous newline character
        if (continue_choice == 'n' || continue_choice == 'N')
        {
            printf("Exiting the program. Goodbye!\n");
            exit(0);
        }
    }
}
