

CXX_DIALECT = c++17
C_DIALECT = c11

INCLUDES = -I./include

LIBRARIES = -lcurl -lssl -ldl -ltorrent

CXX_FLAGS += -std=$(CXX_DIALECT) $(INCLUDES) -pthread -Werror=all -pedantic-errors -fPIC -flto

C_FLAGS += -std=$(C_DIALECT) $(INCLUDES) -pthread -Werror=all -fPIC

LINKER_FLAGS += $(LIBRARIES) -shared -pthread -fPIC

OUTPUT := liblcupm.so

ARCHIVE_OUTPUT := liblcupm.a

OBJECTS := out/PlatformInfo.o out/Provider.o

all: dynamic

out/%.o: src/%.cpp
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
	