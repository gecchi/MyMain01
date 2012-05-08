#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxAlphaCurtain::GgafDxAlphaCurtain(GgafDxScene* prm_pDxScene,
                                       float prm_min_alpha,
                                       float prm_max_alpha) : GgafCurtain(prm_max_alpha-prm_min_alpha) {
    _pDxScene = prm_pDxScene;
    _min_alpha = prm_min_alpha;
    _max_alpha = prm_max_alpha;
    _range_alpha = _max_alpha - _min_alpha;
    _alpha = 1.0;
}

void GgafDxAlphaCurtain::processOpenBegin() {
}

void GgafDxAlphaCurtain::processOpening() {
    _alpha = _max_alpha - _now_curtain_length;
}

void GgafDxAlphaCurtain::processOpenDone() {
    _alpha = _max_alpha;
}

void GgafDxAlphaCurtain::processCloseBegin() {
}

void GgafDxAlphaCurtain::processClosing() {
    _alpha = _max_alpha - _now_curtain_length;
}

void GgafDxAlphaCurtain::processCloseDone() {
    _alpha = _min_alpha;
}

void GgafDxAlphaCurtain::behave() {
    GgafCurtain::behave();
    _pDxScene->_master_alpha = _alpha;
}

GgafDxAlphaCurtain::~GgafDxAlphaCurtain() {
}
