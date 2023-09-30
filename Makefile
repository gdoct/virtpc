CXX       := g++
CXXFLAGS  := -Wall -std=c++20 -Wextra -Werror -pthread -O2
LD        := g++

MODULES   := test microcode util core main
SRC_DIR   := $(addprefix src/,$(MODULES))
BUILD_DIR := $(addprefix obj/,$(MODULES))

SRC       := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.cpp))
OBJ       := $(patsubst src/%.cpp,obj/%.o,$(SRC))
INCLUDES  := $(addprefix -I,$(SRC_DIR))

vpath %.cpp $(SRC_DIR)

define make-goal
$1/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $$< -o $$@
endef

.PHONY: all checkdirs clean

all: checkdirs virtpc

virtpc: $(OBJ)
	$(LD) $(CXXFLAGS) $^ -o $@

checkdirs: $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(BUILD_DIR)

$(foreach bdir,$(BUILD_DIR),$(eval $(call make-goal,$(bdir))))