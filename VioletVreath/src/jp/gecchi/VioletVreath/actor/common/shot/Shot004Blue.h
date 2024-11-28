#ifndef SHOT004BLUE_H_
#define SHOT004BLUE_H_
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
class Shot004Blue : public VvEnemyActor<GgafLib::DefaultMassMeshActor> {

public:
    bool view_in_;

public:
    Shot004Blue(const char* prm_name);

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    virtual ~Shot004Blue();
};

}
#endif /*SHOT004BLUE_H_*/

