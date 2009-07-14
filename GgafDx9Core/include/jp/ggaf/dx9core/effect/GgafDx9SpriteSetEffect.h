#ifndef GGAFDX9SPRITESETEFFECT_H_
#define GGAFDX9SPRITESETEFFECT_H_
namespace GgafDx9Core {

/**
 * GgafDx9SpriteSet�p���f���N���X.
 */
class GgafDx9SpriteSetEffect : public GgafDx9Effect {
    friend class GgafDx9EffectManager;

public:
    D3DXHANDLE _hMatView;
    D3DXHANDLE _ahMatWorld[8];
    D3DXHANDLE _ahOffsetU[8];
    D3DXHANDLE _ahOffsetV[8];
    D3DXHANDLE _ahAlpha[8];

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    GgafDx9SpriteSetEffect(char* prm_effect_name);


    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDx9EffectManager�ł���<BR>
     */
    virtual ~GgafDx9SpriteSetEffect(); //�f�X�g���N�^

};

}
#endif /*GGAFDX9SPRITESETEFFECT_H_*/
