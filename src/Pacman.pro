QT += widgets multimedia

win32:RC_ICONS += pacman-logo.ico

CONFIG += c++23

#DEFINES += DEBUG

SOURCES += \
    Configurator.cpp \
    DialogGame.cpp \
    DialogSettings.cpp \
    FileHandler.cpp \
    GameMenu.cpp \
    GameWidget.cpp \
    LifesDisplay.cpp \
    MainWindow.cpp \
    Message.cpp \
    PathBuilder.cpp \
    ScoreDisplay.cpp \
    StartupSequence.cpp \
    AiStateMachine.cpp \
    AudioEngine.cpp \
    BonusText.cpp \
    Game.cpp \
    GameStatus.cpp \
    actions/CalmDownEnemies.cpp \
    actions/DeenergizePlayer.cpp \
    actions/DeleteGameObject.cpp \
    actions/EnergizePlayer.cpp \
    actions/ScareEnemies.cpp \
    behaviors/AbstractAnimationBehavior.cpp \
    behaviors/AbstractOrientationBehavior.cpp \
    behaviors/AbstractSpatialBehavior.cpp \
    behaviors/AbstractTimedBehavior.cpp \
    behaviors/CameraFollow.cpp \
    behaviors/CharacterMovement.cpp \
    behaviors/CollisionChecking.cpp \
    behaviors/Coloring.cpp \
    behaviors/Delaying.cpp \
    behaviors/DotsEating.cpp \
    behaviors/EnemyAnimation.cpp \
    behaviors/EnemyController.cpp \
    behaviors/EnemyEating.cpp \
    behaviors/EnemyOrientation.cpp \
    behaviors/EnergizerAnimation.cpp \
    behaviors/Energizing.cpp \
    behaviors/KillPlayer.cpp \
    behaviors/PlayerAnimation.cpp \
    behaviors/PlayerController.cpp \
    behaviors/PlayerOrientation.cpp \
    behaviors/Spawning.cpp \
    behaviors/Teleporting.cpp \
    objects/Character.cpp \
    objects/Deenergizer.cpp \
    objects/Enemy.cpp \
    objects/Energizer.cpp \
    objects/GhostEye.cpp \
    objects/Player.cpp \
    objects/Teleporter.cpp \
    personalities/AbstractPersonality.cpp \
    personalities/Poking.cpp \
    personalities/Shadowing.cpp \
    personalities/Shying.cpp \
    personalities/Speeding.cpp \
    main.cpp

HEADERS += \
    Configurator.h \
    DialogGame.h \
    DialogSettings.h \
    FileHandler.h \
    GameGlobals.h \
    GameMenu.h \
    GameWidget.h \
    LifesDisplay.h \
    MainWindow.h \
    Message.h \
    PathBuilder.h \
    ScoreDisplay.h \
    StartupSequence.h \
    AiStateMachine.h \
    AudioEngine.h \
    BonusText.h \
    Game.h \
    GameStatus.h \
    actions/CalmDownEnemies.h \
    actions/DeenergizePlayer.h \
    actions/DeleteGameObject.h \
    actions/EnergizePlayer.h \
    actions/ScareEnemies.h \
    behaviors/AbstractAnimationBehavior.h \
    behaviors/AbstractOrientationBehavior.h \
    behaviors/AbstractSpatialBehavior.h \
    behaviors/AbstractTimedBehavior.h \
    behaviors/CameraFollow.h \
    behaviors/CharacterMovement.h \
    behaviors/CollisionChecking.h \
    behaviors/Coloring.h \
    behaviors/Delaying.h \
    behaviors/DotsEating.h \
    behaviors/EnemyAnimation.h \
    behaviors/EnemyController.h \
    behaviors/EnemyEating.h \
    behaviors/EnemyOrientation.h \
    behaviors/EnergizerAnimation.h \
    behaviors/Energizing.h \
    behaviors/KillPlayer.h \
    behaviors/PlayerAnimation.h \
    behaviors/PlayerController.h \
    behaviors/PlayerOrientation.h \
    behaviors/Spawning.h \
    behaviors/Teleporting.h \
    objects/Character.h \
    objects/Deenergizer.h \
    objects/Enemy.h \
    objects/Energizer.h \
    objects/GhostEye.h \
    objects/Player.h \
    objects/Teleporter.h \
    personalities/AbstractPersonality.h \
    personalities/Poking.h \
    personalities/Shadowing.h \
    personalities/Shying.h \
    personalities/Speeding.h

RESOURCES += \
    resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../Libraries/ArcadeGameEngine/build/release/ -lArcadeGameEngine
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../Libraries/ArcadeGameEngine/build/debug/ -lArcadeGameEngine
else:unix: LIBS += -L$$PWD/../../../Libraries/ArcadeGameEngine/build/ -lArcadeGameEngine

INCLUDEPATH += $$PWD/../../../Libraries/ArcadeGameEngine/src
DEPENDPATH += $$PWD/../../../Libraries/ArcadeGameEngine/src
