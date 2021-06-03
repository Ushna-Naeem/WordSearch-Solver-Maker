//Updated: 3 June 2021
//Written by Ushna Naeem, 20L-1156
//Sloution to Assignment 5 ISE
//The functinality of each function is commented under the function
//Make sure to attach the correct file name with the code
//In case of any query contact l201156@lhr.nu.edu.pk

#include<iostream>
#include<string>
#include<fstream>
#include <ctime>
#include <windows.h>

HANDLE color=GetStdHandle(STD_OUTPUT_HANDLE); 

using namespace std;

int GetStringLenght(char* string){
	//This function returns the lenght of the string.
	int length = 0;
	for(int i = 0; string[i] != '\0'; i++)
		length++;
	return length;
}
char* GetStringFromBuffer(char* string){
	//Allocates memory on the heap for the character pointer. 
	int length = GetStringLenght(string);
	int count = 0;
	for(int i = 0; string[i]  != '\0'; i++)
		if(string[i] == ' '){
			count++;
			continue;
	}
	length -= count;
	char* NewString = 0;
	NewString = new char[length+1];
	int temp = 0;
	for(int i = 0; string[i]  != '\0'; i++){
		if(string[i] == ' ')
			continue;
		int x = int(string[i]);
		if(x > 96 && x < 123)
			string[i] = string[i] - 32;
		NewString[temp] = string[i];
		temp++;
	}
	NewString[temp] = '\0';
	return NewString;
}
char** MakeArray(int  Rows, int Cols){
	//Making Matrix to store alphapets from input.
	char** matrix = new char*[Rows];
	for(int i = 0; i < Rows; i++)
		matrix[i] = new char[Cols];
	return matrix;
}
void Input(ifstream& finput, char** matrix, int Rows, int Cols){
	//Getting the matrix from input file
	for(int i = 0; i < Rows; i++)
		for(int j = 0; j < Cols; j++)
			finput>>matrix[i][j];
}
void MatrixOutput(char** &Matrix,int Rows, int Cols){
	//This function outputs the Character matrix on txt File.
	bool CompletionCheck = false;
	string FileName;
	string SubString;
	int Check = 0;
	SetConsoleTextAttribute(color, 11);
	std::cout<<endl<<"~~ Enter the input file name: \nMake sure that it is in the following format (FileName.txt)\n";
	SetConsoleTextAttribute(color, 6);
	std::cout<<"~~ ";
	std::cin>>FileName;
	cout<<endl;
	if(Check==-1){
		SetConsoleTextAttribute(color, 4);
		std::cout << "Error making the file!\n"; 
	}
	else{
		ofstream OutputFile(FileName);
		for(int i = 0; i < Rows; i++){
			for(int z = 0; z < Cols; z++)
				OutputFile<<Matrix[i][z]<<"  ";
			OutputFile<<endl;
			CompletionCheck = true;
		}
		if(CompletionCheck == true){
			SetConsoleTextAttribute(color, 10);
			cout<<"Output file is made!\n";
		}
	}
}
bool WordCheckLeftToRight(char** matrix, int Index1, int Index2, int Rows, int Cols,char* word){
	//This functions searches for the word Left to Right in all rows of the matrix.
	//Returns true if word found. 
	int length = GetStringLenght(word);
	int check = Index2 + length-1;
	if(check > Rows)
		return false;
	for(int i = Index1, j = Index2, x = 0; x < length; j++, x++){
		if(j >= Cols)
			return false;
		if(matrix[i][j] != word[x])
			return false;
	}
	return true;	
}
bool WordCheckRightToLeft(char** matrix, int Index1, int Index2, int Rows, int Cols,char* word){
	//This functions searches for the word Right to Left in all rows of the matrix.
	//Returns true if word found. 
	int length = GetStringLenght(word);
	int check = Index2 - length+1;
	if(check < 0)
		return false;
	for(int i = Index1, j = Index2, x = 0; x < length ; j--, x++){
		if(j < 0)
			return false;
		if(matrix[i][j] != word[x])
			return false;
	}
	return true;
}
bool WordCheckTopToBottom(char** matrix, int Index1, int Index2, int Rows, int Cols,char* word){
	//This functions searches for the word Top to Bottom in all cols of the matrix.
	//Returns true if word found. 
	int length = GetStringLenght(word);
	int check = Index1 + length-1;
	if(check > Cols)
		return false;
	for(int i = Index1, j = Index2, x = 0; x < length; i++, x++){
		if(i >= Rows)
			return false;
		if(matrix[i][j] != word[x])
			return false;
	}
	return true;
}
bool WordCheckBottomToTop(char** matrix, int Index1, int Index2, int Rows, int Cols,char* word){
	//This functions searches for the word Bottom to Top in all cols of the matrix.
	//Returns true if word found. 
	int length = GetStringLenght(word);
	int check = Index1 - length+1;
	if(check < 0)
		return false;
	for(int i = Index1, j = Index2, x = 0; x < length; i--, x++){
		if(i < 0)
			return false;
		if  (matrix[i][j] != word[x])
			return false;
	}
	return true;
}
bool WordCheckTopLeftToBottomRight(char** matrix, int Index1, int Index2, int Rows, int Cols,char* word){
	//This functions searches for the word in all leading diagonals of the matrix.
	//Returns true if word found. 
	int length = GetStringLenght(word);
	int CheckA = Index1 + length-1;
	int CheckB = Index2 + length-1;
	if(CheckA > length || CheckB > length)
		return false;
	for(int i = Index1, j = Index2, x = 0; x < length; i++, j++, x++){
		if(i >= Rows || j >= Cols)
			return false;
		if(matrix[i][j] != word[x])
			return false;
	}
	return true;
}
bool WordCheckTopRightToBottomLeft(char** matrix, int Index1, int Index2, int Rows, int Cols,char* word){
	//This functions searches for the word in all antidiagonals of the matrix.
	//Returns true if word found. 
	int length = GetStringLenght(word);
	int CheckA = Index1 + length-1;
	int CheckB = Index2 - length+1;
	if(CheckA > length || CheckB < 0)
		return false;
	for(int i = Index1, j = Index2, x = 0; x < length; i++, j--, x++){
		if(i >= Rows || j < 0)	
			return false;
		if(matrix[i][j] != word[x])
			return false;
	}
	return true;	
}
bool WordCheckBottomLeftToTopRight(char** matrix, int Index1, int Index2, int Rows, int Cols,char* word){
	//This functions searches for the word in all reverse antidiagonals of the matrix.
	//Returns true if word found. 
	int length = GetStringLenght(word);
	int CheckA = Index1 - length+1;
	int CheckB = Index2 + length-1;
	if(CheckA < 0)
		return false;
	if(CheckA > length || CheckB < length)
		return false;
	for(int i = Index1, j = Index2, x = 0; x < length; i--, j++, x++){
		if(i < 0 || j >= Cols)
			return false;
		if(matrix[i][j] != word[x])

			return false;
	}
	return true;
}
bool WordCheckBottomRightToTopLeft(char** matrix, int Index1, int Index2, int Rows, int Cols,char* word){
	//This functions searches for the word in all reverse leading diagonals of the matrix.
	//Returns true if word found. 
	int length = GetStringLenght(word);
	int CheckA = Index1 - length+1;
	int CheckB = Index2 - length+1;
	if(CheckA < 0|| CheckB < 0)
		return false;
	if(CheckA > length || CheckB > length)
		return false;
	for(int i = Index1, j = Index2, x = 0; x < length; i--, j--, x++){
		if(i < 0 || j < 0)
			return false;
		if(matrix[i][j] != word[x])
			return false;
	}
	return true;
	
}
bool SearchForWord(ofstream& outputfile, char** matrix, char* word, int size, int Rows, int Cols){
	//Searches for the word in the matrix
	for(int i = 0; i < Rows; i++){
		for(int j = 0; j < Cols; j++){
			if(WordCheckLeftToRight(matrix, i, j, Rows, Cols, word)){
				int length = GetStringLenght(word);
				outputfile<<"{"<<i<<","<<j<<"} {"<<i<<","<<j+length-1<<"}"<<endl;
				cout<<"{"<<i<<","<<j<<"} {"<<i<<","<<j+length-1<<"}"<<endl;
				return true;
			}
			if(WordCheckRightToLeft(matrix, i, j, Rows, Cols, word)){
				int length = GetStringLenght(word);
				outputfile<<"{"<<i<<","<<j<<"} {"<<i<<","<<j-length+1<<"}"<<endl;
				cout<<"{"<<i<<","<<j<<"} {"<<i<<","<<j-length+1<<"}"<<endl;
				return true;
			}
			if(WordCheckTopToBottom(matrix, i, j, Rows, Cols, word)){
				int length = GetStringLenght(word);
				outputfile<<"{"<<i<<","<<j<<"} {"<<i+length-1<<","<<j<<"}"<<endl;
				cout<<"{"<<i<<","<<j<<"} {"<<i+length-1<<","<<j<<"}"<<endl;
				return true;
			}
			if(WordCheckBottomToTop(matrix, i, j, Rows, Cols, word)){
				int length = GetStringLenght(word);
				outputfile<<"{"<<i<<","<<j<<"} {"<<i-length+1<<","<<j<<"}"<<endl;
				cout<<"{"<<i<<","<<j<<"} {"<<i-length+1<<","<<j<<"}"<<endl;
				return true;
			}
			if(WordCheckTopLeftToBottomRight(matrix, i, j, Rows, Cols, word)){
				int length = GetStringLenght(word);
				outputfile<<"{"<<i<<","<<j<<"} {"<<i+length-1<<","<<j+length-1<<"}"<<endl;
				cout<<"{"<<i<<","<<j<<"} {"<<i+length-1<<","<<j+length-1<<"}"<<endl;
				return true;
			}
			if(WordCheckTopRightToBottomLeft(matrix, i, j, Rows, Cols, word)){
				int length = GetStringLenght(word);
				outputfile<<"{"<<i<<","<<j<<"} {"<<i+length-1<<","<<j-length+1<<"}"<<endl;
				cout<<"{"<<i<<","<<j<<"} {"<<i+length-1<<","<<j-length+1<<"}"<<endl;
				return true;
			}
			if(WordCheckBottomLeftToTopRight(matrix, i, j, Rows, Cols, word)){
				int length = GetStringLenght(word);
				outputfile<<"{"<<i<<","<<j<<"} {"<<i-length+1<<","<<j+length-1<<"}"<<endl;
				cout<<"{"<<i<<","<<j<<"} {"<<i-length+1<<","<<j+length-1<<"}"<<endl;
				return true;
			}
			if(WordCheckBottomRightToTopLeft(matrix, i, j, Rows, Cols, word)){
				int length = GetStringLenght(word);
				outputfile<<"{"<<i<<","<<j<<"} {"<<i-length+1<<","<<j-length+1<<"}"<<endl;
				cout<<"{"<<i<<","<<j<<"} {"<<i-length+1<<","<<j-length+1<<"}"<<endl;
				return true;
			}
			
		}
	}
	outputfile<<"Not Found"<<endl;
	return false;

}
bool LeftToRightPlacement(char** &Matrix, char* word, int indexA, int indexB, const int& MaxLen){
	//This functions checks if the word can be placed on the matrix  from left to right. 
	//It places the word on the position.
	int length = GetStringLenght(word);
	int check = MaxLen - indexB;
	if(check < length)	
		return false;    
	for(int z = indexB, k = 0; k < length; z++, k++){
		int y = int(word[k]);
		int x = int(Matrix[indexA][z]);
		if(y == x)
			continue;		
		if(x >= 65 && x <= 90)
			return false;	
	}
	for(int z = indexB, k = 0; k < length; z++, k++)
		Matrix[indexA][z] = word[k];	
	return true;
}
bool RightToLeftPlacement(char** &Matrix, char* word, int indexA, int indexB, const int& MaxLen){
	//This functions checks if the word can be placed on the matrix from right to left in reverse. 
	//It places the word on the position in reverse.
	int length = GetStringLenght(word);
	int check = MaxLen - indexB;
	if(check < length)
		return false;
	for(int z = indexB, k = length-1; k >= 0; z++, k--){
		int x = int(Matrix[indexA][z]);
		int y = int(word[k]);
		if(y == x)
			continue;
		if(x >= 65 && x <= 90)
			return false;
	}
	for(int z = indexB, k = length-1; k >= 0; z++, k--)
		Matrix[indexA][z] = word[k];
	return true;
}
bool TopToBottomPlacement(char** &Matrix, char* word, int indexA, int indexB, const int& MaxLen){
	//This functions checks if the word can be placed on the matrix from top to Bottom. 
	//It places the word on the position.
	int length =GetStringLenght(word);
	int check = MaxLen - indexA;
	if(check < length)
		return false;
	for(int i = indexA, k = 0; k < length; i++, k++){
		int y = int(word[k]);
		int x = int(Matrix[i][indexB]);
		if(y == x)
			continue;
		if(x >= 65 && x <= 90)
			return false;
	}
	for(int i = indexA, k = 0; k < length; i++, k++)
		Matrix[i][indexB] = word[k];
	return true;
}
bool BottomToTopPlacement(char** &Matrix, char* word, int indexA, int indexB, const int& MaxLen){
	//This functions checks if the word can be placed on the matrix from Bottom to Top. 
	//It places the word on the position.
	int length =GetStringLenght(word);
	int check = MaxLen - indexA;
	if(check < length)
		return false;
	for(int i = indexA, k = length-1; k >= 0; i++, k--){
		int y = int(word[k]);
		int x = int(Matrix[i][indexB]);
		if(y == x)
			continue;
		if(x >= 65 && x <= 90)
			return false;
	}
	for(int i = indexA, k = length-1; k >= 0; i++, k--)
		Matrix[i][indexB] = word[k];
	return true;
}
bool LeadingDiagonalPlacement(char** &Matrix, char* word, int indexA, int indexB, int MaxLen){
	//This functions checks if the word can be placed on the matrix in leading diagonal from top left to right bottom. 
	//It places the word on the position.
	int length =GetStringLenght(word);
	int Check1 = MaxLen - indexA; 
	int Check2 = MaxLen - indexB; 
	if(Check1 > MaxLen || Check2 > MaxLen)
		return false;
	if(Check1 < length || Check2 < length)
		return false;
	if(indexB >= length || indexA >= length) //this
		return false;
	for(int i = indexA, z = indexB, k = 0; k < length; i++, z++, k++){
		int y = int(word[k]);
		int x = int(Matrix[i][z]);
		if(y == x)
			continue;
		if(x >= 65 && x <= 90)
			return false;
	}
	for(int i = indexA, z = indexB, k = 0; k < length; i++, z++, k++)
		Matrix[i][z] = word[k];
	return true;
}
bool AntiDiagonalPlacement(char** &Matrix, char* word, int indexA, int indexB, const int& MaxLen){
	//This functions checks if the word can be placed on the matrix in antdiagonal from top right to left bottom. 
	//It places the word on the position.
	int length =GetStringLenght(word);
	int Check1 = MaxLen - indexA; 
	int Check2 = indexB - length; 
	if(indexA > MaxLen || indexB < 0)
		return false;
	if(Check1 < length || Check2 > length)
		return false;
	if(indexB < length-1 || indexA >= length) //this
		return false;
	for(int i = indexA, z = indexB, k = 0; k < length; i++, z--, k++){
		int y = int(word[k]);
		int x = int(Matrix[i][z]);
		if(y == x)
			continue;
		if(x >= 65 && x <= 90)
			return false;
	}
	for(int i = indexA, z = indexB, k = 0; k < length; i++, z--, k++)
		Matrix[i][z] = word[k];
	return true;
}
bool LeadingDiagonalReversePlacement(char** &Matrix, char* word, int indexA, int indexB, const int& MaxLen){
	//This functions checks if the word can be placed on the matrix in leading diagonal reverse from left bottom  to top right. 
	//It places the word on the position.
	int length =GetStringLenght(word);
	int Check1 = indexA - length; 
	int Check2 = MaxLen - indexB; 
	if(indexA < 0 || indexB > MaxLen)
		return false;
	if(Check2 < length || Check1 > length)
		return false;
	if(indexA < length-1 || indexB >= length) //this
		return false;
	for(int i = indexA, z = indexB, k = 0; k < length; i--, z++, k++){
		int y = int(word[k]);
		int x = int(Matrix[i][z]);
		if(y == x)
			continue;
		if(x >= 65 && x <= 90)
			return false;
	}
	for(int i = indexA, z = indexB, k = 0; k < length; i--, z++, k++)
		Matrix[i][z] = word[k];
	return true;
}
bool AntiDiagonalReversePlacement(char** &Matrix, char* word, int indexA, int indexB, const int& MaxLen){
	//This functions checks if the word can be placed on the matrix in antdiagonal reverse from left bottom to top right.
	//It places the word on the position.
	int length = GetStringLenght(word);
	int Check1 = indexA - length; 
	int Check2 = indexB - length; 
	if(indexA < 0 || indexB < 0)
		return false;
	if(Check2 > length || Check1 > length)
		return false;
	if(indexA < length-1 || indexB < length-1) //this
		return false;
	for(int i = indexA, z = indexB, k = 0; k < length; i--, z--, k++){
		int y = int(word[k]);
		int x = int(Matrix[i][z]);
		if(y == x)
			continue;
		if(x >= 65 && x <= 90)
			return false;
	}
	for(int i = indexA, z = indexB, k = 0; k < length; i--, z--, k++)
		Matrix[i][z] = word[k];
	return true;
}
bool SequenceGenerator(char** &Matrix, char* word, const int &Rows, const int& Cols,const int&MaxLen, int Pattren){  
	//It calls the the appropriate function to put the word on the matriz according to the random sequence generator.
	if(Pattren == 0){
		for(int i = 0; i < Rows; i++){
			for(int z = 0; z < Cols; z++){
				if(LeftToRightPlacement(Matrix, word, i, z, MaxLen))
					return true;
				else if(TopToBottomPlacement(Matrix, word, i, z, MaxLen))
					return true;
			}
		}
	}
	if(Pattren == 1){
		for(int i = 0; i < Rows; i++){
			for(int z = 0; z < Cols; z++){
				if(RightToLeftPlacement(Matrix, word, i, z, MaxLen))
					return true;
				else if(BottomToTopPlacement(Matrix, word, i, z, MaxLen))
					return true;
			}
		}
	}
	if(Pattren == 2){
		for(int i = 0; i < Rows; i++){
			for(int z = 0; z < Cols; z++){
				if(LeadingDiagonalPlacement(Matrix, word, i, z, MaxLen))
					return true;
				else if(AntiDiagonalPlacement(Matrix, word, i, z, MaxLen))
					return true;
			}
		}
	}
	if(Pattren == 3){
		for(int i = Rows-1; i >= 0; i--){
			for(int z = Cols-1; z >= 0; z--){
				if(AntiDiagonalReversePlacement(Matrix, word, i, z, MaxLen))
					return true;
				else if(LeadingDiagonalReversePlacement(Matrix, word, i, z, MaxLen))
					return true;
			}
		}	
	}
	if(Pattren == 4){
		for(int i = MaxLen-1; i >= 0; i--){
			for(int z = MaxLen-1; z >= 0; z--){
				if(LeadingDiagonalReversePlacement(Matrix, word, i, z, MaxLen))
					return true;
				else if(LeftToRightPlacement(Matrix, word, i, z, MaxLen))
					return true;
			}
		}	
	}
	if(Pattren == 5){
		for(int i = MaxLen-1; i >= 0; i--){
			for(int z = MaxLen-1; z >= 0; z--){
				if(AntiDiagonalPlacement(Matrix, word, i, z, MaxLen))
					return true;
				else if(BottomToTopPlacement(Matrix, word, i, z, MaxLen))
					return true;
			}
		}	
	}
	return false;
}
void FreeSpaceFill(char** &Matrix, const int &Rows, const int& Cols){  
	//This function puts random upper Case alphabets in empty spaces.
	char str = 'A';
	for(int i = 0; i < Rows; i++){
		for(int z = 0; z < Cols; z++){
			int y = int(Matrix[i][z]);
			if(y < 65 || y > 90){
				Matrix[i][z] = str;
				str++;
				if(i % 2 == 0)
					str = str + 2;
				if(z % 2 == 0)
					str = str + 7;
				int c = int(str);
				if(c > 90)
					str = str - 26;
			}
		}
	}
}
void ArrayDeallocation(char** array, const int Rows){
	//This function return the used memory back to heap.
	for(int i = 0; i < Rows; i++){
		delete[] array[i];
		array[i] = 0;
	}
	delete[] array;
	array = 0;
}
void main(){
	//Menu Interface with Color Handling 
	string Choice = "K"; 
	string SubString;
	int Check =0;
	char MenuKey; 
	SetConsoleTextAttribute(color, 6);
	std::cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^";
	SetConsoleTextAttribute(color, 10);
	std::cout<<endl<<endl<<"                Welcome to the WORD SEARCH!                "<<endl;
	while(Choice!="Q"){
		SetConsoleTextAttribute(color, 6);
		std::cout<<endl<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
		SetConsoleTextAttribute(color, 4);
		std::cout<<endl<<"                         Main Menue                     ";
		SetConsoleTextAttribute(color, 12);
		std::cout<<endl<<"      ~~ Kindly Select one of the following opitions ~~ ";
		SetConsoleTextAttribute(color, 13);
		std::cout<<endl<<endl<<"         << Press (C) to create a new word search >>";
		std::cout<<endl<<"        << Press (S) to search in an existing game >>";
		std::cout<<endl<<"              << Press (Q) to Quit the game >>"<<endl;
		SetConsoleTextAttribute(color, 6);
		std::cout<<endl<<"                 Your Selection: ";
		std::cin>>Choice;
		SetConsoleTextAttribute(color, 1);
		std::cout<<endl<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;

		if(Choice == "C"){
			//If user presses C
			//File Input from user
			string FileName;
			SetConsoleTextAttribute(color, 11);
			std::cout<<endl<<"~~ Enter the input file name: \nMake sure that it is in the following format (FileName.txt)\n";
			SetConsoleTextAttribute(color, 6);
			std::cout<<"~~ ";
			std::cin>>FileName;
			SubString = FileName.substr(FileName.length()-4,4);
			Check = SubString.find(".txt");
			//varaibles used in File handling and getting the data.
			char** words;
			int size = 0;	
			int  size1 = 0;
			char temp[100];	
			int index = 0;		
			int MaxLen = 0;		
			char array[20];
			//Calculating total Number of words from function
			ifstream fin(FileName);
			if (! fin.is_open() || Check == -1){
				SetConsoleTextAttribute(color, 4);
				std::cout << "Error opening file"; 
				SetConsoleTextAttribute(color, 2);
				std::cout<<endl<<"Press any key to return to the main menu\n";
				std::cin>>MenuKey;
			}
			else{
				cout<<endl;
				std::cout<<"Input file opened successfully! \n";
				//Getting total number of words from user
				SetConsoleTextAttribute(color, 11);
				std::cout<<endl<<"~~ Enter the total number of words: ";
				SetConsoleTextAttribute(color, 6);
				std::cin>>size;
				while(!fin.eof()){
					fin.getline(temp, 20);
					size1++;
				}
				fin.close();
				//Comparing the number of words 
				if(size1==size){
					words = new char*[size1];
					ifstream fin2(FileName);
						 while(!fin2.eof()){
						//Loop for data input
							fin2.getline(array, 20);					
							words[index] = GetStringFromBuffer(array);	
							int temp =GetStringLenght(words[index]);
							if(MaxLen < temp)		//Calculating lenght of losngest word in list
								MaxLen = temp;
							index++;
						}
						if(MaxLen < size)			
							MaxLen = size; //size of longest word and total numbers are compared to form form matrix with larger
						char* temp2;	
						//sorts the word list
						for(int i = 0; i < size-1; i++){
							for(int z = i+1; z < size; z++){
								int L1 =GetStringLenght(words[i]);					
								int L2 =GetStringLenght(words[z]);
								if(L2 > L1){
									temp2 = GetStringFromBuffer(words[i]);
									delete[] words[i];
									words[i] = GetStringFromBuffer(words[z]);
									delete[] words[z];
									words[z] = GetStringFromBuffer(temp2);
									delete[] temp2;
								}
							}
						}
						//Taking input of rows and cols from user
						int Rows, Cols;
						SetConsoleTextAttribute(color, 11);
						std::cout<<endl<<"~~ Enter the number of Rows: ";
						SetConsoleTextAttribute(color, 6);
						std::cin>>Rows;
						SetConsoleTextAttribute(color, 11);
						std::cout<<endl<<"~~ Enter the number of Cols: ";
						SetConsoleTextAttribute(color, 6);
						std::cin>>Cols;
						if(Rows>MaxLen || Cols>>MaxLen){ //compareing rows/clol with max lenght
							char** Matrix = MakeArray(Rows,Cols);	
							srand((unsigned)time(0));
							int Pattren;	//Stores randomised value that is used to generate sequence of word placement.
							for(int k = 0; k < size; ){
								Pattren = rand() % 6;
								if(SequenceGenerator(Matrix, words[k], Rows, Cols, MaxLen, Pattren))		
									k++;
								else
									Pattren = rand() % 6;
							}
							FreeSpaceFill(Matrix,Rows,Cols);
							MatrixOutput(Matrix, Rows,Cols);
							//Returning data back to memory
							ArrayDeallocation(Matrix, Rows);
							ArrayDeallocation(words, size);
							SetConsoleTextAttribute(color, 2);
							std::cout<<endl<<"Press any key to return to the main menu\n";
							std::cin>>MenuKey;
						}
						else {
							SetConsoleTextAttribute(color, 2);
							std::cout<<endl<<"Grid Cannot be made.";
							SetConsoleTextAttribute(color, 2);
							std::cout<<endl<<"Press any key to return to the main menu\n";
							std::cin>>MenuKey;
						}
					}
					else{
						SetConsoleTextAttribute(color, 2);
						std::cout<<endl<<"The input size doesn't match.\nPress any key to return to the main menu\n";
						std::cin>>MenuKey;
					}
				}

		}
		if(Choice == "S"){
			//If user presses C
			int Rows = 0;
			int Cols = 0;
			int TestCases;
			char temp[20];
			string FileName;
			SetConsoleTextAttribute(color, 11);
			std::cout<<endl<<"~~ Enter the input file name: \nMake sure that it is in the following format (FileName.txt)\n";
			SetConsoleTextAttribute(color, 6);
			std::cout<<"~~ ";
			std::cin>>FileName;
			//Input of file
			SubString = FileName.substr(FileName.length()-4,4);
			Check = SubString.find(".txt");
			ifstream inputfile(FileName);
			if (!inputfile.is_open() || Check ==-1){
				SetConsoleTextAttribute(color, 4);
				std::cout << "Error opening the file!\n"; 
			}
			else{
				//Searching the words
				SetConsoleTextAttribute(color, 10);
				std::cout<<endl<<"Input file opened successfully! \n\n";
				inputfile>>Rows>>Cols;
				inputfile>>TestCases;
				char** matrix = MakeArray(Rows, Cols);
				Input(inputfile, matrix, Rows, Cols);
				inputfile.close();
				char** Words = new char*[TestCases];
				for(int i = 0; i < TestCases; i++){
					inputfile.ignore();
					inputfile.getline(temp, 20);
					Words[i] = GetStringFromBuffer(temp);
				}
				//Filling the output file
				SetConsoleTextAttribute(color, 11);
				std::cout<<"~~ Enter the output file name:\nMake sure that it is in the following format FileName.txt.\n";
				SetConsoleTextAttribute(color, 6);
				std::cout<<"~~ ";
				std::cin>>FileName;
				SubString = FileName.substr(FileName.length()-4,4);
				Check = SubString.find(".txt");
				if(Check == -1){
					ofstream outputfile(FileName);
					SetConsoleTextAttribute(color, 1);
					std::cout<<endl<<"**** Results! ****\n";
					for(int x = 0; x < TestCases; x++){
						SetConsoleTextAttribute(color, 5);
						if(SearchForWord(outputfile, matrix, Words[x], TestCases, Rows, Cols))
							continue;
						else{
							SetConsoleTextAttribute(color, 12);
							std::cout<<"Not Found"<<endl;
						}
					}
				}
				else{
					SetConsoleTextAttribute(color, 4);
					std::cout << "Error making the file!\n"; 
				}
			 }
			SetConsoleTextAttribute(color, 2);
			std::cout<<endl<<"Press any key to return to the main menu\n";
			std::cin>>MenuKey;
		}
	}
	//If user quits
	SetConsoleTextAttribute(color, 6);
	std::cout<<endl<<"Good Bye! Have a Nice day :) \n\n";
	SetConsoleTextAttribute(color, 7);
	system("pause");
	return;
}
