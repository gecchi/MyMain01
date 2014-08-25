#ifndef RANKUPSTAGE_H_
#define RANKUPSTAGE_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "jp/ggaf/core/GgafFactory.h"

namespace VioletVreath {

class RankUpStage : public GgafLib::DefaultScene {

public:
    static bool pause_;
    enum {
        PROG_INIT    ,
        PROG_BEGIN   ,
        PROG_PLAYING ,
        PROG_RESULT  ,
        PROG_END     ,
        PROG_BANPEI,
    };

    GgafDxCore::GgafDxSeConnection* pSeConnection_all_hit_;

    int hit_enemy_num_;
    int all_hit_num_;

    char buff[80];
    WorldBoundSpaceRankUp* pWorldBoundSpace_;
    HoshiBoshiRankUp* pHoshiBoshi_;
    LabelGecchi16Font* pMessage1_;
    LabelGecchi16Font* pMessage2_;
    LabelGecchi16Font* pMessage3_;
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
