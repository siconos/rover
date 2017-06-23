#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

int main(){

  string str;

  vector<vector<double> > outerVec;
  vector<vector<double> >::iterator outerIt;
  
  vector<double> innerVec;
  vector<double>::iterator innerIt;

  ifstream inpFile("SICout.txt");

  if(inpFile.is_open()){

    while(getline(inpFile, str)){
      
      cout << str << endl;

      //inner loop for extracting doubles

      istringstream iss(str);

      double d;

      while(iss >> setprecision(5) >> d){

        innerVec.push_back(d);

      }

      outerVec.push_back(innerVec);

      innerVec.clear();

    }

    inpFile.close();

    for(outerIt = outerVec.begin(); outerIt != outerVec.end(); ++outerIt){
   
      for(innerIt = outerIt->begin(); innerIt != outerIt->end(); ++innerIt){
               
          cout << *innerIt;
                
      }

      cout << endl;
    }

  }
  else{

    cout << "Can't open the file";

  }

  return 0;

}
