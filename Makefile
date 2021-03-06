#############################################################################
# Makefile for building: app-demo
# Generated by qmake (2.01a) (Qt 4.8.1) on: Wed Jul 15 18:28:17 2015
# Project:  app-demo.pro
# Template: app
# Command: /usr/bin/qmake -spec /usr/share/qt4/mkspecs/qws/linux-arm-g++ CONFIG+=debu -o Makefile app-demo.pro
#############################################################################

####### Compiler, tools and options

CC            = arm-linux-gcc
CXX           = arm-linux-g++
DEFINES       = -DQT_WEBKIT -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/qws/linux-arm-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtNetwork -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -I.
LINK          = arm-linux-g++
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib/x86_64-linux-gnu -lQtGui -lQtNetwork -lQtCore -lpthread 
AR            = arm-linux-ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = arm-linux-strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		mygui.cpp \
		imageframe.cpp moc_mygui.cpp \
		moc_imageframe.cpp \
		qrc_Images.cpp
OBJECTS       = main.o \
		mygui.o \
		imageframe.o \
		moc_mygui.o \
		moc_imageframe.o \
		qrc_Images.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/common/qws.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_phonon.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		app-demo.pro
QMAKE_TARGET  = app-demo
DESTDIR       = 
TARGET        = app-demo

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_mygui.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: app-demo.pro  /usr/share/qt4/mkspecs/qws/linux-arm-g++/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/common/qws.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_phonon.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/x86_64-linux-gnu/libQtGui.prl \
		/usr/lib/x86_64-linux-gnu/libQtNetwork.prl \
		/usr/lib/x86_64-linux-gnu/libQtCore.prl
	$(QMAKE) -spec /usr/share/qt4/mkspecs/qws/linux-arm-g++ CONFIG+=debu -o Makefile app-demo.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/common/qws.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_phonon.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/x86_64-linux-gnu/libQtGui.prl:
/usr/lib/x86_64-linux-gnu/libQtNetwork.prl:
/usr/lib/x86_64-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/share/qt4/mkspecs/qws/linux-arm-g++ CONFIG+=debu -o Makefile app-demo.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/app-demo1.0.0 || $(MKDIR) .tmp/app-demo1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/app-demo1.0.0/ && $(COPY_FILE) --parents mygui.h imageframe.h .tmp/app-demo1.0.0/ && $(COPY_FILE) --parents Images.qrc .tmp/app-demo1.0.0/ && $(COPY_FILE) --parents main.cpp mygui.cpp imageframe.cpp .tmp/app-demo1.0.0/ && $(COPY_FILE) --parents mygui.ui .tmp/app-demo1.0.0/ && (cd `dirname .tmp/app-demo1.0.0` && $(TAR) app-demo1.0.0.tar app-demo1.0.0 && $(COMPRESS) app-demo1.0.0.tar) && $(MOVE) `dirname .tmp/app-demo1.0.0`/app-demo1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/app-demo1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_mygui.cpp moc_imageframe.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mygui.cpp moc_imageframe.cpp
moc_mygui.cpp: mygui.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) mygui.h -o moc_mygui.cpp

moc_imageframe.cpp: imageframe.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) imageframe.h -o moc_imageframe.cpp

compiler_rcc_make_all: qrc_Images.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_Images.cpp
qrc_Images.cpp: Images.qrc \
		images/runner-05.png \
		images/runner-06.png \
		images/runner-07.png \
		images/runner-08.png \
		images/runner-01.png \
		images/runner-02.png \
		images/runner-03.png \
		images/runner-04.png
	/usr/bin/rcc -name Images Images.qrc -o qrc_Images.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_mygui.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mygui.h
ui_mygui.h: mygui.ui
	/usr/bin/uic-qt4 mygui.ui -o ui_mygui.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean compiler_uic_clean 

####### Compile

main.o: main.cpp mygui.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

mygui.o: mygui.cpp mygui.h \
		ui_mygui.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mygui.o mygui.cpp

imageframe.o: imageframe.cpp imageframe.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o imageframe.o imageframe.cpp

moc_mygui.o: moc_mygui.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mygui.o moc_mygui.cpp

moc_imageframe.o: moc_imageframe.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_imageframe.o moc_imageframe.cpp

qrc_Images.o: qrc_Images.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_Images.o qrc_Images.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

