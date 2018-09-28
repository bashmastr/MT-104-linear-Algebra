#include<iostream>
#include<fstream>
using namespace std;

bool is_reducedEche_form(int **matrix, int row, int col) {

	// if bottom-left matrix element is non zero [5,0,6]
		if (matrix[row-1][0] != 0 && row-1 > 0)
			return false;
		//check right down element
		if(matrix[row-1][col-2] == 1 && matrix[row-1][col-1] != 0)
			matrix[row-1][col-1] = 0;
	
	//1. if zero rows above the non-zero rows  
		int rowSum = 0 ,checkZerosRow = 0;

		for (int i = row-1; i >= 0; i--){
			for(int j = 0 ; j < col; j++){
				rowSum =  rowSum + matrix[i][j];
			}

			if (rowSum == 0 && checkZerosRow == 1)
				return false;

			if (rowSum != 0)
				checkZerosRow = 1;

			rowSum = 0;
		}

	//2.check non zero element right to the proceding row
		for(int i = 0; i < row; i++){
			for(int j = 0; j < col; j++){

				if(matrix[i][j] != 0){
					if(matrix[i][j] != 1)
						return false;

					for(int y = i-1; y >= 0; y--){
						
						if( matrix[y][j] != 0 )
							return false;
					}
			
					for(int z = i+1; z < row; z++){

						if(matrix[z][j] != 0)
							return false;

					}
					for(int k = 0; k < j ; k++){
				
						if(i != row-1 && matrix[i+1][k] != 0)
							return false;
						
					}

					if(i != row-1)
						i += 1;
				}
			}
		}

	return true;
}

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

		if (is_reducedEche_form(matrix, row, col)) // your desired function to which you passes 2d array(matrix)
			out << 1<<endl;
		else out << 0 << endl;

		free_memory(matrix, row); // to free the memory allocated

	}
	return 0;

}