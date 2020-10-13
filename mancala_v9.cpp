// Trevor Judd
// Mancala
// The program calls multiple functions to construct the Mancala board,  
// numbers the bins, fills the bins with "beads", tallies the player's 
// scores, and determines the winner

#include <iostream>
#include <iomanip>
using namespace std;

const int BINS = 14; //number of bins on the board

//function prototypes
void showBoard(int beadArray[BINS]); //builds the game board; takes in "beadArray"; returns nothing
void makeSolidLine(int num); //helps showBoard build the outer edge and middle of the game board; takes in "num"; returns nothing
void makeDottedLine(); //helps showBoard build the interior game board; no parameters; returns nothing
void showTopRowNumbers(); //numbers the top row bins on the board; no parameters; returns nothing
void showBottomRowNumbers(); //numbers the bottom row bins; no parameters; returns nothing
void startingArray(int beadArray[BINS]); //fills the bins with beads; takes in "beadArray"; returns nothing
void showTopBins(int beadArray[BINS]); //shows the number of beads in the top bins; takes in "beadArray"; returns nothing
void showBottomBins(int beadArray[BINS]); //shows the number of beads in the bottom bins; takes in "beadArray"; returns nothing
int gameOverCheck(int beadArray[BINS]); //checks to see if the game is over; takes in "beadArray"; returns "winner"
void getStartingBin(int beadArray[BINS], int player, int &move); //user chooses which bin they wish to start their turn with; takes in "beadArray" "player" and "move"; "move" passed by reference; returns nothing
void dropBeads(int beadArray[BINS], int player, int &move); //redistributes beads; takes in "beadArray" "player" and "move"; "move" passed by reference; returns nothing

int main()
{

	int gameStatus = 0; //player one, player two, or neither
	int beadArray[BINS]; //declare array
	int player = 0; //player 1 or 2
	int move = 0; //bin to grab beads from
	
	startingArray(beadArray); //function call
	showBoard(beadArray); //function call
    
    cout << "Choose a side.  Player 1 is top.  Player 2 is bottom. ";
    cin >> player;
    while (player <= 0 || player > 2) //user is only given two choices: player 1 or player 2
    {
          cout << "Invalid. Choose Player 1 or Player 2. ";
          cin >> player;
    }
    
    gameStatus = gameOverCheck(beadArray); //checks the game status
	
	while (gameStatus == -1) //-1 means game is in progress
	{
          dropBeads(beadArray, player, move); //moves beads around
          gameStatus = gameOverCheck(beadArray);//checks the game status every turn        
                    
          //switch players
          if (player == 1)
          {
              player = 2;
          }
          else
          {
              player = 1;
          }
    }

    //declares a winner, prints scores for player 1 and player 2
    if (gameStatus == 1 || gameStatus == 2)
    {
        cout << "GameOver!" << endl;
        cout << "\nThe winner this round is Player " << gameStatus << endl;
        cout << "Player 1 total points: " << beadArray[6] << endl;
        cout << "Player 2 total paints: " << beadArray[13] << endl;
    }
    else
    {
        cout <<"\nTie!" << endl;
    }
        

	cout << endl;
	system("pause");
	return 0;
}

/***********************************************************************/
/* Function "makeSolidLine" prints stars in a horizontal line          */
/* parameter num of stars                                              */
/* returns nothing                                                     */
/***********************************************************************/
void makeSolidLine(int num)
{
	int count = 0;

	while (count < num)
	{ // begin while
		cout << "*";
		count++; //loop control variable
	} //end while
}

/***********************************************************************/
/* Function "makeDottedLine" prints stars and spaces                   */
/* no parameters                                                       */
/* returns nothing                                                     */
/***********************************************************************/
void makeDottedLine()
{
	int starCounter = 0; //counts the number of stars
	int spaceCounter = 0; //counts the number of spaces

	cout << "*";

	while (starCounter < 8)
	{ //begin while loop one
	    while (spaceCounter < 6)
	    { //begin loop two
            cout << " ";
		    spaceCounter++; //loop control variable one
        } //end loop two
        spaceCounter = 0; //resets the space counter for each new loop
		
    cout << "*";
    starCounter++; //loop control variable two
	} //end while loop one
	cout << endl;
}

