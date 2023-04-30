CC = g++
CFLAGS = -std=c++14 -O2

SRCS = main.cpp 			# Archivo a compilar
OBJS = $(SRCS:.cpp=.o)

TEST_CASES_NUMBER := $(shell seq 1 7) # corresponde a los input que queremos utilizar

RANGE = 2 3					# indice de los algoritmos que queremos utilizar (definido en main.cpp)

INPUT_PREFIX := tests/input		# path a los input

OUTPUT_PREFIX := output			# path de los archivos de salida

all: program				# itera sobre los algoritmo y luegos sobre los input
	for j in $(RANGE); do \
		for i in $(TEST_CASES_NUMBER); do \
			echo "./program --test $$j < $(INPUT_PREFIX)$$i.in > $(OUTPUT_PREFIX)$$j$$i.txt"; \
			./program $$j --test < $(INPUT_PREFIX)$$i.in > output/$(OUTPUT_PREFIX)$$j$$i.txt; \
		done; \
		for i in $(TEST_CASES_NUMBER); do \
			diff -q -bB -y $(OUTPUT_PREFIX)$$j$$i.txt tests/output$$i.out; \
		done; \
		echo "Executing program with $$j"; \
		./program $$j; \
	done

program: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o program

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) program output*
