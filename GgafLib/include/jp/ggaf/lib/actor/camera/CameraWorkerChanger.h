#ifndef GGAF_LIB_CAMERAWORKERCHANGER_H_
#define GGAF_LIB_CAMERAWORKERCHANGER_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/core/actor/MainActor.h"

namespace GgafLib {

#define CAM_WORKER_HISTORY_NUM (30)

/**
 * カメラマンチェンジャー .
 * @version 1.00
 * @since 2019/03/2
 * @author Masatoshi Tsuge
 */
class CameraWorkerChanger : public GgafCore::MainActor {

public:
    class History {
    public:
        CameraWorkerConnection* _apCamWorkerConnection[CAM_WORKER_HISTORY_NUM];
        uint32_t _p;
        History();
        CameraWorkerConnection* getLast();
        void push(CameraWorkerConnection* prm_pCamWorkerCon);
        CameraWorkerConnection* pop();
        void dump();
        ~History();
    };

public:
    /** [r]現在のカメラマン */
    GgafLib::CameraWorker* _pActiveCamWorker;
    /** [r]カメラマンのマネージャー */
    CameraWorkerManager* _pCamWorkerManager;
    /** [r]カメラマンのスタック */
    History _stack_CamWorkerConnection;
    DefaultCamera* _pCamera;
public:
    CameraWorkerChanger(const char* prm_name, DefaultCamera* prm_pCamera);

    static bool initStatic();

    /**
     * カメラマン生成関数 .
     * オーバーライドして prm_idstr に応じたカメラマンを生成する処理を実装してください。
     * @param prm_idstr
     * @param prm_pConnector
     * @return
     */
    virtual CameraWorker* createCameraWorker(const char* prm_idstr, void* prm_pConnector) = 0;

    /**
     * 現在のカメラマンを返す .
     * 初期状態は、デフォルトカメラマン(DefaultCamWorker)が一人います。
     * @return 現在のカメラマン
     */
    GgafLib::CameraWorker* getActiveCamWorker() {
        return _pActiveCamWorker;
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
     * カメラマン達を掃除する。
     * 何回 changeCameraWork() を行っていようと、デフォルトカメラマン(DefaultCamWorker)が
     * １人だけの状態に戻ります。
     */
    void cleanCamWorker();

    virtual void initialize() override;

    virtual void onActive() override {}

    virtual void processBehavior() override;

    virtual void processJudgement() override {}

    virtual void processDraw() override {}

    virtual void processFinal() override {}

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    virtual bool processHitChkLogic(GgafCore::Actor* prm_pOtherActor) override {
        return false;
    }

    virtual ~CameraWorkerChanger(); //デストラクタ
};

}
#endif /*GGAF_LIB_CAMERAWORKERCHANGER_H_*/
