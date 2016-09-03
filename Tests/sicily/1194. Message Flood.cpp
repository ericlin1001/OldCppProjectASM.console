
#include<iostream>
#include<cstring>
#include<set>
using namespace std;
void lowerCase(string &str){
   for(int j = 0; j < str.length(); j++)
                str[j] = tolower(str[j]);
}
int main()
{
    int i, j;
	int m, n;
	string temp;
    set<string> friends;
    while (1)
    {
		cin>>n;
        if(n == 0)
            break;
        cin>>m;
	
        for (i = 0; i < n; i++)
        {
            cin >> temp;
            lowerCase(temp);
            friends.insert(temp);
        }
        for(i = 0; i < m; i++)
        {
            cin >> temp;
            lowerCase(temp);
            friends.erase(temp);   
        }
		cout<<friends.size()<<endl;
        friends.clear();
    }
    return 0;
}

