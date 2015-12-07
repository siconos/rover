#include <fstream>
#include <iostream> 
#include <ctime>
#include <cstdlib>
#include<math.h>
using namespace std;


int main(){
int N=2;
double x=0.53;
double y=77.5;
double r=0.5;
double m=0.0;

   ofstream out("disks1.dat");
   out<<N<<' '<<5<<endl;
           out<<x<<' '<<y<<' '<<r<<' '<<m<<' '<<0.0<<endl;
           out<<-x<<' '<<y<<' '<<r<<' '<<m<<' '<<0.0<<endl;  
  return 0; 
}
