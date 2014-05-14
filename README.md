#AssassinWar

`This is a 2D-Game that based on QT 4.8.5`

`The Inspiration came form a RPG-map of Warcraft3 in China`
`Each players control one Assassin that looks like normal people`
`the whole game is about finding other Assassins and kill`

`Be sure that you only kill Assassin(other players)`
`becuase you will get Punishment if you kill the innocence NPCs`


## To open this project you need:
> * vs2010 sp1
> * QT4.8.5
> * GTest 1.7.0

**make sure your already set environment variable : $(GTest) for GTest 1.7.0**

**if you want to comment a lib, just write in** `commentlib.h` **in AW project flie such like:**

```
#ifdef _DEBUG
#pragma comment(lib,"QtUiToolsd.lib")
#pragma comment(lib,"MapLoaderd.lib")
#pragma comment(lib,"GameModuleSetd.lib")
#else
#pragma comment(lib,"QtUiTools.lib")
#pragma comment(lib,"MapLoader.lib")
#pragma comment(lib,"GameModuleSet.lib")
#endif // _DEBUG
```

**Every project path setting should begin with** `$(ProjectDir)`**,do not use** `$(SolutionDir)`**!!!**

`other project link`
[GTest 1.7.0][1]
[QT 4.8.5 GUI][2]

[1]: https://code.google.com/p/googletest/downloads/detail?name=gtest-1.7.0.zip
[2]: http://download.qt-project.org/official_releases/qt/4.8/4.8.5/