#ifndef RANKUPSTAGE_H_
#define RANKUPSTAGE_H_

namespace MyStg2nd {

enum {
    RANKUPSTAGE_PROG_INIT = 1,
    RANKUPSTAGE_PROG_BEGIN   ,
    RANKUPSTAGE_PROG_PLAYING ,
    RANKUPSTAGE_PROG_RESULT  ,
    RANKUPSTAGE_PROG_END     ,
};

class RankUpStage : public GgafLib::DefaultScene {

public:
    static bool _pause;
public:

    WorldBoundSpaceRankUp* _pWorldBoundSpace;
    HoshiBoshiRankUp* _pHoshiBoshi;
    LabelGecchi16Font* _pMessage;

    RankUpStage(const char* prm_name);

    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void processFinal() override;
    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override;
    virtual void onGarbaged() override;


    /**
     * èâä˙èàóù
     */
    //virtual void orderStageMain() = 0;

    virtual ~RankUpStage();
};

}
#endif /*RANKUPSTAGE_H_*/
