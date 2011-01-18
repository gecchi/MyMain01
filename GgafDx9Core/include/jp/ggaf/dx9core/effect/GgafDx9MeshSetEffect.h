#ifndef GGAFDX9MESHSETEFFECT_H_
#define GGAFDX9MESHSETEFFECT_H_
namespace GgafDx9Core {

/**
 * GgafDx9MeshSet�p�G�t�F�N�g�N���X .
 * @version 1.00
 * @since 2009/06/15
 * @author Masatoshi Tsuge
 */
class GgafDx9MeshSetEffect : public GgafDx9Effect {
    friend class GgafDx9EffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_matView;
    //D3DXHANDLE _h_matWorld;
    D3DXHANDLE _ah_matWorld[19];
    D3DXHANDLE _ah_materialDiffuse[19];
    D3DXHANDLE _ahOffsetU[19];
    D3DXHANDLE _ahOffsetV[19];

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    GgafDx9MeshSetEffect(char* prm_effect_name);

    virtual void setParamPerFrame() override;

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDx9MeshSetEffectManager�ł���<BR>
     */
    virtual ~GgafDx9MeshSetEffect(); //�f�X�g���N�^

};

}
#endif /*GGAFDX9MESHSETEFFECT_H_*/
