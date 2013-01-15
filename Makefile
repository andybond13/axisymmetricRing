CPP       = mpic++
CPP_FLAGS = -O2 #-Wall -fPIC -O2 -m64
SOFTWARE  = ./utilities
BOOST_ROOT = $(SOFTWARE)/boost/
#CTL       = $(SOFTWARE)/utils/ctl
#CTLINC    = $(CTL)/include
#CTLLIB    = $(CTL)/lib/libctl_g++Linuxx86_64/libctl.so
INCS      = -I./inc -I$(BOOST_ROOT) #-I./ci -I$(CTLINC) -I$(SOFTWARE)/utils 
SRC       = ./src/
OBJ       = ./bin/
OBJMAIN   = $(OBJ)
OBJSERV   = $(OBJ)/service/
OBJCLIE   = $(OBJ)/client/
TEST      = ./test/

#all    : main.exe service client.exe
#service: $(OBJSERV)connectCR.o $(OBJSERV)connectMPG.o $(OBJSERV)libCartRing.so $(OBJSERV)libMatPropGen.so $(OBJSERV)CartRing.exe $(OBJSERV)MatPropGen.exe


# Classical compilation of the main
main.exe: $(OBJMAIN)main.o $(OBJMAIN)CartRing.o $(OBJMAIN)MatPropGen.o
	$(CPP) $(CPP_FLAGS) -o $(OBJMAIN)main.exe $(OBJMAIN)main.o $(OBJMAIN)CartRing.o $(OBJMAIN)MatPropGen.o

$(OBJMAIN)main.o: $(TEST)main.cpp
	$(CPP) $(CPP_FLAGS) -c $(INCS) $(TEST)main.cpp -o $(OBJMAIN)main.o
	
$(OBJMAIN)CartRing.o: $(SRC)cartRing.C
	$(CPP) $(CPP_FLAGS) -c $(INCS) $(SRC)cartRing.C -o $(OBJMAIN)CartRing.o

$(OBJMAIN)MatPropGen.o: $(SRC)matPropGen.C
	$(CPP) $(CPP_FLAGS) -c $(INCS) $(SRC)matPropGen.C -o $(OBJMAIN)MatPropGen.o


# Compilation of the componant as a shared library and a remote executables
#$(OBJSERV)connectCR.o: $(SRC)connectCR.cpp
#	$(CPP) $(CPP_FLAGS) -c $(INCS) $(SRC)connectCR.cpp -o $(OBJSERV)connectCR.o

#$(OBJSERV)connectMPG.o: $(SRC)connectMPG.cpp
#	$(CPP) $(CPP_FLAGS) -c $(INCS) $(SRC)connectMPG.cpp -o $(OBJSERV)connectMPG.o

#$(OBJSERV)libCartRing.so: $(OBJSERV)connectCR.o $(OBJMAIN)CartRing.o
#	$(CPP) $(CPP_FLAGS) -shared -o $(OBJSERV)libCartRing.so $(OBJSERV)connectCR.o $(OBJMAIN)CartRing.o

#$(OBJSERV)libMatPropGen.so: $(OBJSERV)connectMPG.o $(OBJMAIN)MatPropGen.o
#	$(CPP) $(CPP_FLAGS) -shared -o $(OBJSERV)libMatPropGen.so $(OBJSERV)connectMPG.o $(OBJMAIN)MatPropGen.o

#$(OBJSERV)CartRing.exe: $(OBJSERV)connectCR.o $(OBJMAIN)CartRing.o
#	$(CPP) $(CPP_FLAGS) -o $(OBJSERV)CartRing.exe $(OBJSERV)connectCR.o $(OBJMAIN)CartRing.o $(CTLLIB)

#$(OBJSERV)MatPropGen.exe: $(OBJSERV)connectMPG.o $(OBJMAIN)MatPropGen.o
#	$(CPP) $(CPP_FLAGS) -o $(OBJSERV)MatPropGen.exe $(OBJSERV)connectMPG.o $(OBJMAIN)MatPropGen.o $(CTLLIB)


# compilation d'un client faisant appel au service
#client.exe: $(OBJCLIE)client.o
#	$(CPP) $(CPP_FLAGS) -o $(OBJCLIE)client.exe $(OBJCLIE)client.o $(CTLLIB)

#$(OBJCLIE)client.o: $(TEST)client.cpp
#	$(CPP) $(CPP_FLAGS) -c $(INCS) $(TEST)client.cpp -o $(OBJCLIE)client.o


clean:
	rm $(OBJMAIN)*.o $(OBJMAIN)*.exe
	#rm $(OBJSERV)*.o $(OBJSERV)*.so $(OBJSERV)*.exe
	#rm $(OBJCLIE)*.o $(OBJCLIE)*.exe
