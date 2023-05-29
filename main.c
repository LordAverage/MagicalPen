// main.c

#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "string.dat"

//---------------------------------------------------------------------------------------
//                                       Magical Pen
//                                      -------------
//
// General : The program simulates a typewriter. The program allows a user to manipulate
//			 a string of text by appending, changing, deleting, printing, saving to a
//			 file, or reading from a file. The program uses malloc, realloc, and free to
//			 dynamically adjust the size of the string as the user adds or removes
//			 characters from it. 
//
// Input   : Commands and parameters.
// 
// Process : The program reads input from the user and performs the corresponding 
//			 actions based on the user's input using a switch statement.
//
// Output  : The program can print the string or save it to a file.
// 
//---------------------------------------------------------------------------------------
// Programmer : Lahav Gafni
// Student No : 325761880
// Date       : 10.12.2022
//---------------------------------------------------------------------------------------
int main()
{
	// Variable definition
	FILE* pfsFilePointer;
	char* pcString;
	int nStringLength;
	int nStringToAppendLength;
	int nOptionNumber;
	int nElementsRead;
	int nStartingIndex;
	int nCharactersToDelete;

	// Code section
	
	// Initialize important variables
	pcString = malloc(0);
	nStringLength = 0;
	// Main loop
	do 
	{
		printf("Enter 1 to append text, 2 to change text, 3 to delete text, 4 to ");
		printf("print, 5 to save to file, 6 to read from file, ");
		printf("or 7 to exit the program.\n");
		scanf("%d", &nOptionNumber);
		// Execute command
		switch (nOptionNumber)
		{
		case 1:
			printf("Enter the length of the text to append.\n");
			scanf("%d", &nStringToAppendLength);
			nStringLength += nStringToAppendLength;
			pcString = (char*)realloc(pcString, sizeof(char) * (nStringLength + 1));
			if (!pcString)
			{
				printf("Error allocating memory\n");
				exit(1);
			}
			// Read the '\n' from the buffer
			getchar();
			printf("Enter text to append.\n");
		Case1:
			// Transfer data to string
			for (; 0 < nStringToAppendLength; nStringToAppendLength--)
			{
				nElementsRead =
					scanf("%c", &pcString[nStringLength - nStringToAppendLength]);
				if (nElementsRead != 1)
				{
					printf("Error scanning input\n");
					exit(2);
				}
			}
			// Insert null terminator
			pcString[nStringLength] = '\0';

			break;
		case 2:
			printf("Enter the starting index for the text.\n");
			scanf("%d", &nStartingIndex);
			printf("Enter the length of the text to insert.\n");
			scanf("%d", &nStringToAppendLength);
			getchar();
			printf("Enter the text to insert.\n");
			// Change characters in string in requested index
			for (nStartingIndex--;
				0 < nStringToAppendLength && nStartingIndex < nStringLength;
				nStartingIndex++, nStringToAppendLength--)
			{
				nElementsRead = scanf("%c", &pcString[nStartingIndex]);
				if (nElementsRead != 1)
				{
					printf("Error scanning input\n");
					exit(2);
				}
			}
			// If the end of the string is reached, send rest of data to case 1 to use
			// reallocation of dynamic memory to resize the string
			if (nStringToAppendLength)
			{
				nStringLength += nStringToAppendLength;
				pcString = (char*)realloc(pcString, sizeof(char) * (nStringLength + 1));
				if (!pcString)
				{
					printf("Error allocating memory\n");
					exit(1);
				}
				goto Case1;
			}
			break;
		case 3:
			printf("Enter number of characters to delete.\n");
			nElementsRead = scanf("%d", &nCharactersToDelete);
			if (nElementsRead != 1)
			{
				printf("Error scanning input\n");
				exit(2);
			}
			// Subtract from string length
			nStringLength -= nCharactersToDelete;
			// Set the minimum length to 0 characters
			nStringLength = (0 < nStringLength) * nStringLength;
			// Resize string
			pcString = (char*)realloc(pcString, sizeof(char) * (nStringLength + 1));
			if (!pcString)
			{
				printf("Error allocating memory\n");
				exit(1);
			}
			// Insert null terminator
			pcString[nStringLength] = '\0';

			break;
		case 4:
			printf("%s\n", pcString);

			break;
		case 5:
			pfsFilePointer = fopen(FILE_NAME, "wb");
			if (!pfsFilePointer)
			{
				printf("Error opening file\n");
				exit(3);
			}
			// Save data to file
			nElementsRead = fwrite(pcString, sizeof(char), nStringLength,
				pfsFilePointer);
			if (nElementsRead != nStringLength)
			{
				printf("Error writing to file\n");
				exit(4);
			}
			fclose(pfsFilePointer);
			printf("Successfully saved to file.\n");

			break;
		case 6:
			pfsFilePointer = fopen(FILE_NAME, "rb");
			if (!pfsFilePointer)
			{
				printf("Error opening file\n");
				exit(3);
			}
			// Move cursor to EOF
			fseek(pfsFilePointer, 0, SEEK_END);
			// Get the size of the string
			nStringLength = ftell(pfsFilePointer);
			// Use size to reallocate memory for the string
			pcString = (char*)realloc(pcString, (nStringLength + 1) * sizeof(char));
			if (!pcString)
			{
				printf("Error allocating memory\n");
				exit(1);
			}
			// Return cursor back to start
			fseek(pfsFilePointer, 0, SEEK_SET);
			// Retrieve data from file
			nElementsRead = fread(pcString, sizeof(char), nStringLength,
				pfsFilePointer);
			// Insert null terminator
			pcString[nStringLength] = 0;
			if (nElementsRead != nStringLength)
			{
				printf("Error reading from file\n");
				exit(4);
			}
			fclose(pfsFilePointer);
			printf("Successfully saved from file.\n");
		default:
			break;
		}
	} while (nOptionNumber != 7);
	free(pcString);
	return (0);
}