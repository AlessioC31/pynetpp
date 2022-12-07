CC = clang++
OMNETPP_ROOT = /opt/omnetpp-6.0
OMNET_INCLUDES = -I$(OMNETPP_ROOT)/include
OMNET_LIBFLAGS = -L$(OMNETPP_ROOT)/lib
BINDINGS_TARGET = libpynetpp.so
PYBIND11_INCLUDES = `python3 -m pybind11 --includes`
CXXFLAGS_DEBUG = -O0 -Wall -std=c++17 -fPIC -g
CXXFLAGS_RELEASE = -O3 -Wall -std=c++17 -fPIC
OMNET_LIBRARY_NAME_DEBUG = oppsim_dbg
OMNET_LIBRARY_NAME_RELEASE = oppsim

DEBUG ?= 1
ifeq ($(DEBUG), 1)
	CXXFLAGS = $(CXXFLAGS_DEBUG)
	OMNET_LIBRARY_NAME = $(OMNET_LIBRARY_NAME_DEBUG)
else
	CXXFLAGS = $(CXXFLAGS_RELEASE)
	OMNET_LIBRARY_NAME = $(OMNET_LIBRARY_NAME_RELEASE)
endif

SOURCE_DIR = ./src
SOURCES = $(wildcard $(SOURCE_DIR)/*.cc)

MODEL_SOURCE_DIR = ./model
MODEL_SOURCES = $(wildcard $(MODEL_SOURCE_DIR)/*.cc)

BINDINGS_DIR = ./extras/bindings
BINDINGS_SOURCES = $(wildcard $(BINDINGS_DIR)/*.cc)

TEST_DIR= ./test
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.cc)

TARGET = omnetgym

O = ./build
DIST = ./dist

OBJS = $(SOURCES:$(SOURCE_DIR)/%.cc=$(O)/%.o)
MODEL_OBJS = $(MODEL_SOURCES:$(MODEL_SOURCE_DIR)/%.cc=$(DIST)/%.o)
BINDINGS_OBJS = $(BINDINGS_SOURCES:$(BINDINGS_DIR)/%.cc=$(DIST)/%.o)

bindings: $(DIST) $(BINDINGS_OBJS)
	@echo Building python bindings with DEBUG=$(DEBUG)
	@$(CC) $(CXXFLAGS) -shared -undefined dynamic_lookup $(OMNET_LIBFLAGS) $(PYBIND11_INCLUDES) $(BINDINGS_OBJS) -o $(DIST)/$(BINDINGS_TARGET) -l$(OMNET_LIBRARY_NAME)

$(DIST)/%.o: $(BINDINGS_DIR)/%.cc
	@echo Compiling $@
	@$(CC) $(CXXFLAGS) $(OMNET_INCLUDES) $(PYBIND11_INCLUDES) -Iinclude -c $< -o $@
	
$(DIST):
	@mkdir -p $(DIST)

$(DIST)/%.o: $(MODEL_SOURCE_DIR)/%.cc
	@echo Compiling $@
	@$(CC) $(CXXFLAGS) $(OMNET_INCLUDES) -Iinclude -c $< -o $@

clean:
	@rm -rf $(DIST)
