#ifndef GGAFDXPOINTSPRITEEFFECT_H_
#define GGAFDXPOINTSPRITEEFFECT_H_
namespace GgafDxCore {

/**
 * GgafDxPointSprite�p�G�t�F�N�g�N���X .
 * @version 1.00
 * @since 2009/03/09
 * @author Masatoshi Tsuge
 */
class GgafDxPointSpriteEffect : public GgafDxEffect {
    friend class GgafDxEffectManager;

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
    GgafDxPointSpriteEffect(char* prm_effect_name);


    virtual void setParamPerFrame() override;

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDxPointSpriteEffectManager�ł���<BR>
     */
    virtual ~GgafDxPointSpriteEffect(); //�f�X�g���N�^

};

}
#endif /*GGAFDXPOINTSPRITEEFFECT_H_*/