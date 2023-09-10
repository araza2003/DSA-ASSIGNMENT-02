#include<stdio.h>
#include<stdlib.h>

struct KronstadtIndustries{
    int number;
    struct KronstadtIndustries *next_number;
};

struct KronstadtIndustries *Numbers_Head = NULL;
int count = 0;

void Add_number_to_linked_list_in_a_sorted_manner(int number){
    struct KronstadtIndustries *new_number;
    new_number = (struct KronstadtIndustries *)malloc(sizeof(struct KronstadtIndustries));
    if(Numbers_Head == NULL){
        new_number->number = number;
        new_number->next_number = NULL;
        Numbers_Head = new_number;
    }
    else{
        struct KronstadtIndustries *current_number = Numbers_Head;
        struct KronstadtIndustries *prec_to_curr_num = NULL;
        while(current_number != NULL && current_number->number < number){
            prec_to_curr_num = current_number;
            current_number = current_number->next_number;
        }
        new_number->number = number;
        if(prec_to_curr_num == NULL){
            new_number->next_number = Numbers_Head;
            Numbers_Head = new_number;
        }
        else{
            new_number->next_number = prec_to_curr_num->next_number;
            prec_to_curr_num->next_number = new_number;
        }
    }
    count++;
}

float get_median(){
    struct KronstadtIndustries *current_number = Numbers_Head;
    int mid = count/2;
    if(count%2 == 0){
        for(int i=1;i<mid;i++){
            current_number = current_number->next_number;
        }
        float median = (current_number->number + current_number->next_number->number)/2.0;
        return median;
    }
    else{
        for(int i=1;i<=mid;i++){
            current_number = current_number->next_number;
        }
        return current_number->number;
    }
}

int main(){
    FILE *fp = fopen("myFile.txt","r");
    if(fp == NULL){
        printf("Error: Unable to open file\n");
        exit(0);
    }
    int number;
    while(fscanf(fp,"%d",&number) != EOF){
        Add_number_to_linked_list_in_a_sorted_manner(number);
        float median = get_median();
        printf("%d Median : %.1f\n",number,median);
    }
    fclose(fp);
    return 0;
}