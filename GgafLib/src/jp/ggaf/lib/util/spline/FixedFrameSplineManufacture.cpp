#include "stdafx.h"
#include "jp/ggaf/lib/util/spline/FixedFrameSplineManufacture.h"

#include "jp/ggaf/lib/util/spline/SplineLine.h"
#include "jp/ggaf/lib/util/spline/FixedFrameSplineKurokoLeader.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

FixedFrameSplineManufacture::FixedFrameSplineManufacture(const char* prm_source_file,
                                                         frame prm_spent_frame,
                                                         angvelo prm_angveloRzRyMv,
                                                         int prm_turn_way,
                                                         bool prm_turn_optimaize) :
        SplineManufacture(prm_source_file) {
    _spent_frame = prm_spent_frame;
    _angveloRzRyMv = prm_angveloRzRyMv;
    _turn_way = prm_turn_way;
    _turn_optimize = prm_turn_optimaize;

    //１区間の使用可能フレーム
    _fFrame_of_segment = 1.0*_spent_frame / (_sp->_rnum-1);
    if (_fFrame_of_segment < 1.0f) {
        _TRACE_("＜警告＞FixedFrameSplineManufacture ["<<prm_source_file<<"] _fFrame_of_segment="<<_fFrame_of_segment<<" < 1.0f です。"<<
                "補完点数("<<(_sp->_rnum)<<")よりも、始点～終了点フレーム数("<<_spent_frame<<")が小さいので、補完点の飛びをなくすため、強制的に_fFrame_of_segmentは1.0に上書き。"<<
                "従って移動には"<<(_sp->_rnum)<<"フレームかかります。ご了承下さい。");
        _fFrame_of_segment = 1.0f;
    }
    _paSPMvVeloTo = NEW velo[_sp->_rnum];
}

FixedFrameSplineManufacture::FixedFrameSplineManufacture(SplineSource* prm_pSplSrc,
                                                         frame prm_spent_frame,
                                                         angvelo prm_angveloRzRyMv,
                                                         int prm_turn_way,
                                                         bool prm_turn_optimaize) :
      SplineManufacture(prm_pSplSrc) {
    _spent_frame = prm_spent_frame;
    _angveloRzRyMv = prm_angveloRzRyMv;
    _turn_way = prm_turn_way;
    _turn_optimize = prm_turn_optimaize;

    //１区間の使用可能フレーム
    _fFrame_of_segment = 1.0*_spent_frame / (_sp->_rnum-1);
    if (_fFrame_of_segment < 1.0f) {
        _TRACE_("＜警告＞FixedFrameSplineManufacture  _fFrame_of_segment="<<_fFrame_of_segment<<" < 1.0f です。"<<
                "補完点数("<<(_sp->_rnum)<<")よりも、始点～終了点フレーム数("<<_spent_frame<<")が小さいので、補完点の飛びをなくすため、強制的に_fFrame_of_segmentは1.0に上書き。"<<
                "従って移動には"<<(_sp->_rnum)<<"フレームかかります。ご了承下さい。");
        _fFrame_of_segment = 1.0f;
    }
    _paSPMvVeloTo = NEW velo[_sp->_rnum];
}


void FixedFrameSplineManufacture::calculate() {
    //次の２つのテーブルを再計算し更新します。
    // _paDistance_to[] : 次の補完点までの距離
    // _paSPMvVeloTo[] : 次の補完点到達に必要な速度

    //各点の時点の、距離と速度を予め全部求めておく
    // 制御点[2][3] = { {1000,2000,3000}, {2000,1000,0}, {3900, 0, 1000} }
    // point_num = 3          //制御点の数
    // accuracy = 0.25(=1/4)  //補完点精度
    // spent_frame = 120      //費やすフレーム
    // の場合、下図のようになります。
    //
    // X:制御点
    // o:制御点間の補完点（スプライン曲線通過点）
    // X--o: 移動予定の座標線
    // _paDistance_to[] : 次の補完点までの距離
    // _paSPMvVeloTo[] : 次の補完点到達に必要な速度
    //
    // sp._rnum は合計の点の数を返す。したがって sp._rnum = 9 になる。
    // accuracy が綺麗な分数にならない場合、制御点上に補完点が繰るかとか、面倒なので、sp._rnumを必ず使用せよ
    // 下図は綺麗に重なった場合の図である。
    //
    //           v = _paSPMvVeloTo[1]                           v = _paSPMvVeloTo[8]
    //               _paDistance_to[1]     _paDistance_to[5]          _paDistance_to[8]
    //                    ||                     ||                         ||
    //                   <-->                 <------>                    <----->
    //                  X----o----o----o-----X--------o---------o--------o-------X
    //                  ^                    ^        ^                          ^
    //                  |                    |        |                          |
    //            (sp._X_compute[0],         | (sp._X_compute[5],        sp._X_compute[8]
    //             sp._Y_compute[0],         |  sp._Y_compute[5],        sp._Y_compute[8]
    //             sp._Z_compute[0])         |  sp._Z_compute[5])        sp._Z_compute[8]
    //                  |                    |                                   |
    //              (制御点[0][0],       (制御点[1][0],                       (制御点[2][0],
    //               制御点[0][1],        制御点[1][1],                        制御点[2][1],
    //               制御点[0][2])        制御点[1][2])                        制御点[2][2])
    //            = (1000,2000,3000)    = (2000,1000,0)                      = (3900, 0, 1000)
    //
    //                 <--------------------------------------------------------->
    //                                 120Frame費やして移動(=prm_spent_frame)
    //                  <-->
    //                  _spent_frame = １区間は 120/8 Frame = prm_spent_frame / (sp._rnum-1);
    SplineManufacture::calculate();
    for (int t = 1; t < _sp->_rnum; t ++) {
        //距離 paDistanceTo[t] を、時間frm_segment で移動するために必要な速度を求める。
        //速さ＝距離÷時間
        _paSPMvVeloTo[t] = (velo)(_paDistance_to[t] / _fFrame_of_segment);
    }
    _paSPMvVeloTo[0] = 0; //始点までの速度など分からない。
    _paDistance_to[0] = 0;   //始点までの距離など分からない。
}

SplineKurokoLeader* FixedFrameSplineManufacture::createKurokoLeader(GgafDxCore::GgafDxKurokoA* prm_pKurokoA) {
    return NEW FixedFrameSplineKurokoLeader(this, prm_pKurokoA);
}

FixedFrameSplineManufacture::~FixedFrameSplineManufacture() {
    //イニシャライズされる前に解放されるかもしれない
    GGAF_DELETEARR_NULLABLE(_paDistance_to);
    //イニシャライズされる前に解放されるかもしれない
    GGAF_DELETEARR_NULLABLE(_paSPMvVeloTo);
}
