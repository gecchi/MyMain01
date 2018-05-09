#ifndef GGAFLIB_SINGLELASEREFFECT_H_
#define GGAFLIB_SINGLELASEREFFECT_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/effect/GgafDxMeshSetEffect.h"

namespace GgafLib {

/**
 * SingleLaser�p�G�t�F�N�g�N���X .
 * @version 1.00
 * @since 2018/04/26
 * @author Masatoshi Tsuge
 */
class SingleLaserEffect : public GgafDxCore::GgafDxMeshSetEffect {
    friend class DefaultEffectManager;

public:

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    SingleLaserEffect(const char* prm_effect_name);

    virtual ~SingleLaserEffect(); //�f�X�g���N�^

};

}
#endif /*GGAFLIB_SINGLELASEREFFECT_H_*/