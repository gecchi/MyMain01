#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


boolean GameGlobal::_isInit = false;
MyShip* GameGlobal::_pMyShip = NULL;
CommonScene* GameGlobal::_pSceneCommon = NULL;
int GameGlobal::_iRank = 1;
DWORD GameGlobal::_dwScore = 0;

int GameGlobal::_lim_MyShip_top     =  0;
int GameGlobal::_lim_MyShip_bottom  =  0;
int GameGlobal::_lim_MyShip_front   =  0;
int GameGlobal::_lim_MyShip_behaind =  0;
int GameGlobal::_lim_MyShip_zleft   =  0;
int GameGlobal::_lim_MyShip_zright  =  0;



void GameGlobal::init() {
    if (_isInit == false) {
        _iRank = 1;
        _dwScore = 0;


        _lim_MyShip_top     = GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*3*LEN_UNIT / 2;
        _lim_MyShip_bottom  = -(GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*3*LEN_UNIT / 2);
        _lim_MyShip_front   = GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT / 2;
        _lim_MyShip_behaind = -(GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT / 2);
        _lim_MyShip_zleft   = GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*3*LEN_UNIT / 2;
        _lim_MyShip_zright  = -(GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*3*LEN_UNIT / 2);

        _isInit = true;
    }
}
