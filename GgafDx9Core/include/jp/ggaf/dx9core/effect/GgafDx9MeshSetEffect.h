#ifndef GGAFDX9MESHSETEFFECT_H_
#define GGAFDX9MESHSETEFFECT_H_
namespace GgafDx9Core {

/**
 * GgafDx9Mesh�p���f���N���X.
 */
class GgafDx9MeshSetEffect : public GgafDx9Effect {
    friend class GgafDx9EffectManager;

public:
    D3DXHANDLE _hMatView;
    //D3DXHANDLE _hMatWorld;
    D3DXHANDLE _ahMatWorld[8];
    D3DXHANDLE _hMaterialDiffuse;
    D3DXHANDLE _h_nVertexs;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    GgafDx9MeshSetEffect(char* prm_effect_name);


    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDx9MeshSetEffectManager�ł���<BR>
     */
    virtual ~GgafDx9MeshSetEffect(); //�f�X�g���N�^

};

}
#endif /*GGAFDX9MESHSETEFFECT_H_*/
