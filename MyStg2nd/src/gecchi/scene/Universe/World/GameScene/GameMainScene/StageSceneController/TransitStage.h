#ifndef TRANSITSTAGE_H_
#define TRANSITSTAGE_H_

namespace MyStg2nd {


/**
 * 通過ステージ .
 * 主な仕事は次のステージを決定することです。
 * @version 1.00
 * @since 2011/10/05
 * @author Masatoshi Tsuge
 */
class TransitStage : public StageScene {

public:
    int _teansit_stage;
    int _next_main_stage;
    WorldBoundSpaceTransit* _pWorldBoundSpace;
    HoshiBoshiTransit* _pHoshiBoshi;
    LabelGecchi16Font* _pMessage;

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
    virtual void processFinal() override;
    virtual void onInactive() override;
    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override;
    void ready(int prm_stage);
    void setStage(int prm_stage) {
        _teansit_stage = prm_stage;
    }
    virtual ~TransitStage();
};

}
#endif /*TRANSITSTAGE_H_*/
