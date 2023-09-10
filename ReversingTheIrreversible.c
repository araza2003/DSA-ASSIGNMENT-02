#include <stdio.h>
#include <stdlib.h>

typedef struct Sanguin_Bank_Transaction_details
{
    int transaction_ID;
    int transaction_Amount;
    struct Sanguin_Bank_Transaction_details *nextTransaction;
} transaction_details;

transaction_details *transaction_head = NULL;

void show_transactions()
{
    while (transaction_head != NULL)
    {
        printf("Transaction ID: %d  Transaction Amount: %d\n", transaction_head->transaction_ID, transaction_head->transaction_Amount);
        transaction_head = transaction_head->nextTransaction;
    }
}

transaction_details *Add_transaction_to_linked_list(int transaction_ID, int transaction_Amount)
{
    transaction_details *Add_Transaction = (transaction_details *)malloc(sizeof(transaction_details));
    Add_Transaction->transaction_ID = transaction_ID;
    Add_Transaction->transaction_Amount = transaction_Amount;
    if (transaction_head == NULL)
    {
        transaction_head = Add_Transaction;
        transaction_head->nextTransaction = NULL;
    }
    else
    {
        transaction_details *current_transaction = transaction_head;
        while (current_transaction->nextTransaction != NULL)
        {
            current_transaction = current_transaction->nextTransaction;
        }
        current_transaction->nextTransaction = Add_Transaction;
        Add_Transaction->nextTransaction = NULL;
    }
}

transaction_details *Delete_tranasction_from_linked_list(int fradulent_transction_ID)
{
    transaction_details *current_transaction = transaction_head;
    transaction_details *next_to_current_transaction = transaction_head->nextTransaction;
    while (next_to_current_transaction->transaction_ID != fradulent_transction_ID)
    {
        current_transaction = current_transaction->nextTransaction;
        next_to_current_transaction = next_to_current_transaction->nextTransaction;
    }
    current_transaction->nextTransaction = next_to_current_transaction->nextTransaction;
}

int main()
{
    FILE *transactions;
    transactions = fopen("ReversingTheIrreversible.txt", "r");
    int number_of_transactions;
    fscanf(transactions, "%d", &number_of_transactions);
    int number_of_fradulent_transactions;
    printf("The number of transactions: %d\n", number_of_transactions);
    fscanf(transactions, "%d", &number_of_fradulent_transactions);
    printf("The number of fradulent transactions: %d\n", number_of_fradulent_transactions);
    int transaction_ID;
    int transaction_Amount;
    int fradulent_transction_ID;
    printf("\nBefore Deleting the fradulent Transactions, the transactions are: \n");
    for (int i = 0; !feof(transactions); i++)
    {
        if (i < number_of_transactions)
        {
            fscanf(transactions, "%d", &transaction_ID);
            fgetc(transactions);
            fscanf(transactions, "%d", &transaction_Amount);
            printf("Transaction ID: %d  Transaction Amount: %d\n", transaction_ID, transaction_Amount);
            Add_transaction_to_linked_list(transaction_ID, transaction_Amount);
        }
        if (i > number_of_transactions)
        {
            fscanf(transactions, "%d", &fradulent_transction_ID);
            printf("Fradulent Transaction: %d\n", fradulent_transction_ID);
            Delete_tranasction_from_linked_list(fradulent_transction_ID);
        }
    }
    printf("\nAfter Deleting the fradulent Transactions, the remaining transactions are: \n");
    show_transactions();
    fclose(transactions);
    return 0;
}