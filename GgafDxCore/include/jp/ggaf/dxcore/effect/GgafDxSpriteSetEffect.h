#ifndef GGAFDXSPRITESETEFFECT_H_
#define GGAFDXSPRITESETEFFECT_H_
namespace GgafDxCore {

/**
 * GgafDxSpriteSet�p�G�t�F�N�g�N���X .
 * @version 1.00
 * @since 2009/07/14
 * @author Masatoshi Tsuge
 */
class GgafDxSpriteSetEffect : public GgafDxEffect {
    friend class GgafDxEffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_matView;
    D3DXHANDLE _ah_matWorld[18];
    D3DXHANDLE _ahOffsetU[18];
    D3DXHANDLE _ahOffsetV[18];
    D3DXHANDLE _ahAlpha[18];

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    GgafDxSpriteSetEffect(char* prm_effect_name);

    virtual void setParamPerFrame() override;

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDxEffectManager�ł���<BR>
     */
    virtual ~GgafDxSpriteSetEffect(); //�f�X�g���N�^

};

}
#endif /*GGAFDXSPRITESETEFFECT_H_*/