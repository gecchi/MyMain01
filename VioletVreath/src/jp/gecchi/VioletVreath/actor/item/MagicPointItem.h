#ifndef MAGICPOINTITEM_H_
#define MAGICPOINTITEM_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"

#include "jp/ggaf/lib/actor/DefaultMassMeshActor.h"
#include "jp/gecchi/VioletVreath/actor/VvItemActor.hpp"


namespace VioletVreath {

/**
 * MP�񕜃A�C�e���� .
 * @version 1.00
 * @since 2011/02/04
 * @author Masatoshi Tsuge
 */
class MagicPointItem : public VvItemActor<GgafLib::DefaultMassMeshActor> {

public:
    /** �z���������W */
    int kDX_, kDY_, kDZ_;
public:
    MagicPointItem(const char* prm_name, const char* prm_model, void* prm_pFuncStatusReset);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    virtual void onInactive() override;

//    int isOutOfView() override {
//        //��ʊO���薳��
//        return 0;
//    }
//
//    bool isOutOfSpacetime() const override {
//        //�Q�[�����W�͈͊O���薳��
//        return false;
//    }
    virtual void onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) override;

    virtual ~MagicPointItem();
};

}
#endif /*MAGICPOINTITEM_H_*/

