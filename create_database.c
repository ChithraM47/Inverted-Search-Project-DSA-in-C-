/*
Name:Chithra M
Date:22-03-2026
Description:Inverted_Search_Project
*/
#include "file_operations.h"
#include <string.h>

int create_database(hash_table arr[], FL_LST *head)
{
    FL_LST *temp = head; 
    while (temp != NULL)
    {
        // Open the file
        FILE *fptr = fopen(temp->file_name, "r");
        if (fptr == NULL)
        {
            printf("Error: Could not open file %s\n", temp->file_name);
            return FAILURE;
        }

        char str[20];
        int ind;
        
        // Read each word from the file
        while (fscanf(fptr, "%s", str) != EOF)
        {
            // Determine the index based on the first character of the word
            if (str[0] >= 65 && str[0] <= 90)  // Uppercase letter
            {
                ind = str[0] - 65;
            }
            else if (str[0] >= 97 && str[0] <= 122)  // Lowercase letter
            {
                ind = str[0] - 97;
            }
            else if (str[0] >= 48 && str[0] <= 57)  // Digits
            {
                ind = 26;
            }
            else  // Special characters
            {
                ind = 27;
            }

            M_N *temp1 = arr[ind].m_link;
            M_N *prev = NULL;
            int flag = 0;

            // Check if the word already exists in the main node list
            while (temp1 != NULL)
            {
                if (strcmp(temp1->word, str) == 0)
                {
                    flag = 1;
                    break;
                }
                prev = temp1;
                temp1 = temp1->m_link;
            }

            if (flag)
            {
                // Word exists, check for file in the subnode list
                S_N *temp2 = temp1->sublink;
                S_N *prev_sub = NULL;
                int flag2 = 0;

                // Check if the file is already in the subnode list
                while (temp2 != NULL)
                {
                    if (strcmp(temp2->f_name, temp->file_name) == 0)
                    {
                        temp2->w_count++;  // Increment word count if file exists
                        flag2 = 1;
                        break;
                    }
                    prev_sub = temp2;
                    temp2 = temp2->s_link;
                }

                // File not found in the subnodes, add a new subnode
                if (!flag2)
                {
                    S_N *new_sub = malloc(sizeof(S_N));
                    if (new_sub == NULL)
                    {
                        fclose(fptr);
                        return FAILURE;
                    }
                    strcpy(new_sub->f_name, temp->file_name);
                    temp1->f_count++;
                    new_sub->w_count = 1;
                    new_sub->s_link = NULL;

                    // Attach the new subnode to the list
                    if (prev_sub != NULL)
                    {
                        prev_sub->s_link = new_sub;
                    }
                    else
                    {
                        temp1->sublink = new_sub;
                    }
                }
            }
            else
            {
                // Word not found, create a new main node and subnode
                M_N *new_main = malloc(sizeof(M_N));
                S_N *new_sub = malloc(sizeof(S_N));
                if (new_main == NULL || new_sub == NULL)
                {
                    fclose(fptr);
                    return FAILURE;
                }

                // Initialize the new main node
                strcpy(new_main->word, str);
                new_main->f_count = 1;
                new_main->m_link = NULL;
                new_main->sublink = new_sub;

                // Initialize the new subnode
                strcpy(new_sub->f_name, temp->file_name);
                new_sub->w_count = 1;
                new_sub->s_link = NULL;

                // Attach the new main node to the hash table
                if (arr[ind].m_link == NULL)
                {
                    arr[ind].m_link = new_main;  // First entry in this index
                }
                else
                {
                    prev->m_link = new_main;  // Attach to the previous node
                }
            }
        }
        fclose(fptr);
        temp = temp->link;  // Move to the next file in the list
    }

    printf("Database creation completed successfully!\n");
    return SUCCESS;
}
