/*
    AUTHORS OF SUDOKU.C ARE JAKE OLS AND ORSHI KOZEK
*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

const int N = 9; // board constant dimensions

bool checkPuzzle(int board[N][N], int rowToCheck, int columnToCheck, int guess);
void reset(int board[N][N], int start[N][N]);

/*
Generates a random Soduku board that can be played
Returns the starting board as a 2D array
*/

int canBePlayed(int puzzle[][9], int row, int col, int num)
{
    int rowStart = (row/3) * 3;
    int colStart = (col/3) * 3;
    int i, j;

    for(i=0; i<9; ++i)
    {
        if (puzzle[row][i] == num) return 0;
        if (puzzle[i][col] == num) return 0;
        if (puzzle[rowStart + (i%3)][colStart + (i/3)] == num) return 0;
    }
    return 1;
}

void generateStartingBoard(int board[N][N], int start[N][N]){
    int i,j,k,f,g,h,l;
    for(i = 0; i < 9; i++){
        for(j=0; j < 9; j++){
            board[i][j] = 0;
            start[i][j] = 0;
        }
    }
    srand(time(0)); 
    // adds a random amount of numbers to board first 
    for(k = 0; k < rand() % 10; k++){
        int randomColumn = rand() % 10;
        int randomRow = rand() % 10;
        int randomNumber = rand() % 10;
        board[randomRow][randomColumn] = randomNumber;
    }

    int times = 0;
    // adds random numbers to the corners
    int randomTopLeft = rand() %10;
    board[0][0] = randomTopLeft;
    int randomTopRight = rand() % 10;
    board[8][8] = randomTopRight;
    if(solveBoard(board, 0, 0)){
        // now removed values from the board -> well do it a bunch 
        while(times < 5){
        for(f = rand() % 10; f < N; f++){
            for(g = rand() % 10; g < N; g++){
                board[f][g] = 0;
            }
    }

    for(h = rand() % 10; f < N; h++){
        for(l = rand() % 10; g < N; l++){
            board[h][l] = 0;
        }
    }
    times++;
    }


        
    }
    else {
        reset(board, start);
        generateStartingBoard(board, start);
    }
 
    

}


// will return validity
int solveBoard(int board[][N], int row, int col){
    
    int i;
    if(row < N && col < N)
    {
        if(board[row][col] != 0)
        {
            if((col+1) < N){
                return solveBoard(board, row, col+1);
            } 
            else if((row+1) < N ){
                return solveBoard(board, row+1, 0);
            } 
            else {
                return 1;
            }
        }
        else{
            for(i=0; i< N; ++i) {
                if(canBePlayed(board, row, col, i+1)) {
                    board[row][col] = i+1;
                    if((col+1)<9) {
                        if(solveBoard(board, row, col +1)){
                            return 1;
                        }
                        else{
                            board[row][col] = 0;
                        } 
                    }
                    else if((row+1) < N){
                        if(solveBoard(board, row+1, 0)){
                            return 1;
                        }
                        else{
                            board[row][col] = 0;
                        } 
                    }
                    else {
                        return 1;
                    }
                }
            }
        }
        return 0;
    }
    else{
        return 1;
    }

}


void GeneratePuzzle(){
    int board[9][9];
}

void CreateSudokuPuzzle(int board[N][N], int start[N][N]){
    int i, j;
    for(i = 0; i < N; i++){
    for(j = 0; j < N; j++){
    board[i][j] = start[i][j];
    }
    }
}

int RandomNumber(){
    return rand() % 10;
}

void Display(int board[N][N]){
    printf("\n     0  1  2     3  4  5     6  7  8 \n");
    printf("   ===================================\n");
    int i, j;
    for (i = 0; i < N; i++)
    {
        printf("%d | ", i);
        for(j = 0; j < N; j++){
            if(j != 0 && j % 3 == 0)
                printf(" | ");
            
            printf(" %d ", board[i][j]);

            if(j == 8)
                printf(" |");
        }
        printf("\n");
        
        if(i != 0 && i != 9 && (i + 1) % 3 == 0){
            printf("   ===================================\n");
        }
    }
}


// check if no 0's are left
bool isFull(int board[N][N]){
    int i, j;
    bool isFull = true;
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            if(board[i][j] == 0){
                isFull = false;
            }
        }
    }
    return isFull;
}

void addGuess(int board[N][N], int start[N][N], int row, int column, int guess){
    // add guess to that location if allowed

    bool result;
    if(start[row][column] == 0){
        result = checkPuzzle(board, row, column, guess);
        if(result == true){
            board[row][column] = guess;
            return;
        }
        printf("Please try again\n");
    }
    else{
        printf("You cannot change this value\n");
        printf("Please try again\n");
    }
    return;
    }

