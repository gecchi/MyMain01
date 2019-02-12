#ifndef GGAF_DX_MASSEFFECT_H_
#define GGAF_DX_MASSEFFECT_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/effect/Effect.h"

namespace GgafDx {

/**
 * Mass�p�G�t�F�N�g�N���X .
 * @version 1.00
 * @since 2016/02/09
 * @author Masatoshi Tsuge
 */
class MassEffect : public Effect {
    friend class EffectManager;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    MassEffect(const char* prm_effect_name);


    /**
     * �f�X�g���N�^<BR>
     * delete����̂�MassEffectManager�ł���<BR>
     */
    virtual ~MassEffect(); //�f�X�g���N�^

};

}
#endif /*GGAF_DX_MASSEFFECT_H_*/
