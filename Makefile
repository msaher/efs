srcdir = src
objdir = obj
testdir = test
srcs := $(wildcard $(srcdir)/*.cpp)
objs := $(patsubst $(srcdir)/%.cpp, $(objdir)/%.o, $(srcs))

CXXFLAGS := -g -Wall -Wextra
bin := vic

.PHONEY: all clean test

all: $(bin)

$(bin): $(objs)
	$(CXX) $(CXXFALGS) $(objs) -o $(bin)

$(objdir)/%.o: $(srcdir)/%.cpp $(srcdir)/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(objdir)/%.o: $(srcdir)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm $(bin) $(objs)

