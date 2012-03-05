#ifndef TURBOMETER_H_
#define TURBOMETER_H_
namespace VioletVreath {

class TurboMeter : public GgafLib::DefaultBoardActor {

public:
    /** 100%�̃��[�^�[�̒���(px) */
    float max_px_;
    /** 100%�̃��[�^�[�̒l */
    float max_val_;
    /** ���݂̃��[�^�[�l */
    float val_;
    /** ���[�^�[�l 1 �� �s�N�Z���l     */
    float unit_px_;

    TurboMeter(const char* prm_name);

    /**
     * ���[�^�[�̖ڐ�����`
     * @param prm_max_px ���[�^�[�l��100%���̕��s�N�Z��
     * @param prm_max_val ���[�^�[�l��100%�Ƃ�����ۂ̒l
     */
    void graduateScale(float prm_max_px, float prm_max_val) {
        max_px_ = prm_max_px;
        max_val_ = prm_max_px;
        unit_px_ = max_px_ / max_val_;
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

