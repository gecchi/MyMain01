#ifndef SHOT004_H_
#define SHOT004_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMassMeshActor.h"

namespace VioletVreath {

/**
 * �ėp�e004(��) .
 * �j��s�\�œ��������ړ��̏����ȃ��[�U�[��<BR>
 * @version 1.00
 * @since 2009/12/28
 * @author Masatoshi Tsuge
 */
class Shot004 : public VvEnemyActor<GgafLib::DefaultMassMeshActor> {

public:
    bool view_in_;

public:
    Shot004(const char* prm_name);

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) override;

    virtual ~Shot004();
};

}
#endif /*SHOT004_H_*/

