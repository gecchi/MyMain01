#ifndef MAGICLVCURSOR003_H_
#define MAGICLVCURSOR003_H_


namespace VioletVreath {

/**
 * �e���@�̉r�������������x�������\���J�[�\�� .
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

    void markOff();
    void markOnLevelUpCast(int prm_lv);
    void markOnLevelDownCast(int prm_lv);
    void markOnInvoke(int prm_lv);
    virtual ~MagicLvCursor003();
};

}
#endif /*MAGICLVCURSOR003_H_*/

