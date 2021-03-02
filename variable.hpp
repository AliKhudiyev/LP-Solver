
#pragma once

#include <string>
#include <cmath>

#define LP_EPSILON 1e-6

namespace lp{
  
  class Variable{
  private:
    double m_value;
    double m_min, m_max;
    
  public:
    Variable(double value=0.0):
      m_value(value)
    {
      m_min = 0.0;
      m_max = 1.0;
    }
    ~Variable(){}

    inline void set(double value){ m_value = value; }
    Variable& less_than(double value){
      m_max = value - LP_EPSILON;
      return *this;
    }
    Variable& greater_than(double value){
      m_min = value + LP_EPSILON;
      return *this;
    }
    Variable& less_equal(double value){
      m_max = value;
      return *this;
    }
    Variable& greater_equal(double value){
      m_min = value;
      return *this;
    }
    Variable& equal_to(double value){
      m_min = m_value = m_max = value;
      return *this;
    }
    void condition(const std::string& expression){}
    inline double get() const{ return m_value; }
  };
  
}
