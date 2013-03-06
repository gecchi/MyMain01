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

    GgafDxCore::GgafDxSeConnection* pSeCon_all_hit_;

    int hit_enemy_num_;
    int all_hit_num_;

    char buff[80];
    WorldBoundSpaceRankUp* pWorldBoundSpace_;
    HoshiBoshiRankUp* pHoshiBoshi_;
    LabelGecchi16Font* pMessage1_;
    LabelGecchi16Font* pMessage2_;

public:
    RankUpStage(const char* prm_name);

    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override;
    virtual void onEnd() override;


    /**
     * èâä˙èàóù
     */
    //virtual void orderStageMain() = 0;

    virtual ~RankUpStage();
};

}
#endif /*RANKUPSTAGE_H_*/
