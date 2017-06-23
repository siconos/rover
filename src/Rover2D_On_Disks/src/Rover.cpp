#include "Rover.hpp"

Rover::Rover(double m1, double m2, double R, double l,
             SP::SimpleVector q0, SP::SimpleVector v0)
{
  zeroPlugin();
  
  _l = l;
  _R = R;
  _ndof = 5;
  
  SP::SiconosMatrix Mass(new SimpleMatrix(5,5));
  (*Mass)(0,0) = m1+2*m2;
  (*Mass)(1,1) = m1+2*m2;
  (*Mass)(2,2) = 0.333*m1*R*R+2*l*l*m2;
  (*Mass)(3,3) = 0.5*m2*R*R;
  (*Mass)(4,4) = 0.5*m2*R*R;

  _mass = Mass;
  
  // Initial conditions 
  _q0=q0;
  _velocity0=v0;

  // Current state
  _q.resize(3);
  _q[0].reset(new SimpleVector(*_q0)); 
  _q[1].reset(new SimpleVector(*_velocity0));
  _q[2].reset(new SimpleVector(_ndof));
  _residuFree.reset(new SimpleVector(getDim()));

  _p.resize(3);

  _z.reset(new SimpleVector(2));
  _z->setValue(0,_R);
  _z->setValue(1,_l);
}


struct HashedRover : public Hashed
{
  SP::Rover body;
  HashedRover(SP::Rover r, int i, int j) 
    : Hashed(r, i , j) {};
};

TYPEDEF_SPTR(HashedRover);



void Rover::selfHash(SP::SpaceFilter sf)
{
  int i,j,imin,imax,jmin,jmax;
    
  unsigned int _bboxfactor = sf->bboxfactor();
  unsigned int _cellsize = sf->cellsize();
    
  imin=(int) floor((get()->q()->getValue(0) - _l*cos(get()->q()->getValue(2))-_bboxfactor*_R)/_cellsize);
  imax=(int) floor((get()->q()->getValue(0) - _l*cos(get()->q()->getValue(2))+ _bboxfactor*_R)/_cellsize);
            
  jmin=(int) floor((get()->q()->getValue(1) - _l*sin(get()->q()->getValue(2))- _bboxfactor*_R)/_cellsize);
  jmax=(int) floor((get()->q()->getValue(1) - _l*sin(get()->q()->getValue(2))+ _bboxfactor*_R)/_cellsize);
    
  for (i=imin;i<=imax;++i) 
  {
    for (j=jmin;j<=jmax;++j) 
    {
      SP::HashedRover hrover(new HashedRover(get(), i, j));
      sf->insert(hrover);
    }
  }

  imin=(int) floor((get()->q()->getValue(0) + _l*cos(get()->q()->getValue(2))- _bboxfactor*_R)/_cellsize);
  imax=(int) floor((get()->q()->getValue(0) + _l*cos(get()->q()->getValue(2))+  _bboxfactor*_R)/_cellsize);
  
  jmin=(int) floor((get()->q()->getValue(1) + _l*sin(get()->q()->getValue(2))- _bboxfactor*_R)/_cellsize);
  jmax=(int) floor((get()->q()->getValue(1) + _l*sin(get()->q()->getValue(2))+ _bboxfactor*_R)/_cellsize);
  
  for (i=imin;i<=imax;++i) 
  {
    for (j=jmin;j<=jmax;++j) 
    {
      SP::HashedRover hrover(new HashedRover(boost::static_pointer_cast<Rover>(shared_from_this()), i, j));
      sf->insert(hrover);
    }
  }
  
};

struct Rover::RoverFilter : public SiconosVisitor
{
  SP::Rover rover;
  SP::SpaceFilter parent;

  RoverFilter(SP::SpaceFilter parent, SP::Rover rover) 
    : parent(parent), rover(rover)
  {};

