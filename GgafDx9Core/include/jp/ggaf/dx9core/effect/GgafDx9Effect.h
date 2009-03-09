#ifndef GGAFDX9EFFECT_H_
#define GGAFDX9EFFECT_H_
namespace GgafDx9Core {

/**
 * ���f�����N���X.
 * �L����(�A�N�^�[)�̌`���F�Ȃǂ�ێ�����N���X�ł��B<BR>
 */
class GgafDx9Effect : public GgafCore::GgafObject {
    friend class GgafDx9EffectManager;

protected:
public:

    /** ���f����`�̎��ʖ��B(50�����܂�) */
    char* _effect_name;
    ID3DXEffect* _pID3DXEffect;
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name ���f����`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    GgafDx9Effect(char* prm_effect_name);
    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDx9EffectManager�ł���<BR>
     */
    virtual ~GgafDx9Effect(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9EFFECT_H_*/
