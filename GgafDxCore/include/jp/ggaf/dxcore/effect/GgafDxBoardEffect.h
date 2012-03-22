#ifndef GGAFDXBOARDEFFECT_H_
#define GGAFDXBOARDEFFECT_H_
namespace GgafDxCore {

/**
 * GgafDxBoard�p�G�t�F�N�g�N���X.
 * @version 1.00
 * @since 2009/03/10
 * @author Masatoshi Tsuge
 */
class GgafDxBoardEffect : public GgafDxEffect {
    friend class GgafDxEffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    //D3DXHANDLE _h_matWorld;
    D3DXHANDLE _h_offset_u;
    D3DXHANDLE _h_offset_v;
    D3DXHANDLE _hTransformedX;
    D3DXHANDLE _hTransformedY;
    D3DXHANDLE _hSx;
    D3DXHANDLE _hSy;
    D3DXHANDLE _h_alpha;
    D3DXHANDLE _hDepthZ;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    GgafDxBoardEffect(char* prm_effect_name);


    virtual void setParamPerFrame() override {};

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDxBoardEffectManager�ł���<BR>
     */
    virtual ~GgafDxBoardEffect(); //�f�X�g���N�^

};

}
#endif /*GGAFDXBOARDEFFECT_H_*/
