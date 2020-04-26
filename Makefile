################
#   Makefile   # 
################

#Name, headers, sources
TARGET=URL2
_DEPS=common.hh LZespolona.hh Wektor.hh #MacierzKw.hh UklRowL.hh
_OBJ=common.o main.o LZespolona.o WektorComp.o #MacierzKwComp.o UklRowLComp.o

####DIRS###
TRG_DIR=./
OBJ_DIR=./obj
INC_DIR=./inc
SRC_DIR=./src

###COMPILER###
CC = g++
CFLAGS = -Wall -pedantic -std=c++17 -iquote $(INC_DIR)
LFLAGS = -Wall -pedantic -std=c++17 -iquote $(INC_DIR)

###FORMULA###
DEPS = $(patsubst %,$(INC_DIR)/%,$(_DEPS))
OBJ = $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))

all: $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LFLAGS)

.PHONY: clean

clean:
	rm -f ${TRGDIR}$(TARGET) ${OBJ_DIR}/*

