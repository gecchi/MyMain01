#ifndef MAGICMETERCURSOR001_H_
#define MAGICMETERCURSOR001_H_


namespace MyStg2nd {

/**
 * ���[�^�[��J�[�\�� .
 * @version 1.00
 * @since 2011/12/12
 * @author Masatoshi Tsuge
 */
class MagicMeterCursor001 : public GgafLib::DefaultBoardActor {

public:
    /** �ړ��ڕWX���W */
    coord _tX;
    /** �ړ��ڕWY���W */
    coord _tY;

    MagicMeter* _pMagicMeter;

    MagicMeterCursor001(const char* prm_name, MagicMeter* prm_pMagicMeter);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void moveTo(int prm_magic_mater_index);

    virtual ~MagicMeterCursor001();
};

}
#endif /*MAGICMETERCURSOR001_H_*/
