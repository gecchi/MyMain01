#ifndef TURBOMETER_H_
#define TURBOMETER_H_
namespace VioletVreath {

class TurboMeter : public GgafLib::DefaultBoardActor {

public:
    /** 100%のメーターの長さ(px) */
    float max_px_;
    /** 100%のメーターの値 */
    float max_val_;
    /** 現在のメーター値 */
    float val_;
    /** メーター値 1 の ピクセル値     */
    float unit_px_;

    TurboMeter(const char* prm_name);

    /**
     * メーターの目盛りを定義
     * @param prm_max_px メーター値が100%時の幅ピクセル
     * @param prm_max_val メーター値が100%とする実際の値
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

