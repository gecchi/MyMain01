#ifndef GGAFDX9POINTSPRITEEFFECT_H_
#define GGAFDX9POINTSPRITEEFFECT_H_
namespace GgafDx9Core {

/**
 * GgafDx9PointSprite�p�G�t�F�N�g�N���X .
 * @version 1.00
 * @since 2009/03/09
 * @author Masatoshi Tsuge
 */
class GgafDx9PointSpriteEffect : public GgafDx9Effect {
    friend class GgafDx9EffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_matView;
    D3DXHANDLE _h_matWorld;
    D3DXHANDLE _hOffsetU;
    D3DXHANDLE _hOffsetV;
    D3DXHANDLE _hAlpha;
    D3DXHANDLE _h_dist_VpFrontPlane;
    D3DXHANDLE _hTexSize;
    D3DXHANDLE _hTextureSplitRowcol;
    D3DXHANDLE _hUvFlipPtnNo;
public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    GgafDx9PointSpriteEffect(char* prm_effect_name);


    virtual void setParamPerFrame() override;

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDx9PointSpriteEffectManager�ł���<BR>
     */
    virtual ~GgafDx9PointSpriteEffect(); //�f�X�g���N�^

};

}
#endif /*GGAFDX9POINTSPRITEEFFECT_H_*/
