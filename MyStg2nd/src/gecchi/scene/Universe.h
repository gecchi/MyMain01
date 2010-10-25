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

    class CamWorkerConStack {
    public:
        GgafCore::GgafResourceConnection<CameraWorker>* _apCameraWorkerCon[30];
        UINT32 _p;
        CamWorkerConStack() {
            _p = 0;
        }
        void push(GgafCore::GgafResourceConnection<CameraWorker>* prm_pCameraWorkerCon) {
            if (_p > 30-1) {
                throwGgafCriticalException("CamWorkerStack::push("<<prm_pCameraWorkerCon->getIdStr()<<") スタックを使い切りました、一箇所に当たり判定が塊過ぎです。");
            }
            _apCameraWorkerCon[_p] = prm_pCameraWorkerCon;
            _p++;
        }
        GgafCore::GgafResourceConnection<CameraWorker>* pop() {
            if (_p == 0) {
                return NULL;
            } else {
                _p--;
                return _apCameraWorkerCon[_p];
            }
        }
        void clear() {
            _p = 0;
        }
        ~CamWorkerConStack() {
            clear();
        }
    };


public:

    static CameraWorker* _pActiveCameraWorker;
    CameraWorkerManager* _pCameraWorkerManager;
    World* _pWorld;
    CamWorkerConStack _stack_CameraWorkerCon;

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
