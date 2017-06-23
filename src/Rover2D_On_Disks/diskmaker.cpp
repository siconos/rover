#include <fstream>
#include <iostream> 
#include <ctime>
#include <cstdlib>
#include<math.h>
using namespace std;

double width=120.0;
int layer=3;
double r=1.6;
int ks=20;
double interval=1/ks*2;

int main(){
  int i,j,col,N;
  double eps,x,xn,y,diskr,diskm;
  double m=0.7;
  col= int (width/(r*2+interval));
  N=col*2*layer;
   ofstream out("disks1.dat");
   out<<N<<' '<<5<<endl;
   for (i=0;i<col;i++)
	{ 
         for (j=0;j<layer;j++)
          {
           eps=rand() / (double)(RAND_MAX);
           x=(r*2+interval)*(i+1)-(r*2+interval)/2+ eps/ks;
           eps=rand() / (double)(RAND_MAX);
           xn=-(r*2+interval)*(i+1)+(r*2+interval)/2- eps/ks;
           eps=rand() / (double)(RAND_MAX);
           y=(r*2+interval)*(j+1)- (r*2+interval)/2+ eps/ks; 
           eps=rand() / (double)(RAND_MAX);
           diskr=r+eps/ks;
           diskm=m;
           out<<x<<' '<<y<<' '<<diskr<<' '<<diskm<<' '<<0.0<<endl;
           out<<xn<<' '<<y<<' '<<diskr<<' '<<diskm<<' '<<0.0<<endl;
          }
	}

 return 0;   
}
