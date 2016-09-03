#include<stack>
#include<iostream>
#include<fstream>
using namespace std;
#define Trace(m) //cout<<#m<<"="<<m<<endl;
inline bool is_digital(char ch){return '0'<=ch&&ch<='9';}
inline bool is_lowwer_letter(char ch){return 'a'<=ch&&ch<='z';}
inline bool is_higher_letter(char ch){return 'A'<=ch&&ch<='Z';}
inline bool is_letter(char ch){return is_lowwer_letter(ch) || is_higher_letter(ch); }
inline bool is_letter_or_digital(char ch){return is_letter(ch) || is_digital(ch); }
bool isExistFile(char *fileName){
	if(*fileName==' ' ||*fileName=='\n' ||*fileName=='\0')return false;
	ifstream infile;
	infile.open(fileName);
	if(infile.fail())return false;
	
	infile.close();
	return true;
}
int count;
void printStr(char *str){
	while(*str>0){
		cout<<count++<<"   "<<(int)*str<<":"<<*str<<endl;
		str++;
		
	}
}
void printStack(stack<char> s){
}
bool isCorrectForm(char *str){
	int strlen=0;
	char *p=str;
	while(*p++>0)strlen++;
	while(str[strlen-1]=='\n')strlen--;
	str[strlen]=0;
	char buffer[10];
	//
	strncpy(buffer,str,3);
	buffer[3]=0;
	if(strcmp(buffer,"beg")!=0){
		cout<<"beg wrong!"<<endl;
		return false;
		
	}
	//
	strncpy(buffer,str+strlen-3,3);
	buffer[3]=0;
	if(strcmp(buffer,"end")!=0){
		Trace(buffer);
		cout<<"end wrong!"<<endl;
		return false;
	}
	//
	for(int i=0;i<=strlen-4;i++){
		str[i]=str[i+4];
	}
	strlen-=4;
	//
	str[strlen-3]=0;
	return true;
	
}


int getRand(int min,int max){
	if(min>max)swap(min,max);
	return rand()%(max-min+1)+min;
}
void revStr(char *str,int beg,int end){
	char *pb=str+beg;
	char *pe=str+end;
	while(pb<pe){
		swap(*pb,*pe);
		pb++;
		pe--;
	}
}
void analyExp(char *buffer,char *res){
	int reslen=0;
#define readCh(a) a=buffer[readLen++]
#define nextChar buffer[readLen]
		char ch;int readLen=0;
		//
		stack<char> s;
		while(nextChar){
			readCh(ch);
			//cout<<"read ("<<readLen<<"): "<<ch<<endl;
			if(ch==')' && !s.empty() && is_digital(s.top())){
				int min,max;
				char temp[10];
				int templen=0;
				//get max
				while(is_digital(s.top())){
					temp[templen++]=s.top();
					s.pop();
					reslen--;
				}
				temp[templen++]=0;
				revStr(temp,0,strlen(temp)-1);
				//cout<<"max:";
				Trace(temp);
				max=atoi(temp);
				//get min
				templen=0;
				if(s.top()==','){reslen--;s.pop();}else{cout<<"Error:Not correct syntax"<<endl;return ;}
				while(!s.empty() && is_digital(s.top())){
					temp[templen++]=s.top();
					s.pop();
					reslen--;
				}
				temp[templen++]=0;
				revStr(temp,0,strlen(temp)-1);
				//cout<<"min:";
				Trace(temp);
				min=atoi(temp);
				//
				if(s.top()=='('){reslen--;s.pop();}else{cout<<"Error:Not correct syntax"<<endl;return ;}
				//
				Trace(min);
				Trace(max);
				int r=getRand(min,max);
				Trace(r);
				//
				itoa(r,temp,10);
				templen=0;
				while(temp[templen]){res[reslen++]=temp[templen];s.push(temp[templen]);templen++;}
				
			}else{
				s.push(ch);
				res[reslen++]=ch;
				Trace(res);
			}
		}
		res[reslen++]=0;
		//printStack(s);
		Trace(res);
}
int calculate(const char *str){
	int answer=0;
		//calculate:
		char order[100]="set /a t=";
		strcat(order,str);
		strcat(order," > temp");
		Trace(order);
		Trace("begin sys");
		system(order);
		Trace("end sys");
		ifstream tempfile;tempfile.open("temp");
		
		tempfile>>answer;
		tempfile.close();
		remove("temp");
		return answer;
}

int main(){
	if(!isExistFile("defaultName.data")){
		cout<<"Error:Can't open defaultName.data"<<endl;
		return 0;
	}
	ifstream expFile;
	//
	char buffer[1000]; 
	char fileNames[100];
	ifstream names;
	names.open("defaultName.data");
	//
	bool isOk=false;
	//
	while(!names.eof()){
		names>>fileNames;Trace(fileNames);
		if(isExistFile(fileNames)){
			//cout<<"next file............................"<<endl;
			expFile.open(fileNames);
			expFile.read(buffer,1000);
			Trace(expFile.gcount());
			Trace(buffer);
			if(expFile.gcount() >=1000){
				cout<<"Error:the file \""<<fileNames<<"\" is too long to read"<<endl;
				continue;
			}
			expFile.close();
			if(!isCorrectForm(buffer)){
				cout<<"Error:the file \""<<fileNames<<"\" is not in a correct format."<<endl;
				continue;
			}
			//printStr(buffer);
			Trace(buffer);
			isOk=true;
			break;
		}
	}
	names.close();
	if(isOk){
		Trace(buffer);
		char copybuffer[1000];
		strcpy(copybuffer,buffer);
		cout<<"beginning..."<<endl;
		while(1){
		char exp[100];int answer;
		char *pbeg;char *pend;
		pbeg=buffer;
		pend=pbeg;
		do{
			strcpy(buffer,copybuffer);
			while(*pend && *pend!='\n')pend++;
			if(!(*pend))break;
			*pend=0;
			//
			memset(exp,0,100);
			analyExp(pbeg,exp);
			answer=calculate(exp);
			//
			int input=0;
			char inputBuffer[10];
			do{
				
				cout<<exp<<"=";
				//cin.get(inputBuffer,9);
				//input=atoi(inputBuffer);
				cin>>input;
				if(input!=answer){
					cout<<"wrong!"<<endl;
				}else{
					cout<<"correct."<<endl;
					break;
				}
			}while(1);
				
			//
			pbeg=++pend;
		}while(1);
	}
		cout<<"exiting..."<<endl;
	}
	return 0;
}