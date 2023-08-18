#include <iostream>
using namespace std;

//----------------------------------------------------------------------------------Start of Q1--------------------------------------------------------------------------------------------
char* removeSentence(char* Para, char* input)
{
	//Declaring and Initializing Variables
	int remove = 0, counter = 0, size = 0, Parasize = 0, place = 0, check, test, number, copy = 0;
	while (*(input + size) != '\0')
	{
		size++; //Calculating the size of the input array
	}
	while (*(input + remove) != '\0')
	{
		check = 0;
		test = 0;
		while (*(Para + check) != '\0')
		{
			if (*(Para + check) == *(input + test) && counter != 0) //Checking if consecutive letters match
			{
				counter++;
				test++;
			}
			else
			{
				counter = 0;
				if (*(Para + check) == *(input+ test)) //Checking if the first letter matches
				{
					counter++;
					test++;
				}
				else
				{
					test = 0; //Resetting if letters don't match
				}
			}
			if (counter == size)
			{
				place = check - test; //Calculating the address of the point where the word starts matching
				number = counter; //Storing the number of matching words
			}
			check++;
		}
		remove++;
	}
	number++;
	while (*(Para + Parasize) != '\0')
	{
		Parasize++; //Calculating the size of the Para array
	}
	char* temp = new char[Parasize - number + 1]; //Making a temporary array whose size is the same as the Para array minus the input array
	for (int copy2 = 0; copy2 < Parasize + 1; copy2++)
	{
		if (copy2 == place)
		{
			copy2 += number; //Skipping the input array if match is found
		}
		*(temp + copy) = *(Para + copy2); //Copying the para array into the temp
		copy++;
	}
	Para = temp; //Making the Para point to the same memory as temp
	return Para;
}

bool FindSubString(char* Str, char* substr, int& start, int& end)
{
	//Declaring and Initializing Variables
	int counter = 0, size = 0, size2 = 0, loopnum = 0, check = 0;
	bool match = false, startcheck = false;
	while (*(substr + size) != '\0')
	{
		size++; //Calculating the size of the substring
	}
	while (*(Str + size2) != '\0')
	{
		size2++; //Calculating the size of the String
	}
	for (int compare = 0; *(Str + compare) != '\0'; compare++)
	{
		if (*(substr + check) == *(Str + compare))
		{
			counter++; //Counting matching characters
			check++;
			if (startcheck == false)
			{
				start = compare; //Finding starting location
				startcheck = true;
			}
			if (counter == size)
			{
				match = true; //Match is found
				end = compare; //Finding ending location
				break;
			}
			else if (compare == size2 - 1)
			{
				loopnum++; //Counting the number of loops
				compare = -1; //Resetting the loop
				if (loopnum > 50)
				{
					break; //Breaking if loop keeps going infinitely
				}
			}
		}
		else
		{
			counter = 0; //Resetting the count
			check = 0;
			startcheck = false;
		}
	}
	if (match == false)
	{
		start = end = -1; //Making the start and end -1 if match isn't found
	}
	return match;
}

//----------------------------------------------------------------------------------Start of Q2--------------------------------------------------------------------------------------------
char*** ConvertToDynamic(char arr[], int x, int y, int z) //Converts 1D Array to 3D dynamically allocated array
{
	//Declaring Variables
	int count = 0;
	char ***Three = new char**[x]; //Dynamically allocating x spaces into the triple pointer
	for (int X = 0; X < x; X++)
	{
		*(Three + X) = new char*[y]; //Dynamically allocating y spaces into the double pointer
		for (int Y = 0; Y < y; Y++)
		{
			*(*(Three + X) + Y) = new char[z]; //Dynamically allocating z spaces into the single pointer
		}
	}
	for (int X = 0; X < x; X++)
	{
		for (int Y = 0; Y < y; Y++)
		{
			for (int Z = 0; Z < z; Z++)
			{
				if (Z == z - 1)
				{
					*(*(*(Three + X) + Y) + Z) = '\0'; //Making the last column of each row a null character
					break;
				}
				*(*(*(Three + X) + Y) + Z) = arr[count]; //Putting the values of the character array into the 3D pointer
				count++;
			}
		}
	}
	return Three;
}

