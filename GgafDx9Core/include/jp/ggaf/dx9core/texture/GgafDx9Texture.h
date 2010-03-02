#ifndef GGAFDX9TEXTURE_H_
#define GGAFDX9TEXTURE_H_
namespace GgafDx9Core {

/**
 * �G�t�F�N�g���N���X.
 * �L����(�A�N�^�[)�̃G�t�F�N�g��ێ�����N���X�ł��B<BR>
 * @version 1.00
 * @since 2009/03/09
 * @author Masatoshi Tsuge
 */
class GgafDx9Texture : public GgafCore::GgafObject {
    friend class GgafDx9TextureManager;

protected:
public:

    /** ���f����`�̎��ʖ��B(50�����܂�) */
    char* _effect_name;
    ID3DXTexture* _pID3DXTexture;
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name ���f����`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    GgafDx9Texture(char* prm_effect_name);

    char* getName() {
        return _effect_name;
    }


    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDx9TextureManager�ł���<BR>
     */
    virtual ~GgafDx9Texture(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9EFFECT_H_*/
