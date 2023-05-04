#include "Matrix.h"

int Matrix::nAlloc = 0;
int Matrix::nFree = 0;

int Matrix::get_nAlloc() { return nAlloc; }

int Matrix::get_nFree() { return nFree; }

int Matrix::get_dy() { return dy; }

int Matrix::get_dx() { return dx; }

int **Matrix::get_array() { return array; }

// (cy, cx) 메모리 공간
void Matrix::alloc(int cy, int cx) { // 메모리 할당 후 초기화
  if ((cy < 0) || (cx < 0)) return;
  dy = cy;
  dx = cx;
  array = new int*[dy];
  for (int y = 0; y < dy; y++)
    array[y] = new int[dx];
  for (int y = 0; y < dy; y++)
    for (int x = 0; x < dx; x++)
      array[y][x] = 0;
  
  nAlloc++; // 할당개수 ++
}

Matrix::Matrix() { alloc(0, 0); }

// 행렬 소멸자
Matrix::~Matrix() {  // 행렬 삭제
  for (int y = 0; y < dy; y++)
    delete array[y];
  delete array;

  nFree++; // 삭제 개수 ++
}

// 
Matrix::Matrix(int cy, int cx) { // int로 받아 초기화
  alloc(cy, cx); // 공간할당
  for (int y = 0; y < dy; y++)
    for (int x = 0; x < dx; x++)
      array[y][x] = 0; // 초기화
}


Matrix::Matrix(const Matrix *obj) {// 인트 포인터로 받아 초기화
  alloc(obj->dy, obj->dx); 
  for (int y = 0; y < dy; y++)
    for (int x = 0; x < dx; x++)
      array[y][x] = obj->array[y][x];
}

Matrix::Matrix(const Matrix &obj) { // 참조변수로 받아 초기화
  alloc(obj.dy, obj.dx);
  for (int y = 0; y < dy; y++)
    for (int x = 0; x < dx; x++)
      array[y][x] = obj.array[y][x];
}

Matrix::Matrix(int *arr, int col, int row) {
  alloc(col, row);
  for (int y = 0; y < dy; y++)
    for (int x = 0; x < dx; x++)
      array[y][x] = arr[y * dx + x];
}

// 행렬 자르기
Matrix *Matrix::clip(int top, int left, int bottom, int right) {
  int cy = bottom - top;
  int cx = right - left;
  Matrix *temp = new Matrix(cy, cx);
  for (int y = 0; y < cy; y++) {
    for (int x = 0; x < cx; x++) {
      if ((top + y >= 0) && (left + x >= 0) &&
	  (top + y < dy) && (left + x < dx))
	temp->array[y][x] = array[top + y][left + x];
      else {
	cerr << "invalid matrix range";
	return NULL;
      }
    }
  }
  return temp;
}

// obj를 array에 붙여넣기
void Matrix::paste(const Matrix *obj, int top, int left) {
  for (int y = 0; y < obj->dy; y++)
    for (int x = 0; x < obj->dx; x++) {
      if ((top + y >= 0) && (left + x >= 0) &&
	  (top + y < dy) && (left + x < dx))
	array[y + top][x + left] = obj->array[y][x];
      else {
	cerr << "invalid matrix range";
	return NULL;
      }
    }
}

Matrix *Matrix::add(const Matrix *obj) { // array 행렬 + obj행렬
  if ((dx != obj->dx) || (dy != obj->dy)) return NULL;
  Matrix *temp = new Matrix(dy, dx);
  for (int y = 0; y < dy; y++)
    for (int x = 0; x < dx; x++)
      temp->array[y][x] = array[y][x] + obj->array[y][x];
  return temp;
}

const Matrix operator+(const Matrix& m1, const Matrix& m2){
  if ((m1.dx != m2.dx) || (m1.dy != m2.dy)) return Matrix();
  Matrix temp(m1.dy, m1.dx);
  for (int y = 0; y < m1.dy; y++)
    for (int x = 0; y < m1.dx; x++)
      temp.array[y][x] = m1.array[y][x] + m2.array[y][x];
  return temp;
}

int Matrix::sum() { // 행렬의 모든 요소의 합
  int total = 0;
  for (int y = 0; y < dy; y++)
    for (int x = 0; x < dx; x++)
      total += array[y][x];
  return total;
}

void Matrix::mulc(int coef) { // 행렬의 모든 요소의 곱
  for (int y = 0; y < dy; y++)
    for (int x = 0; x < dx; x++)
      array[y][x] = coef * array[y][x];
}

Matrix *Matrix::int2bool() {// 행렬을 2진수로 만들기 0이나 1로
  Matrix *temp = new Matrix(dy, dx);
  int **t_array = temp->get_array();
  for (int y = 0; y < dy; y++)
    for (int x = 0; x < dx; x++)
      t_array[y][x] = (array[y][x] != 0 ? 1 : 0);
  
  return temp;
}

bool Matrix::anyGreaterThan(int val) { //val값이 행렬의 어떠한 한 값보다 크면 true
  for (int y = 0; y < dy; y++) {
    for (int x = 0; x < dx; x++) {
      if (array[y][x] > val)
	return true;
    }
  }
  return false;
}

void Matrix::print() { // 행렬 프린트 하기
  cout << "Matrix(" << dy << "," << dx << ")" << endl;
  for (int y = 0; y < dy; y++) {
    for (int x = 0; x < dx; x++)
      cout << array[y][x] << " ";
    cout << endl;
  }
}


ostream& operator<<(ostream& out, const Matrix& obj){
  out << "Matrix(" << obj.dy << "," << obj.dx << ")" << endl;
  for(int y = 0; y < obj.dy; y++){
    for(int x = 0; x < obj.dx; x++)
      out << obj.array[y][x] << " ";
    out << endl;
  }
  out << endl;
  return out;
}

Matrix& Matrix::operator=(const Matrix& obj)
{
  if (this == &obj) return *this;
  if ((dx != obj.dx) || (dy != obj.dy))
    alloc(obj.dy, obj.dx);

  for (int y = 0; y < dy; y++)
    for (int x = 0; x < dx; x++)
      array[y][x] = obj.array[y][x];
  return *this;
}
