#include <iostream>

#define ROW 4  // rows are fixed to 4

using namespace std;

int getDifficultyFromUser(void);  // easy-medium-hard
int getColumnSize(int gameDeficultyLevel);
void setValuesToInitialBallPositionsArray(int* array, int gameDeficultyLevel);
void setArrayValuesToZero(int** array, int columnSize);  // set all 2d array  elements to zero
void PrintArrayValuesToConsole(int** array, int columnSize);  // print 2d array elements to terminal
void setInitialBallPositions(int** array, int colSize,int* initialBallPositions);  // set initial ball position after game started
int FirstselectedColNumber(int** array, int columnSize);  // take the ball from the pipeLine(column)
int getFirstNoneZeroValueRowNum(int** array,int colNumber);  // we need to take the ball from the pipeLine top
int secondSelectedColNumber(int** array, int firstselectedNumber, int columnSize,int firstSelectedColumn);  // drop the ball to pipeLine(column)
int getLastZeroValueRowNum(int** array,int colNumber);  // we need to drop the ball to the pipeLine bottom
void swapValueInArray(int** array, int firstNumRow, int firstNumCol,int secondNumRow,int secondNumCol);  // 2 value swap in 2d array
bool getWinningStatus(int** array, int colSize);
bool canGameContineAfterFirstSelection(int** array, int colSize,int firstselectedRowNumber,int firstselectedColNumber);

int main() {
  int gameDeficultyLevel;
  int columnSize;
  int firstSelectedColNum;   // ball take column position
  int firstSelectedRowNum;   // ball take row position
  int secondSelectedColNum;  // ball drop column position
  int secondSelectedRowNum;  // ball drop row position

  cout << "\n-------------------------WELCOME TO BALL SORT PUZZLE GAME!-------------------------\n"<< endl;

  gameDeficultyLevel = getDifficultyFromUser();
  columnSize = getColumnSize(gameDeficultyLevel);

  int** ballPipeLine = new int*[columnSize];  // rows are fixed to 4
  for (int i = 0; i < ROW; i++) {
    ballPipeLine[i] =new int[columnSize];  // easy column-5, medium column-7, hard column-9
  }

  // in the start we need to fill the pipelines(column) with 2 empty
  // pipeline(column)
  int* initialBallPositions = new int[ROW * (columnSize - 2)];
  setValuesToInitialBallPositionsArray(initialBallPositions,gameDeficultyLevel);

  setArrayValuesToZero(ballPipeLine, columnSize);
  setInitialBallPositions(ballPipeLine, (columnSize - 2), initialBallPositions);

  while (true) {
    PrintArrayValuesToConsole(ballPipeLine, columnSize);

    firstSelectedColNum = FirstselectedColNumber(ballPipeLine, columnSize);
    firstSelectedRowNum =getFirstNoneZeroValueRowNum(ballPipeLine, firstSelectedColNum);

    // check game can contine after first selection
    if (!canGameContineAfterFirstSelection(ballPipeLine, columnSize,firstSelectedRowNum,firstSelectedColNum)) {
      // deallocate 2d array
      for (int i = 0; i < ROW; i++) {
        delete[] ballPipeLine[i];
      }
      delete[] ballPipeLine;
      delete[] initialBallPositions;
      cout << "\nYou Lost!" << endl;
      break;
    }

    secondSelectedColNum = secondSelectedColNumber(ballPipeLine,ballPipeLine[firstSelectedRowNum - 1][firstSelectedColNum - 1],columnSize, firstSelectedColNum);
    secondSelectedRowNum =getLastZeroValueRowNum(ballPipeLine, secondSelectedColNum);

    swapValueInArray(ballPipeLine, firstSelectedRowNum, firstSelectedColNum,secondSelectedRowNum, secondSelectedColNum);

    // check winning status
    if (getWinningStatus(ballPipeLine, columnSize)) {
      PrintArrayValuesToConsole(ballPipeLine, columnSize);
      // deallocate 2d array
      for (int i = 0; i < ROW; i++) {
        delete[] ballPipeLine[i];
      }
      delete[] ballPipeLine;
      delete[] initialBallPositions;
      cout << "\nCongratulations! Level Completed!!" << endl;
      break;
    }
  }
}


