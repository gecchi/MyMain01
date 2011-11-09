#ifndef GGAFDXBOARDSETEFFECT_H_
#define GGAFDXBOARDSETEFFECT_H_
namespace GgafDxCore {

/**
 * GgafDxBoardSet�p���f���N���X.
 * @version 1.00
 * @since 2009/07/21
 * @author Masatoshi Tsuge
 */
class GgafDxBoardSetEffect : public GgafDxEffect {
    friend class GgafDxEffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _ahOffsetU[28];
    D3DXHANDLE _ahOffsetV[28];
    D3DXHANDLE _ahTransformedX[28];
    D3DXHANDLE _ahTransformedY[28];
    D3DXHANDLE _ahAlpha[28];
    D3DXHANDLE _ahDepthZ[28];

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    GgafDxBoardSetEffect(char* prm_effect_name);


    virtual void setParamPerFrame() override {};

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDxEffectManager�ł���<BR>
     */
    virtual ~GgafDxBoardSetEffect(); //�f�X�g���N�^

};

}
#endif /*GGAFDXBOARDSETEFFECT_H_*/