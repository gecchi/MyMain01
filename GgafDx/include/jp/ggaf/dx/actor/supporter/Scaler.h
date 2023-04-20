#ifndef GGAF_DX_SCALER_H_
#define GGAF_DX_SCALER_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/ValueTransitioner.hpp"

namespace GgafDx {

/**
 * 拡大縮小支援クラス.
 * GeometricActor のメンバの<BR>
 * _sx, _sy, _sz  ・・・ アクターのスケール<BR>
 * を、簡単に操作するために設計した。<BR>
 * 拡大縮小1.0倍（スケール無し）は、本クラスでのスケール値1000に相当する。
 * [日本語]     → [本クラスのスケール値]
 * 等倍         → 1000
 * 2.5倍拡大    → 2500
 * 半分の大きさ → 500
 * 縮小率80%    → 800
 * 本クラスでは、スケールとスケーリングという単語を次の意味で使用している箇所がある。
 * スケール・・・現在（のフレーム）の拡大縮小状態、スケール値
 * スケーリング・・・フレーム間の拡大縮小状態の遷移
 * 2009/05/22 LocoVehicle から分割した。
 * @version 1.00
 * @since 2009/05/22
 * @author Masatoshi Tsuge
 */
class Scaler : public GgafCore::ValueTransitioner<scale, 3 > {

public:
    /** [r]対象アクター */
    GeometricActor* const _pActor;
    /** [r]スケールプロパティへの参照 */
    scale* _apActorScale[3];

public:
    /**
     * コンストラクタ<BR>
     * @param   prm_pActor  適用対象のActor
     */
    explicit Scaler(GeometricActor* prm_pActor);

    void reset() override;

    scale getValue(int idx) override;

    void setValue(int idx, scale value) override;

    virtual ~Scaler();
};

}
#endif /*GGAF_DX_SCALER_H_*/

