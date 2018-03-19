EASYLOCAL = ../easylocal-3
FLAGS = -std=c++11 -Wall #-O3 # -g
COMPOPTS = -I$(EASYLOCAL)/include $(FLAGS)
EASYLOCALLIB = -lEasyLocal -lboost_program_options
LINKOPTS = -L$(EASYLOCAL)/lib $(EASYLOCALLIB)  -pthread

SOURCE_FILES = JS_Data.cc JS_Basics.cc JS_Helpers.cc  JS_Main.cc
OBJECT_FILES = JS_Data.o JS_Basics.o JS_Helpers.o JS_Main.o
HEADER_FILES = JS_Data.hh JS_Basics.hh JS_Helpers.hh  

JS: $(OBJECT_FILES)
	g++ $(OBJECT_FILES) $(LINKOPTS) -o JS

JS_Data.o: JS_Data.cc JS_Data.hh
	g++ -c $(COMPOPTS) JS_Data.cc

JS_Basics.o: JS_Basics.cc JS_Basics.hh JS_Data.hh
	g++ -c $(COMPOPTS) JS_Basics.cc

JS_Helpers.o: JS_Helpers.cc JS_Helpers.hh JS_Basics.hh JS_Data.hh
	g++ -c $(COMPOPTS) JS_Helpers.cc

JS_Main.o: JS_Main.cc JS_Helpers.hh JS_Basics.hh JS_Data.hh
	g++ -c $(COMPOPTS) JS_Main.cc

clean:
	rm -f $(OBJECT_FILES) JS

