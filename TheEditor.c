#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Editor
{
    int number;
    struct Editor *next_number;
    struct Editor *prev_number;
} Editor;

typedef struct Operation
{
    char name[20];
    int num1;
    int num2;
} Operation;

Editor *head_of_numbers = NULL;
Editor *tail_of_numbers = NULL;
Editor *cursor = NULL;
Operation *op_stack[1000];
int sp = -1;

void push(Operation *op)
{
    sp++;
    op_stack[sp] = op;
}

Operation *pop()
{
    Operation *op = op_stack[sp];
    sp--;
    return op;
}

void print_list_of_numbers()
{
    Editor *curr_num = head_of_numbers;
    while (curr_num != NULL)
    {
        printf("The number is: %d\n", curr_num->number);
        curr_num = curr_num->next_number;
    }
}

void Add_Number_At_The_End(int num_to_add)
{
    Editor *Add_Number = (Editor *)malloc(sizeof(Editor));
    Add_Number->number = num_to_add;
    if (head_of_numbers == NULL)
    {
        head_of_numbers = Add_Number;
        tail_of_numbers = Add_Number;
        Add_Number->next_number = NULL;
        Add_Number->prev_number = NULL;
    }
    else
    {
        Add_Number->prev_number = tail_of_numbers;
        tail_of_numbers->next_number = Add_Number;
        tail_of_numbers = Add_Number;
        Add_Number->next_number = NULL;
    }

    Operation *op = (Operation *)malloc(sizeof(Operation));
    strcpy(op->name, "Add_Number_At_The_End");
    op->num1 = num_to_add;
    op->num2 = -1;
    push(op);
}

void Add_Number_At_An_Index(int num_to_add, int index)
{
    if (head_of_numbers == NULL)
    {
        printf("Invalid function call\n");
    }
    else
    {
        Editor *Add_Number = (Editor *)malloc(sizeof(Editor));
        Add_Number->number = num_to_add;
        Editor *curr_num = head_of_numbers;
        int i = 0;
        while (i != index - 1 && curr_num != NULL)
        {
            curr_num = curr_num->next_number;
            i++;
        }
        if (curr_num == NULL)
        {
            printf("Invalid index\n");
        }
        else
        {
            if (curr_num->prev_number == NULL)
            { 
                head_of_numbers = Add_Number;
                Add_Number->prev_number = NULL;
            }
            else
            {
                Add_Number->prev_number = curr_num->prev_number;
                curr_num->prev_number->next_number = Add_Number;
            }
            Add_Number->next_number = curr_num;
            curr_num->prev_number = Add_Number;
        }

        Operation *op = (Operation *)malloc(sizeof(Operation));
        strcpy(op->name, "Add_Number_At_An_Index");
        op->num1 = index;
        op->num2 = num_to_add;
        push(op);
    }
}

void Delete_Tail()
{
    if (tail_of_numbers == NULL)
    {
        printf("Invalid function call\n");
    }
    else
    {
        Editor *Delete_Number = tail_of_numbers;
        tail_of_numbers = tail_of_numbers->prev_number;
        if (tail_of_numbers == NULL)
        {
            head_of_numbers = NULL;
        }
        else
        {
            tail_of_numbers->next_number = NULL;
        }
        free(Delete_Number);

        Operation *op = (Operation *)malloc(sizeof(Operation));
        strcpy(op->name, "Delete_Tail");
        op->num1 = -1;
        op->num2 = -1;
        push(op);
    }
}

void Delete_Specific_Index(int index_to_delete)
{
    if (head_of_numbers == NULL)
    {
        printf("Invalid function call\n");
    }
    else
    {
        Editor *curr_num = head_of_numbers;
        int i = 0;
        while (i != index_to_delete && curr_num != NULL)
        {
            curr_num = curr_num->next_number;
            i++;
        }
        if (curr_num == NULL)
        {
            printf("Invalid index\n");
        }
        else
        {
            if (curr_num->prev_number == NULL) 
            {
                head_of_numbers = curr_num->next_number;
                if (head_of_numbers == NULL)
                {
                    tail_of_numbers = NULL;
                }
                else
                {
                    head_of_numbers->prev_number = NULL;
                }
            }
            else
            {
                curr_num->prev_number->next_number = curr_num->next_number;
                if (curr_num->next_number == NULL)
                {
                    tail_of_numbers = curr_num->prev_number;
                }
                else
                {
                    curr_num->next_number->prev_number = curr_num->prev_number;
                }
            }
            free(curr_num);
        }

        Operation *op = (Operation *)malloc(sizeof(Operation));
        strcpy(op->name, "Delete_Specific_Index");
        op->num1 = index_to_delete;
        op->num2 = -1;
        push(op);
    }
}

