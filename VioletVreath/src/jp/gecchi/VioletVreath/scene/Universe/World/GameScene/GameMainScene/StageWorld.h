#ifndef STAGEWORLD_H_
#define STAGEWORLD_H_


#ifdef P_GAME_SCENE
    #define P_STAGE_WORLD (P_GAME_SCENE->pStageWorld_)
#else
    #error P_GAME_SCENE isnt define
#endif


namespace VioletVreath {

class StageWorld : public GgafLib::DefaultScene {

public:
    /** ランクアップ挿入シーン */
    RankUpStageController* pRankUpStageCtrler_;
    StageController* pStageCtrler_;
    bool can_rank_up_;
    StageWorld(const char* prm_name);
    void onReset() override;
    void initialize() override;
    void processBehavior() override;
    void onCatchEvent(hashval prm_no, void* prm_pSource) override;
    virtual ~StageWorld();
};

}
#endif /*STAGEWORLD_H_*/
