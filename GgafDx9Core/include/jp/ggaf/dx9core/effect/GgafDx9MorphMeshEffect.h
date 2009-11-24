#ifndef GGAFDX9MORPHMESHEFFECT_H_
#define GGAFDX9MORPHMESHEFFECT_H_
namespace GgafDx9Core {

/**
 * GgafDx9MorphMesh�p�G�t�F�N�g�N���X.
 * @version 1.00
 * @since 2009/05/08
 * @author Masatoshi Tsuge
 */
class GgafDx9MorphMeshEffect : public GgafDx9Effect {
    friend class GgafDx9EffectManager;

public:
    D3DXHANDLE _hMorphTargetnum;
    D3DXHANDLE _hWeight[10];
    D3DXHANDLE _hMatView;
    D3DXHANDLE _hMatWorld;
    D3DXHANDLE _hMaterialDiffuse;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    GgafDx9MorphMeshEffect(char* prm_effect_name);


    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDx9MorphMeshEffectManager�ł���<BR>
     */
    virtual ~GgafDx9MorphMeshEffect(); //�f�X�g���N�^

};

}
#endif /*GGAFDX9MORPHMESHEFFECT_H_*/
