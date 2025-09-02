# Makefile for the molecular dynamics code with OpenMP

#
# C compiler and options for Cray
#
#CC=	cc
#LIB=

#
# C compiler and options for Intel
#
#CC=     icc -O3 -openmp
#LIB=    -lm

#
# C compiler and options for PGI 
#
#CC=     pgcc -O3 -mp 
#LIB=	-lm

#
# C compiler and options for GNU (ENABLED - Default)
#
CC=     gcc -O3 -fopenmp 
LIB=	-lm

#
# Object files
#
OBJ=    main.o \
	dfill.o \
	domove.o \
        dscal.o \
	fcc.o \
	forces.o \
	mkekin.o \
	mxwell.o \
	prnout.o \
	velavg.o

#
# Compile
#
md:	$(OBJ)
	$(CC) -o $@ $(OBJ) $(LIB)

.c.o:
	$(CC) -c $<

#
# Test with different thread counts
#
test: md
	@echo "Testing MD simulation with different thread counts:"
	@echo "Thread Count | Total Time | Forces Time | Final Energy"
	@echo "-------------|------------|-------------|-------------"
	@for threads in 1 2 3 4; do \
		echo -n "     $$threads       | "; \
		output=$$(OMP_NUM_THREADS=$$threads ./md 2>/dev/null); \
		echo "$$output" | grep "Total simulation time" | awk '{printf "%10.3f | ", $$5}'; \
		echo "$$output" | grep "Total forces calculation time" | awk '{printf "%11.3f | ", $$6}'; \
		echo "$$output" | grep "^ *20" | tail -1 | awk '{printf "%11.4f", $$4}'; \
		echo ""; \
	done

#
# Test different scheduling strategies
#
test-schedule: md
	@echo "Testing different OpenMP scheduling strategies:"
	@for schedule in "static" "static,1" "static,10" "dynamic" "guided"; do \
		echo "Schedule: $$schedule"; \
		OMP_NUM_THREADS=4 OMP_SCHEDULE="$$schedule" ./md | grep "Total simulation time"; \
		echo ""; \
	done

#
# Clean out object files and the executable.
#
clean:
	rm -f *.o md

.PHONY: test test-schedule clean