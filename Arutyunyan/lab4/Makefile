CXX = g++
TARGET = lab4
CXXFLAGS = -g -c -std=c++17
CXXOBJFLAGS = -g -std=c++17
LIBDIR = source/lib
SRCDIR = source/src
SRCS = $(wildcard $(SRCDIR)/*.cc)
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXOBJFLAGS) $(OBJS) -o $(TARGET)

%.o: $(SRCDIR)/%.cpp $(LIBDIR)/*.h
	$(CXX) $(CXXFLAGS) $<

clean:
	rm -rf $(SRCDIR)/*.o $(TARGET)
