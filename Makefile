CC := gcc

BIN_DIR := bin
INT_DIR := $(BIN_DIR)/int
VENDOR_DIR := vendor
SRC_DIR := src
INCLUDES := include $(VENDOR_DIR)/SDL2/include
LIB_DIRS := $(VENDOR_DIR)/SDL2/lib
ASSETS_DIR := assets
SOURCES := $(shell find $(SRC_DIR) -type f -name "*.c")
OBJECTS := $(SOURCES:$(SRC_DIR)/%.c=$(INT_DIR)/%.o)
DEPENDS := $(OBJECTS:%.o=%.d)
DLLS := $(shell find $(VENDOR_DIR) -type f -path "*/bin/*.dll")
TARGET := $(BIN_DIR)/Ruins

config ?= debug
ifeq ($(config),debug)
	CFLAGS := -DDEBUG -g3 -ggdb $(addprefix -I,$(INCLUDES)) -Wall -Wextra -Wpedantic -MMD -MP
else ifeq ($(config),release)
	CFLAGS := -O3 $(addprefix -I,$(INCLUDES)) -Wall -Wextra -Wpedantic -MMD -MP
endif
LDFLAGS := -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer $(addprefix -L,$(LIB_DIRS)) -Wl,-Map,$(TARGET).map

ifeq ($(verbose),1)
else
	MUTE := @
endif

all: dir $(TARGET) db
	@echo -e "\033[1;32mAll done\033[0m"

dir:
	@echo -e "\033[1;32mCreating build directory\033[0m"
	$(MUTE)mkdir -p $(INT_DIR)

$(TARGET): $(OBJECTS)
	@echo -e "\033[1;32mLinking $@\033[0m"
	$(MUTE)$(CC) $^ $(LDFLAGS) -o $@
	@echo -e "\033[1;32mCopying dlls and assets\033[0m"
	$(MUTE)cp $(DLLS) $(BIN_DIR)
	$(MUTE)cp -r $(ASSETS_DIR) $(BIN_DIR)

$(INT_DIR)/%.o: $(SRC_DIR)/%.c
	@echo -e "\033[1;32mCompiling $<\033[0m"
	$(MUTE)$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPENDS)

db:
	@echo -e "\033[1;32mGenerating compile_commands.json\033[0m"
	$(MUTE)compiledb -n make --cmd=mingw32-make

run:
	@echo -e "\033[1;32mRunning $(TARGET)\033[0m"
	$(MUTE)cd $(BIN_DIR)
	$(MUTE)./$(TARGET)

clean:
	$(MUTE)rm -rf $(BIN_DIR)
	@echo -e "\033[1;32mClean done\033[0m"

.PHONY: all clean
