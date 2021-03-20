#include <iostream>
#include <cstdlib>
#include <ctime>
#define WIDTH 9
#define HEIGHT 9
#define TOTAL_MINES 10
std::string player = "computer";
bool ENDGAME = false;

//==================================================

void usage()
{
    std::cout << "USAGE: \n ============How To Play Minesweeper v.1 !!! ============= \n";
    std::cout << "You have a board 9x9 with 10 mines. Each of turn, you can choose a cell.\n";
    std::cout << "If there is no mine, this cell will open, if there are mines around this cell. \n";
    std::cout << "it's stop. if not, continue to open adjacent cells.\n";
    std::cout << "========== Now --- How to play ========= \n You can press a number to choose latitude and longitude. \n Example : if you want to choose third cell you must press: \n Longitude : 0 Latitude : 2 \n And Good Luck \n";
}

// change player
void togglePlayer()
{
    if (player == "human")
    {
        player = "computer";
    }
    else
        player = "human";
}

// ouput data on screen
void displayBoard(int board[][WIDTH])
{
    for (int i = 0; i < WIDTH; ++i)
    {
        std::cout << "   " << i;
    }
    std::cout << std::endl;
    std::cout << "  -------------------------------------" << std::endl;
    for (int i = 0; i < HEIGHT; ++i)
    {
        std::cout << i;
        for (int j = 0; j < WIDTH; ++j)
        {
            if (board[i][j] == 32 || board[i][j] == 77)
            {
                std::cout << " | " << (char)board[i][j];
            }
            else
            {
                std::cout << " | " << board[i][j];
            }
        }
        std::cout << " |" << std::endl;
        std::cout << "  -------------------------------------" << std::endl;
    }
    return;
}

// check position
bool isCorrectPos(int x, int y)
{
    if (x < 0 || x > WIDTH - 1 || x > HEIGHT - 1 || y < 0 || y > WIDTH - 1 || y > HEIGHT - 1)
    {
        return false;
    }
    return true;
}

// check mines
bool isMine(char x)
{
    if (x != 'M')
    {
        return false;
    }
    return true;
}

//==========================================================

//function for computer sweeps
void minesSweeperC(int playBoard[][WIDTH], int minesBoard[][WIDTH], int computerBoard[][WIDTH], int x, int y)
{
    int countMines = 0;
    int x1, y1;

    //=================================
    //check for mines around cell
    //above of cell

    for (x1 = x - 1, y1 = y - 1; y1 < (y + 2); ++y1)
    {
        if (isCorrectPos(x1, y1))
        {
            if (isMine(minesBoard[x1][y1]))
            {
                ++countMines;
            }
        }
    }

    //under of cell

    for (x1 = x + 1, y1 = y - 1; y1 < (y + 2); ++y1)
    {
        if (isCorrectPos(x1, y1))
        {
            if (isMine(minesBoard[x1][y1]))
            {
                ++countMines;
            }
        }
    }

    //check left cell

    if (isCorrectPos(x, y - 1))
    {
        if (isMine(minesBoard[x][y - 1]))
        {
            ++countMines;
        }
    }

    // check right cell

    if (isCorrectPos(x, y + 1))
    {
        if (isMine(minesBoard[x][y + 1]))
        {
            ++countMines;
        }
    }

    ///================================================
    // If there are no mines around, backtracking to check the other cell
    // if so, stop.

    if (countMines == 0)
    {
        //check top of the cell

        for (x1 = x - 1, y1 = y - 1; y1 < (y + 2); ++y1)
        {
            if (isCorrectPos(x1, y1))
            {
                if (playBoard[x1][y1] == 32)
                {
                    playBoard[x1][y1] = 0;
                    minesSweeperC(playBoard, minesBoard, computerBoard, x1, y1);
                }
            }
        }

        //check below the cell

        for (x1 = x + 1, y1 = y - 1; y1 < (y + 2); ++y1)
        {
            if (isCorrectPos(x1, y1))
            {
                if (playBoard[x1][y1] == 32)
                {
                    playBoard[x1][y1] = 0;
                    minesSweeperC(playBoard, minesBoard, computerBoard, x1, y1);
                }
            }
        }

        //check left cell

        if (isCorrectPos(x, y - 1))
        {
            if (playBoard[x][y - 1] == 32)
            {
                playBoard[x][y - 1] = 0;
                minesSweeperC(playBoard, minesBoard, computerBoard, x, y - 1);
            }
        }

        // check right cell

        if (isCorrectPos(x, y + 1))
        {
            if (playBoard[x][y + 1] == 32)
            {
                playBoard[x][y + 1] = 0;
                minesSweeperC(playBoard, minesBoard, computerBoard, x, y + 1);
            }
        }
    }
    playBoard[x][y] = countMines;
    computerBoard[x][y] = 2;
}

