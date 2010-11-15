#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9AlphaCurtain::GgafDx9AlphaCurtain(GgafDx9Scene* prm_pDxScene) : GgafCurtain(prm_pDxScene) {
    _pDxScene = prm_pDxScene;
    _alpha = 1.0;
}

GgafDx9AlphaCurtain::~GgafDx9AlphaCurtain() {
}
