#include <cmath>
#include <iostream>
#include <stdlib.h>

#define PI 3.1415

using namespace std;

class vect
{
 
  public:
    
    double x, y, z;
    
    vect()
    {

      x = 0;
      y = 0;
      z = 0;

    }

    vect(double a, double b, double c)
    {
      
      x = a;
      y = b;
      z = c;
      
    }

    vect& operator=(const vect & templ)
    {

      if(&templ == this)
      {

        return *this;

      }
      
      x = templ.x;
      y = templ.y;
      z = templ.z;

      return *this;

    }

    vect operator-(vect temp)
    {
     
      vect res;
       
      res.x = x - temp.x;
      res.y = y - temp.y;
      res.z = z - temp.z;

      return res;

    }

    vect& operator*(double temp)
    {
               
      x = x*temp;
      y = y*temp;
      z = z*temp;

      return *this;

    }

    vect operator+(vect temp)
    {
     
      vect res;
       
      res.x = x + temp.x;
      res.y = y + temp.y;
      res.z = z + temp.z;

      return res;

    }


    vect(const vect & templ)
    {

      x = templ.x;
      y = templ.y;
      z = templ.z;
    
    }

    void norm()
    {
      
      double l = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
      
      if(l > 0)
      {

      x = x/l;
      y = y/l;
      z = z/l;

      }
    
    }

  void flip()
  {

    x = -x;
    y = -y;
    z = -z;

  }


};

double dotProd(vect A, vect B)
{

  double tmp;

  tmp = A.x*B.x + A.y*B.y + A.z*B.z;

  return tmp;

}

vect crossProd(vect A, vect B)
{

  vect tmp;

  tmp.x = (A.y*B.z) - (B.y*A.z);
  tmp.y = (B.x*A.z) - (A.x*B.z);
  tmp.z = (A.x*B.y) - (A.y*B.x);

  return tmp;

}

bool checkIfSameSideOfEdge(vect P1, vect P2, vect A, vect B)
{

  vect cp1, cp2, tmp1, tmp2, tmp3;

  tmp1 = B - A;
  tmp2 = P1 - A;
  tmp3 = P2 - A;

  cp1 = crossProd(tmp1, tmp2);
  cp2 = crossProd(tmp1, tmp3);
  
  //if(dotProd(cp1,cp2) >= 0)
  if(dotProd(cp1,cp2) > 0)
  {
  
  return true;

  }
  else
  {

  return false;
 
  }

}

