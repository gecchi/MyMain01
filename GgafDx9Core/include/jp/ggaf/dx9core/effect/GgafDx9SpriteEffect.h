#ifndef GGAFDX9SPRITEEFFECT_H_
#define GGAFDX9SPRITEEFFECT_H_
namespace GgafDx9Core {

/**
 * GgafDx9Sprite�p���f���N���X.
 */
class GgafDx9SpriteEffect : public GgafDx9Effect {
    friend class GgafDx9EffectManager;

public:
    D3DXHANDLE _hMatWorld;
    D3DXHANDLE _hOffsetU;
    D3DXHANDLE _hOffsetV;
    D3DXHANDLE _hAlpha;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    GgafDx9SpriteEffect(char* prm_effect_name);


    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDx9SpriteEffectManager�ł���<BR>
     */
    virtual ~GgafDx9SpriteEffect(); //�f�X�g���N�^

};

}
#endif /*GGAFDX9SPRITEEFFECT_H_*/
