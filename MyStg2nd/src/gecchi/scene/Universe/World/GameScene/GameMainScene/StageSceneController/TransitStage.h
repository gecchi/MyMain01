#ifndef TRANSITSTAGE_H_
#define TRANSITSTAGE_H_

namespace MyStg2nd {


/**
 * �ʉ߃X�e�[�W .
 * ��Ȏd���͎��̃X�e�[�W�����肷�邱�Ƃł��B
 * @version 1.00
 * @since 2011/10/05
 * @author Masatoshi Tsuge
 */
class TransitStage : public StageScene {

public:

    WorldBoundSpaceTransit* _pWorldBoundSpace;
    HoshiBoshiTransit* _pHoshiBoshi;
    LabelGecchi16Font* _pMessage;

    TransitStage(const char* prm_name);
    /**
     * ��������
     */
    virtual void initialize() override;
    virtual void onReset() override;
    virtual void onActive() override;
    virtual void processBehavior() override;
    virtual void processJudgement() override;
    virtual void processFinal() override;
    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override;
    void ready(int prm_stage);
    virtual ~TransitStage();
};

}
#endif /*TRANSITSTAGE_H_*/
