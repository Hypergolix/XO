#include <iostream>

using namespace std;

#define X 3
#define Y 3
bool running = true;
char board[X][Y];
int userInput_int;
char userInput_char;
short int inputString[2];
short int player = 1; //could probably be a bool as theres only 2 players
short int gameRound = 0;
short int totalCellValue;

int wait; // should use a proper wait function

// for some reason x and y are backwards and its annoying and this for loop should be the other way around 


void drawGame()
{
	cout << "     a     b     c" << "\n";
	cout << "\n";
	cout << " 1   " << board[0][0] << "  |" << "  " << board[0][1] << "  |" << "  " << board[0][2] << "\n"; // this seems excessive. Also bad ASCII art. could it be in a for loop?
	cout << "     " << "-------------" << "\n";
	cout << " 2   " << board[1][0] << "  |" << "  " << board[1][1] << "  |" << "  " << board[1][2] << "\n";
	cout << "     " << "-------------" << "\n";
	cout << " 3   " << board[2][0] << "  |" << "  " << board[2][1] << "  |" << "  " << board[2][2] << "\n\n"; // get rid of the unneccesary quatations

}
void inputCheck()
{
	while (running)
	{

		do {
			cout << "Player " << player << "'s turn, input coordinate: " << "\n"; //player 1 starts

			cin >> userInput_int; // no mouse control so use coordinates
			cin >> userInput_char;// i don't like this, seems like overuse of variables

			// could either convert char to an int or write a case for each letter. one is more code and one uses more resources
			//make a check that something is input as well as the first being a number and the second being a char

			inputString[0] = userInput_int; //first  number is Y coordinate
			inputString[1] = userInput_char; // second character is X coordinate

			if (inputString[0] < 1 || inputString[0] > 3 || inputString[1] < 97 || inputString[1] > 99) // seems like repeat code
			{
				cout << "Please enter a number and letter within the grid" << "\n";
			}
		} while (inputString[0] < 1 || inputString[0] > 3 || inputString[1] < 97 || inputString[1] > 99);

		inputString[0] --; // converts to number that array can use for the next bit
		inputString[1] = (inputString[1] - 97); // do i even need brackets?

		if (board[inputString[0]][inputString[1]] == 'O' || board[inputString[0]][inputString[1]] == 'X')
		{
			cout << "That cell has been taken" << "\n";
			//inputCheck();
		}else
		{
			break; // this needs to actually break the while loop 
		}
	}
	//has to be a more efficient way to say above 0 and below 4
}
void winCheck()
{
	for(int i = 0; i < 2; i++)
	{
		for (int y = 0; y < Y; y++) 
		{
			for (int x = 0; x < X; x++)
			{
				if (i > 0)
				{
					totalCellValue = totalCellValue + board[y][x];
				}
				else
				{
					totalCellValue = totalCellValue + board[x][y];
				}
	
				//board[1][x] = 'A';// checks sideways at the moment
	
				if (totalCellValue == 264 || totalCellValue == 237)
				{
					cout << "Player "<< player << " won!" << "\n";
					drawGame();
					running = false;
					break;
				}
	
			}
			totalCellValue = 0;
		} // use variables for the x and y so you only need one of these
	}
	for(int j = -1; j < 2; j++)
	{
		totalCellValue = totalCellValue + board[( 1 + (j))][(1 + (j))];

		if (totalCellValue == 264 || totalCellValue == 237) // repeat code, would like to avoid too many functions however
		{
			cout << "Player " << player << " won!" << "\n";
			drawGame(); // is this inefficient? this function is called often 
			running = false;
		}
	}
	totalCellValue = 0;

	for (int j = -1, k = 2; j < 2; j++) 
	{

		totalCellValue = totalCellValue + board[(1 + j + k)][(1 + j + k)]; 

		if (totalCellValue == 264 || totalCellValue == 237) // repeat code, would like to avoid too many functions however
		{
			cout << "Player " << player << " won!" << "\n";
			drawGame(); // is this inefficient? this function is called often 
			running = false;
		}
		k = k - 2; // this also seems wrong, would be better inside the for loop
	}

		//cout << totalCellValue << "\n";

		//cout << (1 + (j)) << (1 + (j)) << "\n";

	
	totalCellValue = 0;


}
int main()
{
	while(running)
	{
		system("CLS");
		drawGame();
		inputCheck();

		if (player == 1) 
		{
			board[inputString[0]][inputString[1]] = 'O';
			winCheck();
			player = 2; // hopefully it doesn't try the else statement
		}else
		{
			board[inputString[0]][inputString[1]] = 'X';
			winCheck();
			player = 1; // hope that doesn't cause a problem
		}

		//uhhh do a for loop or something 


		//cout << "player:" << player;
		//cout << inputString[0] << "\n" << inputString[1]; //there has to be a better way of doing this - maybe just output the entire array?
		gameRound++;
		if (gameRound == 9)
		{
			drawGame();
			cout << "It's a Tie";
			//should be running = false

			running = false;

			//break;
		}
		//cout << userInput_int << userInput_char;
		//cin >> wait;
	}

	cin >> wait;
	return 0;
}