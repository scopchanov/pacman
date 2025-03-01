QT += widgets multimedia

win32:RC_ICONS += pacman-logo.ico

CONFIG += c++23

#DEFINES += DEBUG

SOURCES += \
    ComponentBuilder.cpp \
    Configurator.cpp \
    DialogGame.cpp \
    DialogSettings.cpp \
    Factory.cpp \
    FileHandler.cpp \
    GameLevel.cpp \
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
    actions/AbstractOrientate.cpp \
    actions/AbstractTimedAction.cpp \
    actions/ActivateDeenergizer.cpp \
    actions/CalmDownEnemies.cpp \
    actions/DeactivateDeenergizer.cpp \
    actions/DeenergizePlayer.cpp \
    actions/DeleteGameObject.cpp \
    actions/EatDot.cpp \
    actions/EatEnemy.cpp \
    actions/EnergizePlayer.cpp \
    actions/EyeOrientate.cpp \
    actions/KillPlayer.cpp \
    actions/PlayerOrientate.cpp \
    actions/ScareEnemies.cpp \
    actions/Teleport.cpp \
    actions/animate/AbstractAnimate.cpp \
    actions/animate/AnimateEnemy.cpp \
    actions/animate/AnimateEnergizer.cpp \
    actions/animate/AnimatePlayer.cpp \
    actions/animate/AnimateTeleporter.cpp \
    behaviors/AbstractControllingBehavior.cpp \
    behaviors/AbstractSpatialBehavior.cpp \
    behaviors/Delaying.cpp \
    behaviors/EnemyControlling.cpp \
    behaviors/Moving.cpp \
    behaviors/PlayerControlling.cpp \
    behaviors/Spawning.cpp \
    objects/AbstractCharacter.cpp \
    objects/Deenergizer.cpp \
    objects/Enemy.cpp \
    objects/EnemyEye.cpp \
    objects/Energizer.cpp \
    objects/Player.cpp \
    objects/Teleporter.cpp \
    personalities/AbstractPersonality.cpp \
    personalities/Poking.cpp \
    personalities/Shadowing.cpp \
    personalities/Shying.cpp \
    personalities/Speeding.cpp \
    main.cpp

HEADERS += \
    ComponentBuilder.h \
    Configurator.h \
    DialogGame.h \
    DialogSettings.h \
    Factory.h \
    FileHandler.h \
    GameGlobals.h \
    GameLevel.h \
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
    actions/AbstractOrientate.h \
    actions/AbstractTimedAction.h \
    actions/ActivateDeenergizer.h \
    actions/CalmDownEnemies.h \
    actions/DeactivateDeenergizer.h \
    actions/DeenergizePlayer.h \
    actions/DeleteGameObject.h \
    actions/EatDot.h \
    actions/EatEnemy.h \
    actions/EnergizePlayer.h \
    actions/EyeOrientate.h \
    actions/KillPlayer.h \
    actions/PlayerOrientate.h \
    actions/ScareEnemies.h \
    actions/Teleport.h \
    actions/animate/AbstractAnimate.h \
    actions/animate/AnimateEnemy.h \
    actions/animate/AnimateEnergizer.h \
    actions/animate/AnimatePlayer.h \
    actions/animate/AnimateTeleporter.h \
    behaviors/AbstractControllingBehavior.h \
    behaviors/AbstractSpatialBehavior.h \
    behaviors/Delaying.h \
    behaviors/EnemyControlling.h \
    behaviors/Moving.h \
    behaviors/PlayerControlling.h \
    behaviors/Spawning.h \
    objects/AbstractCharacter.h \
    objects/Deenergizer.h \
    objects/Enemy.h \
    objects/EnemyEye.h \
    objects/Energizer.h \
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
