#ifndef TRANSITSTAGE_H_
#define TRANSITSTAGE_H_
namespace VioletVreath {

/**
 * 通過ステージ .
 * 主な仕事は次のステージを決定することです。
 * @version 1.00
 * @since 2011/10/05
 * @author Masatoshi Tsuge
 */
class TransitStage : public Stage {

public:
    int teansit_stage_;
    int next_main_stage_;
    WorldBoundSpaceTransit* pWorldBoundSpace_;
    HoshiBoshiTransit* pHoshiBoshi_;
    LabelGecchi16Font* pMessage_;

public:
    TransitStage(const char* prm_name);
    /**
     * 初期処理
     */
    virtual void initialize() override;
    virtual void onReset() override;
    virtual void onActive() override;
    virtual void processBehavior() override;
    void processBehaviorProgPlaying();

    virtual void processJudgement() override;
    virtual void onInactive() override;
    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override;
    void ready(int prm_stage);
    void setStage(int prm_stage) {
        teansit_stage_ = prm_stage;
    }
    virtual ~TransitStage();
};

}
#endif /*TRANSITSTAGE_H_*/
