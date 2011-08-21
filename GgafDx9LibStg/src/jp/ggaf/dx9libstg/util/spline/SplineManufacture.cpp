#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

SplineManufacture::SplineManufacture(const char* prm_source_file) : GgafObject() {

    _pSplSrcCon = (SplineSourceConnection*)((P_GOD)->_pSplSrcManager->connect(prm_source_file));
    _pSplSrc = _pSplSrcCon->use();
    _sp = _pSplSrc->_pSp;
    _rate_X = 1.0f;
    _rate_Y = 1.0f;
    _rate_Z = 1.0f;
}
SplineManufacture::SplineManufacture(SplineSource* prm_pSplSrc) {
    _pSplSrcCon = NULL;
    _pSplSrc = prm_pSplSrc;
    _sp = _pSplSrc->_pSp;
    _rate_X = 1.0f;
    _rate_Y = 1.0f;
    _rate_Z = 1.0f;
}
void SplineManufacture::adjustAxisRate(float prm_rate_X, float prm_rate_Y, float prm_rate_Z) {
    _rate_X = prm_rate_X;
    _rate_Y = prm_rate_Y;
    _rate_Z = prm_rate_Z;
}

SplineManufacture::~SplineManufacture () {
    if (_pSplSrcCon) {
        _pSplSrcCon->close();
    }
//    if (!_is_connected) {
//        DELETE_IMPOSSIBLE_NULL(_pSplSrc);
//    }
}
