#ifndef RANKUP100_H_
#define RANKUP100_H_



namespace MyStg2nd {

class RankUp100 : public RankUpStage {

public:

    WorldBoundSpace001* _pWorldBoundSpace;
    HoshiBoshi001* _pHoshiBoshi;


    LabelGecchi16Font* _pMessage;

    RankUp100(const char* prm_name);
    /**
     * èâä˙èàóù
     */
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void processJudgement() override;
    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override;
    virtual ~RankUp100();
};

}
#endif /*RANKUP100_H_*/
