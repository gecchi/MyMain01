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
 * また、CameraWorkerManager::processCreateResource(char* prm_idstr, void* prm_p) の prm_p には NULL がセットされている。
 */
#define connectCameraWorkerManager(X) ((VioletVreath::CameraWorkerConnection*)P_UNIVERSE->pCamWorkerManager_->connect(X))


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
        CameraWorkerConnection* apCamWorkerCon_[30];
        UINT32 p_;
        CameraWorkerConnectionStack() {
            p_ = 0;
            for (int i = 0; i < 30; i++) {
                apCamWorkerCon_[i] = NULL;
            }
        }
        CameraWorkerConnection* getLast() {
            if (p_ == 0) {
                return NULL;
            } else {
                return apCamWorkerCon_[p_-1];
            }
        }
        void push(CameraWorkerConnection* prm_pCamWorkerCon) {
            if (p_ > 30-1) {
                throwGgafCriticalException("CameraWorkerConnectionStack::push("<<prm_pCamWorkerCon->getIdStr()<<") スタックを使い切りました。");
            }
            apCamWorkerCon_[p_] = prm_pCamWorkerCon;
            p_++;
        }
        CameraWorkerConnection* pop() {
            if (p_ == 0) {
                throwGgafCriticalException("CameraWorkerConnectionStack::pop() ポップしすぎです");
            } else {
                p_--;
                CameraWorkerConnection* r = apCamWorkerCon_[p_];
                apCamWorkerCon_[p_] = NULL;
                return r;
            }
        }
        void clear() {
            p_ = 0;
            for (int i = 0; i < 30; i++) {
                apCamWorkerCon_[i] = NULL;
            }
        }

        void dump() {
            _TRACE_("CameraWorkerConnectionStack p_="<<p_);
            for (int i = 0; i < 30; i++) {
                if (apCamWorkerCon_[i]) {
                    _TRACE_("apCamWorkerCon_["<<i<<"]="<<(apCamWorkerCon_[i]->getIdStr()));
                }
            }
        }
        ~CameraWorkerConnectionStack() {
            clear();
        }
    };


public:

    CameraWorker* pActiveCamWorker_;
    CameraWorkerManager* pCamWorkerManager_;
    World* pWorld_;
    CameraWorkerConnectionStack stack_CamWorkerCon_;

    Universe(const char* prm_name, Camera* prm_pCamera);

    void initialize() override;

    void processBehavior() override;

    void processJudgement() override;

    CameraWorker* switchCameraWork(const char* prm_pID);

    CameraWorker* undoCameraWork();

    void resetCameraWork();

    virtual ~Universe();
};

}
#endif /*UNIVERSE_H_*/
