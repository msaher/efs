srcdir := src
objdir := obj
srcs := $(wildcard $(srcdir)/*.cpp)
objs := $(patsubst $(srcdir)/%.cpp, $(objdir)/%.o, $(srcs))

CXXFLAGS := -g -Wall -Wextra
bin := vic

.PHONEY: all clean test

all: $(bin) test

$(bin): $(objs)
	$(CXX) $(CXXFALGS) $(objs) -o $(bin)

$(objdir)/%.o: $(srcdir)/%.cpp $(srcdir)/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(objdir)/%.o: $(srcdir)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

testdir := test
testsrcs := $(wildcard $(testdir)/*.cpp)
testobjs := $(patsubst $(testdir)/%.cpp, $(testdir)/%.o, $(testsrcs))
testbin := testbin
testflags := -l boost_unit_test_framework
nomain := 

test: $(bin) $(testbin)
	./$(testbin)

$(testbin): $(testobjs) $(bin)
	$(CXX) $(filter-out $(objdir)/main.o, $(objs)) $(testobjs) $(CXXFALGS) $(testflags) -o $@

$(testdir)/%.o: $(testdir)/%.cpp
	$(CXX) $(CXXFALGS) -c $< -o $@

clean:
	rm $(bin) $(objs) $(testbin) $(testobjs)
