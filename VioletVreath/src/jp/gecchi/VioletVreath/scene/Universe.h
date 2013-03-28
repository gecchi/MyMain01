#ifndef UNIVERSE_H_
#define UNIVERSE_H_


#ifdef P_UNIVERSE
    #ifdef P_CAM
        #undef P_CAM
    #endif
    #define P_CAM ((VioletVreath::Camera*)(P_UNIVERSE->_pCamera))
#else
    #error P_UNIVERSE isnt define
#endif

/**
 * この世が保持する CameraWorkerManager に接続し、コネクションを取得。
 * X：識別文字列（CameraWorkerManager::processCreateResource(char* prm_idstr, void* prm_p) の prm_idstr に渡る)
 * また、CameraWorkerManager::processCreateResource(char* prm_idstr, void* prm_p) の prm_p には nullptr がセットされている。
 */
#define connectToCameraWorkerManager(X) ((VioletVreath::CameraWorkerConnection*)P_UNIVERSE->pCamWorkerManager_->connect(X))


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
class Universe : public GgafLib::DefaultUniverse {

    class CameraWorkerConnectionStack {
    public:
        CameraWorkerConnection* apCamWorkerConnection_[30];
        UINT32 p_;
        CameraWorkerConnectionStack() {
            p_ = 0;
            for (int i = 0; i < 30; i++) {
                apCamWorkerConnection_[i] = nullptr;
            }
        }
        CameraWorkerConnection* getLast() {
            if (p_ == 0) {
                return nullptr;
            } else {
                return apCamWorkerConnection_[p_-1];
            }
        }
        void push(CameraWorkerConnection* prm_pCamWorkerCon) {
            if (p_ > 30-1) {
                throwGgafCriticalException("CameraWorkerConnectionStack::push("<<prm_pCamWorkerCon->getIdStr()<<") スタックを使い切りました。");
            }
            apCamWorkerConnection_[p_] = prm_pCamWorkerCon;
            p_++;
        }
        CameraWorkerConnection* pop() {
            if (p_ == 0) {
                throwGgafCriticalException("CameraWorkerConnectionStack::pop() ポップしすぎです");
            } else {
                p_--;
                CameraWorkerConnection* r = apCamWorkerConnection_[p_];
                apCamWorkerConnection_[p_] = nullptr;
                return r;
            }
        }
        void clear() {
            p_ = 0;
            for (int i = 0; i < 30; i++) {
                apCamWorkerConnection_[i] = nullptr;
            }
        }

        void dump() {
            _TRACE_("CameraWorkerConnectionStack p_="<<p_);
            for (int i = 0; i < 30; i++) {
                if (apCamWorkerConnection_[i]) {
                    _TRACE_("apCamWorkerConnection_["<<i<<"]="<<(apCamWorkerConnection_[i]->getIdStr()));
                }
            }
        }
        ~CameraWorkerConnectionStack() {
            clear();
        }
    };


public:
    /** [r]現在のカメラマン */
    CameraWorker* pActiveCamWorker_;
    /** [r]カメラマンのマネージャー */
    CameraWorkerManager* pCamWorkerManager_;
    /** [r]カメラマンのスタック */
    CameraWorkerConnectionStack stack_CamWorkerConnection_;
    /** [r]世界 */
    World* pWorld_;

public:
    Universe(const char* prm_name, Camera* prm_pCamera);

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
    CameraWorker* switchCameraWork(const char* prm_pID);

    /**
     * 現在のカメラマンを排除し、一つ前のカメラマンに戻す。 .
     * 事前に switchCameraWork() を１回以上実行しておく必要があります。
     * @return 元々居た、戻った方のカメラマン
     */
    CameraWorker* undoCameraWork();

    /**
     * カメラマンをリセットする。
     * 何回 switchCameraWork() を行っていようと、デフォルトカメラマン(DefaultCamWorker)が
     * １人だけの状態に戻ります。
     */
    void resetCamWorker();

    virtual ~Universe();
};

}
#endif /*UNIVERSE_H_*/
