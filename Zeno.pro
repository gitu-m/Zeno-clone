######################################################################
# Automatically generated by qmake (3.0) Tue Feb 27 02:24:35 2018
######################################################################

TEMPLATE = app
TARGET = Zeno
INCLUDEPATH += ./include

# Input
HEADERS +=	include/Board.h \
			include/Button.h \
		 	include/Game.h \
		 	include/Player.h \
		 	include/Event.h \
		 	include/Tesseract.h \
		 	include/Tile.h \
                        include/Clone.h \
                        include/Levels.h \
                        include/GenLeveLs.h

SOURCES += 	main.cpp \
			src/Board.cpp \
			src/Button.cpp \
			src/Game.cpp \
			src/Player.cpp \
			src/Tesseract.cpp \
			src/Tile.cpp \
			src/Clone.cpp                    

CONFIG += c++11

QT += core gui widgets concurrent\
	multimedia

RESOURCES += \
    res.qrc
