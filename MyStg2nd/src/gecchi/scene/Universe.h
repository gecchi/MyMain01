#ifndef UNIVERSE_H_
#define UNIVERSE_H_
namespace MyStg2nd {

//getParent getSub そして キャストマクロ。
//下記マクロ使用するには、オブジェクトの識別名が、
//クラス名の末尾の"...Scene"という文字列を取り去ったものであることが前提条件です
#define getParentScene(X) ((X##Scene*)getParent(#X))
#define getSubScene(X) ((X##Scene*)getSub(#X))
#define getParentActor(X) ((X##Actor*)getParent(#X))
#define getSubActor(X) ((X##Actor*)getSub(#X))

/**
 * この世シーン .
 * まずこの世がありました。<BR>
 * 本クラスは、この世の振る舞い等を実装しています。<BR>
 */
class Universe : public GgafDx9LibStg::DefaultUniverse {

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
                throwGgafCriticalException("CameraWorkerConnectionStack::push("<<prm_pCameraWorkerCon->getIdStr()<<") スタックを使い切りました。");
            }
            _apCameraWorkerCon[_p] = prm_pCameraWorkerCon;
            _p++;
        }
        CameraWorkerConnection* pop() {
            if (_p == 0) {
                throwGgafCriticalException("CameraWorkerConnectionStack::pop() ポップしすぎです");
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

    Universe(const char* prm_name, GgafDx9Core::GgafDx9Camera* prm_pCamera);

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