bool checkPuzzle(int board[N][N], int rowToCheck, int columnToCheck, int guess){
    int horiz, vert, box;

    horiz = checkHorizontally(board, rowToCheck, 0, guess, 9);
    if(horiz == -1)
        printf("%d already exists in this row\n", guess);

    vert = checkVertically(board, columnToCheck, guess);
    if(vert == -1)
        printf("%d already exists in this column\n", guess);

    box = checkBox(board, rowToCheck, columnToCheck, guess);
    if(box == -1)
        printf("%d already exists in this square\n", guess);

    if(horiz == 1 && vert == 1 && box == 1){
        return true;
    }
    else{
        return false;
    }
}

int checkHorizontally(int board[][9], int startRow, int startCol, int value, int end){
    int i = startCol;

    while(board[startRow][i] != value && i < end){ //as long as value doesn't match numbers already in the board
        i++;
    }

    if(i == end){ //if while loop reached the end of the row
        return 1; //number given (value) doesn't exist in the row
    }
    else{
        return -1; //number already exists in the row yet
    }
}

int checkVertically(int board[][9], int col, int value){
    int i = 0;
    while(board[i][col] != value && i < 9){ //as long as value doesn't match numbers already in the board
    i++;
    }

    if(i == 9){ //if while loop reached the end of the column
        return 1; //number given (value) doesn't exist in the column
    }
    else{
        return -1; //number already exists in the column yet
    }
}

int checkBox(int board[][9], int row, int col, int value){
    int rowIndex, colIndex;

    if(row < 3){ //check box starting from row 0 to row 2
        rowIndex = 0;
        if(col < 3){ //check box starting from col 0 to col 2
            colIndex = 0;
        }
        else if(col >= 3 && col < 6){ //check box starting from col 3 to col 5
            colIndex = 3;
        }
        else{ //otherwise check from col 6 to col 8
            colIndex = 6;
        }
    }


    else if(row >= 3 && row < 6){ //check box starting from row 3 to row 5
        rowIndex = 3;
        if(col < 3){ //check box starting from col 0 to col 2
            colIndex = 0;
        }
        else if(col >= 3 && col < 6){ //check box starting from col 3 to col 5
            colIndex = 3;
        }
        else{ //otherwise check from col 6 to col 8
            colIndex = 6;
        }
    }


    else{ //otherwise check from row 6 to row 8
        rowIndex = 6;
        if(col < 3){ //check box starting from col 0 to col 2
            colIndex = 0;
        }
        else if(col >= 3 && col < 6){ //check box starting from col 3 to col 5
            colIndex = 3;
        }
        else{ //otherwise check from col 6 to col 8
            colIndex = 6;
        }
    }

    int r1 = checkHorizontally(board, rowIndex, colIndex, value, colIndex + 3);
    rowIndex++;
    int r2 = checkHorizontally(board, rowIndex, colIndex, value, colIndex + 3);

    rowIndex++;
    int r3 = checkHorizontally(board, rowIndex, colIndex, value, colIndex + 3);


    if(r1 == 1 && r2 == 1 && r3 == 1)
        return 1; //number doesn't occur twice in box
    else
        return -1;
}

void reset(int board[N][N], int start[N][N]){
    int i, j;
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
        board[i][j] = start[i][j];
        }
    }
}

void copyBoard(int board[N][N], int start[N][N]){
    int i, j;
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
        start[i][j] = board[i][j];
        }
    }
}

int getValueIn(int board[N][N], int row, int column){
    return board[row][column];
}

int main(int argc, char const *argv[])
{
    bool playAgain = true;
    while(playAgain){ // keep the user in the game

        int board[9][9];
        int start[9][9];
        

        printf("Welcome to Sudoku!");

        generateStartingBoard(board, start);
        copyBoard(board, start);
        Display(board);
        while(!isFull(board)){
            int guessRow, guessColumn, guess;
            printf("Enter desired row: ");
            scanf("%d", &guessRow);
            printf("Enter desired column: ");
            scanf("%d", &guessColumn);
            printf("Enter guess: ");
            scanf("%d", &guess);
            addGuess(board, start, guessRow, guessColumn, guess);
            Display(board);
        }   

        int choice;
        printf("Would you like to play a new game? Y = 1, N = 0\n");
        scanf("%d", &choice);
        while(choice > 1){
            printf("Invalid answer. Please enter Y or N\n");
            scanf("%d", &choice);
        }

        if(choice == 0){
            playAgain = false;
        }
        else{
            playAgain = true;
        }

    }
    
    return 0;

}