/***********************************************************************/
/* Function "showBoard" builds the Mancala game board                  */
/* no parameters                                                       */
/* returns nothing                                                     */
/***********************************************************************/
void showBoard(int beadArray[BINS])
{
	makeSolidLine(57); //builds the top edge of the board
	cout << endl;
	makeDottedLine();
	showTopRowNumbers(); //number's the top bins and prints stars and spaces
	makeDottedLine();
	showTopBins(beadArray);	
	makeDottedLine();
	/* creates the solid line that divides the board and assigns the
	left and right bins their numbers */
	cout << "*" << setw(4) << "13" << setw(3) << "*";
	makeSolidLine(42);
	cout << setw(4) << "6" << setw(3) << "*" << endl;
	makeDottedLine();
	showBottomRowNumbers(); //numbers the bottom bins and prints stars and spaces
	makeDottedLine();
	showBottomBins(beadArray);
	makeDottedLine();
    makeSolidLine(57); //builds the bottom edge of the board
    cout << endl;
}

/***********************************************************************/
/* Function "showTopRowNumbers" numbers the top bins from 0 to 5       */
/* no parameters                                                       */
/* returns nothing                                                     */
/***********************************************************************/
void showTopRowNumbers()
{
	int topNum = 0; //number's the top row bins
	int counter = 0; //loop control variable

	cout << "*" << setw(7) << "*";

	while (counter < 6)
	{
		topNum = (counter + 1) - 1;
		cout << setw(4) << topNum << setw(3) << "*";
		counter++;
	}
	cout << setw(7) << "*";
	cout << endl;
}

/*************************************************************************/
/* Function "showBottomRowNumbers" numbers the bottom bins from 12 to 7  */
/* no parameters                                                         */
/* returns nothing                                                       */
/*************************************************************************/
void showBottomRowNumbers()
{
	int bottomNum = 13; //number's the bottom row bins

	cout << "*" << setw(7) << "*";

	while (bottomNum > 7)
	{
		bottomNum = bottomNum - 1;
		cout << setw(4) << bottomNum << setw(3) << "*";
	}
	cout << setw(7) << "*";
	cout << endl;
}

/*************************************************************/
/* Function "startingArray" fills the array "beadArray" with */
/* four beads in each bin except the two end bins which      */
/* get zero beads                                            */
/* Parameter "int beadArray[BINS]"                           */
/*************************************************************/
void startingArray(int beadArray[BINS])
{
	int i = 0; //loop control variable

	while (i < BINS)
	{
	    beadArray[i] = 4;
		i++;
	}
	beadArray[6] = 0;
	beadArray[13] = 0;
}

/*********************************************************************/
/* Function "showTopBins" prints the number of beads in each top bin */
/* Parameter "int beadArray[BINS]"                                   */
/* returns nothing                                                   */
/*********************************************************************/
void showTopBins(int beadArray[BINS])
{
    int x = 0; //loop control variable
    
    cout << "*" << setw(7) << "*";

	while (x < (BINS - 8))
	{
		cout << setw(4) << beadArray[x] << setw(3) << "*";
		x++;
	}
	cout << setw(7) << "*";
	cout << endl;
}

/***************************************************************************/
/* Function "showBottomBins" prints the number of beads in each bottom bin */
/* Parameter "int beadArray[BINS]"                                         */
/* returns nothing                                                         */
/***************************************************************************/
void showBottomBins(int beadArray[BINS])
{
    int x = 13; //loop control variable
    
    cout << "*";

	while (x >= (BINS - 8))
	{
        cout << setw(3) << beadArray[x] << setw(4) << "*";
		x--;
	}
	cout << endl;
}

