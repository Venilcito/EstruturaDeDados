# --- Makefile Árvore RED BLACK!!!!! ---

ifeq ($(OS), Windows_NT)
$(error Deixa de ser BAGRE e roda isso aqui no linux.)
else
$(info Muito bem, tem que usar o linux mesmo. Compilando...)
endif

# Compilador C++
CXX = g++

# Flags de compilação:
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# .cpp principal
SRC = dicionario.cpp

# O nome do executável final
TARGET = myrb

# --- Regras ---

# Regra principal (o que 'make' faz por padrão)
all: $(TARGET)

# Regra para buildar o executável
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Regra 'clean' para apagar o executável
clean:
	rm -f $(TARGET)

.PHONY: all clean

