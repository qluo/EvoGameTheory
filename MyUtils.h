
#ifndef MY_UTILS_H
#define MY_UTILS_H

//! Utility functions
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

namespace std {
	
	template<class T1,class T2>
	ostream &operator<<(std::ostream &os,const pair<T1,T2>& p)
	{
		os<<p.first<<" "<<p.second;
		return os;
	}
	template<class X>
	std::ostream &operator<<(std::ostream &s,std::vector<X> const &v)
	{
		s<<v.size()<<"\n";
		for (size_t i=0;i<v.size();i++) s<<v[i]<<"\n";
		return s;
	}
	template<class X>
	X operator*(std::vector<X> const &v,std::vector<X> const &w)
	{
		X result=0;
		for (size_t i=0;i<v.size();i++) result += v[i]*w[i];
		return result;
	}

}

namespace myUtils {

  // For error testing
  inline void check(bool cond, const std::string& msg = "testing failed")
  {
    if(!cond) {
      std::cerr<<msg<<std::endl;
      exit(1);
    }
  }

} // namespace myUtils


#endif
