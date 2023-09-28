CXX = g++
CXXFLAGS = -Wall -std=c++11 -Wextra -Werror -pthread -O2
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,obj/%.o,$(SRCS))
TARGET = virtpc
OBJDIR = obj

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean
