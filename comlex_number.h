#pragma once

#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

#include <sstream> 
#include <string.h> 

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

template <typename T>
class Сomplex {
private:
  T Re_part;
  T Im_part;
public:
  bool re(T Real) {
    Re_part = Real;
    return true;
  }
  const T& re() {
    return Re_part;
  }
  bool im(T UnReal) {
    Im_part = UnReal;
    return true;
  }
  const T& im() {
    return Im_part;
  }
  T Abs() {
    return sqrt(Re_part * Re_part + Im_part * Im_part);
  }
  T arg() {
    if (Im_part == 0) {
      return 0;
    }
    return atan(Re_part / Im_part);
  }

  T argDeg() {
    if (Im_part == 0) {
      return 0;
    }
    return atan(Re_part / Im_part) * 360 / (2 * 3.141592);
  }
  string conj(){
    ostringstream s;
    s << Re_part;
    s << ' ';
    s << -1*Im_part;
    s << 'i';
    string out = s.str();
    return out;
  }

  explicit Сomplex(T Real = 0, T UnReal = 0) : Re_part(Real), Im_part(UnReal)
  {}
};

class ICreatorComplexNumber{
public:
    virtual Сomplex<double>* createComplexNumber(int& Phase) = 0;
};

class CreatorComplexNumberFromPhaseRadians : public ICreatorComplexNumber {
public:
    Сomplex<double>* createComplexNumber(int& Phase) override{
      return new Сomplex(cos(Phase),sin(Phase));
    }
    
};
class CreatorComplexNumberFromPhaseDegree : public ICreatorComplexNumber {
  public:
    Сomplex<double>*  createComplexNumber(int& Phase) override{
      Phase = Phase *M_PI/180;
      return new Сomplex(cos(Phase),sin(Phase));
    }
};
