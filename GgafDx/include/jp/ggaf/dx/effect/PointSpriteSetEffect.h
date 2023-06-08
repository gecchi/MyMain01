#ifndef GGAF_DX_POINTSPRITESETEFFECT_H_
#define GGAF_DX_POINTSPRITESETEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "World3DimEffect.h"
#include "interface/IPlaneEffect.h"

namespace GgafDx {

/**
 * PointSpriteSet�p�G�t�F�N�g�N���X .
 * @version 1.00
 * @since 2016/06/09
 * @author Masatoshi Tsuge
 */
class PointSpriteSetEffect : public World3DimEffect, public IPlaneEffect {
    friend class EffectManager;

public:
    D3DXHANDLE _ah_matWorld[32];
    D3DXHANDLE _ah_colMaterialDiffuse[32];
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
    PointSpriteSetEffect(const char* prm_effect_name);

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�PointSpriteSetEffectManager�ł���<BR>
     */
    virtual ~PointSpriteSetEffect();

};

}
#endif /*GGAF_DX_POINTSPRITESETEFFECT_H_*/
