srcs := $(wildcard *.cpp)
objs := $(patsubst %.cpp, %.o, $(srcs))

CXXFLAGS := -g -Wall -Wextra
bin := vic

.PHONEY: all clean test

all: $(bin)

$(bin): $(objs)
	$(CXX) $(CXXFALGS) $(objs) -o $(bin)

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm $(bin) $(objs)

