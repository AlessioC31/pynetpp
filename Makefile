OMNETPP_ROOT = /opt/omnetpp-6.0
INCLUDES = -I$(OMNETPP_ROOT)/include
LIBFLAGS = -L$(OMNETPP_ROOT)/lib
CXXFLAGS_DEBUG = -O0 -Wall -std=c++14 -fPIC -g
CXXFLAGS_RELEASE = -O3 -Wall -std=c++14 -fPIC
LIBRARY_NAME_DEBUG = oppsim_dbg
LIBRARY_NAME_RELEASE = oppsim

DEBUG ?= 1
ifeq ($(DEBUG), 1)
	CXXFLAGS = $(CXXFLAGS_DEBUG)
	LIBRARY_NAME = $(LIBRARY_NAME_DEBUG)
else
	CXXFLAGS = $(CXXFLAGS_RELEASE)
	LIBRARY_NAME = $(LIBRARY_NAME_RELEASE)
endif

SOURCE_DIR = ./src
SOURCES = $(wildcard $(SOURCE_DIR)/*.cc)

MODEL_SOURCE_DIR = ./model
MODEL_SOURCES = $(wildcard $(MODEL_SOURCE_DIR)/*.cc)

TARGET = omnetgym

O = ./build
DIST = ./dist

OBJS = $(SOURCES:$(SOURCE_DIR)/%.cc=$(O)/%.o)
MODEL_OBJS = $(MODEL_SOURCES:$(MODEL_SOURCE_DIR)/%.cc=$(DIST)/%.o)

exec: $(DIST) $(MODEL_OBJS)
	@echo Building executable with DEBUG=$(DEBUG)
	@g++ $(CXXFLAGS) $(LIBFLAGS) -L/home/alessioc/pynetpp/build $(MODEL_OBJS) -o $(DIST)/main -l$(LIBRARY_NAME) -lomnetgym

$(DIST):
	@mkdir -p $(DIST)

$(DIST)/%.o: $(MODEL_SOURCE_DIR)/%.cc
	@echo Compiling $@
	@g++ $(CXXFLAGS) $(INCLUDES) -Iinclude -c $< -o $@
	
mainlib: $(O) $(OBJS)
	@echo Building $@ with DEBUG=$(DEBUG)
	@g++ $(CXXFLAGS) -shared $(LIBFLAGS) $(OBJS) -o $(O)/$(TARGET) -l$(LIBRARY_NAME)
	@mv $(O)/$(TARGET) $(O)/lib$(TARGET).so
$(O):
	@mkdir -p $(O)

$(O)/%.o: $(SOURCE_DIR)/%.cc
	@echo Compiling $@
	@g++ $(CXXFLAGS) $(INCLUDES) -Iinclude -c $< -o $@

clean:
	@rm -rf $(O)
	@rm -rf $(DIST)
