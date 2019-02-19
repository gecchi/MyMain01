#ifndef JIKI_H_
#define JIKI_H_
#include "jp/gecchi/VioletVrain/actor/kind/VvMyActor.h"
#include "VioletVrain.h"

#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"

namespace VioletVrain {

/**
 * �e�X�g
 * @author Masatoshi Tsuge
 */
class Jiki : public VvMyActor<GgafLib::DefaultSpriteActor> {

public:
    Jiki(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onReset() override;

    void onInactive() override;

    void processJudgement() override;

    virtual ~Jiki();

    static GgafCore::Status* resetJikiStatus(GgafCore::Status* p) {
        _TRACE_("���Ђ�Ђ�");
        return nullptr;
    }

};

}
#endif /*TEST01_H_*/

