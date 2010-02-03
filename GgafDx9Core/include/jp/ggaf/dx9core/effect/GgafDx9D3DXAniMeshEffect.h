#ifndef GGAFDX9D3DXANIMESHEFFECT_H_
#define GGAFDX9D3DXANIMESHEFFECT_H_
namespace GgafDx9Core {

/**
 * GgafDx9Mesh�p�G�t�F�N�g�N���X.
 * @version 1.00
 * @since 2009/03/09
 * @author Masatoshi Tsuge
 */
class GgafDx9D3DXAniMeshEffect : public GgafDx9Effect {
    friend class GgafDx9EffectManager;

public:
    D3DXHANDLE _hPowerBlink;
    D3DXHANDLE _hBlinkThreshold;
    D3DXHANDLE _hMatView;
    D3DXHANDLE _hMatWorld;
    D3DXHANDLE _hMaterialDiffuse;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    GgafDx9D3DXAniMeshEffect(char* prm_effect_name);


    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDx9D3DXAniMeshEffectManager�ł���<BR>
     */
    virtual ~GgafDx9D3DXAniMeshEffect(); //�f�X�g���N�^

};

}
#endif /*GGAFDX9D3DXANIMESHEFFECT_H_*/
