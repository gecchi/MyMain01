#ifndef VIEWPOINTGUIDE_H_
#define VIEWPOINTGUIDE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultD3DXMeshActor.h"

namespace VioletVreath {

/**
 * �����_ .
 * @version 1.00
 * @since 2011/03/21
 * @author Masatoshi Tsuge
 */
class ViewPointGuide : public GgafLib::DefaultD3DXMeshActor {

public:

    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @return
     */
    ViewPointGuide(const char* prm_name);

    void onCreateModel() override {
    }
    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    virtual int isOutOfView() override {
        return 0; //��ɕ\��
    }

    virtual bool isOutOfSpacetime() const override {
        return false; //��ɕ\��
    }

    void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) override;

    virtual ~ViewPointGuide();
};

}
#endif /*VIEWPOINTGUIDE_H_*/

