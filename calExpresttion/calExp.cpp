#include<iostream.h>
#include "calExp.h"
#include<string.h>
char *mainCal(char *exp){
	char *tempExp=new char[strlen(exp)+1];
	strcpy(tempExp,exp);
	char *answer=calExp(tempExp);
	return answer;
}
char *calExp(char *exp){
	//for open the brace.
	int start=findIndex(exp,'(');
	if(start!=-1){
		//contain brace().
		int end=findLastIndex(exp,')');
		if(end==-1){
			cerr<<"Error:have not )"<<endl;
			return "0";
		}
		char *subAnswer=calExp(subStr(exp,start+1,end-1));
		strSplice(exp,start,end,subAnswer);
	}
	return cal(exp);
}
char *cal(char *exp)
{
	//calculate expression without ()
	//seperate num and sign
	List nums;
	List signs;
	int i=0;
	char buffer[MAXSIZEOFNUM+1];//the max size of number is 10
	char *pNum=buffer;
	char ch;
	while(ch=*(exp+i)){
		i++;
		if(isOperation(ch)){
			*pNum++=ch;
		}else if(isSign(ch)){
			signs.push(ch);
			*pNum++='\0';
			nums.push(buffer);
			pNum=buffer;
		}else{
			cerr<<"Error:Have not defined sign."<<endl;
			return "0";
		}
	}
	*pNum++='\0';
	nums.push(buffer);
	//for test
	//cout<<"nums:";
//	nums.print();
	//cout<<"sign:";
	//signs.print();
	//calculating...
	while(nums.getLength()>1 && signs.getLength()>0){
		//i=0;
		i=getMaxIndex(signs);
		char sign=*signs.del(i);
		char *ROPT=nums.del(i+1);//"test1";
		char *LOPT=nums.get(i);
		char *temp=calTwo(LOPT,ROPT,sign);//ok
		//cout<<"strlen(temp)="<<strlen(temp)<<endl;
		//cout<<"temp="<<temp<<endl;
		nums.set(i,temp);
	}
	return nums.get(0);
}





//


char *subStr(char *str,int begin,int end){
	end++;
	char *tempstr=new char[end-begin+1];
	str+=begin;
	end-=begin;
	begin=end;
	while((end--)) *tempstr++=*str++;
	*tempstr=0;
	tempstr-=begin;
	return tempstr;
}
void strSplice(char * &str,int start,int end,char *substr){
	int lensub=strlen(substr);
	char *tempstr=new char[strlen(str)+lensub-(end-start+1)+1];
	*(str+start)='\0';
	strcpy(tempstr,str);
	strcpy(tempstr+start,substr);
	strcpy(tempstr+start+lensub,str+end+1);
	str=tempstr;
}

bool isSign(char ch){
	return signLevel(ch)!=-1;
}

//
int getMaxIndex(List &list){
	int max=-1;
	int nowlevel=-1;
	list.fromBegin();
	for(int i=0;i<list.getLength();i++){
		char *t=list.get();
		if(signLevel(*t)>nowlevel){
			max=i;
			nowlevel=signLevel(*t);
		}
		list.next();
	}
	//
	if(max==-1){
		cerr<<"Error:in get MaxIndex"<<endl;
		return 0;
	}
	return max;
}
int findIndex(char *str,char ch){
	int index=-1;
	for(int i=0;i<(int)strlen(str);i++){
		if(*(str+i)==ch){
			index=i;
			break;
		}
	}
	return index;
}
int findLastIndex(char *str,char ch){
	int index=-1;
	for(int i=strlen(str)-1;i>=0;i--){
		if(*(str+i)==ch){
			index=i;
			break;
		}
	}
	return index;
}


