#ifndef BOX_H_
#define BOX_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/DefaultMassMeshActor.h"

namespace Mogera {

/**
 * �e�X�g�L�����N�^ .
 * @version 1.00
 * @since 2011/02/16
 * @author Masatoshi Tsuge
 */
class Box : public GgafLib::DefaultMassMeshActor {

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    Box(const char* prm_name);

    /**
     * �L�����̏������� .
     */
    void initialize() override;

    /**
     * �L�����̐U�镑������ .
     */
    void processBehavior() override;

    virtual ~Box();
};

}
#endif /*BOX_H_*/

