/*
Name:Chithra M
Date:24-03-2026
Description:Inverted_Search_Project
*/
#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include<stdio.h>
#include<stdlib.h>

// Defining success and failure constants
#define SUCCESS 1
#define FAILURE 0

// Structure for the hash table
typedef struct hash_table
{
    int index;
    struct main_node *m_link;
} hash_table;

// Structure for the file linked list
typedef struct File_list
{
    char file_name[20];
    struct File_list *link;
} FL_LST;

// Structure for the main node in the hash table
typedef struct main_node
{
    char word[30];
    struct main_node *m_link;
    int f_count;
    struct sub_node *sublink;
} M_N;

// Structure for the subnode, containing file-specific information
typedef struct sub_node
{
    char f_name[30];
    int w_count;
    struct sub_node *s_link;
} S_N;

// Function declarations
int read_and_validations(int argc, char *argv[], FL_LST **head);
void print_list(FL_LST *head);
int insert_last(FL_LST **head, char *str);
void create_hashtable(hash_table *arr, int size);
int create_database(hash_table arr[], FL_LST *head);
void display(hash_table arr[]);
int savefiles(hash_table arr[]);
int searchdatabase(hash_table arr[]);
int updatedatabase(hash_table arr[]);
void duplicate(hash_table arr[], FL_LST **head);

#endif
