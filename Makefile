# Derleyici ve bayraklar
CC = gcc
CFLAGS = -Wall -I./include

# Klasörler
SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin

# Kaynak dosyaları
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/directory_ops.c $(SRC_DIR)/file_ops.c $(SRC_DIR)/logger.c $(SRC_DIR)/permissions.c $(SRC_DIR)/color_utils.c
# Hedef nesne dosyaları
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Çıktı dosyası
TARGET = $(BIN_DIR)/mainProgram

# Varsayılan hedef: derleme ve çalıştırma
all: $(TARGET)

# Nesne dosyalarını derleyin
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)  # obj dizini yoksa oluştur
	$(CC) $(CFLAGS) -c $< -o $@

# Programı bağla (linkle)
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)  # bin dizini yoksa oluştur
	$(CC) $(OBJS) -o $(TARGET)

# Programı çalıştır
run: $(TARGET)
	$(TARGET)

# Temizleme
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Nesne dosyalarını ve çıktıyı temizle
fclean: clean
	rm -f $(TARGET)

# Sadece derleme işlemi
re: fclean all
