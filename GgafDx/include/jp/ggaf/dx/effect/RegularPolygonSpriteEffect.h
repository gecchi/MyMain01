#ifndef GGAFDXREGULARPOLYGONSPRITEEFFECT_H_
#define GGAFDXREGULARPOLYGONSPRITEEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "World3DimEffect.h"
#include "interface/IPlaneEffect.h"

namespace GgafDx {

/**
 * RegularPolygonSprite�p�G�t�F�N�g�N���X .
 * @version 1.00
 * @since 2018/10/18
 * @author Masatoshi Tsuge
 */
class RegularPolygonSpriteEffect : public World3DimEffect, public IPlaneEffect {
    friend class EffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_matWorld;
    D3DXHANDLE _h_colMaterialDiffuse;
    D3DXHANDLE _h_offset_u;
    D3DXHANDLE _h_offset_v;
    D3DXHANDLE _h_sin_rz;
    D3DXHANDLE _h_cos_rz;

    D3DXHANDLE _h_u_center;
    D3DXHANDLE _h_v_center;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    RegularPolygonSpriteEffect(const char* prm_effect_name);

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�RegularPolygonSpriteEffectManager�ł���<BR>
     */
    virtual ~RegularPolygonSpriteEffect();

};

}
#endif /*GGAFDXREGULARPOLYGONSPRITEEFFECT_H_*/
