# Compilador
CXX = g++
# Flags de compilación
CXXFLAGS = -std=c++11 -Wall -Wextra -g

# Archivos fuente y objeto
SRCS = main.cpp Automaton.cpp State.cpp
OBJS = $(SRCS:.cpp=.o)

# Ejecutable
TARGET = automaton_sim

# Regla por defecto: compilar el programa
all: $(TARGET)

# Regla para generar el ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Regla para compilar los archivos .cpp a .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Regla para limpiar los archivos generados
clean:
	rm -f $(OBJS) $(TARGET)

# Regla para limpiar todo, incluyendo los archivos temporales
distclean: clean
	rm -f *~ *.bak

# Phony targets
.PHONY: all clean distclean
