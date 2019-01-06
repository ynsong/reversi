CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror -Werror=vla -g -MMD 
EXEC = a4q5
OBJECTS = main.o cell.o textdisplay.o grid.o  window.o graphicsdisplay.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean

