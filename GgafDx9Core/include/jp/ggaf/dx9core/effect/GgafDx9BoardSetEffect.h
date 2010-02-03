#ifndef GGAFDX9BOARDSETEFFECT_H_
#define GGAFDX9BOARDSETEFFECT_H_
namespace GgafDx9Core {

/**
 * GgafDx9BoardSet�p���f���N���X.
 * @version 1.00
 * @since 2009/07/21
 * @author Masatoshi Tsuge
 */
class GgafDx9BoardSetEffect : public GgafDx9Effect {
    friend class GgafDx9EffectManager;

public:
    D3DXHANDLE _hPowerBlink;
    D3DXHANDLE _hBlinkThreshold;
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
    GgafDx9BoardSetEffect(char* prm_effect_name);


    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDx9EffectManager�ł���<BR>
     */
    virtual ~GgafDx9BoardSetEffect(); //�f�X�g���N�^

};

}
#endif /*GGAFDX9BOARDSETEFFECT_H_*/
