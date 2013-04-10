
/*! \file Parameters.h
 *
 *  Contains the parameters
 *
 */
#ifndef PARAMETERS_H
#define PARAMETERS_H

#include "MyUtils.h"
#include "SimpleReader.h"

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
  Parameters& operator <= (Parameters& parameters,  Dmrg::SimpleReader& reader);

  //! print parameters
  std::ostream& operator << (std::ostream &os, const Parameters &parameters);

} // namespace EGT

#endif
