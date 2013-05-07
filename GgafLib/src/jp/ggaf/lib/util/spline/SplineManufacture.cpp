#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

SplineManufacture::SplineManufacture(const char* prm_source_file) : GgafObject() {
    _source_file = std::string(prm_source_file);
    _pSplSrcCon = (SplineSourceConnection*)((P_GOD)->_pSplSrcManager->connect(prm_source_file, this));
    _pSplSrc = _pSplSrcCon->peek();
    _sp = _pSplSrc->_pSp;
    _paDistance_to = NEW coord[_sp->_rnum];
    _rate_X = 1.0;
    _rate_Y = 1.0;
    _rate_Z = 1.0;
    _total_distance = 0;
}
SplineManufacture::SplineManufacture(SplineSource* prm_pSplSrc) {
    _source_file = "Nothing";
    _pSplSrcCon = nullptr;
    _pSplSrc = prm_pSplSrc;
    _sp = _pSplSrc->_pSp;
    _paDistance_to = NEW coord[_sp->_rnum];
    _rate_X = 1.0;
    _rate_Y = 1.0;
    _rate_Z = 1.0;
    _total_distance = 0;
}
void SplineManufacture::adjustAxisRate(double prm_rate_X, double prm_rate_Y, double prm_rate_Z) {
    _rate_X = prm_rate_X;
    _rate_Y = prm_rate_Y;
    _rate_Z = prm_rate_Z;
}
void SplineManufacture::calculate() {
    coord x_from, y_from, z_from;
    coord x_to, y_to, z_to;

    x_to = _sp->_X_compute[0]*_rate_X;
    y_to = _sp->_Y_compute[0]*_rate_Y;
    z_to = _sp->_Z_compute[0]*_rate_Z;

    for (int t = 1; t < _sp->_rnum; t ++) {
        x_from = x_to;
        y_from = y_to;
        z_from = z_to;
        x_to = _sp->_X_compute[t]*_rate_X;
        y_to = _sp->_Y_compute[t]*_rate_Y;
        z_to = _sp->_Z_compute[t]*_rate_Z;
        _paDistance_to[t] = UTIL::getDistance(
                                    x_from,
                                    y_from,
                                    z_from,
                                    x_to,
                                    y_to,
                                    z_to
                                 );
        _total_distance += _paDistance_to[t];
    }
    _paDistance_to[0] = 0; //_paDistance_to[0] は最初の補完点までの距離となるべきだが、
                          //SplineKurokoLeader::start() を行うまで距離が確定しない。ので使用不可。
                          //最初の補完点までの距離は、SplineKurokoLeader メンバーの _distance_to_begin で
                          //取得可能。
}

SplineManufacture::~SplineManufacture () {
    if (_pSplSrcCon) {
        _pSplSrcCon->close();
    }
//    if (!_is_connected) {
//        GGAF_DELETE(_pSplSrc);
//    }
}