/*************************************************************************/
/* Function "gameOverCheck" sums each player's points and determines the */
/* winner of that round                                                  */
/* Parameter "int beadArray[BINS]"                                       */
/* returns "winner"                                                      */
/*************************************************************************/
int gameOverCheck(int beadArray[BINS])
{
    int player1total = 0; //number of player one's beads still on the board
	int player2total = 0; //number of player two's beads still on the board
	int winner = 0; //player 1, player 2, tie, or "in progress"
	
	for (int a = 0; a < 6; a++)
	{
        player1total = player1total + beadArray[a];//sums the number of beads in bins 0 through 5
    }
    
    for (int b = 7; b < 13; b++)
    {
        player2total = player2total + beadArray[b];//sums the number of beads in bins 7 through 12
    }
    
    //whichever player clears their side of beads first then collects their opponent's remaining beads
    if (player1total == 0 || player2total == 0)
    {   
        beadArray[6] = beadArray[6] + player2total;
        beadArray[13] = beadArray[13] + player1total;
        
        //board is cleared
        for (int c = 0; c < 14; c++)
        {
            if (c != 6 && c != 13)
            {
                 beadArray[c] = 0;
            }
            else {;}
        }
        
        //winner is determined
        if (beadArray[6] > beadArray[13])
        {
            winner = 1;
        }
        else if (beadArray[13] > beadArray[6])
        {
            winner = 2;
        }
        else
        {
            winner = 0; //tie
        }
    }
    else 
    {
        winner = -1; //game still in progress
    }
    
    return winner;
}

/*************************************************************************/
/* Function "getStartingBin" asks the player which bin they want to      */
/* start with                                                            */
/* Parameter "int beadArray[BINS]"  and "int player"                     */
/* passes "move" by reference                                            */
/*************************************************************************/
void getStartingBin(int beadArray[BINS], int player, int &move)
{
    int startingBin = 0; //bin to take beads from
    int lowbin = 0; //lowest numbered bin the user can take beads from
    int highbin = 0; //highest numbered bin the user can take beads from
    
    cout << "Player " << player << " choose a bin: " << endl;
    cin >> startingBin;
    
    if (player == 1) //player cannot take from player 2's bins
    {
          lowbin = 0;
          highbin = 5;
    }
    else //player 2 cannot take from player 1's bins
    {
        lowbin = 7;
        highbin = 12;
    }
    
    //player must select a bin within their range
    while (startingBin < lowbin || startingBin > highbin || beadArray[startingBin] == 0)
    {
        cout << "\nSelect a valid bin. ";
        cin >> startingBin;
    }
    
    move = startingBin; //move is passed by reference
}

/*************************************************************************/
/* Function "dropBeads" distributes beads each turn                      */
/* Parameter "int beadArray[BINS]", "int player", and "int &move"        */
/* returns nothing                                                       */
/*************************************************************************/
void dropBeads(int beadArray[BINS], int player, int &move)
{
    int endBin = 0; //player's home bin 
    int opponentEndBin = 0; //opponent's home bin
    int hand = 0; //takes beads
    int end = 0; //game over
    
    //cannot drop beds in opponent's home bin
    if (player == 1)
    {
        endBin = 6;
        opponentEndBin = 13;
    }    
    else
    {
        endBin = 13;
        opponentEndBin = 6;
    }
    
    do { //begin do-while 1
           getStartingBin(beadArray, player, move);//function call
           //cout << move << " first do while" << endl;
           
           do { //begin do-while 2
                   hand = beadArray[move]; //hand takes beads from that location
                   beadArray[move] = 0; //empties location of beads
                   
                   //begin while
                   while (hand > 0)
                   {
                       move++; //hand moves from bin to bin until empty
                       move = move % 14; //hand cannot move out of the array
                       
                       //cannot deposit beads in opponents home bin
                       if (move == opponentEndBin)
                       {
                           move++; //hand skips opponent home bin
                           move = move % 14; //hand cannot move out of the array
                       }
                       else{;}
                   beadArray[move]++; //L.C.V.
                   hand--; //L.C.V.
                   }//end while                   
               showBoard(beadArray); 
               //if last bead in hand falls in a bin with more than one bead, player gets another turn             
               } while (beadArray[move] > 1 && move != endBin); //end do-while 2
               
               end = gameOverCheck(beadArray); //checks to see if game is over        
        //loop will terminate if last bead in hand falls in a bin (other than home bin) with no beads 
        //and when gameOverCheck returns a value other than -1       
        } while (move == endBin && end == -1); //end do-while 1
}
