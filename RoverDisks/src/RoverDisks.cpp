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

/*!\file Rover.cpp

*/

// Siconos
#include <SiconosKernel.hpp>
#include <SiconosPointers.hpp>
#include "RoverDisks.hpp"
#include "Rover.hpp"

using namespace std;

/* do nothing if solver does not converge */
void localCheckSolverOuput(int, Simulation*)
{};

double A(double t)
{
  return 0. ;
}
double B(double t)
{
  return 1. ;
}
double C(double t)
{
  return 0. ;// return 1.1*cos(32.*M_PI*t) ;
}
double DA(double t)
{
  return 0. ;
}
double DB(double t)
{
  return 0. ;
}
double DC(double t)
{
  return 0. ; //return -1.1*32.*M_PI*sin(32.*M_PI*t) ;
}

// ================= Creation of the model =======================
void RoverDisks::init()
{

  SP::TimeDiscretisation timedisc_;
  SP::Simulation simulation_;
  SP::FrictionContact osnspb_;

  // User-defined main parameters

  double t0 = 0;                   // initial computation time

  double T = 0.02;

  double h = 0.02;                // time step previous initial 0.01
  double g = 9.81;

  double theta = 0.5;              // theta for Moreau integrator

  std::string solverName = "NSGS";

  // -----------------------------------------
  // --- Dynamical systems && interactions ---
  // -----------------------------------------

  unsigned int j;
  int interCounter=0;

  double R;
  double m;

  try
  {

    // ------------
    // --- Init ---
    // ------------

    std::cout << "====> Model loading ..." <<std::endl<<std::endl;

    double m1=130.; //100
    double m2=60; //70
    double R=20.0; //10
    double l=40.0;  //30
      // Initial position (angles in radian)
    SP::SimpleVector q0(new SimpleVector(5));
    SP::SimpleVector v0(new SimpleVector(5));
    q0->zero(); v0->zero();
    (*q0)(0) = 75; //300--255
    (*q0)(1) = 30.0;
    (*v0)(3) = 0.0;
    SP::Rover rover(new Rover(m1,m2,R,l,q0,v0));
    
    // -- external forces (weight) --
    SP::SimpleVector RoverFExt;
    RoverFExt.reset(new SimpleVector(5));
    RoverFExt->zero();
    RoverFExt->setValue(1, -m1*g - 2*m2*g);
    (*RoverFExt)(3) = 5000.0;
    (*RoverFExt)(4) = 5000.0;
    rover->get()->setFExtPtr(RoverFExt);

    
    _plans.reset(new SimpleMatrix("plans.dat",true));

    /* set center positions */
    for (unsigned int i = 0 ; i< _plans->size(0); ++i)
    {
      SP::DiskPlanR tmpr;
      tmpr.reset(new DiskPlanR(1,(*_plans)(i,0),(*_plans)(i,1),(*_plans)(i,2),
                               (*_plans)(i,3),(*_plans)(i,4),(*_plans)(i,5)));
      (*_plans)(i,3) = tmpr->getXCenter();
      (*_plans)(i,4) = tmpr->getYCenter();
    }

    _moving_plans.reset(new FMatrix(1,6));
    (*_moving_plans)(0,0) = &A;
    (*_moving_plans)(0,1) = &B;
    (*_moving_plans)(0,2) = &C;
    (*_moving_plans)(0,3) = &DA;
    (*_moving_plans)(0,4) = &DB;
    (*_moving_plans)(0,5) = &DC;



    SP::SiconosMatrix Disks;
    Disks.reset(new SimpleMatrix("disks1.dat",true));

    // -- OneStepIntegrators --
    SP::OneStepIntegrator osi;
    osi.reset(new Moreau(theta));
    
    // -- Model -- 
    _model.reset(new Model(t0,T));

    // add the dynamical system to the one step integrator
    osi->insertDynamicalSystem(rover->get());

    // add the dynamical system in the non smooth dynamical system
    _model->nonSmoothDynamicalSystem()->insertDynamicalSystem(rover->get());

    for (unsigned int i=0; i<Disks->size(0); i++)
    {
      R=Disks->getValue(i,2);
      m=Disks->getValue(i,3);

      SP::SimpleVector qTmp;
      SP::SimpleVector vTmp;

      qTmp.reset(new SimpleVector(3));
      vTmp.reset(new SimpleVector(3));
      vTmp->zero();
      (*qTmp)(0) = (*Disks)(i,0);
      (*qTmp)(1) = (*Disks)(i,1);

      SP::LagrangianDS body;
      if (R>0)
        body.reset(new Disk(R, m, qTmp, vTmp));
      else
        body.reset(new Circle(-R, m, qTmp, vTmp));

       // -- external forces (weight) --
      SP::SimpleVector FExt;
      FExt.reset(new SimpleVector(3));
      FExt->zero();
      FExt->setValue(1, -m*g);
      body->setFExtPtr(FExt);

      // add the dynamical system to the one step integrator
      osi->insertDynamicalSystem(body);

      // add the dynamical system in the non smooth dynamical system
      _model->nonSmoothDynamicalSystem()->insertDynamicalSystem(body);

    }

    

    // ------------------
    // --- Simulation ---
    // ------------------

    // -- Time discretisation --
    timedisc_.reset(new TimeDiscretisation(t0,h));
  
    // -- OneStepNsProblem --
    osnspb_.reset(new FrictionContact(2));

    osnspb_->numericsSolverOptions()->iparam[0]=100; // Max number of
    // iterations
    osnspb_->numericsSolverOptions()->iparam[1]=20;  // compute error
    // iterations
    osnspb_->numericsSolverOptions()->dparam[0]=1e-3;// Tolerance


    osnspb_->setMaxSize(16384);
    osnspb_->setMStorageType(0);            // Sparse storage
    osnspb_->setNumericsVerboseMode(0);

    osnspb_->setKeepLambdaAndYState(true);  // inject previous solution

    

    // -- Simulation --
    simulation_.reset(new TimeStepping(timedisc_));
    
    simulation_->insertIntegrator(osi);
   
    simulation_->insertNonSmoothProblem(osnspb_);
 
    //simulation_->setCheckSolverFunction(localCheckSolverOuput);

    // --- Simulation initialization ---

    std::cout <<"====> Simulation initialisation ..." <<std::endl<<std::endl;

    SP::NonSmoothLaw nslaw(new NewtonImpactFrictionNSL(0,0,0.5,2));

    _playground.reset(new SpaceFilter(3,6,_model->nonSmoothDynamicalSystem(),nslaw,_plans, _moving_plans));

    _model->initialize(simulation_);

  }

  catch (SiconosException e)
  {
    std::cout << e.report() << std::endl;
    exit(1);
  }
  catch (...)
  {
    std::cout << "Exception caught in Disks::init()" << std::endl;
    exit(1);
  }
}





// =========================== End of model definition ===========================

// ================================= Computation =================================

void RoverDisks::compute()
{
  try
  {

    _playground->buildInteractions(_model->currentTime());

    _model->simulation()->updateInteractions();

    _model->simulation()->advanceToEvent();

    _model->simulation()->processEvents();

  }

  catch (SiconosException e)
  {
    std::cout << e.report() << std::endl;
  }
  catch (...)
  {
    std::cout << "Exception caught in SiconosBodies::compute()" << std::endl;
  }
}
