CC := gcc

PROJ_NAME := Ruins
BIN_DIR := bin
INT_DIR := $(BIN_DIR)/int
VENDOR_DIR := vendor
SRC_DIR := src
ASSETS_DIR := assets

INCLUDES := include $(VENDOR_DIR)/SDL2/include $(VENDOR_DIR)/tmx/include
LIB_DIRS := $(VENDOR_DIR)/SDL2/lib $(VENDOR_DIR)/tmx/lib

SOURCES := $(shell find $(SRC_DIR) -type f -name "*.c" ! -wholename "$(SRC_DIR)/config_assets.c")
OBJECTS := $(SOURCES:$(SRC_DIR)/%.c=$(INT_DIR)/%.o)
DEPENDS := $(OBJECTS:%.o=%.d)
SDL2_DLLS := $(shell find $(VENDOR_DIR)/SDL2/dll -type f -name "*.dll")
TMX_DLLS := $(shell find $(VENDOR_DIR)/tmx/dll -type f -name "*.dll")
DLLS := $(SDL2_DLLS) $(TMX_DLLS)

TARGET := $(BIN_DIR)/$(PROJ_NAME)

config ?= debug
ifeq ($(config),debug)
	WARNINGS := -Wall -Wextra -Wpedantic
	CFLAGS := -DDEBUG -g3 -ggdb $(WARNINGS) -MMD -MP
else ifeq ($(config),release)
	CFLAGS := -O3 -Wall -Wextra -Wpedantic -MMD -MP
endif
LDFLAGS := -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -ltmx $(addprefix -L,$(LIB_DIRS)) -Wl,-Map,$(TARGET).map

ifeq ($(verbose),1)
else
	MUTE := @
endif

all: dir assets $(TARGET) db
	@echo All done

build: dir assets $(TARGET)
	@echo Build done

dir:
	@echo Creating build directory
	$(MUTE)mkdir -p $(INT_DIR)

assets: dir $(BIN_DIR)/config_assets $(ASSETS_DIR)/assets.conf
	@echo Copying assets
	$(MUTE)cp -r $(ASSETS_DIR)/. $(BIN_DIR)
	$(MUTE)$(BIN_DIR)/config_assets $(ASSETS_DIR)/assets.conf > include/ruins_asset_defines.h

$(BIN_DIR)/config_assets: $(INT_DIR)/config_assets.o $(INT_DIR)/ruins_parser.o $(INT_DIR)/ruins_string.o $(INT_DIR)/ruins_containers.o
	$(MUTE)$(CC) $^ -Wl,-Map,$(BIN_DIR)/config_assets.map -o $@

$(TARGET): $(OBJECTS)
	@echo Linking $@
	$(MUTE)$(CC) $^ $(LDFLAGS) -o $@
	@echo Copying dlls
	$(MUTE)cp $(DLLS) $(BIN_DIR)

$(INT_DIR)/%.o: $(SRC_DIR)/%.c
	@echo Compiling $<
	$(MUTE)$(CC) $(CFLAGS) -Iinclude -I$(VENDOR_DIR)/SDL2/include -I$(VENDOR_DIR)/tmx/include -c $< -o $@

-include $(DEPENDS)

db:
	@echo Generating compile_commands.json
	$(MUTE)compiledb -n make --cmd=mingw32-make

run:
	@echo Running $(TARGET)
	$(MUTE)cd $(BIN_DIR) && ./$(PROJ_NAME)

clean:
	$(MUTE)rm -rf include/ruins_asset_defines.h
	$(MUTE)rm -rf $(BIN_DIR)
	@echo Clean done

.PHONY: all build clean dir assets db run
