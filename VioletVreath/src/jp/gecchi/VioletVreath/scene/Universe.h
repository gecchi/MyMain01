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
#define connectCameraWorkerManager(X) ((VioletVreath::CameraWorkerConnection*)P_UNIVERSE->_pCameraWorkerManager->connect(X))


/**
 * ��̓I�Ȃ��̐� .
 * �{�N���X�́A���̐��̐U�镑�����������܂��B<BR>
 * ��ɐ��E(World)���f���o���J����(Camera)���������A���̃J������
 * ��܂��Ȑ��䃁�\�b�h������܂��B<BR>
 * @version 1.00
 * @since 2009/04/24
 * @author Masatoshi Tsuge
 */
class Universe : public GgafLib::DefaultUniverse {

    class CameraWorkerConnectionStack {
    public:
        CameraWorkerConnection* _apCameraWorkerCon[30];
        UINT32 _p;
        CameraWorkerConnectionStack() {
            _p = 0;
            for (int i = 0; i < 30; i++) {
                _apCameraWorkerCon[i] = NULL;
            }
        }
        CameraWorkerConnection* getLast() {
            if (_p == 0) {
                return NULL;
            } else {
                return _apCameraWorkerCon[_p-1];
            }
        }
        void push(CameraWorkerConnection* prm_pCameraWorkerCon) {
            if (_p > 30-1) {
                throwGgafCriticalException("CameraWorkerConnectionStack::push("<<prm_pCameraWorkerCon->getIdStr()<<") �X�^�b�N���g���؂�܂����B");
            }
            _apCameraWorkerCon[_p] = prm_pCameraWorkerCon;
            _p++;
        }
        CameraWorkerConnection* pop() {
            if (_p == 0) {
                throwGgafCriticalException("CameraWorkerConnectionStack::pop() �|�b�v�������ł�");
            } else {
                _p--;
                CameraWorkerConnection* r = _apCameraWorkerCon[_p];
                _apCameraWorkerCon[_p] = NULL;
                return r;
            }
        }
        void clear() {
            _p = 0;
            for (int i = 0; i < 30; i++) {
                _apCameraWorkerCon[i] = NULL;
            }
        }

        void dump() {
            _TRACE_("CameraWorkerConnectionStack _p="<<_p);
            for (int i = 0; i < 30; i++) {
                if (_apCameraWorkerCon[i]) {
                    _TRACE_("_apCameraWorkerCon["<<i<<"]="<<(_apCameraWorkerCon[i]->getIdStr()));
                }
            }
        }
        ~CameraWorkerConnectionStack() {
            clear();
        }
    };


public:

    CameraWorker* _pActiveCameraWorker;
    CameraWorkerManager* _pCameraWorkerManager;
    World* _pWorld;
    CameraWorkerConnectionStack _stack_CameraWorkerCon;

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
