/*
Name:Chithra M
Date:24-03-2026
Description:Inverted_Search_Project
*/
#include "file_operations.h"
#include <string.h>

int updatedatabase(hash_table arr[])
{
    // Start the file reading process for database update
back:
    printf("Please enter the filename to update the database (must have a .txt extension): \n");
    char filename[100];
    scanf("%s", filename);

    // Check if the file has the correct .txt extension
    const char *ext = strrchr(filename, '.');
    if (ext && strcmp(ext, ".txt") == 0)
    {
        FILE *fptr = fopen(filename, "r");
        if (fptr == NULL)
        {
            printf("Failed to open the file. Please check the file path and try again.\n");
            return FAILURE;
        }

        char ch = fgetc(fptr);
        if (ch == '#')
        {
            // Check if the file ends with a '#', indicating it's formatted correctly
            fseek(fptr, -2, SEEK_END);
            if (fgetc(fptr) == '#')
            {
                rewind(fptr);
                char line[100];
                // Process each line in the file
                while (fscanf(fptr, "%s", line) != EOF)
                {
                    char *token = strtok(line, "#;");
                    int index = atoi(token);  // Extract index for the word
                    char *word = strtok(NULL, ";");  // Extract the word

                    // Allocate memory for the new main node
                    M_N *new_main = malloc(sizeof(M_N));
                    if (new_main == NULL)
                    {
                        fclose(fptr);
                        printf("Memory allocation failed.\n");
                        return FAILURE;
                    }

                    M_N *temp = arr[index].m_link;
                    if (temp == NULL)
                    {
                        // If no word exists at the index, create the first node
                        arr[index].m_link = new_main;
                        strcpy(new_main->word, word);
                        new_main->sublink = NULL;
                        new_main->m_link = NULL;
                    }
                    else
                    {
                        // Traverse the list and add the new word at the end
                        while (temp->m_link != NULL)
                        {
                            temp = temp->m_link;
                        }
                        temp->m_link = new_main;
                        strcpy(new_main->word, word);
                        new_main->sublink = NULL;
                    }

                    // Process the file count and subnodes (file name and word count)
                    char *file_count_str = strtok(NULL, ";");
                    int file_count = atoi(file_count_str);
                    new_main->f_count = file_count;

                    S_N *subnode_temp = new_main->sublink;
                    for (int i = 0; i < file_count; i++)
                    {
                        S_N *subnode = malloc(sizeof(S_N));
                        if (subnode == NULL)
                        {
                            fclose(fptr);
                            printf("Memory allocation for subnode failed.\n");
                            return FAILURE;
                        }

                        char *filename = strtok(NULL, ";");
                        char *word_count_str = strtok(NULL, ";");
                        int word_count = atoi(word_count_str);
                        subnode->w_count = word_count;
                        strcpy(subnode->f_name, filename);
                        subnode->s_link = NULL;

                        if (subnode_temp == NULL)
                        {
                            new_main->sublink = subnode;
                            subnode_temp = subnode;
                        }
                        else
                        {
                            // Add the subnode to the list of subnodes
                            while (subnode_temp->s_link != NULL)
                            {
                                subnode_temp = subnode_temp->s_link;
                            }
                            subnode_temp->s_link = subnode;
                        }
                    }
                }
            }
            else
            {
                fclose(fptr);
                printf("File format is incorrect. Missing ending '#'.\n");
                return FAILURE;
            }
        }
        else
        {
            fclose(fptr);
            printf("File does not start with a '#' character, indicating an invalid format.\n");
            return FAILURE;
        }

        fclose(fptr);
        printf("Database successfully updated.\n");
        return SUCCESS;
    }
    else
    {
        printf("Invalid file extension. Please enter a valid .txt file to update the database.\n");
        goto back;  // Prompt again for valid file input
    }
}

// Function to remove duplicate files from the update process
void duplicate(hash_table arr[], FL_LST **head)
{
    // Iterate through each index in the hash table
    for (int i = 0; i < 28; i++)
    {
        M_N *current_main = arr[i].m_link;

        // Iterate through all main nodes in the hash table
        while (current_main != NULL)
        {
            // For each main node, iterate through all subnodes
            S_N *current_sub = current_main->sublink;

            // Create a temporary pointer to the address of the head of the linked list of files
            FL_LST *temp = *head;
            FL_LST *prev = NULL;

            // Iterate through the linked list of files
            while (temp != NULL)
            {
                int found = 0;  // Flag to track whether the file is found in the subnodes

                // Traverse the subnode list for the current main node
                current_sub = current_main->sublink;
                while (current_sub != NULL)
                {
                    // If a matching file name is found, set the flag to 1
                    if (strcmp(temp->file_name, current_sub->f_name) == 0)
                    {
                        found = 1;
                        break;  // Exit the loop as a match is found
                    }
                    current_sub = current_sub->s_link;
                }

                if (found)
                {
                    // Remove the current temp node from the linked list if the file is found
                    if (prev == NULL)
                    {
                        // If prev is NULL, temp is the first node in the list
                        *head = temp->link;
                    }
                    else
                    {
                        // Otherwise, link the previous node to the next node
                        prev->link = temp->link;
                    }

                    // Free the memory of the removed node
                    FL_LST *to_delete = temp;
                    temp = temp->link;
                    free(to_delete);  // Free the memory
                }
                else
                {
                    // If no match is found, move to the next node in the linked list
                    prev = temp;
                    temp = temp->link;
                }
            }

            // Move to the next main node in the hash table
            current_main = current_main->m_link;
        }
    }

    printf("Duplicate files removed successfully.\n");
}
