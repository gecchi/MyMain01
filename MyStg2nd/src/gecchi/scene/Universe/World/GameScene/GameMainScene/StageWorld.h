#ifndef STAGEWORLD_H_
#define STAGEWORLD_H_


#ifdef P_GAME_SCENE
    #define P_STAGE_WORLD (P_GAME_SCENE->_pStageWorld)
#else
    #error P_GAME_SCENE isnt define
#endif


namespace MyStg2nd {

class StageWorld : public GgafLib::DefaultScene {

public:
    /** ランクアップ挿入シーン */
    RankUpStageController* _pRankUpStageController;
    StageController* _pStageController;
    bool _can_rank_up;
    StageWorld(const char* prm_name);
    void onReset() override;
    void initialize() override;
    void processBehavior() override;
    void onCatchEvent(hashval prm_no, void* prm_pSource) override;
    virtual ~StageWorld();
};

}
#endif /*STAGEWORLD_H_*/
