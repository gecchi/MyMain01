#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

FixedVelocitySplineManufacture::FixedVelocitySplineManufacture(const char* prm_source_file, ang_velo prm_ang_veloRzRyMv) :
        SplineManufacture(prm_source_file) {
    _ang_veloRzRyMv = prm_ang_veloRzRyMv;

    _veloMvUnit = LEN_UNIT; //速度1000とした場合の、各区間のフレーム数を求める
    _paDistace_to = NEW coord[_sp->_rnum];
    _paFrame_need_at = NEW float[_sp->_rnum];
}

FixedVelocitySplineManufacture::FixedVelocitySplineManufacture(SplineSource* prm_pSplSrc, ang_velo prm_ang_veloRzRyMv) :
        SplineManufacture(prm_pSplSrc) {
    _ang_veloRzRyMv = prm_ang_veloRzRyMv;
    _veloMvUnit = LEN_UNIT; //速度1000とした場合の、各区間のフレーム数を求める
    _paDistace_to = NEW coord[_sp->_rnum];
    _paFrame_need_at = NEW float[_sp->_rnum];
}

void FixedVelocitySplineManufacture::calculate() {
    //次の２つのテーブルを再計算し更新します。
    // _paDistace_to[] : 現在の補完点から、次の補完点までの距離
    // _paFrame_need_at[] : 始点から補完点到達に必要なフレーム数の配列

    //各点の時点の、距離と必要なフレーム数を予め全部求めておく
    // 基点[2][3] = { {1000,2000,3000}, {2000,1000,0}, {3900, 0, 1000} }
    // point_num = 3          //基点の数
    // accuracy = 0.25(=1/4)  //補完点精度
    //
    // の場合、下図のようになります。
    //
    // X:基点
    // o:基点間の補完点（スプライン曲線通過点）
    // X--o: 移動予定の座標線
    // _paDistace_to[] : 現在の補完点から、次の補完点までの距離
    // _paFrame_need_at[] : 始点から補完点到達に必要なフレーム数の配列
    //
    // sp._rnum は合計の点の数を返す。したがって sp._rnum = 9 になる。
    // prm_accuracy が綺麗な分数にならない場合、基点上に補完点が繰るかとか、全然わからないので、sp._rnumを必ず使用せよ
    // 下図は綺麗に重なった場合の図である。
    //
    //                           ＜速さは  _veloMvUnit = 1000＞
    //
    //               _paFrame_need_at[1] 必要なフレーム数
    //                     ||              _paFrame_need_at[5]
    //                   <--->                      ||                 _paFrame_need_at[8]
    //                   <----------------------------->                      ||
    //                   <------------------------------------------------------->
    //
    //              _paDistace_to[1]      _paDistace_to[5]         _paDistace_to[8]
    //                    ||                     ||                         ||
    //                   <--->                <------->                  <------->
    //                  X----o----o----o-----X--------o---------o--------o-------X
    //                  ^                    ^        ^                          ^
    //                  |                    |        |                          |
    //            (sp._X_compute[0],         | (sp._X_compute[5],        sp._X_compute[8]
    //             sp._Y_compute[0],         |  sp._Y_compute[5],        sp._Y_compute[8]
    //             sp._Z_compute[0])         |  sp._Z_compute[5])        sp._Z_compute[8]
    //                  |                    |                                   |
    //            (基点[0][0],            (基点[1][0],                      (基点[2][0],
    //             基点[0][1],             基点[1][1],                       基点[2][1],
    //             基点[0][2])             基点[1][2])                       基点[2][2])
    //              = (1000,2000,3000)    = (2000,1000,0)                   = (3900, 0, 1000)
    //
    //                 <--------------------------------------------------------->
    //                         ずっと veloMoveUnit の速度で移動とした場合を計算
    //

    coord x_from, y_from, z_from;
    coord x_to, y_to, z_to;

    x_to = _sp->_X_compute[0]*_rate_X;
    y_to = _sp->_Y_compute[0]*_rate_Y;
    z_to = _sp->_Z_compute[0]*_rate_Z;

    _paFrame_need_at[0] = 0;

    for (int t = 1; t < _sp->_rnum; t ++) {
        x_from = x_to;
        y_from = y_to;
        z_from = z_to;
        x_to = _sp->_X_compute[t]*_rate_X;
        y_to = _sp->_Y_compute[t]*_rate_Y;
        z_to = _sp->_Z_compute[t]*_rate_Z;
        _paDistace_to[t] = GgafDx9Util::getDistance(
                                    x_from,
                                    y_from,
                                    z_from,
                                    x_to,
                                    y_to,
                                    z_to
                                 );

        //距離 paDistaceTo[t] を、速度 _veloMvUnit(=1000) で移動するのに必要なフレーム数を求める。
        //時間＝距離÷速さ
        _paFrame_need_at[t] = _paFrame_need_at[t-1] + (float)(1.0*_paDistace_to[t] / _veloMvUnit);
    }
}

SplineSequence* FixedVelocitySplineManufacture::createSplineSequence(GgafDx9Core::GgafDx9KurokoA* prm_pKurokoA) {
    return NEW FixedVelocitySplineSequence(this, prm_pKurokoA);
}

FixedVelocitySplineManufacture::~FixedVelocitySplineManufacture() {
    DELETEARR_POSSIBLE_NULL(_paDistace_to);
    DELETEARR_POSSIBLE_NULL(_paFrame_need_at);
}
