
/*! \file Parameters.h
 *
 *  Contains the parameters
 *
 */
#ifndef PARAMETERS_H
#define PARAMETERS_H

#include "MyUtils.h"
#include "SimpleReader.h"
//#include "Constants.h"

namespace EGT{
	
  //! Structure that contains the Engine parameters
  struct Parameters {

    std::string outputFile; // filename to save observables and continued fractions
    unsigned long nPlayer; // # of players
    unsigned long stepMAX; // maximum of allowed steps
    std::string initSignal; // intialization of system signal
    std::vector<long> randomSeed; // random seeds: [0]--choose S strategies, [1]--choose one out of S strategies

  };

  //! Read parameters from input file
  Parameters& operator <= (Parameters& parameters,  Dmrg::SimpleReader& reader) 
    {
      reader.read(parameters.outputFile);
      reader.read(parameters.nPlayer); 
      reader.read(parameters.stepMAX);
      reader.read(parameters.initSignal);
      reader.read(parameters.randomSeed);

      return parameters;
    } 

	//! print parameters
  std::ostream &operator << (std::ostream &os, const Parameters &parameters)
    {
      os<<"parameters.filename="<<parameters.outputFile<<"\n";
      os<<"parameters.nPlayer="<<parameters.nPlayer<<"\n";
      os<<"parameters.stepMAX="<<parameters.stepMAX<<"\n";
      os<<"parameters.initSingal="<<parameters.initSignal<<"\n";
      os<<"parameters.seed="<<parameters.randomSeed;

      return os;
    }

} // namespace EGT

#endif
