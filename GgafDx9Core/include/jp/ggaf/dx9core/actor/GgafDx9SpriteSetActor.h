#ifndef GGAFDX9SPRITESETACTOR_H_
#define GGAFDX9SPRITESETACTOR_H_
namespace GgafDx9Core {

/**
 * �X�v���C�g�Z�b�g�A�N�^�[.
 * GgafDx9DrawableActor ���p�����A�|���S���Ƀe�N�X�`����\��t����<BR>
 * �[���X�v���C�g�@�\��ǉ����A���������`��ɍœK�����ꂽ�A�N�^�[�ł��B<BR>
 * @version 1.00
 * @since 2009/07/14
 * @author Masatoshi Tsuge
 */
class GgafDx9SpriteSetActor : public GgafDx9DrawableActor {

public:
    /** �����`��Z�b�g�� */
    int _draw_set_num;

    /** ���f���I�u�W�F�N�g�ւ̃|�C���^ */
    GgafDx9SpriteSetModel* _pSpriteSetModel;

    /** �G�t�F�N�g */
    GgafDx9SpriteSetEffect* _pSpriteSetEffect;

    /** UV�t���b�p�[(�p���p���A�j��) */
    GgafDx9UvFlipper* _pUvFlipper;

    GgafDx9SpriteSetActor(const char* prm_name,
                          const char* prm_model_id,
                          const char* prm_effect_id,
                          const char* prm_technique,
                          GgafDx9Checker* prm_pChecker );

    virtual void processDraw() override;

    virtual ~GgafDx9SpriteSetActor();

    /**
     * ���ݒ�.
     * ���I�[�o�[���C�g��
     * @param prm_fAlpha
     */
    void setAlpha(float prm_fAlpha) override;

};

}
#endif /*GGAFDX9SPRITESETACTOR_H_*/
