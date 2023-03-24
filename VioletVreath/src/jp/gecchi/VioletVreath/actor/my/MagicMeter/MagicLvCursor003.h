#ifndef MAGICLVCURSOR003_H_
#define MAGICLVCURSOR003_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/MagicLvCursor.h"



namespace VioletVreath {

/**
 * �e���@�̃��x���̏󋵁i�r���J�n�`�r����/������/�����J�n)�G�t�F�N�g�\���J�[�\�� .
 * @version 1.00
 * @since 2012/04/24
 * @author Masatoshi Tsuge
 */
class MagicLvCursor003 : public MagicLvCursor {

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name ����
     * @param prm_pMagicMeter ���[�^�[
     * @param prm_pMagic ���x���J�[�\���̑Ώۂ̖��@
     */
    MagicLvCursor003(const char* prm_name, MagicMeter* prm_pMagicMeter, Magic* prm_pMagic);

    void initialize() override;
    void processPreDraw() override;
    void processAfterDraw() override;
    void markOff();

    /**
     * �r���J�n�`�r�����i���x���A�b�v���j�̃G�t�F�N�g�J�n .
     * @param prm_lv ���x��
     */
    void markOnLevelUpCast(int prm_lv);

    /**
     * ���x���_�E�������̃G�t�F�N�g�J�n .
     * @param prm_lv ���x��
     */
    void markOnLevelDownCast(int prm_lv);

    /**
     * �������G�t�F�N�g�J�n .
     * @param prm_lv ���x��
     */
    void markOnInvoke(int prm_lv);

    /**
     * �����J�n�G�t�F�N�g�J�n .
     * @param prm_lv
     */
    void markOnEffect(int prm_lv);

    virtual ~MagicLvCursor003();
};

}
#endif /*MAGICLVCURSOR003_H_*/

