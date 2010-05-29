# +++++++++++++++++++ Variables +++++++++++++++++++
CPU = VMWareCore1
CXX = g++
CXXFLAGS = -W -Wall -g -D CPU=$(CPU) ${DEBUGFLAG} #rq : ${DEBUGFLAG} ajouté à la configuration de construction "Debug" dans eclipse cdt
LDFLAGS = #-L./lib/$(CPU)/atlas/ -Wl,--rpath,./lib/$(CPU)/atlas/ -L./lib/$(CPU)/gotoblas/ -Wl,--rpath,./lib/$(CPU)/gotoblas/ -L./lib/$(CPU)/intelmkl/ -Wl,--rpath,./lib/$(CPU)/intelmkl/ 
LDLIBS = -lm -lpthread -lgmpxx -lgmp -ldl #-lclapack -lcblas -latlas -lgoto2 -lgfortran -Wl,--start-group -lmkl_intel -lmkl_sequential -lmkl_core -Wl,--end-group
INCLUDES =
PREPROCESS_AND_COMPIL = $(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@
LINK = $(CXX) -o $@ $^ $(LDFLAGS) $(LDLIBS)
SRCDIR = ./src
IFACEDIR = $(SRCDIR)/interfaces
BINDIR = ./bin
OBJ = $(BINDIR)/Types.o $(BINDIR)/Types.o $(BINDIR)/Matrix.o $(BINDIR)/Vector.o $(BINDIR)/RowChecksumMatrix.o $(BINDIR)/ColumnChecksumMatrix.o $(BINDIR)/FullChecksumMatrix.o $(BINDIR)/CalculatorNaive.o $(BINDIR)/CalculatorBlasLapack.o $(BINDIR)/AtlasAdapter.o $(BINDIR)/GotoBlasAdapter.o $(BINDIR)/IntelMKLAdapter.o $(BINDIR)/Processor.o $(BINDIR)/ErrorGenerator.o
OBJTEST = $(OBJ) $(BINDIR)/tests/TypesTest.o $(BINDIR)/tests/MatrixTest.o $(BINDIR)/tests/VectorTest.o $(BINDIR)/tests/RowChecksumMatrixTest.o $(BINDIR)/tests/ColumnChecksumMatrixTest.o $(BINDIR)/tests/FullChecksumMatrixTest.o $(BINDIR)/tests/CalculatorTest.o $(BINDIR)/tests/ErrorGeneratorTest.o $(BINDIR)/tests/BenchmarkTest.o
PROGS = $(BINDIR)/PSTL $(BINDIR)/tests/PSTLTest

# +++++++++++++++++++ Cibles habituelles +++++++++++++++++++
all : $(PROGS)

clean :
	rm -f $(PROGS) $(OBJTEST)

.PHONY : all clean

# +++++++++++++++++++ Fichiers exécutables +++++++++++++++++++
$(BINDIR)/PSTL : $(SRCDIR)/PSTL.cpp $(OBJ)
	$(LINK)

$(BINDIR)/tests/PSTLTest : $(SRCDIR)/tests/PSTLTest.cpp $(OBJTEST)
	$(LINK) -lcppunit
	
# +++++++++++++++++++ Fichiers objets +++++++++++++++++++
$(BINDIR)/%.o : $(SRCDIR)/%.cpp $(SRCDIR)/%.hpp $(SRCDIR)/settings.hpp
	$(PREPROCESS_AND_COMPIL)

$(BINDIR)/tests/%.o : $(SRCDIR)/tests/%.cpp $(SRCDIR)/tests/%.hpp $(SRCDIR)/settings.hpp
	$(PREPROCESS_AND_COMPIL)
	
# +++++++++++++++++++ Dépendances +++++++++++++++++++
TypesDep = $(SRCDIR)/Types.hpp

IMatrixDep = $(IFACEDIR)/IMatrix.hpp $(TypesDep)
IVectorDep = $(IFACEDIR)/IVector.hpp $(IMatrixDep)
IRowChecksumMatrixDep = $(IFACEDIR)/IRowChecksumMatrix.hpp $(IMatrixDep) $(IVectorDep)
IColumnChecksumMatrixDep = $(IFACEDIR)/IColumnChecksumMatrix.hpp $(IMatrixDep) $(IVectorDep)
IFullChecksumMatrixDep = $(IFACEDIR)/IFullChecksumMatrix.hpp $(IRowChecksumMatrixDep) $(IColumnChecksumMatrixDep)
ICalculatorDep = $(IFACEDIR)/ICalculator.hpp $(IMatrixDep)
IBlasLapackAdapterDep = $(IFACEDIR)/IBlasLapackAdapter.hpp
IErrorGeneratorDep = $(IFACEDIR)/IErrorGenerator.hpp $(IMatrixDep)

MatrixDep = $(SRCDIR)/Matrix.hpp $(IMatrixDep)
VectorDep = $(SRCDIR)/Vector.hpp $(IVectorDep) $(MatrixDep)
RowChecksumMatrixDep = $(SRCDIR)/RowChecksumMatrix.hpp $(IRowChecksumMatrixDep) $(MatrixDep)
ColumnChecksumMatrixDep = $(SRCDIR)/ColumnChecksumMatrix.hpp $(IColumnChecksumMatrixDep) $(MatrixDep)
FullChecksumMatrixDep = $(SRCDIR)/FullChecksumMatrix.hpp $(IFullChecksumMatrixDep) $(RowChecksumMatrixDep) $(ColumnChecksumMatrixDep)
CalculatorNaiveDep = $(SRCDIR)/CalculatorNaive.hpp $(ICalculatorDep)
CalculatorBlasLapackDep = $(SRCDIR)/CalculatorBlasLapack.hpp $(CalculatorNaiveDep) $(IBlasLapackAdapterDep)
AtlasAdapterDep = $(SRCDIR)/AtlasAdapter.hpp $(IBlasLapackAdapterDep)
GotoBlasAdapterDep = $(SRCDIR)/GotoBlasAdapter.hpp $(IBlasLapackAdapterDep)
IntelMKLAdapterDep = $(SRCDIR)/IntelMKLAdapter.hpp $(IBlasLapackAdapterDep)
ProcessorDep = $(SRCDIR)/Processor.hpp $(ICalculatorDep) $(IErrorGeneratorDep)
ErrorGeneratorDep = $(SRCDIR)/ErrorGenerator.hpp $(IErrorGeneratorDep)

$(BINDIR)/Types.o : $(TypesDep)
$(BINDIR)/Matrix.o : $(MatrixDep)
$(BINDIR)/Vector.o : $(VectorDep)
$(BINDIR)/RowChecksumMatrix.o : $(RowChecksumMatrixDep) $(VectorDep)
$(BINDIR)/ColumnChecksumMatrix.o : $(ColumnChecksumMatrixDep) $(VectorDep)
$(BINDIR)/FullChecksumMatrix.o : $(FullChecksumMatrixDep)
$(BINDIR)/CalculatorNaive.o : $(CalculatorNaiveDep)
$(BINDIR)/CalculatorBlasLapack.o : $(CalculatorBlasLapackDep) $(IFullChecksumMatrixDep)
$(BINDIR)/AtlasAdapter.o : $(AtlasAdapterDep)
$(BINDIR)/GotoBlasAdapter.o : $(GotoBlasAdapterDep)
$(BINDIR)/IntelMKLAdapter.o : $(IntelMKLAdapterDep)
$(BINDIR)/Processor.o : $(ProcessorDep) $(FullChecksumMatrixDep) $(ErrorGeneratorDep)
$(BINDIR)/ErrorGenerator.o : $(ErrorGeneratorDep)

TypesTestDep : $(SRCDIR)/tests/TypesTest.hpp
MatrixTestDep : $(SRCDIR)/tests/MatrixTest.hpp
VectorTestDep : $(SRCDIR)/tests/VectorTest.hpp
RowChecksumMatrixTestDep : $(SRCDIR)/tests/RowChecksumMatrixTest.hpp $(RowChecksumMatrixDep)
ColumnChecksumMatrixTestDep : $(SRCDIR)/tests/ColumnChecksumMatrixTest.hpp $(ColumnChecksumMatrixDep)
FullChecksumMatrixTestDep : $(SRCDIR)/tests/FullChecksumMatrixTest.hpp $(FullChecksumMatrixDep)
CalculatorTestDep : $(SRCDIR)/tests/CalculatorTest.hpp $(MatrixDep) $(ICalculatorDep) $(AtlasAdapterDep) $(GotoBlasAdapterDep) $(IntelMKLAdapterDep) $(ErrorGeneratorDep) $(FullChecksumMatrixDep)
ErrorGeneratorTestDep : $(SRCDIR)/tests/ErrorGeneratorTest.hpp
BenchmarkTestDep : $(SRCDIR)/tests/BenchmarkTest.hpp

$(BINDIR)/tests/TypesTest.o : $(TypesTestDep) $(TypesDep)
$(BINDIR)/tests/MatrixTest.o : $(MatrixTestDep) $(MatrixDep)
$(BINDIR)/tests/VectorTest.o : $(VectorTestDep) $(VectorDep)
$(BINDIR)/tests/RowChecksumMatrixTest.o : $(RowChecksumMatrixTestDep)
$(BINDIR)/tests/ColumnChecksumMatrixTest.o : $(ColumnChecksumMatrixTestDep)
$(BINDIR)/tests/FullChecksumMatrixTest.o : $(FullChecksumMatrixTestDep)
$(BINDIR)/tests/CalculatorTest.o : $(CalculatorTestDep) $(ProcessorDep) $(CalculatorNaiveDep) $(CalculatorBlasLapackDep)
$(BINDIR)/tests/ErrorGeneratorTest.o : $(ErrorGeneratorTestDep) $(ErrorGeneratorDep) $(MatrixDep)
$(BINDIR)/tests/BenchmarkTest.o : $(BenchmarkTestDep) $(FullChecksumMatrixDep) $(CalculatorNaiveDep) $(CalculatorBlasLapackDep) $(AtlasAdapterDep) $(GotoBlasAdapterDep) $(IntelMKLAdapterDep) $(ErrorGeneratorDep)
