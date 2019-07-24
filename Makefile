CXX = g++-8
CC = gcc-8

CXX_DIALECT = c++17
C_DIALECT = c11

INCLUDES = -I./include

LIBRARIES = -lcurl -lssl -ldl -ltorrent

DEFINES := -DLCUPM_BUILD

CXX_FLAGS += -std=$(CXX_DIALECT) $(INCLUDES) $(DEFINES) -fvisibility=hidden -fvisibility-inlines-hidden -pthread -pedantic-errors -fPIC -flto

C_FLAGS += -std=$(C_DIALECT) $(INCLUDES) $(DEFINES) -fvisibility=hidden -fvisibility-inlines-hidden -pthread -fPIC

LINKER_FLAGS += $(LIBRARIES) -fvisibility=hidden -fvisibility-inlines-hidden -shared -pthread -fPIC

OUTPUT := liblcupm.so

ARCHIVE_OUTPUT := liblcupm.a

OBJECTS := out/PlatformInfo.o out/Provider.o out/Downloader.o out/Utilities.o

all: dynamic static

out:
	mkdir out

test:
	mkdir test

out/%.o: src/%.cpp | out
	$(CXX) $(CXX_FLAGS) -c $^ -o $@

$(OUTPUT): $(OBJECTS)
	$(CXX) $(LINKER_FLAGS) $^ -o $@
	
$(ARCHIVE_OUTPUT): $(OBJECTS)
	ar rcs $(ARCHIVE_OUTPUT) $(OBJECTS)
	
clean:
	rm -rf out/
	rm -f $(OUTPUT)
	rm -f $(ARCHIVE_OUTPUT)
	mkdir out/
	
dynamic: $(OUTPUT)

static: $(ARCHIVE_OUTPUT)

rebuild: clean all
	

version:
	$(CXX) --version
	$(CC) --version