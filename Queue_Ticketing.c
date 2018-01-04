//PROGRAM TITLE: 'Queue_Ticketing.c'
//LAST MODIFIED: 22/04/2017
//AUTHOR: Stephen Alger ©

//VERSION IDENTIFIER: 1.1
//
//MODULE: PROGRAMMING WITH WITH PERSISTENT DATA
//PROGRAM DESIGN CORRESPONDS TO THE SPECIFICATION OF REQUIREMENTS DOCUMENTED: GrpTasksOddTeams.pdf
//PROGRAMMING LANGUAGE: C
//LICENSE: ALL RIGHTS RESERVED STEPHEN ALGER © 2017

//REFERENCES FOR CODE DESIGN
//1. 'A Guide To C Programming' - © Paul Kelly 2007
//2. Linked List Resource Information - cprogramming.com
//3. Bug Fixing & Diagnostic - Stackoverflow Forums - stackoverflow.com
//4. Bug Fixing & Diagnostics - Tutorialspoint - tutorialspoint.com

/*Program Information:
This Program Implements a Linked List System to Function as a queuing system for an IT Client - Issue Resolution centre.
 The Program handles up to 5 support tickets at once and is designed so that the user can add more tickets ontop of the pre-initialised tickets. 
 This program uses three functions, Dynamic memory allocation, customised structures, structure variables & structure variable pointers.
 */

//Include Libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#defines - SYMBOLIC NAMING SCHEMES
#define PIN_SIZE 4
#define ARRAY_SIZE 3
#define STD_FIELD_LEN 81
#define UNIQUE_ID 1234
#define MAX_TICKETS 5
#define MODE_ADD '1'
#define MODE_DELETE '2'
#define MODE_QUIT '3'

//Structure Template
struct IT_Services_Ticketing_Node
{

	char Name_Of_Client[STD_FIELD_LEN];
	char Description_Of_Issue[STD_FIELD_LEN];
	int Contact_Number;
	float Time_Of_Call;
	struct IT_Services_Ticketing_Node *Next_Node;
	
};

typedef struct IT_Services_Ticketing_Node IT_Services_Ticketing_Node;

//Function prototype
void Display(IT_Services_Ticketing_Node* Conductor, int Node_Counter);
void  New_Ticket(IT_Services_Ticketing_Node* Next);
void Remove_Ticket(IT_Services_Ticketing_Node* Head);


