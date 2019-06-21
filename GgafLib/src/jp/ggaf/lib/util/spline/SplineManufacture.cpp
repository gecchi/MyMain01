#include "jp/ggaf/lib/util/spline/SplineManufacture.h"

#include "jp/ggaf/lib/DefaultGod.h"
#include "jp/ggaf/lib/util/spline/SplineSource.h"
#include "jp/ggaf/lib/manager/SplineSourceConnection.h"
#include "jp/ggaf/lib/manager/SplineSourceManager.h"



using namespace GgafLib;

SplineManufacture::SplineManufacture(const char* prm_coord_data_file) : GgafCore::Object() {
    _spl_file = std::string(prm_coord_data_file);
    _pSplSrcCon = connectToSplineSourceManager(prm_coord_data_file);
    _pSpl = _pSplSrcCon->peek();
    _paDistance_to = NEW coord[_pSpl->_rnum];
    _rate_x = 1.0;
    _rate_y = 1.0;
    _rate_z = 1.0;
    _total_distance = 0;
    _is_calculated = false;
}

SplineManufacture::SplineManufacture(SplineSource* prm_pSpl) {
    _spl_file = "Nothing";
    _pSplSrcCon = nullptr;
    _pSpl = prm_pSpl;
    _paDistance_to = NEW coord[_pSpl->_rnum];
    _rate_x = 1.0;
    _rate_y = 1.0;
    _rate_z = 1.0;
    _total_distance = 0;
    _is_calculated = false;
}

void SplineManufacture::adjustAxisRate(double prm_rate_x, double prm_rate_y, double prm_rate_z) {
    _rate_x = prm_rate_x;
    _rate_y = prm_rate_y;
    _rate_z = prm_rate_z;
    _is_calculated = false;
}

void SplineManufacture::calculate() {
    coord x_to = _pSpl->_x_compute[0]*_rate_x;
    coord y_to = _pSpl->_y_compute[0]*_rate_y;
    coord z_to = _pSpl->_z_compute[0]*_rate_z;
    int rnum = _pSpl->_rnum;
    coord x_from, y_from, z_from;
    for (int t = 1; t < rnum; t ++) {
        x_from = x_to;
        y_from = y_to;
        z_from = z_to;
        x_to = _pSpl->_x_compute[t]*_rate_x;
        y_to = _pSpl->_y_compute[t]*_rate_y;
        z_to = _pSpl->_z_compute[t]*_rate_z;
        _paDistance_to[t] = UTIL::getDistance(x_from, y_from, z_from,
                                              x_to  , y_to  , z_to   );
        _total_distance += _paDistance_to[t];
    }
    _paDistance_to[0] = 0; //_paDistance_to[0] は最初の補完点までの距離となるべきだが、
                           //SplineLeader::start() を行うまで距離が確定しない。ので使用不可。
                           //最初の補完点までの距離は、SplineLeader メンバーの _distance_to_begin で
                           //取得可能。
    _is_calculated = true;
}

SplineLeader* SplineManufacture::createRikishaLeader(GgafDx::Rikisha* prm_pRikisha) {
    throwCriticalException("SplineManufacture::createRikishaLeader() 下位でオーバーライドして実装が必要です。");
    return nullptr;
}

SplineLeader* SplineManufacture::createKagoLeader(GgafDx::Kago* prm_pKago) {
    throwCriticalException("SplineManufacture::createKagoLeader() 下位でオーバーライドして実装が必要です。");
    return nullptr;
}

SplineManufacture::~SplineManufacture () {
    if (_pSplSrcCon) {
        _pSplSrcCon->close();
    }
}
