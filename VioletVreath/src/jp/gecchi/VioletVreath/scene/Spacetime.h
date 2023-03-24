#ifndef SPACETIME_H_
#define SPACETIME_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"

#include "jp/ggaf/lib/scene/DefaultSpacetime.h"
#include "jp/gecchi/VioletVreath/actor/camera/Camera.h"

namespace VioletVreath {

/**
 * 具体的なこの世 .
 * 本クラスは、この世の振る舞い等を実装ます。<BR>
 * 主に世界(World)を映し出すカメラ(Camera)が所属し、そのカメラの
 * 大まかな制御メソッドを備えます。<BR>
 * @version 1.00
 * @since 2009/04/24
 * @author Masatoshi Tsuge
 */
class Spacetime : public GgafLib::DefaultSpacetime {


public:
    VVCameraWorkerChanger* pCameraWorkerChanger_;
    /** [r]世界 */
    World* pWorld_;

public:
    Spacetime(const char* prm_name, Camera* prm_pCamera);

    void initialize() override;

    void processBehavior() override;

    void processJudgement() override;

    void processHitCheck() override;

    VVCameraWorkerChanger* getCameraWorkerChanger() {
        return pCameraWorkerChanger_;
    }

    virtual Camera* getCamera() override { //共変の戻り値
        return (Camera*)_pCamera;
    }

    World* getWorld() {
        return pWorld_;
    }
    virtual ~Spacetime();
};

}
#endif /*SPACETIME_H_*/
