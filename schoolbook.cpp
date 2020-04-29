#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int size = 0;

int** schoolBook(int **A, int **B, int size)
{
	int **Result;
	Result = new int *[size];
	for(int i=0; i<size; i++){
		Result[i] = new int[size]();
	}
		
	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
			Result[i][j]=0;
			for(int k=0; k<size; k++)
			{
				Result[i][j] = Result[i][j] + A[i][k]*B[k][j];
			}
		}
	}
	return Result;
}

int main()
{
	string line;
	int num;
	ifstream readFile;
	readFile.open("input.txt");
	if(readFile.is_open())
	{
		while((readFile.peek()!='\n' && readFile>>num)){	
			size++;
		}		
		readFile.clear();
		readFile.seekg(0);	
	}	

	int **A;
	int **B;
	A = new int *[size];
	B = new int *[size];
	for(int i=0; i<size; i++){
		A[i] = new int[size]();
		B[i] = new int[size]();
	}	
		
	if(readFile.is_open())
	{
		for(int i=0; i<size; i++){
			for(int j=0; j<size; j++){
				readFile>>A[i][j];
			}
		}
		
		for(int i=0; i<size; i++){
			for(int j=0; j<size; j++){
				readFile>>B[i][j];
			}
		}
	}
	readFile.close();

	int **Result = schoolBook(A, B, size);
	
	ofstream writeFile("output.txt");
		
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(j!=size-1)
				writeFile<<Result[i][j]<<" ";
			else
				writeFile<<Result[i][j];
		}
			writeFile<<endl;
	}
	writeFile.close();
	
	for(int i=0; i<size; i++){
		delete[] A[i];
		delete[] B[i];
		delete[] Result[i];
	}
	delete []A;
	delete []B;
	delete []Result;	
	
	
	return 0;
}