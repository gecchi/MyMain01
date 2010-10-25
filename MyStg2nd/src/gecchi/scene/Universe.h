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

#ifdef pCAM
#undef pCAM
#endif
#define pCAM ((Camera*)GgafDx9Universe::_pCamera)
#define pCAM_WORKER (Universe::_pActiveCameraWorker)
/**
 * この世シーン .
 * まずこの世がありました。<BR>
 * 本クラスは、この世の振る舞い等を実装しています。<BR>
 */
class Universe : public GgafDx9LibStg::DefaultUniverse {

    class CameraWorkerStack {
    public:
        CameraWorker* _apCameraWorker[30];
        UINT32 _p;
        CameraWorkerStack() {
            _p = 0;
        }
        void push(CameraWorker* prm_pCameraWorker) {
            if (_p > 30-1) {
                throwGgafCriticalException("CameraWorkerStack::push("<<prm_pCameraWorker->getName()<<") スタックを使い切りました。");
            }
            _apCameraWorker[_p] = prm_pCameraWorker;
            _p++;
        }
        CameraWorker* pop() {
            if (_p == 0) {
                return NULL;
            } else {
                _p--;
                return _apCameraWorker[_p];
            }
        }
        void clear() {
            _p = 0;
        }
        ~CameraWorkerStack() {
            clear();
        }
    };


public:

    static CameraWorker* _pActiveCameraWorker;
    CameraWorkerManager* _pCameraWorkerManager;
    World* _pWorld;
    CameraWorkerStack _stack_CameraWorker;

    Universe(const char* prm_name, GgafDx9Core::GgafDx9Camera* prm_pCamera);

    void initialize() override;

    void processBehavior() override;

    void processJudgement() override;

    void pushCameraWork(const char* prm_pID);

    void popCameraWork();



    virtual ~Universe();
};

}
#endif /*UNIVERSE_H_*/
