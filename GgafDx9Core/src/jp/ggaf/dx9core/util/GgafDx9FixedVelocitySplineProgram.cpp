#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9FixedVelocitySplineProgram::GgafDx9FixedVelocitySplineProgram() : GgafDx9SplineProgram() {

    _paSPDistaceTo = NULL;
    _paSPNeedFrameTo = NULL;
    _is_executing = false;
    _option = 0;

    _X_relative = 0;
    _Y_relative = 0;
    _Z_relative = 0;
    _SPNextChangeFrame = 0;
    _SPPointIndex = 0;
    _angRotMove = ANGLE360;
}

GgafDx9FixedVelocitySplineProgram::GgafDx9FixedVelocitySplineProgram(double prm_paaCriteriaPoints[][3],
                                                               int prm_point_num,
                                                               double prm_accuracy,
                                                               velo prm_veloMove,
                                                               angvelo prm_angRotMove )

                                        : GgafDx9SplineProgram(prm_paaCriteriaPoints,
                                                               prm_point_num,
                                                               prm_accuracy)      {


    //各点の時点の、距離と必要なフレーム数を予め全部求めておく

    // prm_paaCriteriaPoints[2][3] = { {1000,2000,3000}, {2000,1000,0}, {3900, 0, 1000} }
    // prm_point_num = 3          //基点の数
    // prm_accuracy = 0.25(=1/4)  //補完点精度
    // prm_veloMove = 5000        //速度
    // の場合、下図のようになります。
    //
    // X:基点
    // o:基点間の補完点（スプライン曲線通過点）
    // X--o: 移動予定の座標線
    // _paSPDistaceTo[] : 次の補完点までの距離
    // _paSPNeedFrameTo[] : 次の補完点到達に必要なフレーム数
    //
    // sp._rnum は合計の点の数を返す。したがって sp._rnum = 9 になる。
    // prm_accuracy が綺麗な分数にならない場合、基点上に補完点が繰るかとか、全然わからないので、sp._rnumを必ず使用せよ
    // 下図は綺麗に重なった場合の図である。
    //
    //                           ＜速さは  prm_veloMove = 5000＞
    //      距離：_paSPDistaceTo[1]          _paSPDistaceTo[5]           _paSPDistaceTo[8]
    //
    //      時間：_paSPNeedFrameTo[1]        _paSPNeedFrameTo[5]         _paSPNeedFrameTo[8]
    //           = _paSPDistaceTo[1]/5000   = _paSPDistaceTo[5]/5000     = _paSPDistaceTo[8]/5000  Frame 必要
    //                    ||                     ||                         ||
    //                   <-->                 <------>                    <----->
    //                  X----o----o----o-----X--------o---------o--------o-------X
    //                  ^                    ^        ^                          ^
    //                  |                    |        |                          |
    //            (sp._X_compute[0],         | (sp._X_compute[5],        sp._X_compute[8]
    //             sp._Y_compute[0],         |  sp._Y_compute[5],        sp._Y_compute[8]
    //             sp._Z_compute[0])         |  sp._Z_compute[5])        sp._Z_compute[8]
    //                  |                    |                                   |
    // (prm_paaCriteriaPoints[0][0],   (prm_paaCriteriaPoints[1][0],    (prm_paaCriteriaPoints[2][0],
    //  prm_paaCriteriaPoints[0][1],    prm_paaCriteriaPoints[1][1],     prm_paaCriteriaPoints[2][1],
    //  prm_paaCriteriaPoints[0][2])    prm_paaCriteriaPoints[1][2])     prm_paaCriteriaPoints[2][2])
    //   = (1000,2000,3000)             = (2000,1000,0)                    = (3900, 0, 1000)
    //
    //                 <--------------------------------------------------------->
    //                                 ずっと prm_veloMove で移動
    //

    _angRotMove = prm_angRotMove;
    _veloMove = prm_veloMove;
    _paSPDistaceTo = NEW int[_sp->_rnum];
    _paSPNeedFrameTo = NEW DWORD[_sp->_rnum];

    int x_from, y_from, z_from;
    int x_to, y_to, z_to;

    x_to = _sp->_X_compute[0];
    y_to = _sp->_Y_compute[0];
    z_to = _sp->_Z_compute[0];
    for (int t = 1; t < _sp->_rnum; t ++) {
        x_from = x_to;
        y_from = y_to;
        z_from = z_to;
        x_to = _sp->_X_compute[t];
        y_to = _sp->_Y_compute[t];
        z_to = _sp->_Z_compute[t];
        _paSPDistaceTo[t] = GgafDx9Util::getDistance(
                                    x_from,
                                    y_from,
                                    z_from,
                                    x_to,
                                    y_to,
                                    z_to
                                 );

        //距離 paDistaceTo[t] を、速度 prm_veloMove で移動するのに必要なフレーム数を求める。
        //時間＝距離÷速さ
        _paSPNeedFrameTo[t] = (DWORD)(1.0*_paSPDistaceTo[t] / prm_veloMove);

    }

}

