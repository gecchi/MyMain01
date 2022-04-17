#ifndef MAGICLVCURSOR001_H_
#define MAGICLVCURSOR001_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/MagicLvCursor.h"

namespace VioletVreath {

/**
 * �e���@�̃��[�U�[���x���I��(����ړ��p)�J�[�\�� .
 * @version 1.00
 * @since 2011/12/12
 * @author Masatoshi Tsuge
 */
class MagicLvCursor001 : public MagicLvCursor {

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name ����
     * @param prm_pMagicMeter ���[�^�[
     * @param prm_pMagic ���x���J�[�\���̑Ώۂ̖��@
     */
    MagicLvCursor001(const char* prm_name, MagicMeter* prm_pMagicMeter, Magic* prm_pMagic);

    void initialize() override;

    void moveSmoothTo(int prm_lv) { //�Ӑ}�I�� ��ʂ� moveSmoothTo �� hiding
        MagicLvCursor::moveSmoothTo(prm_lv, 12, 0.3f, 0.7f);
    }

    /**
     * ����s��ԕ\�� .
     */
    void dispDisable();
    /**
     * �����ԕ\�� .
     */
    void dispEnable();

    virtual ~MagicLvCursor001();
};

}
#endif /*MAGICLVCURSOR001_H_*/

