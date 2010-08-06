#ifndef GGAFDX9MESHEFFECT_H_
#define GGAFDX9MESHEFFECT_H_
namespace GgafDx9Core {

/**
 * GgafDx9Mesh�p�G�t�F�N�g�N���X.
 * @version 1.00
 * @since 2009/03/09
 * @author Masatoshi Tsuge
 */
class GgafDx9MeshEffect : public GgafDx9Effect {
    friend class GgafDx9EffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_matView;
    D3DXHANDLE _h_matWorld;
    D3DXHANDLE _h_colMaterialDiffuse;
    D3DXHANDLE _h_offset_u;
    D3DXHANDLE _h_offset_v;

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
