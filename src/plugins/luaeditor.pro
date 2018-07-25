DEFINES += LUAEDITOR_LIBRARY

CONFIG += c++11

# DEFINES += ALLOW_LOGGING

INCLUDEPATH += "/z/dev/lua-5.2.3/src"

LIBS += -L/z/dev/lua-5.2.3/src -llua -L/mingw64/bin

SOURCES += luaeditorplugin.cpp \
    luahoverhandler.cpp \
    luaeditorwidget.cpp \
    luaeditorfactory.cpp \
    luahighlighter.cpp \
    scanner/luascanner.cpp \
    luaeditor_global.cpp \
    luaindenter.cpp \
    luaautocompleter.cpp \
    luacompletionassistprovider.cpp \
    luacompletionassistprocessor.cpp \
    luafunctionhintproposalmodel.cpp \
    scanner/recursiveclassmembers.cpp \
    luaengine/luaEngine.cpp \
    luafunctionfilter.cpp \
    luafunctionparser.cpp \
    predefineddocumentationparser.cpp


HEADERS += luaeditorplugin.h \
    luaeditor_global.h \
    luaeditorconstants.h \
    luahoverhandler.h \
    luaeditorwidget.h \
    luaeditorfactory.h \
    luahighlighter.h \
    scanner/luascanner.h \
    scanner/luaformattoken.h \
    scanner/sourcecodestream.h \
    luaindenter.h \
    luaautocompleter.h \
    luacompletionassistprovider.h \
    luacompletionassistprocessor.h \
    luafunctionhintproposalmodel.h \
    scanner/recursiveclassmembers.h \
    luaengine/luaengine.h \
    luafunctionfilter.h \
    luafunctionparser.h \
    predefineddocumentationparser.h \
    luaengine/lua.hpp

# Qt Creator linking

## set the QTC_SOURCE environment variable to override the setting here
QTCREATOR_SOURCES = $$(QTC_SOURCE)
isEmpty(QTCREATOR_SOURCES):QTCREATOR_SOURCES="/tools/git-sdk-64/usr/src/MINGW-packages/mingw-w64-qt-creator/src/qt-creator-opensource-src-4.7.0"

## set the QTC_BUILD environment variable to override the setting here
IDE_BUILD_TREE = $$(QTC_BUILD)
isEmpty(IDE_BUILD_TREE):IDE_BUILD_TREE="/mingw64/"

## uncomment to build plugin into user config directory
## <localappdata>/plugins/<ideversion>
##    where <localappdata> is e.g.
##    "%LOCALAPPDATA%\QtProject\qtcreator" on Windows Vista and later
##    "$XDG_DATA_HOME/data/QtProject/qtcreator" or "~/.local/share/data/QtProject/qtcreator" on Linux
##    "~/Library/Application Support/QtProject/Qt Creator" on Mac
# USE_USER_DESTDIR = yes

###### If the plugin can be depended upon by other plugins, this code needs to be outsourced to
###### <dirname>_dependencies.pri, where <dirname> is the name of the directory containing the
###### plugin's sources.

QTC_PLUGIN_NAME = LuaEditor
QTC_LIB_DEPENDS += \
    utils

QTC_PLUGIN_DEPENDS += \
    coreplugin \
    texteditor

QTC_PLUGIN_RECOMMENDS +=

###### End _dependencies.pri contents ######

include($$QTCREATOR_SOURCES/src/qtcreatorplugin.pri)

OTHER_FILES += \
    luaeditor.mimetypes.xml \
    LuaEditor.json.in

RESOURCES += \
    luaeditor.qrc

DISTFILES += \
    sandbox.lua

