# --- CONFIGURACIÓN DEL COMPILADOR ---
CXX = g++.exe

# --- CONFIGURACIÓN DEL PROYECTO ---
TARGET = output/Canciones.exe
DEBUG_TARGET = output/Canciones_debug.exe

# --- BANDERAS (FLAGS) DE COMPILACIÓN Y ENLACE ---
# Se eliminaron las flags de SFML que no son necesarias
CXXFLAGS = -std=c++14 -Iinclude -m64
LDFLAGS = -static-libgcc -static-libstdc++ -m64
LIBS = 

# --- BANDERAS (FLAGS) DE DEPURACIÓN ---
DEBUG_CXXFLAGS = $(CXXFLAGS) -g -O0

# --- BÚSQUEDA AUTOMÁTICA DE ARCHIVOS ---
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
DEBUG_OBJECTS = $(SOURCES:.cpp=.o.debug)

# --- REGLAS DE MAKEFILE ---
all: $(TARGET)

debug: $(DEBUG_TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS) $(LIBS)

$(DEBUG_TARGET): $(DEBUG_OBJECTS)
	$(CXX) $(DEBUG_OBJECTS) -o $(DEBUG_TARGET) $(LDFLAGS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o.debug: %.cpp
	$(CXX) $(DEBUG_CXXFLAGS) -c $< -o $@

# --- REGLAS ADICIONALES ---
clean:
	rm -f src/*.o src/*.o.debug $(TARGET) $(DEBUG_TARGET)

run: all
	./$(TARGET)

run-debug: debug
	./$(DEBUG_TARGET)