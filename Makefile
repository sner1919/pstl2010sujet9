# +++++++++++++++++++ Variables +++++++++++++++++++
CXX = g++
CXXFLAGS = -W -Wall ${DEBUGFLAG} #rq : ${DEBUGFLAG} ajouté à la configuration de construction "Debug" dans eclipse cdt
LDFLAGS =
LDLIBS = -latlas -lblas
INCLUDES =
PREPROCESS_AND_COMPIL = $(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@
LINK = $(CXX) $(LDFLAGS) $(LDLIBS) $^ -o $@
SRCDIR = ./src
IFACEDIR = $(SRCDIR)/interfaces
BINDIR = ./bin
OBJ = $(BINDIR)/Matrix.o $(BINDIR)/Vector.o $(BINDIR)/RowChecksumMatrix.o $(BINDIR)/ColumnChecksumMatrix.o $(BINDIR)/FullChecksumMatrix.o $(BINDIR)/CalculatorNaive.o $(BINDIR)/CalculatorAtlas.o $(BINDIR)/Processor.o $(BINDIR)/ErrorGenerator.o
OBJTEST = $(OBJ) $(BINDIR)/tests/MatrixTest.o $(BINDIR)/tests/FullChecksumMatrixTest.o $(BINDIR)/tests/BenchmarkTest.o
PROGS = $(BINDIR)/PSTL $(BINDIR)/tests/PSTLTest

# +++++++++++++++++++ Cibles habituelles +++++++++++++++++++
all : $(PROGS)

clean :
	rm -f $(PROGS) $(BINDIR)/*.o $(BINDIR)/tests/*.o

.PHONY: all clean

# +++++++++++++++++++ Fichiers exécutables +++++++++++++++++++
$(BINDIR)/PSTL : $(BINDIR)/PSTL.o $(OBJ)
	$(LINK)

$(BINDIR)/tests/PSTLTest : $(BINDIR)/tests/PSTLTest.o $(OBJTEST)
	$(LINK) -lcppunit
	
# +++++++++++++++++++ Fichiers objets +++++++++++++++++++
$(BINDIR)/%.o : $(SRCDIR)/%.cpp
	$(PREPROCESS_AND_COMPIL)

$(BINDIR)/tests/%.o : $(SRCDIR)/tests/%.cpp
	$(PREPROCESS_AND_COMPIL)
	
# +++++++++++++++++++ Dépendances +++++++++++++++++++
IMatrixDep = $(IFACEDIR)/IMatrix.hpp
IVectorDep = $(IFACEDIR)/IVector.hpp $(IMatrixDep)
IRowChecksumMatrixDep = $(IFACEDIR)/IRowChecksumMatrix.hpp $(IMatrixDep) $(IVectorDep)
IColumnChecksumMatrixDep = $(IFACEDIR)/IColumnChecksumMatrix.hpp $(IMatrixDep) $(IVectorDep)
IFullChecksumMatrixDep = $(IFACEDIR)/IFullChecksumMatrix.hpp $(IRowChecksumMatrixDep) $(IColumnChecksumMatrixDep)
ICalculatorDep = $(IFACEDIR)/ICalculator.hpp $(IMatrixDep)
IErrorGeneratorDep = $(IFACEDIR)/IErrorGenerator.hpp $(IMatrixDep)

MatrixDep = $(SRCDIR)/Matrix.hpp $(IMatrixDep)
VectorDep = $(SRCDIR)/Vector.hpp $(IVectorDep) $(MatrixDep)
RowChecksumMatrixDep = $(SRCDIR)/RowChecksumMatrix.hpp $(IRowChecksumMatrixDep) $(MatrixDep) $(VectorDep)
ColumnChecksumMatrixDep = $(SRCDIR)/ColumnChecksumMatrix.hpp $(IColumnChecksumMatrixDep) $(MatrixDep) $(VectorDep)
FullChecksumMatrixDep = $(SRCDIR)/FullChecksumMatrix.hpp $(IFullChecksumMatrixDep) $(RowChecksumMatrixDep) $(ColumnChecksumMatrixDep)
CalculatorNaiveDep = $(SRCDIR)/CalculatorNaive.hpp $(ICalculatorDep)
CalculatorAtlasDep = $(SRCDIR)/CalculatorAtlas.hpp $(ICalculatorDep)
ProcessorDep = $(SRCDIR)/Processor.hpp $(ICalculatorDep) $(FullChecksumMatrixDep)
ErrorGeneratorDep = $(SRCDIR)/ErrorGenerator.hpp $(IErrorGeneratorDep)

$(BINDIR)/Matrix.o : $(MatrixDep)
$(BINDIR)/Vector.o : $(VectorDep)
$(BINDIR)/RowChecksumMatrix.o : $(RowChecksumMatrixDep)
$(BINDIR)/ColumnChecksumMatrix.o : $(ColumnChecksumMatrixDep)
$(BINDIR)/FullChecksumMatrix.o : $(FullChecksumMatrixDep)
$(BINDIR)/CalculatorNaive.o : $(CalculatorNaiveDep)
$(BINDIR)/CalculatorAtlas.o : $(CalculatorAtlasDep)
$(BINDIR)/Processor.o : $(ProcessorDep)
$(BINDIR)/ErrorGenerator.o : $(ErrorGeneratorDep)

$(BINDIR)/tests/MatrixTest.o : $(SRCDIR)/tests/MatrixTest.hpp $(MatrixDep)
$(BINDIR)/tests/FullChecksumMatrixTest.o : $(SRCDIR)/tests/FullChecksumMatrixTest.hpp $(FullChecksumMatrixDep)
$(BINDIR)/tests/BenchmarkTest.o : $(SRCDIR)/tests/BenchmarkTest.hpp $(FullChecksumMatrixDep) $(CalculatorNaiveDep) $(CalculatorAtlasDep) $(ErrorGeneratorDep)
