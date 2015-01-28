#ifndef GGAFDXCORE_GGAFDXTEXTUREBLINKER_H_
#define GGAFDXCORE_GGAFDXTEXTUREBLINKER_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/GgafValueEnveloper.hpp"

namespace GgafDxCore {

/**
 * 特定カラー点滅支援クラス.
 * GgafDxModel のメンバの _power_blink <BR>
 * を、簡単に操作するために設計した。<BR>
 * 最終的にピクセルシェーダーで色(float4)に乗ずる値となる。
 * 色強度 1.0 は色強度無し、
 * 色強度 2.0 は色強度２倍。明るくなる。
 * 色強度 0.5 は色強度1/２倍。暗くなる。
 * @version 1.00
 * @since 2009/05/22
 * @author Masatoshi Tsuge
 */
class GgafDxTextureBlinker : public GgafCore::GgafValueEnveloper<float, 1 > {

public:
    /** 対象アクター */
    GgafDxModel* const _pModel;

public:
    /**
     * コンストラクタ<BR>
     * @param   prm_pModel  適用対象のModel
     */
    GgafDxTextureBlinker(GgafDxModel* prm_pModel);

    void reset() override;

    float getValue(int idx) override;

    void setValue(int idx, float value) override;

    virtual ~GgafDxTextureBlinker();
};

}
#endif /*GGAFDXCORE_GGAFDXTEXTUREBLINKER_H_*/

