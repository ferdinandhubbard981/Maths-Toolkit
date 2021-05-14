
#include <cmath>
double GetFuncOutput(double input, int orderOfEqn, int* coefficients) // coeff in form an * xn an-1 * xn-1 ... a0 x0
{
  double output;
  for (int i = orderOfEqn; i >= 0; i--)
  {
    output +=  coefficients[i] * pow(input, i);
  }
  return output;
}

bool CheckChangeOfSign(orderOfEqn, int* coefficients, double[2] bounds)
{
  lowerBoundOutput = GetFuncOutput(bound * -1, orderOfEqn, coefficients);
  upperBoundOutput = GetFuncOutput(bound, orderOfEqn, coefficients);
  if (GetFuncOutput(bound[0], orderOfEqn, coefficients) * GetFuncOutput(bound[1], orderOfEqn, coefficients) <= 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}


double[2] FindInitialBounds(int orderOfEqn, int* coefficients)
{
  double bound = 0.1;
  double increment = bound;
  bool found = false;
  //double* previousOutput
  while(!found)
  {
    lowerBoundOutput = GetFuncOutput(bound * -1, orderOfEqn, coefficients);
    upperBoundOutput = GetFuncOutput(bound, orderOfEqn, coefficients);
    if (lowerBoundOutput * upperBoundOutput <= 0)
    {
      found = true;
    }
    else
    {
      bound += increment;
    }
  }
  double[2] bounds = {-1 * bound, bound};
  return bounds;
}


double Bisection(int orderOfEqn, int* coefficients, int dp) //dp = decimal places
{
  //find initial bounds
  double[2] bounds = FindInitialBounds(orderOfEqn, coefficients);
  //half bounds each time
  double diff;
  bool found = false;
  while (!found)
  {
    double midpoint = 0.5(bounds[0] + bounds[1]);
    CheckChangeOfSign({})

  }


  //stop when change in result is lower than required significant figures
}
