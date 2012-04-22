#ifndef MAGICMETERCURSOR003_H_
#define MAGICMETERCURSOR003_H_


namespace VioletVreath {

/**
 * �e���@�̃��x���J�[�\���i���݂̃��x�������j .
 * @version 1.00
 * @since 2012/04/19
 * @author Masatoshi Tsuge
 */
class MagicMeterCursor003 : public GgafLib::DefaultBoardActor {

public:
    /** �ړ��ڕWX���W */
    coord tX_;
    /** �ړ��ڕWY���W */
    coord tY_;

    /** [r]�J�[�\���Ώۂ̖��@ */
    Magic* pMagic_;
    /** [r]���@���[�^�[ */
    MagicMeter* pMagicMeter_;



    int magic_index_;

    coord tmp_Y_;

    /**
     * �R���X�g���N�^ .
     * @param prm_name ����
     * @param prm_pMagicMeter ���[�^�[
     * @param prm_pMagic ���x���J�[�\���̑Ώۂ̖��@
     */
    MagicMeterCursor003(const char* prm_name, MagicMeter* prm_pMagicMeter, Magic* prm_pMagic);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;


    void processPreDraw() override;

    void processAfterDraw() override;

    void disable();
    void enable();

    void moveToLv(int prm_lv);

    void beginBlinking();
    void stopBlinking();

    virtual ~MagicMeterCursor003();
};

}
#endif /*MAGICMETERCURSOR003_H_*/

