#ifndef GGAFDXCORE_GGAFDXMASSEFFECT_H_
#define GGAFDXCORE_GGAFDXMASSEFFECT_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/effect/GgafDxEffect.h"

namespace GgafDxCore {

/**
 * GgafDxMass�p�G�t�F�N�g�N���X .
 * @version 1.00
 * @since 2016/02/09
 * @author Masatoshi Tsuge
 */
class GgafDxMassEffect : public GgafDxEffect {
    friend class GgafDxEffectManager;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    GgafDxMassEffect(const char* prm_effect_name);


    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDxMassEffectManager�ł���<BR>
     */
    virtual ~GgafDxMassEffect(); //�f�X�g���N�^

};

}
#endif /*GGAFDXCORE_GGAFDXMASSEFFECT_H_*/
