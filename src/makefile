# Fichero make para compilar C_FlowGround
CC = gcc

# Etiquetas para el compilador
# -Wall :
# -lm
CFLAGS = -Wall -lm

# Nombre del programa
TARGET = C_FlowGround

all: $(TARGET)

$(TARGET): $(TARGET).c
	   $(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	$(RM) $(TARGET)
