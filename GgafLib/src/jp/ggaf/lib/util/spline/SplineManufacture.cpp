#include "stdafx.h"
#include "jp/ggaf/lib/util/spline/SplineManufacture.h"

#include "jp/ggaf/lib/DefaultGod.h"
#include "jp/ggaf/lib/util/spline/SplineSource.h"
#include "jp/ggaf/lib/util/spline/SplineLine.h"
#include "jp/ggaf/lib/manager/SplineSourceConnection.h"
#include "jp/ggaf/lib/manager/SplineSourceManager.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

SplineManufacture::SplineManufacture(const char* prm_source_file) : GgafObject() {
    _source_file = std::string(prm_source_file);
    _pSplSrcCon = (SplineSourceConnection*)((P_GOD)->_pSplSrcManager->connect(prm_source_file, this));
    _pSplSrc = _pSplSrcCon->peek();
    _sp = _pSplSrc->_pSp;
    _paDistance_to = NEW coord[_sp->_rnum];
    _rate_x = 1.0;
    _rate_y = 1.0;
    _rate_z = 1.0;
    _total_distance = 0;
}
SplineManufacture::SplineManufacture(SplineSource* prm_pSplSrc) {
    _source_file = "Nothing";
    _pSplSrcCon = nullptr;
    _pSplSrc = prm_pSplSrc;
    _sp = _pSplSrc->_pSp;
    _paDistance_to = NEW coord[_sp->_rnum];
    _rate_x = 1.0;
    _rate_y = 1.0;
    _rate_z = 1.0;
    _total_distance = 0;
}
void SplineManufacture::adjustAxisRate(double prm_rate_x, double prm_rate_y, double prm_rate_z) {
    _rate_x = prm_rate_x;
    _rate_y = prm_rate_y;
    _rate_z = prm_rate_z;
}
void SplineManufacture::calculate() {
    coord x_from, y_from, z_from;
    coord x_to, y_to, z_to;

    x_to = _sp->_x_compute[0]*_rate_x;
    y_to = _sp->_y_compute[0]*_rate_y;
    z_to = _sp->_z_compute[0]*_rate_z;
    int rnum = _sp->_rnum;
    for (int t = 1; t < rnum; t ++) {
        x_from = x_to;
        y_from = y_to;
        z_from = z_to;
        x_to = _sp->_x_compute[t]*_rate_x;
        y_to = _sp->_y_compute[t]*_rate_y;
        z_to = _sp->_z_compute[t]*_rate_z;
        _paDistance_to[t] = UTIL::getDistance(x_from, y_from, z_from,
                                              x_to  , y_to  , z_to   );
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
