#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int ** DAC (int **A, int **B, int size)
{
	int **C;
	C = new int *[size];
	for(int i=0; i<size; i++){
		C[i] = new int[size];
	}
	
	if(size==1)
	{
		C[0][0] = A[0][0] * B[0][0];
	}
	
	else{
		//분할
		int **A11; 
		int **A12;
		int **A21;
		int **A22;
		A11 = new int *[size/2];
		A12 = new int *[size/2];
		A21 = new int *[size/2];
		A22 = new int *[size/2];
		int **B11; 
		int **B12;
		int **B21;
		int **B22;
		B11 = new int *[size/2];
		B12 = new int *[size/2];
		B21 = new int *[size/2];
		B22 = new int *[size/2];
				
		for(int i=0; i<size/2; i++){
			A11[i] = new int[size/2];
			A12[i] = new int[size/2];
			A21[i] = new int[size/2];
			A22[i] = new int[size/2];
			B11[i] = new int[size/2];
			B12[i] = new int[size/2];
			B21[i] = new int[size/2];
			B22[i] = new int[size/2];
		}		
		
		for(int i=0;i<size;i++){
			for(int j=0;j<size;j++){
				if(i<size/2 && j<size/2){
					A11[i][j] = A[i][j];
					B11[i][j] = B[i][j];
				}	
				else if(i<size/2 && j>=size/2){
					A12[i][j-(size/2)] = A[i][j];
					B12[i][j-(size/2)] = B[i][j];
				}
				else if(i>=size/2 && j<size/2){
					A21[i-(size/2)][j] = A[i][j];
					B21[i-(size/2)][j] = B[i][j];
				}
				else{
					A22[i-(size/2)][j-(size/2)] = A[i][j];
					B22[i-(size/2)][j-(size/2)] = B[i][j];
				}
			}
		}
		
		//이거도 for문으로 접근 
		int C11[size/2][size/2];
		int C12[size/2][size/2];
		int C21[size/2][size/2];
		int C22[size/2][size/2];
		
		int **temp1 = DAC(A11,B11,size/2);
		int **temp2 = DAC(A12,B21,size/2);
		int **temp3 = DAC(A11,B12,size/2);
		int **temp4 = DAC(A12,B22,size/2);
		int **temp5 = DAC(A21,B11,size/2);
		int **temp6 = DAC(A22,B21,size/2);
		int **temp7 = DAC(A21,B12,size/2);
		int **temp8 = DAC(A22,B22,size/2);	
		
		for(int i=0;i<size/2;i++){
			for(int j=0;j<size/2;j++){
				C11[i][j] = temp1[i][j] + temp2[i][j];
				C12[i][j] = temp3[i][j] + temp4[i][j];
				C21[i][j] = temp5[i][j] + temp6[i][j];
				C22[i][j] = temp7[i][j] + temp8[i][j];
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
				delete []temp1[i];
				delete []temp2[i];
				delete []temp3[i];
				delete []temp4[i];
				delete []temp5[i];
				delete []temp6[i];
				delete []temp7[i];
				delete []temp8[i];
		}
		delete []A11;
		delete []A12;
		delete []A21;
		delete []A22;
		delete []B11;
		delete []B12;
		delete []B21;
		delete []B22;
		delete []temp1;
		delete []temp2;
		delete []temp3;
		delete []temp4;
		delete []temp5;
		delete []temp6;
		delete []temp7;
		delete []temp8;
		
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
	} 
	
	return C;
	
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

	int **Result = DAC(A, B, total_size);
	
	ofstream writeFile("output.txt");
		
	for(int i=0;i<total_size;i++){
		for(int j=0;j<total_size;j++){
			if(j!=total_size-1)
				writeFile<<Result[i][j]<<" ";
			else
				writeFile<<Result[i][j];
		}
//		if(i!=total_size-1)
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