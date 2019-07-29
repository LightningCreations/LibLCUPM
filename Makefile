CXX = g++-8
CC = gcc-8

CXX_DIALECT = c++17
C_DIALECT = c11

INCLUDE_DIRS := ./include

INCLUDES = $(foreach inc,$(INCLUDE_DIRS),-I$(inc))

BUILD_STATIC := yes
BUILD_DYNAMIC := yes

TARGETS =

ifeq ($(BUILD_STATIC),yes)
TARGETS += static
endif

ifeq ($(BUILD_DYNAMIC),yes)
TARGETS += dynamic
endif

ifeq ($(TARGETS),)
$(error "No Target for LCUPM, were both BUILD_STATIC and BUILD_DYNAMIC disabled)
endif

INSTALL_PREFIX := /usr

INSTALL_TARGETS = $(foreach target,$(TARGETS),install-$(target))

LIBRARIES = curl ssl dl torrent

DEFINES := LCUPM_BUILD

DEF_FLAGS = $(foreach def,$(DEFINES),-D$(def))

CXX_FLAGS += -std=$(CXX_DIALECT) $(INCLUDES) $(DEF_FLAGS) -fvisibility=hidden -fvisibility-inlines-hidden -pthread -pedantic-errors -fPIC -flto

C_FLAGS += -std=$(C_DIALECT) $(INCLUDES) $(DEF_FLAGS) -fvisibility=hidden -fvisibility-inlines-hidden -pthread -fPIC -flto

LINKER_FLAGS += $(foreach library,$(LIBRARIES),-l$(library)) -fvisibility=hidden -fvisibility-inlines-hidden -shared -pthread -fPIC

OUTPUT := liblcupm.so

ARCHIVE_OUTPUT := liblcupm.a

OBJECTS := out/PlatformInfo.o out/Provider.o out/Downloader.o out/Utilities.o
OBJECTS += out/Version.o out/Exception.o

all: $(TARGETS)

.PHONY: all dynamic static rebuild version

out:
	mkdir out

test:
	mkdir test

out/%.o: src/%.cpp | out
	$(CXX) $(CXX_FLAGS) -c $^ -o $@

out/%.o: src/%.c | out
	$(CC) $(C_FLAGS) -c $^ -o $@

$(OUTPUT): $(OBJECTS)
	$(CXX) $(LINKER_FLAGS) $^ -o $@
	
$(ARCHIVE_OUTPUT): $(OBJECTS)
	$(AR) rcs $(ARCHIVE_OUTPUT) $(OBJECTS)
	
clean:
	rm -rf out/
	rm -f $(OUTPUT)
	rm -f $(ARCHIVE_OUTPUT)
	mkdir out/
	
dynamic: $(OUTPUT)

static: $(ARCHIVE_OUTPUT)

rebuild: clean all

install-headers: 
	install -m 755 ./include/lcupm $(INSTALL_PREFIX)/include

install-dynamic: $(OUTPUT) install-headers
	install $(OUTPUT) $(INSTALL_PREFIX)/lib
	
install-static: $(ARCHIVE_OUTPUT) install-headers
	install $(ARCHIVE_OUTPUT) $(INSTALL_PREFIX)/lib

install: $(INSTALL_TARGETS)

version:
	$(CXX) --version
	$(CC) --version