#ifndef GGAFDXSPRITESETACTOR_H_
#define GGAFDXSPRITESETACTOR_H_
namespace GgafDxCore {

/**
 * �X�v���C�g�Z�b�g�A�N�^�[.
 * GgafDxDrawableActor ���p�����A�|���S���Ƀe�N�X�`����\��t����<BR>
 * �[���X�v���C�g�@�\��ǉ����A���������`��ɍœK�����ꂽ�A�N�^�[�ł��B<BR>
 * @version 1.00
 * @since 2009/07/14
 * @author Masatoshi Tsuge
 */
class GgafDxSpriteSetActor : public GgafDxDrawableActor {

public:
    /** [r]�����`��Z�b�g�� */
    int _draw_set_num;
    /** [r]���f������ */
    GgafDxSpriteSetModel* _pSpriteSetModel;
    /** [r]�G�t�F�N�g���� */
    GgafDxSpriteSetEffect* _pSpriteSetEffect;
    /** [r]UV�t���b�p�[(�p���p���A�j��) */
    GgafDxUvFlipper* _pUvFlipper;

    /**
     * �R���X�g���N�^ .
     * @param prm_name �A�N�^�[���́i�f�o�b�O���O�ŕ\���A�Ȃ�ł��ǂ��j
     * @param prm_model_id ���f����`���A������ ".x" ������X�t�@�C�����ɂȂ邱�ƁB
     * @param prm_effect_id �G�t�F�N�g��`���B������ ".fx" �����ăG�t�F�N�g�t�@�C�����ɂȂ邱�ƁB
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N��
     * @param prm_pStat �g�p����X�e�[�^�X�I�u�W�F�N�g(�g�p���Ȃ��� NULL�ł悢)
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����NULL�ł悢�j
     * @return
     */
    GgafDxSpriteSetActor(const char* prm_name,
                         const char* prm_model_id,
                         const char* prm_effect_id,
                         const char* prm_technique,
                         GgafCore::GgafStatus* prm_pStat,
                         GgafDxChecker* prm_pChecker );

    virtual void processDraw() override;

    virtual ~GgafDxSpriteSetActor();

    /**
     * ���ݒ�.
     * @param prm_alpha
     */
    void setAlpha(float prm_alpha) override;

    /**
     * �����Z .
     * @param prm_alpha
     */
    void addAlpha(float prm_alpha) override;
};

}
#endif /*GGAFDXSPRITESETACTOR_H_*/
