#ifndef GGAF_DX_MASSBOARDEFFECT_H_
#define GGAF_DX_MASSBOARDEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "Fix2DimEffect.h"
#include "interface/IPlaneEffect.h"

namespace GgafDx {

/**
 * MassBoard�p���f���N���X.
 * @version 1.00
 * @since 2015/02/25
 * @author Masatoshi Tsuge
 */
class MassBoardEffect : public Fix2DimEffect, public IPlaneEffect {
    friend class EffectManager;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    MassBoardEffect(const char* prm_effect_name);

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�EffectManager�ł���<BR>
     */
    virtual ~MassBoardEffect();

};

}
#endif /*GGAF_DX_MASSBOARDEFFECT_H_*/
