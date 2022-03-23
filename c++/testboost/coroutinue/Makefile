CXXFLAGS = -Wall -I/home/zhangjun-s/opt/boost/include/boost-1_53 
LDFLAGS = -L/home/zhangjun-s/opt/boost/lib -Wl,-R/home/zhangjun-s/opt/boost/lib -lboost_context-gcc41-d-1_53
CXX = g++

%.exe: %.o
	$(CXX) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	rm -f *.o *.exe
