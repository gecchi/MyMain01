#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

SplineManufacture::SplineManufacture(const char* prm_source_file) : GgafObject() {

    _pSplSourceConnection = (SplineSourceConnection*)((P_GOD)->_pSplSourceManager->connect(prm_source_file));
    _pSplSource = _pSplSourceConnection->use();
    _sp = _pSplSource->_pSp;
    _rate_X = 1.0;
    _rate_Y = 1.0;
    _rate_Z = 1.0;
    _is_connected = true;
}
SplineManufacture::SplineManufacture(SplineSource* prm_pSplineSource) {
    _pSplSourceConnection = NULL;
    _pSplSource = prm_pSplineSource;
    _sp = _pSplSource->_pSp;
    _rate_X = 1.0;
    _rate_Y = 1.0;
    _rate_Z = 1.0;
    _is_connected = false;
}
void SplineManufacture::adjustAxisRate(float prm_rate_X, float prm_rate_Y, float prm_rate_Z) {
    _rate_X = prm_rate_X;
    _rate_Y = prm_rate_Y;
    _rate_Z = prm_rate_Z;
}

SplineManufacture::~SplineManufacture () {
    if (_pSplSourceConnection) {
        _pSplSourceConnection->close();
    }
    if (!_is_connected) {
        DELETE_IMPOSSIBLE_NULL(_pSplSource);
    }
}
