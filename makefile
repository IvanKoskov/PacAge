CC = gcc
CFLAGS = -Wall
BUILD_DIR = bin
TARGET = ${BUILD_DIR}/pacage
SRC = main.c alert.c createconf.c config.c clone.c modify.c newrepo.c showrepos.c deleterepo.c searchingforfiles.c searchexec.c listinstalled.c updateCommand.c

# Default target to build the program
all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(TARGET): $(SRC)
	@echo "BUILDING"
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

install: $(TARGET)
	@echo "Installing to /usr/local/bin"
	mv $(TARGET) /usr/local/bin

# Clean up build artifacts
clean:
	rm -rf $(BUILD_DIR)

# Phony targets
.PHONY: all clean install
