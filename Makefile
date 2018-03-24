
CCC=g++
# list all warnings
CCFLAGS = -Wall -g -std=c++11 

# all is called a target, after the colon you have dependencies
# ie. "the target all is dependent on the executables
all : sudoku

# the target <excecutable1> is dependent on the list of dependencies
# the line following  is the required executable (don't need to adjust it)
# Note: executable lines, ie. $(CCC) ..., always begin with a tab.
# $^ = this target
# $@ = this/these dependencies
sudoku : SudokuGrid.o sudoku.o
	$(CCC) $(CCFLAGS) $^ -o $@

# if 2 or more problems in assignment, you can compile them all with extra
# executable targets and dependencies.

sudoku.o : SudokuGrid.h

# default rule compiling .cc to .o
# all .o file targets are dependent on the corresponding .cc files
# $< = the corresponding .cc file
%.o : %.cc
	$(CCC) -c $(CCFLAGS) $<

clean:
	rm -f *.o *~ *% *# .#*

clean-all: clean
	rm -f sudoku