Editor *Add_Immediate_Number(int num_to_add)
{
    if (cursor == NULL)
    {
        printf("Invalid function call: Cursor is NULL\n");
        return NULL;
    }
    Editor *Add_Number = (Editor *)malloc(sizeof(Editor));
    Add_Number->number = num_to_add;
    Add_Number->next_number = cursor->next_number;
    Add_Number->prev_number = cursor;
    if (cursor->next_number == NULL)
    {
        tail_of_numbers = Add_Number;
    }
    else
    {
        cursor->next_number->prev_number = Add_Number;
    }
    cursor->next_number = Add_Number;

    Operation *op = (Operation *)malloc(sizeof(Operation));
    strcpy(op->name, "Add_Immediate_Number");
    op->num1 = num_to_add;
    op->num2 = -1;
    push(op);

    return Add_Number;
}

Editor *Delete_Immediate_Number()
{
    if (cursor == NULL || cursor->next_number == NULL)
    {
        printf("Invalid function call\n");
        return NULL;
    }
    Editor *Delete_Number = cursor->next_number;
    cursor->next_number = Delete_Number->next_number;
    if (Delete_Number->next_number == NULL)
    {
        tail_of_numbers = cursor;
    }
    else
    {
        Delete_Number->next_number->prev_number = cursor;
    }
    free(Delete_Number);

    Operation *op = (Operation *)malloc(sizeof(Operation));
    strcpy(op->name, "Delete_Immediate_Number");
    op->num1 = -1;
    op->num2 = -1;
    push(op);

    return cursor->next_number;
}

Editor *Update_Index_Number(int index, int new_number)
{
    Editor *curr_num = head_of_numbers;
    int i = 0;
    while (i != index && curr_num != NULL)
    {
        curr_num = curr_num->next_number;
        i++;
    }
    if (curr_num == NULL)
    {
        printf("Invalid index\n");
        return NULL;
    }
    else
    {
        int old_number = curr_num->number;
        curr_num->number = new_number;

        Operation *op = (Operation *)malloc(sizeof(Operation));
        strcpy(op->name, "Update_Index_Number");
        op->num1 = index;
        op->num2 = old_number;
        push(op);

        return curr_num;
    }
}

Editor *Update_Immediate_Number(int new_number)
{
    if (cursor == NULL)
    {
        printf("Invalid function call: Cursor is NULL\n");
        return NULL;
    }
    int old_number = cursor->number;
    cursor->number = new_number;

    Operation *op = (Operation *)malloc(sizeof(Operation));
    strcpy(op->name, "Update_Immediate_Number");
    op->num1 = -1;
    op->num2 = old_number;
    push(op);

    return cursor;
}

Editor *Move_Forward(int num_of_positions)
{
    for (int i = 0; i < num_of_positions; i++)
    {
        if (cursor == NULL || cursor->next_number == NULL)
        {
            printf("Invalid function call: Cursor cannot be moved forward\n");
            return NULL;
        }
        cursor = cursor->next_number;
    }
    return cursor;
}

Editor *Move_Backward(int num_of_positions)
{
    for (int i = 0; i < num_of_positions; i++)
    {
        if (cursor == NULL || cursor->prev_number == NULL)
        {
            printf("Invalid function call: Cursor cannot be moved backward\n");
            return NULL;
        }
        cursor = cursor->prev_number;
    }
    return cursor;
}

