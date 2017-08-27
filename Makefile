FLAGS = -Wall -Werror -std=c++11

src = $(wildcard *.cpp)
objects = $(patsubst %.cpp, %.o, $(src))

INCLUDE = -Izlib/include
LIBS = -Lzlib/lib -lz


ifeq ($(OS), Windows_NT)
	RM = del
else
	RM = rm -f
endif


main: $(objects)
	g++  $(objects) $(LIBS) $(FLAGS) -o $@


$(objects):%.o : %.cpp 
	g++ -c $(FLAGS) $(INCLUDE)  $<  -o $@

	
	
.PHONY:clean
clean:
	$(RM) $(objects)
	$(RM) main.exe
	