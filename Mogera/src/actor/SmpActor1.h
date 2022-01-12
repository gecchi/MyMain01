#ifndef SMPACTOR1_H_
#define SMPACTOR1_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace Mogera {

/**
 * �e�X�g�L�����N�^ .
 * @version 1.00
 * @since 2011/02/16
 * @author Masatoshi Tsuge
 */
class SmpActor1 : public GgafLib::DefaultMeshSetActor {

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    SmpActor1(const char* prm_name);

    /**
     * �L�����̏������� .
     */
    void initialize() override;

    /**
     * �L�����̐U�镑������ .
     */
    void processBehavior() override;

    void onHit(const GgafCore::Actor* prm_pOtherActor);

    virtual ~SmpActor1();
};

}
#endif /*SMPACTOR1_H_*/

