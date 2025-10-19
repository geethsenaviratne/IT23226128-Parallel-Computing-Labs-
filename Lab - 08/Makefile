NVCC := nvcc
CFLAGS := -O2

ALL := ex1 ex2 ex3 ex4 ex5

all: $(ALL)

ex1: ex1.cu cuda_check.hpp
	$(NVCC) $(CFLAGS) ex1.cu -o ex1

ex2: ex2.cu cuda_check.hpp
	$(NVCC) $(CFLAGS) ex2.cu -o ex2

ex3: ex3.cu cuda_check.hpp
	$(NVCC) $(CFLAGS) ex3.cu -o ex3

ex4: ex4_vecmul.cu cuda_check.hpp
	$(NVCC) $(CFLAGS) ex4_vecmul.cu -o ex4

ex5: ex5_mat_elemwise.cu cuda_check.hpp
	$(NVCC) $(CFLAGS) ex5_mat_elemwise.cu -o ex5

clean:
	rm -f $(ALL)
