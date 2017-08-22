#ifndef GGAFDXCORE_GGAFDXMASSPOINTSPRITEEFFECT_H_
#define GGAFDXCORE_GGAFDXMASSPOINTSPRITEEFFECT_H_
#include "GgafDxCommonHeader.h"

#include "jp/ggaf/dxcore/effect/GgafDxMassEffect.h"

namespace GgafDxCore {

/**
 * GgafDxMassPointSpriteEffect�p�G�t�F�N�g�N���X .
 * @version 1.00
 * @since 2009/03/09
 * @author Masatoshi Tsuge
 */
class GgafDxMassPointSpriteEffect : public GgafDxMassEffect {
    friend class GgafDxEffectManager;

public:
    D3DXHANDLE _h_matView;
    D3DXHANDLE _hTexSize;
    D3DXHANDLE _hTextureSplitRowcol;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    GgafDxMassPointSpriteEffect(const char* prm_effect_name);


    virtual void setParamPerFrame() override;

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDxPointSpriteEffectManager�ł���<BR>
     */
    virtual ~GgafDxMassPointSpriteEffect(); //�f�X�g���N�^

};

}
#endif /*GGAFDXCORE_GGAFDXPOINTSPRITEEFFECT_H_*/
