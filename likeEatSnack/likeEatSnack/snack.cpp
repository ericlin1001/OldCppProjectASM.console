#define _CONSOLE_MODE
//
#ifdef CONSOLE_MODE
#include<iostream>
using namespace std;
#define Out(m) cout<<m<<endl;
#define Out1(m) cout<<m;
#define In(m) cin>>m;
#else
#define Out(m)  ;
#define Out1(m) ;
#define In(m) ;
#define system(m) ;
#define NULL 0
#endif
#define Trace(m) Out(#m"="<<(int)m);
//main code....
struct Node{
        unsigned char x,y;
       Node*next;
       Node(unsigned char tx,unsigned char ty,Node *p=NULL){
                 x=tx;y=ty;
                 next=p;
       }
};
struct Dir{
       unsigned char dx,dy;
};
typedef unsigned short int word ;
/*
;Y
;^
;|
;|
;0-------->X
;left,up,right ,down 1,2,3,4
*/
Dir dirs[5]={{0,0},{-1,0},{0,1},{1,0},{0,-1}};
Node *head,*food,*pivot;
unsigned char idir=3;
unsigned char len;
const unsigned char size=8;//can and only can be 8.
unsigned char winLen=size*2+2;
unsigned char outputData[8];
char isLose;
char isWin;
unsigned char graph[size][size];
///
const word MAX_SIZE=size*size*sizeof(Node);
struct Heap{
       char mem[MAX_SIZE];
       word next;
       void *lastp;
       
};
Heap heap;
//
void *myalloc(word num){
     heap.lastp=(void *)((char*)heap.mem+heap.next);
     heap.next+=num;
     return heap.lastp;
}
Node*newNode(unsigned char tx,unsigned char ty,Node *p=NULL){
                      Node*node=(Node*)myalloc(sizeof(Node));
                      node->x=tx;
                      node->y=ty;
                      node->next=p;
                      return node;
}

//myrand
//#define M=65535
int c=7;//change it.
int an=c;
int getRand(){
    an=(c*an+1)%65535;
    return an;
}
void setSeed(int k){
     //3,5,6,7
     int t=k;
     if(k!=6)k=2*k+1;
     k%=8;
     if(k==1)k=7;
     an=c=k;
     while(t--)getRand();
}
//end myrand

void init(){
     head=newNode(2,1);
     head->next=head;
     head->next=newNode(1,1,head->next);
     head->next=newNode(0,1,head->next);
     len=3;
     food=newNode(0,0);
     ;
     pivot=newNode(0,0,head->next);
     isLose=isWin=0;
}

void lose(){ if(!isWin){isLose=1;Out("lose");} }
     void win(){
          if(!isLose){isWin=1;Out("win");}
          }
void createGraph(){
     unsigned char i;
     unsigned char *pg=&graph[0][0];
     for(i=0;i<size*size;i++)*pg++=0;
     
     Node *p=head;
     do{
                    graph[p->x][p->y]=1;
                    p=p->next;
       }while(p!=head);
       graph[food->x][food->y]=2;
     }
void move(unsigned char tdir){
     if(tdir<=0||5<=tdir){
        tdir=idir;
     }
     Dir dir=dirs[tdir];
     Node*p=head;
     Trace(dir.dx);Trace(dir.dy);
     pivot->x=(head->x+dir.dx)%size;
     pivot->y=(head->y+dir.dy)%size;
     Out((int)pivot->x<<","<<(int)pivot->y);
     if(food->x==pivot->x && food->y==pivot->y){
                          //eating food.
                        //  cout<<"eating food."<<endl;
            head=head->next=pivot;
            len++;
            if(len>=winLen)win();
            ;
            pivot=newNode(0,0,head->next);                 
            //place food to other places.
                    unsigned char index=getRand()%(size*size-len);
                    index++;
                    createGraph();
                    unsigned char *pg=&graph[0][0];
                    unsigned char ipg=0;
                    while(index){if(*(pg+ipg++)==0)index--;};
                    ipg--;
                    
                    food->x=ipg/size;
                    food->y=ipg%size;
                    
            return ;
     }else{
           p=head;
           while((p=p->next)!=head)if(p->x==pivot->x && p->y ==pivot->y)break;
           if(p->next==head){//move back
           Out("Moving back");
                                    tdir=idir;
                                    dir=dirs[tdir];
                pivot->x=(head->x+dir.dx)%size;
                pivot->y=(head->y+dir.dy)%size;
           }else if(p!=head){
                       lose();
                       return;
           }
                             idir=tdir;
                             Out("noramlly move");
                             //noramlly move the snack.
                             head=head->next=pivot;
                             pivot=pivot->next;
                             head->next=pivot->next;
                             
  }
        
}

void print(){
     unsigned char i,j;
     createGraph();
     for(i=0;i<size;i++){
                      for(j=0;j<size;j++){
                                       Out1((unsigned char)(graph[j][size-1-i]+'0'));
                                       }
                                       Out("");
                      }
     }
     unsigned char converToHex(unsigned char ch){
       
     if(ch<=9)return ch+'0';
     else return ch+'A'-10;
     
}
void createOutputData(){
     unsigned char i,j;
     createGraph();
     for(i=0;i<size;i++){
                         outputData[i]=0;
                      for(j=0;j<size;j++){
                                          outputData[i]<<=1;
                                          outputData[i]+=graph[i][size-1-j]?1:0;
                                           }
                                         //  cout<<"("<<outputData[i]<<")";
                                   Out1(converToHex(outputData[i]/16)<<converToHex(outputData[i]%16)<<"("<<(int)outputData[i]<<")"<<",");
                                 }
                                 Out("");
                               
}

unsigned char convert(unsigned char ch){
     switch(ch){
               case 1:return 1;
                case 2:return 4;
                 case 3:return 3;
                 case 5:return 2;
                }
                return 0;
}

int main(){
    setSeed(1000);
    init();
    unsigned char idir=0;
    while(1){
              system("cls");
              move(idir);
              print();
               createOutputData();
              Out("left:1\tup:2\tright:3\tdown:4");
    In(idir);
    idir-='0';
    idir=convert(idir);
}
    return 0;
} 
  /*  while(1){
             int k;
cin>>k;
setSeed(k);
int i;
int times[8];
for(i=0;i<8;i++){times[i]=0;}
for(i=0;i<800;i++){int r=getRand()%8;times[r]++;cout<<r<<",";}
for(i=0;i<8;i++){cout<<i<<":"<<times[i]<<"\t";if(i%10==0)cout<<endl;}
cout<<endl;
}*/
