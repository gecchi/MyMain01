#ifndef RANKUPSTAGE_H_
#define RANKUPSTAGE_H_
#include "VioletVreath.h"

#include "jp/ggaf/core/GgafFactory.h"
#include "jp/ggaf/core/actor/GgafMainActor.h"
#include "jp/ggaf/core/actor/ex/GgafFormation.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"
#include "jp/ggaf/lib/actor/DefaultSceneMediator.h"


namespace VioletVreath {

class RankUpStage : public GgafLib::DefaultScene {

public:
    enum {
        PROG_INIT    ,
        PROG_BEGIN   ,
        PROG_PLAYING ,
        PROG_RESULT  ,
        PROG_END     ,
        PROG_BANPEI,
    };

    static bool pause_;
    GgafDxCore::GgafDxSeConnection* pSeConnection_all_hit_;

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

        GgafCore::GgafGroupHead* addSubGroup(kind_t prm_kind, GgafCore::GgafMainActor* prm_pMainActor) {
            GgafCore::GgafGroupHead* pGroupHead = GgafLib::DefaultSceneMediator::addSubGroup(prm_kind, prm_pMainActor);
            if (prm_pMainActor->instanceOf(Obj_GgafFormation)) {
                GgafCore::GgafFormation* pF = (GgafCore::GgafFormation*)prm_pMainActor;
                all_hit_num_ += pF->getMemberNum();
            } else if (prm_pMainActor->lookUpKind() & KIND_ENEMY_BODY) {
                all_hit_num_ ++;
            }
            return pGroupHead;
        }
        GgafCore::GgafGroupHead* addSubGroup(GgafCore::GgafMainActor* prm_pMainActor) {
            return Medietor::addSubGroup(prm_pMainActor->getDefaultKind(), prm_pMainActor);
        }
    };

public:
    RankUpStage(const char* prm_name);

    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override;



    /**
     * 初期処理
     */
    //virtual void orderStageMain() = 0;

    virtual ~RankUpStage();



    virtual RankUpStage::Medietor* bringSceneMediator() const override {
        return (RankUpStage::Medietor*)_pSceneMediator;
    }
    void onDestroyedEnemy(GgafDxCore::GgafDxFigureActor* prm_this, const GgafDxCore::GgafDxGeometricActor* const prm_pOther) {
        bringSceneMediator()->hit_enemy_num_ ++; //ランクアップステージの敵倒したよ！カウントアップ
    }

};

}
#endif /*RANKUPSTAGE_H_*/
