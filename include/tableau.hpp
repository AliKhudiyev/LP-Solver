
#pragma once

#include <iostream>

namespace lp{ namespace utils{

    class Tableau{
    private:
      size_t m_rowCount, m_columnCount;
      double** m_data;

    public:
      Tableau(size_t n_row, size_t n_col):
	m_rowCount(n_row), m_columnCount(n_col)
      {
	
	m_data = (double**)malloc(n_row*sizeof(double*));
	for(size_t i=0; i<n_row; ++i){
	  m_data[i] = new double[n_col];
	  for(size_t j=0; j<n_col; ++j) m_data[i][j] = 0.;
	}
	
      }
      ~Tableau(){
	for(size_t i=0; i<m_rowCount; ++i){
	  delete[] m_data[i];
	}
	delete[] m_data;
      }

      inline size_t width() const{ return m_columnCount; }
      inline size_t height() const{ return m_rowCount; }

      double& at(size_t row, size_t col){ return m_data[row][col]; }
      Tableau& add(size_t src_row1, size_t src_row2, size_t dest_row=-1, double coef=1.0){
	if(dest_row == -1) dest_row = src_row2;
	for(size_t i=0; i<m_columnCount; ++i){
	  m_data[dest_row][i] = m_data[src_row1][i] + m_data[src_row2][i] * coef;
	}
	return *this;
      }
      Tableau& subtract(size_t src_row1, size_t src_row2, size_t dest_row=-1){
	if(dest_row == -1) dest_row = src_row2;
	for(size_t i=0; i<m_columnCount; ++i){
	  m_data[dest_row][i] = m_data[src_row1][i] - m_data[src_row2][i];
	}
	return *this;
      }
      Tableau& mult(double coef, size_t row){
	for(size_t i=0; i<m_columnCount; ++i){
	  m_data[row][i] *= coef;
	}
	return *this;
      }

      size_t get_index(size_t index, bool from_row){
	size_t final_index = -1;
	double sign = -1;
	size_t dx = 1;
	size_t count = m_rowCount-2;

	if(from_row){
	  dx = 0;
	  count = m_columnCount-1;
	  sign = 1;
	}

	double recent = m_data[index*(1-dx)][index*dx];
	if(!from_row && recent) recent = m_data[0][m_columnCount-1] / recent;
	
	for(size_t i=0; i<count; ++i){
	  double current = m_data[index*(1-dx)+dx*i][index*dx+(1-dx)*i];
	  // printf("\t[%d]current: %lf\n", from_row, current);
	  
	  if(!from_row && current){
	    current = m_data[i][m_columnCount-1] / current;
	  }
	  if(current <= 0) continue;
	  // printf("\t[%d]current: %lf | %lf >= %lf\n", from_row, current, sign*current, sign*recent);
	  if(sign * current >= sign * recent || recent <= 0){
	    recent = current;
	    final_index = i;
          }
	}

        return final_index;
      }
      
      friend std::ostream& operator<<(std::ostream& out, const Tableau& tableau){
	for(size_t i=0; i<tableau.m_rowCount; ++i){
	  for(size_t j=0; j<tableau.m_columnCount; ++j){
	    out << tableau.m_data[i][j] << "\t";
	  }
	  out << "\n";
	}
	return out;
      }
    };

} }
