QT += widgets svgwidgets multimedia

CONFIG += c++23

SOURCES += \
    FileHandler.cpp \
    Game.cpp \
    GameController.cpp \
    LifesDisplay.cpp \
    MainWindow.cpp \
    Message.cpp \
    PathBuilder.cpp \
    ScoreDisplay.cpp \
    SoundEngine.cpp \
    StartupSequence.cpp \
    engine/AbstractChasingStrategy.cpp \
    engine/GameEvent.cpp \
    engine/GameTimer.cpp \
    engine/GameView.cpp \
    engine/Grid.cpp \
    engine/Poking.cpp \
    engine/Shadowing.cpp \
    engine/Shying.cpp \
    engine/Speeding.cpp \
    engine/behaviors/AbstractBehavior.cpp \
    engine/behaviors/AbstractSpatialBehavior.cpp \
    engine/behaviors/AbstractTimedBehavior.cpp \
    engine/behaviors/AiStateMachine.cpp \
    engine/behaviors/Animation.cpp \
    engine/behaviors/CameraFollow.cpp \
    engine/behaviors/CharacterMovement.cpp \
    engine/behaviors/DotsEating.cpp \
    engine/behaviors/EnemyController.cpp \
    engine/behaviors/KillPlayer.cpp \
    engine/behaviors/PlayerAnimation.cpp \
    engine/behaviors/PlayerController.cpp \
    engine/GameObject.cpp \
    engine/InputSystem.cpp \
    engine/Scene.cpp \
    engine/Tile.cpp \
    engine/Tilemap.cpp \
    engine/Vector2.cpp \
    engine/behaviors/PlayerOrientation.cpp \
    engine/behaviors/Teleporting.cpp \
    main.cpp

HEADERS += \
    FileHandler.h \
    Game.h \
    GameController.h \
    LifesDisplay.h \
    MainWindow.h \
    Message.h \
    PathBuilder.h \
    ScoreDisplay.h \
    SoundEngine.h \
    StartupSequence.h \
    engine/AbstractChasingStrategy.h \
    engine/GameEvent.h \
    engine/GameTimer.h \
    engine/GameView.h \
    engine/Grid.h \
    engine/Poking.h \
    engine/Shadowing.h \
    engine/Shying.h \
    engine/Speeding.h \
    engine/behaviors/AbstractBehavior.h \
    engine/behaviors/AbstractSpatialBehavior.h \
    engine/behaviors/AbstractTimedBehavior.h \
    engine/behaviors/AiStateMachine.h \
    engine/behaviors/Animation.h \
    engine/behaviors/CameraFollow.h \
    engine/behaviors/CharacterMovement.h \
    engine/behaviors/DotsEating.h \
    engine/behaviors/EnemyController.h \
    engine/behaviors/KillPlayer.h \
    engine/behaviors/PlayerAnimation.h \
    engine/behaviors/PlayerController.h \
    engine/GameObject.h \
    engine/InputSystem.h \
    engine/Scene.h \
    engine/Tile.h \
    engine/Tilemap.h \
    engine/Vector2.h \
    engine/behaviors/PlayerOrientation.h \
    engine/behaviors/Teleporting.h

RESOURCES += \
    resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
