
LDFLAGS = -L.   
#-llapack -lblas -lm -L../lib
EXENAME = egt
#CPPFLAGS = -DNDEBUG 
CXX = g++ -Werror -Wall -g3 -O3
OBJ = main.o Engine.o Market.o Normals.o Parameters.o RandomNumRec.o RandomBase.o StatsGathererEGT.o Strategy.o PlayerNormal.o PlayerFactory.o 
#PlayerFactoryInitializer.o

$(EXENAME): $(OBJ)
	$(CXX) -o $(EXENAME) $(OBJ) $(LDFLAGS) 

main.o : SimpleReader.h Parameters.h Engine.h

Engine.o : Parameters.h PlayerBase.h Market.h StatsGathererEGT.h RandomDrand.h MyUtils.h

Market.o :

Normals.o : 

Parameters.o : MyUtils.h SimpleReader.h

RandomDrand.o : RandomBase.h

RandomNumRec.o : RandomBase.h

RandomBase.o : Normals.h

StatsGathererEGT.o : 

Strategy.o : RandomDrand.h

PlayerNormal.o : PlayerBase.h Strategy.h RandomDrand.h PlayerFactory.h 

PlayerFactory.o : PlayerBase.h

clean:
	rm -f core* *.o *.ii *.tt *~

######## End of Makefile ########

