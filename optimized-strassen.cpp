#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int** MATADD (int **A, int **B, int size)
{
	int **S;
	S = new int *[size];
	for(int i=0; i<size; i++){
		S[i] = new int[size]();
	}
	
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			S[i][j] = A[i][j] + B[i][j];
		}
	}
	
	return S;	
}

int** MATSUB (int **A, int **B, int size)
{
	int **S;
	S = new int *[size];
	for(int i=0; i<size; i++){
		S[i] = new int[size]();
	}
	
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			S[i][j] = A[i][j] - B[i][j];
		}
	}
	
	return S;	
}

int** QUARTER (int **A, int row, int column, int size)
{
	int **temp;
	temp = new int*[size];
	for(int i=0; i<size; i++){
		temp[i] = new int[size]();
	}
	
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			temp[i][j] = A[row+i][column+j];
		}
	}
	return temp;
}

int** STRASSEN (int **A, int **B, int size)
{
	if(size<=32)
	{
		int **C;
		C = new int *[size];
		for(int i=0; i<size; i++){
			C[i] = new int[size]();
		}

		int a;
		for(int k=0; k<size; k++)
		{
			for(int i=0; i<size; i++)
			{
				a = A[i][k];
				for(int j=0; j<size; j++)
				{
					C[i][j] += a*B[k][j];
				}
			}
		}  
		return C;		
	}
	
	
	else{
		int **C;
		C = new int *[size];
		for(int i=0; i<size; i++){
			C[i] = new int[size]();
		}		
		//분할
		int **A11 = QUARTER (A,0,0,size/2); 
		int **A12 = QUARTER (A,0,size/2,size/2);
		int **A21 = QUARTER (A,size/2,0,size/2);
		int **A22 = QUARTER (A,size/2,size/2,size/2);
		int **B11 = QUARTER (B,0,0,size/2); 
		int **B12 = QUARTER (B,0,size/2,size/2);
		int **B21 = QUARTER (B,size/2,0,size/2);
		int **B22 = QUARTER (B,size/2,size/2,size/2);

		
		//이거도 for문으로 접근 
		int C11[size/2][size/2];
		int C12[size/2][size/2];
		int C21[size/2][size/2];
		int C22[size/2][size/2];
		
		int **S1 = MATSUB(B12,B22,size/2);
		int **S2 = MATADD(A11,A12,size/2);
		int **S3 = MATADD(A21,A22,size/2);
		int **S4 = MATSUB(B21,B11,size/2);
		int **S5 = MATADD(A11,A22,size/2);
		int **S6 = MATADD(B11,B22,size/2);
		int **S7 = MATSUB(A12,A22,size/2);
		int **S8 = MATADD(B21,B22,size/2);
		int **S9 = MATSUB(A11,A21,size/2);
		int **S10 = MATADD(B11,B12,size/2);	
		
		int **P1 = STRASSEN(A11, S1, size/2);
		int **P2 = STRASSEN(S2, B22, size/2);
		int **P3 = STRASSEN(S3, B11, size/2);
		int **P4 = STRASSEN(A22, S4, size/2);
		int **P5 = STRASSEN(S5, S6, size/2);
		int **P6 = STRASSEN(S7, S8, size/2);
		int **P7 = STRASSEN(S9, S10, size/2);
		
		for(int i=0;i<size/2;i++){
			for(int j=0;j<size/2;j++){
				C11[i][j] = P5[i][j] + P4[i][j] -P2[i][j] + P6[i][j];
				C12[i][j] = P1[i][j] + P2[i][j];
				C21[i][j] = P3[i][j] + P4[i][j];
				C22[i][j] = P5[i][j] + P1[i][j] -P3[i][j] - P7[i][j];
			}
		}			
		
		
		for(int i=0;i<size/2;i++){
				delete []A11[i];
				delete []A12[i];
				delete []A21[i];
				delete []A22[i];
				delete []B11[i];
				delete []B12[i];
				delete []B21[i];
				delete []B22[i];
				delete []S1[i];
				delete []S2[i];
				delete []S3[i];
				delete []S4[i];
				delete []S5[i];
				delete []S6[i];
				delete []S7[i];
				delete []S8[i];
				delete []S9[i];
				delete []S10[i];
				delete []P1[i];
				delete []P2[i];
				delete []P3[i];
				delete []P4[i];
				delete []P5[i];
				delete []P6[i];
				delete []P7[i];
		}
		delete []A11;
		delete []A12;
		delete []A21;
		delete []A22;
		delete []B11;
		delete []B12;
		delete []B21;
		delete []B22;
		delete []S1;
		delete []S2;
		delete []S3;
		delete []S4;
		delete []S5;
		delete []S6;
		delete []S7;
		delete []S8;
		delete []S9;
		delete []S10;
		delete []P1;
		delete []P2;
		delete []P3;
		delete []P4;
		delete []P5;
		delete []P6;
		delete []P7;
		
		//Combine
		for(int i=0;i<size;i++){
			for(int j=0;j<size;j++){
				if(i<size/2 && j<size/2)
					C[i][j] = C11[i][j];
				else if(i<size/2 && j>=size/2)
					C[i][j] = C12[i][j-(size/2)];
				else if(i>=size/2 && j<size/2)
					C[i][j] = C21[i-(size/2)][j];
				else
					C[i][j] = C22[i-(size/2)][j-(size/2)];
			}
		}
		return C;
	} 
		
}

int main()
{
	int total_size = 0;
	int num;
	ifstream readFile;
	readFile.open("input.txt");
	if(readFile.is_open())
	{
		while((readFile.peek()!='\n')&&readFile>>num){	
			total_size++;
		}		
		readFile.clear();
		readFile.seekg(0);	
	}	

	int **A;
	int **B;
	A = new int *[total_size];
	B = new int *[total_size];
	for(int i=0; i<total_size; i++){
		A[i] = new int[total_size]();
		B[i] = new int[total_size]();		
	}
	
	if(readFile.is_open())
	{
		for(int i=0; i<total_size; i++){
			for(int j=0; j<total_size; j++){
				readFile>>A[i][j];
			}
		}
		
		for(int i=0; i<total_size; i++){
			for(int j=0; j<total_size; j++){
				readFile>>B[i][j];
			}
		}
	}

	int **Result = STRASSEN(A, B, total_size);
	
	ofstream writeFile("output.txt");
		
	for(int i=0;i<total_size;i++){
		for(int j=0;j<total_size;j++){
			if(j!=total_size-1)
				writeFile<<Result[i][j]<<" ";
			else
				writeFile<<Result[i][j];
		}
			writeFile<<endl;
	}
	writeFile.close();
	
	for(int i=0; i<total_size; i++){
		delete[] A[i];
		delete[] B[i];
		delete[] Result[i];
	}
	delete []A;
	delete []B;
	delete []Result;
	
	return 0;
}