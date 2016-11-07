// lab8.cpp : Defines the entry point for the console application.
//
/*
Name:Daniel Webber Daniel Toree
Date: 11-8-2016 (the day you have lab)
Title: Lab 8
File: Lab8
Description:
This program is designed to be a system to reserve hotel rooms with complex functionality.
*/

 #include "stdafx.h"
#include <stdio.h>// Needed for printf_s()
#include <stdlib.h>// Needed for system()
#include <string.h> //needed to deal with strings

#define SIZE 10 //10 rooms for the system
#define STRINGSIZE 15
//function protoype
int userPrompt(char *command);

void roomReservation(int reservationArray[SIZE], char reservationName[SIZE][STRINGSIZE], int *id,  int waitlistArray[SIZE], char waitlistName[SIZE][STRINGSIZE],int *resID);

void listReservations(int reservationArray[SIZE], char reservationName[SIZE][STRINGSIZE], int waitlistArray[SIZE], char waitlistName[SIZE][STRINGSIZE]);

void roomCancelation(int reservationArray[SIZE], char reservationName[SIZE][STRINGSIZE], int *id, int waitlistArray[SIZE], char waitlistName[SIZE][STRINGSIZE], int *resID);

void waitCancelation(int *id, int waitlistArray[SIZE], char waitlistName[SIZE][STRINGSIZE], int *resID);
//reservation array and reservation name array associated with it

int main()
{
	int keepGoing = 0;
	int reservationId = 1;//creating and setting reservation id to 1 a reservation ID of 0 means it is empty
	int roomsReserved = 0;
	int waitListID = 1; //keep track of how many waitlist people there are 
	int rA[SIZE], waitA[SIZE]; //reservation id array 
	char rName[SIZE][STRINGSIZE], waitName[SIZE][STRINGSIZE]; //reservation name array  10 rows with 14 char max string bc we need one for \0
	char null[] = "Null"; 

	for (int i = 0; i<SIZE; i++) { //we have to set all the ID's to 0 so we can check if it is empty
		rA[i] = 0;
		waitA[i] = 0;
		strcpy_s(rName[i], null); //fill all name strings to null
		strcpy_s(waitName[i], null); //fill all name strings to null
	}

	//run the prompt loop forever
	do {
		int keepGoing = 0;
		char cmd = 'n';
		keepGoing = userPrompt(&cmd);
		int breakLoop = 0;
		//switch statment to drive all the functions
		switch (cmd) {
		case 'r':
			roomReservation(rA, rName, &reservationId, waitA, waitName,&waitListID); //run room reservations pass in room r ID array and associated name array 				
			break;
		case 'c':
			roomCancelation(rA, rName, &reservationId, waitA, waitName, &waitListID);
			break;
		case 'w':
			waitCancelation(&reservationId, waitA, waitName, &waitListID);
			break;
		case 'l':
			listReservations(rA, rName, waitA, waitName);			
			break;
		case 'q': //quit 
			breakLoop = 1; //breakloop
			break;			
		}
		if (breakLoop == 1) // if q is hit break out of do while loop 
			break;

	} while (keepGoing == 0);

	//system("pause");
	return 0;
}
/*function to prompt user to run a specfic function and pass it out as a ptr but we return
an int to tell the main if we get garbage so we can re run the loop.
*/
int userPrompt(char *command) {
	*command = 'n';
	char userInput='n';	
	printf_s("Hello welcome to the hotel reservations system!\n");
	printf_s("Enter R or r to reserve a room\n");
	printf_s("Enter C or c to cancel a reservation\n");
	printf_s("Enter W or w: to remove a request from the waiting list\n");
	printf_s("Enter L or l: to list the current reservations for the night\n");
	printf_s("Enter Q or q: to quit the program\n");
	printf_s("\n");
	scanf_s(" %c", &userInput);
	//swtich statement to pt to what cmd we want to do 
	switch (userInput) {
	case 'R':
	case 'r':
		*command = 'r';
		return(0);
		break;
	case 'C':
	case 'c':
		*command = 'c';
		return(0);
		break;
	case 'W':
	case 'w':
		*command = 'w';
		return(0);
		break;
	case 'l':
	case 'L':
		*command = 'l';
		return(0);
		break;
	case 'q':
	case 'Q':
		*command = 'q';
		system("pause");
		return(0);
		break;
	default:
		return(1);
		// if we get anything else we return 1 
	}

}
//function to deal with room reservations. Probably will call another function if rooms are full 
void roomReservation(int reservationArray[SIZE], char reservationName[SIZE][STRINGSIZE], int *id, int waitlistArray[SIZE], char waitlistName[SIZE][STRINGSIZE], int *resID) {
	int freeRoom, roomAvail = 0;	
	char nameString[STRINGSIZE];
	//checking for the first empty room freeRoom keeps track of what room is empty 
	for (int i = 0; i<SIZE; i++) {
		if (reservationArray[i] == 0) {

			freeRoom = i;
			roomAvail = 1;
			break;
		}
		else {
			roomAvail = 0;
			// go to wating list
		}
	}
	if (roomAvail == 1) {

		printf_s("Enter Your name\n");
		scanf_s("%s", nameString,STRINGSIZE);
		printf_s("Your room is: %d and your ID is: %d\n", freeRoom, *id);
		printf_s("\n");
		reservationArray[freeRoom] = *id;
		strcpy_s(reservationName[freeRoom], nameString);

		*id += 1; //increment id number so someone else cant have it
		roomAvail = 0;
	}
	else { // this is is the part when no rooms are left and we need to put people on the waiting list
		char waitList;
		char nameString[STRINGSIZE];
		printf_s("Sorry there are no More rooms avail\n");
		printf_s("Do you want to be placed on the wait list. Enter Y for yes and N for no\n");
		scanf_s(" %c", &waitList);
		if (waitList == 'y'||waitList=='Y') 
		{
			printf_s("Enter Your name\n");
			scanf_s("%s", nameString, STRINGSIZE);
			printf_s("Your ID is: %d\n", *id);			
			waitlistArray[(*resID)-1] = *id;
			strcpy_s(waitlistName[(*resID)-1], nameString);
			*id += 1;  //increment id number so someone else cant have it
			*resID += 1;
		}		
	}
}
void listReservations(int reservationArray[SIZE], char reservationName[SIZE][STRINGSIZE], int waitlistArray[SIZE], char waitlistName[SIZE][STRINGSIZE]) {
	printf_s("Rooms Reserved:\t\t\t\tWait List:\n");
	printf_s("%-20s%-20s%-21s%s","Reservation ID","Name","Reservation ID", "Name" );
	printf_s("\n");
	char null[] = "Null";
	/* http://stackoverflow.com/questions/1330550/c-compare-char-array-with-string
	this is how i figured out how to compare strings directly
	*/
	for (int i = 0; i<SIZE; i++) {
		if(reservationArray[i]!=0)
			printf_s("%-20d", reservationArray[i]);
		if(strcmp(reservationName[i],null)!=0)
			printf_s("%-24s", reservationName[i]);
		if(waitlistArray[i]!=0)
			printf_s("%-17d", waitlistArray[i]);
		if(strcmp(waitlistName[i], null) !=0)
			printf_s("%s", waitlistName[i]);
		printf_s("\n");
	}
}

