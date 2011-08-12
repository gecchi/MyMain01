#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
FixedVelocitySplineSequence::FixedVelocitySplineSequence(SplineManufacture* prm_pManufacture, GgafDx9KurokoA* prm_pKurokoA) :
        SplineSequence(prm_pManufacture, prm_pKurokoA) {
    _pFixedVelocitySplineManufacture = (FixedVelocitySplineManufacture*)prm_pManufacture;
    _fFrame_executing = 0.0f;
    _fFrame_next_point = -0.00001f;
    _point_index = 0;
    _SIN_RzMv_begin = 0.0f;
    _COS_RzMv_begin = 0.0f;
    _SIN_RyMv_begin = 0.0f;
    _COS_RyMv_begin = 0.0f;

}

FixedVelocitySplineSequence::FixedVelocitySplineSequence(GgafDx9KurokoA* prm_pKurokoA,
                                                         Spline3D* prmpSpl,
                                                         ang_velo prm_ang_veloRzRyMv):
        SplineSequence(NULL, prm_pKurokoA) {
    SplineSource *pSplSource = NEW SplineSource(prmpSpl);
    _pFixedVelocitySplineManufacture = NEW FixedVelocitySplineManufacture(pSplSource, prm_ang_veloRzRyMv);
    _pManufacture = _pFixedVelocitySplineManufacture;
    _is_create_pManufacture = true;
}

void FixedVelocitySplineSequence::exec(SplinTraceOption prm_option) {
    if (_pFixedVelocitySplineManufacture) {
        _is_executing = true;
        _option = prm_option;
        _fFrame_executing = 0.0f;
        _fFrame_next_point = -0.00001f;
        _point_index = 0;
        Spline3D* pSpl = _pFixedVelocitySplineManufacture->_sp;
        if (_option == RELATIVE_DIRECTION) {
            _X_begin = _flip_X*pSpl->_X_compute[0]*_pFixedVelocitySplineManufacture->_rate_X + _offset_X - _pActor_target->_X ;
            _Y_begin = _flip_Y*pSpl->_Y_compute[0]*_pFixedVelocitySplineManufacture->_rate_Y + _offset_Y - _pActor_target->_Y;
            _Z_begin = _flip_Z*pSpl->_Z_compute[0]*_pFixedVelocitySplineManufacture->_rate_Z + _offset_Z - _pActor_target->_Z;
            _SIN_RzMv_begin = GgafDx9Util::SIN[_pActor_target->_pKurokoA->_angRzMv/ANGLE_RATE];
            _COS_RzMv_begin = GgafDx9Util::COS[_pActor_target->_pKurokoA->_angRzMv/ANGLE_RATE];
            _SIN_RyMv_begin = GgafDx9Util::SIN[_pActor_target->_pKurokoA->_angRyMv/ANGLE_RATE];
            _COS_RyMv_begin = GgafDx9Util::COS[_pActor_target->_pKurokoA->_angRyMv/ANGLE_RATE];
        } else if (_option == RELATIVE_COORD) {
            _X_begin = _flip_X*pSpl->_X_compute[0]*_pFixedVelocitySplineManufacture->_rate_X + _offset_X - _pActor_target->_X;
            _Y_begin = _flip_Y*pSpl->_Y_compute[0]*_pFixedVelocitySplineManufacture->_rate_Y + _offset_Y - _pActor_target->_Y;
            _Z_begin = _flip_Z*pSpl->_Z_compute[0]*_pFixedVelocitySplineManufacture->_rate_Z + _offset_Z - _pActor_target->_Z;
        } else { //ABSOLUTE_COORD
            _X_begin = _flip_X*pSpl->_X_compute[0]*_pFixedVelocitySplineManufacture->_rate_X + _offset_X;
            _Y_begin = _flip_Y*pSpl->_Y_compute[0]*_pFixedVelocitySplineManufacture->_rate_Y + _offset_Y;
            _Z_begin = _flip_Z*pSpl->_Z_compute[0]*_pFixedVelocitySplineManufacture->_rate_Z + _offset_Z;
        }
    }
}

