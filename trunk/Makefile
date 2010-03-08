# +++++++++++++++++++ Variables +++++++++++++++++++
CXX = g++
CXXFLAGS = -Wall
LDFLAGS = -lcppunit
LDLIBS =
INCLUDES =
PREPROCESS_AND_COMPIL = $(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@
LINK = $(CXX) $(LDFLAGS) $(LDLIBS) $^ -o $@
SRCDIR = ./src
IFACEDIR = $(SRCDIR)/interfaces
BINDIR = ./bin
OBJ = $(BINDIR)/Vector.o $(BINDIR)/Matrix.o $(BINDIR)/RowChecksumMatrix.o $(BINDIR)/ColumnChecksumMatrix.o $(BINDIR)/FullChecksumMatrix.o $(BINDIR)/Calculator.o $(BINDIR)/Processor.o
OBJTEST = $(OBJ) $(BINDIR)/MatrixTest.o $(BINDIR)/VectorTest.o
PROGS = $(BINDIR)/PSTL $(BINDIR)/PSTLTest

# +++++++++++++++++++ Cibles habituelles +++++++++++++++++++
all : $(PROGS)

clean :
	rm -f $(PROGS) $(BINDIR)/*.o

.PHONY: all clean

# +++++++++++++++++++ Fichiers exécutables +++++++++++++++++++
$(BINDIR)/PSTL : $(BINDIR)/PSTL.o $(OBJ)
	$(LINK)

$(BINDIR)/PSTLTest : $(BINDIR)/PSTLTest.o $(OBJTEST)
	$(LINK)
	
# +++++++++++++++++++ Fichiers objets +++++++++++++++++++
$(BINDIR)/%.o : $(SRCDIR)/%.cpp
	$(PREPROCESS_AND_COMPIL)

$(BINDIR)/%Test.o : $(SRCDIR)/tests/%Test.cpp
	$(PREPROCESS_AND_COMPIL)

# +++++++++++++++++++ Dépendances habituelles +++++++++++++++++++
%.cpp : %.hpp
	
# +++++++++++++++++++ Dépendances spécifiques +++++++++++++++++++
$(SRCDIR)/Matrix.hpp : $(SRCDIR)/interfaces/IMatrix.hpp

$(IFACEDIR)/IVector.hpp : $(IFACEDIR)/IMatrix.hpp
$(SRCDIR)/Vector.cpp : $(IFACEDIR)/IVector.hpp $(SRCDIR)/Matrix.cpp

$(IFACEDIR)/IRowChecksumMatrix.hpp : $(IFACEDIR)/IMatrix.hpp $(IFACEDIR)/IVector.hpp
$(SRCDIR)/RowChecksumMatrix.cpp : $(IFACEDIR)/IRowChecksumMatrix.hpp $(SRCDIR)/Matrix.cpp $(SRCDIR)/Vector.cpp

$(IFACEDIR)/IColumnChecksumMatrix.hpp : $(IFACEDIR)/IMatrix.hpp $(IFACEDIR)/IVector.hpp
$(SRCDIR)/ColumnChecksumMatrix.cpp : $(IFACEDIR)/IColumnChecksumMatrix.hpp $(SRCDIR)/Matrix.cpp $(SRCDIR)/Vector.cpp

$(IFACEDIR)/IFullChecksumMatrix.hpp : $(IFACEDIR)/IRowChecksumMatrix.hpp $(IFACEDIR)/IColumnChecksumMatrix.hpp
$(SRCDIR)/FullChecksumMatrix.cpp : $(IFACEDIR)/IFullChecksumMatrix.hpp $(IFACEDIR)/IRowChecksumMatrix.hpp $(IFACEDIR)/IColumnChecksumMatrix.hpp

$(IFACEDIR)/ICalculator.hpp : $(IFACEDIR)/IMatrix.hpp
$(SRCDIR)/Calculator.cpp : $(IFACEDIR)/ICalculator.hpp

$(SRCDIR)/Processor.cpp : $(IFACEDIR)/ICalculator.hpp