int main()
{
	
	//Root Node Declaration
	IT_Services_Ticketing_Node Head;
	
	//Next Node Pointer
	IT_Services_Ticketing_Node *Next;
	
	//Sequential Node Pointer
	IT_Services_Ticketing_Node *Conductor;
	
	//Node Counter & Variable declarations
	int Node_Counter=0;
    
    //Loop maintaining int variable declaration
    int Loop=0;
	
	//UNIQUE ID Pin (Actual & User Guess Arrays)
	int ID = UNIQUE_ID;
	int Guess_ID=0;
    
    //MODE SELECTOR
    char Mode = '0';
	
	//Used to Remove Unwanted Characters from buffer
	char Unwanted_Chars;
	
	//assign pointer address of the Head node
	Conductor = &Head;
	
	//provide basic user feedback
	printf("\nHello this is your IT services ticketing system - Unique Identifier is the number \"1234\"\nEnter It Below...\n");
	
	//Implement basic neccessary Unique ID pin code access, self-explanatory.
	while (Guess_ID != ID)
	{
		scanf("%d", &Guess_ID);
		
		if (Guess_ID != ID)
			printf("\nEnter The Correct ID - 1234!\n");
		
		else
			printf("\nWelcome Back");
		
	} //end while
	
	//Clear the input buffer of any unwanted data
	while ((Unwanted_Chars = getchar()) != '\n' && Unwanted_Chars != EOF );
	
	//Allocate 3 Initialised Tickets
	strcpy(Head.Name_Of_Client, "Jane");
	Head.Contact_Number = 4558;
	strcpy(Head.Description_Of_Issue, "Monitor broken");
	Head.Time_Of_Call = 12.05;
	
	//Assign Next Node address to Head struct variable
	Head.Next_Node = malloc(sizeof(IT_Services_Ticketing_Node));
	Next = Head.Next_Node;
	
	//Increment node counter
	Node_Counter++;
	
	//repeat with next node
	strcpy(Next->Name_Of_Client, "Sean");
	Next->Contact_Number = 5656;
	strcpy(Next->Description_Of_Issue, "Desktop won’t stop flickering");
	Next->Time_Of_Call = 12.06;
	
	//Assign Next Node address to previous struct variable
	Next->Next_Node = malloc(sizeof(IT_Services_Ticketing_Node));
	Next = Next->Next_Node;
	
	//Increment node counter
	Node_Counter++;
	
	//repeat with next node
	strcpy(Next->Name_Of_Client, "Mark");
	Next->Contact_Number = 1212;
	strcpy(Next->Description_Of_Issue, "Router lights amber");
	Next->Time_Of_Call = 12.10;
	Next->Next_Node = NULL;
	
	//Increment node counter
	Node_Counter++;
	
	//provide basic feedback
	printf("\nThere are 3 Queued Tickets Already:\n");
	
	//Display Ticket Queue
	Display(Conductor, Node_Counter);
	
    //Run loop
	while (Loop != MODE_QUIT)
	{
        //Reset Mode handler
        Mode = '0';
        
        //Output the menu
		printf("\nWould You Like To Add Or Delete Tickets,\nEnter 1 To Add Tickets To Queue\nEnter 2 To Delete Tickets From Queue\nEnter 3 To Quit This Program\n");
		
        //Input User's Selection
		scanf("%c", &Mode);
		
		//Clear the input buffer of any unwanted data
        while ((Unwanted_Chars = getchar()) != '\n' && Unwanted_Chars != EOF ){
        }
        
        system("clear"); /*Triggers compiler warning with MacOS Terminal Compiler due to it being invalid with C99 Standards - however it carries out the desired function*/
		
        //Carry out the User's Command
		switch (Mode)
		{

            //User wants to add tickets
			case MODE_ADD:
			{
				//Provide basic feedback
				printf("\nYou Wish To Create A New Ticket...\n");
				
				//Check if there is space
				if (Node_Counter < MAX_TICKETS)
				{
                    //If Node counter is equal to 1 we are in the base case, As we always need a Head Node to control this queue, this means even if its contents are deleted and we have an 'empty queue' it still exists in memory. So if Node_Counter = 1 then we just refill the head struct variable instead of performing a memory allocation.
                    if (Node_Counter != 0)
                    {
                        //Assign Next Node address to previous struct variable
                        Next->Next_Node = malloc(sizeof(IT_Services_Ticketing_Node));
                        Next = Next->Next_Node;
                    }//end if
                    
                    else
                    {
                        //Assign Next (struct pointer) the address of the Head (Node) Struct Variable
                        Next = &Head;
                    }//end else
					
					//call the dedicated new_ticket function.
					New_Ticket(Next);
					printf("\nSuccessfully Added A New Ticket...");
                    
                    //Increment Node Counter
                    Node_Counter++;

                    //re-initialise the conducting pointer variable back to the head node & call the display fucntion.
					Conductor = &Head;
					Display(Conductor, Node_Counter);
					
				} //end if
                
                //Otherwise there is no space for more tickets right now.
                else
                {
                    printf("\n***There Is Too Many Tickets Left Opened To Open Another!***\n");
                }//end else
			
				break;
			} //end case
			
            //User wishes to Delete a Ticket
			case MODE_DELETE:
			{
				//Provide basic user feedback
				printf("\nYou Wish To Close The A Ticket...\n");
				
				//If there are nodes present...
				if (Node_Counter>1)
				{
					
					//Call the Remove_Ticket funtion passing the old Head Node address
					Remove_Ticket(&Head);
					
					//Decrement number of Nodes
					Node_Counter--;
                    
                    //More Feedback
                    printf("\nYou Have Successfully Closed A Ticket...\n");
                    
                    //re-initialise the conducting pointer variable back to the head node & call the display fucntion.
                    Conductor = &Head;
                    Display(Conductor, Node_Counter);
						
				} //end if
                
                //Maintain Head variable at all times...
                else if (Node_Counter == 1)
                {
                    //Reset the Head Struct Variable - to act as deleting node
                    strcpy(Head.Name_Of_Client, "0");
                    strcpy(Head.Description_Of_Issue, "0");
                    Head.Contact_Number=0;
                    Head.Next_Node = NULL;
                    Head.Time_Of_Call = -1;
                    
                    //Decrement number of Nodes
                    Node_Counter--;
                    
                    //More Feedback
                    printf("\nYou Have Successfully Closed The Last Ticket...\n");
                    
                }//end else
                
                //Otherwise there are no nodes to delete
                else
                {
                    printf("\n***There Are No Tickets To Close***\n");
                } //end else
                
                break;
				
			} //end case
			
			//User wishes to terminate program.
			case MODE_QUIT:
			{
				printf("\nGoodbye, Come Back Soon!\n");
                
                //End the loop...
				Loop= MODE_QUIT;
                break;
			} //end case
			
            //Perhaps - input error
			default:
			{
				printf("\n***Invalid Entry - Program Terminating, Goodbye!***\n");
				return 0;
			}//end default
		}// end switch
    
	}//end while
	
} //end main()


