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

    class CameraWorkerStack {
    public:
        CameraWorker* _apCameraWorker[30];
        UINT32 _p;
        CameraWorkerStack() {
            _p = 0;
        }
        void push(CameraWorker* prm_pCameraWorker) {
            if (_p > 30-1) {
                throwGgafCriticalException("CameraWorkerStack::push("<<prm_pCameraWorker->getName()<<") �X�^�b�N���g���؂�܂����B");
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