//function for player sweeps
void minesSweeperH(int playBoard[][WIDTH], int minesBoard[][WIDTH], int computerBoard[][WIDTH], int x, int y, int &totalScore)
{
    ++totalScore;
    int countMines = 0;
    int x1, y1;

    //=================================
    //check for mines around cell
    //above of cell

    for (x1 = x - 1, y1 = y - 1; y1 < (y + 2); ++y1)
    {
        if (isCorrectPos(x1, y1))
        {
            if (isMine(minesBoard[x1][y1]))
            {
                ++countMines;
            }
        }
    }

    //under of cell

    for (x1 = x + 1, y1 = y - 1; y1 < (y + 2); ++y1)
    {
        if (isCorrectPos(x1, y1))
        {
            if (isMine(minesBoard[x1][y1]))
            {
                ++countMines;
            }
        }
    }

    //check left cell

    if (isCorrectPos(x, y - 1))
    {
        if (isMine(minesBoard[x][y - 1]))
        {
            ++countMines;
        }
    }

    // check right cell

    if (isCorrectPos(x, y + 1))
    {
        if (isMine(minesBoard[x][y + 1]))
        {
            ++countMines;
        }
    }

    ///================================================
    // If there are no mines around, backtracking to check the other cell
    // if so, stop.

    if (countMines == 0)
    {
        //check top of the cell

        for (x1 = x - 1, y1 = y - 1; y1 < (y + 2); ++y1)
        {
            if (isCorrectPos(x1, y1))
            {
                if (playBoard[x1][y1] == 32)
                {
                    playBoard[x1][y1] = 0;
                    minesSweeperH(playBoard, minesBoard, computerBoard, x1, y1, totalScore);
                }
            }
        }

        //check below the cell

        for (x1 = x + 1, y1 = y - 1; y1 < (y + 2); ++y1)
        {
            if (isCorrectPos(x1, y1))
            {
                if (playBoard[x1][y1] == 32)
                {
                    playBoard[x1][y1] = 0;
                    minesSweeperH(playBoard, minesBoard, computerBoard, x1, y1, totalScore);
                }
            }
        }

        //check left cell

        if (isCorrectPos(x, y - 1))
        {
            if (playBoard[x][y - 1] == 32)
            {
                playBoard[x][y - 1] = 0;
                minesSweeperH(playBoard, minesBoard, computerBoard, x, y - 1, totalScore);
            }
        }

        // check right cell

        if (isCorrectPos(x, y + 1))
        {
            if (playBoard[x][y + 1] == 32)
            {
                playBoard[x][y + 1] = 0;
                minesSweeperH(playBoard, minesBoard, computerBoard, x, y + 1, totalScore);
            }
        }
    }
    playBoard[x][y] = countMines;
    computerBoard[x][y] = 1;
}

