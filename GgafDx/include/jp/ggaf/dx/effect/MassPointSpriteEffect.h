#ifndef GGAF_DX_MASSPOINTSPRITEEFFECT_H_
#define GGAF_DX_MASSPOINTSPRITEEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"

#include "jp/ggaf/dx/effect/World3DimEffect.h"

namespace GgafDx {

/**
 * MassPointSpriteEffect�p�G�t�F�N�g�N���X .
 * @version 1.00
 * @since 2009/03/09
 * @author Masatoshi Tsuge
 */
class MassPointSpriteEffect : public World3DimEffect {
    friend class EffectManager;

public:
    D3DXHANDLE _hTexSize;
    D3DXHANDLE _hTextureSplitRowcol;
    D3DXHANDLE _hInvTextureSplitRowcol;
public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    MassPointSpriteEffect(const char* prm_effect_name);

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�PointSpriteEffectManager�ł���<BR>
     */
    virtual ~MassPointSpriteEffect();

};

}
#endif /*GGAF_DX_POINTSPRITEEFFECT_H_*/
