#ifndef STAGEWORLD_H_
#define STAGEWORLD_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene.h"

namespace VioletVreath {

#ifdef pGAME_SCENE
    #define pSTAGE_WORLD (pGAME_SCENE->pStageWorld_)
#else
    #error pGAME_SCENE isnt define
#endif

#define SLOW_FRAME_RANKUP (2)

/**
 * �X�e�[�W���E�V�[�� .
 * �Q�[���̖ʂɓ�����u�X�e�[�W�v�̒��_�Ɉʒu����V�[���N���X�ł��B
 * @version 1.00
 * @since 2011/10/24
 * @author Masatoshi Tsuge
 */
class StageWorld : public GgafLib::DefaultScene {

public:
    /** �����N�A�b�v�}���V�[�� */
    RankUpStageController* pRankUpStageCtrler_;
    StageController* pStageCtrler_;
    bool can_rank_up_;

public:
   StageWorld(const char* prm_name);
    void onReset() override;
    void initialize() override;
    void processBehavior() override;
    void onCatchEvent(hashval prm_no, void* prm_pSource) override;
    virtual ~StageWorld();
};

}
#endif /*STAGEWORLD_H_*/
