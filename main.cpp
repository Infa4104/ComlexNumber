
#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

#include <sstream> 
#include <string.h> 

using namespace std;
ostringstream sstream;

// Написал Антон



class ComlexNumber
{
private:
  double Re_part;
  double Im_part;

public:
  
  bool Re(double Real) {
    Re_part = Real;
    return true;
  }
  const double& Re() {
    return Re_part;
  }
  bool Im(double UnReal) {
    Im_part = UnReal;
    return true;
  }
  const double& Im() {
    return Im_part;
  }
  double Abs() {
    return sqrt(Re_part * Re_part + Im_part * Im_part);
  }
  double Arg() {
    if (Im_part == 0) {
      return 0;
    }
    return atan(Re_part / Im_part);
  }

  double ArgDeg() {
    if (Im_part == 0) {
      return 0;
    }
    return atan(Re_part / Im_part) * 360 / (2 * 3.141592);
  }
  string Conj(){
    ostringstream s;
    s << Re_part;
    s << ' ';
    s << -1*Im_part;
    s << 'i';
    string out = s.str();
    return out;
  }

  explicit ComlexNumber(double Real = 0, double UnReal = 0) : Re_part(Real), Im_part(UnReal)
  {}

};

// Написал Иван

class ICreatorComplexNumber{
public:
    virtual ComlexNumber* createComplexNumber(double& Phase) = 0;
};

class CreatorComplexNumberFromPhaseRadians : public ICreatorComplexNumber {
public:
    ComlexNumber* createComplexNumber(double& Phase) override{
      return new ComlexNumber(cos(Phase),sin(Phase));
    }
    
};
class CreatorComplexNumberFromPhaseDegree : public ICreatorComplexNumber {
  public:
    ComlexNumber* createComplexNumber(double& Phase) override{
      Phase = Phase *M_PI/180;
      return new ComlexNumber(cos(Phase),sin(Phase));
    }
};


int main() {

  double phase = M_PI;

  ICreatorComplexNumber* creator = new CreatorComplexNumberFromPhaseRadians();

  ComlexNumber* cn1 = creator->createComplexNumber(phase);

  cout << cn1->Conj() << endl;
  
  creator = new CreatorComplexNumberFromPhaseDegree();

  ComlexNumber* cn2 = creator->createComplexNumber(phase);

  cout << cn2->Conj() << endl;

  exit(0);
  return 0;
}