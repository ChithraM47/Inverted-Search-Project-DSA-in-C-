/*
Name:Chithra M
Date:24-03-2026
Description:Inverted_Search_Project
*/
#include<stdio.h>
#include "file_operations.h"
#include<string.h>
#include<stdlib.h>

int read_and_validations(int argc, char *argv[], FL_LST **head)
{
    int i;
    for (i = 1; i < argc; i++)
    {
        if (strstr(argv[i], ".txttxt"))
        {
            printf("Error: Invalid file extension. Please use the '.txt' extension.\n");
            continue;
        }
        if (strstr(argv[i], ".txt") != NULL)  // Checking the file extension
        {
            // Check if the file is present
            FILE *fptr = fopen(argv[i], "r"); // Open in read mode
            if (fptr == NULL)
            {
                printf("Error: File '%s' is not found.\n", argv[i]);
                continue;
            }
            else
            {
                char ch = getc(fptr);
                if (ch == EOF)
                {
                    printf("Warning: File '%s' is empty.\n", argv[i]);
                    continue;
                }
                int flag = 0;
                for (int j = 1; j < i; j++)
                {
                    if (strcmp(argv[j], argv[i]) == 0)
                    {
                        printf("Warning: Duplicate file '%s' found.\n", argv[i]);
                        flag = 1;
                        continue;
                    }
                }
                if (!flag)
                {
                    if (insert_last(head, argv[i]) == FAILURE)
                    {
                        printf("Error: Failed to insert file '%s' into the list.\n", argv[i]);
                        continue;
                    }
                    printf("File '%s' added successfully to the list.\n", argv[i]);
                }
            }
        }
        else
        {
            printf("Error: Invalid file '%s'. Please provide a valid .txt file.\n", argv[i]);
        }
    }
    printf("File validation completed successfully.\n");
}

// Insert file name at the end of the linked list
int insert_last(FL_LST **head, char *str)
{
    FL_LST *new = malloc(sizeof(FL_LST));
    if (new == NULL)
    {
        printf("Error: Memory allocation failed while creating a new node.\n");
        return FAILURE;
    }

    if ((*head) == NULL)
    {
        (*head) = new;
        strcpy(new->file_name, str);
        new->link = NULL;
        return SUCCESS;
    }

    FL_LST *temp = (*head);
    while (temp->link != NULL)
    {
        if (strcmp(new->file_name, str) == 0)
        {
            printf("Warning: Duplicate file '%s' already exists in the list.\n", str);
            return SUCCESS;
        }
        temp = temp->link;
    }

    temp->link = new;
    strcpy(new->file_name, str);
    new->link = NULL;
    printf("File '%s' inserted successfully.\n", str);
    return SUCCESS;
}

// Print the list of inserted files
void print_list(FL_LST *head)
{
    if (head == NULL)
    {
        printf("Error: The list is empty.\n");
    }
    else
    {
        printf("List of files:\n");
        while (head)
        {
            printf("%s -> ", head->file_name);
            head = head->link;
        }
        printf("NULL\n");
    }
}

// Creating the hash table
void create_hashtable(hash_table *HT, int size)
{
    printf("Hash table created successfully with %d entries.\n", size);
    for (int i = 0; i < size; i++)
    {
        HT[i].index = i;
        HT[i].m_link = NULL;
    }
}
