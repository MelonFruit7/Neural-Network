.PHONY: clean

EXE = Network

CC = g++
SRCS = main.cpp Network.cpp Neuron.cpp NetworkTools.cpp TrainSet.cpp
LIBS = -lraylib -ldl -lpthread -lX11 -lm -O2

${EXE}: ${SRCS}
	${CC} ${SRCS} -o ${EXE} ${LIBS}

clean:
	rm -f ${EXE}