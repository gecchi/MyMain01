#ifndef TEKI001_H_
#define TEKI001_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

namespace Mogera {

/**
 * �e�X�g�G�L�����N�^ .
 * @version 1.00
 * @since 2013/08/30
 * @author Masatoshi Tsuge
 */
class Zako : public GgafLib::DefaultMeshActor {

public:

    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    Zako(const char* prm_name);

    /**
     * �L�����̏������� .
     */
    void initialize() override;

    /**
     * �L�����̐U�镑������ .
     */
    void processBehavior() override;

    virtual ~Zako();
};

}
#endif /*TEKI001_H_*/