//function for computer to check the best coordinates
void tempMinesSweeper(int playBoard[][WIDTH], int minesBoard[][WIDTH], int computerBoard[][WIDTH], int x, int y, int &res)
{
    ++res;
    int countMines = 0;
    int x1, y1;

    //=================================
    //check for mines around cell
    //above of cell

    for (x1 = x - 1, y1 = y - 1; y1 < (y + 2); ++y1)
    {
        if (isCorrectPos(x1, y1))
        {
            if (isMine(minesBoard[x1][y1]))
            {
                ++countMines;
            }
        }
    }

    //under of cell

    for (x1 = x + 1, y1 = y - 1; y1 < (y + 2); ++y1)
    {
        if (isCorrectPos(x1, y1))
        {
            if (isMine(minesBoard[x1][y1]))
            {
                ++countMines;
            }
        }
    }

    //check left cell

    if (isCorrectPos(x, y - 1))
    {
        if (isMine(minesBoard[x][y - 1]))
        {
            ++countMines;
        }
    }

    // check right cell

    if (isCorrectPos(x, y + 1))
    {
        if (isMine(minesBoard[x][y + 1]))
        {
            ++countMines;
        }
    }

    ///================================================
    // If there are no mines around, backtracking to check the other cell
    // if so, stop.

    if (countMines == 0)
    {
        //check top of the cell

        for (x1 = x - 1, y1 = y - 1; y1 < (y + 2); ++y1)
        {
            if (isCorrectPos(x1, y1))
            {
                if (computerBoard[x1][y1] == 0)
                {
                    computerBoard[x1][y1] = 3;
                    tempMinesSweeper(playBoard, minesBoard, computerBoard, x1, y1, res);
                }
            }
        }

        //check below the cell

        for (x1 = x + 1, y1 = y - 1; y1 < (y + 2); ++y1)
        {
            if (isCorrectPos(x1, y1))
            {
                if (computerBoard[x1][y1] == 0)
                {
                    computerBoard[x1][y1] = 3;
                    tempMinesSweeper(playBoard, minesBoard, computerBoard, x1, y1, res);
                }
            }
        }

        //check left cell

        if (isCorrectPos(x, y - 1))
        {
            if (computerBoard[x][y - 1] == 0)
            {
                computerBoard[x][y - 1] = 3;
                tempMinesSweeper(playBoard, minesBoard, computerBoard, x, y - 1, res);
            }
        }

        // check right cell

        if (isCorrectPos(x, y + 1))
        {
            if (computerBoard[x][y + 1] == 0)
            {
                computerBoard[x][y + 1] = 3;
                tempMinesSweeper(playBoard, minesBoard, computerBoard, x, y + 1, res);
            }
        }
    }
}

//============================================================

// reset temp board of computer
void resetCBoard(int board[][WIDTH])
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (board[i][j] == 3)
            {
                board[i][j] = 0;
            }
        }
    }
    return;
}

//function for computer plays
void turnOfComputer(int playBoard[][WIDTH], int minesBoard[][WIDTH], int computerBoard[][WIDTH], int &totalScore)
{
    int res = 0;
    int x, y, total = 0;
    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            if (computerBoard[i][j] == 0)
            {
                tempMinesSweeper(playBoard, minesBoard, computerBoard, i, j, res);
                if (total <= res)
                {
                    total = res;
                    x = i;
                    y = j;
                }
                res = 0;
            }
        }
    }
    if (total == 1)
    {
        totalScore += total;
    }
    else
        totalScore += total - 1;

    playBoard[x][y] = 0;
    computerBoard[x][y] = 2;
    std::cout << "Computer just chose : \nLongitude : " << x << "\nLatitude : " << y << std::endl;
    resetCBoard(computerBoard);
    minesSweeperC(playBoard, minesBoard, computerBoard, x, y);
    return;
}

// if game ended
bool endGame(int board[][WIDTH])
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (board[i][j] == 0)
            {
                return false;
            }
        }
    }
    return true;
}

