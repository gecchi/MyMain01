#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

SplineManufacture::SplineManufacture(const char* prm_source_file) : GgafObject() {
    _source_file = std::string(prm_source_file);
    _pSplSrcCon = (SplineSourceConnection*)((P_GOD)->_pSplSrcManager->connect(prm_source_file));
    _pSplSrc = _pSplSrcCon->fetch();
    _sp = _pSplSrc->_pSp;
    _rate_X = 1.0;
    _rate_Y = 1.0;
    _rate_Z = 1.0;
}
SplineManufacture::SplineManufacture(SplineSource* prm_pSplSrc) {
    _source_file = "Nothing";
    _pSplSrcCon = NULL;
    _pSplSrc = prm_pSplSrc;
    _sp = _pSplSrc->_pSp;
    _rate_X = 1.0;
    _rate_Y = 1.0;
    _rate_Z = 1.0;
}
void SplineManufacture::adjustAxisRate(double prm_rate_X, double prm_rate_Y, double prm_rate_Z) {
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
