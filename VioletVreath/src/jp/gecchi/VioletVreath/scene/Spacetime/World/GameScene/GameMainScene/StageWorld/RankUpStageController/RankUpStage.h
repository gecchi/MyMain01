#ifndef RANKUPSTAGE_H_
#define RANKUPSTAGE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"

#include "jp/ggaf/core/actor/MainActor.h"
#include "jp/ggaf/dx/actor/ex/Formation.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"
#include "jp/ggaf/lib/actor/DefaultSceneChief.h"
#include "jp/gecchi/VioletVreath/scene/VvScene.hpp"

namespace VioletVreath {

class RankUpStage : public VvScene<GgafLib::DefaultScene> {

public:
    enum {
        PHASE_INIT    ,
        PHASE_BEGIN   ,
        PHASE_PLAYING ,
        PHASE_RESULT  ,
        PHASE_END     ,
        PHASE_BANPEI,
    };

    static bool pause_;
    GgafDx::SeConnection* pSeConnection_all_hit_;

    char buff[80];
    WorldBoundRankUp* pWorldBound_;
    HoshiBoshiRankUp* pHoshiBoshi_;
    LabelGecchi16Font* pMessage1_;
    LabelGecchi16Font* pMessage2_;
    LabelGecchi16Font* pMessage3_;

public:

    /** RankUpStage ��p�� SceneChief */
    class SceneChief : public GgafLib::DefaultSceneChief {
    public:
        int hit_enemy_num_;
        int all_hit_num_;
        SceneChief(GgafLib::DefaultScene* prm_pRankUpStage) :
            GgafLib::DefaultSceneChief(prm_pRankUpStage) {
            all_hit_num_ = 0;
            hit_enemy_num_ = 0;
        }
        void appendChild(GgafCore::MainActor* prm_pMainActor) {
            GgafLib::DefaultSceneChief::appendChild(prm_pMainActor);
            //�S�ґ������~�����̂ŁA�ǉ���Ƀ����o�[�������Z���ĕێ����Ă���
            if (prm_pMainActor->instanceOf(Obj_GgafDx_Formation)) {
                GgafDx::Formation* pF = (GgafDx::Formation*)prm_pMainActor;
                all_hit_num_ += pF->getMemberNum();
            } else if (prm_pMainActor->getCheckerKind() & KIND_ENEMY_BODY) {
                all_hit_num_ ++;
            }
        }
    };

public:
    RankUpStage(const char* prm_name);

    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override;



    /**
     * ��������
     */
    //virtual void orderStageMain() = 0;

    virtual ~RankUpStage();



    virtual RankUpStage::SceneChief* getSceneChief() const override {
        return (RankUpStage::SceneChief*)_pSceneChief;
    }

    /**
     * �V�[���z���A�N�^�[���j�󂳂ꂽ�ꍇ�ɃR�[���o�b�N .
     * @param prm_pDestroyedActor �j�󂳂ꂽ�V�[���z���A�N�^�[
     */
    virtual void onDestroyedActor(GgafDx::GeometricActor* prm_pDestroyedActor) override {
        getSceneChief()->hit_enemy_num_ ++; //�����N�A�b�v�X�e�[�W�̓G�|������I�J�E���g�A�b�v
    }

};

}
#endif /*RANKUPSTAGE_H_*/
