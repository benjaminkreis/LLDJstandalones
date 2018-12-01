
ROOTFLAGS=`root-config --cflags --libs` 
CXXDEPFLAGS = -MMD -MP

all: main

main:  analyzer_base.o \
       analyzer_globalvalues.o \
       analyzer_config.o \
       analyzer_createobjects.o \
       analyzer_selections.o \
       analyzer_scalefactors.o \
       analyzer_histograms.o \
       analyzer_tree.o \
       analyzer_loop.o \
       main.C 
	g++ --std=c++11 $^ -o runanalyzer.exe ${ROOTFLAGS} ${CXXDEPFLAGS}

%.o: %.C  
	g++ --std=c++11 -c $^ -o $@ ${ROOTFLAGS} ${CXXDEPFLAGS} 

clean:
	rm -f  *.{o,d,exe}
