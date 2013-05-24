#ifndef UNIVERSE_H_
#define UNIVERSE_H_
#include "jp/ggaf/lib/scene/DefaultUniverse.h"

#include "jp/gecchi/VioletVreath/actor/Camera.h"
#include "jp/gecchi/VioletVreath/manager/CameraWorkerManager.h"
#include "jp/gecchi/VioletVreath/manager/CameraWorkerConnection.h"

#ifdef P_UNIVERSE
    #ifdef P_CAM
        #undef P_CAM
    #endif
    #define P_CAM ((VioletVreath::Camera*)(P_UNIVERSE->_pCamera))
#else
    #error P_UNIVERSE isnt define
#endif

/**
 * ���̐����ێ����� CameraWorkerManager �ɐڑ����A�R�l�N�V�������擾�B
 * X�F���ʕ�����iCameraWorkerManager::processCreateResource(char* prm_idstr, void* prm_pConnector) �� prm_idstr �ɓn��)
 * �܂��ACameraWorkerManager::processCreateResource(char* prm_idstr, void* prm_pConnector) �� prm_p �ɂ� nullptr ���Z�b�g����Ă���B
 */
#define connectToCameraWorkerManager(X) ((VioletVreath::CameraWorkerConnection*)P_UNIVERSE->pCamWorkerManager_->connect((X), this))


namespace VioletVreath {

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
        CameraWorkerConnection* apCamWorkerConnection_[30];
        uint32_t p_;
        CameraWorkerConnectionStack();
        CameraWorkerConnection* getLast();
        void push(CameraWorkerConnection* prm_pCamWorkerCon);
        CameraWorkerConnection* pop();
        void clear();
        void dump();
        ~CameraWorkerConnectionStack();
    };


public:
    /** [r]���݂̃J�����}�� */
    CameraWorker* pActiveCamWorker_;
    /** [r]�J�����}���̃}�l�[�W���[ */
    CameraWorkerManager* pCamWorkerManager_;
    /** [r]�J�����}���̃X�^�b�N */
    CameraWorkerConnectionStack stack_CamWorkerConnection_;
    /** [r]���E */
    World* pWorld_;

public:
    Universe(const char* prm_name, Camera* prm_pCamera);

    void initialize() override;

    void processBehavior() override;

    void processJudgement() override;

    /**
     * ���݂̃J�����}����Ԃ� .
     * ������Ԃ́A�f�t�H���g�J�����}��(DefaultCamWorker)����l���܂��B
     * @return ���݂̃J�����}��
     */
    CameraWorker* getActiveCamWorker() {
        return pActiveCamWorker_;
    }

    /**
     * �J�����}�����ꎞ�I�ɐ؂�ւ��� .
     * �V�����J�����}�����P�l�ǉ����A������ɃJ�����̎哱����؂�ւ��܂��B
     * �Ȍ�AundoCameraWork() �����s�����܂ł��̂܂܂ł��B
     * @param prm_pID �V�����J�����}������ID�i����ID�� CameraWorkerManager �Ɏ��O�o�^�v�j
     * @return �V�����J�����}��
     */
    CameraWorker* switchCameraWork(const char* prm_pID);

    /**
     * ���݂̃J�����}����r�����A��O�̃J�����}���ɖ߂��B .
     * ���O�� switchCameraWork() ���P��ȏ���s���Ă����K�v������܂��B
     * @return ���X�����A�߂������̃J�����}��
     */
    CameraWorker* undoCameraWork();

    /**
     * �J�����}�������Z�b�g����B
     * ���� switchCameraWork() ���s���Ă��悤�ƁA�f�t�H���g�J�����}��(DefaultCamWorker)��
     * �P�l�����̏�Ԃɖ߂�܂��B
     */
    void resetCamWorker();

    virtual ~Universe();
};

}
#endif /*UNIVERSE_H_*/
