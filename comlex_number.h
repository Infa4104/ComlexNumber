#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

#include <sstream> 
#include <string.h> 

#include <complex>

using namespace std;
ostringstream sstream;

// Пример пользования 

// double phase = 3.141;

// ICreatorComplexNumber* creator = new CreatorComplexNumberFromPhaseRadians();

// ComlexNumber* cn1 = creator->createComplexNumber(phase);

// cout << cn1->Conj() << endl;

// creator = new CreatorComplexNumberFromPhaseDegree();

// ComlexNumber* cn2 = creator->createComplexNumber(phase);

// cout << cn2->Conj() << endl;


class ICreatorComplexNumber{
public:
    virtual complex<double>* createComplexNumber(int& Phase) = 0;
};

class CreatorComplexNumberFromPhaseRadians : public ICreatorComplexNumber {
public:
    complex<double>* createComplexNumber(int& Phase) override{
      return new complex(cos(Phase),sin(Phase));
    }
    
};
class CreatorComplexNumberFromPhaseDegree : public ICreatorComplexNumber {
  public:
    complex<double>*  createComplexNumber(int& Phase) override{
      Phase = Phase *M_PI/180;
      return new complex(cos(Phase),sin(Phase));
    }
};
