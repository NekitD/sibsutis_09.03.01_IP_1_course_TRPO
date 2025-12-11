CC = gcc
APP_NAME = geometry
LIB_NAME = libgeometry

CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -I src -MP -MMD
LDFLAGS = -L $(OBJ_DIR)/$(SRC_DIR)/$(LIB_NAME)/

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src


APP_PATH = $(BIN_DIR)/$(APP_NAME)
LIB_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(LIB_NAME)/$(LIB_NAME).a


APP_SOURCES = $(wildcard $(SRC_DIR)/$(APP_NAME)/*.c)
APP_OBJECTS = $($(APP_SOURCES):$(SRC_DIR)/$(APP_NAME)/%.c=$(OBJ_DIR)/$(SRC_DIR)/$(APP_NAME)/%.o)

LIB_SOURCES = $(wildcard $(SRC_DIR)/$(LIB_NAME)/*.c)
LIB_OBJECTS = $($(LIB_SOURCES):$(SRC_DIR)/$(LIB_NAME)/%.c=$(OBJ_DIR)/$(SRC_DIR)/$(LIB_NAME)/%.o)

DEPS = $(APP_OBJECTS: .o=.d) $(LIB_OBJECTS: .o=.d)

.PHONY: all clean
all: $(APP_PATH)

-include $(DEPS)

$(APP_PATH): $(OBJ_DIR)/$(SRC_DIR)/$(APP_NAME)/*.o $(OBJ_DIR)/$(SRC_DIR)/$(LIB_NAME)/*.a
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ $(LDFLAGS) -lm

$(OBJ_DIR)/$(SRC_DIR)/$(LIB_NAME)/*.a: $(OBJ_DIR)/$(SRC_DIR)/$(LIB_NAME)/*.o 
	ar rcs $@ $^

$(OBJ_DIR)/$(SRC_DIR)/$(APP_NAME)/*.o: $(SRC_DIR)/$(APP_NAME)/*.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@ -lm

$(OBJ_DIR)/$(SRC_DIR)/$(LIB_NAME)/*.o: $(SRC_DIR)/$(LIB_NAME)/*.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@ -lm

clean:
	$(RM) $(APP_PATH) $(LIB_PATH) $(APP_OBJECTS) $(LIB_OBJECTS) $(DEPS)

