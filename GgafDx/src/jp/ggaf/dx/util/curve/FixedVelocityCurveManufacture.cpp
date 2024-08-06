#include "jp/ggaf/dx/util/curve/FixedVelocityCurveManufacture.h"

#include "jp/ggaf/dx/util/curve/CurveSource.h"
#include "jp/ggaf/dx/util/curve/FixedVelocityCurveLocusVehicleLeader.h"

using namespace GgafDx;

FixedVelocityCurveManufacture::FixedVelocityCurveManufacture(const char* prm_coord_spl_file,
                                                             angvelo prm_angvelo_rzry_mv,
                                                             int prm_turn_way,
                                                             bool prm_turn_optimaize) :
        CurveManufacture(prm_coord_spl_file) {
    _angvelo_rzry_mv = prm_angvelo_rzry_mv;
    _turn_way = prm_turn_way;
    _turn_optimize = prm_turn_optimaize;
    _velo_mvUnit = PX_C(1); //速度 PX_C(1) とした場合の各区間のフレーム数を基本とする
    _paFrame_need_at = NEW float[_pCurve->_rnum];
    _move_method = FixedVelocity;
}

FixedVelocityCurveManufacture::FixedVelocityCurveManufacture(CurveSource* prm_pCurve,
                                                             angvelo prm_angvelo_rzry_mv,
                                                             int prm_turn_way,
                                                             bool prm_turn_optimaize) :
        CurveManufacture(prm_pCurve) {
    _angvelo_rzry_mv = prm_angvelo_rzry_mv;
    _turn_way = prm_turn_way;
    _turn_optimize = prm_turn_optimaize;
    _velo_mvUnit = PX_C(1); //速度 PX_C(1) とした場合の各区間のフレーム数を基本とする
    _paFrame_need_at = NEW float[_pCurve->_rnum];
    _move_method = FixedVelocity;
}

void FixedVelocityCurveManufacture::calculate() {
    //次の２つのテーブルを再計算し更新します。
    // _paDistance_to[] : 現在の補完点から、次の補完点までの距離
    // _paFrame_need_at[] : 始点から補完点到達に必要なフレーム数の配列

    //各点の時点の、距離と必要なフレーム数を予め全部求めておく
    // 制御点[2][3] = { {1000,2000,3000}, {2000,1000,0}, {3900, 0, 1000} }
    // point_num = 3          //制御点の数
    // accuracy = 0.25(=1/4)  //補完点精度
    //
    // の場合、下図のようになります。
    //
    // X:制御点
    // o:制御点間の補完点（スプライン曲線通過点）
    // X--o: 移動予定の座標線
    // _paDistance_to[] : 現在の補完点から、次の補完点までの距離
    // _paFrame_need_at[] : 始点から補完点到達に必要なフレーム数の配列
    //
    // sp._rnum は合計の点の数を返す。したがって sp._rnum = 9 になる。
    // prm_accuracy が綺麗な分数にならない場合、制御点上に補完点が繰るかとか、全然わからないので、sp._rnumを必ず使用せよ
    // 下図は綺麗に重なった場合の図である。
    //
    //                           ＜速さは  _velo_mvUnit = 1000＞
    //
    //               _paFrame_need_at[1] 必要なフレーム数
    //                     ||              _paFrame_need_at[5]
    //                   <--->                      ||                 _paFrame_need_at[8]
    //                   <----------------------------->                      ||
    //                   <------------------------------------------------------->
    //
    //              _paDistance_to[1]      _paDistance_to[5]         _paDistance_to[8]
    //                    ||                     ||                         ||
    //                   <--->                <------->                  <------->
    //                  X----o----o----o-----X--------o---------o--------o-------X
    //                  ^                    ^        ^                          ^
    //                  |                    |        |                          |
    //            (sp._x_compute[0],         | (sp._x_compute[5],        sp._x_compute[8]
    //             sp._y_compute[0],         |  sp._y_compute[5],        sp._y_compute[8]
    //             sp._z_compute[0])         |  sp._z_compute[5])        sp._z_compute[8]
    //                  |                    |                                   |
    //            (制御点[0][0],           (制御点[1][0],                   (制御点[2][0],
    //             制御点[0][1],            制御点[1][1],                    制御点[2][1],
    //             制御点[0][2])            制御点[1][2])                    制御点[2][2])
    //              = (1000,2000,3000)    = (2000,1000,0)                   = (3900, 0, 1000)
    //
    //                 <--------------------------------------------------------->
    //                         ずっと veloMoveUnit の速度で移動とした場合を計算
    //
    CurveManufacture::calculate();
    _paFrame_need_at[0] = 0; //始点に行くまでに必要なフレーム数は不明
    int rnum = _pCurve->_rnum;
    for (int t = 1; t < rnum; t ++) {
        //距離 paDistanceTo[t] を、速度 _velo_mvUnit(=1000) で移動するのに必要なフレーム数を求める。
        //時間＝距離÷速さ
        _paFrame_need_at[t] = _paFrame_need_at[t-1] + (float)(1.0*_paDistance_to[t] / _velo_mvUnit);
    }
}

VehicleLeader* FixedVelocityCurveManufacture::createLocusVehicleLeader(GgafDx::LocusVehicle* prm_pLocusVehicle) {
    return NEW FixedVelocityCurveLocusVehicleLeader(this, prm_pLocusVehicle);
}

FixedVelocityCurveManufacture::~FixedVelocityCurveManufacture() {
    GGAF_DELETEARR_NULLABLE(_paDistance_to);
    GGAF_DELETEARR_NULLABLE(_paFrame_need_at);
}
