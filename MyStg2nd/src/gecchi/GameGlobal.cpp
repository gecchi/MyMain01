#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


boolean GameGlobal::_isInit = false;
MyShip* GameGlobal::_pMyShip = NULL;
CommonScene* GameGlobal::_pSceneCommon = NULL;
GameScene*   GameGlobal::_pSceneGame = NULL;
double GameGlobal::_rank = 1.0;
DWORD GameGlobal::_dwScore = 0;





void GameGlobal::init() {
    if (_isInit == false) {
        _rank = 1;
        _dwScore = 0;


        _isInit = true;
    }
}
