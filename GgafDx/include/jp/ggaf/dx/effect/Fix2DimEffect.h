#ifndef GGAF_DX_FIX2DIMEFFECT_H_
#define GGAF_DX_FIX2DIMEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/effect/Effect.h"

namespace GgafDx {

/**
 * Fix2D�p�G�t�F�N�g�N���X .
 * @version 1.00
 * @since 2023/06/07
 * @author Masatoshi Tsuge
 */
class Fix2DimEffect : public Effect {
    friend class EffectManager;

public:
    /**
     * �R���X�g���N�^<BR>
     * @return
     */
    Fix2DimEffect(const char* prm_effect_name);

    virtual void setParamPerFrame() override {};

    /**
     * �f�X�g���N�^<BR>
     */
    virtual ~Fix2DimEffect();

};

}
#endif /*GGAF_DX_FIX2DIMEFFECT_H_*/
