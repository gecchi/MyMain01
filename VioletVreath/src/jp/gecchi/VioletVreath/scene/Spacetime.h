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
        void dump();
        ~CameraWorkerHistory();
    };


public:
    /** [r]現在のカメラマン */
    GgafLib::CameraWorker* pActiveCamWorker_;
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
    GgafLib::CameraWorker* getActiveCamWorker() {
        return pActiveCamWorker_;
    }

    /**
     * カメラマンを切り替える .
     * 引数のカメラマンIDが初めてならば、カメラマン１人追加し、そちらにカメラの活動権与え切り替えます。 <br>
     * 引数のカメラマンIDが現在活動中のカメラマンと同じIDを指定した場合、単に無視されます。 <br>
     * 引数のカメラマンIDが現在活動中のカメラマンとは異なるが、以前切り替え済みのIDをだった場合、以前のそのカメラマンに切り替わります。 <br>
     * @param prm_pID 新しいカメラマン識別ID（識別IDは CameraWorkerManager に事前登録要）
     * @return カメラマンID
     */
    GgafLib::CameraWorker* changeCameraWork(const char* prm_pID);

    /**
     * 現在活動中のカメラマン、切り替え前のカメラマンに戻します。 .
     * 事前に changeCameraWork() を１回以上実行しておく必要があります。
     * @return 元々居た、戻った方のカメラマン
     */
    GgafLib::CameraWorker* undoCameraWork();

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
