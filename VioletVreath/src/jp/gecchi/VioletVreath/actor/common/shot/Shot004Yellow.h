#ifndef SHOT004YELLOW_H_
#define SHOT004YELLOW_H_
#include "jp/ggaf/lib/actor/SingleLaser.h"

namespace VioletVreath {

/**
 * �ėp�e004(��) .
 * �j��s�\�œ��������ړ��̏����ȃ��[�U�[��<BR>
 * @version 1.00
 * @since 2009/12/28
 * @author Masatoshi Tsuge
 */
class Shot004Yellow : public GgafLib::SingleLaser {

public:
    bool view_in_;

public:
    Shot004Yellow(const char* prm_name);

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~Shot004Yellow();
};

}
#endif /*SHOT004YELLOW_H_*/

