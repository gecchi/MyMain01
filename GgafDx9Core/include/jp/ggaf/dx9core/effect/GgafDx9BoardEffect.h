#ifndef GGAFDX9BOARDEFFECT_H_
#define GGAFDX9BOARDEFFECT_H_
namespace GgafDx9Core {

/**
 * GgafDx9Board�p���f���N���X.
 */
class GgafDx9BoardEffect : public GgafDx9Effect {
    friend class GgafDx9EffectManager;

public:
    D3DXHANDLE _hMatWorld;
    D3DXHANDLE _hOffsetU;
    D3DXHANDLE _hOffsetV;
    D3DXHANDLE _hTransformedX;
    D3DXHANDLE _hTransformedY;
    D3DXHANDLE _hAlpha;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    GgafDx9BoardEffect(char* prm_effect_name);


    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDx9BoardEffectManager�ł���<BR>
     */
    virtual ~GgafDx9BoardEffect(); //�f�X�g���N�^

};

}
#endif /*GGAFDX9BOARDEFFECT_H_*/
