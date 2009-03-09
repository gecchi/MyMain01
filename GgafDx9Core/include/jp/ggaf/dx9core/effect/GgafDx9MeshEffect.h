#ifndef GGAFDX9MESHEFFECT_H_
#define GGAFDX9MESHEFFECT_H_
namespace GgafDx9Core {

/**
 * GgafDx9Mesh�p���f���N���X.
 */
class GgafDx9MeshEffect : public GgafDx9Effect {
    friend class GgafDx9EffectManager;

public:
    D3DXHANDLE _hMatWorld;
    D3DXHANDLE _hMaterialDiffuse;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    GgafDx9MeshEffect(char* prm_effect_name);


    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDx9MeshEffectManager�ł���<BR>
     */
    virtual ~GgafDx9MeshEffect(); //�f�X�g���N�^

};

}
#endif /*GGAFDX9MESHEFFECT_H_*/
