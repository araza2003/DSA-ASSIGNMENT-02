#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int no_of_customers = 0;

typedef struct Customer
{
    int customerID;
    struct Customer *nextCustomer;
} Customer;

int count = 1;

Customer *FirstCustomer = NULL;

void printList()
{
    Customer *current_customer = FirstCustomer;
    while (current_customer != NULL)
    {
        printf("The Element is: %d\n", current_customer->customerID);
        current_customer = current_customer->nextCustomer;
    }
}

void ADD(int ID)
{
    Customer *newCustomer = (Customer *)malloc(sizeof(Customer));
    newCustomer->customerID = ID;
    newCustomer->nextCustomer = NULL;

    if (FirstCustomer == NULL)
    {
        FirstCustomer = newCustomer;
    }
    else
    {
        Customer *current_customer = FirstCustomer;
        while (current_customer->nextCustomer != NULL)
        {
            current_customer = current_customer->nextCustomer;
        }
        current_customer->nextCustomer = newCustomer;
    }

    printf("Added element: %d\n", ID);
    no_of_customers = no_of_customers + 1;
}

void DELETE()
{
    if (FirstCustomer == NULL)
    {
        printf("List is empty, cannot delete.\n");
        return;
    }
    else if (FirstCustomer->nextCustomer == NULL)
    {
        free(FirstCustomer);
        FirstCustomer = NULL;
    }
    else
    {
        Customer *previous_to_current_customer = FirstCustomer;
        Customer *current_customer = FirstCustomer->nextCustomer;

        while (current_customer->nextCustomer != NULL)
        {
            current_customer = current_customer->nextCustomer;
            previous_to_current_customer = previous_to_current_customer->nextCustomer;
        }

        previous_to_current_customer->nextCustomer = NULL;
        free(current_customer);
    }
    printf("Last element deleted!\n");
    no_of_customers = no_of_customers - 1;
}

void END()
{
    printf("File ended.\n");
}

void SplitList(Customer *source, Customer **frontRef, Customer **backRef);
Customer *MergeLists(Customer *a, Customer *b);

void MergeSort(Customer **headRef)
{
    Customer *head = *headRef;
    Customer *a;
    Customer *b;

    if (head == NULL || head->nextCustomer == NULL)
    {
        return;
    }

    SplitList(head, &a, &b);

    MergeSort(&a);
    MergeSort(&b);

    *headRef = MergeLists(a, b);
}

void SplitList(Customer *source, Customer **frontRef, Customer **backRef)
{
    Customer *slow;
    Customer *fast;

    slow = source;
    fast = source->nextCustomer;

    while (fast != NULL)
    {
        fast = fast->nextCustomer;
        if (fast != NULL)
        {
            slow = slow->nextCustomer;
            fast = fast->nextCustomer;
        }
    }

    *frontRef = source;
    *backRef = slow->nextCustomer;
    slow->nextCustomer = NULL;
}

Customer *MergeLists(Customer *a, Customer *b)
{
    Customer *result = NULL;

    if (a == NULL)
        return b;
    else if (b == NULL)
        return a;

    if (a->customerID <= b->customerID)
    {
        result = a;
        result->nextCustomer = MergeLists(a->nextCustomer, b);
    }
    else
    {
        result = b;
        result->nextCustomer = MergeLists(a, b->nextCustomer);
    }

    return result;
}

void calculateMedian(Customer *head, int count)
{
    int middleIndex = count / 2;
    Customer *current_customer = head;
    int middleID;

    if (count % 2 == 0)
    {
        // Even number of elements
        int count = 0;
        int previousID = 0;
        while (current_customer != NULL)
        {
            if (count == middleIndex - 1)
            {
                previousID = current_customer->customerID;
            }
            else if (count == middleIndex)
            {
                printf("The median ids are: %d, %d\n", previousID, current_customer->customerID);
                return;
            }
            current_customer = current_customer->nextCustomer;
            count++;
        }
    }
    else
    {
        // Odd number of elements
        int count = 0;
        while (current_customer != NULL)
        {
            if (count == middleIndex)
            {
                printf("The median id is: %d\n", current_customer->customerID);
                return;
            }
            current_customer = current_customer->nextCustomer;
            count++;
        }
    }

    printf("List has fewer than 2 elements, cannot compute median.\n");
}

int main() 
{
    int id;
    char command[15];
    FILE* input_file = fopen("myFile.txt", "r");
    while (fscanf(input_file, "%s", command) != EOF)
    {
        if (strcmp(command, "ADD") == 0)
        {
            fscanf(input_file, "%d", &id);
            ADD(id);
        }
        else if (strcmp(command, "DELETE") == 0)
        {
            DELETE();
        }
        else if (strcmp(command, "END") == 0)
        {
            calculateMedian(FirstCustomer,no_of_customers);
            break;
        }
        else
        {
            printf("Invalid command: %s\n", command);
        }
    }
    fclose(input_file);

    return 0;
}