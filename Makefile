
LDFLAGS = -L.   
#-llapack -lblas -lm -L../lib
EXENAME = egt
#CPPFLAGS = -DNDEBUG 
CXX = g++ -Werror -Wall -g3 -O3
OBJ = main.o Engine.o Market.o Normals.o Parameters.o RandomDrand.o Player.o RandomBase.o StatsGathererEGT.o Strategy.o 

$(EXENAME): $(OBJ)
	$(CXX) -o $(EXENAME) $(OBJ) $(LDFLAGS) 

main.o : SimpleReader.h Constants.h Parameters.h Engine.h

Engine.o : Parameters.h Player.h Market.h StatsGathererEGT.h RandomDrand.h MyUtils.h

Market.o : Constants.h 

Normals.o : 

Parameters.o : MyUtils.h SimpleReader.h

RandomDrand.o : RandomBase.h

Player.o : Constants.h Strategy.h RandomDrand.h

RandomBase.o : Normals.h

StatsGathererEGT.o : 

Strategy.o : Constants.h RandomDrand.h

clean:
	rm -f core* *.o *.ii *.tt *~

######## End of Makefile ########

