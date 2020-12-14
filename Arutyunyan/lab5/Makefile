.PHONY: all clean

CXX = g++
TARGET = lab5
CXXFLAGS = -g -c -std=c++17
CXXOBJFLAGS = -g -std=c++17
LIBDIR = source/lib
SRCDIR = source/src
SRCS = $(wildcard $(SRCDIR)/*.cc)
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "Compiling:"
	$(CXX) $(CXXOBJFLAGS) $(OBJS) -o $(TARGET)

%.o: $(SRCDIR)/%.cpp $(LIBDIR)/*.h
	$(CXX) $(CXXFLAGS) $<

clean:
	@echo "Cleaning build files:"
	rm -rf $(SRCDIR)/*.o $(TARGET)
