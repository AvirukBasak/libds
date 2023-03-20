SRCEXT         := c
OBJEXT         := o
HEADEREXT      := h

## directories

SRC_DIR        := src
BUILD_DIR      := build
TARGET_DIR     := target
LIB_DIR        := lib
TEST_DIR       := tests
INCLUDE_DIR    := include

REQ_DIRS       := $(BUILD_DIR) $(TARGET_DIR)

## compiler options

LIB_NAME       := ds

CC             := gcc
CFLAGS         := -Wall -Ofast
CDBGFLAGS      := -Wall -g -fsanitize=address -D DEBUG
DBG            := gdb -q

INCLUDE        := -I $(INCLUDE_DIR) -I $(LIB_DIR)
LIB            := -L$(LIB_DIR) -lm -ldummy
DBG_LIB        := -L$(LIB_DIR) -lm -ldummy-dbg

LIBRARIES      := $(LIB_DIR)/libdummy.a
DBG_LIBRARIES  := $(LIB_DIR)/libdummy-dbg.a

## targets

TARGET_NAME    := lib$(LIB_NAME)
TARGET         := $(TARGET_DIR)/$(TARGET_NAME).a
DBG_TARGET     := $(TARGET_DIR)/$(TARGET_NAME)-dbg.a
HDR_TARGET     := $(TARGET_DIR)/$(TARGET_NAME).$(HEADEREXT)

TLIB_TARGET    := $(patsubst $(INCLUDE_DIR)/%.$(HEADEREXT), $(TARGET_DIR)/%.$(HEADEREXT), $(shell find $(INCLUDE_DIR)/ -name "*."$(HEADEREXT)))

SOURCES        := $(shell find $(SRC_DIR)/ -name "*."$(SRCEXT))
HEADERS        := $(shell find $(INCLUDE_DIR)/ -name "*."$(HEADEREXT))
TESTSRC        := $(shell find $(TEST_DIR)/ -name "*."$(SRCEXT))

## release build

rel: $(TARGET)

OBJECTS        := $(patsubst $(SRC_DIR)/%.$(SRCEXT), $(BUILD_DIR)/%-rel.$(OBJEXT), $(shell find $(SRC_DIR)/ -name "*."$(SRCEXT)))

$(OBJECTS): $(SOURCES) $(HEADERS)
	@cd $(SRC_DIR) && $(MAKE)

## target for static lib
$(TARGET): $(REQ_DIRS) $(HDR_TARGET) $(TLIB_TARGET) $(OBJECTS)
	ar rcs $(TARGET) $(BUILD_DIR)/*-rel.$(OBJEXT)

## debug build

dbg: $(DBG_TARGET)

DBG_OBJECTS    := $(patsubst $(SRC_DIR)/%.$(SRCEXT), $(BUILD_DIR)/%-dbg.$(OBJEXT), $(shell find $(SRC_DIR)/ -name "*."$(SRCEXT)))

$(DBG_OBJECTS): $(SOURCES) $(HEADERS)
	@cd $(SRC_DIR) && $(MAKE) dbg

## target for static debug lib
$(DBG_TARGET): $(REQ_DIRS) $(HDR_TARGET) $(TLIB_TARGET) $(DBG_OBJECTS)
	ar rcs $(DBG_TARGET) $(BUILD_DIR)/*-dbg.$(OBJEXT)

## build libraries
$(LIBRARIES):
	@cd $(LIB_DIR) && $(MAKE) $(LIBRARIES)

## build libraries
$(DBG_LIBRARIES):
	@cd $(LIB_DIR) && $(MAKE) $(DBG_LIBRARIES)

## make lib headers
$(TARGET_DIR)/%.$(HEADEREXT): $(INCLUDE_DIR)/%.$(HEADEREXT)
	@cp $^ $@
	$(info make $@)

## testing static lib

test: $(LIBRARIES) $(TARGET) $(TESTSRC)
	@$(CC) $(CFLAGS) -I $(TARGET_DIR) $(TEST_DIR)/*.$(SRCEXT) -o $(TEST_DIR)/test-rel.out -L$(TARGET_DIR) -l$(LIB_NAME) $(LIB)
	./$(TEST_DIR)/test-rel.out $(ARGS)

## test in debug mode in gdb
test-dbg: $(TEST_DIR)/test-dbg.out
	$(DBG) $(TEST_DIR)/test-dbg.out

## find memory bugs w/ -fsanitize
test-sanitize: $(TEST_DIR)/test-dbg.out
	@ASAN_OPTIONS=detect_leaks=1 ./$(TEST_DIR)/test-dbg.out $(ARGS)

$(TEST_DIR)/test-dbg.out: $(DBG_LIBRARIES) $(DBG_TARGET) $(TESTSRC)
	@$(CC) $(CDBGFLAGS) -I $(TARGET_DIR) $(TEST_DIR)/*.$(SRCEXT) -o $(TEST_DIR)/test-dbg.out -L$(TARGET_DIR) -l$(LIB_NAME)-dbg $(DBG_LIB)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(TARGET_DIR):
	@mkdir -p $(TARGET_DIR)/avl
	@mkdir -p $(TARGET_DIR)/ctl

## cleanup

clean:
	@cd $(SRC_DIR) && $(MAKE) clean
	@cd $(LIB_DIR) && $(MAKE) clean
	@rm -rf $(TEST_DIR)/*.out

cleaner:
	@cd $(SRC_DIR) && $(MAKE) cleaner
	@cd $(LIB_DIR) && $(MAKE) cleaner
	@rm -rf $(TEST_DIR)/*.out
	@rm -rf $(BUILD_DIR)
	@rm -rf $(TARGET)
	@rm -rf $(DBG_TARGET)
	@rm -rf $(HDR_TARGET)
	@rm -rf $(TLIB_TARGET)
	@rm -rf $(TARGET_DIR)
