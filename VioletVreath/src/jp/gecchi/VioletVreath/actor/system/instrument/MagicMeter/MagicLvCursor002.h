#ifndef MAGICLVCURSOR002_H_
#define MAGICLVCURSOR002_H_


namespace VioletVreath {

/**
 * �e���@�̃��x���J�[�\���i���݂̃��x�������j .
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
    void moveTo(int prm_lv);
    void disable();
    void enable();

    void beginBlinking();
    void stopBlinking();

    virtual ~MagicLvCursor002();
};

}
#endif /*MAGICLVCURSOR002_H_*/

