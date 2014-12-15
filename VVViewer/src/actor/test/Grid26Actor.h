#ifndef GRID26ACTOR_H_
#define GRID26ACTOR_H_
#include "VVViewer.h"
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

namespace VVViewer {

/**
 * �e�X�g�G�L�����N�^ .
 * @version 1.00
 * @since 2014/12/15
 * @author Masatoshi Tsuge
 */
class Grid26Actor : public GgafLib::DefaultMeshActor {

public:

    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    Grid26Actor(const char* prm_name);

    /**
     * �L�����̏������� .
     */
    void initialize() override;

    /**
     * �L�����̐U�镑������ .
     */
    void processBehavior() override;

    virtual ~Grid26Actor();
};

}
#endif /*GRID26ACTOR_H_*/

