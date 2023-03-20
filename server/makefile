CC        := g++
PROJECT   := server
SRC_DIR    := src
BUILD_DIR  := build
EXE_DIR    := exe
TARGET    := $(EXE_DIR)/$(PROJECT)
SOURCES   := $(shell find $(SRC_DIR) -type f -name *.c*)
OBJECTS   := $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%, \
$(addsuffix .o,$(basename $(SOURCES))))
CFLAGS    := 
LIB       := -ljsoncpp
INC       := -I inc -I src

all: $(TARGET)

$(TARGET): $(EXE_DIR) $(BUILD_DIR) $(OBJECTS)
	@$(CC) $(OBJECTS) -o $(TARGET) $(LIB)

$(BUILD_DIR) :
	mkdir $(BUILD_DIR)

$(EXE_DIR):
	mkdir $(EXE_DIR)
	
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c*
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
	@$(CC) $(CFLAGS) $(INC) -M $< -MT $@ > $(@:.o=.td)
	@cp $(@:.o=.td) $(@:.o=.d); 
	@sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $(@:.o=.td) >> $(@:.o=.d); 
	@rm -f $(@:.o=.td)


.PHONY: clean all

clean:
	rm $(BUILD_DIR) $(EXE_DIR) -rf



