#include "jp/ggaf/dx/util/curve/CurveManufacture.h"

#include "jp/ggaf/dx/God.h"
#include "jp/ggaf/dx/util/curve/CurveSource.h"
#include "jp/ggaf/dx/manager/CurveSourceConnection.h"
#include "jp/ggaf/dx/manager/CurveSourceManager.h"
#include "jp/ggaf/dx/util/curve/FixedFrameCurveGeoDriverLeader.h"
#include "jp/ggaf/dx/util/curve/FixedFrameCurveVecDriverLeader.h"
#include "jp/ggaf/dx/util/curve/FixedVelocityCurveVecDriverLeader.h"
#include "jp/ggaf/dx/util/curve/SteppedCoordCurveVecDriverLeader.h"

using namespace GgafDx;

CurveManufacture::CurveManufacture(const char* prm_coord_spl_file) : GgafCore::Object() {
    _ldr_file = std::string(prm_coord_spl_file);
    _pCurveSrcCon = connectToCurveSourceManager(prm_coord_spl_file);
    _pCurve = _pCurveSrcCon->peek();
    _paDistance_to = NEW coord[_pCurve->_rnum];
    _rate_x = 1.0;
    _rate_y = 1.0;
    _rate_z = 1.0;
    _total_distance = 0;
    _is_calculated = false;
    _move_method = (MoveMethod)0;
    _move_driver = VecDriver;
}

CurveManufacture::CurveManufacture(CurveSource* prm_pCurve) {
    _ldr_file = "Nothing";
    _pCurveSrcCon = nullptr;
    _pCurve = prm_pCurve;
    _paDistance_to = NEW coord[_pCurve->_rnum];
    _rate_x = 1.0;
    _rate_y = 1.0;
    _rate_z = 1.0;
    _total_distance = 0;
    _is_calculated = false;
    _move_method = (MoveMethod)0;
    _move_driver = VecDriver;
}

void CurveManufacture::adjustAxisRate(double prm_rate_x, double prm_rate_y, double prm_rate_z) {
    _rate_x = prm_rate_x;
    _rate_y = prm_rate_y;
    _rate_z = prm_rate_z;
    _is_calculated = false;
}

void CurveManufacture::calculate() {
    coord x_to = _pCurve->_x_compute[0]*_rate_x;
    coord y_to = _pCurve->_y_compute[0]*_rate_y;
    coord z_to = _pCurve->_z_compute[0]*_rate_z;
    int rnum = _pCurve->_rnum;
    coord x_from, y_from, z_from;
    for (int t = 1; t < rnum; t ++) {
        x_from = x_to;
        y_from = y_to;
        z_from = z_to;
        x_to = _pCurve->_x_compute[t]*_rate_x;
        y_to = _pCurve->_y_compute[t]*_rate_y;
        z_to = _pCurve->_z_compute[t]*_rate_z;
        _paDistance_to[t] = UTIL::getDistance(x_from, y_from, z_from,
                                              x_to  , y_to  , z_to   );
        _total_distance += _paDistance_to[t];
    }
    _paDistance_to[0] = 0; //_paDistance_to[0] は最初の補完点までの距離となるべきだが、
                           //DriverLeader::start() を行うまで距離が確定しない。ので使用不可。
                           //最初の補完点までの距離は、DriverLeader メンバーの _distance_to_begin で
                           //取得可能。
    _is_calculated = true;
}

DriverLeader* CurveManufacture::createDriverLeader(GgafDx::GeometricActor* prm_pActor) {

    DriverLeader* pDriverLeader = nullptr;
    if (_move_method == FixedVelocity) {
        if (_move_driver == GeoDriver) {
            //pDriverLeader = NEW FixedVelocityCurveGeoDriverLeader(this, prm_pActor->getGeoDriver());
        } else if (_move_driver == VecDriver) {
            pDriverLeader = NEW FixedVelocityCurveVecDriverLeader(this, prm_pActor->getVecDriver());
        }
    } else if (_move_method == FixedVelocity) {
        if (_move_driver == GeoDriver) {
            pDriverLeader = NEW FixedFrameCurveGeoDriverLeader(this, prm_pActor->getGeoDriver());
        } else if (_move_driver == VecDriver) {
            pDriverLeader = NEW FixedFrameCurveVecDriverLeader(this, prm_pActor->getVecDriver());
        }
    } else if (_move_method == SteppedCoord) {
        if (_move_driver == GeoDriver) {
            //pDriverLeader = NEW SteppedCoordCurveGeoDriverLeader(this, prm_pActor->getGeoDriver());
        } else if (_move_driver == VecDriver) {
            pDriverLeader = NEW SteppedCoordCurveVecDriverLeader(this, prm_pActor->getVecDriver());
        }
    }

    if (!pDriverLeader) {
        throwCriticalException("CurveManufacture::createDriverLeader() DriverLeader 情報が特定できません。_move_method="<<_move_method+"/_move_driver="<<_move_driver);
    }
    return pDriverLeader;
}

DriverLeader* CurveManufacture::createVecDriverLeader(GgafDx::VecDriver* prm_pVecDriver) {
    throwCriticalException("CurveManufacture::createVecDriverLeader() 下位でオーバーライドして実装が必要です。");
    return nullptr;
}

DriverLeader* CurveManufacture::createGeoDriverLeader(GgafDx::GeoDriver* prm_pGeoDriver) {
    throwCriticalException("CurveManufacture::createGeoDriverLeader() 下位でオーバーライドして実装が必要です。");
    return nullptr;
}

CurveManufacture::~CurveManufacture () {
    if (_pCurveSrcCon) {
        _pCurveSrcCon->close();
    }
}
