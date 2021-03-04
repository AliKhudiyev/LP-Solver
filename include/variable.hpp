
#pragma once

#include <stdio.h>
#include <string>
#include <cmath>
#include <limits>

#define LP_EPSILON (std::numeric_limits<double>::epsilon())
#define LP_INFINITY (std::numeric_limits<double>::max())
#define LP_PRINT_INFO {\
  printf("*** Limitation on boundaries: [%.10e, %.10e]\n", std::numeric_limits<double>::min(), std::numeric_limits<double>::max());\
  printf("*** Limitation on precision: %.30e\n\n", std::numeric_limits<double>::epsilon());\
}

namespace lp{
  
  class Variable{
  private:
    double m_value;
    double m_min, m_max;
    
  public:
    Variable(double min=0., double max=LP_INFINITY):
      m_value(0.), m_min(min), m_max(max) {}
    ~Variable(){}

    inline void set(double value){ m_value = value; }
    Variable& less_than(double number){
      m_max = number - LP_EPSILON;
      return *this;
    }
    Variable& greater_than(double number){
      m_min = number + LP_EPSILON;
      return *this;
    }
    Variable& less_equal(double number){
      m_max = number;
      return *this;
    }
    Variable& greater_equal(double number){
      m_min = number;
      return *this;
    }
    Variable& equal_to(double number){
      m_min = m_value = m_max = number;
      return *this;
    }
    void satisfy(double min, double max){
      m_min = min;
      m_max = max;
      
      if(min > max){
	m_min = max;
	m_max = min;
      }
    }
    void satisfy(const std::string& expression){
      // TO DO
    }
    inline double get() const{ return m_value; }
    inline double lower_boundary() const{ return m_min; }
    inline double upper_boundary() const{ return m_max; }
  };
  
}
