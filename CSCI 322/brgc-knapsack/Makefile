#
# Makefile for Generating C++ executables
#
# CSCI 332 - Design and Analysis of Algorithms
# Phillip J. Curtiss, Associate Professor
# Department of Computer Science, Montana Tech
#
# Project Files Specified Below
##
# Source files should be added to the SRCS variable
SRCS =	main.cpp BRGC.cpp Knapsack.cpp
# Object files will be inferred from soruce files; adjust as needed
OBJS =	$(SRCS:.cpp=.o)
# Dependency files will be inferred from source files; adjust as needed
DEPS =	$(SRCS:.cpp=.dep)
# List all targets this Makefile is to create from source files
TARGET = driver

###################################################
# Should Not need to modify lines of Makefile below
#
# g++ compiler flags; standard is C++17; level-3 optimization
CXXFLAGS = -std=gnu++17 -O3 -Wall -Werror -I. -I./menu 
# Additional Library Search Paths specified below
LDFLAGS = -L./menu
# Additional Libraries to link in with executable below
LDLIBS = -ltui

#
# Provide Make with additionally known suffixes
.SUFFIXES:	.dia .dep

# Default rule to make if no target specified
# (make dependencies first, then all targets)
default: $(DEPS) $(TARGET) 

# Rules to generate targets
# Note: If more than one target, might need multiple rules
#       of the form below
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDLIBS)

# Make dependency file for each source file
# include all dependency files so Make can 
# conditionally make required project file
%.dep: %.cpp
	$(CXX) -MM -I. -I./menu $< -o $@
-include $(DEPS)

#
# Clean up Intermediate files and targets
.PHONY: clean doxygen
clean: 
	-$(RM) $(DEPS) $(OBJS) $(TARGET) 

