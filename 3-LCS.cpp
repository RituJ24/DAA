#include<iostream>
#include<iomanip>
#include<stdio.h>
#include <sstream> 
#include<vector>
#include<string>

using namespace std;

class StringNode{
	
	private:
		int rank;
		bool hasDiagonal;
		StringNode* previous;
		string characters;
		char direction;
		
	public:
		StringNode(){
			this->rank= 0;
			this->hasDiagonal = false;
			this->previous = NULL;
			this->characters = "INI";
			this->direction = 'N'; 
		}
		
		void setRank(int rank){
			this->rank = rank;
		}
		
		int getRank(){
			return rank;
		}
		
		void setHasDiagonal(bool hasDiagonal){
			this->hasDiagonal = hasDiagonal;
		}
		
		bool getHasDiagonal(){
			return hasDiagonal;
		}
		
		void setPrevious(StringNode* previous){
			this->previous = previous;
		}
		
		StringNode* getPrevious(){
			return this->previous;
		}
		
		void setCharacters(string characters){
			this->characters = characters;
		}
		
		string getCharacters(){
			return this->characters;
		}
		
		void setDirection(char direction){
			this->direction = direction;
		}
		
		char getDirection(){
			return this->direction;
		}
};

typedef vector<vector<StringNode*> > LCSMATRIX;

class LCS{
	
	private:
		LCSMATRIX lcsM;
		string str1;
		string str2;
		string dispStr;
		int sizeStr1;
		int sizeStr2;
		int rank;
		StringNode* newStrNode = NULL;
		StringNode* previous = NULL;
		StringNode* left = NULL;
		StringNode* above = NULL;
	
	public:
		LCS(string str1, string str2){
			if (str1.size() > str2.size()) {
        		swap(str1, str2); 
    		}
			this->str1 = str1;
			this->str2 = str2;
			this->sizeStr1 = str1.size();
			this->sizeStr2 = str2.size();
			lcsM.resize(sizeStr1 + 1, vector<StringNode*>(sizeStr2 + 1));
		}
		
		string intTostr(int num) {
        	stringstream ss;
        	ss << num;
        	return ss.str();
    	}
		
	
		void buildLCSMatrix(){
			
			lcsM[0][0] = new StringNode();
				
			//str1 is considered in rows
			for(int i = 1; i < sizeStr1 + 1; i++){
				lcsM[i][0] = new StringNode();
			}
			
			//str2 is considered in columns
			for(int i = 1; i < sizeStr2 + 1; i++){
				lcsM[0][i] = new StringNode();
			}
			
			 
			for (int i = 1; i < sizeStr1 + 1; i++){
				for (int j = 1; j < sizeStr2 + 1; j++){
					string str = "";
					newStrNode = new StringNode();
					if (str1[i-1] == str2[j-1]){
						newStrNode->setHasDiagonal(true);
						newStrNode->setDirection('D');
						previous = lcsM[i-1][j-1];
						newStrNode->setRank(previous->getRank() + 1); 
						newStrNode->setPrevious(previous);
						str += str1[i-1];
						newStrNode->setCharacters(str);
					} else {
						left = lcsM[i][j-1];
						above = lcsM[i-1][j];
						str += str1[i-1];
						str += str2[j-1];
						if (left->getRank() > above->getRank()){
							newStrNode->setRank(left->getRank());
							newStrNode->setPrevious(left);
							newStrNode->setDirection('L');
						}
						else if (left->getRank() < above->getRank()){
							newStrNode->setRank(above->getRank());
							newStrNode->setPrevious(above);
							newStrNode->setDirection('A');
						}
						else {
							newStrNode->setRank(left->getRank());
							newStrNode->setPrevious(left);
							newStrNode->setDirection('B');
						}
						newStrNode->setCharacters(str);
					}
					lcsM[i][j] = newStrNode;
				}
			}
		}
		
		void showLCSMatrix() {
			
			StringNode* first = lcsM[0][0];
			
			cout<< setw(2*(sizeStr1+1))<< first->getCharacters() << setw(sizeStr1+1);
			for (int i = 0; i < sizeStr2; i++){
				cout<< str2[i] << setw(sizeStr1+1);
			}
			cout<<endl;
			
			cout<< first->getCharacters() << setw(sizeStr1+1);
			for (int i = 0; i < sizeStr2 + 1; i++){
				newStrNode = lcsM[0][i];
				cout<< intTostr(newStrNode->getRank()) + newStrNode->getDirection() << setw(sizeStr1+1);
			}
			cout<<endl;
			
			/*
				Displaying other values in the matrix form with the Row-Labels
			*/
			for (int i = 1; i < sizeStr1 + 1; i++){
				cout<< str1[i-1] << setw(sizeStr1+1);
				newStrNode = lcsM[i][0];
				cout << intTostr(newStrNode->getRank()) + newStrNode->getDirection() << setw(sizeStr1+1);
				for (int j = 1; j < sizeStr2 + 1; j++){
					newStrNode = lcsM[i][j];
					cout<< intTostr(newStrNode->getRank()) + newStrNode->getDirection() << setw(sizeStr1+1);	
				}
				cout<<endl;
			}	
		}
		
		void lcsLogic(){
			string lcs = "";
			previous = lcsM[sizeStr1][sizeStr2];
			cout<<endl<<"\nTHE LENGTH OF THE LONGEST SUB-SEQUENCE IS: "<<previous->getRank()<<endl;			
			cout<<"\nPATH TAKEN: ";
			while (previous != NULL){
				
				if (previous->getHasDiagonal()){
					lcs += previous->getCharacters();
				}
				
				if (previous->getPrevious() != NULL){
					cout<< intTostr(previous->getRank()) + previous->getDirection() << " --> ";
				} else {
					cout<< intTostr(previous->getRank()) + previous->getDirection();
				}
				previous = previous->getPrevious();
			}
			cout<<endl<<"\nTHE LONGEST SUB-SEQUENT STRING IS: " << string(lcs.rbegin(), lcs.rend());
		}
		
};

int main(){
	
	string str1,str2;
	cout << endl << "Enter the string 1: ";
	cin >> str1;
	cout << endl << "Enter the string 2: ";
	cin >> str2;
	cout << endl;
	LCS l(str1,str2);
	l.buildLCSMatrix();
	l.showLCSMatrix();
	l.lcsLogic();
	return 0;
}
