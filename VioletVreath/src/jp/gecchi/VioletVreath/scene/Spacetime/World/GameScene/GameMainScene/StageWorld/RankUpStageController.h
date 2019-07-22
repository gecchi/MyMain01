#ifndef RANKUPSTAGECONTROLLER_H_
#define RANKUPSTAGECONTROLLER_H_
#include "VioletVreath.h"

#include "jp/gecchi/VioletVreath/scene/VvScene.hpp"
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld.h"

#ifdef pSTAGE_WORLD
    #define pRANKUP_CONTROLLER (pSTAGE_WORLD->pRankUpStageCtrler_)
#else
    #error pSTAGE_CTRLER isnt define
#endif

DECLARE_HASHVAL(EVENT_RANKUP_WAS_END);

namespace VioletVreath {

#define MAX_RANKUP_SCENE 100

/**
 * �����N�A�b�v�V�[���̃R���g���[���[ .
 * ��Ȏd���̓����N�A�b�v�X�e�[�W�̐؂�ւ��ł��B
 * @version 1.00
 * @since 2011/07/17
 * @author Masatoshi Tsuge
 */
class RankUpStageController : public VvScene<GgafLib::DefaultScene> {

public:
    char buf_[60];
    RankUpStage* apRankUpStage_[MAX_RANKUP_SCENE];
    RankUpStage* pNowRankUpStage_;
    GgafDx::SeConnection* pSeConn_RankUpStageExec_;
public:
    RankUpStageController(const char* prm_name);
    void startRunkUpStage(int prm_rank_up_level);

    void onReset() override;
    void ready(int prm_rank_up_level);

    void initialize() override;
    void processBehavior() override;
    void onCatchEvent(hashval prm_no, void* prm_pSource) override;
    /**
     * �z���̃����N�A�b�v�X�e�[�W��S�ĊJ��(sayonara())����B
     */
    void sayonaraRankUpStages();
    virtual ~RankUpStageController();

};

}
#endif /*RANKUPSTAGECONTROLLER_H_*/