void GgafDx9FixedVelocitySplineProgram::begin(GgafDx9GeometricActor* prm_pActor, int prm_option) {

    if (_sp != NULL) {
        _is_executing = true;
        _option = prm_option;
        _pActor_executing = prm_pActor;
        _SPframe = 0;
        _SPNextChangeFrame = 0;
        _SPPointIndex = 0;
        if (_option == 1) {
            _X_relative = _sp->_X_compute[0] - _pActor_executing->_X ;
            _Y_relative = _sp->_Y_compute[0] - _pActor_executing->_Y;
            _Z_relative = _sp->_Z_compute[0] - _pActor_executing->_Z;
        }


    }
}




void GgafDx9FixedVelocitySplineProgram::behave() {

    if (_is_executing) {
        //変わり目
        if (_SPframe == _SPNextChangeFrame) {
            GgafDx9GeometryMover* _pActorMover = _pActor_executing->_pMover;
            if (_option == 1) {
                //相対座標ターゲット
                _pActorMover->setSuspendTargetRzRyMoveAngle(_sp->_X_compute[_SPPointIndex] - _X_relative,
                                                            _sp->_Y_compute[_SPPointIndex] - _Y_relative,
                                                            _sp->_Z_compute[_SPPointIndex] - _Z_relative);
            } else {
                //絶対座標ターゲット
                _pActorMover->setSuspendTargetRzRyMoveAngle(_sp->_X_compute[_SPPointIndex],
                                                            _sp->_Y_compute[_SPPointIndex],
                                                            _sp->_Z_compute[_SPPointIndex]);
            }
            if (_pActorMover->getDifferenceFromRzMoveAngleTo(_pActorMover->_angTargetRzMove, TURN_CLOSE_TO) > 0) {
                _pActorMover->setRzMoveAngleVelocity(_angRotMove);
            } else {
                _pActorMover->setRzMoveAngleVelocity(-_angRotMove);
            }
            if (_pActorMover->getDifferenceFromRyMoveAngleTo(_pActorMover->_angTargetRyMove, TURN_CLOSE_TO) > 0) {
                _pActorMover->setRyMoveAngleVelocity(_angRotMove);
            } else {
                _pActorMover->setRyMoveAngleVelocity(-_angRotMove);
            }


            if (_SPPointIndex == 0) {
                //始点へ行く！
                _paSPDistaceTo[0] = GgafDx9Util::getDistance(
                                        (double)_pActor_executing->_X,
                                        (double)_pActor_executing->_Y,
                                        (double)_pActor_executing->_Z,
                                        _sp->_X_compute[0],
                                        _sp->_Y_compute[0],
                                        _sp->_Z_compute[0]
                                     );
                //始点までに必要なフレーム数取得
                _paSPNeedFrameTo[0] =  (DWORD)(1.0*_paSPDistaceTo[0] / _veloMove);
                _pActorMover->setMoveVelocity(_veloMove);
            }

            //次の補完点までに必要なフレーム数を更新
            _SPNextChangeFrame += _paSPNeedFrameTo[_SPPointIndex];
            _SPPointIndex++;
            if ( _SPPointIndex == _sp->_rnum) {
                //終了
                _is_executing = false;
                return;
            }
        }
        _SPframe++;
    }

}
GgafDx9FixedVelocitySplineProgram::~GgafDx9FixedVelocitySplineProgram() {
    DELETEARR_POSSIBLE_NULL(_paSPDistaceTo);
    DELETEARR_POSSIBLE_NULL(_paSPNeedFrameTo);
}