Editor *Shift_Index(int num_of_positions)
{
    if (cursor == NULL)
    {
        printf("Invalid function call: Cursor is NULL\n");
        return NULL;
    }
    Editor *new_cursor = cursor;
    int i;
    if (num_of_positions >= 0)
    {
        for (i = 0; i < num_of_positions && new_cursor->next_number != NULL; i++)
        {
            new_cursor = new_cursor->next_number;
        }
    }
    else
    {
        for (i = 0; i > num_of_positions && new_cursor->prev_number != NULL; i--)
        {
            new_cursor = new_cursor->prev_number;
        }
    }
    cursor = new_cursor;
    return cursor;
}

void Print_Data_Of_The_Cursor()
{
    if (cursor == NULL)
    {
        printf("Invalid function call: Cursor is NULL\n");
    }
    else
    {
        printf("The number at current cursor position is: %d\n", cursor->number);
    }
}

void Undo()
{
    if (sp < 0)
    {
        printf("No operation to undo\n");
        return;
    }

    Operation *op = pop();
    int num1 = op->num1;
    int num2 = op->num2;
    if (strcmp(op->name, "Add_Number_At_The_End") == 0)
    {
        Delete_Tail();
    }
    else if (strcmp(op->name, "Add_Number_At_An_Index") == 0)
    {
        Delete_Specific_Index(num1);
    }
    else if (strcmp(op->name, "Delete_Tail") == 0)
    {
        Add_Number_At_The_End(num2);
    }
    else if (strcmp(op->name, "Delete_Specific_Index") == 0)
    {
        Add_Number_At_An_Index(num2, num1);
    }
    else if (strcmp(op->name, "Add_Immediate_Number") == 0)
    {
        Delete_Immediate_Number();
    }
    else if (strcmp(op->name, "Delete_Immediate_Number") == 0)
    {
        Add_Immediate_Number(num2);
    }
    else if (strcmp(op->name, "Update_Index_Number") == 0)
    {
        Update_Index_Number(num1, num2);
    }
    else if (strcmp(op->name, "Update_Immediate_Number") == 0)
    {
        Update_Immediate_Number(num2);
    }
    else
    {
        printf("Unknown operation\n");
    }

    free(op);
}

int main()
{
    char command[100];
    int num1, num2;
    FILE *input_file = fopen("myFile.txt", "r");
    while (fscanf(input_file, "%s", command) != EOF)
    {
        if (strcmp(command, "Add") == 0)
        {
            fscanf(input_file, "%d", &num1);
            fscanf(input_file, "%d", &num2);
            if (num2 > 1000)
            {
                Add_Number_At_The_End(num1);
            }
            else
            {
                Add_Number_At_An_Index(num2, num1);
            }
        }
        else if (strcmp(command, "Delete") == 0)
        {
            fscanf(input_file, "%d", &num1);
            if (num1 == 0)
            {
                Delete_Tail();
            }
            else
            {
                Delete_Specific_Index(num1);
            }
        }
        else if (strcmp(command, "Update") == 0)
        {
            fscanf(input_file, "%d", &num1);
            fscanf(input_file, "%d", &num2);
            if (num2 == -1)
            {
                Update_Immediate_Number(num1);
            }
            else
            {
                Update_Index_Number(num2, num1);
            }
        }
        else if (strcmp(command, "Print") == 0)
        {
            Print_Data_Of_The_Cursor();
        }
        else if (strcmp(command, "MoveForward") == 0)
        {
            fscanf(input_file, "%d", &num1);
            Move_Forward(num1);
        }
        else if (strcmp(command, "MoveBackward") == 0)
        {
            fscanf(input_file, "%d", &num1);
            Move_Backward(num1);
        }
        else if (strcmp(command, "AddImmediate") == 0)
        {
            fscanf(input_file, "%d", &num1);
            Add_Immediate_Number(num1);
        }
        else if (strcmp(command, "DeleteImmediate") == 0)
        {
            Delete_Immediate_Number();
        }
        else if (strcmp(command, "UpdateImmediate") == 0)
        {
            fscanf(input_file, "%d", &num1);
            Update_Immediate_Number(num1);
        }
        else if (strcmp(command, "Shift") == 0)
        {
            fscanf(input_file, "%d", &num1);
            Shift_Index(num1);
        }
        else if (strcmp(command, "Undo") == 0)
        {
            Undo();
        }
        else
        {
            printf("Invalid command: %s\n", command);
        }
    }
    //print_list_of_numbers();
    fclose(input_file);
    return 0;
}