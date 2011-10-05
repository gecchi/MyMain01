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

    WorldBoundSpace001* _pWorldBoundSpace;
    HoshiBoshi001* _pHoshiBoshi;
    LabelGecchi16Font* _pMessage;

    TransitStage(const char* prm_name);
    /**
     * 初期処理
     */
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void processJudgement() override;
    virtual void processFinal() override;
    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override;
    virtual ~TransitStage();
};

}
#endif /*TRANSITSTAGE_H_*/
