#ifndef RANKUPSTAGE_H_
#define RANKUPSTAGE_H_

namespace VioletVreath {



class RankUpStage : public GgafLib::DefaultScene {

public:
    static bool pause_;

    enum {
        PROG_INIT = 1,
        PROG_BEGIN   ,
        PROG_PLAYING ,
        PROG_RESULT  ,
        PROG_END     ,
    };
    WorldBoundSpaceRankUp* pWorldBoundSpace_;
    HoshiBoshiRankUp* pHoshiBoshi_;
    LabelGecchi16Font* pMessage_;

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
