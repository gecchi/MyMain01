#ifndef RANKUP002_H_
#define RANKUP002_H_



namespace MyStg2nd {

class RankUp002 : public RankUpStage {

public:

    RankUp002(const char* prm_name);
    /**
     * ��������
     */
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void processJudgement() override;
    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override;
    virtual ~RankUp002();
};

}
#endif /*RANKUP002_H_*/
