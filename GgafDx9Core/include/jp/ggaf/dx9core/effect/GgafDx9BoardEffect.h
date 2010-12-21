#ifndef GGAFDX9BOARDEFFECT_H_
#define GGAFDX9BOARDEFFECT_H_
namespace GgafDx9Core {

/**
 * GgafDx9Board�p�G�t�F�N�g�N���X.
 * @version 1.00
 * @since 2009/03/10
 * @author Masatoshi Tsuge
 */
class GgafDx9BoardEffect : public GgafDx9Effect {
    friend class GgafDx9EffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    //D3DXHANDLE _h_matWorld;
    D3DXHANDLE _hOffsetU;
    D3DXHANDLE _hOffsetV;
    D3DXHANDLE _hTransformedX;
    D3DXHANDLE _hTransformedY;
    D3DXHANDLE _hSx;
    D3DXHANDLE _hSy;
    D3DXHANDLE _hAlpha;
    D3DXHANDLE _hDepthZ;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    GgafDx9BoardEffect(char* prm_effect_name);


    virtual void setParamPerFrame() override {};

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDx9BoardEffectManager�ł���<BR>
     */
    virtual ~GgafDx9BoardEffect(); //�f�X�g���N�^

};

}
#endif /*GGAFDX9BOARDEFFECT_H_*/
