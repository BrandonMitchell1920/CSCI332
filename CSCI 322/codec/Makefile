#
# Makefile for Generating C++ executables
#
# CSCI 332 - Design and Analysis of Algorithms
# Phillip J. Curtiss, Associate Professor
# Computer Science Department, Montana Tech
#
# Huffman Image CODEC
#
# Project Files Specified Below
##
# Source files should be added to the SRCS variable
SRCS =	main.cpp utilities/Pairing.cpp utilities/GenHuffmanCode.cpp Encoder.cpp Decoder.cpp
# Object files will be inferred from soruce files; adjust as needed
OBJS =	$(SRCS:.cpp=.o)
# Dependency files will be inferred from source files; adjust as needed
DEPS =	$(SRCS:.cpp=.dep)
# List all targets this Makefile is to create from source files
TARGET = hcodec

###################################################
# Should Not need to modify lines of Makefile below
#
# g++ compiler flags; standard is C++14; level-3 optimization
CXXFLAGS = -std=gnu++17 -O3 -Wall -Werror -Wno-unused-function
# Additional Library Search Paths specified below
LDFLAGS = 
# Additional Libraries to link in with executable below
LDLIBS = 

#
# Provide Make with additionally known suffixes
.SUFFIXES:	.dia .dep .tex .md

# Default rule to make if no target specified
# (make dependencies first, then all targets)
default: $(DEPS) $(TARGET) 

# Rules to generate targets
# Note: If more than one target, might need multiple rules
#       of the form below
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

# Make dependency file for each source file
# include all dependency files so Make can 
# conditionally make required project file
%.dep: %.cpp
	$(CXX) -MM $< -o $@
-include $(DEPS)

#
# Clean up Intermediate files and targets
.PHONY: clean doxygen
clean: 
	-$(RM) $(DEPS) $(OBJS) $(TARGET)