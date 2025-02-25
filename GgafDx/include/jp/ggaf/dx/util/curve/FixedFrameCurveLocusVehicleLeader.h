#ifndef GGAF_DX_FIXEDFRAMECURVELOCUSVEHICLELEADER_H_
#define GGAF_DX_FIXEDFRAMECURVELOCUSVEHICLELEADER_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"

namespace GgafDx {

/**
 * 固定時間（フレーム）スプライン曲線移動の先導者。 .
 * 開始点〜終了点まで、決められた時間で移動します。<BR>
 * 中間の補完点〜次の補完点までを、均等に割った時間で移動します。<BR>
 * 補完点の密度が薄いところは移動速度増。<BR>
 * 補完点の密度が濃いところは移動速度減。<BR>
 * そのように動作するよう、移動車両(GgafDx::LocusVehicle)に指示を出して移動を実現します。<BR>
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class FixedFrameCurveLocusVehicleLeader : public VehicleLeader {

public:
    GgafDx::LocusVehicle* _pLocusVehicle_target;
    /** [r]スプライン情報セット(ldrファイルの情報に相当) */
    FixedFrameCurveManufacture* _pFixedFrameSplManuf;
    /** _leading_framesに加算される補正フレーム */
    frame _hosei_frames;
    /** [r]現在向かっている最中の補完点(基準点も含む)の数 */
    int _point_index;
    /** 前回の_point_index */
    int _prev_point_index;
    /** start()からの経過フレーム数 */
    frame _leading_frames;
public:
    /**
     *
     * @param prm_pManufacture
     * @param prm_pLocusVehicle
     */
    FixedFrameCurveLocusVehicleLeader(CurveManufacture* prm_pManufacture,
                                 GgafDx::LocusVehicle* prm_pLocusVehicle_target);

    virtual void restart() override;

    /**
     * 移動実行メソッド .
     * start() を行った同一フレームに behave() 実行を避けるといったことは不要。<BR>
     * start() を行った最初の behave() は、『現在の座標→ポイント[0]』への処理となります。<BR>
     */
    virtual void behave() override;


    virtual ~FixedFrameCurveLocusVehicleLeader();
};

}
#endif /*GGAF_LIB_FIXEDFRAMECURVELOCUSVEHICLELEADER_H_*/
