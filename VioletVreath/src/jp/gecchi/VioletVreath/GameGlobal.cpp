#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


bool GameGlobal::_isInit = false;
double GameGlobal::_rank = 0.0;
int GameGlobal::_rank_up_level = 0;
UINT32 GameGlobal::_score = 0;


void GameGlobal::init() {
    GameGlobal::_rank = 0.0;
    GameGlobal::_rank_up_level = 0;
    GameGlobal::_score = 0;
    GameGlobal::_isInit = true;
}
