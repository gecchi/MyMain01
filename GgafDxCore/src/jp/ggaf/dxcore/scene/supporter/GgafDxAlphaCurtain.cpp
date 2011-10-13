#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxAlphaCurtain::GgafDxAlphaCurtain(GgafDxScene* prm_pDxScene,
                                       float prm_min_alpha,
                                       float prm_max_alpha) : GgafCurtain(prm_pDxScene, _max_alpha-_min_alpha) {
    _pDxScene = prm_pDxScene;
    _min_alpha = prm_min_alpha;
    _max_alpha = prm_max_alpha;
    _range_alpha = _max_alpha - _min_alpha;
    _alpha = 1.0;


}

GgafDxAlphaCurtain::~GgafDxAlphaCurtain() {
}
