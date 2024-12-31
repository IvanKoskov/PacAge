CC = gcc
CFLAGS = -Wall
BUILD_DIR = bin
TARGET = ${BUILD_DIR}/pacage
SRC = main.c alert.c createconf.c config.c clone.c modify.c newrepo.c showrepos.c deleterepo.c searchingforfiles.c searchexec.c

# Default target to build the program
all: $(TARGET)

$(TARGET): $(SRC)
	@echo "BUILDING"
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

install: $(TARGET)
	mv pacage /usr/local/bin

# Clean up build artifacts
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: all clean
