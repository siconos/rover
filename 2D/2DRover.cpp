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
 * Contact: Vincent ACARY vincent.acary@inrialpes.fr 
 */


// =============================== Double Pendulum Example ===============================
// 
// Author: Vincent Acary
//
// Keywords: LagrangianDS, LagrangianLinear relation, Moreau TimeStepping, LCP. 
// 
// =============================================================================================

#include "SiconosKernel.hpp"
#include <stdlib.h>
using namespace std;

#include <boost/progress.hpp>

int main(int argc, char* argv[])
{
  try{
	
    // ================= Creation of the model =======================
    
    // User-defined main parameters 
    unsigned int nDof = 3;           // degrees of freedom for robot arm 
    double t0 = 0;                   // initial computation time
    double m=3;
    double T = 10.0;                   // final computation time 
    double h = 0.0005;                // time step
    double e = 0.3;                  // nslaw  
    double eps_n=0.7;
    double eps_t=0;
    double mu=0.6;
    double R=1.5;
    double g=9.8;
    double ls1,ls2;

    // -> mind to set the initial conditions below. 
    
    // -------------------------
    // --- Dynamical systems --- 
    // -------------------------
    SP::SiconosMatrix Mass(new SimpleMatrix(nDof,nDof));
    (*Mass)(0,0) = m;
    (*Mass)(1,1) = m;
    (*Mass)(2,2) = 3./5*m*R*R;
   
    // --- DS: Double Pendulum ---
    
    // Initial position (angles in radian)
    SP::SimpleVector q0(new SimpleVector(nDof));
    SP::SimpleVector v0(new SimpleVector(nDof));
    q0->zero(); v0->zero();
    (*q0)(0) = -2.5;
    (*q0)(1) = 1;
    (*q0)(2) = 0;
    
    // -- The dynamical system --
    SP::LagrangianLinearTIDS ball(new LagrangianLinearTIDS(q0,v0,Mass));

    // -- Set external forces (weight) --
    SP::SimpleVector weight(new SimpleVector(nDof));
    (*weight)(1) = -m*g;
    ball->setFExtPtr(weight);
    

    // -------------------
    // --- Interactions---
    // -------------------

    
    // -- relations --
    string G ="2DRoverPlugin:G0";
    SP::NonSmoothLaw nslaw(new NewtonImpactFrictionNSL(eps_n, eps_t, mu,2));
    //SP::NonSmoothLaw nslaw(new NewtonImpactNSL(e));     
    SP::Relation relation(new LagrangianScleronomousR("2DRoverPlugin:h0",G));
    SP::Interaction inter(new Interaction("floor-mass1", ball,1,2, nslaw, relation));
    //SP::Interaction inter(new Interaction(1, nslaw, relation));
    
    
    // -------------
    // --- Model ---
    // -------------

    SP::Model Pendulum(new Model(t0,T)); 
    

    // add the dynamical system in the non smooth dynamical system
    Pendulum->nonSmoothDynamicalSystem()->insertDynamicalSystem(ball);

    // link the interaction and the dynamical system
    Pendulum->nonSmoothDynamicalSystem()->link(inter,ball);
    // ----------------
    // --- Simulation ---
    // ----------------

    // -- Time discretisation --
    SP::TimeDiscretisation t(new TimeDiscretisation(t0,h));
 
    SP::TimeStepping s(new TimeStepping(t));
    //        s->setUseRelativeConvergenceCriteron(true);

    // -- OneStepIntegrators --   

    //double theta=0.500001;
    double theta=0.50000;

    SP::Moreau OSI(new Moreau(ball,theta));
    //OSI->insertDynamicalSystem(ball);
    s->insertIntegrator(OSI);

    // -- OneStepNsProblem --
    //SP::OneStepNSProblem osnspb(new LCP());
    SP::OneStepNSProblem osnspb(new FrictionContact(2));
    s->insertNonSmoothProblem(osnspb);

    cout << "=== End of model loading === " << endl;

    // =========================== End of model definition ===========================	dataPlot(k,7) = (*inter->y(0))(0);


    // ================================= Computation =================================

    // --- Simulation initialization ---
    Pendulum->initialize(s); 
    cout <<"End of simulation initialisation" << endl;
    
    int k = 0;
    int N = (int)((T-t0)/h)+1;
     cout << "Number of time step   " << N << endl;
    // --- Get the values to be plotted ---
    // -> saved in a matrix dataPlot
    unsigned int outputSize = 9;
    SimpleMatrix dataPlot(N+1,outputSize );
    // For the initial time step: 
    // time
    SP::SiconosVector q = ball->q();
    SP::SiconosVector v = ball->velocity();
    SP::SiconosVector lambda = inter->lambda(1);
    SP::SiconosVector y = inter->y(0);

    dataPlot(k,0) =  t0;
    dataPlot(k,1) = (*q)(0);
    dataPlot(k,2) = (*q)(1);
    dataPlot(k,6) = (*q)(2);
    dataPlot(k,3) = (*v)(0);
    dataPlot(k,4) = (*v)(1);
    ls1=dataPlot(k,3);
    ls2=dataPlot(k,4);
    dataPlot(k,5)=sqrt(ls1*ls1+ls2*ls2);
    dataPlot(k, 7) = (*lambda)(0);
    dataPlot(k, 8) = (*lambda)(1);
	
    boost::timer time;
    time.restart();

    // --- Time loop ---
    cout << "Start computation ... " << endl;

    boost::progress_display show_progress( N );
  
    while(k < N)
      {
	k++;
	++show_progress;
	//	if (!(div(k,1000).rem))  cout <<"Step number "<< k << "\n";
	
	// Solve problem
	s->computeOneStep();
       //s->newtonSolve(criterion,maxIter);
	// Data Output
	dataPlot(k, 0) =  s->nextTime();	
	dataPlot(k,1) = (*q)(0);
        dataPlot(k,2) = (*q)(1);
        dataPlot(k,6) = (*q)(2);
        dataPlot(k,3) = (*v)(0);
        dataPlot(k,4) = (*v)(1);
        ls1=dataPlot(k,3);
        ls2=dataPlot(k,4);
        dataPlot(k,5)=sqrt(ls1*ls1+ls2*ls2);
        //dataPlot(0, 7) = (*lambda)(0);
        dataPlot(k, 7) = (*lambda)(0);
        dataPlot(k, 8) = (*lambda)(1);

	s->nextStep();
      }
     
    cout<<"End of computation - Number of iterations done: "<<k<<endl;
    cout << "Computation Time " << time.elapsed()  << endl;  
    
    // --- Output files --- 
    ioMatrix out("2DRoverResult.dat", "ascii");
    out.write(dataPlot,"noDim");
    double *toto = (double *)malloc(1000*sizeof(double));
    toto = NULL;


  }
 
  catch(SiconosException e)
    {cout << e.report() << endl;}
  catch(...)
    {cout << "Exception caught in \'sample/MultiBeadsColumn\'" << endl;} 

  while(1) sleep(60);
}
