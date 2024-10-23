
#include <iostream>
#include <math.h>

#include <sstream> 
#include <string.h> 

using namespace std;
ostringstream sstream;

class Comlex_number
{
private:
  double Re_part;
  double Im_part;

public:
  
  // Написал Антон

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


};
int main() {
  Comlex_number cmx;
  cmx.Re(2);
  cmx.Im(2);
  
  cout << cmx.Abs();
  cout << '\n';
  cout << cmx.ArgDeg();
  cout << '\n';
  cout << cmx.Conj();
  exit(0);
  return 0;
}