//Play game
void playGameWithComputer(int playBoard[][WIDTH], int minesBoard[][WIDTH], int computerBoard[][WIDTH], int &totalScoreOfComputer, int &totalScoreOfHuman)
{
    if (endGame(computerBoard))
    {
        std::cout << "Game Over !!!!!!!!!!!!" << std::endl;
        if (totalScoreOfComputer > totalScoreOfHuman)
        {
            std::cout << "Computer Has Won !!!!!!!!!!!" << std::endl;
        }
        else
        {
            std::cout << "You Have Won !!!!!!!!!!!" << std::endl;
        }

        std::cout << "You got :" << totalScoreOfHuman << " Score !!!! " << std::endl;
        std::cout << "Computer got : " << totalScoreOfComputer << " Score !!!!" << std::endl;
        ENDGAME = true;
        return;
    }

    if (player == "computer")
    {
        int currentScore = totalScoreOfComputer;
        std::cout << "=======================================\nTurn of " << player << std::endl;
        turnOfComputer(playBoard, minesBoard, computerBoard, totalScoreOfComputer);
        std::cout << "          Minesweeper v.1" << std::endl;
        displayBoard(playBoard);

        std::cout << "=======================================\nComputer just got : " << totalScoreOfComputer - currentScore << "\nComputer's total score: " << totalScoreOfComputer << std::endl;
        return;
    }
    else
    {
        std::cout << "=======================================\nTurn of you :" << std::endl;
        int x, y;
        std::cout << "Choose the cell you want to play: " << std::endl;
        std::cout << "Longitude X: ";
        std::cin >> x;
        std::cout << "\nLatitude Y: ";
        std::cin >> y;
        if (isMine(minesBoard[x][y]))
        {
            system("cls");
            std::cout << "You just chose Longitude : " << x << " Latitude : " << y << "\nYou lost!!!!" << std::endl;
            std::cout << "          Minesweeper v.1" << std::endl;
            displayBoard(minesBoard);
            ENDGAME = true;
            return;
        }
        else
        {
            int currentScore = totalScoreOfHuman;
            playBoard[x][y] = 0;
            minesSweeperH(playBoard, minesBoard, computerBoard, x, y, totalScoreOfHuman);
            system("cls");
            std::cout << "          Minesweeper v.1" << std::endl;
            displayBoard(playBoard);
            std::cout << "=======================================\nYou just got : " << totalScoreOfHuman - currentScore << "\nYour total score: " << totalScoreOfHuman << std::endl;
            return;
        }
    }
    return;
}
//========================

//initial board
void initialBoard(int playBoard[][WIDTH], int minesBoard[][WIDTH], int computerBoard[][WIDTH])
{
    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            playBoard[i][j] = 32;
            minesBoard[i][j] = 32;
            computerBoard[i][j] = 0;
        }
    }
    return;
}

// place random mines
void placeMines(int board[][WIDTH], int cBoard[][WIDTH])
{
    srand((unsigned)time(0));
    int x, x1;
    int y, y1, countMines = 0;
    int totalMines = 0;
    do
    {
        do
        {
            x = rand() % WIDTH;
            y = rand() % HEIGHT;
        } while (board[x][y] != 32);

        for (x1 = x - 1, y1 = y - 1; y1 < (y + 2); ++y1)
        {
            if (isCorrectPos(x1, y1))
            {
                if (isMine(board[x1][y1]))
                {
                    ++countMines;
                }
            }
        }

        //under of cell

        for (x1 = x + 1, y1 = y - 1; y1 < (y + 2); ++y1)
        {
            if (isCorrectPos(x1, y1))
            {
                if (isMine(board[x1][y1]))
                {
                    ++countMines;
                }
            }
        }

        //check left cell

        if (isCorrectPos(x, y - 1))
        {
            if (isMine(board[x][y - 1]))
            {
                ++countMines;
            }
        }

        // check right cell

        if (isCorrectPos(x, y + 1))
        {
            if (isMine(board[x][y + 1]))
            {
                ++countMines;
            }
        }
        if (countMines < 4)
        {
            board[x][y] = 'M';
            cBoard[x][y] = 'M';
            ++totalMines;
        }
        countMines = 0;
    } while (totalMines < TOTAL_MINES);
    return;
}

