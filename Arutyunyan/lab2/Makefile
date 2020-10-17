CXX = g++
TARGET = lab2
CXXFLAGS = -c -std=c++17
CXXOBJFLAGS = -std=c++17
LIBDIR = source/lib
SRCDIR = source/src
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXOBJFLAGS) $(OBJS) -o $(TARGET)

%.o: $(SRCDIR)/%.cpp $(LIBDIR)/*.h
	$(CXX) $(CXXFLAGS) $<

clean:
	rm -rf $(SRCDIR)/*.o $(TARGET)
