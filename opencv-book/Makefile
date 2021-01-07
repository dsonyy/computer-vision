# Not-so-beautiful makefile which works only with Windows Powershell :(
#
# Usage:
#	make F=filename.cpp  
#	make F=filename.cpp DEBUG=1
#

# Compiler flags
CXX = cl

# Project files
SRC = test.cpp
OBJ = $(SRC:.cpp=.obj)
EXE = $(SRC:.cpp=.exe)

# Debug settings
ifeq ($(DEBUG), 1)
	DIR = debug
	EXE = $(addprefix $(DIR)/, $(EXE))
	OBJ = $(addprefix $(DIR)/, $(OBJ))
	CXXFLAGS = \
		-Zi \
		-MDd \
		-EHsc \
		-DEBUG \
		-std:c++17 \
		-Fd./$(DIR)/vc.pdb \
		-Fe./$(DIR)/ \
		-Fo./$(DIR)/
	IFLAGS = -I $(OPENCV_INCLUDE)
	LFLAGS = -link -LIBPATH:$(OPENCV_VC_LIB_DEBUG)
	LIBS = \
		opencv_calib3d451d.lib \
		opencv_core451d.lib \
		opencv_dnn451d.lib \
		opencv_features2d451d.lib \
		opencv_flann451d.lib \
		opencv_gapi451d.lib \
		opencv_highgui451d.lib \
		opencv_imgcodecs451d.lib \
		opencv_imgproc451d.lib \
		opencv_ml451d.lib \
		opencv_objdetect451d.lib \
		opencv_photo451d.lib \
		opencv_stitching451d.lib \
		opencv_ts451d.lib \
		opencv_video451d.lib \
		opencv_videoio451d.lib
# Release settings
else 
	DIR = release
	EXE = $(addprefix $(DIR)/, $(EXE))
	OBJ = $(addprefix $(DIR)/, $(OBJ))
	CXXFLAGS = \
		-O2 \
		-Fe./$(DIR)/ \
		-Fo./$(DIR)/ \
		-EHsc
	IFLAGS = -I $(OPENCV_INCLUDE)
	LFLAGS = -link -LIBPATH:$(OPENCV_VC_LIB)
	LIBS = \
		opencv_calib3d451.lib \
		opencv_core451.lib \
		opencv_dnn451.lib \
		opencv_features2d451.lib \
		opencv_flann451.lib \
		opencv_gapi451.lib \
		opencv_highgui451.lib \
		opencv_imgcodecs451.lib \
		opencv_imgproc451.lib \
		opencv_ml451.lib \
		opencv_objdetect451.lib \
		opencv_photo451.lib \
		opencv_stitching451.lib \
		opencv_ts451.lib \
		opencv_video451.lib \
		opencv_videoio451.lib
endif

# -----------------------------------------------------------------------------

.PHONY: all debug release

all: $(F)

$(F): prep
	$(CXX) $(F) $(CXXFLAGS) $(IFLAGS) $(LFLAGS) $(LIBS)

prep:
	@powershell -noprofile New-Item $(DIR) -ItemType Directory -Force

clean:
	@powershell -noprofile Remove-Item $(DIR) -Recurse -ErrorAction Ignore