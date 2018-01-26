EXE = mp6
TEST = test

OBJS_DIR = .objs
OBJS_DIR_STUDENT = $(OBJS_DIR)/student
OBJS_DIR_PROVIDED = $(OBJS_DIR)/provided

OBJS_STUDENT = maptiles.o
OBJS_PROVIDED = main.o util/util.o mosaiccanvas.o sourceimage.o util/coloredout.o tileimage.o
OBJS_PROVIDED += cs225/HSLAPixel.o cs225/PNG.o cs225/lodepng/lodepng.o

OBJS_MAIN = $(OBJS_PROVIDED)

CXX = clang++
LD = clang++
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable
CXXFLAGS = -std=c++1y -stdlib=libc++ -g -O0 $(WARNINGS) -MMD -MP -msse2 -c
CXXFLAGS_PROVIDED = -O0
CXXFLAGS_STUDENT = -O0
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpthread
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer


all: mp6

# Pattern rules for object files
$(OBJS_DIR_STUDENT)/%-asan.o: %.cpp | $(OBJS_DIR_STUDENT)
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_STUDENT) $(ASANFLAGS) $< -o $@
$(OBJS_DIR_PROVIDED)/%-asan.o: %.cpp | $(OBJS_DIR_PROVIDED)
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_PROVIDED) $(ASANFLAGS) $< -o $@
$(OBJS_DIR_STUDENT)/%.o: %.cpp | $(OBJS_DIR_STUDENT)
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_STUDENT) $< -o $@
$(OBJS_DIR_PROVIDED)/%.o: %.cpp | $(OBJS_DIR_PROVIDED)
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_PROVIDED) $< -o $@

# Create directories
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
$(OBJS_DIR_STUDENT):
	@mkdir -p $(OBJS_DIR_STUDENT)
$(OBJS_DIR_PROVIDED):
	@mkdir -p $(OBJS_DIR_PROVIDED)
	@mkdir -p $(OBJS_DIR_PROVIDED)/util
	@mkdir -p $(OBJS_DIR_PROVIDED)/cs225
	@mkdir -p $(OBJS_DIR_PROVIDED)/cs225/lodepng

# Rules for executables... we can use a pattern for the -asan versions, but, unfortunately, we can't use a pattern for the normal executables
$(EXE):
	$(LD) $^ $(LDFLAGS) -o $@
%-asan:
	$(LD) $^ $(LDFLAGS) $(ASANFLAGS) -o $@


# Executable dependencies
$(EXE):         $(patsubst %.o, $(OBJS_DIR_STUDENT)/%.o,      $(OBJS_STUDENT))   $(patsubst %.o, $(OBJS_DIR_PROVIDED)/%.o, $(OBJS_MAIN))
$(EXE)-asan:    $(patsubst %.o, $(OBJS_DIR_STUDENT)/%-asan.o, $(OBJS_STUDENT))   $(patsubst %.o, $(OBJS_DIR_PROVIDED)/%.o, $(OBJS_MAIN))


# Include automatically generated dependencies
-include $(OBJS_DIR_STUDENT)/*.d
-include $(OBJS_DIR_PROVIDED)/*.d

clean:
	rm -rf $(EXE) $(EXE)-asan $(OBJS_DIR)

tidy: clean
	rm -rf doc

.PHONY: all mp6 tidy clean check
