#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;



FixedFrameSplineSequence::FixedFrameSplineSequence(SplineManufacture* prm_pManufacture, GgafDx9KurokoA* prm_pKurokoA) :
        SplineSequence(prm_pManufacture, prm_pKurokoA) {
    _pFixedFrameSplineManufacture = (FixedFrameSplineManufacture*)prm_pManufacture;
    _SIN_RzMv_begin = 0;
    _COS_RzMv_begin = 0;
    _SIN_RyMv_begin = 0;
    _COS_RyMv_begin = 0;
}
FixedFrameSplineSequence::FixedFrameSplineSequence(GgafDx9KurokoA* prm_pKurokoA,
                                                 Spline3D* prmpSpl,
                                                 frame prm_spent_frame,
                                                 ang_velo prm_ang_veloRzRyMv):
        SplineSequence(NULL, prm_pKurokoA) {

    SplineSource *pSplSource = NEW SplineSource(prmpSpl);
    _pFixedFrameSplineManufacture = NEW FixedFrameSplineManufacture(pSplSource, prm_spent_frame, prm_ang_veloRzRyMv);
    _pManufacture = _pFixedFrameSplineManufacture;
    _is_create_pManufacture = true;
}


void FixedFrameSplineSequence::exec(SplinTraceOption prm_option) {
    if (_pFixedFrameSplineManufacture) {
        _is_executing = true;
        _option = prm_option;
        _SPframe = 0;
        Spline3D* pSpl = _pFixedFrameSplineManufacture->_sp;
        if (_option == RELATIVE_DIRECTION) {
            _X_begin = _flip_X*pSpl->_X_compute[0]*_pFixedFrameSplineManufacture->_rate_X + _offset_X - _pActor_target->_X ;
            _Y_begin = _flip_Y*pSpl->_Y_compute[0]*_pFixedFrameSplineManufacture->_rate_Y + _offset_Y - _pActor_target->_Y;
            _Z_begin = _flip_Z*pSpl->_Z_compute[0]*_pFixedFrameSplineManufacture->_rate_Z + _offset_Z - _pActor_target->_Z;
            _SIN_RzMv_begin = GgafDx9Util::SIN[_pActor_target->_pKurokoA->_angRzMv/ANGLE_RATE];
            _COS_RzMv_begin = GgafDx9Util::COS[_pActor_target->_pKurokoA->_angRzMv/ANGLE_RATE];
            _SIN_RyMv_begin = GgafDx9Util::SIN[_pActor_target->_pKurokoA->_angRyMv/ANGLE_RATE];
            _COS_RyMv_begin = GgafDx9Util::COS[_pActor_target->_pKurokoA->_angRyMv/ANGLE_RATE];
        } else if (_option == RELATIVE_COORD) {
            _X_begin = _flip_X*pSpl->_X_compute[0]*_pFixedFrameSplineManufacture->_rate_X + _offset_X - _pActor_target->_X;
            _Y_begin = _flip_Y*pSpl->_Y_compute[0]*_pFixedFrameSplineManufacture->_rate_Y + _offset_Y - _pActor_target->_Y;
            _Z_begin = _flip_Z*pSpl->_Z_compute[0]*_pFixedFrameSplineManufacture->_rate_Z + _offset_Z - _pActor_target->_Z;
        } else { //ABSOLUTE_COORD
            _X_begin = _flip_X*pSpl->_X_compute[0]*_pFixedFrameSplineManufacture->_rate_X + _offset_X;
            _Y_begin = _flip_Y*pSpl->_Y_compute[0]*_pFixedFrameSplineManufacture->_rate_Y + _offset_Y;
            _Z_begin = _flip_Z*pSpl->_Z_compute[0]*_pFixedFrameSplineManufacture->_rate_Z + _offset_Z;

        }
    }
}


void FixedFrameSplineSequence::behave() {
    if (_is_executing) {
        Spline3D* pSpl = _pFixedFrameSplineManufacture->_sp;
        GgafDx9KurokoA* _pKurokoA = _pActor_target->_pKurokoA;

        //現在の点INDEX
        int SPPointIndex = _SPframe/_pFixedFrameSplineManufacture->_SPframe_segment;
        if ( SPPointIndex == pSpl->_rnum) {
            //終了
            _is_executing = false;
            return;
        }

        //変わり目
        if (_SPframe % _pFixedFrameSplineManufacture->_SPframe_segment == 0) {
            double dx = _flip_X*pSpl->_X_compute[SPPointIndex]*_pFixedFrameSplineManufacture->_rate_X + _offset_X;
            double dy = _flip_Y*pSpl->_Y_compute[SPPointIndex]*_pFixedFrameSplineManufacture->_rate_Y + _offset_Y;
            double dz = _flip_Z*pSpl->_Z_compute[SPPointIndex]*_pFixedFrameSplineManufacture->_rate_Z + _offset_Z;


            //次の補間点（or基点)に移動方角を向ける
            if (_option == RELATIVE_DIRECTION) {
                //    並行移動 ＞ Z軸回転 ＞ Y軸回転
                //    | cosRz*cosRy                            , sinRz                , cosRz*-sinRy                            , 0 |
                //    | -sinRz*cosRy                           , cosRz                , -sinRz*-sinRy                           , 0 |
                //    | sinRy                                  , 0                    , cosRy                                   , 0 |
                //    | (dx*cosRz + dy*-sinRz)*cosRy + dz*sinRy, (dx*sinRz + dy*cosRz), (dx*cosRz + dy*-sinRz)*-sinRy + dz*cosRy, 1 |
                _pKurokoA->execTurnMvAngSequence(
                                ((dx * _COS_RzMv_begin + dy * -_SIN_RzMv_begin) * _COS_RyMv_begin + dz * _SIN_RyMv_begin) - _X_begin,
                                (dx * _SIN_RzMv_begin + dy * _COS_RzMv_begin) - _Y_begin,
                                ((dx * _COS_RzMv_begin + dy * -_SIN_RzMv_begin) * -_SIN_RyMv_begin + dz * _COS_RyMv_begin) - _Z_begin,
                                _pFixedFrameSplineManufacture->_ang_veloRzRyMv, 0,
                                TURN_CLOSE_TO, true
                              );
            } else if (_option == RELATIVE_COORD) {
                //相対座標ターゲット
                _pKurokoA->execTurnMvAngSequence(
                                dx - _X_begin, dy - _Y_begin, dz - _Z_begin,
                                _pFixedFrameSplineManufacture->_ang_veloRzRyMv, 0,
                                TURN_CLOSE_TO, true
                              );
            } else { //RELATIVE_DIRECTION
                //絶対座標ターゲット
                _pKurokoA->execTurnMvAngSequence(
                                dx, dy, dz,
                                _pFixedFrameSplineManufacture->_ang_veloRzRyMv, 0,
                                TURN_CLOSE_TO, true
                              );
            }
            if (SPPointIndex == 0) {
                //_paSPMvVeloTo[0] は未定義なので、特別処理
                if (_pActor_target->_pKurokoA->_veloMv <= 0) {
                    _pActor_target->_pKurokoA->setMvVelo(1000);
                } else {
                    //なにもせん
                }
            } else {
                _pActor_target->_pKurokoA->setMvVelo(_pFixedFrameSplineManufacture->_paSPMvVeloTo[SPPointIndex]);
            }
        }
        _SPframe++;
    }

}
FixedFrameSplineSequence::~FixedFrameSplineSequence() {
}
