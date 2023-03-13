CC = g++
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include
CFLAGS = -std=c++11 -I$(INCLUDE_DIR)

EXECUTABLE_FILE = server.out
OBJECTS = \
	$(BUILD_DIR)/server.o \
	$(BUILD_DIR)/main.o \
	$(BUILD_DIR)/cmdHandler.o \
	$(BUILD_DIR)/jsonReader.o \
	$(BUILD_DIR)/room.o \
	$(BUILD_DIR)/user.o \
	$(BUILD_DIR)/date.o \
	$(BUILD_DIR)/logger.o \
	$(BUILD_DIR)/exception.o \
	$(BUILD_DIR)/response.o

userSensitivityList = \
	$(SRC_DIR)/user.cpp \
	$(INCLUDE_DIR)/user.hpp

jsonReaderSensitivityList = \
	$(SRC_DIR)/jsonReader.cpp \
	$(INCLUDE_DIR)/jsonReader.hpp

cmdHandlerSensitivityList = \
	$(SRC_DIR)/cmdHandler.cpp \
	$(INCLUDE_DIR)/cmdHandler.hpp

serverSensitivityList = \
	$(SRC_DIR)/server.cpp \
	$(INCLUDE_DIR)/server.hpp

mainSensitivityList = \
	$(SRC_DIR)/main.cpp \
	$(INCLUDE_DIR)/server.hpp \

dateSensitivityList = \
	$(SRC_DIR)/date.cpp \
	$(INCLUDE_DIR)/date.hpp \
	$(INCLUDE_DIR)/consts.hpp

loggerSensitivityList = \
	$(SRC_DIR)/logger.cpp \
	$(INCLUDE_DIR)/logger.hpp \
	$(INCLUDE_DIR)/consts.hpp

roomSensitivityList = \
	$(SRC_DIR)/room.cpp \
	$(INCLUDE_DIR)/room.hpp

exceptionSensitivityList = \
	$(SRC_DIR)/exception.cpp \
	$(INCLUDE_DIR)/exception.hpp

responseSensitivityList = \
	$(SRC_DIR)/response.cpp \
	$(INCLUDE_DIR)/response.hpp

all: $(BUILD_DIR) $(EXECUTABLE_FILE)

$(EXECUTABLE_FILE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE_FILE)

$(BUILD_DIR)/room.o: $(roomSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/room.cpp -o $(BUILD_DIR)/room.o

$(BUILD_DIR)/main.o: $(mainSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/logger.o: $(loggerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/logger.cpp -o $(BUILD_DIR)/logger.o

$(BUILD_DIR)/server.o: $(serverSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/cmdHandler.o: $(cmdHandlerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/cmdHandler.cpp -o $(BUILD_DIR)/cmdHandler.o

$(BUILD_DIR)/jsonReader.o: $(jsonReaderSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jsonReader.cpp -o $(BUILD_DIR)/jsonReader.o

$(BUILD_DIR)/user.o: $(userSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/user.cpp -o $(BUILD_DIR)/user.o

$(BUILD_DIR)/date.o: $(dateSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/date.cpp -o $(BUILD_DIR)/date.o

$(BUILD_DIR)/exception.o: $(exceptionSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/exception.cpp -o $(BUILD_DIR)/exception.o

$(BUILD_DIR)/response.o: $(responseSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out