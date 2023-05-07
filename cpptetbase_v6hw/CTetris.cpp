#include "CTetris.h"

using namespace std;

///**************************************************************
/// static member variables and functions
///**************************************************************

Matrix *** CTetris::setOfColorBlockObjects = NULL;

void CTetris::init(int **setOfColorBlockArrays, int nTypes, int nDegrees) {
  if (setOfColorBlockObjects != NULL) // already allocated?
    deinit();

  Tetris::init(setOfColorBlockArrays, nTypes, nDegrees); // call superclass' function

  numTypes = nTypes;
  numDegrees = nDegrees;

  setOfBlockObjects = new Matrix**[numTypes]; // allocate 1d array of pointers to Matrix pointer arrays

  for (int t = 0; t < numTypes; t++)
    setOfBlockObjects[t] = new Matrix*[numDegrees]; // allocate 1d array of Matrix pointers

  for (int t = 0; t < numTypes; t++) { // 타입 기준 for 문
    int *array = setOfColorBlockArrays[numDegrees * t]; // 어레이에서 타입 뽑기
    int idx, size;
    for (idx = 0; array[idx] != -1 ; idx++); // find the element of -1 in array[] // idx 크기 조절
    for (size = 0; size*size < idx; size++); // comupte the square root of idx // size 사이즈 측정
    wallDepth = (size > wallDepth ? size : wallDepth); // ?? 모르겠다
    for (int d = 0; d < numDegrees; d++) { // allocate matrix objects // 회전 블록 기준
      int *array2 = new int[size*size+1]; // 블록 메모리 생성
      int k; 
      for (k = 0; k < size*size; k++) // 블록 생성, 0이 아닌 다른 수 1로 통일
        array2[k] = setOfColorBlockArrays[numDegrees * t + d][k];
      array2[k] = -1;
      setOfBlockObjects[t][d] = new Matrix(array2, size, size);
      delete[] array2;
      // cout << *setOfBlockObjects[t][d] << endl;
    }
  }
  // write the rest of this function!!
}

void CTetris::deinit(void) {
  Tetris::deinit(); // call superclass' function

  for (int t = 0; t < numTypes; t++)
    for (int d = 0; d < numDegrees; d++)
      delete setOfColorBlockObjects[t][d]; // deallocate matrix objects

  for (int t = 0; t < numTypes; t++)
    delete [] setOfColorBlockObjects[t]; // deallocate 1d array of Matrix pointers

  delete []  setOfColorBlockObjects; // deallocate 1d array of pointers to Matrix pointer arrays

  setOfColorBlockObjects = NULL;
}

///**************************************************************
/// dynamic member variables and functions
///**************************************************************

/// constructors and destructor

CTetris::CTetris(int cy, int cx) : Tetris(cy, cx) {
  iCScreen = new Matrix(iScreen);
  oCScreen = new Matrix(oScreen);
  currCBlk = NULL;
}

CTetris::~CTetris() {
  delete iCScreen;
  delete oCScreen;
}



// mutators
TetrisState CTetris::accept(char key) {

  TetrisState _state = Tetris::accept(key); // call superclass' function

  // write the rest of this function!!

  // you can use the following code if you want to
  // oCScreen = deleteFullLines(oCScreen, currCBlk, top, wallDepth);

  return _state;
}
