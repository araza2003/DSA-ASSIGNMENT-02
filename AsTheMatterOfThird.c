#include <stdio.h>
#include <stdlib.h>

int count = 0;

typedef struct Emmas_List
{
    int number;
    struct Emmas_List *next_number;
    // struct Emmas_List * prev_number;
} Numbers_List;

Numbers_List *list_head = NULL;

void print_list_of_numbers()
{
    Numbers_List *current_number = list_head;
    for (int i = 1; current_number != NULL; i++)
    {
        printf("The number at position %d in Emma's Linked List is: %d\n", i, current_number->number);
        current_number = current_number->next_number;
    }
}

Numbers_List *AsTheMatterOfThird()
{
    Numbers_List *current_number = list_head;
    while (current_number->next_number->next_number->next_number != NULL)
    {
        current_number = current_number->next_number;
    }
    printf("The third last element of Emma's linked list is: %d\n", current_number->number);
}

Numbers_List Add_number_to_Emmas_linked_list(int number)
{
    Numbers_List *List_node = (Numbers_List *)malloc(sizeof(Numbers_List));
    List_node->number = number;
    if (list_head == NULL)
    {
        list_head = List_node;
        list_head->next_number = NULL;
    }
    else
    {
        Numbers_List *current_number = list_head;
        while (current_number->next_number != NULL)
        {
            current_number = current_number->next_number;
        }
        current_number->next_number = List_node;
        List_node->next_number = NULL;
    }
}

int main()
{
    FILE *Emmas_Linked_List;
    Emmas_Linked_List = fopen("AsTheMatterOfThird.txt", "r");
    int number;
    for (int i = 0; !feof(Emmas_Linked_List); i++)
    {
        fscanf(Emmas_Linked_List, "%d", &number);
        count = count + 1;
        Add_number_to_Emmas_linked_list(number);
    }
    fclose(Emmas_Linked_List);
    if (count < 3)
    {
        printf("Error! Linked list not sufficient enough to print third last element!");
    }
    else
    {
        print_list_of_numbers();
    }
    AsTheMatterOfThird();
    return 0;
}