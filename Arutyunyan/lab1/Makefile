CC = g++
TARGET = lab1
CFLAGS = -c
LIBDIR = Source/lib
SRCDIR = Source/src
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS)  -o $(TARGET)

%.o: $(SRCDIR)/%.cpp $(LIBDIR)/*.h
	$(CC) $(CFLAGS) $<

clean:
	rm -rf $(SRCDIR)/*.o $(TARGET)
