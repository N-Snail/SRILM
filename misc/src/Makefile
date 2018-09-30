#
#    File:   Makefile.example
#    Author: The SRI DECIPHER (TM) System
#    Date:   Thu Sep  9 12:04:47 1993
#
#    Description:
#	This is the example makefile to start from when adding new
#       modules to the DECIPHER System.  To use this makefile, first
#       copy it to your directory as the file "Makefile".  Second,
#       replace the word "Example" in the text below with the real name
#	of your library.  Next replace the the example filenames with
#	the names of your actual declarations and source files in the
#	appropriate variable definitions.  Finally clean up by deleting
#	any lines not relevant to your module and updating this header
#       to describe your new module.  Do not forget to use the proper
#       RCS keywords!
#
#    Copyright (c) 1993, SRI International.  All Rights Reserved.
#
#    $Header: /home/srilm/devel/misc/src/RCS/Makefile,v 1.13 1999/02/20 07:26:42 stolcke Exp $
#

DECIPHER = $(SRILM)
#MACHINE_TYPE := $(shell $(DECIPHER)/bin/machine-type)

# Include common DECIPHER (TM) variable definitions.
include $(DECIPHER)/common/Makefile.common.variables

ifneq ($(CC), $(subst gcc,,$(CC)))
CC += -Wreturn-type 
endif

ifneq ($(CXX), $(subst g++,,$(CXX)))
CXX += -Wreturn-type 
endif

# Define variables.

# Example Library declarations files.

EXTERNAL_LIB_HEADERS = \
	$(SRCDIR)/cfuncproto.h          \
	$(SRCDIR)/option.h		\
	$(SRCDIR)/zio.h			\
	$(SRCDIR)/Boolean.h		\
	$(SRCDIR)/Debug.h		\
	$(SRCDIR)/File.h

INTERNAL_LIB_HEADERS = 

# Example Library source files.
LIB_SOURCES = 				\
	$(SRCDIR)/tclmain.cc		\
	$(SRCDIR)/option.c		\
	$(SRCDIR)/zio.c			\
	$(SRCDIR)/fcheck.c		\
	$(SRCDIR)/Debug.cc		\
	$(SRCDIR)/File.cc

# Example Library object files.
LIB_OBJECTS = $(patsubst $(SRCDIR)/%.cc,$(OBJDIR)/%.o,\
		$(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(LIB_SOURCES)))


# Example Library.
LIBRARY = $(OBJDIR)/libmisc.a

ADDITIONAL_INCLUDES += -I/usr/local/include
ADDITIONAL_LIBRARIES += -L/usr/local/lib -ltcl -lm

# Example programs.
PROGRAM_NAMES = \
	ztest \
	testFile

PROGRAMS = $(PROGRAM_NAMES:%=$(BINDIR)/%)

PROGRAM_SOURCES = $(foreach prog,$(PROGRAM_NAMES),\
			$(wildcard $(SRCDIR)/$(prog).c) \
			$(wildcard $(SRCDIR)/$(prog).cc))
PROGRAM_OBJECTS = $(PROGRAM_NAMES:%=$(OBJDIR)/%.o)


# Libraries to be linked with the Example programs.
LIBRARIES = $(LIBRARY) \
	    $(ADDITIONAL_LIBRARIES)

# All of the types of files.

ALL_HEADERS = $(EXTERNAL_LIB_HEADERS) \
	      $(INTERNAL_LIB_HEADERS)

ALL_SOURCES = $(LIB_SOURCES) \
	      $(PROGRAM_SOURCES)

ALL_OBJECTS = $(LIB_OBJECTS) \
	      $(PROGRAM_OBJECTS)

ALL_LIBRARIES = $(LIBRARY)

ALL_PROGRAMS = $(PROGRAMS)

ALL_PROGRAM_NAMES = $(PROGRAM_NAMES)


# Define pseudo-targets.


# Make sure the library does not get deleted if the make is interrupted.
.PRECIOUS:	$(LIBRARY)


# Define targets.


all:	libraries

$(LIBRARY):	$(LIB_OBJECTS)
	$(ARCHIVE) $@ $^
	$(RANLIB) $@ $(DEMANGLE_FILTER)

# Variables and Targets for released system

EXPORTED_HEADERS   = $(EXTERNAL_LIB_HEADERS)
EXPORTED_LIBRARIES = $(LIBRARY)
EXPORTED_PROGRAMS  = 

release:	release-headers release-libraries release-programs

# Include common DECIPHER (TM) target definitions.
include $(DECIPHER)/common/Makefile.common.targets