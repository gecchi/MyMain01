#ifndef TEKI001_H_
#define TEKI001_H_
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

namespace Mogera {

/**
 * �e�X�g�G�L�����N�^ .
 * @version 1.00
 * @since 2013/08/30
 * @author Masatoshi Tsuge
 */
class Teki001 : public GgafLib::DefaultMeshActor {

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    Teki001(const char* prm_name);

    /**
     * �L�����̏������� .
     */
    void initialize() override;

    /**
     * �L�����̐U�镑������ .
     */
    void processBehavior() override;

    virtual ~Teki001();
};

}
#endif /*TEKI001_H_*/