//function for player sweeps
void minesSweeper(int playBoard[][WIDTH], int minesBoard[][WIDTH], int x, int y)
{
    int countMines = 0;
    int x1, y1;

    //=================================
    //check for mines around cell
    //above of cell

    for (x1 = x - 1, y1 = y - 1; y1 < (y + 2); ++y1)
    {
        if (isCorrectPos(x1, y1))
        {
            if (isMine(minesBoard[x1][y1]))
            {
                ++countMines;
            }
        }
    }

    //under of cell

    for (x1 = x + 1, y1 = y - 1; y1 < (y + 2); ++y1)
    {
        if (isCorrectPos(x1, y1))
        {
            if (isMine(minesBoard[x1][y1]))
            {
                ++countMines;
            }
        }
    }

    //check left cell

    if (isCorrectPos(x, y - 1))
    {
        if (isMine(minesBoard[x][y - 1]))
        {
            ++countMines;
        }
    }

    // check right cell

    if (isCorrectPos(x, y + 1))
    {
        if (isMine(minesBoard[x][y + 1]))
        {
            ++countMines;
        }
    }

    ///================================================
    // If there are no mines around, backtracking to check the other cell
    // if so, stop.

    if (countMines == 0)
    {
        //check top of the cell

        for (x1 = x - 1, y1 = y - 1; y1 < (y + 2); ++y1)
        {
            if (isCorrectPos(x1, y1))
            {
                if (playBoard[x1][y1] == 32)
                {
                    playBoard[x1][y1] = 0;
                    minesSweeper(playBoard, minesBoard, x1, y1);
                }
            }
        }

        //check below the cell

        for (x1 = x + 1, y1 = y - 1; y1 < (y + 2); ++y1)
        {
            if (isCorrectPos(x1, y1))
            {
                if (playBoard[x1][y1] == 32)
                {
                    playBoard[x1][y1] = 0;
                    minesSweeper(playBoard, minesBoard, x1, y1);
                }
            }
        }

        //check left cell

        if (isCorrectPos(x, y - 1))
        {
            if (playBoard[x][y - 1] == 32)
            {
                playBoard[x][y - 1] = 0;
                minesSweeper(playBoard, minesBoard, x, y - 1);
            }
        }

        // check right cell

        if (isCorrectPos(x, y + 1))
        {
            if (playBoard[x][y + 1] == 32)
            {
                playBoard[x][y + 1] = 0;
                minesSweeper(playBoard, minesBoard, x, y + 1);
            }
        }
    }
    playBoard[x][y] = countMines;
}

//check if player wins
bool Win(int pBoard[][WIDTH], int mBoard[][WIDTH])
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            if (pBoard[i][j] == 32 && mBoard[i][j] != 77)
            {
                return false;
            }
        }
    }
    return true;
}

//function for player plays
void playGame(int playBoard[][WIDTH], int minesBoard[][WIDTH])
{
    int x, y;
    std::cout << "Choose the cell you want to play: " << std::endl;
    std::cout << "Longitude X: ";
    std::cin >> x;
    std::cout << "\nLatitude Y: ";
    std::cin >> y;
    if (isMine(minesBoard[x][y]))
    {
        system("cls");
        std::cout << "You just chose Longitude : " << x << " Latitude : " << y << "\nYou lost!!!!" << std::endl;
        std::cout << "          Minesweeper v.1" << std::endl;
        displayBoard(minesBoard);
        ENDGAME = true;
        return;
    }
    else
    {
        playBoard[x][y] = 0;
        minesSweeper(playBoard, minesBoard, x, y);
        system("cls");
        std::cout << "          Minesweeper v.1" << std::endl;
        displayBoard(playBoard);
        if (Win(playBoard, minesBoard))
        {
            std::cout << "Congratulation !!!!! You won !!!!!!!" << std::endl;
            ENDGAME = true;
            return;
        }
    }
    return;
}

int main()
{
    int playBoard[HEIGHT][WIDTH];
    int minesBoard[HEIGHT][WIDTH];
    int computerBoard[HEIGHT][WIDTH];
    int totalScoreOfComputer = 0;
    int totalScoreOfHuman = 0;

    initialBoard(playBoard, minesBoard, computerBoard);
    placeMines(minesBoard, computerBoard);
    //displayBoard(minesBoard);
    usage();
    displayBoard(playBoard);

    char start;
    std::cout << "Start now ---> (Y/N) : " << std::endl;
    std::cin >> start;
    if (start == 'y' || start == 'Y')
    {
        int choose;
        std::cout << "1. Minesweeper!!! " << std::endl;
        std::cout << "2. Minesweeper With Computer !!! [You Can Win If You Are A Luckiest Person !!! Goodluck] " << std::endl;
        std::cin >> choose;
        if (choose == 1)
        {
            while (!ENDGAME)
            {
                playGame(playBoard, minesBoard);
            }
        }
        else
        {
            std::cout << "You want to play first (Y/N) ? " << std::endl;
            char playFirst;
            std::cin >> playFirst;
            if (playFirst == 'y' || playFirst == 'Y')
            {
                player = "human";
            }
            while (!ENDGAME)
            {
                playGameWithComputer(playBoard, minesBoard, computerBoard, totalScoreOfComputer, totalScoreOfHuman);
                togglePlayer();
            }
        }
    }
    else
    {
        exit(0);
    }

    system("pause");
    return 0;
}