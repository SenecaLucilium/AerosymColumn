QT       += core printsupport xml gui

greaterThan(QT_MAJOR_VERSION, 4): QT += svg widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += svgwidgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    # GraphViewModule/graphviewmodule.cpp \
    # ResultsViewModule/resultsviewmodule.cpp \
    SectionDataModule/InitData/GeometryData/WeirTypes/sievegeometry.cpp \
    SectionDataModule/InitData/GeometryData/geometrydatatab.cpp \
    SectionDataModule/InitData/ParamsData/paramsdatatab.cpp \
    SectionDataModule/InitData/SummaryData/summarydatatab.cpp \
    SectionDataModule/InitData/initialdatatab.cpp \
    main.cpp \
    columnmodule.cpp

HEADERS += \
    CalculationModule/WeirTypes/calculationbase.h \
    CalculationModule/WeirTypes/sievecalculation.h \
    CalculationModule/calculationmodule.h \
    # GraphViewModule/graphsectiondiagram.h \
    # GraphViewModule/graphviewmodule.h \
    # ResultsViewModule/resultsviewmodule.h \
    SectionDataModule/InitData/GeometryData/WeirTypes/sievegeometry.h \
    SectionDataModule/InitData/GeometryData/geometrydatatab.h \
    SectionDataModule/InitData/ParamsData/paramsdatatab.h \
    SectionDataModule/InitData/SummaryData/WeirTypes/sievesummary.h \
    SectionDataModule/InitData/SummaryData/summarydatatab.h \
    SectionDataModule/InitData/initialdatatab.h \
    SectionDataModule/Messages/messagestab.h \
    SectionDataModule/Results/WeirTypes/sieveresults.h \
    SectionDataModule/Results/resultstab.h \
    SectionDataModule/sectiondatamodule.h \
    columnmodule.h \
    datatypes.h \
    sectionscheme.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += C:/Libs/JKQtPlotter-master/lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD -ljkqtplotterlib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD -llibjkqtplotterlib_debug

RESOURCES += \
    resources.qrc
