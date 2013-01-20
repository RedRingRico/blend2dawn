###############################################################################
#                                    blend2dawn Makefile [Linux x86] Ver. 1.0 #
###############################################################################

ifndef TOPDIR
export TOPDIR		:= $(shell cd ../../ && pwd)
export TOPSRC		= $(TOPDIR)/Source
export TARGETDIR	= $(TOPDIR)/Bin/Linux/$(ARCH)_$(BITSIZE)
export OBJSDIR		= $(TOPDIR)/Obj/Linux/$(ARCH)_$(BITSIZE)/GCC/$(GCCVER)/$(BUILD)
endif

SOURCEDIR	= Source ../Common/Source
TARGET := blend2dawn
OUTFILE	= $(TARGETDIR)/$(TARGET)

PLATFORM		:= Linux
BUILD_PLATFORM	:= LINUX
ARCH			:= X86
BITSIZE			:= 32
GCCVER			= $(shell $(CPP) -dumpversion)
BUILD_TYPE		:= debug

32BIT	?= False
64BIT	?= False

# Get the machine type to determine which set of libraries to use
UNAME			= $(shell uname)
UNAME_MACHINE	= $(shell uname -m)

ifeq ($(UNAME), Linux)
	CPPFLAGS_EXT	= -ffriend-injection -std=gnu++0x
	SYSIPATH		= 
	SYSLIBS			= -lncurses -lrt
	LINKFLAGS		=
##### Check for forced 32-bit or 64-bit builds ################################
ifneq ($(64BIT), False)
	TOOL_PREFIX		= x86_64-pc-linux-gnu
	CPPFLAGS_EXT	+= -m64
	ARCH			= X86
	BITSIZE			= 64
else
ifneq ($(32BIT), False)
	TOOL_PREFIX		= i686-pc-linux-gnu
	CPPFLAGS_EXT	+= -m32
	ARCH			= X86
	BITSIZE			= 32
else
##### Use what the machine reports ############################################
ifeq ($(UNAME_MACHINE), x86_64)
	TOOL_PREFIX		= x86_64-pc-linux-gnu
	CPPFLAGS_EXT	+= -m64
	ARCH			= X86
	BITSIZE			= 64
endif
ifeq ($(UNAME_MACHINE), i686)
	TOOL_PREFIX		= i686-pc-linux-gnu
	CPPFLAGS_EXT	+= -m32
	ARCH			= X86
	BITSIZE			= 32
endif
endif
endif
endif

##### Tools ###################################################################
CPP = $(TOOL_PREFIX)-g++

##### Common compiler flags ###################################################
CPPFLAGS =	-c -DBUILD_$(BUILD_DEF) -DPLATFORM_$(BUILD_PLATFORM) \
			-DPLATFORM_$(BUILD_PLATFORM)_$(ARCH) \
			-DPLATFORM_$(BUILD_PLATFORM)_$(ARCH)_$(BITSIZE) \
			-DBITSIZE_$(BITSIZE) -DARCH_$(ARCH) \
			-I$(TOPSRC)/Linux/Headers -I$(TOPSRC)/Common/Headers 

##### Debug #######
debug:		BUILD = Debug
debug:		BUILD_TYPE = debug
debug:		BUILD_DEF = DEBUG
debug:		TARGET := $(TARGET)D
debug:		CPPFLAGS += -g -ggdb -Wall -D_DEBUG $(CPPFLAGS_EXT)
debug:		$(TARGET)

##### Release #####
release:	BUILD = Release
release:	BUILD_TYPE = release
release:	BUILD_DEF = RELEASE
release:	TARGET := $(TARGET)
release:	CPPFLAGS += -O3 $(CPPFLAGS_EXT)
release:	LINKFLAGS += -Wl,-S
release:	$(TARGET)

##### Profile #####
profile:	BUILD = Profile
profile:	BUILD_TYPE = profile
profile:	BUILD_DEF = PROFILE
profile:	TARGET := $(TARGET)P
profile:	CPPFLAGS += -O3 -g -ggdb -Wall -D_DEBUG $(CPPFLAGS_EXT)
profile:	$(TARGET)

##### Build the object files while not in the Obj directory ###################
ifneq ($(OBJSDIR), $(CURDIR))

VERSIONINFO:
	@echo "---------------------- Generating Version Information -------------------------"
	@./GitVersion.sh ./Headers/GitVersion.hpp
	@echo "-------------------------------------------------------------------------------"

TARGETDIR:
	@mkdir -p $(TARGETDIR)

OBJSDIR:
	@mkdir -p $(OBJSDIR)

CPPFILES	:= $(foreach dir,$(SOURCEDIR),$(notdir $(wildcard $(dir)/*.cpp)))
export VPATH	= $(foreach dir,$(SOURCEDIR),$(CURDIR)/$(dir))
export OBJS		= $(CPPFILES:.cpp=.o)

$(TARGET): OBJSDIR TARGETDIR VERSIONINFO
	@/usr/bin/time -f "%E" -o $(OBJSDIR)/compiletime $(MAKE) \
	--no-print-directory -C $(OBJSDIR) -f $(TOPSRC)/Linux/Makefile \
	$(BUILD_TYPE)
	@printf "\n%s" "----------------------------------------------------------"
	@printf "%s\n" "---------------------"
	@cat $(OBJSDIR)/compiletime
	@printf "%s" "------------------------------------------------------------"
	@printf "%s\n" "-------------------"
else

$(TARGET): $(OBJS)
	@printf "\n\n%s" "------------------------ MESSAGES FROM THE COMPILER ----"
	@printf "%s\n" "-----------------------"
	@cat *.cmsgs
	@printf "%s" "------------------------------------------------------------"
	@printf "%s\n\n" "-------------------"
	@printf "Creating: $(OUTFILE)... "
	@$(CPP) -o $(OUTFILE) $(OBJS) $(SYSLIBS)
	@printf "[OK]\n"

%.o: %.cpp
	@printf "Compiling: $<... "
	@$(CPP) -MMD -MP -MF $(OBJSDIR)/$*.d $(CPPFLAGS) $(SYSIPATH) $< -o $@ \
	2> $*.cmsgs;\
	RETVAL=$$?;\
	if [[ $$RETVAL == 0 ]]; then\
		printf "[OK]\n";\
	else\
		printf "\n\n%s" "------------------------------------ ERROR --------";\
		printf "%s\n" "----------------------------";\
		cat $*.cmsgs;\
		printf "%s" "-------------------------------------------------------";\
		printf "%s\n" "------------------------";\
		exit 1;\
	fi

endif

.PHONY: clean
clean:
	@printf "Removing files from $(TARGETDIR)... "
	@cd $(TARGETDIR) && rm -f ./*
	@printf "[OK]\n"
	@printf "Removing files from $(OBJSDIR)... "
	@cd $(OBJSDIR) && rm -rf ./*
	@printf "[OK]\n"

