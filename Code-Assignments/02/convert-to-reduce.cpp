#include "fraction_class.h"
///use fraction class for fraction e.g remain 4/5
#include <iostream>
#include <fstream>
using namespace std;


class reduce_echelon{
private:
  fraction **matrix;
  int row , col;
public:

//////allocate the memory for matrix////
  void allocate_memory(int r, int c){
    row = r;
    col = c;
    matrix = new fraction*[row];
    for(int i = 0; i < row; i++)
      matrix[i] = new fraction[col];
  }

/////deallcate the memory////// destructor
  ~reduce_echelon(){
    for(int i = 0; i < row;i++)
      delete[] matrix[i];
    delete[] matrix;
  }

///////swap the rows in matrix////////
  void swap(int oneRow, int secRow){
    fraction var;
    for(int j = 0; j < col; j++){
      var = matrix[oneRow][j];
      matrix[oneRow][j] = matrix[secRow][j];
      matrix[secRow][j] = var;
    }
  }

/////////BY user/////////
  // void add_values(){
  //   cout<<"Enter number row\n";
  //   cin>>row;
  //   cout<<"Enter number col\n";
  //   cin>>col;
  //   alloca_memory(row,col);
  //   for(int i = 0; i < row; i++){
  //     for (int j = 0; j < col; j++){
  //       cin>>matrix[i][j];
  //     }
  //   }
  // }

  void get(int **m1,int r,int c){
  	
  	allocate_memory(r,c);
    for(int i = 0; i < row; i++){
      for (int j = 0; j < col; j++){
        matrix[i][j].nume = m1[i][j];
      }
    }
  }
////////print on console//////
  void show(){
    for(int i = 0; i < row; i++){
      for(int j = 0; j < col; j++){
        double var = (double)matrix[i][j].nume/matrix[i][j].demo;
        cout<<var<<" ";
      }
      cout<<endl;
    }
  }
  // void save_to_file(){
  // 	ofstream out("out.txt");
  // 	out << row
  // 	for(int i = 0; i < row; i++){
  // 		for(int j = 0; j < col; j++){
  // 			double var = (double)matrix[i][j].nume/matrix[i][j].demo;
  // 			out<<var;
  // 		}
  // 	}
  // }

//convert a matrix into recduce echelon form
  void simplify(){
    int j = 0,i = 0;
    for(; i < row;){
      for(; j < col;){

      //if first pivot element is zero  e.g m = {{0,3},{4,5}} m[0][0] == 0 true
        if(matrix[i][j].nume == 0){

          /*check if all elements in the same colom is zero,e.g m = {{0,9},{0,5}}
          m[0][0] ==0 && [1][0] == 0
          now incerment the j by 1 and continue to check all condition again*/
          int check = 0;
          for(int k = i ; k < row; k++){
            if(matrix[k][j].nume != 0){
              check = 1;
              break;
            }
          }
          if(check == 0){
            j += 1;
            continue;
          }

          /*if procceding same colom are now zero the swap the rows
          e.g m = {{0,4},{4,5}} swap m = {{4,5},{0,4}}*/
          for(int k = i ; k < row; k++){
            if(matrix[k][j].nume != 0){
              swap(i,k);
              break;
            }
          }
        }

        /*if pivot element not 1 then divide the whole row by first element
        row to whole row e.g m = {2,4} divide by 2 m = {1,2}*/
        if(matrix[i][j].nume != 1){
          fraction div = matrix[i][j];
          for(int k = j; k < col ; k++){
            matrix[i][k] /= div;
          }
        }
        /* now to make all colom elements zero by row operation
        by subtract the scalar multiply of pivot row,below to pivot element*/
        for(int k = i+1; k < row; k++){
          if(matrix[k][j].nume != 0){
            fraction f = matrix[k][j];
            for(int z = j; z < col; z++){
              matrix[k][z] =  (f*matrix[i][z]) - matrix[k][z];
            }
          }
        }
        //make zeros to above to the pivot elements
        for(int k = i - 1; k > -1; k--){
          if(matrix[k][j].nume != 0){
            fraction f = matrix[k][j];
            for(int z = j; z < col; z++){
              matrix[k][z] = matrix[k][z] - (f*matrix[i][z]) ;
            }
          }
        }

        j += 1;
        break;
      }
      i += 1;
    }
  }

};


//Don't touch this function
void alloca_memory(int **matrix, int row, int col) {
	for (int i = 0; i < row; i++)
		matrix[i] = new int[col];
}

//Don't touch this function
void free_memory(int **matrix, int row) {
	for (int i = 0; i > row; i++)
		delete[] matrix[i];
	delete[] matrix;
}

int main() {

	int row = 0, col = 0, tmatrix = 0;
	int **matrix = 0;
	ifstream in("in.txt");
	ofstream out("out.txt"); // will automatically created if not present

	if (!in.is_open()) {
		cout << "Error in opening file" << endl;
		return 0;
	}

	in >> tmatrix;

	for (int i = 0; i < tmatrix; i++) {
		in >> row >> col;
		matrix = new int*[row];
		alloca_memory(matrix, row, col);

		for (int k = 0; k < row; k++) 
			for (int j = 0; j < col; j++)
				in >> matrix[k][j];

		
		reduce_echelon m;
		m.get(matrix,row,col);
    	m.simplify();
    	//m.save_to_file();
    	m.show();
    	cout<<endl;

		free_memory(matrix, row); // to free the memory allocated

	}
	return 0;

}

// int main(){

//   reduce_echelon m;
//   m.add_values();
//   m.simplify();
//   m.show();

//   return 0;
// }
