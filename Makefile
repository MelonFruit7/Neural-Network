.PHONY: clean

EXE = Network

CC = g++
SRCS = main.cpp Network.cpp Neuron.cpp NetworkTools.cpp
LIBS = -lm

${EXE}: ${SRCS}
	${CC} ${SRCS} -o ${EXE} ${LIBS}

clean:
	rm -f ${EXE}