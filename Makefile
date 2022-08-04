OMNETPP_ROOT = /opt/omnetpp-6.0
OMNET_INCLUDES = -I$(OMNETPP_ROOT)/include
OMNET_LIBFLAGS = -L$(OMNETPP_ROOT)/lib
BINDINGS_TARGET = omnetgym$(shell python3-config --extension-suffix)
PYBIND11_INCLUDES = `python3 -m pybind11 --includes`
CXXFLAGS_DEBUG = -O0 -Wall -std=c++20 -fPIC -g
CXXFLAGS_RELEASE = -O3 -Wall -std=c++20 -fPIC
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
TEST_OBJS = $(TEST_SOURCES:$(TEST_DIR)/%.cc=$(TEST_DIR)/%.o)

cleantest:
	@rm $(TEST_DIR)/*.o
	
runtest: $(TEST_DIR)/test
	./$(TEST_DIR)/test

test: $(TEST_OBJS)
	@echo Building tests
	@g++ $(CXXFLAGS) -L/home/alessioc/pynetpp/build $(TEST_OBJS) -o $(TEST_DIR)/test -lomnetgym

$(TEST_DIR)/%.o: $(TEST_DIR)/%.cc
	@echo Compiling $@
	@g++ $(CXXFLAGS) -Iinclude -c $< -o $@

all: mainlib bindings

bindings: $(DIST) $(BINDINGS_OBJS) $(MODEL_OBJS)
	@echo Building python bindings with DEBUG=$(DEBUG)
	@g++ $(CXXFLAGS) -shared $(OMNET_LIBFLAGS) $(PYBIND11_INCLUDES) -L/home/alessioc/pynetpp/build $(MODEL_OBJS) $(BINDINGS_OBJS) -o $(DIST)/$(BINDINGS_TARGET) -l$(OMNET_LIBRARY_NAME) -lomnetgym

$(DIST)/%.o: $(BINDINGS_DIR)/%.cc
	@echo Compiling $@
	@g++ $(CXXFLAGS) $(OMNET_INCLUDES) $(PYBIND11_INCLUDES) -Iinclude -c $< -o $@
	
# makexec: $(DIST) $(MODEL_OBJS)
# 	@echo Building executable with DEBUG=$(DEBUG)
# 	@g++ $(CXXFLAGS) $(OMNET_LIBFLAGS) -L/home/alessioc/pynetpp/build $(MODEL_OBJS) -o $(DIST)/main -l$(OMNET_LIBRARY_NAME) -lomnetgym

$(DIST):
	@mkdir -p $(DIST)

$(DIST)/%.o: $(MODEL_SOURCE_DIR)/%.cc
	@echo Compiling $@
	@g++ $(CXXFLAGS) $(OMNET_INCLUDES) -Iinclude -c $< -o $@
	
mainlib: $(O) $(OBJS)
	@echo Building $@ with DEBUG=$(DEBUG)
	@g++ $(CXXFLAGS) -shared $(OMNET_LIBFLAGS) $(OBJS) -o $(O)/$(TARGET) -l$(OMNET_LIBRARY_NAME)
	@mv $(O)/$(TARGET) $(O)/lib$(TARGET).so
$(O):
	@mkdir -p $(O)

$(O)/%.o: $(SOURCE_DIR)/%.cc
	@echo Compiling $@
	@g++ $(CXXFLAGS) $(OMNET_INCLUDES) -Iinclude -c $< -o $@

clean:
	@rm -rf $(O)
	@rm -rf $(DIST)