void roomCancelation(int reservationArray[SIZE], char reservationName[SIZE][STRINGSIZE], int * id, int waitlistArray[SIZE], char waitlistName[SIZE][STRINGSIZE], int *resID)
{
	int notfound = 0;
	int reservationID;
	printf("Enter you reservation ID to cancel :\n");
	scanf_s(" %d", &reservationID);
	for (int i = 0; i < SIZE; i++) {
		if (reservationID == reservationArray[i]) {
			notfound = 0;
			if (waitlistArray[0] != 0) {
				reservationArray[i] = waitlistArray[0]; //set id of person on waitlist to the room just canceled
				strcpy_s(reservationName[i], waitlistName[0]); //copy the name of the person on the waitlist to reservation list
				printf_s("The id is: %d is now off the waitlist and is in room: %d\n", reservationArray[i], (i+1));

				for (int j = 1; j < SIZE; j++) {
					waitlistArray[j - 1] = waitlistArray[j];
					strcpy_s(waitlistName[j - 1], waitlistName[j]);
					waitlistArray[j] = 0;
					strcpy_s(waitlistName[j], "Null");
					
				}
				*resID = (*resID) - 1;//decrement the slot of where the next waitlist entry will be bc if we dont we will not put it in the right place

				break;

				// a way to exit this loop 
			}
			else {
				reservationArray[i] = 0; //if no one one is on the waiting list remove them
				strcpy_s(reservationName[i], "Null");
				//breakloop = 1; //a way to exit the outer loop
				break; // a way to break out of this lop 

			}
		}
		else
			notfound = 1;
	}
	if (notfound == 1)
		printf_s("ID NOT FOUND!\n");		
}

void waitCancelation(int * id, int waitlistArray[SIZE], char waitlistName[SIZE][STRINGSIZE], int * resID)
{


	int notfound = 0;
	int reservationID;
	printf("Enter you reservation ID to cancel :\n");
	scanf_s("%d", &reservationID);
	for (int i = 0; i < SIZE; i++) {
		if (reservationID == waitlistArray[i]) {
			notfound = 0;
			for ( int j = i; j < (SIZE-1); j++) {
				waitlistArray[j] = waitlistArray[j+1];
				strcpy_s(waitlistName[j], waitlistName[j+1]);
				waitlistArray[j+1] = 0;
				strcpy_s(waitlistName[j+1], "Null");

			}
			*resID = (*resID) - 1;
			break;
		}
		else
			notfound = 1;
	}	
	if (notfound == 1)
		printf_s("ID NOT FOUND!\n");

}












