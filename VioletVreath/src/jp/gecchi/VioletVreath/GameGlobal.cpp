#include "stdafx.h"
#include "GameGlobal.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

bool GameGlobal::is_init_ = false;
double GameGlobal::rank_ = 0.0;
int GameGlobal::rank_up_level_ = 0;
int GameGlobal::score_ = 0;
QueryRanking GameGlobal::qryRanking_;

