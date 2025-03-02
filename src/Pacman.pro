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
    AudioEngine.cpp \
    Game.cpp \
    GameStatus.cpp \
    components/actions/AbstractTimedAction.cpp \
    components/actions/ActivateDeenergizer.cpp \
    components/actions/CalmDownEnemies.cpp \
    components/actions/DeactivateDeenergizer.cpp \
    components/actions/DeenergizePlayer.cpp \
    components/actions/DeleteGameObject.cpp \
    components/actions/EatEnemy.cpp \
    components/actions/EnergizePlayer.cpp \
    components/actions/KillPlayer.cpp \
    components/actions/ManageLevelMode.cpp \
    components/actions/Spawn.cpp \
    components/actions/Teleport.cpp \
    components/actions/UpdateDeenergizer.cpp \
    components/actions/animate/AbstractAnimate.cpp \
    components/actions/animate/AnimateEnemy.cpp \
    components/actions/animate/AnimateEnergizer.cpp \
    components/actions/animate/AnimatePlayer.cpp \
    components/actions/animate/AnimateTeleporter.cpp \
    components/actions/control/AbstractControl.cpp \
    components/actions/control/ControlEnemy.cpp \
    components/actions/control/ControlPlayer.cpp \
    components/actions/orientate/AbstractOrientate.cpp \
    components/actions/orientate/OrientateEye.cpp \
    components/actions/orientate/OrientatePlayer.cpp \
    components/actions/tilemap/AbstractTilemapAction.cpp \
    components/actions/tilemap/EatDot.cpp \
    components/actions/tilemap/Move.cpp \
    components/behaviors/Delaying.cpp \
    objects/AbstractCharacter.cpp \
    objects/BonusText.cpp \
    objects/Deenergizer.cpp \
    objects/Enemy.cpp \
    objects/EnemyEye.cpp \
    objects/Energizer.cpp \
    objects/LevelMode.cpp \
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
    AudioEngine.h \
    Game.h \
    GameStatus.h \
    components/actions/AbstractTimedAction.h \
    components/actions/ActivateDeenergizer.h \
    components/actions/CalmDownEnemies.h \
    components/actions/DeactivateDeenergizer.h \
    components/actions/DeenergizePlayer.h \
    components/actions/DeleteGameObject.h \
    components/actions/EatEnemy.h \
    components/actions/EnergizePlayer.h \
    components/actions/KillPlayer.h \
    components/actions/ManageLevelMode.h \
    components/actions/Spawn.h \
    components/actions/Teleport.h \
    components/actions/UpdateDeenergizer.h \
    components/actions/animate/AbstractAnimate.h \
    components/actions/animate/AnimateEnemy.h \
    components/actions/animate/AnimateEnergizer.h \
    components/actions/animate/AnimatePlayer.h \
    components/actions/animate/AnimateTeleporter.h \
    components/actions/control/AbstractControl.h \
    components/actions/control/ControlEnemy.h \
    components/actions/control/ControlPlayer.h \
    components/actions/orientate/AbstractOrientate.h \
    components/actions/orientate/OrientateEye.h \
    components/actions/orientate/OrientatePlayer.h \
    components/actions/tilemap/AbstractTilemapAction.h \
    components/actions/tilemap/EatDot.h \
    components/actions/tilemap/Move.h \
    components/behaviors/Delaying.h \
    objects/AbstractCharacter.h \
    objects/BonusText.h \
    objects/Deenergizer.h \
    objects/Enemy.h \
    objects/EnemyEye.h \
    objects/Energizer.h \
    objects/LevelMode.h \
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
