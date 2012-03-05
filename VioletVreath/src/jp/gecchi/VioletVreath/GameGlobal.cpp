#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


bool GameGlobal::is_init_ = false;
double GameGlobal::rank_ = 0.0;
int GameGlobal::rank_up_level_ = 0;
UINT32 GameGlobal::score_ = 0;


void GameGlobal::init() {
    GameGlobal::rank_ = 0.0;
    GameGlobal::rank_up_level_ = 0;
    GameGlobal::score_ = 0;
    GameGlobal::is_init_ = true;
}