bool MatchString3DArray(char*** mat, int xSize, int ySize, int zSize, char * input, int**& resultMat, int& colSize)
{
	//Declaring variables
	int count = 0;
	colSize = 0;
	bool match = false, letter = false, found = false;
	for (int size = 0; *(input + size) != '\0'; size++)
	{
		colSize++; //Calculating the colSize
	}
	resultMat = new int*[3]; //Dynamically allocating the pointer to a new memory
	for (int resultsize = 0; resultsize < 3; resultsize++)
	{
		*(resultMat + resultsize) = new int[colSize];
	}
	while (count < xSize * ySize * zSize)
	{
		for (int X = 0; X < xSize; X++)
		{
			for (int Y = 0; Y < ySize; Y++)
			{
				for (int Z = 0; Z < zSize; Z++)
				{
					if (*input == *(*(*(mat + X) + Y) + Z))
					{
						*(*(resultMat)) = X; //Storing the x, y and z co-ordinates of the letter
						*(*(resultMat + 1)) = Y;
						*(*(resultMat + 2)) = Z;
						letter = true;
						*(*(*(mat + X) + Y) + Z) = ' '; //Replacing the letter with a space so it doesn't get found again
						break;
					}
				}
				if (letter == true)
				{
					break;
				}
			}
			if (letter == true)
			{
				break;
			}
		}
		if (letter == true)
		{
			for (int words = 1; words < colSize; words++)
			{
				if (*(*(resultMat + 2)) < zSize)
				{
					if (*(input + words) == *(*(*(mat + *(*(resultMat))) + *(*(resultMat + 1))) + *(*(resultMat + 2)) + words)) //Checking if the word matches horizontally
					{
						*(*(resultMat) + words) = *(*(resultMat)); //Storing the x, y and z co-ordinates of the next letter
						*(*(resultMat + 1) + words) = *(*(resultMat + 1));
						*(*(resultMat + 2) + words) = *(*(resultMat + 2)) + words;
						match = true;
					}
					else if ((*(*(resultMat + 1)) + words) < ySize)
					{
						if (*(input + words) == *(*(*(mat + *(*(resultMat))) + *(*(resultMat + 1)) + words) + *(*(resultMat + 2)) + words)) //Checking if the word matches diagonally
						{
							*(*(resultMat) + words) = *(*(resultMat)); //Storing the x, y and z co-ordinates of the next letter
							*(*(resultMat + 1) + words) = *(*(resultMat + 1)) + words;
							*(*(resultMat + 2) + words) = *(*(resultMat + 2)) + words;
							match = true;
						}
					}
					else if ((*(*(resultMat + 1)) - words) >= 0)
					{
						if (*(input + words) == *(*(*(mat + *(*(resultMat))) + *(*(resultMat + 1)) - words) + *(*(resultMat + 2)) + words)) //Checking if the word matches diagonally
						{
							*(*(resultMat) + words) = *(*(resultMat)); //Storing the x, y and z co-ordinates of the next letter
							*(*(resultMat + 1) + words) = *(*(resultMat + 1)) - words;
							*(*(resultMat + 2) + words) = *(*(resultMat + 2)) + words;
							match = true;
						}
					}
					else if ((*(*(resultMat)) + words) < xSize)
					{
						if (*(input + words) == *(*(*(mat + *(*(resultMat)) + words) + *(*(resultMat + 1))) + *(*(resultMat + 2))) + words) //Checking if the word matches diagonally
						{
							*(*(resultMat) + words) = *(*(resultMat)) + words; //Storing the x, y and z co-ordinates of the next letter
							*(*(resultMat + 1) + words) = *(*(resultMat + 1));
							*(*(resultMat + 2) + words) = *(*(resultMat + 2)) + words;
							match = true;
						}
					}
					else if ((*(*(resultMat)) - words) >= 0)
					{
						if (*(input + words) == *(*(*(mat + *(*(resultMat)) - words) + *(*(resultMat + 1))) + *(*(resultMat + 2))) + words) //Checking if the word matches diagonally
						{
							*(*(resultMat) + words) = *(*(resultMat)) - words; //Storing the x, y and z co-ordinates of the next letter
							*(*(resultMat + 1) + words) = *(*(resultMat + 1));
							*(*(resultMat + 2) + words) = *(*(resultMat + 2)) + words;
							match = true;
						}
					}
				}
				if (*(*(resultMat + 2)) >= 0)
				{
					if (*(input + words) == *(*(*(mat + *(*(resultMat))) + *(*(resultMat + 1))) + *(*(resultMat + 2)) - words)) //Checking if the word matches horizontally in reverse
					{
						*(*(resultMat) + words) = *(*(resultMat)); //Storing the x, y and z co-ordinates of the next letter
						*(*(resultMat + 1) + words) = *(*(resultMat + 1));
						*(*(resultMat + 2) + words) = *(*(resultMat + 2)) - words;
						match = true;
					}
					else if ((*(*(resultMat + 1)) + words) < ySize)
					{
						if (*(input + words) == *(*(*(mat + *(*(resultMat))) + *(*(resultMat + 1)) + words) + *(*(resultMat + 2)) - words)) //Checking if the word matches diagonally
						{
							*(*(resultMat) + words) = *(*(resultMat)); //Storing the x, y and z co-ordinates of the next letter
							*(*(resultMat + 1) + words) = *(*(resultMat + 1)) + words;
							*(*(resultMat + 2) + words) = *(*(resultMat + 2)) - words;
							match = true;
						}
					}
					else if ((*(*(resultMat + 1)) - words) >= 0)
					{
						if (*(input + words) == *(*(*(mat + *(*(resultMat))) + *(*(resultMat + 1)) - words) + *(*(resultMat + 2)) - words)) //Checking if the word matches diagonally
						{
							*(*(resultMat) + words) = *(*(resultMat)); //Storing the x, y and z co-ordinates of the next letter
							*(*(resultMat + 1) + words) = *(*(resultMat + 1)) - words;
							*(*(resultMat + 2) + words) = *(*(resultMat + 2)) - words;
							match = true;
						}
					}
					else if ((*(*(resultMat)) + words) < xSize)
					{
						if (*(input + words) == *(*(*(mat + *(*(resultMat)) + words) + *(*(resultMat + 1))) + *(*(resultMat + 2))) - words) //Checking if the word matches diagonally
						{
							*(*(resultMat) + words) = *(*(resultMat)) + words; //Storing the x, y and z co-ordinates of the next letter
							*(*(resultMat + 1) + words) = *(*(resultMat + 1));
							*(*(resultMat + 2) + words) = *(*(resultMat + 2)) - words;
							match = true;
						}
					}
					else if ((*(*(resultMat)) - words) >= 0)
					{
						if (*(input + words) == *(*(*(mat + *(*(resultMat)) - words) + *(*(resultMat + 1))) + *(*(resultMat + 2))) - words) //Checking if the word matches diagonally
						{
							*(*(resultMat) + words) = *(*(resultMat)) - words; //Storing the x, y and z co-ordinates of the next letter
							*(*(resultMat + 1) + words) = *(*(resultMat + 1));
							*(*(resultMat + 2) + words) = *(*(resultMat + 2)) - words;
							match = true;
						}
					}

				}

				if ((*(*(resultMat + 1)) + words) < ySize)
				{
					if (*(input + words) == *(*(*(mat + *(*(resultMat))) + *(*(resultMat + 1)) + words) + *(*(resultMat + 2)))) //Checking if the word matches vertically
					{
						*(*(resultMat) + words) = *(*(resultMat)); //Storing the x, y and z co-ordinates of the next letter
						*(*(resultMat + 1) + words) = *(*(resultMat + 1)) + words;
						*(*(resultMat + 2) + words) = *(*(resultMat + 2));
						match = true;
					}
					else if ((*(*(resultMat)) + words) < xSize)
					{
						if (*(input + words) == *(*(*(mat + *(*(resultMat)) + words) + *(*(resultMat + 1)) + words) + *(*(resultMat + 2)))) //Checking if the word matches diagonally
						{
							*(*(resultMat) + words) = *(*(resultMat)) + words; //Storing the x, y and z co-ordinates of the next letter
							*(*(resultMat + 1) + words) = *(*(resultMat + 1)) + words;
							*(*(resultMat + 2) + words) = *(*(resultMat + 2));
							match = true;
						}
					}
					else if ((*(*(resultMat)) - words) >= 0)
					{
						if (*(input + words) == *(*(*(mat + *(*(resultMat)) - words) + *(*(resultMat + 1)) + words) + *(*(resultMat + 2)))) //Checking if the word matches diagonally
						{
							*(*(resultMat) + words) = *(*(resultMat)) - words; //Storing the x, y and z co-ordinates of the next letter
							*(*(resultMat + 1) + words) = *(*(resultMat + 1)) + words;
							*(*(resultMat + 2) + words) = *(*(resultMat + 2));
							match = true;
						}
					}
				}

				if ((*(*(resultMat + 1)) - words) >= 0)
				{
					if (*(input + words) == *(*(*(mat + *(*(resultMat))) + *(*(resultMat + 1)) - words) + *(*(resultMat + 2)))) //Checking if the word matches vertically in reverse
					{
						*(*(resultMat) + words) = *(*(resultMat)); //Storing the x, y and z co-ordinates of the next letter
						*(*(resultMat + 1) + words) = *(*(resultMat + 1)) - words;
						*(*(resultMat + 2) + words) = *(*(resultMat + 2));
						match = true;
					}
					else if ((*(*(resultMat)) + words) < xSize)
					{
						if (*(input + words) == *(*(*(mat + *(*(resultMat)) + words) + *(*(resultMat + 1)) - words) + *(*(resultMat + 2)))) //Checking if the word matches diagonally
						{
							*(*(resultMat) + words) = *(*(resultMat)) + words; //Storing the x, y and z co-ordinates of the next letter
							*(*(resultMat + 1) + words) = *(*(resultMat + 1)) - words;
							*(*(resultMat + 2) + words) = *(*(resultMat + 2));
							match = true;
						}
					}
					else if ((*(*(resultMat)) - words) >= 0)
					{
						if (*(input + words) == *(*(*(mat + *(*(resultMat)) - words) + *(*(resultMat + 1)) - words) + *(*(resultMat + 2)))) //Checking if the word matches diagonally
						{
							*(*(resultMat) + words) = *(*(resultMat)) - words; //Storing the x, y and z co-ordinates of the next letter
							*(*(resultMat + 1) + words) = *(*(resultMat + 1)) - words;
							*(*(resultMat + 2) + words) = *(*(resultMat + 2));
							match = true;
						}
					}

				}
				if ((*(*(resultMat)) + words) < xSize) //Checking if the word matches in 3D
				{
					if (*(input + words) == *(*(*(mat + *(*(resultMat)) + words) + *(*(resultMat + 1))) + *(*(resultMat + 2))))
					{
						*(*(resultMat) + words) = *(*(resultMat)) + words; //Storing the x, y and z co-ordinates of the next letter
						*(*(resultMat + 1) + words) = *(*(resultMat + 1));
						*(*(resultMat + 2) + words) = *(*(resultMat + 2));
						match = true;
					}
				}
				if ((*(*(resultMat)) - words) >= 0) //Checking if the word matches in 3D in reverse
				{
					if (*(input + words) == *(*(*(mat + *(*(resultMat)) - words) + *(*(resultMat + 1))) + *(*(resultMat + 2))))
					{
						*(*(resultMat) + words) = *(*(resultMat)) - words; //Storing the x, y and z co-ordinates of the next letter
						*(*(resultMat + 1) + words) = *(*(resultMat + 1));
						*(*(resultMat + 2) + words) = *(*(resultMat + 2));
						match = true;
					}
				}
				if (match == false)
				{
					letter = false; //If more than one letter doesn't match, look for another
					break;
				}
				if (match == true && words == colSize - 1)
				{
					found = true;
				}
				match = false;
			}
		}
		if (letter == true)
		{
			break; //Breaking the loop if all letters match
		}
		count++;
	}
	if (found == false)
	{
		for (int no = 0; no < 3; no++)
		{
			for (int no2 = 0; no2 < colSize; no2++)
			{
				*(*(resultMat + no) + no2) = -1; //Assigning -1 to all values if match isn't found
			}
		}
	}
	return found;
}

