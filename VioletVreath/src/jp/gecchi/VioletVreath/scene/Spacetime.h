#ifndef SPACETIME_H_
#define SPACETIME_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/scene/DefaultSpacetime.h"

#include "jp/gecchi/VioletVreath/actor/camera/Camera.h"
#include "jp/gecchi/VioletVreath/manager/CameraWorkerManager.h"
#include "jp/gecchi/VioletVreath/manager/CameraWorkerConnection.h"

/**
 * この世が保持する CameraWorkerManager に接続し、コネクションを取得。
 * X：識別文字列（CameraWorkerManager::processCreateResource(const char* prm_idstr, void* prm_pConnector) の prm_idstr に渡る)
 * pCAMERA：カメラを渡すこと
 * また、CameraWorkerManager::processCreateResource(const char* prm_idstr, void* prm_pConnector) の prm_p には nullptr がセットされている。
 */
#define CAM_WORKER_STACK_NUM (30)

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

    class CameraWorkerHistory {
    public:
        CameraWorkerConnection* apCamWorkerConnection_[CAM_WORKER_STACK_NUM];
        uint32_t p_;
        CameraWorkerHistory();
        CameraWorkerConnection* getLast();
        void push(CameraWorkerConnection* prm_pCamWorkerCon);
        CameraWorkerConnection* pop();
        void clear();
        void dump();
        ~CameraWorkerHistory();
    };


public:
    /** [r]現在のカメラマン */
    CameraWorker* pActiveCamWorker_;
    /** [r]カメラマンのマネージャー */
    CameraWorkerManager* pCamWorkerManager_;
    /** [r]カメラマンのスタック */
    CameraWorkerHistory stack_CamWorkerConnection_;
    /** [r]世界 */
    World* pWorld_;

public:
    Spacetime(const char* prm_name, Camera* prm_pCamera);

    void initialize() override;

    void processBehavior() override;

    void processJudgement() override;

    /**
     * 現在のカメラマンを返す .
     * 初期状態は、デフォルトカメラマン(DefaultCamWorker)が一人います。
     * @return 現在のカメラマン
     */
    CameraWorker* getActiveCamWorker() {
        return pActiveCamWorker_;
    }

    /**
     * カメラマンを一時的に切り替える .
     * 新しいカメラマンを１人追加し、そちらにカメラの主導権を切り替えます。
     * 以後、undoCameraWork() が実行されるまでそのままです。
     * @param prm_pID 新しいカメラマン識別ID（識別IDは CameraWorkerManager に事前登録要）
     * @return 新しいカメラマン
     */
    CameraWorker* changeCameraWork(const char* prm_pID);

    /**
     * 現在のカメラマンを排除し、一つ前のカメラマンに戻す。 .
     * 事前に changeCameraWork() を１回以上実行しておく必要があります。
     * @return 元々居た、戻った方のカメラマン
     */
    CameraWorker* undoCameraWork();

    /**
     * カメラマンをリセットする。
     * 何回 changeCameraWork() を行っていようと、デフォルトカメラマン(DefaultCamWorker)が
     * １人だけの状態に戻ります。
     */
    void resetCamWorker();

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
