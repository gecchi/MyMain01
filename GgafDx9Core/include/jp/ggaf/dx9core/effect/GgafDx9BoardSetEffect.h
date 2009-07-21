#ifndef GGAFDX9BOARDSETEFFECT_H_
#define GGAFDX9BOARDSETEFFECT_H_
namespace GgafDx9Core {

/**
 * GgafDx9BoardSet�p���f���N���X.
 */
class GgafDx9BoardSetEffect : public GgafDx9Effect {
    friend class GgafDx9EffectManager;

public:
    D3DXHANDLE _ahOffsetU[8];
    D3DXHANDLE _ahOffsetV[8];
    D3DXHANDLE _ahTransformedX[8];
    D3DXHANDLE _ahTransformedY[8];
    D3DXHANDLE _ahAlpha[8];
    D3DXHANDLE _ahDepthZ[8];

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
