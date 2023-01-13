#ifndef RANKUPSTAGE_H_
#define RANKUPSTAGE_H_
#include "VioletVreath.h"

#include "jp/ggaf/core/actor/MainActor.h"
#include "jp/ggaf/core/actor/ex/Formation.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"
#include "jp/ggaf/lib/actor/DefaultSceneMediator.h"
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
    class Medietor : public GgafLib::DefaultSceneMediator {
    public:
        int hit_enemy_num_;
        int all_hit_num_;

    public:
        Medietor(GgafLib::DefaultScene* prm_pRankUpStage) :
            GgafLib::DefaultSceneMediator(prm_pRankUpStage) {
            all_hit_num_ = 0;
            hit_enemy_num_ = 0;
        }

        GgafCore::GroupHead* appendGroupChild(kind_t prm_kind, GgafCore::MainActor* prm_pMainActor) {
            GgafCore::GroupHead* pGroupHead = GgafLib::DefaultSceneMediator::appendGroupChild(prm_kind, prm_pMainActor);
            //全編隊数が欲しいので、追加後にメンバー数を合算して保持しておく
            if (prm_pMainActor->instanceOf(Obj_ggaf_Formation)) {
                GgafCore::Formation* pF = (GgafCore::Formation*)prm_pMainActor;
                all_hit_num_ += pF->getMemberNum();
            } else if (prm_pMainActor->lookUpKind() & KIND_ENEMY_BODY) {
                all_hit_num_ ++;
            }
            return pGroupHead;
        }
        GgafCore::GroupHead* appendGroupChild(GgafCore::MainActor* prm_pMainActor) {
            return Medietor::appendGroupChild(prm_pMainActor->getDefaultKind(), prm_pMainActor);
        }
    };

public:
    RankUpStage(const char* prm_name);

    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override;



    /**
     * 初期処理
     */
    //virtual void orderStageMain() = 0;

    virtual ~RankUpStage();



    virtual RankUpStage::Medietor* bringSceneMediator() const override {
        return (RankUpStage::Medietor*)_pSceneMediator;
    }
    void onDestroyedEnemy(GgafDx::FigureActor* prm_this, const GgafDx::GeometricActor* const prm_pOther) {
        bringSceneMediator()->hit_enemy_num_ ++; //ランクアップステージの敵倒したよ！カウントアップ
    }

};

}
#endif /*RANKUPSTAGE_H_*/
