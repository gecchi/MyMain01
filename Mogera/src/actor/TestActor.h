#ifndef TESTACTOR_H_
#define TESTACTOR_H_
#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"

namespace Mogera {

/**
 * �e�X�g�w�i .
 * @version 1.00
 * @since 2013/08/29
 * @author Masatoshi Tsuge
 */
class TestActor : public GgafLib::DefaultBoardActor {

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    TestActor(const char* prm_name);

    /**
     * �L�����̏������� .
     */
    void initialize() override;

    /**
     * �L�����̐U�镑������ .
     */
    void processBehavior() override;

    virtual ~TestActor();
};

}
#endif /*TESTACTOR_H_*/

