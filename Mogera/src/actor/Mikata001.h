#ifndef MIKATA001_H_
#define MIKATA001_H_
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"
#include "jp/ggaf/core/util/GgafValueAccelerator.hpp"

namespace Mogera {

/**
 * �e�X�g�����L�����N�^ .
 * @version 1.00
 * @since 2013/08/30
 * @author Masatoshi Tsuge
 */
class Mikata001 : public GgafLib::DefaultMorphMeshActor {

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    Mikata001(const char* prm_name);

    /**
     * �L�����̏������� .
     */
    void initialize() override;

    void onActive() override;

    /**
     * �L�����̐U�镑������ .
     */
    void processBehavior() override;

    void onInactive() override;

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~Mikata001();
};

}
#endif /*MIKATA001_H_*/

