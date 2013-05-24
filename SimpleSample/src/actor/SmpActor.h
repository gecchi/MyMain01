#ifndef SMPACTOR_H_
#define SMPACTOR_H_
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

namespace SimpleSample {

/**
 * �e�X�g�L�����N�^ .
 * @version 1.00
 * @since 2011/02/16
 * @author Masatoshi Tsuge
 */
class SmpActor : public GgafLib::DefaultMeshActor {

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    SmpActor(const char* prm_name);

    /**
     * �L�����̏������� .
     */
    void initialize() override;

    /**
     * �L�����̐U�镑������ .
     */
    void processBehavior() override;

    virtual ~SmpActor();
};

}
#endif /*SMPACTOR_H_*/

