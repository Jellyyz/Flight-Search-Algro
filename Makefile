# Executable names:
EXENAME = flight
OBJS = main.o parser.o adj_list_graph.o vertex.o BFS.o dijikstra.o betweencentrality.o

# Compiler/linker comfig and object/depfile directory:
CXX = clang++
LD = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -Werror -pedantic
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

# make sure we are on ews
IS_EWS=$(shell hostname | grep "ews.illinois.edu") 
IS_CORRECT_CLANG=$(shell clang -v 2>&1 | grep "version 6")
ifneq ($(strip $(IS_EWS)),)
ifeq ($(strip $(IS_CORRECT_CLANG)),)
CLANG_VERSION_MSG = $(error $(ccred) On EWS, please run 'module load llvm/6.0.1' first when running CS225 assignments. $(ccend))
endif
else
ifneq ($(strip $(SKIP_EWS_CHECK)),True)
CLANG_VERSION_MSG = $(warning $(ccyellow) Looks like you are not on EWS. Be sure to test on EWS before the deadline. $(ccend))
endif
endif

.PHONY: all test clean cleanobj cleandiff 

all : $(EXENAME)

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME): output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o: main.cpp main.h 
	$(CXX) $(CXXFLAGS) main.cpp

parser.o: parser.cpp parser.h
	$(CXX) $(CXXFLAGS) parser.cpp 

vertex.o: vertex.cpp vertex.h
	$(CXX) $(CXXFLAGS) vertex.cpp 

adj_list_graph.o: adj_list_graph.cpp adj_list_graph.h
	$(CXX) $(CXXFLAGS) adj_list_graph.cpp

BFS.o: BFS.cpp BFS.h 
	$(CXX) $(CXXFLAGS) BFS.cpp

dijikstra.o: Algorithms/dijikstra.cpp Algorithms/dijikstra.h
	$(CXX) $(CXXFLAGS) Algorithms/dijikstra.cpp

betweencentrality.o: Algorithms/betweencentrality.cpp Algorithms/betweencentrality.h
	$(CXX) $(CXXFLAGS) Algorithms/betweencentrality.cpp 
	
test: output_msg catch/catchmain.cpp testing/tests.cpp parser.cpp adj_list_graph.cpp vertex.cpp Algorithms/dijikstra.cpp Algorithms/betweencentrality.cpp  BFS.cpp
	$(LD) catch/catchmain.cpp testing/tests.cpp parser.cpp adj_list_graph.cpp vertex.cpp Algorithms/dijikstra.cpp Algorithms/betweencentrality.cpp  BFS.cpp $(LDFLAGS) -o test

clean: 		
	rm -rf $(EXENAME) $(TEST) $(OBJS_DIR) $(CLEAN_RM) *.o *.d

cleanobj:
	rm -rf *.o 

cleandiff: 
	rm -rf *.diff 

