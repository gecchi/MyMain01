#ifndef SPACETIME_H_
#define SPACETIME_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/scene/DefaultSpacetime.h"

#include "jp/gecchi/VioletVreath/actor/camera/Camera.h"

namespace VioletVreath {

/**
 * ��̓I�Ȃ��̐� .
 * �{�N���X�́A���̐��̐U�镑�����������܂��B<BR>
 * ��ɐ��E(World)���f���o���J����(Camera)���������A���̃J������
 * ��܂��Ȑ��䃁�\�b�h������܂��B<BR>
 * @version 1.00
 * @since 2009/04/24
 * @author Masatoshi Tsuge
 */
class Spacetime : public GgafLib::DefaultSpacetime {


public:
    VVCameraWorkerChanger* pCameraWorkerChanger_;
    /** [r]���E */
    World* pWorld_;

public:
    Spacetime(const char* prm_name, Camera* prm_pCamera);

    void initialize() override;

    void processBehavior() override;

    void processJudgement() override;

    VVCameraWorkerChanger* getCameraWorkerChanger() {
        return pCameraWorkerChanger_;
    }

    virtual Camera* getCamera() override { //���ς̖߂�l
        return (Camera*)_pCamera;
    }

    World* getWorld() {
        return pWorld_;
    }
    virtual ~Spacetime();
};

}
#endif /*SPACETIME_H_*/
