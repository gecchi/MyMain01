#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxAlphaCurtain::GgafDxAlphaCurtain(GgafDxScene* prm_pDxScene) : GgafCurtain(prm_pDxScene) {
    _pDxScene = prm_pDxScene;
    _alpha = 1.0;
}

GgafDxAlphaCurtain::~GgafDxAlphaCurtain() {
}
