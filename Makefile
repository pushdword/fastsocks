# Makefile for the ENCTCP project
#
#---------------------------------------------------------
.SILENT:

ARCH          = linux

CXX           = 
ObjSuf        = o
SrcSuf        = cpp
ExeSuf        =
DllSuf        = so
OutPutOpt     = -o 

ifeq ($(ARCH),hpux)
# HP-UX with CC
CXX           = CC
CXXFLAGS      = -O +Z
LD            = CC
LDFLAGS       = -O +a1 -z
SOFLAGS       = -b
DllSuf        = sl
endif

ifeq ($(ARCH),solaris)
# Solaris with CC
CXX           = CC
CXXFLAGS      = -O +Z
LD            = CC
LDFLAGS       = -O -z
SOFLAGS       = -b
DllSuf        = sl
endif

ifeq ($(ARCH),linux)
# Linux with gcc 2.7.2.x
CXX           = g++
CXXFLAGS      = -O -Wall -fPIC
LD            = g++
LDFLAGS       = -O
SOFLAGS       = -shared
endif

ifeq ($(ARCH),mingw)
# MinGW g++ 3.0.6
CXX           = g++
CXXFLAGS      = -Wall
LD            = g++
LDFLAGS       =
SOFLAGS       = -shared
endif

ifeq ($(ARCH),freebsd)
# FreeBSD with libc5
CXX           = g++
CXXFLAGS      = -O -pipe -W -Wall -fPIC
LD            = g++
LDFLAGS       = -O
SOFLAGS       = -shared -Wl,-x
endif

ifeq ($(CXX),)
$(error $(ARCH) invalid architecture)
endif

CXXFLAGS     += $(DEBUG_OPTIONS)

#------------------------------------------------------------------------------


OBJFILES      = main.$(ObjSuf)


#------------------------------------------------------------------------------

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf)

all:	ENCTCP

ENCTCP:   $(OBJFILES)
	@echo "Linking..."
	$(LD) $(LDFLAGS) $(OBJFILES) $(LIBS) \
	    -o ENCTCP
	@echo "Done"

clean:
	@echo "Cleaning project area"
	@rm -f $(OBJFILES) core

.SUFFIXES: .$(SrcSuf)

#------------------------------------------------------------------------------

.$(SrcSuf).$(ObjSuf):
	@echo "Compiling $<"
	$(CXX) $(CXXFLAGS) -c $<

