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

LIB_NAME       := ds

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

AVLSRC         := $(SRC_DIR)/avl/avl.$(SRCEXT) $(SRC_DIR)/avl/balancer.$(SRCEXT) $(SRC_DIR)/avl/helperfn.$(SRCEXT)

## release build

OBJECTS        := $(patsubst %.$(SRCEXT), %-rel.$(OBJEXT), $(wildcard *.$(SRCEXT)))
AVLOBJ         := $(BUILD_DIR)/avl-rel.$(OBJEXT) $(BUILD_DIR)/balancer-rel.$(OBJEXT) $(BUILD_DIR)/helperfn-rel.$(OBJEXT)

rel: mkdirp $(AVLOBJ) $(OBJECTS) cpobj

$(AVLOBJ): $(AVLSRC)
	@cd avl/ && $(MAKE)

%-rel.$(OBJEXT): %.$(SRCEXT) $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

## build subdirs
# $(SUB_DIRS): FORCE \
	@$(MAKE) -C $@

## debug build

DBG_OBJECTS    := $(patsubst %.$(SRCEXT), %-dbg.$(OBJEXT), $(wildcard *.$(SRCEXT)))
DBG_AVLOBJ     := $(BUILD_DIR)/avl-dbg.$(OBJEXT) $(BUILD_DIR)/balancer-dbg.$(OBJEXT) $(BUILD_DIR)/helperfn-dbg.$(OBJEXT) 

dbg: mkdirp $(DBG_AVLOBJ) $(DBG_OBJECTS) cpobj

$(DBG_AVLOBJ): $(AVLSRC)
	@cd avl/ && $(MAKE) dbg

%-dbg.$(OBJEXT): %.$(SRCEXT) $(HEADERS)
	$(CC) $(CDBGFLAGS) $(INCLUDE) -c -o $@ $<

## build subdirs
# $(SUB_DIR_DBG): FORCE \
	@$(MAKE) -C $@ dbg

cpobj:
	@cp *.$(OBJEXT) $(BUILD_DIR)

mkdirp:
	@mkdir -p $(BUILD_DIR)

clean:
	@cd avl && $(MAKE) clean
	@rm -f *.$(OBJEXT)

cleaner: clean
	@cd avl && $(MAKE) cleaner
	@rm -f $(BUILD_DIR)/*.$(OBJEXT)

# FORCE:
