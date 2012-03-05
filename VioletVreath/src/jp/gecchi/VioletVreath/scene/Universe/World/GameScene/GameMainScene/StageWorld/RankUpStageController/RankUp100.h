#ifndef RANKUP100_H_
#define RANKUP100_H_



namespace VioletVreath {

class RankUp100 : public RankUpStage {

public:

    WorldBoundSpace001* pWorldBoundSpace_;
    HoshiBoshi001* pHoshiBoshi_;


    LabelGecchi16Font* pMessage_;

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
