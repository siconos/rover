/* Siconos-sample version 3.0.0, Copyright INRIA 2005-2008.
 * Siconos is a program dedicated to modeling, simulation and control
 * of non smooth dynamical systems.	
 * Siconos is a free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * Siconos is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Siconos; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Simulation of Rover on the Plane with incline
 *
 *
 * Contact: Vincent ACARY vincent.acary@inrialpes.fr 
 */


#include "Robot.h"
#include "SiconosKernel.hpp"
#include <stdlib.h>
using namespace std;

#include <boost/progress.hpp>

int main(int argc, char* argv[])
{
  try{
	
    // ================= Creation of the model =======================
    
    // User-defined main parameters 
    unsigned int nDof = 21;           // degrees of freedom for robot rover_ds 
    double t0 = 0;                    // initial computation time
    double T = 5.;                    // final computation time 
    double h = 0.005;                  // time step
    double eps_n=0.3;                 
    double eps_t=0.0;
    double mu=0.7;
    double RAngle[3]= {0.1,0.0,0.1}; //Format of RAngle: Euler angles (alpha,beta,gamma)


    // -> mind to set the initial conditions below. 
    
    // -------------------------
    // --- Dynamical systems --- 
    // -------------------------
    // --- DS: Rover ---
    
    // Initial position (angles in radian)
    SP::SiconosVector q0(new SiconosVector(nDof));
    SP::SiconosVector v0(new SiconosVector(nDof));
    q0->zero(); v0->zero();
    (*q0)(4) = 0;
    (*q0)(1) = 95.5;
    (*q0)(7) = -0.1;      // angle of turning aixls of front left wheel (FL)
    (*q0)(8) = -0.1;      // angle of turning aixls of front right wheel (FR)
    //(*q0)(6) = 0.0;
    
    SP::LagrangianDS rover_ds(new LagrangianDS(q0, v0));
    // external plug-in
    rover_ds->setComputeMassFunction("RobotPlugin.so","mass");
  
    // -- Set external forces (Driving force of Wheels) --
    SP::SiconosVector force(new SiconosVector(nDof));
    (*force)(9) = 2000;   //FL  Driving force
    (*force)(10) = 2000;  //FR  Driving force
    (*force)(14) = 2000;  //ML  Driving force
    (*force)(15) = 2000;  //BL  Driving force
    (*force)(19) = 2000;  //MR  Driving force
    (*force)(20) = 2000;  //BR  Driving force   

    rover_ds->setFExtPtr(force);
 
    rover_ds->setComputeFGyrFunction("RobotPlugin.so","FGyr");
    rover_ds->setComputeJacobianFGyrqFunction("RobotPlugin.so","jacobianFGyrq");
    rover_ds->setComputeJacobianFGyrqDotFunction("RobotPlugin.so","jacobianVFGyr");
    rover_ds->setComputeFIntFunction("RobotPlugin.so","U");
    rover_ds->setComputeJacobianFIntqFunction("RobotPlugin.so","jacobFintQ");
    rover_ds->setComputeJacobianFIntqDotFunction("RobotPlugin.so","jacobFintV");

    // -------------
    // --- Model ---
    // -------------

    SP::Model Rover(new Model(t0,T)); 
    Rover->nonSmoothDynamicalSystem()->insertDynamicalSystem(rover_ds);
    // -------------------
    // --- Interactions---
    // -------------------
    // -- relations --
    string G ="RobotPlugin:G0";
    SP::NonSmoothLaw nslaw(new NewtonImpactFrictionNSL(eps_n, eps_t, mu,3));   
    SP::Relation relation(new LagrangianScleronomousR("RobotPlugin:h0",G));
    SP::Interaction inter(new Interaction(3, nslaw, relation));
    // link the interaction and the dynamical system
    Rover->nonSmoothDynamicalSystem()->link(inter, rover_ds);

    string G1 ="RobotPlugin:G1";
    SP::NonSmoothLaw nslaw1(new NewtonImpactFrictionNSL(eps_n, eps_t,mu,3)); 
    SP::Relation relation1(new LagrangianScleronomousR("RobotPlugin:h1",G1));
    SP::Interaction inter1(new Interaction(3, nslaw1, relation1));
    Rover->nonSmoothDynamicalSystem()->link(inter1, rover_ds);

    string G2 ="RobotPlugin:G2";
    SP::NonSmoothLaw nslaw2(new NewtonImpactFrictionNSL(eps_n, eps_t, mu,3));
    SP::Relation relation2(new LagrangianScleronomousR("RobotPlugin:h2",G2));
    SP::Interaction inter2(new Interaction(3, nslaw2, relation2));
    Rover->nonSmoothDynamicalSystem()->link(inter2, rover_ds);
    
    string G3 ="RobotPlugin:G3";
    SP::NonSmoothLaw nslaw3(new NewtonImpactFrictionNSL(eps_n, eps_t, mu,3));    //BL
    SP::Relation relation3(new LagrangianScleronomousR("RobotPlugin:h3",G3));
    SP::Interaction inter3(new Interaction(3, nslaw3, relation3));
    Rover->nonSmoothDynamicalSystem()->link(inter3, rover_ds);
    
    string G4 ="RobotPlugin:G4";
    SP::NonSmoothLaw nslaw4(new NewtonImpactFrictionNSL(eps_n, eps_t, mu,3));   
    SP::Relation relation4(new LagrangianScleronomousR("RobotPlugin:h4",G4));
    SP::Interaction inter4(new Interaction(3, nslaw4, relation4));
    Rover->nonSmoothDynamicalSystem()->link(inter4, rover_ds);

    string G5 ="RobotPlugin:G5";
    SP::NonSmoothLaw nslaw5(new NewtonImpactFrictionNSL(eps_n, eps_t, mu,3));   //BR
    SP::Relation relation5(new LagrangianScleronomousR("RobotPlugin:h5",G5));
    SP::Interaction inter5(new Interaction(3, nslaw5, relation5));
    Rover->nonSmoothDynamicalSystem()->link(inter5, rover_ds);
    
    // ----------------
    // --- Simulation ---
    // ----------------
    // -- OneStepIntegrators --
    //double theta=0.500001;
    double theta=0.50000001;

    SP::MoreauJeanOSI OSI(new MoreauJeanOSI(theta));

    // -- Time discretisation --
    SP::TimeDiscretisation t(new TimeDiscretisation(t0,h));
 
    // -- OneStepNsProblem --
    SP::OneStepNSProblem osnspb(new FrictionContact(3));
    osnspb->numericsSolverOptions()->iparam[SICONOS_IPARAM_MAX_ITER]=10000; // Max number of
                                                      // iterations
    osnspb->numericsSolverOptions()->iparam[1]=10000;  // compute error
    // iterations
    //osnspb->numericsSolverOptions()->iparam[4]=1;   // projection
    // Solver/formulation  0: projection, 1: Newton/AlartCurnier, 2: Newton/Fischer-Burmeister
    osnspb->numericsSolverOptions()->dparam[SICONOS_DPARAM_TOL]=1e-5;// Tolerance
    //osnspb->numericsSolverOptions()->dparam[2]=1e-5;// Local tolerance
    osnspb->numericsSolverOptions()->internalSolvers->dparam[SICONOS_DPARAM_TOL]=1e-5;
    SP::TimeStepping s(new TimeStepping(t, OSI, osnspb));
    Rover->setSimulation(s);

    //        s->setUseRelativeConvergenceCriteron(true);
    cout << "=== End of model loading === " << endl;

    // ================================= Computation =================================

    // --- Simulation initialization ---
    cout << "=== Simulation initialization ===" << endl;
    Rover->initialize(); 
    cout <<"End of initialisation" << endl;
    unsigned int i=0;
    int k=0;
    int N = (int)((T-t0)/h); //+1
    cout << "Number of time step   " << N << endl;
    // --- Get the values to be plotted ---
    // -> saved in a matrix dataPlot
    SimpleMatrix dataPlot(N+1,nDof+17);
    
    double qq[21];
    double Test[69];
 
    SimpleMatrix testdatabase(N+1,18);

    SP::SiconosVector q = rover_ds->q();
    SP::SiconosVector v = rover_ds->velocity();
    SP::SiconosVector yfunc = inter->y(0);
    SP::SiconosVector yfunc1 = inter1->y(0);
    SP::SiconosVector yfunc2 = inter2->y(0);
    SP::SiconosVector yfunc3 = inter3->y(0);
    SP::SiconosVector yfunc4 = inter4->y(0);
    SP::SiconosVector yfunc5 = inter5->y(0);
    SP::SiconosVector lambda = inter1->lambda(1);

    dataPlot(k,0)= t0;
    dataPlot(k,1)=(*q)(0)/100;
    dataPlot(k,2)=(*q)(1)/100;
    dataPlot(k,3)=(*q)(2)/100;
    dataPlot(k,4)=(*q)(3);
    dataPlot(k,5)=(*q)(4);
    dataPlot(k,6)=(*q)(5);
    dataPlot(k,7)=(*q)(6);
    dataPlot(k,8)=(*q)(7);
    dataPlot(k,9)=(*q)(8);
    dataPlot(k,10)= (*q)(9);
    dataPlot(k,11)=(*q)(10);
    dataPlot(k,12)=(*q)(11);
    dataPlot(k,13)=(*q)(12);
    dataPlot(k,14)=(*q)(13);
    dataPlot(k,15)=(*q)(14);
    dataPlot(k,16)=(*q)(15);
    dataPlot(k,17)=(*q)(16);
    dataPlot(k,18)=(*q)(17);
    dataPlot(k,19)=(*q)(18);
    dataPlot(k,20)=(*q)(19);
    dataPlot(k,21)=(*q)(20); 
    dataPlot(k,22)=(*v)(0);
    dataPlot(k,23)=(*v)(1);
    dataPlot(k,24)=(*v)(2);
    dataPlot(k,25)=(*yfunc)(0);
    dataPlot(k,26)=(*yfunc1)(0);
    dataPlot(k,27)=(*yfunc2)(0);
    dataPlot(k,28)=(*yfunc3)(0);
    dataPlot(k,29)=(*yfunc4)(0);
    dataPlot(k,30)=(*yfunc5)(0);
    dataPlot(k,31)=(*lambda)(0);
    dataPlot(k,32)=(*v)(9);
    dataPlot(k,33)=(*v)(10);
    dataPlot(k,34)=(*v)(14);
    dataPlot(k,35)=(*v)(15);
    dataPlot(k,36)=(*v)(19);
    dataPlot(k,37)=(*v)(20);

    //----------------------gnuplot data----------------************************ 
    i=0;
    while(i < nDof)
      {  
	qq[i]=(*q)(i);
	i++;
      }
    Tags(Test ,qq);
    testdatabase(k,0)= Test[4];
    testdatabase(k,1)= Test[27];
    testdatabase(k,2)= Test[50];  //FL
    testdatabase(k,3)= Test[5];
    testdatabase(k,4)= Test[28];
    testdatabase(k,5)= Test[51];  //FR
    testdatabase(k,6)= Test[9];
    testdatabase(k,7)= Test[32];  
    testdatabase(k,8)= Test[55];  //ML
    testdatabase(k,9)= Test[10];
    testdatabase(k,10)= Test[33];
    testdatabase(k,11)= Test[56];  //BL
    testdatabase(k,12)= Test[14];
    testdatabase(k,13)= Test[37];
    testdatabase(k,14)= Test[60];  //BR
    testdatabase(k,15)= Test[15];
    testdatabase(k,16)= Test[38];
    testdatabase(k,17)= Test[61];
    //--------------------------------------------------
   

    //-------------------------------------------************************

    boost::timer time;
    time.restart();
    // --- Time loop ---
    cout << "Start computation ... " << endl;

    boost::progress_display show_progress( N );
  
    while(s->hasNextEvent())
      {
	osnspb->setNumericsVerboseMode(0); 
       
	k++;
	++show_progress;
	//	if (!(div(k,1000).rem))  cout <<"Step number "<< k << "\n";
	
	// Solve problem
	s->computeOneStep();
	//s->newtonSolve(criterion,maxIter);
	// Data Output
	//cout << "k value ..ak2. " << k << endl;

	dataPlot(k, 0) =  s->nextTime();
   
	dataPlot(k,1)=(*q)(0)/100;
	dataPlot(k,2)=(*q)(1)/100;
	dataPlot(k,3)=(*q)(2)/100;
	dataPlot(k,4)=(*q)(3);
	dataPlot(k,5)=(*q)(4);
	dataPlot(k,6)=(*q)(5);
	dataPlot(k,7)=(*q)(6);
	dataPlot(k,8)=(*q)(7);
	dataPlot(k,9)=(*q)(8);
	dataPlot(k,10)=(*q)(9);
	dataPlot(k,11)=(*q)(10);
	dataPlot(k,12)=(*q)(11);
	dataPlot(k,13)=(*q)(12);
	dataPlot(k,14)=(*q)(13);
	dataPlot(k,15)=(*q)(14);
	dataPlot(k,16)=(*q)(15);
	dataPlot(k,17)=(*q)(16);
	dataPlot(k,18)=(*q)(17);
	dataPlot(k,19)=(*q)(18);
	dataPlot(k,20)=(*q)(19);
	dataPlot(k,21)=(*q)(20);
	dataPlot(k,22)=(*v)(0);
	dataPlot(k,23)=(*v)(1);
	dataPlot(k,24)=(*v)(2);
	dataPlot(k,25)=(*yfunc)(0);
	dataPlot(k,26)=(*yfunc1)(0);
	dataPlot(k,27)=(*yfunc2)(0);
	dataPlot(k,28)=(*yfunc3)(0);
	dataPlot(k,29)=(*yfunc4)(0);
	dataPlot(k,30)=(*yfunc5)(0);
	dataPlot(k,31)=(*lambda)(0);
	dataPlot(k,32)=(*v)(9);
	dataPlot(k,33)=(*v)(10);
	dataPlot(k,34)=(*v)(14);
	dataPlot(k,35)=(*v)(15);
	dataPlot(k,36)=(*v)(19);
	dataPlot(k,37)=(*v)(20);
	//-------------------gnuplot ------------------*********************
	i=0;
	while(i < nDof)
	  {  
	    qq[i]=(*q)(i);
	    i++;
	  }
	Tags(Test,qq);
   
	testdatabase(k,0)= Test[4];
	testdatabase(k,1)= Test[27];
	testdatabase(k,2)= Test[50];  //FL
	testdatabase(k,3)= Test[5];
	testdatabase(k,4)= Test[28];
	testdatabase(k,5)= Test[51];  //FR
	testdatabase(k,6)= Test[9];
	testdatabase(k,7)= Test[32];  
	testdatabase(k,8)= Test[55];  //ML
	testdatabase(k,9)= Test[10];
	testdatabase(k,10)= Test[33];
	testdatabase(k,11)= Test[56];  //BL
	testdatabase(k,12)= Test[14];
	testdatabase(k,13)= Test[37];
	testdatabase(k,14)= Test[60];  //BR
	testdatabase(k,15)= Test[15];
	testdatabase(k,16)= Test[38];
	testdatabase(k,17)= Test[61];
   
	//--------------------------------------------------
   
	//----------------------------------------------------**********************

	s->nextStep();
      }
     
    cout<<"End of computation - Number of iterations done: "<<k<<endl;
    cout << "Computation Time " << time.elapsed()  << endl;  



    // --- Output files --- 
    cout<<"====> Output file writing ..."<<endl;
    const char *Names[17]={
      "DEF Rover_RootRotInterp OrientationInterpolator{\n",
      "DEF Rover_body_jointRotInterp OrientationInterpolator{\n",
      "DEF Rover_l_pendulum_jointRotInterp OrientationInterpolator{\n",
      "DEF Rover_lf_wheelAxis_jointRotInterp OrientationInterpolator{\n",
      "DEF Rover_lf_wheel_jointRotInterp OrientationInterpolator{\n",
      "DEF Rover_lm_wheelAxis_jointRotInterp OrientationInterpolator{\n",
      "DEF Rover_lm_wheel_jointRotInterp OrientationInterpolator{\n",
      "DEF Rover_r_pendulum_jointRotInterp OrientationInterpolator{\n",
      "DEF Rover_rf_wheelAxis_jointRotInterp OrientationInterpolator{\n",
      "DEF Rover_rf_wheel_jointRotInterp OrientationInterpolator{\n",
      "DEF Rover_rm_wheelAxis_jointRotInterp OrientationInterpolator{\n",
      "DEF Rover_rm_wheel_jointRotInterp OrientationInterpolator{\n",
      "DEF Rover_b_pendulum_jointRotInterp OrientationInterpolator{\n",
      "DEF Rover_br_wheelAxis_jointRotInterp OrientationInterpolator{\n",
      "DEF Rover_br_wheel_jointRotInterp OrientationInterpolator{\n",
      "DEF Rover_bl_wheelAxis_jointRotInterp OrientationInterpolator{\n",
      "DEF Rover_bl_wheel_jointRotInterp OrientationInterpolator{\n"};


    const char *NamesRotationVector[17]={
      "Rover_RootRotInterp OrientationInterpolator{\n",
      "Rover_body_jointRotInterp OrientationInterpolator{\n",
      "1 0 0",       //DEF Rover_l_pendulum_jointRotInterp
      "0 -1 0",       //DEF Rover_lf_wheelAxis_jointRotInterp
      "1 0 0",	//DEF Rover_lf_wheel_jointRotInterp
      "0 -1 0",	//DEF Rover_lm_wheelAxis_jointRotInterp
      "1 0 0",	//DEF Rover_lm_wheel_jointRotInterp
      "1 0 0",	//DEF Rover_r_pendulum_jointRotInterp
      "0 -1 0",	//DEF Rover_rf_wheelAxis_jointRotInterp
      "1 0 0",	//DEF Rover_rf_wheel_jointRotInterp
      "0 -1 0",	//DEF Rover_rm_wheelAxis_jointRotInterp
      "1 0 0",	//DEF Rover_rm_wheel_jointRotInterp
      "0 0 1",	//DEF Rover_b_pendulum_jointRotInterp
      "0 -1 0",	//DEF Rover_br_wheelAxis_jointRotInterp
      "1 0 0",	//DEF Rover_br_wheel_jointRotInterp
      "0 -1 0",	//DEF Rover_bl_wheelAxis_jointRotInterp
      "1 0 0"	};	//DEF Rover_bl_wheel_jointRotInterp

    int NamesDOF[17];
    NamesDOF[0]=0;
    NamesDOF[1]=0;
    NamesDOF[2]=12;
    NamesDOF[3]=14;
    NamesDOF[4]=16;
    NamesDOF[5]=13;
    NamesDOF[6]=15;
    NamesDOF[7]=17;
    NamesDOF[8]=19;
    NamesDOF[9]=21;
    NamesDOF[10]=18;
    NamesDOF[11]=20;
    NamesDOF[12]=7;
    NamesDOF[13]=9;
    NamesDOF[14]=11;
    NamesDOF[15]=8;
    NamesDOF[16]=10;

    double RootRotationVector[4];
    double PlaneRotationVector[4];

  
    FILE * pFile;
    pFile = fopen ("data.wrl","w");

    //---------------floor---------------------

    fprintf(pFile,"DEF FLOOR Transform {\n"); 
    fprintf(pFile,"translation ");
    fprintf(pFile,"%e %e %e\n", 0.0,-0.0, 0.0);
    fprintf(pFile,"rotation ");
    qq[0] = 0;
    PRV(PlaneRotationVector,RAngle,qq);
    if (PlaneRotationVector[3]==0)
      {fprintf(pFile,"%e %e %e %e\n",0.0,0.0,0.0,0.0);}
    else
      {fprintf(pFile,"%e %e %e %e\n",PlaneRotationVector[0],PlaneRotationVector[1],PlaneRotationVector[2],PlaneRotationVector[3]);}


    fprintf(pFile,"children [\n Shape {\n appearance Appearance {\n material Material { diffuseColor 0 1 1 }}\n");
    fprintf(pFile,"geometry Box { size 70 0.05 70 }");
    fprintf(pFile,"}\n]\n}\n");

    //fprintf(pFile,"DEF FLOORCompare Transform {\n"); 
    //fprintf(pFile,"translation ");
    //fprintf(pFile,"%e %e %e\n", 0.0, -10, 0.0);
   
    //fprintf(pFile,"children [\n Shape {\n appearance Appearance {\n material Material { diffuseColor 0 0 1 }}");
    //fprintf(pFile,"geometry Box { size 20 0.05 30 }");
    //fprintf(pFile,"}\n]\n}\n");



    //----------------Animation------------------
    fprintf(pFile,"DEF Animation Group {\n  children [\n");
    fprintf(pFile,"\n");

    fprintf(pFile,"DEF Rover_RootPosInterp PositionInterpolator{\n");
    fprintf(pFile,"    key [ 0 ");
    for (int cmp =1;cmp <= N;cmp++){
      fprintf(pFile,",%e",(dataPlot(cmp,0)-t0)/(T-t0));}
	
    fprintf(pFile,"]\n"); 
    fprintf(pFile,"    keyValue [  ");
    fprintf(pFile,"%e %e %e,\n",dataPlot(0,1),dataPlot(0,2),dataPlot(0,3));
    for (int cmp =1;cmp <= N;cmp++){
        
      fprintf(pFile,"%e %e %e,\n",-dataPlot(cmp,3),dataPlot(cmp,2),-dataPlot(cmp,1));}

    fprintf(pFile,"  ]\n}\n");

    // ----------root oritation--------------
    fprintf(pFile,"DEF Rover_RootRotInterp OrientationInterpolator{\n");
    fprintf(pFile,"    key [ 0 ");
    for (int cmp =1;cmp <= N;cmp++){
      fprintf(pFile,",%e",(dataPlot(cmp,0)-t0)/(T-t0));}
	
    fprintf(pFile,"]\n"); 
    fprintf(pFile,"    keyValue [  ");

    i = 0;
    while(i < nDof)
      {  
	qq[i]=dataPlot(0,i+1);
	i++;
      } 
    RRV(RootRotationVector,RAngle,qq);
    if (RootRotationVector[3]==0 )
      {fprintf(pFile,"%e %e %e %e,\n",0.0,0.0,0.0,0.0);}
    else
      {fprintf(pFile,"%e %e %e %e,\n",RootRotationVector[2], RootRotationVector[1], RootRotationVector[0],RootRotationVector[3]);}
   
    for (int cmp =1;cmp <= N;cmp++){
      i = 0;
      while(i < nDof)
	{  
	  qq[i]=dataPlot(cmp,i+1);
          i++;
	} 
      RRV(RootRotationVector,RAngle,qq);
      if (RootRotationVector[3]==0 )
	{fprintf(pFile,"%e %e %e %e,\n",0.0,0.0,0.0,0.0);}
      else
	{fprintf(pFile,"%e %e %e %e,\n",RootRotationVector[2], RootRotationVector[1], RootRotationVector[0],RootRotationVector[3]);}
    }
    

    fprintf(pFile,"  ]\n}\n");

    //---------segment rotation----------------
    for (int CountN=2; CountN<=16; CountN++){
    
      fprintf(pFile, "%s", Names[CountN]);
      fprintf(pFile,"    key [ 0 ");
      for (int cmp =1;cmp <= N;cmp++){
        fprintf(pFile,",%e",(dataPlot(cmp,0)-t0)/(T-t0));}
	
      fprintf(pFile,"]\n"); 
      fprintf(pFile,"    keyValue [  ");
      fprintf(pFile, "%s", NamesRotationVector[CountN]);
      fprintf(pFile," %e,\n",dataPlot(0,NamesDOF[CountN]));

      for (int cmp =1;cmp <= N;cmp++){
	fprintf(pFile, "%s", NamesRotationVector[CountN]);
	fprintf(pFile," %e,\n",dataPlot(cmp,NamesDOF[CountN]));}

      fprintf(pFile,"  ]\n}\n");
    }
    //fprintf(pFile,"  ]\n}\n");
    fclose(pFile);
    //system("cat RoverModel.wrl data.wrl RoverAnimation.wrl > run.wrl");


    // --- Output files --- 
    ioMatrix::write("RoverPlane.dat", "ascii",
		    dataPlot,"noDim");
    ioMatrix::write("TAGSDATA.dat", "ascii",
		    testdatabase,"noDim");
  }
	
  catch(SiconosException e)
    {cout << e.report() << endl;}
  catch(...)
    {cout << "Exception caught in \'sample/MultiBeadsColumn\'" << endl;}
}
