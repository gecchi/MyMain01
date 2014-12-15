#ifndef TESTSCENE_H_
#define TESTSCENE_H_
#include "VVViewer.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

namespace VVViewer {


/**
 * �e�X�g�V�[�� .
 * @version 1.00
 * @since 2014/12/15
 * @author Masatoshi Tsuge
 */
class TestScene : public GgafLib::DefaultScene {

public:
    VecUpActor* _pVecUpActor;
    VecEyeActor* _pVecEyeActor;
    /**
     * �R���X�g���N�^ .
     * @param prm_name ����
     */
    TestScene(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    virtual ~TestScene();
};

}
#endif /*TESTSCENE_H_*/
