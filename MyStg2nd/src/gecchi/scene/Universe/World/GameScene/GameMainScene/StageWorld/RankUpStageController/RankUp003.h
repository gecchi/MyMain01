#ifndef RANKUP003_H_
#define RANKUP003_H_



namespace MyStg2nd {

class RankUp003 : public RankUpStage {

public:

    RankUp003(const char* prm_name);
    /**
     * ��������
     */
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void processJudgement() override;
    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override;
    virtual ~RankUp003();
};

}
#endif /*RANKUP003_H_*/