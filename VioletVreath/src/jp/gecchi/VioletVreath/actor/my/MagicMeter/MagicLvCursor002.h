#ifndef MAGICLVCURSOR002_H_
#define MAGICLVCURSOR002_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/MagicLvCursor.h"



namespace VioletVreath {

/**
 * �e���@�̌��s���x�������\���J�[�\���i�j .
 * @version 1.00
 * @since 2012/04/19
 * @author Masatoshi Tsuge
 */
class MagicLvCursor002 : public MagicLvCursor {

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name ����
     * @param prm_pMagicMeter ���[�^�[
     * @param prm_pMagic ���x���J�[�\���̑Ώۂ̖��@
     */
    MagicLvCursor002(const char* prm_name, MagicMeter* prm_pMagicMeter, Magic* prm_pMagic);

    void initialize() override;

    void moveSmoothTo(int prm_lv, frame prm_spent=10) { //�Ӑ}�I�� ��ʂ� moveSmoothTo �� hiding
        MagicLvCursor::moveSmoothTo(prm_lv, prm_spent, 0.3f, 0.7f); //����`���ƈړ�
    }

    /**
     * ����s��ԕ\�� .
     */
    void dispDisable();
    /**
     * ����\��ԕ\�� .
     */
    void dispEnable();

    virtual ~MagicLvCursor002();
};

}
#endif /*MAGICLVCURSOR002_H_*/

