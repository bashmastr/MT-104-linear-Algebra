#include <iostream>
#include "fraction_class.h"
#include <fstream>
  void swap(fraction **matrix, int oneRow, int secRow,int row,int col){
    fraction var;
    for(int j = 0; j < col; j++){
      var = matrix[oneRow][j];
      matrix[oneRow][j] = matrix[secRow][j];
      matrix[secRow][j] = var;
    }
  }

 void simplify(fraction **matrix,int row,int col){
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
              swap(matrix,i,k,row,col);
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
/////////////check matrix linear independence//////////
  bool check_linear_independence(fraction **matrix , int row ,int col){
    if (col == 1){
      for(int i = 0 ; i < row ; i++){
        if(matrix[i][col-1].nume != 0){
          cout<<"independent\n";
          return true;
        }
      }
    }
    if(col == 1){
      cout<<"dependent\n";
      return false;
    }
    if( col > row){
      cout<<"dependent\n";
      return false;
    }
    simplify(matrix , row , col);

    for(int i = 0; i < row; i++){
      if(matrix[i][i].nume == 0){
        cout<<"dependent\n";
        return false;
      }
    }
    cout<<"independent\n";
    return 0;
  }

  // void show(fraction **matrix , int row, int col){
  //   for(int i = 0; i < row; i++){
  //     for(int j = 0; j < col; j++){
  //       double var = (double)matrix[i][j].nume/matrix[i][j].demo;
  //       cout<<var<<" ";
  //     }
  //     cout<<endl;
  //   }
  // }



void alloca_memory(fraction **matrix, int row, int col) {
	for (int i = 0; i < row; i++)
		matrix[i] = new fraction[col];
}

//Don't touch this function
void free_memory(fraction **matrix, int row) {
	for (int i = 0; i > row; i++)
		delete[] matrix[i];
	delete[] matrix;
}

int main() {

	int row = 0, col = 0, tmatrix = 0;
	fraction **matrix = 0;
	ifstream in("in.txt");
	ofstream out("out.txt"); // will automatically created if not present

	if (!in.is_open()) {
		cout << "Error in opening file" << endl;
		return 0;
	}

	in >> tmatrix;

	for (int i = 0; i < tmatrix; i++) {
		in >> row >> col;
		matrix = new fraction*[row];
		alloca_memory(matrix, row, col);

		for (int k = 0; k < row; k++) 
			for (int j = 0; j < col; j++)
				in >> matrix[k][j].nume;

		
		check_linear_independence(matrix , row , col);
		//get(matrix,row,col);
    	//simplify(matrix,row,col);
    	//show(matrix,row,col);
    	out<<row<<endl<<col<<endl;
		for (int k = 0; k < row; k++){
			for (int j = 0; j < col; j++){
				 double var = (double)matrix[k][j].nume/matrix[k][j].demo;
				 out<<var<<" ";
			}
			out<<endl;
		}


		free_memory(matrix, row); // to free the memory allocated

	}
	return 0;

}

