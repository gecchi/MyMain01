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


namespace VioletVreath {
#define connectCameraWorkerManager(X) ((VioletVreath::CameraWorkerConnection*)P_UNIVERSE->pCameraWorkerManager_->connect(X))


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
        CameraWorkerConnection* apCameraWorkerCon_[30];
        UINT32 p_;
        CameraWorkerConnectionStack() {
            p_ = 0;
            for (int i = 0; i < 30; i++) {
                apCameraWorkerCon_[i] = NULL;
            }
        }
        CameraWorkerConnection* getLast() {
            if (p_ == 0) {
                return NULL;
            } else {
                return apCameraWorkerCon_[p_-1];
            }
        }
        void push(CameraWorkerConnection* prm_pCameraWorkerCon) {
            if (p_ > 30-1) {
                throwGgafCriticalException("CameraWorkerConnectionStack::push("<<prm_pCameraWorkerCon->getIdStr()<<") スタックを使い切りました。");
            }
            apCameraWorkerCon_[p_] = prm_pCameraWorkerCon;
            p_++;
        }
        CameraWorkerConnection* pop() {
            if (p_ == 0) {
                throwGgafCriticalException("CameraWorkerConnectionStack::pop() ポップしすぎです");
            } else {
                p_--;
                CameraWorkerConnection* r = apCameraWorkerCon_[p_];
                apCameraWorkerCon_[p_] = NULL;
                return r;
            }
        }
        void clear() {
            p_ = 0;
            for (int i = 0; i < 30; i++) {
                apCameraWorkerCon_[i] = NULL;
            }
        }

        void dump() {
            _TRACE_("CameraWorkerConnectionStack p_="<<p_);
            for (int i = 0; i < 30; i++) {
                if (apCameraWorkerCon_[i]) {
                    _TRACE_("apCameraWorkerCon_["<<i<<"]="<<(apCameraWorkerCon_[i]->getIdStr()));
                }
            }
        }
        ~CameraWorkerConnectionStack() {
            clear();
        }
    };


public:

    CameraWorker* pActiveCameraWorker_;
    CameraWorkerManager* pCameraWorkerManager_;
    World* pWorld_;
    CameraWorkerConnectionStack stack_CameraWorkerCon_;

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
