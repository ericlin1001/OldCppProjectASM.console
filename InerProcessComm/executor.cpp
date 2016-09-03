#include<fstream>
#include<iostream>
using namespace std;
int main(){
    while(1){
		ifstream infile("do");
		if(infile){
			int t=0;
			infile>>t;
			infile.close();
			int oldt=t;
			if(t>0){
				cout<<"do="<<t<<endl;
				//
				ifstream cmdFile;
				
				int failCount=20;
				while(failCount--){
					cmdFile.open("temp_cmd.bat");
					if(!cmdFile)continue;
					cout<<"executing..."<<endl;

					system("temp_cmd.bat > temp_cmd_result.txt");
					//system("type temp_cmd_result.txt");
					t--;
					/*
					char buffer[1024]="";
					int len=0;
					while(1){
						char ch=cmdFile.get();
						if(cmdFile.eof())break;
						buffer[len++]=ch;
					}
					buffer[len]=0;
					cout<<"<buffer>"<<buffer<<"</buffer>"<<endl;
					if(strcmp(buffer,"")!=0){
						
						t--;
					}*/
					//
					if(oldt!=t){
						cout<<"rewrite do="<<t<<endl;
						ofstream outfile("do");
						outfile<<t;
						outfile.close();
					}
				}
			}
			
		}
		
	}
    return 0;
}
