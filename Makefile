#the compiler define as g++ for C++
CC = g++

#compiler flags:
# -g adds debugging information to the executable file
#  # -Wall turns on most, but not all, compiler warnings
CFLAGS = -g -Wall --coverage

#define the cpp source files
SRCS = $(shell find src/ -name \*.cpp)

HDRS = $(shell find src/ -name \*.h)

#define the cpp object files
OBJS = $(SRCS:.cpp=.o)

#define the executable:
TARGET = rugby

.PHONY: coverage test clean

all: $(TARGET) test coverage

$(TARGET): $(OBJS) main.o
				$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) main.o

#create object files
$(OBJS): %.o: %.cpp $(HDRS)
		$(CC) $(CFLAGS) -c -o $@ $< 

main.o: main.cpp $(HDRS) 
		$(CC) $(CFLAGS) -Isrc/ -c main.cpp

tests/unittests: tests/*.cpp
		$(CC) $(CFLAGS) -Isrc/ $(OBJS) tests/*.cpp -o tests/unittests
	
test: tests/unittests
		cd tests && ./unittests

clean:
	$(RM) *.o src/*.o tests/*.o $(TARGET) tests/unittests `find . -regex ".*\.\(gcov\|gcda\|gcno\)"`

coverage:
	@echo " ================="
	@echo " = Code coverage ="
	@echo " ================="
	@mv src/*.gcno src/*.gcda . 2>/dev/null || true
	@gcov src/*.cpp 2>&1 | grep -A 1 'File.*cpp' | sed '/File/N;s/\n/ - /' | grep File
	@mkdir -p coverage
	@mv *.gcov coverage/
