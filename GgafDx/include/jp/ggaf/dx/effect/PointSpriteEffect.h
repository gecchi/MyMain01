#ifndef GGAF_DX_POINTSPRITEEFFECT_H_
#define GGAF_DX_POINTSPRITEEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "World3DimEffect.h"
#include "interface/IPlaneEffect.h"

namespace GgafDx {

/**
 * PointSprite�p�G�t�F�N�g�N���X .
 * @version 1.00
 * @since 2009/03/09
 * @author Masatoshi Tsuge
 */
class PointSpriteEffect : public World3DimEffect, public IPlaneEffect {
    friend class EffectManager;

public:
    D3DXHANDLE _h_matWorld;
    D3DXHANDLE _h_colMaterialDiffuse;
    D3DXHANDLE _hTexSize;
    D3DXHANDLE _hTextureSplitRowcol;
    D3DXHANDLE _hInvTextureSplitRowcol;
    D3DXHANDLE _hUvFlipPtnNo;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    PointSpriteEffect(const char* prm_effect_name);

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�PointSpriteEffectManager�ł���<BR>
     */
    virtual ~PointSpriteEffect();

};

}
#endif /*GGAF_DX_POINTSPRITEEFFECT_H_*/
