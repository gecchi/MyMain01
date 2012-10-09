#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

bool GameGlobal::is_init_ = false;
double GameGlobal::rank_ = 0.0;
int GameGlobal::rank_up_level_ = 0;
int GameGlobal::score_ = 111111110;
GgafQuery GameGlobal::qryScoreRanking_;

void GameGlobal::init() {
    //GameScene::onReset() ‚©‚çŒÄ‚Î‚ê‚Ü‚·
    GameGlobal::rank_ = 0.0;
    GameGlobal::rank_up_level_ = 0;
    GameGlobal::score_ = 111111110;
    GameGlobal::is_init_ = true;
}
