#ifndef GGAFDX9SPRITEACTORD_H_
#define GGAFDX9SPRITEACTORD_H_
namespace GgafDx9Core {

/**
 * �X�v���C�g�A�N�^�[.
 * GgafDx9GeometricActor ���p�����A�|���S���Ƀe�N�X�`����\��t����<BR>
 * �[���X�v���C�g�@�\��ǉ������A�N�^�[�ł��B<BR>
 * ������|��<BR>
 * @version 1.00
 * @since 2007/11/14
 * @author Masatoshi Tsuge
 */
class GgafDx9SpriteActor : public GgafDx9DrawableActor {

public:
    /** ���f���I�u�W�F�N�g�ւ̃|�C���^ */
    GgafDx9SpriteModel* _pSpriteModel;
    /** �G�t�F�N�g */
    GgafDx9SpriteEffect* _pSpriteEffect;
    /** UV�t���b�p�[(�p���p���A�j��) */
    GgafDx9UvFliper* _pUvFliper;

    GgafDx9SpriteActor(const char* prm_name,
                       const char* prm_model_id,
                       const char* prm_effect_id,
                       const char* prm_technique,
                       GgafDx9Checker* prm_pChecker );

    virtual void processDraw() override;

    virtual ~GgafDx9SpriteActor();

    /**
     * ���ݒ�.
     * ���I�[�o�[���C�g��
     * @param prm_fAlpha
     */
    void setAlpha(float prm_fAlpha);

};

}
#endif /*GGAFDX9SPRITEACTORD_H_*/
