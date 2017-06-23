#include <cmath>
#include <iostream>
#include <stdlib.h>

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
  
/*  vect a(1, 2, 3) , b(3, 4, 5);

  vect c = crossProd(a, b);

  cout << c.x << " " << c.y << " " << c.z << endl;

  c.norm();

  cout << c.x << " " << c.y << " " << c.z << endl;

  vect d;

  d = a;

  cout << d.x << " " << d.y << " " << d.z << endl;

  vect e;

  e = a + b;

  cout << e.x << " " << e.y << " " << e.z << endl;
*/

  //triangle vertices

  vect vert1(0, 0, 0), vert2(10, 0, 0), vert3(0, 0, 10);
  
  double A, B, C, D;
  
  A = (vert2.y - vert1.y)*(vert3.z - vert1.z) - (vert3.y - vert1.y)*(vert2.z - vert1.z); 
  B = (vert2.z - vert1.z)*(vert3.x - vert1.x) - (vert3.z - vert1.z)*(vert2.x - vert1.x);
  C = (vert2.x - vert1.x)*(vert3.y - vert1.y) - (vert3.x - vert1.x)*(vert2.y - vert1.y);
  D = -(A*(vert1.x) + B*(vert1.y) + C*(vert1.z));

  //////////////////////////////////////////////////////////////////////////////////////

  //conversion from rotation matrix to euler angles

  /*if(axy.z > 0.998 || axy.z < -0.998){

    eul[0] = atan2(-axz.x, axx.x);
    eul[1] = 0;

  }
  else {

    eul[0] = atan2(axx.z, axz.z);
    eul[1] = atan2(axy.x, axy.y);  

  }

  eul[2] = asin(axy.z);*/

  //both methods below are ok

  //////////////////////////////////////////////////////////////////////////////////////

  cout << "Plane coeffs : " << endl;

  cout << A << " " << B << " " << C << " " << D << endl;

  vect one(0, 1000, 0), two(10000, 0, 0), three(10000, 1000, 10000);

  vect axx, axz;

  double eul[3];

  vect ab = two - one;
  vect ac = three - one;

  vect axy = crossProd(ab, ac);

  //axis flipping

  if(axy.y < 0){

    axy.flip();
    axx = crossProd(axy, ac);
    //axx = crossProd(axy, ab);
    axz = ac;
    //axz = ab;
  
  }else{
    axx = crossProd(axy, ab);
    //axx = crossProd(axy, ac);
    axz = ab;
    //axz = ac;

  }

  //orthonoral basis

  axy.norm();  
  axz.norm();
  axx.norm();

  /*axx.x = axx.x*0.9950 + axx.y*(-0.09933) + axx.z*0.00997; 
  axx.y = axx.x*0.09983 + axx.y*0.99003 + axx.z*(-0.09933); 
  axx.z = axx.x*0 + axx.y*0.09983 + axx.z*0.99500; 

  axy.x = axy.x*0.9950 + axy.y*(-0.09933) + axy.z*0.00997; 
  axy.y = axy.x*0.09983 + axy.y*0.99003 + axy.z*(-0.09933); 
  axy.z = axy.x*0 + axy.y*0.09983 + axy.z*0.99500; 

  axz.x = axz.x*0.9950 + axz.y*(-0.09933) + axz.z*0.00997; 
  axz.y = axz.x*0.09983 + axz.y*0.99003 + axz.z*(-0.09933); 
  axz.z = axz.x*0 + axz.y*0.09983 + axz.z*0.99500;*/ 

  eul[0] = atan2((axz.y/cos(eul[1])), (axz.z/cos(eul[1])));
  eul[1] = -asin(axz.x);
  eul[2] = atan2((axy.x/cos(eul[1])), (axx.x/cos(eul[1])));

  //eul[0] = atan2(axy.x, axx.x);
  //eul[1] = atan2(-axz.x, sqrt(pow(axz.y, 2) + pow(axz.z, 2)));
  //eul[2] = atan2(axz.y, axz.z);

  cout << "euler angles: " << endl;
  cout << eul[0] << " " << eul[1] << " " << eul[2] << endl;

  cout << "Rotation matrix : " << endl;

  cout << axx.x << " " << axx.y << " " << axx.z << endl;
  cout << axy.x << " " << axy.y << " " << axy.z << endl;
  cout << axz.x << " " << axz.y << " " << axz.z << endl;

  //testing if two points are on the same side of a segment

  vect vertex1(2, 0, 0), vertex2(2, 0, 7), p1(1.99, 0, 5), p2(1.98, 0, 6);

  bool val = checkIfSameSideOfEdge(p1, p2, vertex1, vertex2);

  cout << "on the same side of the segment : " << endl;

  cout << boolalpha << val << endl;
  
  //testing if a point is inside of a triangle

  vect point(2, 0, -0.0001);

  bool val1 = checkIfInsideTriangle(point, vert1, vert2, vert3);

  cout << "inside the triangle : " << endl;

  cout << boolalpha << val1 << endl;


  //testing if a point is inside of a segment

  vect point1(6, 2, 2), Aa(0, 0, 2), Bb(7, 0, 2);

  bool val2 = checkIfInsideSegment(point1, Aa, Bb);

  cout << "inside the segment : " << endl;

  cout << boolalpha << val2 << endl;


  /////////////////////////////////////////

  vect s, tmp1, verte1(0, 0, 2), verte2(7, 0, 2), tmp2, P3(2, 0, 1);

    tmp1 = verte1 - P3;

    s = verte2 - verte1;
    
    tmp2 = crossProd(tmp1, s);

    double d1 = sqrt(pow(tmp2.x, 2) + pow(tmp2.y, 2) + pow(tmp2.z, 2));
    double d2 = sqrt(pow(s.x, 2) + pow(s.y, 2) + pow(s.z, 2));

    double l = d1/d2;
    
    cout << "distance from the segment : " << endl;

    cout << l << endl;

    //testing the projection on the plane
  
    double Al, Bl, Cl, Dl;
  
    Al = 0;
    Bl = 1;
    Cl = 0;
    Dl = 4;

    vect Q, P(2, 2, 2);

    Q.x = P.x - Al*((Al*P.x + Bl*P.y + Cl*P.z + Dl)/(pow(Al,2) + pow(Bl,2) + pow(Cl,2)));
    Q.y = P.y - Bl*((Al*P.x + Bl*P.y + Cl*P.z + Dl)/(pow(Al,2) + pow(Bl,2) + pow(Cl,2)));
    Q.z = P.z - Cl*((Al*P.x + Bl*P.y + Cl*P.z + Dl)/(pow(Al,2) + pow(Bl,2) + pow(Cl,2)));

    cout << "Coords of the projected point : " << endl;
    cout << Q.x << " " << Q.y << " " << Q.z << endl;
                                                  
    /*int Ns = 20;

    int NumSphere = Ns*Ns/2;
    const double AverageR = 50;
    const double AverageDistance = 60 ;
    double Sphere[NumSphere][4];



    double eps;
    int NumS = 0;
    for(int i=0; i<Ns; i++)
      for(int j=0; j<Ns/2; j++)
      {
        eps=rand() / (double)(RAND_MAX);
        //eps=(1-(double) i/Ns)*1.5;
        Sphere[NumS][0] = AverageDistance*i+eps*AverageR*0.0;
        Sphere[NumS][2] = AverageDistance*j+eps*AverageR*0.0;
        Sphere[NumS][1] = -AverageR+eps*AverageR*0.0+AverageR*sin(Sphere[NumS][0]/500+3.1415927/2)+eps*AverageR*0.0;   
        //(Sphere[NumS][0]/1000+3.1415927/2)
        Sphere[NumS][3] = AverageR+eps*AverageR*0.0;
        NumS++;

        cout << "Sphere coords: " << Sphere[NumS][0] << " " << Sphere[NumS][2] << " " << Sphere[NumS][1] << endl;
        cout << "Sphere Rad. : " << Sphere[NumS][3] << endl;

      }*/

  //euler angles

  //vect vert1(100, 0, 0), vert2(100, 0, 100), vert3(0 , 0, 100);
  //vect vert1(0, 0, 0), vert2(0, 0, 100), vert3(100 , 0, 0);

  //vect ab, ac;

  //axes

  //vect axz, axy, axx;

  //ab = vert2 - vert1;
  //ac = vert3 - vert1;
  
  //axy cannot have zero magintude as a result of triangulation (ab and ac can't be parallel)
  
  //axy = crossProd(ac, ab);

  //cout << "BLA :" << axy.x << " " << axy.y << " " << axy.z << endl;

  //if(axy.y < 0) axy.flip();

  //axx = crossProd(axy, ac);

  //axz = ac;

  //cout << "BLA2 :" << axy.x << " " << axy.y << " " << axy.z << endl;
    
  //orthonormal basis

  //axy.norm();  
  //axz.norm();
  //axx.norm();

  /* 

          |axx.x axx.y axx.z|
    rot = |axy.x axy.y axy.z|
          |axz.x axz.y axz.z|

  */

  //conversion from rotation matrix to euler angles

  //double eul[3];

  //eul[0] = atan2(axz.y, axz.z);
  //eul[1] = atan2(-axz.x, sqrt(pow(axz.y, 2) + pow(axz.z, 2)));       
  //eul[2] = atan2(axy.x, axx.x);

  /*if(axy.z > 0.998 || axy.z < -0.998){

    eul[0] = atan2(-axz.x, axx.x);
    eul[1] = 0;

  }
  else {

    eul[0] = atan2(axx.z, axz.z);
    eul[1] = atan2(axy.x, axy.y);  

  }

  eul[2] = asin(axy.z);*/

  //cout << "euler angles: " << endl;
  //cout << eul[0] << " " << eul[1] << " " << eul[2] << endl;

  //cout << "rot. matrices: " << endl;
  //cout << "[ " << axx.x  << " " << axx.y << " " << axx.z << " ]" << endl;
  //cout << "[ " << axy.x  << " " << axy.y << " " << axy.z << " ]" << endl;
  //cout << "[ " << axz.x  << " " << axz.y << " " << axz.z << " ]" << endl;  

    vect p(3.555, 10.566, 0), ll(0, 0, 0), k(5, 0, 0);

    vect mm = k - ll;
    vect nn = p - ll;

    mm.norm();

    vect midd = crossProd(mm, nn);

    double lengthFin = sqrt(pow(midd.x, 2) + pow(midd.y, 2) + pow(midd.z, 2));

    /*double length = sqrt(pow(k.x - ll.x, 2) + pow(k.y - ll.y, 2) + pow(k.z - ll.z, 2));

    vect st = k - ll;
    st.norm();

    vect tmpp1 = p - ll; 

    double t = dotProd(st, tmpp1)/length;
    
    vect project;

    project.x = ll.x + t*(st.x);
    project.y = ll.y + t*(st.y);
    project.z = ll.z + t*(st.z);
    
    double lengthFin = sqrt(pow(p.x - project.x, 2) + pow(p.y - project.y, 2) + pow(p.z - project.z, 2));*/

    cout << "lengthFin " << lengthFin << endl;   
    /*if((t > 0) && (t < length)){

      cout << "true" << endl;

    }
    else{

      cout << "false" << endl;

    }*/

    if(1){

      cout << "hello" << endl;

    }
    else if(1){

      cout << "helloooooooooo" << endl;

    }
    else{

      cout << "hellooooooooooooooooooooo" << endl;

    }


}





