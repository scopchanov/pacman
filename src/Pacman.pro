QT += widgets multimedia

win32:RC_ICONS += pacman-logo.ico

CONFIG += c++23

#DEFINES += DEBUG

SOURCES += \
    BehaviorBuilder.cpp \
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
    actions/CalmDownEnemies.cpp \
    actions/DeenergizePlayer.cpp \
    actions/DeleteGameObject.cpp \
    actions/EnergizePlayer.cpp \
    actions/ScareEnemies.cpp \
    behaviors/AbstractAnimatingBehavior.cpp \
    behaviors/AbstractControllingBehavior.cpp \
    behaviors/AbstractOrientatingBehavior.cpp \
    behaviors/AbstractSpatialBehavior.cpp \
    behaviors/AbstractTimedBehavior.cpp \
    behaviors/Coloring.cpp \
    behaviors/Delaying.cpp \
    behaviors/DotsEating.cpp \
    behaviors/EnemyAnimating.cpp \
    behaviors/EnemyControlling.cpp \
    behaviors/EnemyEating.cpp \
    behaviors/EnemyOrientating.cpp \
    behaviors/EnergizerAnimating.cpp \
    behaviors/Energizing.cpp \
    behaviors/Killing.cpp \
    behaviors/Moving.cpp \
    behaviors/PlayerAnimating.cpp \
    behaviors/PlayerControlling.cpp \
    behaviors/PlayerOrientating.cpp \
    behaviors/Spawning.cpp \
    behaviors/TeleporterAnimating.cpp \
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
    BehaviorBuilder.h \
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
    actions/CalmDownEnemies.h \
    actions/DeenergizePlayer.h \
    actions/DeleteGameObject.h \
    actions/EnergizePlayer.h \
    actions/ScareEnemies.h \
    behaviors/AbstractAnimatingBehavior.h \
    behaviors/AbstractControllingBehavior.h \
    behaviors/AbstractOrientatingBehavior.h \
    behaviors/AbstractSpatialBehavior.h \
    behaviors/AbstractTimedBehavior.h \
    behaviors/Coloring.h \
    behaviors/Delaying.h \
    behaviors/DotsEating.h \
    behaviors/EnemyAnimating.h \
    behaviors/EnemyControlling.h \
    behaviors/EnemyEating.h \
    behaviors/EnemyOrientating.h \
    behaviors/EnergizerAnimating.h \
    behaviors/Energizing.h \
    behaviors/Killing.h \
    behaviors/Moving.h \
    behaviors/PlayerAnimating.h \
    behaviors/PlayerControlling.h \
    behaviors/PlayerOrientating.h \
    behaviors/Spawning.h \
    behaviors/TeleporterAnimating.h \
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
