#ifndef TURBOMETER_H_
#define TURBOMETER_H_
namespace MyStg2nd {

class TurboMeter : public GgafDx9LibStg::DefaultBoardActor {

public:
    /** 100%のメーターの長さ(px) */
    float _max_px;
    /** 100%のメーターの値 */
    float _max_val;
    /** 現在のメーター値 */
    float _val;
    /** メーター値 1 の ピクセル値     */
    float _unit_px;

    TurboMeter(const char* prm_name);

    /**
     * メーターの目盛りを定義
     * @param prm_max_px メーター値が100%時の幅ピクセル
     * @param prm_max_val メーター値が100%とする実際の値
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

