#ifndef UNIVERSE_H_
#define UNIVERSE_H_
namespace MyStg2nd {

//getParent getSub ������ �L���X�g�}�N���B
//���L�}�N���g�p����ɂ́A�I�u�W�F�N�g�̎��ʖ����A
//�N���X���̖�����"...Scene"�Ƃ������������苎�������̂ł��邱�Ƃ��O������ł�
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
 * ���̐��V�[�� .
 * �܂����̐�������܂����B<BR>
 * �{�N���X�́A���̐��̐U�镑�������������Ă��܂��B<BR>
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
                throwGgafCriticalException("CamWorkerStack::push("<<prm_pCameraWorkerCon->getIdStr()<<") �X�^�b�N���g���؂�܂����A��ӏ��ɓ����蔻�肪��߂��ł��B");
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