  void visit(SP::Disk ds2)
  {
    SP::Relation rel1;
    SP::Relation rel2;
    
    SP::DynamicalSystemsGraph DSG0 = parent->nsds()->topology()->dSG(0);

    double r2 = ds2->getRadius();

    double xa = rover->get()->q()->getValue(0) - rover->_l*cos(rover->get()->q()->getValue(2));
    double ya = rover->get()->q()->getValue(1) - rover->_l*sin(rover->get()->q()->getValue(2));

    double xb = rover->get()->q()->getValue(0) + rover->_l*cos(rover->get()->q()->getValue(2));
    double yb = rover->get()->q()->getValue(1) + rover->_l*sin(rover->get()->q()->getValue(2));
      
    double x2 = ds2->q()->getValue(0);
    double y2 = ds2->q()->getValue(1);
    double rmax = fmax(rover->_R,r2);
    double d = fmin(hypot(xa-x2,ya-y2),hypot(xb-x2,yb-y2));

    if (d-rover->_R-r2<rmax)
    {
      rel1.reset(new LagrangianScleronomousR("RoverPlugin:h5","RoverPlugin:G5"));
      rel2.reset(new LagrangianScleronomousR("RoverPlugin:h6","RoverPlugin:G6"));
      //rel1.reset(new LagrangianScleronomousR("RoverPlugin:statich5","RoverPlugin:staticG5"));
      //rel2.reset(new LagrangianScleronomousR("RoverPlugin:statich6","RoverPlugin:staticG6"));
      
      assert(ds2->z()->size()==1);
      ds2->z()->setValue(0,ds2->getRadius());
    }
    
    if (rel1 && rel2)
    {

      bool found = false;
      DynamicalSystemsGraph::OEIterator oei,oeiend;
      for (boost::tie(oei,oeiend) = DSG0->out_edges(DSG0->descriptor(rover->get()));
           oei!=oeiend; ++oei)
      {
        if (DSG0->bundle(DSG0->target(*oei)) == ds2)
        {
          found = true;
          break;
        }
      }
      
      if(!found)
      { SP::NonSmoothLaw nslawrover(new NewtonImpactFrictionNSL(0,0,0.9,2));
        SP::Interaction inter1(new Interaction(2, 
                                               nslawrover,
                                               rel1, parent->newInteractionId()));
        SP::Interaction inter2(new Interaction(2, 
                                               nslawrover,
                                               rel2, parent->newInteractionId()));
        /*
        SP::Interaction inter1(new Interaction(2, 
                                               parent->nslaw(),
                                               rel1, parent->newInteractionId()));
        SP::Interaction inter2(new Interaction(2, 
                                               parent->nslaw(),
                                               rel2, parent->newInteractionId()));*/
        inter1->insert(rover);
        inter1->insert(ds2);
        inter2->insert(rover);
        inter2->insert(ds2);
        parent->nsds()->topology()->insertInteraction(inter1);
        parent->nsds()->topology()->insertInteraction(inter2);
      }
    }
    else
    {
        // are the two interactions in graph ?
      DynamicalSystemsGraph::OEIterator oei,oeiend;
      SP::Interaction int1, int2;
      bool first = true;
      
      for (boost::tie(oei,oeiend) = DSG0->out_edges(DSG0->descriptor(rover));
           oei!=oeiend; ++oei)
      {
        if (DSG0->bundle(DSG0->target(*oei)) == ds2)
        {
          if (first)
          {
            int1 = DSG0->bundle(*oei)->interaction();
            first = false;
          }
          else
          {
            int2 =  DSG0->bundle(*oei)->interaction();
            break;
          }
        }
      }
      
      
      if (!first)
      {
        assert (int1);

        assert (int2);
          
        parent->nsds()->topology()->removeInteraction(int1);
        parent->nsds()->topology()->removeInteraction(int2);
      }
      
    }    
    
  }
};

  
void Rover::selfFindInteractions(SP::SpaceFilter sf)
{


  typedef std::pair<int,int> interPair;
  typedef std::tr1::unordered_multiset<interPair, 
    boost::hash<interPair> > interPairs;
  
  // interactions with plans not for the moment

  SP::SiconosVector Q1 = get()->q();
    
  double x1 = Q1->getValue(0);
  double y1 = Q1->getValue(1);

  unsigned int _bboxfactor = sf->bboxfactor();
  unsigned int _cellsize = sf->cellsize();

  int imin1=(int) floor((get()->q()->getValue(0) - _l*cos(get()->q()->getValue(2))- _bboxfactor*_R)/_cellsize);
  int imax1=(int) floor((get()->q()->getValue(0) - _l*cos(get()->q()->getValue(2))+ _bboxfactor*_R)/_cellsize);
            
  int jmin1=(int) floor((get()->q()->getValue(1) - _l*sin(get()->q()->getValue(2))- _bboxfactor*_R)/_cellsize);
  int jmax1=(int) floor((get()->q()->getValue(1) - _l*sin(get()->q()->getValue(2))+ _bboxfactor*_R)/_cellsize);

  int imin2=(int) floor((get()->q()->getValue(0) + _l*cos(get()->q()->getValue(2))- _bboxfactor*_R)/_cellsize);
  int imax2=(int) floor((get()->q()->getValue(0) + _l*cos(get()->q()->getValue(2))+ _bboxfactor*_R)/_cellsize);
            
  int jmin2=(int) floor((get()->q()->getValue(1) + _l*sin(get()->q()->getValue(2))- _bboxfactor*_R)/_cellsize);
  int jmax2=(int) floor((get()->q()->getValue(1) + _l*sin(get()->q()->getValue(2))+ _bboxfactor*_R)/_cellsize);

  int imin=(std::min)(imin1,imin2);
  int imax=(std::max)(imax1,imax2);

  int jmin=(std::min)(jmin1,jmin2);
  int jmax=(std::max)(jmax1,jmax2);

  for(int i=imin;i<=imax;++i) 
  {
    for (int j=jmin;j<=jmax;++j)
    {
      SP::Hashed hds1(new Hashed(get(),i,j));
  
      // find all other systems that are in the same cells
      std::pair<space_hash::iterator, space_hash::iterator> 
        neighbours = sf->neighbours(hds1);

      unsigned int k;
      interPairs declaredInteractions;
      boost::shared_ptr<RoverFilter> 
        roverFilter(new RoverFilter(sf, boost::static_pointer_cast<Rover>(shared_from_this())));

      for (k=0;neighbours.first!=neighbours.second; ++neighbours.first,++k) 
      {
        // ds2 is a disk
        SP::LagrangianDS ds2 = (*neighbours.first)->body;
        int ids1 = get()->number();
        int ids2 = ds2->number();
        int imax = (std::max)(ids1,ids2);
        int imin = (std::min)(ids1,ids2);
        if (ids1 != ids2) 
          {
            // is interaction already treated ?
            interPair interpair;
            interpair=std::pair<int,int>(imin,imax);

            if (declaredInteractions.find(interpair)
                  ==declaredInteractions.end())
              {
                // no, check proximity
                declaredInteractions.insert(interpair);
                ds2->acceptSP(roverFilter);
              }
            
          }
      }

    }
    
  }
};

