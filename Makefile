cc = g++
prom = out
deps = $(shell find include/*.h)
src = $(shell find src/*.cc)
obj = $(src:%.cc=%.o) 
$(prom): $(obj)
	$(cc) -o $(prom) $(obj) -lgsl -lgslcblas -lm

%.o: %.cc $(deps)
	$(cc) -g -c -Iinclude/ $< -o $@
clean:
	rm $(obj)