// three main level (easy-medium-hard )
int getDifficultyFromUser(void) {
  int choice;
  cout << "======================================" << endl;
  cout << "|   Press 1 For Easy Mode            |" << endl;
  cout << "|   Press 2 For Medium Mode          |" << endl;
  cout << "|   Press 3 For Hard Mode            |" << endl;
  cout << "======================================" << endl;
  while (true) {
    cout << "\nChoose your difficulty level: ";
    cin >> choice;
    if (choice > 0 && choice <= 3) return choice;
    cout << "(Please Enter Valid Input)" << endl;
  }
}
int getColumnSize(int gameDeficultyLevel) {
  if (gameDeficultyLevel == 1)
    return 5;
  else if (gameDeficultyLevel == 2)
    return 7;
  else if (gameDeficultyLevel == 3)
    return 9;
  else
    return -1;
}
void setValuesToInitialBallPositionsArray(int* array, int gameDeficultyLevel) {
  int initialBallPositionsEasy[] = {1, 2, 1, 2, 2, 1, 1, 3, 3, 3, 3, 2};
  int initialBallPositionMedium[] = {2, 3, 3, 4, 5, 5, 1, 3, 1, 2,
                                     4, 2, 4, 1, 3, 1, 2, 4, 5, 5};
  int initialBallPositionHard[] = {3, 5, 4, 4, 6, 4, 7, 7, 6, 1, 1, 2, 4, 7,
                                   3, 5, 6, 3, 6, 7, 1, 2, 5, 2, 3, 5, 2, 1};

  if (gameDeficultyLevel == 1) {
    for (int i = 0; i < 12; i++) {
      array[i] = initialBallPositionsEasy[i];
    }
  }
  if (gameDeficultyLevel == 2) {
    for (int i = 0; i < 20; i++) {
      array[i] = initialBallPositionMedium[i];
    }
  }
  if (gameDeficultyLevel == 3) {
    for (int i = 0; i < 28; i++) {
      array[i] = initialBallPositionHard[i];
    }
  }
}
// set all 2d array  elements to zero
void setArrayValuesToZero(int** array, int columnSize) {
  for (int i = 0; i < ROW; i++) {
    for (int j = 0; j < columnSize; j++) {
      array[i][j] = 0;
    }
  }
}
// print 2d array elements to terminal
void PrintArrayValuesToConsole(int** array, int columnSize) {
cout << endl;
  for (int i = 0; i < columnSize; i++) {
    cout << "----";
  }
  cout << endl;

  for (int i = 0; i < columnSize; i++) {
    cout << " " << i + 1 << "  ";
  }

  cout << endl;
  for (int i = 0; i < columnSize; i++) {
    cout << "----";
  }
  cout << endl ;

  for (int i = 0; i < ROW; i++) {
    for (int j = 0; j < columnSize; j++) {
      //map number with letter
      char name;
      if(array[i][j]==1)
        name='Y';
      if(array[i][j]==2)
        name='B';
      if(array[i][j]==3)
        name='R';
      if(array[i][j]==4)
        name='G';
      if(array[i][j]==5)
        name='P';
      if(array[i][j]==6)
        name='W';
      if(array[i][j]==7)
        name='L';
      if(array[i][j]==0)
        name='?';

      cout << "(" << name << ") ";
    }
    cout << endl << endl;
  }
}
// set initial ball position after game started
void setInitialBallPositions(int** array, int colSize,
                             int* initialBallPositions) {
  // yellow 1
  // blue 2
  // red 3
  // green 4
  // pink 5
  // white 6
  // Lime 7
  int count = 0;
  for (int i = 0; i < ROW; i++) {
    for (int j = 0; j < colSize; j++) {
      array[i][j] = initialBallPositions[count];
      count++;
    }
  }
}
// take the ball from the pipeLine(column)
int FirstselectedColNumber(int** array, int columnSize) {
  int selectedCol;
  bool canSelectCol;
  while (true) {
    cout << endl << "Select the column to take a ball: ";
    cin >> selectedCol;
    // case: check column range
    if (selectedCol > 0 && selectedCol <= columnSize) {
      // case: check column has at least one none zero value
      for (int i = 0; i < ROW; i++) {
        if (array[i][selectedCol - 1] != 0) canSelectCol = true;
      }
      if (canSelectCol) return selectedCol;
    }

    cout << endl << "(Enter Valid Column Number)" << endl;
  }
}
// drop the ball to pipeLine(column)
int secondSelectedColNumber(int** array, int firstselectedNumber,
                            int columnSize, int firstSelectedColumn) {
  int selectedCol;
  while (true) {
    bool isAllColumnValueZero = true;
    bool isAllColumnValueNoneZero = true;
    cout << endl << "Select a column to move the ball: ";
    cin >> selectedCol;
    // case: check column range
    if (selectedCol > 0 && selectedCol <= columnSize &&
        selectedCol != firstSelectedColumn) {
      // case: check is all column value ==0
      for (int i = 0; i < ROW; i++) {
        if (array[i][selectedCol - 1] != 0) isAllColumnValueZero = false;
      }
      // case: all column value zero
      if (isAllColumnValueZero) return selectedCol;
      // case: check is all column has none zero value
      for (int i = 0; i < ROW; i++) {
        if (array[i][selectedCol - 1] == 0) isAllColumnValueNoneZero = false;
      }
      // case: all column has not (zero or none zero value)
      if (!isAllColumnValueZero && !isAllColumnValueNoneZero) {
        for (int i = 0; i < ROW; i++) {
          /* case: check is space available in the pipe and first  none zero
          value
          == firstselectedNumber  (Game Rule)*/
          if (array[i][selectedCol - 1] != 0 &&
              array[i][selectedCol - 1] == firstselectedNumber) {
            return selectedCol;
          }
        }
      }
    }

    cout << endl << "(Enter Valid Column Number)" << endl;
  }
}
// we need to take the ball from the pipeLine top
int getFirstNoneZeroValueRowNum(int** array, int colNumber) {
  for (int i = 0; i < ROW; i++) {
    if (array[i][colNumber - 1] != 0) return i + 1;
  }
  // if any error occurred in other funtions
  return -1;
}
// we need to drop the ball to the pipeLine bottom
int getLastZeroValueRowNum(int** array, int colNumber) {
  for (int i = 0; i < ROW; i++) {
    if (array[i][colNumber - 1] != 0) return i;
  }
  // case: all column value == zero
  return ROW;
}
// 2 value swap in 2d array
void swapValueInArray(int** array, int firstNumRow, int firstNumCol,
                      int secondNumRow, int secondNumCol) {
  int temp1 = array[firstNumRow - 1][firstNumCol - 1];
  int temp2 = array[secondNumRow - 1][secondNumCol - 1];
  array[firstNumRow - 1][firstNumCol - 1] = temp2;
  array[secondNumRow - 1][secondNumCol - 1] = temp1;
}
bool getWinningStatus(int** array, int colSize) {
  for (int i = 0; i < colSize; i++) {
    int columnFirstValue = array[0][i];
    for (int j = 0; j < ROW; j++) {
      if (columnFirstValue != array[j][i]) return false;
    }
  }
  return true;
}
bool canGameContineAfterFirstSelection(int** array, int colSize,
                                       int firstselectedRowNumber,
                                       int firstselectedColNumber) {
  int value = array[firstselectedRowNumber - 1][firstselectedColNumber - 1];
  int count = 0;
  // find there is any full empty column available
  for (int i = 0; i < colSize; i++) {
    for (int j = 0; j < ROW; j++) {
      if (array[j][i] != 0) {
        break;
      } else {
        count++;
      }
      if (count == ROW) return true;
    }
    count = 0;
  }
  // case: space available accouding to game rule
  for (int i = 0; i < colSize; i++) {
    // ignore selected column
    if (i == firstselectedColNumber - 1) continue;
    for (int j = 0; j < ROW; j++) {
      if (array[j][i] != value && array[j][i] != 0) break;
      if (array[j][i] == 0) continue;
      if (array[j][i] == value && j == 0) break;
      if (array[j][i] == value && j != 0) return true;
    }
  }
  // no space available accouding to game rules
  return false;
}
