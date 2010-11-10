#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


boolean GameGlobal::_isInit = false;
double GameGlobal::_rank = 0.0;
UINT32 GameGlobal::_score = 0;


void GameGlobal::init() {
    if (_isInit == false) {
        _rank = 0.0;
        _score = 0;
        _isInit = true;
    }
}
