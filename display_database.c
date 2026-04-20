/*
Name:Chithra M
Date:24-03-2026
Description:Inverted_Search_Project
*/
// Display the data
#include "file_operations.h"

void display(hash_table arr[])
{
    int i;

    // Iterate through all indices of the hash table
    for (i = 0; i < 28; i++)
    {
        // Check if there are any words in this index
        if (arr[i].m_link != NULL)
        {
            M_N *temp1 = arr[i].m_link;

            // Traverse the linked list of words in this index
            while (temp1 != NULL)
            {
                // Display the data with tab spaces: index, word, file count
                printf("%d\t%s\t%d", i, temp1->word, temp1->f_count);  // Index, Word, File count
                
                // If the word has associated files (subnodes)
                if (temp1->sublink != NULL)
                {
                    S_N *temp = temp1->sublink;

                    // Traverse the list of subnodes (files associated with the word)
                    while (temp != NULL)
                    {
                        printf("\t%s\t%d\n", temp->f_name, temp->w_count);  // File name and word count in the file
                        
                        temp = temp->s_link;  // Move to the next subnode
                    }
                }
                temp1 = temp1->m_link;  // Move to the next word in the main linked list
            }
        }
    }
}
