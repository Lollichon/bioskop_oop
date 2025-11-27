# Nama output
TARGET = bioskop

# Folder
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

# Compiler
CXX = g++
CXXFLAGS = -I$(INC_DIR) -std=c++17 -Wall

# Semua file .cpp di src/
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Mengubah .cpp → .o
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Rule utama
all: $(TARGET)

# Link semua object
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# Compile tiap .cpp → .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Buat folder obj jika belum ada
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Bersihkan file
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

# Hapus folder build total
cleanall:
	rm -rf $(OBJ_DIR) $(TARGET)
