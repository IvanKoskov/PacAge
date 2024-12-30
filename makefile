CC = gcc
CFLAGS = -Wall
TARGET = pacage
SRC = main.c alert.c createconf.c config.c clone.c modify.c newrepo.c showrepos.c deleterepo.c searchingforfiles.c searchexec.c

# Default target to build the program
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# Clean up build artifacts
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: all clean
