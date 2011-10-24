#ifndef RANKUP001_H_
#define RANKUP001_H_



namespace MyStg2nd {

class RankUp001 : public RankUpStage {

public:

    RankUp001(const char* prm_name);
    /**
     * ‰Šúˆ—
     */
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void processJudgement() override;
    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override;
    virtual ~RankUp001();
};

}
#endif /*RANKUP001_H_*/
