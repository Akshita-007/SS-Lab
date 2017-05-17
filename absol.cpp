#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<iomanip>
using namespace std; 
int main(){
	int start, length;
	ifstream input;
	ofstream output;
	input.open("inputa.txt");
	output.open("outputa.txt");
	string data;
	char type;
	//getline(input,data);
	//type=data.at(0);
	while(type!='E'){
		getline(input,data);
		type=data.at(0);
		if(type=='T'){		
			string opcodes = data.substr(9);
			string locstring = data.substr(1,6);
			stringstream s(locstring);
			int loc;
			s>>hex>>loc;
			while(opcodes.length()>0){
				output<<hex<<loc<<" " <<opcodes.substr(0,2)<<endl;
				opcodes.erase(0,2);
				loc++;
			}
		}
	}
}