void DeleteArray(char***& arr, int x, int y, int z) //Function to delete the array
{
    	for (int delx = 0; delx < x; delx++)
	{
		for (int dely = 0; dely < y; dely++)
		{
			delete[] *(*(arr + delx) + dely); //Deleting the Z-axis
			*(*(arr + delx) + dely) = NULL; //Equating it to NULL
		}
		delete[] *(arr + delx); //Deleting the Y-axis
		*(arr + delx) = NULL; //Equating it to NULL
	}
	delete [] arr; //Deleting the X-axis
	arr = NULL;
}

//----------------------------------------------------------------------------------Start of Q3--------------------------------------------------------------------------------------------
//Q3 Part 1
//Helper function for perfect numbers
int checkperfectNumber(int number, int divisor)
{
	if (divisor == 1)
	{
		return 1; //Base case
	}
	if (number % divisor == 0)
	{
		return divisor + checkperfectNumber(number, divisor - 1); //Dividing by smaller numbers and adding the sum
	}
	else
	{
		return checkperfectNumber(number, divisor - 1); //Dividing by smaller numbers and not adding the sum
	}
}

bool isperfectNumber(int n)
{
	if (n == 1)
	{
		return isperfectNumber(n + 1); //Base case
	}
	if (checkperfectNumber(n, n - 1) == n) //Checking if the number is perfect
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Q3 Part 2
int findVowels(char* str)
{
 	if (*str == '\0') //Base case
	{
		return 0;
	}
	if (*str == 'a' || *str == 'e' || *str == 'i' || *str == 'o' || *str == 'u') //Checking for vowel
	{
		return 1 + findVowels(str + 1); //Returning +1 if vowel is found
	}
	else
	{
		return findVowels(str + 1); //Returning +0 if vowel is not found
	}
}

//Q3 Part 3
int pascal(int row, int col)
{
	if (row == col) //Checking if the column number and row number are same
	{
		return 1; //There is always a 1 at the location where the row and column numbers are the same
	}
	else if (col == 0)
	{
		return 1; //There is always a 1 in the fist column
	}
	else
	{
		return pascal(row - 1, col) + pascal(row - 1, col - 1); //Calling the function twice, once while subtracting only rows and once while subtracting both rows anc columns
	}
}

//Q3 Part 4
//Helper function for Pattern 1
void PrintSpaces(int space)
{
	if (space == 1) //Base case
	{
		return;
	}
	else
	{
		cout << " "; //Outputting spaces
		if (space > 0)
		{
			PrintSpaces(space - 1); //If space is positive
		}
		else
		{
			PrintSpaces(space + 1); //If space is negative
		}

	}
}

void PrintPattern1(int start, int end)
{
	if (end == 1) //Base case
	{
		return;
	}
	else
	{
		PrintSpaces(end - start); //Calling helper function
		cout << "*" << endl; //Printing stars
		PrintPattern1(start + 1, end - 1); //Calling the function again
	}
}

//Q3 Part 5
//Helper function to print stars
void printStars(int stars)
{
	if (stars == 0) //Base case
	{
		return;
	}
	else
	{
		cout << "*"; //Printing
		return printStars(stars - 1); //Recursion
	}
}

//Helper function to print spaces
void printSpaces(int spaces, int original)
{
	if (spaces == original) //Base case
	{
		return;
	}
	else
	{
		cout << " " << " "; //Printing
		printSpaces(spaces + 1, original); //Recursion
	}
}

//Helper function to create the shape
void HollowShape(int n, int original)
{
	if (n == 0) //Base case
	{
		return;
	}
	else
	{
		//Calling Helper functions
		printStars(n);
		printSpaces(n, original);
		printStars(n);
		cout << endl;
		HollowShape(n - 1, original); //Recursion
	    	printStars(n);
		printSpaces(n, original);
		printStars(n);
	    	cout << endl;
	}
}

//Main function of Q3 Part 5
void printHollowDiamond(int n)
{
	if (n == 0) //Base case
	{
		return;
	}
	else
	{
		HollowShape(n, n); //Calling helper function
		if (n == 0)
		{
			printHollowDiamond(n - 1); //Recursion
		}
	}
}

//Q3 Part 6
//Helper function to print spaces
void PrintSpaces2(int space)
{
	if (space == 1) //Base case
	{
		return;
	}
	else
	{
		cout << " "; //Outputting spaces
		PrintSpaces2(space - 1); //Recursion
	}
}

//Helper function to print dashes
void PrintDashes(int dash)
{
	if (dash == 0) //Base case
	{
		return;
	}
	else
	{
		cout << "-"; //Outputting spaces
		PrintDashes(dash - 1); //Recursion
	}
}

//Helper function to print stars
void PrintStars(int star, int original)
{
	if (star == original) //Base case
	{
		return;
	}
	else
	{
		cout << "**"; //Printing two stars
		PrintStars(star + 1, original); //Recursion
	}
}

//Main function of Q3 Part 6
void PrintPattern2(int value, int original)
{
	if (value == 1) //Base case
	{
		cout << "#"; //Printing hash
		//Calling helper functions
		PrintDashes(value);
		PrintStars(value, original);
		cout << "|"; //Printing vertical line
		PrintStars(value, original);
		PrintDashes(value);
		cout << "#";
		cout << endl; //Moving to next
		return;
	}
	else
	{
		//Calling helper functions
		PrintSpaces2(value); 
		cout << "#";
		PrintDashes(value);
		PrintStars(value, original);
		cout << "|";
		PrintStars(value, original);
		PrintDashes(value);
		cout << "#";
		cout << endl;
		PrintPattern2(value - 1, original); //Calling the function again
		PrintSpaces2(value); //Calling helper function
		cout << "#";
		PrintDashes(value);
		PrintStars(value, original);
		cout << "|";
		PrintStars(value, original);
		PrintDashes(value);
		cout << "#";
		cout << endl;
	}

}

//----------------------------------------------------------------------------------Start of Q4--------------------------------------------------------------------------------------------
//Function to create the game board
int** snakeBoardCreation(int M, int N)
{
	//Declaring Variables
	int X = 0, Y = 0, X2 = 0;
	//Generating a 2D array as the board
	int **Board = new int*[M];
	for (int row = 0; row < M; row++)
	{
		*(Board + row) = new int[N];
	}
	for (int row = 0; row < M; row++)
	{
		for (int col = 0; col < N; col++)
		{
			*(*(Board + row) + col) = 0; //Initializing all values of array to 0
		}
	}
	if (M % 2 == 0)
	{
		*(*(Board)) = 100; //Making the End Point
	}
	else
	{
		*(*(Board) + N - 1) = 100; //Making the End Point
	}
	//Generating the Snakes and Ladders on the Board
	for (int snakes = 0; snakes < N - 1; snakes++)
	{
		do
		{
			X = rand() % M;
			Y = rand() % N;
		} while (*(*(Board + X) + Y) != 0 || X == 0);
		*(*(Board + X) + Y) = 4;

		do
		{
			X2 = rand() % M;
			Y = rand() % N;
		} while ((*(*(Board + X2) + Y) != 0 && X2 <= X) || X2 == M - 1);
		*(*(Board + X2) + Y) = 3;

		do
		{
			X = rand() % M;
			Y = rand() % N;
		} while (*(*(Board + X) + Y) != 0 || X == 0);
		*(*(Board + X) + Y) = 5;

		do
		{
			X2 = rand() % M;
			Y = rand() % N;
		} while ((*(*(Board + X2) + Y) != 0 && X2 <= X) || X2 == M - 1);
		*(*(Board + X2) + Y) = 6;
	}
	return Board;
}

//The function to display the board
void displayBoard(int** Board, int M, int N, int p1[2], int p2[2])
{
	//Title Screen
	static bool first = true;
	if (first == true)
	{
		cout << "____________________________________________________________" << endl;
		cout << "|                                                          |" << endl;
		cout << "|                   Snakes and Ladders                     |" << endl;
		cout << "|__________________________________________________________|" << endl;
		cout << "|                                                          |" << endl;
		cout << "|                     Press S to Start                     |" << endl;
		cout << "|     Press P to roll dice for the next player in game     |" << endl;
		cout << "|__________________________________________________________|" << endl;
		char start;
		while (start != 'S' && start != 's')
		{
			cin >> start;
		}
		first = false;
	}
	cout << endl;
	//Displaying the Board
	for (int col = 0; col < N * 13; col++)
	{
		cout << "_";
	}
	cout << endl;
	for (int row = 0; row < M; row++)
	{
		cout << "| ";
		for (int col = 0; col < N; col++)
		{
			if ((row == p1[0] && col == p1[1]) && (row == p2[0] && col == p2[1]))
			{
				cout << "  P1, P2  ";
			}
			else if (row == p1[0] && col == p1[1])
			{
				cout << "    P1    ";
			}
			else if (row == p2[0] && col == p2[1])
			{
				cout << "    P2    ";
			}
			else
			{
				if (*(*(Board + row) + col) == 0)
				{
					cout << "          ";
				}
				else if (*(*(Board + row) + col) == 3)
				{
					cout << "Snake Head";
				}
				else if (*(*(Board + row) + col) == 4)
				{
					cout << "Snake Tail";
				}
				else if (*(*(Board + row) + col) == 5)
				{
					cout << "Ladder Leg";
				}
				else if (*(*(Board + row) + col) == 6)
				{
					cout << "Ladder Top";
				}
				else if (*(*(Board + row) + col) == 100)
				{
					cout << " Game End ";
				}
				else if (*(*(Board + row) + col) == 101)
				{
					cout << " P1 Wins  ";
				}
				else if (*(*(Board + row) + col) == 102)
				{
					cout << " P2 Wins  ";
				}
			}
			cout << " | ";
		}
		cout << endl;
		cout << "|";
		for (int col = 0; col < N * 13 - 1; col++)
		{
			cout << "_";
		}
		cout << "|" << endl;
	}
	cout << endl;
}

//The function to generate new values of dice
int playdice()
{
	return (1 + rand() % 6); //Returning a random value between 1 and 6
}

//The function for ladder functionality
void ladderFound(int** Board, int p[1], int M, int N)
{
	cout << "You got lucky and found a ladder" << endl;
	bool found = false;
	for (int ladderx = p[0] - 1; ladderx >= 0; ladderx--)
	{
		for (int laddery = 0; laddery < N; laddery++)
		{
			if (*(*(Board + ladderx) + laddery) == 6) //Finding the nearest ladder top above the player
			{
				p[0] = ladderx; //Moving the player to the top of the ladder
				p[1] = laddery;
				found = true;
			}
			if (found == true)
			{
				break;
			}
		}
		if (found == true)
		{
			break;
		}
	}
	if (found == false)
	{
		for (int laddery = 0; laddery < N; laddery++)
		{
			if (*(*(Board + p[0]) + laddery) == 6)
			{
				p[1] = laddery;
				found = true;
			}
			if (found == true)
			{
				break;
			}
		}
	}
}

//The function for snake functionality
void snakeFound(int** Board, int p[2], int M, int N)
{
	cout << "Oops, the snake got you" << endl;
	bool found = false;
	for (int snakex = p[0] + 1; snakex < M; snakex++)
	{
		for (int snakey = 0; snakey < N; snakey++)
		{
			if (*(*(Board + snakex) + snakey) == 4) //Finding the nearest snake tail below the player
			{
				p[0] = snakex; //Moving the player down to the bottom of the snake
				p[1] = snakey;
				found = true;
			}
			if (found == true)
			{
				break;
			}
		}
		if (found == true)
		{
			break;
		}
	}
	if (found == false)
	{
		for (int snakey = 0; snakey < N; snakey++)
		{
			if (*(*(Board + p[0]) + snakey) == 4)
			{
				p[1] = snakey;
				found = true;
			}
			if (found == true)
			{
				break;
			}
		}
	}
}

//The main function that moves the pieces around the board
void playGame(int** Board, int M, int N, int p1[2], int p2[2])
{
	//Declaring Variables
	int roll = 0, player = 1;
	bool game = true;
	char choice;
	while (game == true)
	{
		//To pause until the player presses the button
		choice = ' ';
		while (choice != 'P' && choice != 'p')
		{
			cin >> choice;
		}
		if (player == 1) //Alternating between players
		{
			roll = playdice(); //Rolling the dice
			cout << "Player 1 rolled: " << roll << endl;
			//In case the player doesn't land exactly on the end tile
			if (p1[0] == 0 && p1[1] + roll > N - 1 && M % 2 == 1)
			{
				cout << "Roll too high, try again" << endl;
			}
			else if (p1[0] == 0 && p1[1] - roll < 0 && M % 2 == 0)
			{
				cout << "Roll too high, try again" << endl;
			}
			else if (p1[0] % 2 == 0)
			{
				if (M % 2 == 0)
				{
					p1[1] -= roll; //Moving the player left
				}
				else
				{
					p1[1] += roll; //Moving the player right
				}
			}
			else
			{
				if (M % 2 == 0)
				{
					p1[1] += roll; //Moving the player right
				}
				else
				{
					p1[1] -= roll; //Moving the player left
				}
			}

			if (p1[1] >= N)
			{
				p1[0] -= 1; //Moving the player up
				p1[1] = N - (p1[1] - N + 1); //Moving the player left
			}
			else if (p1[1] < 0)
			{
				p1[0] -= 1; //Moving the player up
				p1[1] = N - (N + p1[1] + 1); //Moving the player right
			}
			if (p1[0] == 0 && p1[1] == N - 1 && M % 2 == 1) //Checking if player reaches end
			{
				cout << "Player 1 wins" << endl;
				*(*(Board + p1[0]) + p1[1]) = 101;
				p1[0] = -1;
				game = false; //Ending the game
			}
			else if (p1[0] == 0 && p1[1] == 0 && M % 2 == 0) //Checking if player reaches end
			{
				cout << "Player 1 wins" << endl;
				*(*(Board + p1[0]) + p1[1]) = 101;
				p1[1] = -1;
				game = false; //Ending the game
			}
			else
			{
				if (*(*(Board + p1[0]) + p1[1]) == 5) //If player lands on ladder foot
				{
					ladderFound(Board, p1, M, N); //Calling the ladder function
				}
				else if (*(*(Board + p1[0]) + p1[1]) == 3) //If player lands on snake head
				{
					snakeFound(Board, p1, M, N); //Calling the snake function
				}
			}
			player = 2; //Switching players
		}
		else if (player == 2)
		{
			roll = playdice(); //Rolling the dice
			cout << "Player 2 rolled: " << roll << endl;
			//In case the player doesn't land exactly on the end tile
			if (p2[0] == 0 && p2[1] + roll > N - 1 && M % 2 == 1)
			{
				cout << "Roll too high, try again" << endl;
			}
			else if (p2[0] == 0 && p2[1] - roll < 0 && M % 2 == 0)
			{
				cout << "Roll too high, try again" << endl;
			}
			else if (p2[0] % 2 == 0)
			{
				if (M % 2 == 0)
				{
					p2[1] -= roll; //Moving the player left
				}
				else
				{
					p2[1] += roll; //Moving the player right
				}
			}
			else
			{
				if (M % 2 == 0)
				{
					p2[1] += roll; //Moving the player right
				}
				else
				{
					p2[1] -= roll; //Moving the player left
				}
			}

			if (p2[1] >= N)
			{
				p2[0] -= 1; //Moving the player up
				p2[1] = N - (p2[1] - N + 1); //Moving the player left
			}
			else if (p2[1] < 0)
			{
				p2[0] -= 1; //Moving the player up
				p2[1] = N - (N + p2[1] + 1); //Moving the player right
			}
			if (p2[0] == 0 && p2[1] == N - 1 && M % 2 == 1) //Checking if player reaches end
			{
				cout << "Player 2 wins" << endl;
				*(*(Board + p2[0]) + p2[1]) = 102;
				p2[0] = -1;
				game = false; //Ending the game
			}
			else if (p2[0] == 0 && p2[1] == 0 && M % 2 == 0) //Checking if player reaches end
			{
				cout << "Player 2 wins" << endl;
				*(*(Board + p2[0]) + p2[1]) = 102;
				p2[1] = -1;
				game = false; //Ending the game
			}
			else
			{
				if (*(*(Board + p2[0]) + p2[1]) == 5) //If player lands on ladder foot
				{
					ladderFound(Board, p2, M, N); //Calling the ladder function
				}
				else if (*(*(Board + p2[0]) + p2[1]) == 3) //If player lands on snake head
				{
					snakeFound(Board, p2, M, N); //Calling the ladder function
				}
			}
			player = 1; //Switching players
		}
		displayBoard(Board, M, N, p1, p2); //Displaying the game
	}
}


void startSnakeGame() // controller of the game
{
	srand(time(0)); //To randomize locations and die rolls each time
	int M = 5, N = 6; //Rows and Columns of the Board
	int **Board = snakeBoardCreation(M, N); //Making a Board
	int p1[2] = {M - 1, 0}, p2[2] = {M - 1, 0}; //Making two arrays to store locations of players
	displayBoard(Board, M, N, p1, p2); //Displaying the game
	playGame(Board, M, N, p1, p2); //Calling the main function to play the game
}

//-------------------------------------------------------Main function to run Q3: Part 4,5 and 6, and Q4--------------------------------------------------------------------------------------

int main()
{
	//Q3 Part 4
	PrintPattern1(1, 16);
	//Q3 Part 5
	printHollowDiamond(7);
	//Q3 Part 6
	PrintPattern2(5, 5);
	//Q4
	startSnakeGame();
}
