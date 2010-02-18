#ifndef TURBOMETER_H_
#define TURBOMETER_H_
namespace MyStg2nd {

class TurboMeter : public GgafDx9LibStg::DefaultBoardActor {

public:
    /** 100%�̃��[�^�[�̒���(px) */
    float _max_px;
    /** 100%�̃��[�^�[�̒l */
    float _max_val;
    /** ���݂̃��[�^�[�l */
    float _val;
    /** ���[�^�[�l 1 �� �s�N�Z���l     */
    float _unit_px;

    TurboMeter(const char* prm_name);

    /**
     * ���[�^�[�̖ڐ�����`
     * @param prm_max_px ���[�^�[�l��100%���̕��s�N�Z��
     * @param prm_max_val ���[�^�[�l��100%�Ƃ�����ۂ̒l
     */
    void graduateScale(float prm_max_px, float prm_max_val) {
        _max_px = prm_max_px;
        _max_val = prm_max_val;
        _unit_px = _max_px / _max_val;
    }

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    virtual ~TurboMeter();
};

}
#endif /*BACKGROUNDCHIPBOARD_H_*/

