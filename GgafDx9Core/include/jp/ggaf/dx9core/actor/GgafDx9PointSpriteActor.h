#ifndef GGAFDX9POINTSPRITEACTOR_H_
#define GGAFDX9POINTSPRITEACTOR_H_
namespace GgafDx9Core {

/**
 * ���b�V���A�N�^�[.
 * GgafDx9DrawableActor ���p�����A�Ǝ���X�t�@�C����`�̃��b�V���\���@�\��<BR>
 * �ǉ������A�N�^�[�ł�<BR>
 * @version 1.00
 * @since 2009/02/26
 * @author Masatoshi Tsuge
 */
class GgafDx9PointSpriteActor : public GgafDx9DrawableActor {

public:

    /** ���f������ */
    GgafDx9PointSpriteModel* _pPointSpriteModel;
    /** �G�t�F�N�g���� */
    GgafDx9PointSpriteEffect* _pPointSpriteEffect;

    /**
     * �R���X�g���N�^
     * @param prm_name ���f�����́i�f�o�b�O���O�ŕ\���A�Ȃ�ł��ǂ��j
     * @param prm_model_id ���f����`���B������ ".x" ������X�t�@�C�����ɂȂ邱�ƁB
     * @param prm_effect_id �G�t�F�N�g��`���B������ ".fx" �����ăG�t�F�N�g�t�@�C�����ɂȂ邱�ƁB
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N��
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����NULL�ł悢�j
     */
    GgafDx9PointSpriteActor(const char* prm_name,
                       const char* prm_model_id,
                       const char* prm_effect_id,
                       const char* prm_technique,
                       GgafDx9Checker* prm_pChecker );

    virtual void processDraw() override;

    /**
     * ���l�ݒ�.
     * ���I�[�o�[���C�g��
     * @param prm_fAlpha ���l
     */
    void setAlpha(float prm_fAlpha) override;

    virtual ~GgafDx9PointSpriteActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9POINTSPRITEACTOR_H_*/
