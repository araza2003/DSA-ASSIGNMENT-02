# DSA-ASSIGNMENT-02
In the assignment we were assigned 5 coding problems. Here's a description to how I solved those.
**Question # 01: Retieving The Trump**
The task was to read the input from a .txt file, so for that i used the following functions: 
1. fscanf() to read a string one by one and assign it into an array.
2. strcmp() to compare the read string with the function name inorder to call that function.
File pointer was created to open and read the file by providing path.
To implement the functions I created a single linked list using typedef struct class.
In C there are no classes so struct class is used and typedef is a keyword that is used to provide existing data types with a new name.
Then simple linked list functions like;
1. ADD : to add a node at the end of the linked list.
2. DELETE : to delete at the end of the linked list.
were used and one more function named,
END : was used, when the file pointer reads END, the functions prompts the end of file and of the linked list is calculated.
In order to calculate median the list should be sorted, so for that I used merge sort.
If the count is even, the function traverses the list until it reaches the first middle element. It then stores the ID of this element in a variable called 'previousID'. The function then continues traversing the list until it reaches the second middle element and displays both the 'previousID' and the ID of the second middle element as the median IDs.
If the count is odd, the function simply traverses the list until it reaches the middle element and displays its ID as the median ID.
If the list has fewer than two elements, then the function displays a message that the median cannot be computed.

**Question # 02: Survival of the Fittest**
In this question, fscanf() and file pointer were used to read the imput from the .txt file.
Again simple linked list was created by typedef and struct and insert at end and delete at end functions was used.
Here median is calculated as;
For calculating median I declared a variable count globally which is incremented when a node is inserted and decremented when a node is deleted.
If the number of nodes in the linked list is odd, returns the middle number.
If the number of nodes in the linked list is even, returns the average of the two middle numbers.
Merge sort was used to sort the list.

**Question # 03: Reversing The Irreversible**
Here the input file had some transactions from which some fradulent transactions were to be deleted.
So for that, number of transaction and fradulent transactions and transaction ID and amount was read by the same fscanf() function but there was a comma separating transaction ID and amount which was read by fgetc().
When ever a transaction was read it was inserted into a linked list.
Linked list was created in the same way as above.
Transactions were read upto number of transaction times.
Then when fradulent transactions were read the transaction ID was provided by which that particular transaction was deleted from the linked list.

**Question # 04: The Editor**
This was a complex code for which I think my code is not 100% but I gave my level best.
Here we were asked to create a editor which supports muliple functions.
Double linked list was used.
The file reading was done by fscanf() and strcmp()
Mainting stack for undo function was tpyical as well. For which I took help from the internet.
I think some of my cursor operations were not being implemented for which I could not find errors in my code. 

**Question # 05: As The Matter of Third**
This problem can be implemented by double linked list as well but I chose single.
There was a running stream of numbers for which I had to calculate the third last value.
Same input functions were used as above. 
When the stream of numbers is less than three, the code prompts the user that the third last number can not be calculated.
**Question # 05: The Editor**
