#ifndef GGAF_DX_TEXTUREBLINKER_H_
#define GGAF_DX_TEXTUREBLINKER_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/TransitionValueSet.hpp"

namespace GgafDx {

/**
 * 特定カラー点滅支援クラス.
 * Model のメンバの _power_blink <BR>
 * を、簡単に操作するために設計した。<BR>
 * 最終的にピクセルシェーダーで色(float4)に乗ずる値となる。
 * 色強度 1.0 は色強度無し、
 * 色強度 2.0 は色強度２倍。明るくなる。
 * 色強度 0.5 は色強度1/２倍。暗くなる。
 * @version 1.00
 * @since 2009/05/22
 * @author Masatoshi Tsuge
 */
class TextureBlinker : public GgafCore::TransitionValueSet<float, 1 > {

public:
    /** 対象アクター */
    Model* _pModel;

public:
    /**
     * コンストラクタ<BR>
     * @param   prm_pModel  適用対象のModel
     */
    TextureBlinker(Model* prm_pModel);

    void reset() override;

    float getValue(int idx) override;

    void setValue(int idx, float value) override;

    virtual ~TextureBlinker();
};

}
#endif /*GGAF_DX_TEXTUREBLINKER_H_*/

