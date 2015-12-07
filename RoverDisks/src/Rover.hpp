#include <SiconosKernel.hpp>
#include <SpaceFilter.hpp>
#include <ExternalBody.hpp>

DEFINE_SPTR(Rover);


class Rover : public ExternalBody
{

private:

  double _R;
  
  double _l;
  
public:
  Rover(double m1, double m2, double R, double l,
        SP::SimpleVector q0, SP::SimpleVector v0);

  SP::Rover get() 
  {
    return boost::static_pointer_cast<Rover>(shared_from_this());
  };
  

  double wheelRadius() 
  {
    return _R;
  }
  
  double length()
  {
    return _l;
  }
  
    
  
  void selfHash(SP::SpaceFilter);
  
  void selfFindInteractions(SP::SpaceFilter);

  struct RoverFilter;

  friend class RoverFilter;
  
  

};


