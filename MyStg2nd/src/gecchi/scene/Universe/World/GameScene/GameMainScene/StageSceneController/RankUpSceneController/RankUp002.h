#ifndef RANKUP002_H_
#define RANKUP002_H_



namespace MyStg2nd {

class RankUp002 : public RankUpScene {

public:

    WorldBoundSpace001* _pWorldBoundSpace;
    HoshiBoshi001* _pHoshiBoshi;


    LabelGecchi16Font* _pMessage;

    RankUp002(const char* prm_name);
    /**
     * èâä˙èàóù
     */
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void processJudgement() override;
    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override;
    virtual ~RankUp002();
};

}
#endif /*RANKUP002_H_*/
