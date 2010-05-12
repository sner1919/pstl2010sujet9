# +++++++++++++++++++ Variables +++++++++++++++++++
CPU = VMWareCore1
CXX = g++
CXXFLAGS = -W -Wall -D CPU=$(CPU) ${DEBUGFLAG} #rq : ${DEBUGFLAG} ajouté à la configuration de construction "Debug" dans eclipse cdt
LDFLAGS = #-L./lib/$(CPU)/atlas/ -Wl,--rpath,./lib/$(CPU)/atlas/ -L./lib/$(CPU)/gotoblas/ -Wl,--rpath,./lib/$(CPU)/gotoblas/ -L./lib/$(CPU)/intelmkl/ -Wl,--rpath,./lib/$(CPU)/intelmkl/ 
LDLIBS = -lpthread -lgmpxx -lgmp -ldl #-lclapack -lcblas -latlas -lgoto2 -lgfortran -Wl,--start-group -lmkl_intel -lmkl_sequential -lmkl_core -Wl,--end-group
INCLUDES =
PREPROCESS_AND_COMPIL = $(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@
LINK = $(CXX) -o $@ $^ $(LDFLAGS) $(LDLIBS)
SRCDIR = ./src
IFACEDIR = $(SRCDIR)/interfaces
BINDIR = ./bin
OBJ = $(BINDIR)/Matrix.o $(BINDIR)/Vector.o $(BINDIR)/RowChecksumMatrix.o $(BINDIR)/ColumnChecksumMatrix.o $(BINDIR)/FullChecksumMatrix.o $(BINDIR)/CalculatorNaive.o $(BINDIR)/CalculatorBlasLapack.o $(BINDIR)/AtlasAdapter.o $(BINDIR)/GotoBlasAdapter.o $(BINDIR)/IntelMKLAdapter.o $(BINDIR)/Processor.o $(BINDIR)/ErrorGenerator.o
OBJTEST = $(OBJ) $(BINDIR)/tests/MatrixTest.o $(BINDIR)/tests/VectorTest.o $(BINDIR)/tests/RowChecksumMatrixTest.o $(BINDIR)/tests/ColumnChecksumMatrixTest.o $(BINDIR)/tests/FullChecksumMatrixTest.o $(BINDIR)/tests/CalculatorTest.o $(BINDIR)/tests/ErrorGeneratorTest.o $(BINDIR)/tests/BenchmarkTest.o
PROGS = $(BINDIR)/PSTL $(BINDIR)/tests/PSTLTest

# +++++++++++++++++++ Cibles habituelles +++++++++++++++++++
all : $(PROGS)

clean :
	rm -f $(PROGS) $(BINDIR)/*.o $(BINDIR)/tests/*.o

.PHONY: all clean

# +++++++++++++++++++ Fichiers exécutables +++++++++++++++++++
$(BINDIR)/PSTL : $(SRCDIR)/PSTL.cpp $(OBJ)
	$(LINK)

$(BINDIR)/tests/PSTLTest : $(SRCDIR)/tests/PSTLTest.cpp $(OBJTEST)
	$(LINK) -lcppunit
	
# +++++++++++++++++++ Fichiers objets +++++++++++++++++++
$(BINDIR)/%.o : $(SRCDIR)/%.cpp
	$(PREPROCESS_AND_COMPIL)

$(BINDIR)/tests/%.o : $(SRCDIR)/tests/%.cpp
	$(PREPROCESS_AND_COMPIL)
	
# +++++++++++++++++++ Dépendances +++++++++++++++++++
IMatrixDep = $(IFACEDIR)/IMatrix.hpp $(SRCDIR)/settings.hpp
IVectorDep = $(IFACEDIR)/IVector.hpp $(IMatrixDep)
IRowChecksumMatrixDep = $(IFACEDIR)/IRowChecksumMatrix.hpp $(IMatrixDep) $(IVectorDep)
IColumnChecksumMatrixDep = $(IFACEDIR)/IColumnChecksumMatrix.hpp $(IMatrixDep) $(IVectorDep)
IFullChecksumMatrixDep = $(IFACEDIR)/IFullChecksumMatrix.hpp $(IRowChecksumMatrixDep) $(IColumnChecksumMatrixDep)
ICalculatorDep = $(IFACEDIR)/ICalculator.hpp $(IMatrixDep)
IBlasLapackAdapterDep = $(IFACEDIR)/IBlasLapackAdapter.hpp $(SRCDIR)/settings.hpp
IErrorGeneratorDep = $(IFACEDIR)/IErrorGenerator.hpp $(IMatrixDep)

MatrixDep = $(SRCDIR)/Matrix.hpp $(IMatrixDep)
VectorDep = $(SRCDIR)/Vector.hpp $(IVectorDep) $(MatrixDep)
RowChecksumMatrixDep = $(SRCDIR)/RowChecksumMatrix.hpp $(IRowChecksumMatrixDep) $(MatrixDep) $(VectorDep)
ColumnChecksumMatrixDep = $(SRCDIR)/ColumnChecksumMatrix.hpp $(IColumnChecksumMatrixDep) $(MatrixDep) $(VectorDep)
FullChecksumMatrixDep = $(SRCDIR)/FullChecksumMatrix.hpp $(IFullChecksumMatrixDep) $(RowChecksumMatrixDep) $(ColumnChecksumMatrixDep)
CalculatorNaiveDep = $(SRCDIR)/CalculatorNaive.hpp $(ICalculatorDep)
CalculatorBlasLapackDep = $(SRCDIR)/CalculatorBlasLapack.hpp $(ICalculatorDep) $(IBlasLapackAdapterDep)
AtlasAdapterDep = $(SRCDIR)/AtlasAdapter.hpp $(IBlasLapackAdapterDep)
GotoBlasAdapterDep = $(SRCDIR)/GotoBlasAdapter.hpp $(IBlasLapackAdapterDep)
IntelMKLAdapterDep = $(SRCDIR)/IntelMKLAdapter.hpp $(IBlasLapackAdapterDep)
ProcessorDep = $(SRCDIR)/Processor.hpp $(ICalculatorDep) $(FullChecksumMatrixDep) $(ErrorGeneratorDep)
ErrorGeneratorDep = $(SRCDIR)/ErrorGenerator.hpp $(IErrorGeneratorDep)

$(BINDIR)/Matrix.o : $(MatrixDep)
$(BINDIR)/Vector.o : $(VectorDep)
$(BINDIR)/RowChecksumMatrix.o : $(RowChecksumMatrixDep)
$(BINDIR)/ColumnChecksumMatrix.o : $(ColumnChecksumMatrixDep)
$(BINDIR)/FullChecksumMatrix.o : $(FullChecksumMatrixDep)
$(BINDIR)/CalculatorNaive.o : $(CalculatorNaiveDep)
$(BINDIR)/CalculatorBlasLapack.o : $(CalculatorBlasLapackDep)
$(BINDIR)/AtlasAdapter.o : $(AtlasAdapterDep)
$(BINDIR)/GotoBlasAdapter.o : $(GotoBlasAdapterDep)
$(BINDIR)/IntelMKLAdapter.o : $(IntelMKLAdapterDep)
$(BINDIR)/Processor.o : $(ProcessorDep)
$(BINDIR)/ErrorGenerator.o : $(ErrorGeneratorDep)

$(BINDIR)/tests/MatrixTest.o : $(SRCDIR)/tests/MatrixTest.hpp $(MatrixDep)
$(BINDIR)/tests/VectorTest.o : $(SRCDIR)/tests/VectorTest.hpp $(VectorDep)
$(BINDIR)/tests/RowChecksumMatrixTest.o : $(SRCDIR)/tests/RowChecksumMatrixTest.hpp $(RowChecksumMatrixDep)
$(BINDIR)/tests/ColumnChecksumMatrixTest.o : $(SRCDIR)/tests/ColumnChecksumMatrixTest.hpp $(ColumnChecksumMatrixDep)
$(BINDIR)/tests/FullChecksumMatrixTest.o : $(SRCDIR)/tests/FullChecksumMatrixTest.hpp $(FullChecksumMatrixDep)
$(BINDIR)/tests/CalculatorTest.o : $(SRCDIR)/tests/CalculatorTest.hpp $(MatrixDep) $(CalculatorNaiveDep) $(CalculatorBlasLapackDep) $(AtlasAdapterDep) $(GotoBlasAdapterDep) $(IntelMKLAdapterDep) $(ProcessorDep)
$(BINDIR)/tests/ErrorGeneratorTest.o : $(SRCDIR)/tests/ErrorGeneratorTest.hpp $(MatrixDep) $(ErrorGeneratorDep)
$(BINDIR)/tests/BenchmarkTest.o : $(SRCDIR)/tests/BenchmarkTest.hpp $(FullChecksumMatrixDep) $(CalculatorNaiveDep) $(CalculatorBlasLapackDep) $(AtlasAdapterDep) $(GotoBlasAdapterDep) $(IntelMKLAdapterDep) $(ErrorGeneratorDep)
