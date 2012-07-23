#ifndef MAGICLVCURSOR001_H_
#define MAGICLVCURSOR001_H_


namespace VioletVreath {

/**
 * �e���@�̃��x���J�[�\���i����ړ��p�j .
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


    void moveSmoothTo(int prm_lv); //�Ӑ}�I�� ��ʂ� moveSmoothTo �� hide ���Ă܂��B

    void dispDisable();
    void dispEnable();

    virtual ~MagicLvCursor001();
};

}
#endif /*MAGICLVCURSOR001_H_*/

