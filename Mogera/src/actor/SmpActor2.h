#ifndef SMPACTOR2_H_
#define SMPACTOR2_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

namespace Mogera {

/**
 * �e�X�g�L�����N�^ .
 * @version 1.00
 * @since 2011/02/16
 * @author Masatoshi Tsuge
 */
class SmpActor2 : public GgafLib::DefaultMeshActor {

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    SmpActor2(const char* prm_name);

    /**
     * �L�����̏������� .
     */
    void initialize() override;

    /**
     * �L�����̐U�镑������ .
     */
    void processBehavior() override;

    void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor);

    virtual ~SmpActor2();
};

}
#endif /*SMPACTOR2_H_*/