//Simple Function which Displays Active Tickets, pass in the Contents of the Conductor Pointer (i.e. Address held in Conductor Pointer).
void Display(IT_Services_Ticketing_Node* Conductor, int Node_Counter)
{
    //Basic index counter
    int Index=0;
    
	//Equates to - 'While there is another ticket to print...'
	while (Conductor != NULL)
	{
        if (Conductor->Time_Of_Call != -1 && Node_Counter > 0)
        {
            //Increment counter
            Index++;
            
            //Provide user-output
            printf("\nThere Are Now %d Active Tickets", Node_Counter);
            printf("\n----------------------------------\n");
            printf("%d.[%s]		[%d]		[%s]		[%.2f]\n", Index,Conductor->Name_Of_Client, Conductor->Contact_Number, Conductor->Description_Of_Issue, Conductor->Time_Of_Call);
            printf("\n----------------------------------\n");
            
            //Move the conducting pointer variable onto the next Node
            Conductor = Conductor->Next_Node;
        }//end if
        
        else
        {
            printf("\n----------------------------------\n");
            printf("\nThere Are No Tickets To Print\n");
            printf("\n----------------------------------\n");
            
            //terminate loop
            Conductor = NULL;
        }
		
	} //end while
	
	
} //end function


//Simple New Ticket Recording Function, pass in the Contents of the Next Node Pointer (i.e. Address held in 'Next' Pointer).
void New_Ticket(IT_Services_Ticketing_Node* Next)
{
	//Used for clearing buffer.
	char Unwanted_Chars;
	
	//Take in Client's details...
	
	printf("\nAdd A Ticket Client Name:\n");
	//Utilising fgets to format input to set length whilst also allowing whitespace data to be read in.
	fgets(Next->Name_Of_Client,STD_FIELD_LEN-1, stdin);
	
	//Now we must remove the newline character which may be stored as a result of the above fgets() function.
	//If statement checks that the length of string is greater than 0 and the last character is actually the newline specifier which we wish to remove, if so then we put the null terminator in manually.
	if ((strlen(Next->Name_Of_Client)>0) && (Next->Name_Of_Client[strlen (Next->Name_Of_Client) - 1] == '\n'))
	{
		Next->Name_Of_Client[strlen (Next->Name_Of_Client) - 1] = '\0';
		
	}//end if
	
	printf("\nAdd A Contact Number:\n");
	scanf("%d", &Next->Contact_Number);
	
	//Clear the input buffer of any unwanted data
	while ((Unwanted_Chars = getchar()) != '\n' && Unwanted_Chars != EOF );
	
	printf("\nAdd An Issue Description:\n");
	fgets(Next->Description_Of_Issue,STD_FIELD_LEN-1, stdin);
	
	if ((strlen(Next->Description_Of_Issue)>0) && (Next->Description_Of_Issue[strlen (Next->Description_Of_Issue) - 1] == '\n'))
	{
		Next->Description_Of_Issue[strlen (Next->Description_Of_Issue) - 1] = '\0';
		
	}//end if
	
	printf("\nAdd Time of Client Call:\n");
	scanf("%f", &Next->Time_Of_Call);
	
	//Clear the input buffer of any unwanted data
	while ((Unwanted_Chars = getchar()) != '\n' && Unwanted_Chars != EOF );
	
	//Place the NULL value in the Next Node Member of the struct variable. i.e. this is now the last node.
	Next->Next_Node = NULL;

}//end function


void Remove_Ticket(IT_Services_Ticketing_Node* Head)
{
	//Backup Next node address
	IT_Services_Ticketing_Node* Next = Head->Next_Node;
	
	//Copy Contents of next node and overwrite Head
	strcpy(Head->Name_Of_Client, Next->Name_Of_Client);
	strcpy(Head->Description_Of_Issue,  Next->Description_Of_Issue);
	Head->Contact_Number = Next->Contact_Number;
	Head->Time_Of_Call = Next->Time_Of_Call;
	Head->Next_Node = Next->Next_Node;

} //end function
