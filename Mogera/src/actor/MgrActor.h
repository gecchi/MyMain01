#ifndef MGRACTOR_H_
#define MGRACTOR_H_
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"

namespace Mogera {

/**
 * �e�X�g�L�����N�^ .
 * @version 1.00
 * @since 2011/02/16
 * @author Masatoshi Tsuge
 */
class MgrActor : public GgafLib::DefaultBoardActor {

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    MgrActor(const char* prm_name);

    /**
     * �L�����̏������� .
     */
    void initialize() override;

    /**
     * �L�����̐U�镑������ .
     */
    void processBehavior() override;

    virtual ~MgrActor();
};

}
#endif /*MGRACTOR_H_*/