void FixedVelocitySplineSequence::behave() {
    if (_is_executing) {
        GgafDx9KurokoA* _pKurokoA = _pActor_target->_pKurokoA;
        //変わり目
//        printf("%s _point_index=%d _fFrame_executing=%f _fFrame_next_point=%f\n",_pActor_target->getName(), _point_index,_fFrame_executing, _fFrame_next_point);
        if (_fFrame_executing >= _fFrame_next_point) {
//            printf("%s _point_index=%d _fFrame_executing >= _fFrame_next_point HIT\n",_pActor_target->getName(), _point_index);
            Spline3D* pSpl = _pFixedVelocitySplineManufacture->_sp;
            if (_point_index == 0) {
                //始点へ行く！
                int distace_to;
                double dx = _flip_X*pSpl->_X_compute[0]*_pFixedVelocitySplineManufacture->_rate_X + _offset_X;
                double dy = _flip_Y*pSpl->_Y_compute[0]*_pFixedVelocitySplineManufacture->_rate_Y + _offset_Y;
                double dz = _flip_Z*pSpl->_Z_compute[0]*_pFixedVelocitySplineManufacture->_rate_Z + _offset_Z;
                if (_option == RELATIVE_DIRECTION) {
                    //    並行移動 ＞ Z軸回転 ＞ Y軸回転
                    //    | cosRz*cosRy                            , sinRz                , cosRz*-sinRy                            , 0 |
                    //    | -sinRz*cosRy                           , cosRz                , -sinRz*-sinRy                           , 0 |
                    //    | sinRy                                  , 0                    , cosRy                                   , 0 |
                    //    | (dx*cosRz + dy*-sinRz)*cosRy + dz*sinRy, (dx*sinRz + dy*cosRz), (dx*cosRz + dy*-sinRz)*-sinRy + dz*cosRy, 1 |

                    distace_to = GgafDx9Util::getDistance(
                                            (double)_pActor_target->_X,
                                            (double)_pActor_target->_Y,
                                            (double)_pActor_target->_Z,
                                            ((dx * _COS_RzMv_begin + dy * -_SIN_RzMv_begin) * _COS_RyMv_begin + dz * _SIN_RyMv_begin) - _X_begin,
                                            (dx * _SIN_RzMv_begin + dy * _COS_RzMv_begin) - _Y_begin,
                                            ((dx * _COS_RzMv_begin + dy * -_SIN_RzMv_begin) * -_SIN_RyMv_begin + dz * _COS_RyMv_begin) - _Z_begin
                                         );
                } else if (_option == RELATIVE_COORD) {
                    //相対座標ターゲット
                    distace_to = GgafDx9Util::getDistance(
                                            (double)_pActor_target->_X,
                                            (double)_pActor_target->_Y,
                                            (double)_pActor_target->_Z,
                                            dx - _X_begin,
                                            dy - _Y_begin,
                                            dz - _Z_begin
                                         );
                } else { //ABSOLUTE_COORD
                    //絶対座標ターゲット
                    distace_to = GgafDx9Util::getDistance(
                                            (double)_pActor_target->_X,
                                            (double)_pActor_target->_Y,
                                            (double)_pActor_target->_Z,
                                            dx,
                                            dy,
                                            dz
                                         );
                }


                //始点までに必要なフレーム数取得
//                _paFrame_need_at[0] =  (float)(1.0*distace_to / _veloMvUnit);
//                _fFrame_next_point = _paFrame_need_at[0];
                _fFrame_next_point = (float)(1.0*distace_to / _pFixedVelocitySplineManufacture->_veloMvUnit);
            } else {
                //始点以外の場合
                //次の補間点（or基点)に移動方角を向ける
                double dx = _flip_X*pSpl->_X_compute[_point_index]*_pFixedVelocitySplineManufacture->_rate_X + _offset_X;
                double dy = _flip_Y*pSpl->_Y_compute[_point_index]*_pFixedVelocitySplineManufacture->_rate_Y + _offset_Y;
                double dz = _flip_Z*pSpl->_Z_compute[_point_index]*_pFixedVelocitySplineManufacture->_rate_Z + _offset_Z;
                if (_option == RELATIVE_DIRECTION) {
                    //    並行移動 ＞ Z軸回転 ＞ Y軸回転
                    //    | cosRz*cosRy                            , sinRz                , cosRz*-sinRy                            , 0 |
                    //    | -sinRz*cosRy                           , cosRz                , -sinRz*-sinRy                           , 0 |
                    //    | sinRy                                  , 0                    , cosRy                                   , 0 |
                    //    | (dx*cosRz + dy*-sinRz)*cosRy + dz*sinRy, (dx*sinRz + dy*cosRz), (dx*cosRz + dy*-sinRz)*-sinRy + dz*cosRy, 1 |
                    _pKurokoA->execTurnMvAngSequence(
                                    ((dx*_COS_RzMv_begin + dy*-_SIN_RzMv_begin) * _COS_RyMv_begin + dz*_SIN_RyMv_begin) - _X_begin,
                                    (dx*_SIN_RzMv_begin + dy*_COS_RzMv_begin) - _Y_begin,
                                    ((dx*_COS_RzMv_begin + dy*-_SIN_RzMv_begin) * -_SIN_RyMv_begin + dz*_COS_RyMv_begin) - _Z_begin,
                                    _pFixedVelocitySplineManufacture->_ang_veloRzRyMv, 0,
                                    TURN_CLOSE_TO, true);
                } else if (_option == RELATIVE_COORD) {
                    //相対座標ターゲット
                    _pKurokoA->execTurnMvAngSequence(
                                    dx - _X_begin, dy - _Y_begin, dz - _Z_begin,
                                    _pFixedVelocitySplineManufacture->_ang_veloRzRyMv, 0,
                                    TURN_CLOSE_TO, true
                                  );
                } else { //ABSOLUTE_COORD
                    //絶対座標ターゲット
                    _pKurokoA->execTurnMvAngSequence(
                                    dx, dy, dz,
                                    _pFixedVelocitySplineManufacture->_ang_veloRzRyMv, 0,
                                    TURN_CLOSE_TO, true
                                  );
                }
                //次の補完点までに必要なフレーム数を更新
                _fFrame_next_point = _pFixedVelocitySplineManufacture->_paFrame_need_at[0] +
                                     _pFixedVelocitySplineManufacture->_paFrame_need_at[_point_index];
            }

            _point_index++;
            if ( _point_index == pSpl->_rnum) {
//                printf(" %s END _point_index=%d\n",_pActor_target->getName(),_point_index);
                //終了
                _is_executing = false;
                return;
            }
        } else {

//            printf("%s XX _point_index=%d _fFrame_executing >= _fFrame_next_point NO HIT\n",_pActor_target->getName(),_point_index);
        }

        //キャラの速度が1000ならば、_fFrame_executing ++;
        //キャラの速度が2000ならば  _fFrame_executing += 2.0;
        //キャラの速度が500ならば、 _fFrame_executing += 0.5
        _fFrame_executing = _fFrame_executing +  (1.0*_pKurokoA->_veloMv / LEN_UNIT);
    }

}
FixedVelocitySplineSequence::~FixedVelocitySplineSequence() {
}
