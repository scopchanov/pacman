QT += widgets multimedia

CONFIG += c++20

SOURCES += \
    Message.cpp \
    engine/PathBuilder.cpp \
    engine/behaviors/AbstractBehavior.cpp \
    engine/behaviors/AbstractCharacterBehavior.cpp \
    engine/behaviors/CameraFollow.cpp \
    engine/behaviors/CharacterMovement.cpp \
    engine/behaviors/DotsEating.cpp \
    engine/behaviors/PlayerController.cpp \
    engine/GameController.cpp \
    engine/GameObject.cpp \
    engine/InputSystem.cpp \
    engine/Scene.cpp \
    engine/Tile.cpp \
    engine/Tilemap.cpp \
    engine/Vector2.cpp \
    FileHandler.cpp \
    Game.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    Message.h \
    engine/PathBuilder.h \
    engine/behaviors/AbstractBehavior.h \
    engine/behaviors/AbstractCharacterBehavior.h \
    engine/behaviors/CameraFollow.h \
    engine/behaviors/CharacterMovement.h \
    engine/behaviors/DotsEating.h \
    engine/behaviors/PlayerController.h \
    engine/GameController.h \
    engine/GameObject.h \
    engine/InputSystem.h \
    engine/Scene.h \
    engine/Tile.h \
    engine/Tilemap.h \
    engine/Vector2.h \
    FileHandler.h \
    Game.h \
    MainWindow.h

RESOURCES += \
    resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
