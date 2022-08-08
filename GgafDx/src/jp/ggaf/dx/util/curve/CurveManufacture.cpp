#include "jp/ggaf/dx/util/curve/CurveManufacture.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/util/curve/CurveSource.h"
#include "jp/ggaf/dx/manager/CurveSourceConnection.h"
#include "jp/ggaf/dx/manager/CurveSourceManager.h"
#include "jp/ggaf/dx/util/curve/FixedFrameCurveAxisVehicleLeader.h"
#include "jp/ggaf/dx/util/curve/FixedFrameCurveVecVehicleLeader.h"
#include "jp/ggaf/dx/util/curve/FixedVelocityCurveVecVehicleLeader.h"
#include "jp/ggaf/dx/util/curve/SteppedCoordCurveVecVehicleLeader.h"

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
    _move_driver = VecVehicle;
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
    _move_driver = VecVehicle;
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
                           //VehicleLeader::start() を行うまで距離が確定しない。ので使用不可。
                           //最初の補完点までの距離は、VehicleLeader メンバーの _distance_to_begin で
                           //取得可能。
    _is_calculated = true;
}

VehicleLeader* CurveManufacture::createVehicleLeader(GgafDx::GeometricActor* prm_pActor) {

    VehicleLeader* pVehicleLeader = nullptr;
    if (_move_method == FixedVelocity) {
        if (_move_driver == AxisVehicle) {
            //pVehicleLeader = NEW FixedVelocityCurveAxisVehicleLeader(this, prm_pActor->getAxisVehicle());
        } else if (_move_driver == VecVehicle) {
            pVehicleLeader = NEW FixedVelocityCurveVecVehicleLeader(this, prm_pActor->getVecVehicle());
        }
    } else if (_move_method == FixedVelocity) {
        if (_move_driver == AxisVehicle) {
            pVehicleLeader = NEW FixedFrameCurveAxisVehicleLeader(this, prm_pActor->getAxisVehicle());
        } else if (_move_driver == VecVehicle) {
            pVehicleLeader = NEW FixedFrameCurveVecVehicleLeader(this, prm_pActor->getVecVehicle());
        }
    } else if (_move_method == SteppedCoord) {
        if (_move_driver == AxisVehicle) {
            //pVehicleLeader = NEW SteppedCoordCurveAxisVehicleLeader(this, prm_pActor->getAxisVehicle());
        } else if (_move_driver == VecVehicle) {
            pVehicleLeader = NEW SteppedCoordCurveVecVehicleLeader(this, prm_pActor->getVecVehicle());
        }
    }

    if (!pVehicleLeader) {
        throwCriticalException("CurveManufacture::createVehicleLeader() VehicleLeader 情報が特定できません。_move_method="<<_move_method+"/_move_driver="<<_move_driver);
    }
    return pVehicleLeader;
}

VehicleLeader* CurveManufacture::createVecVehicleLeader(GgafDx::VecVehicle* prm_pVecVehicle) {
    throwCriticalException("CurveManufacture::createVecVehicleLeader() 下位でオーバーライドして実装が必要です。");
    return nullptr;
}

VehicleLeader* CurveManufacture::createAxisVehicleLeader(GgafDx::AxisVehicle* prm_pAxisVehicle) {
    throwCriticalException("CurveManufacture::createAxisVehicleLeader() 下位でオーバーライドして実装が必要です。");
    return nullptr;
}

CurveManufacture::~CurveManufacture () {
    if (_pCurveSrcCon) {
        _pCurveSrcCon->close();
    }
}
