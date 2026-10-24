CXX = g++
CXXFLAGS = -std=c++11 -Iinclude
SRC = src/main.cpp src/store.cpp src/util.cpp src/student.cpp src/teacher.cpp src/admin.cpp
OBJ = $(SRC:.cpp=.o)

main: $(OBJ)
	$(CXX) $(OBJ) -o main

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f src/*.o main