#include <iostream>
//#include<cstring>
using namespace std;
typedef char STRING_11[11];
void mylowerCase(char *str){
    while(*str!='\0'){
        if(*str<'a'){
            *str+=0x20;
        }
        str++;
    }
}
int  mystrcmp(const char *str1,const char *str2){
	while(*str1 && *str2 && *str1++ == *str2++);
	return ((*str1) - (*str2));
}
void mystrcpy(char *str1,const char *str2){
	while(*str1++=*str2++);
}
int main()
{  
	int n,m;
	int row;
	while(1){
		cin>>n;
		if (n == 0)break;   
		cin>>m;
		STRING_11 *friends=new STRING_11[n];  
		STRING_11 *sentFriends=new STRING_11[n];
		for ( row = 0;row<n;row++){
			cin>>friends[row];
			mylowerCase(friends[row]);
		}
		for (row = 0;row < m;row++){
			cin>>sentFriends[row];
			mylowerCase(sentFriends[row]);
		}
		// ÅÅÐò
		/*STRING_11 currentMax1;
		int currentMaxIndex1 ;
		int i ;
		int j;
		for ( i = m-1;i >= 1;i--){
			mystrcpy(currentMax1, sentFriends[0]);
			 currentMaxIndex1 = 0;
			for  (j = 1;j <= i;j++){
				if (mystrcmp(currentMax1 , sentFriends[j]) < 0){
					mystrcpy(currentMax1, sentFriends[j]);
					currentMaxIndex1 = j;
				}
			}
			if (currentMaxIndex1 != i){
				mystrcpy(sentFriends[currentMaxIndex1], sentFriends[i]);
				mystrcpy(sentFriends[i], currentMax1);
			}
		}	
		int ttt= n;
		for (int s = 0;s < ttt;s++){
			int low = 0;
			int high = m - 1;
			while (high >= low){
				int mid = (low + high)/2;
				if(mystrcmp (friends[s] , sentFriends[mid]) < 0){
					high = mid - 1;
				}else if (mystrcmp (friends[s] , sentFriends[mid]) == 0){   
					n--;
					break;
				}else{
					low = mid + 1;
				}
			}
		}*/
		cout<<n<<endl;
	} 
	return 0;            
}


/*testcase:
5 3
Inkfish
Henry
Carp
Max
Jericho
Carp
Max
Carp
0
*/