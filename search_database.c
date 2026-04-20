/*
Name:Chithra M
Date:24-03-2026
Description:Inverted_Search_Project
*/
#include "file_operations.h"
#include <string.h>

int searchdatabase(hash_table arr[])
{
    // Prompt the user to enter a word to search in the database
    char ch[10];
    printf("Enter the word you want to search for: \n");
    scanf("%s", ch);

    // Calculate the hash index based on the first character of the word
    int index;
    if (ch[0] >= 65 && ch[0] <= 92)  // For uppercase letters A-Z
    {
        index = ch[0] - 65;
    }
    else if (ch[0] >= 97 && ch[0] <= 122)  // For lowercase letters a-z
    {
        index = ch[0] - 97;
    }
    else if (ch[0] >= 48 && ch[0] <= 58)  // For numbers 0-9
    {
        index = 26;
    }
    else  // For other characters
    {
        index = 27;
    }

    // Check if there is any word at the calculated index
    if (arr[index].m_link == NULL)
    {
        printf("Word not found in the database.\n");
        return FAILURE;
    }
    else
    {
        // Traverse through the linked list of words at the index
        M_N *temp = arr[index].m_link;
        while (temp != NULL)
        {
            // If the word is found
            if (strcmp(temp->word, ch) == 0)
            {
                printf("The word is: %s\n", temp->word);
                printf("The file count is: %d\n", temp->f_count);
                
                // Print details of all the files where the word appears
                S_N *temp1 = temp->sublink;
                while (temp1 != NULL)
                {
                    printf("The word is present in the file: %s\n", temp1->f_name);
                    printf("Word count in the file: %d\n", temp1->w_count);
                    temp1 = temp1->s_link;
                }

                return SUCCESS;  // Return success when word is found
            }
            temp = temp->m_link;
        }
    }

    // Return failure if the word was not found in the list
    printf("Word not found in the database.\n");
    return FAILURE;
}
