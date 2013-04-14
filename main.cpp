/*	Evonomics theory --- Evolutionary Game Theory (EGT)
 *	by Q. Luo
 *	Date: Apr 8, 2013
 *	Platform: linux
 *	Model: Physica A 246 (1997) 407-418 
 */

#include "SimpleReader.h"
#include "Constants.h"
#include "Parameters.h"
#include "Engine.h"

typedef EGT::Parameters ParamsType;
typedef EGT::Engine EngineType;

int main(int argc,char *argv[])
{
  ParamsType params;
  Dmrg::SimpleReader reader(argv[1]);
  
  std::cout<<"Loading"<<std::endl;
  reader.load(params);
  
  EngineType engine(params);
  engine.Run();

}

/* ####### End of main.cpp ######## */

