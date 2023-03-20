SRCEXT         := c
OBJEXT         := o
HEADEREXT      := h

## directories

SRC_DIR        := ../src
BUILD_DIR      := ../build
TARGET_DIR     := ../target
LIB_DIR        := ../lib
TEST_DIR       := ../tests
INCLUDE_DIR    := ../include

## compiler options

LIB_NAME       := libds

CC             := gcc
CFLAGS         := -Wall -Ofast
CDBGFLAGS      := -Wall -g -fsanitize=address -D DEBUG
DBG            := gdb -q

INCLUDE        := -I $(INCLUDE_DIR) -I $(LIB_DIR)
LIB            := -L$(LIB_DIR) -lm -ldummy
DBG_LIB        := -L$(LIB_DIR) -lm -ldummy-dbg

HEADERS        := $(shell find $(INCLUDE_DIR)/ -name "*."$(HEADEREXT))

SUB_DIRS       := $(shell find -type f -name Makefile | sed 's/Makefile//g')
SUB_DIR_DBG    := $(SUB_DIRS)

AVLSRC         := $(shell find avl/ -name "*."$(SRCEXT))

## release build

AVL_OBJ        := $(patsubst avl/%.$(SRCEXT), %-rel.$(OBJEXT), $(AVLSRC))
OBJECTS        := $(patsubst %.$(SRCEXT), %-rel.$(OBJEXT), $(wildcard *.$(SRCEXT))) $(AVL_OBJ)

rel: mkdirp $(OBJECTS) cpobj

%-rel.$(OBJEXT): avl/%.$(SRCEXT) $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

%-rel.$(OBJEXT): %.$(SRCEXT) $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

## build subdirs
# $(SUB_DIRS): FORCE
# @$(MAKE) -C $@

## debug build

AVL_DBGOBJ     := $(patsubst avl/%.$(SRCEXT), %-dbg.$(OBJEXT), $(AVLSRC))
DBG_OBJECTS    := $(patsubst %.$(SRCEXT), %-dbg.$(OBJEXT), $(wildcard *.$(SRCEXT))) $(AVL_DBGOBJ)

dbg: mkdirp $(DBG_OBJECTS) cpobj

%-dbg.$(OBJEXT): avl/%.$(SRCEXT) $(HEADERS)
	$(CC) $(CDBGFLAGS) $(INCLUDE) -c -o $@ $<

%-dbg.$(OBJEXT): %.$(SRCEXT) $(HEADERS)
	$(CC) $(CDBGFLAGS) $(INCLUDE) -c -o $@ $<

## build subdirs
# $(SUB_DIR_DBG): FORCE
#     @$(MAKE) -C $@ dbg

cpobj:
	@cp *.$(OBJEXT) $(BUILD_DIR)

mkdirp:
	@mkdir -p $(BUILD_DIR)

clean:
	@rm -f *.$(OBJEXT)

cleaner: clean
	@rm -f $(BUILD_DIR)/*.$(OBJEXT)

## FORCE:
