#ifndef RANKUPSTAGE_H_
#define RANKUPSTAGE_H_

namespace MyStg2nd {



class RankUpStage : public GgafLib::DefaultScene {

public:
    static bool _pause;

    enum {
        PROG_INIT = 1,
        PROG_BEGIN   ,
        PROG_PLAYING ,
        PROG_RESULT  ,
        PROG_END     ,
    };
    WorldBoundSpaceRankUp* _pWorldBoundSpace;
    HoshiBoshiRankUp* _pHoshiBoshi;
    LabelGecchi16Font* _pMessage;

    RankUpStage(const char* prm_name);

    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override;
    virtual void onEnded() override;


    /**
     * èâä˙èàóù
     */
    //virtual void orderStageMain() = 0;

    virtual ~RankUpStage();
};

}
#endif /*RANKUPSTAGE_H_*/
