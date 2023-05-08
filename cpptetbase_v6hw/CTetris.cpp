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

  // write the rest of this function!!

  // setOfColorBlockObjects = setOfBlockObjects; // allocate 1d array of pointers to Matrix pointer arrays
  setOfColorBlockObjects = new Matrix**[numTypes]; // allocate 1d array of pointers to Matrix pointer arrays

  for (int t = 0; t < numTypes; t++)
    setOfColorBlockObjects[t] = new Matrix*[numDegrees]; // allocate 1d array of Matrix pointers
  for (int t = 0; t < numTypes; t++) {
    int *array = setOfColorBlockArrays[numDegrees * t];
    
    // int idx, size;
    // for (idx = 0; array[idx] != -1 ; idx++); // find the element of -1 in array[]
    // for (size = 0; size*size < idx; size++); // comupte the square root of idx
    for (int d = 0; d < numDegrees; d++) {
      Matrix *size_Object = setOfBlockObjects[t][d]; 
      int size = size_Object->get_dx();
      int *array2 = new int[size*size+1];
      int k;
      for (k = 0; k < size*size; k++){
        array2[k] = setOfColorBlockArrays[numDegrees * t + d][k];
      }
      array2[k] = -1;
      setOfColorBlockObjects[t][d] = new Matrix(array2, size, size);
      delete[] array2;
    }
  }
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

  return _state;
}