bool checkIfInsideTriangle(vect P, vect vert1, vect vert2, vect vert3)
{

  vect A = vert1;
  vect B = vert2;
  vect C = vert3;

  if(checkIfSameSideOfEdge(P, A, B, C) && checkIfSameSideOfEdge(P, B, A, C) && checkIfSameSideOfEdge(P, C, A, B))
  {

  return true;

  }
  else
  {

  return false;

  }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

bool checkIfInsideSegment(vect P, vect A, vect B)
{

  vect tmp1, AB, AP, BP;
  double tmp2, tmp3, tmp4;
    
  double tol = 0.000000000000000001;

  AB = B - A;
  AP = P - A;
  BP = P - B;
  
  tmp1 = crossProd(AP, AB);

  tmp2 = sqrt(pow(tmp1.x, 2) + pow(tmp1.y, 2) + pow(tmp1.z, 2));

  tmp3 = dotProd(AP, AB);

  tmp4 = dotProd(BP, AB);

  if((tmp2 < tol) && (tmp3 >= 0) && (tmp4 <= 0))
  {

  return true;

  }
  else
  {

  return false;

  }
   
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*void Rover3DWheelFixedTriangleR::calcDistance(double* dist, double* q, double* cont)
{

  double Px, Py, Pz;
  
  //Calculate the distance for each wheel

  vect tmp1, tmp2, s, P;
  double d1, d2, l;

  //projected point

  vect Q;

  //normal vector to the plane (projection is offset along the normal)

  vect n(A, B, C);

  //distances from the vertices

  double dis1, dis2, dis3;

  //where maximum value will be stored

  double tmpmin;

  //vars to compute the projection onto a segment

  vect t1, t2;

  double t;

  vect proj;
  
  for(int i = 0; i < 6; i++)
  {
    
    //project point on the plane and check if the projection lies inside the triangle

    //contact point in cartesian space 
    
    Px = CC[(i*3)];
    Py = CC[(i*3) + 1];
    Pz = CC[(i*3) + 2];
    
    //Check!!!!!!

    //Px = Px/100.0;
    //Py = Py/100.0;
    //Pz = Pz/100.0;


    P.x = Px;
    P.y = Py;
    P.z = Pz;


    //cout << P.x << " " << P.y << " " << P.z << endl; 

    //projection on the plane

    Q.x = Px - A*((A*Px + B*Py + C*Pz + D)/(pow(A,2) + pow(B,2) + pow(C,2)));
    Q.y = Py - B*((A*Px + B*Py + C*Pz + D)/(pow(A,2) + pow(B,2) + pow(C,2)));
    Q.z = Pz - C*((A*Px + B*Py + C*Pz + D)/(pow(A,2) + pow(B,2) + pow(C,2)));
    
    if(checkIfInsideTriangle(Q))
    {  

    //calculate the distance between the plane and the point

    l = (fabs(A*Px + B*Py + C*Pz + D)/sqrt(pow(A,2) + pow(B,2) + pow(C,2))) + TireRadius;

    //dist[i] = l;

    //cont[(i*3)] = Q.x;
    //cont[(i*3) + 1] = Q.y;
    //cont[(i*3) + 2] = Q.z;


    //check below!!!!!!!!!!!!!!!

    dist[i] = l/100.0;

    cont[(i*3)] = Q.x/100.0;
    cont[(i*3) + 1] = Q.y/100.0;
    cont[(i*3) + 2] = Q.z/100.0;



    //cout << l << endl;

    continue;

    }
    else
    {

    //projection is outside the triangle so we check if the point projects inside any of the edges  
    
    if(checkIfInsideSegment(P, vert1, vert2))  
    {
      
    //get the distance from that segment  
    
    tmp1.x = vert1.x - P.x;
    tmp1.y = vert1.y - P.y;
    tmp1.z = vert1.z - P.z;

    s.x = vert2.x - vert1.x;
    s.y = vert2.y - vert1.y;
    s.z = vert2.z - vert1.z;
    
    tmp2 = crossProd(tmp1, s);

    d1 = sqrt(pow(tmp2.x, 2) + pow(tmp2.y, 2) + pow(tmp2.z, 2));
    d2 = sqrt(pow(s.x, 2) + pow(s.y, 2) + pow(s.z, 2));

    l = d1/d2;

    dist[i] = l;  

    //cout << l << endl;

    //project the point on that segment
    //from www.http://stackoverflow.com/questions/849211/

    t1 = P - vert1;
    t2 = vert2 - vert1;

    t  = (dotProd(t1, t2)/(pow(vert2.x - vert1.x, 2) + pow(vert2.y - vert1.y, 2) + pow(vert2.z - vert1.z, 2)));
    
    proj = vert1 + (vert2 - vert1)*t;

    cont[(i*3)] = proj.x;
    cont[(i*3) + 1] = proj.y;
    cont[(i*3) + 2] = proj.z;

    continue;  

    }  
    else if(checkIfInsideSegment(P, vert1, vert3))  
    {

    //get the distance from that segment  
    
    tmp1.x = vert1.x - P.x;
    tmp1.y = vert1.y - P.y;
    tmp1.z = vert1.z - P.z;

    s.x = vert3.x - vert1.x;
    s.y = vert3.y - vert1.y;
    s.z = vert3.z - vert1.z;
    
    tmp2 = crossProd(tmp1, s);

    d1 = sqrt(pow(tmp2.x, 2) + pow(tmp2.y, 2) + pow(tmp2.z, 2));
    d2 = sqrt(pow(s.x, 2) + pow(s.y, 2) + pow(s.z, 2));

    l = d1/d2;

    dist[i] = l;
    cout << l << endl;
    //project the point on that segment
    //from www.http://stackoverflow.com/questions/849211/

    t1 = P - vert1;
    t2 = vert3 - vert1;

    t  = (dotProd(t1, t2)/(pow(vert3.x - vert1.x, 2) + pow(vert3.y - vert1.y, 2) + pow(vert3.z - vert1.z, 2)));
    
    proj = vert1 + (vert3 - vert1)*t;

    cont[(i*3)] = proj.x;
    cont[(i*3) + 1] = proj.y;
    cont[(i*3) + 2] = proj.z;
    
    continue;

    }  
    else if(checkIfInsideSegment(P, vert2, vert3))
    {

    //get the distance from that segment

    tmp1.x = vert1.x - P.x;
    tmp1.y = vert1.y - P.y;
    tmp1.z = vert1.z - P.z;

    s.x = vert3.x - vert2.x;
    s.y = vert3.y - vert2.y;
    s.z = vert3.z - vert2.z;
    
    tmp2 = crossProd(tmp1, s);

    d1 = sqrt(pow(tmp2.x, 2) + pow(tmp2.y, 2) + pow(tmp2.z, 2));
    d2 = sqrt(pow(s.x, 2) + pow(s.y, 2) + pow(s.z, 2));

    l = d1/d2;

    dist[i] = l;
    cout << l << endl;
    //project the point on that segment
    //from www.http://stackoverflow.com/questions/849211/

    t1 = P - vert2;
    t2 = vert3 - vert2;

    t  = (dotProd(t1, t2)/(pow(vert3.x - vert2.x, 2) + pow(vert3.y - vert2.y, 2) + pow(vert3.z - vert2.z, 2)));
    
    proj = vert2 + (vert3 - vert2)*t;

    cont[(i*3)] = proj.x;
    cont[(i*3) + 1] = proj.y;
    cont[(i*3) + 2] = proj.z;
    
    continue;

    }

    //point is outside the  segments and triangle - we get as distance the minimum of the distances from vertices

    dis1 = sqrt(pow(vert1.x - Px, 2) + pow(vert1.y - Py, 2) +  pow(vert1.z - Pz, 2));
    dis2 = sqrt(pow(vert2.x - Px, 2) + pow(vert2.y - Py, 2) +  pow(vert2.z - Pz, 2));
    dis3 = sqrt(pow(vert3.x - Px, 2) + pow(vert3.y - Py, 2) +  pow(vert3.z - Pz, 2));    
    
    tmpmin = fcnMin(dis1, dis2);

    dist[i] = fcnMin(tmpmin, dis3);

    //the projection is simply one of the vertices (the one we took the distance from)

    if(dist[i] == dis1)
    {

    cont[(i*3)] = vert1.x;
    cont[(i*3) + 1] = vert1.y;
    cont[(i*3) + 2] = vert1.z;

    cout << dis1 << endl;
    
    }
    else if(dist[i] == dis2)
    {

    cont[(i*3)] = vert2.x;
    cont[(i*3) + 1] = vert2.y;
    cont[(i*3) + 2] = vert2.z;

    cout << dis1 << endl;

    }
    else if(dist[i] == dis3)
    {

    cont[(i*3)] = vert3.x;
    cont[(i*3) + 1] = vert3.y;
    cont[(i*3) + 2] = vert3.z;

    cout << dis1 << endl;

    }

    }
  
  }

}*/

//////////////////////////////////////////////////////////////////////////////////////

int main()
{
  
  //triangle vertices

  //vect vert1(1000, 0, 0), vert2(0, 0, 2000), vert3(2000, 0, 2000);

  vect vert1(0, 10, 1000), vert2(1000, 10, 1000), vert3(0, 10, 0);  

  double A, B, C, D;
  
  A = (vert2.y - vert1.y)*(vert3.z - vert1.z) - (vert3.y - vert1.y)*(vert2.z - vert1.z); 
  B = (vert2.z - vert1.z)*(vert3.x - vert1.x) - (vert3.z - vert1.z)*(vert2.x - vert1.x);
  C = (vert2.x - vert1.x)*(vert3.y - vert1.y) - (vert3.x - vert1.x)*(vert2.y - vert1.y);
  D = -(A*(vert1.x) + B*(vert1.y) + C*(vert1.z));

  cout << "Plane coeffs: " << endl;
  cout << A << " " << B << " " << C << " " << D << " " << endl;

  //////////////////////////////////////////////////////////////////////////////////////

  //getting the normalized right-handed frame located in vertex 1 

  double eul[3];

  vect n;

  vect ab, ac;

  //axes

  vect axz, axy, axx;

  ab = vert2 - vert1;
  ac = vert3 - vert1;
  
  //axy cannot have zero magintude as a result of triangulation (ab and ac can't be parallel)

  axy = crossProd(ac, ab);
  
  //axis flipping - if normal's pointing downwards

  if(axy.y < 0){

    axy.flip();
   
    axx = crossProd(axy, ab);
   
    axz = ab;
  
  }else{
    
    axx = crossProd(axy, ac);
   
    axz = ac;

  }

  //orthonormal basis

  axy.norm();  
  axz.norm();
  axx.norm();

  n.x = axy.x;
  n.y = axy.y;
  n.z = axy.z;
  n.norm();
  
  /* 

          |axx.x axy.x axz.x|
    rot = |axx.y axy.y axz.y|
          |axx.z axy.z axz.z|

  */

  if((axx.z != 1) && (axx.z != -1)){
    
    eul[1] = atan2(-axx.z, sqrt(pow(axx.x, 2) + pow(axx.y, 2)));
    eul[0] = atan2((axy.z/cos(eul[1])), (axz.z/cos(eul[1])));
    eul[2] = atan2((axx.y/cos(eul[1])), (axx.x/cos(eul[1])));
  
  }
  else{

    eul[2] = 0;
    
    if(axx.z == -1){

      eul[1] = PI/2;
      eul[0] = atan2(axy.x, axy.y);
      

    }
    else{

      eul[1] = -PI/2;
      eul[0] = -atan2(axy.x, axy.y);

    }

  }

  //////////////////////////////////////////////////////////////////////////////////////

  //intuitive method of dealing with euler angles singularities

  /*if((axx.z != 1) && (axx.z != -1)){
    
    eul[1] = atan2(-axx.z, sqrt(pow(axx.x, 2) + pow(axx.y, 2)));
    eul[0] = atan2((axy.z/cos(eul[1])), (axz.z/cos(eul[1])));
    eul[2] = atan2((axx.y/cos(eul[1])), (axx.x/cos(eul[1])));
  
  }
  else{

    //recalculating the normalized right-handed frame located in vertex 2 (singularity) 

    ab = vert1 - vert2;
    ac = vert3 - vert2;
  
    //axy cannot have zero magintude as a result of triangulation (ab and ac can't be parallel)

    axy = crossProd(ac, ab);
  
    //axis flipping - if normal's pointing downwards

    if(axy.y < 0){

      axy.flip();
   
      axx = crossProd(axy, ab);
   
      axz = ab;
  
    }else{
    
      axx = crossProd(axy, ac);
   
      axz = ac;

    }

    //orthonormal basis

    axy.norm();  
    axz.norm();
    axx.norm();
    
    eul[1] = atan2(-axx.z, sqrt(pow(axx.x, 2) + pow(axx.y, 2)));
    eul[0] = atan2((axy.z/cos(eul[1])), (axz.z/cos(eul[1])));
    eul[2] = atan2((axx.y/cos(eul[1])), (axx.x/cos(eul[1])));

    if((axx.z == 1) || (axx.z == -1)){

      //recalculating again the normalized right-handed frame located in vertex 3 (singularity) 

      ab = vert1 - vert3;
      ac = vert2 - vert3;
  
      //axy cannot have zero magintude as a result of triangulation (ab and ac can't be parallel)

      axy = crossProd(ac, ab);
  
      //axis flipping - if normal's pointing downwards

      if(axy.y < 0){

        axy.flip();
   
        axx = crossProd(axy, ab);
   
        axz = ab;
  
      }else{
    
        axx = crossProd(axy, ac);
   
        axz = ac;

      }

      //orthonormal basis

      axy.norm();  
      axz.norm();
      axx.norm();

    eul[1] = atan2(-axx.z, sqrt(pow(axx.x, 2) + pow(axx.y, 2)));
    eul[0] = atan2((axy.z/cos(eul[1])), (axz.z/cos(eul[1])));
    eul[2] = atan2((axx.y/cos(eul[1])), (axx.x/cos(eul[1])));

    }

  }*/

  ///////////////////////////////////////////////////////////////////////////////

  cout << "euler angles: " << endl;
  cout << eul[0] << " " << eul[1] << " " << eul[2] << endl;
  
  cout << "Normal " << endl;
  cout << n.x << " " << n.y << " " << n.z << endl;

  cout << "rot. matrices: " << endl;
  cout << "[ " << axx.x  << " " << axy.x << " " << axz.x << " ]" << endl;
  cout << "[ " << axx.y  << " " << axy.y << " " << axz.y << " ]" << endl;
  cout << "[ " << axx.z  << " " << axy.z << " " << axz.z << " ]" << endl;  

}





