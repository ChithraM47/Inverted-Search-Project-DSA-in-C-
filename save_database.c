/*
Name:Chithra M
Date:24-03-2026
Description:Inverted_Search_Project
*/
// Save the content in a file
#include "file_operations.h"
#include <string.h>

int savefiles(hash_table arr[])
{
    int i;
    
retry:
    // Prompt the user to input the filename to save data
    printf("Enter the filename (with .txt extension) to save the data: \n");
    
    char str[100];
    scanf("%s", str);  // Read the filename from user input
    
    // Check if the file has a valid .txt extension
    const char *ext = strrchr(str, '.');
    if (ext && strcmp(ext, ".txt") == 0)
    {
        // Open the file in write mode
        FILE *fptr = fopen(str, "w");
        if (fptr == NULL)
        {
            // If file cannot be opened, return failure
            printf("Unable to open the file for saving the data.\n");
            return FAILURE;
        }

        // Iterate over all hash table entries
        for (i = 0; i < 28; i++)
        {
            // Check if there are any words in this hash table index
            if (arr[i].m_link != NULL)
            {
                M_N *temp = arr[i].m_link;

                // Iterate through each word in the linked list at this index
                while (temp != NULL)
                {
                    // Save the index, word, and file count into the file
                    fprintf(fptr, "#%d;%s;%d;", i, temp->word, temp->f_count);

                    // If there are associated files for the word
                    if (temp->sublink != NULL)
                    {
                        S_N *temp1 = temp->sublink;

                        // Iterate through the subnodes (files) for the word
                        while (temp1 != NULL)
                        {
                            // Save the file name and word count into the file
                            fprintf(fptr, "%s;%d;", temp1->f_name, temp1->w_count);
                            temp1 = temp1->s_link;  // Move to the next subnode (file)
                        }
                    }

                    temp = temp->m_link;  // Move to the next word in the main linked list

                    // End of word data for this entry
                    fprintf(fptr, "#\n");
                }
            }
        }

        // Close the file after saving the data
        fclose(fptr);
        printf("Data successfully saved to %s\n", str);
        return SUCCESS;
    }
    else
    {
        // If the extension is not .txt, prompt the user to enter a valid extension
        printf("Invalid file extension. Please enter a valid .txt file extension.\n");
        goto retry;  // Retry by asking for the filename again
    }
}
