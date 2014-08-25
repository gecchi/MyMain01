#ifndef TAMAGOACTOR_H_
#define TAMAGOACTOR_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultD3DXAniMeshActor.h"

namespace VioletVreath {

/**
 * �ŏ��ɍ����3D�̓G(���ݖ��g�p)
 * @version 1.00
 * @since 2008/07/23
 * @author Masatoshi Tsuge
 */
class TamagoActor : public  GgafLib::DefaultD3DXAniMeshActor {

    int rnd_;
    double last_time_;

public:
    TamagoActor(const char* prm_name, GgafCore::GgafStatus* prm_pStat);

    void initialize() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    int isOutOfView() override {
        return 0;
    }

    bool isOutOfUniverse() override {
        return false;
    }

    virtual ~TamagoActor();
};

}
#endif /*TAMAGOACTOR_H_*/

