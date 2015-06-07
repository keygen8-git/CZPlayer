DEPENDPATH  += $$PWD
INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/GlobalHotkey.h \
    $$PWD/NoFocusDelegate.h \
    $$PWD/signal_slot.h \
    $$PWD/StatusDefine.h \
    $$PWD/TR.h \
    $$PWD/ChineseToLetter.h \
    $$PWD/AutoStart.h \
    $$PWD/FileRelation.h \
    $$PWD/AutoStartHandle.h \
    $$PWD/FileRelationHandle.h

SOURCES += \
    $$PWD/GlobalHotkey.cpp \
    $$PWD/NoFocusDelegate.cpp \
    $$PWD/AutoStart.cpp \
    $$PWD/FileRelation.cpp \
    $$PWD/AutoStartHandle.cpp \
    $$PWD/FileRelationHandle.cpp

#����ע������api������
LIBS += -lAdvapi32
#ˢ��ϵͳ���溯����SHChangeNotify��������
LIBS += -lshell32

