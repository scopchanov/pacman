QT += widgets multimedia

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
    engine/AiStateMachine.cpp \
    engine/Character.cpp \
    engine/Enemy.cpp \
    engine/GameEvent.cpp \
    engine/GameTimer.cpp \
    engine/GameView.cpp \
    engine/Grid.cpp \
    engine/Pacman.cpp \
    engine/Player.cpp \
    engine/behaviors/AbstractBehavior.cpp \
    engine/behaviors/AbstractSpatialBehavior.cpp \
    engine/behaviors/AbstractTimedBehavior.cpp \
    engine/behaviors/CameraFollow.cpp \
    engine/behaviors/CharacterMovement.cpp \
    engine/behaviors/DotsEating.cpp \
    engine/behaviors/EnemyAnimation.cpp \
    engine/behaviors/EnemyController.cpp \
    engine/behaviors/KillPlayer.cpp \
    engine/behaviors/PlayerAnimation.cpp \
    engine/behaviors/PlayerController.cpp \
    engine/personalities/AbstractPersonality.cpp \
    engine/personalities/Poking.cpp \
    engine/personalities/Shadowing.cpp \
    engine/personalities/Shying.cpp \
    engine/personalities/Speeding.cpp \
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
    engine/AiStateMachine.h \
    engine/Character.h \
    engine/Enemy.h \
    engine/GameEvent.h \
    engine/GameTimer.h \
    engine/GameView.h \
    engine/Grid.h \
    engine/Pacman.h \
    engine/Player.h \
    engine/behaviors/AbstractBehavior.h \
    engine/behaviors/AbstractSpatialBehavior.h \
    engine/behaviors/AbstractTimedBehavior.h \
    engine/behaviors/CameraFollow.h \
    engine/behaviors/CharacterMovement.h \
    engine/behaviors/DotsEating.h \
    engine/behaviors/EnemyAnimation.h \
    engine/behaviors/EnemyController.h \
    engine/behaviors/KillPlayer.h \
    engine/behaviors/PlayerAnimation.h \
    engine/behaviors/PlayerController.h \
    engine/personalities/AbstractPersonality.h \
    engine/personalities/Poking.h \
    engine/personalities/Shadowing.h \
    engine/personalities/Shying.h \
    engine/personalities/Speeding.h \
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
