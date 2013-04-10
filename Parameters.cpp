#include "Parameters.h"

EGT::Parameters& EGT::operator <= (EGT::Parameters& parameters,  Dmrg::SimpleReader& reader) 
{
  reader.read(parameters.outputFile);
  reader.read(parameters.nPlayer);
  reader.read(parameters.stepMAX);
  reader.read(parameters.initSignal);
  reader.read(parameters.randomSeed);

  return parameters;
}

std::ostream& EGT::operator << (std::ostream &os, const EGT::Parameters &parameters)
{
  os<<"parameters.filename="<<parameters.outputFile<<"\n";
  os<<"parameters.nPlayer="<<parameters.nPlayer<<"\n";
  os<<"parameters.stepMAX="<<parameters.stepMAX<<"\n";
  os<<"parameters.initSingal="<<parameters.initSignal<<"\n";
  os<<"parameters.seed="<<parameters.randomSeed;

  return os;
}

