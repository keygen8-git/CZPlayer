DEPENDPATH  += $$PWD
INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/AudioStream.h \
    $$PWD/BasicPlayer.h \
    $$PWD/CriticalSection.h \
    $$PWD/FastFourierTransform.h \
    $$PWD/IO.h \
    $$PWD/SoundControl.h \
    $$PWD/SpectroGraph.h \
    $$PWD/Stream.h \
    $$PWD/Thread.h \
    $$PWD/Utils.h

SOURCES += \
    $$PWD/AudioStream.cpp \
    $$PWD/BasicPlayer.cpp \
    $$PWD/FastFourierTransform.cpp \
    $$PWD/IO.cpp \
    $$PWD/SoundControl.cpp \
    $$PWD/SpectroGraph.cpp \
    $$PWD/Stream.cpp \
    $$PWD/Utils.cpp \
    $$PWD/WMWrapper.cpp

#ʹ��libmad��
INCLUDEPATH += $$PWD/../3rdParty/libmad/include
CONFIG(release, debug|release): LIBS += -L$$PWD/../3rdParty/libmad/lib/   -llibmad
CONFIG(debug, debug|release): LIBS += -L$$PWD/../3rdParty/libmad/lib/   -llibmadd

#ʹ��libogg��
INCLUDEPATH += $$PWD/../3rdParty/libogg/include
CONFIG(release, debug|release): LIBS += -L$$PWD/../3rdParty/libogg/lib/   -llibogg
CONFIG(debug, debug|release): LIBS += -L$$PWD/../3rdParty/libogg/lib/   -lliboggd

#ʹ��libvorbis��
INCLUDEPATH += $$PWD/../3rdParty/libvorbis/include
CONFIG(release, debug|release): LIBS += -L$$PWD/../3rdParty/libvorbis/lib/   -llibvorbis
CONFIG(debug, debug|release): LIBS += -L$$PWD/../3rdParty/libvorbis/lib/   -llibvorbisd

#ʹ��dx������ؿ�
LIBS += -ldsound
LIBS += -ldxguid
LIBS += -lstrsafe
LIBS += -lwmvcore
LIBS += -lmsimg32
LIBS += -lmsacm32
LIBS += -lWinmm
LIBS += -lole32
