## compilation options
USE_GCC = 1
PRODUCE_REPORTS = 0
DEBUG_MODE = 0
USE_PRINTING = 0

## MATLAB options
USE_MATLAB = 0

## sampler options
USE_SFMT = 1

## OpenEXR options
USE_OPENEXR = 0

## optimization options
USE_THREADED = 1
USE_DOUBLE_PRECISION = 1
USE_PIXEL_SHARING = 1
USE_NO_FRESNEL = 0
USE_FILE = 0
USE_WEIGHT_NORMALIZATION = 0

# initialize variables
LIBS =
INCLUDES =
CFLAGS =
LDFLAGS =

## specify compiler, adds to CFLAGS
ifeq ($(USE_GCC), 1)
	include mkfiles/gcc.mk
	CFLAGS += -DUSE_GCC
else
	include mkfiles/icc.mk
endif

## specify boost version to use
include mkfiles/boost.mk

## specify MATLAB flags, adds to INCLUDES and CFLAGS
ifeq ($(USE_MATLAB), 1)
	include mkfiles/matlab.mk
endif

## specify sampler-related options
# specify RNG to use 
ifeq ($(USE_RNG), BOOST)
	CFLAGS += -DUSE_BOOST
endif

# specify algorithm to use
ifeq ($(USE_SFMT), 1)
	CFLAGS += -DUSE_SFMT
endif

## specify OPENEXR flags, adds to LIBS and INCLUDES, available only with GCC
ifeq ($(USE_OPENEXR), 1)
ifeq ($(USE_GCC), 1)
	include mkfiles/openexr.mk
	CFLAGS += -DUSE_OPENEXR
endif
endif

ifeq ($(USE_THREADED), 1)
	CFLAGS += -DUSE_THREADED
endif

ifeq ($(USE_DOUBLE_PRECISION), 1)
	CFLAGS += -DUSE_DOUBLE_PRECISION
endif

ifeq ($(USE_DIRECT), 1)
	CFLAGS += -DUSE_DIRECT
endif

ifeq ($(USE_PIXEL_SHARING), 1)
	CFLAGS += -DUSE_PIXEL_SHARING
endif

ifeq ($(USE_NO_FRESNEL), 1)
	CFLAGS += -DUSE_NO_FRESNEL
endif

ifeq ($(USE_FILE), 1)
	CFLAGS += -DUSE_FILE
endif

ifeq ($(USE_WEIGHT_NORMALIZATION), 1)
	CFLAGS += -DUSE_WEIGHT_NORMALIZATION
endif

ifeq ($(USE_PRINTING), 1)
	CFLAGS += -DUSE_PRINTING
endif

ifeq ($(USE_MATLAB), 1)
	MATLIBS += $(LIBS)
endif

# ROOTDIR = $(shell pwd)
ROOTDIR = .
INCLUDEDIR = $(ROOTDIR)/include
SRCDIR = $(ROOTDIR)/src
MEXDIR = $(ROOTDIR)/mexfiles

INCLUDES += -I$(INCLUDEDIR)

HEADERS = \
	$(INCLUDEDIR)/constants.h \
	$(INCLUDEDIR)/debug_util.h \
	$(INCLUDEDIR)/image.h \
	$(INCLUDEDIR)/medium.h \
	$(INCLUDEDIR)/phase.h \
	$(INCLUDEDIR)/renderer.h \
	$(INCLUDEDIR)/sampler.h \
	$(INCLUDEDIR)/tvector.h \
	$(INCLUDEDIR)/util.h \
	$(INCLUDEDIR)/photon.h \
	$(INCLUDEDIR)/scene.h \
	$(INCLUDEDIR)/bsdf.h
	
OBJ = \
	$(SRCDIR)/image.o \
	$(SRCDIR)/phase.o \
	$(SRCDIR)/sampler.o \
	$(SRCDIR)/photon.o \
	$(SRCDIR)/scene.o \
	$(SRCDIR)/bsdf.o

## specify sampler-related options
# specify RNG to use 
ifeq ($(USE_SFMT), 1)
	HEADERS += $(INCLUDEDIR)/rng_sse.h $(INCLUDEDIR)/sse.h
	OBJ += $(SRCDIR)/rng_sse.o
else
	HEADERS += $(INCLUDEDIR)/rng_boost.h
endif

ifeq ($(USE_MATLAB), 1)
all: mexfiles main
else
all: main
endif

main: \
	$(SRCDIR)/main

mexfiles: \
	$(MEXDIR)/renderImage_mex.$(MEXEXT) \
	$(MEXDIR)/renderDerivImage_mex.$(MEXEXT) \
	$(MEXDIR)/renderDerivImageWeight_mex.$(MEXEXT) \
	$(MEXDIR)/test_fp_mex.$(MEXEXT) \
	$(MEXDIR)/test_source_mex.$(MEXEXT)

$(SRCDIR)/%: \
	$(SRCDIR)/%.o \
	$(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(MEXDIR)/%.$(MEXEXT): \
	$(MEXDIR)/%.o \
	$(OBJ)
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $^ $(MATLIBS)

# sample object files
$(SRCDIR)/%.o: $(SRCDIR)/%.cpp $(INCLUDEDIR)/renderer.h
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $(SRCDIR)/$*.cpp

# mex object files
$(MEXDIR)/%.o: $(MEXDIR)/%.cpp \
	$(INCLUDEDIR)/mex_wrapper.h \
	$(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

# src object files
$(SRCDIR)/rng_sse.o: \
	$(SRCDIR)/rng_sse.cpp \
	$(INCLUDEDIR)/rng_sse.h \
	$(INCLUDEDIR)/sse.h
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<
	
$(SRCDIR)/rng_%.o: \
	$(SRCDIR)/rng_%.cpp \
	$(INCLUDEDIR)/rng_%.h
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<


$(SRCDIR)/%.o: \
	$(SRCDIR)/%.cpp \
	$(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

clean:	
	rm -rf *.o *~
	rm -rf $(MEXDIR)/*.o $(MEXDIR)/*~
	rm -rf $(SRCDIR)/*.o $(SRCDIR)/*~
	rm -rf $(SRCDIR)/*.o $(SRCDIR)/*~

distclean:	
	rm -rf *.o *~
	rm -rf $(MEXDIR)/*.o $(MEXDIR)/*~ $(MEXDIR)/*.$(MEXEXT) 
	rm -rf $(SRCDIR)/*.o $(SRCDIR)/*~ $(SRCDIR)/*_bin
	rm -rf $(SRCDIR)/*.o $(SRCDIR)/*~
