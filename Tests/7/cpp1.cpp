#include<fstream.h>
#include<windows.h>
int main(){
	system("start tt.bat>nul");
//	system("dir>D:\temp.txt");
	fstream outFile;
	outFile.open("cmd.txt",ios::in,0);
	char temp[100];
	int lentemp=0;
	while(!outFile.eof()){
		temp[lentemp++]=outFile.get();
	}
	cout<<"temp="<<temp<<endl;
	cout<<"lentemp="<<lentemp<<endl;
	outFile.close();
	fstream inFile;
	inFile.open("temp.txt",ios::out,0);
	for(int i=0;i<lentemp;i++){
		inFile.put(temp[i]);
	}
	inFile.close();
	char ch='a';
	char *t=&ch;
	return 0;
}