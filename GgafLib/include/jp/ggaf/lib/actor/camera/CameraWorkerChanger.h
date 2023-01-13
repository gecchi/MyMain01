#ifndef GGAF_LIB_CAMERAWORKERCHANGER_H_
#define GGAF_LIB_CAMERAWORKERCHANGER_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/core/actor/MainActor.h"

namespace GgafLib {

#define CAM_WORKER_HISTORY_NUM (30)

/**
 * �J�����}���`�F���W���[ .
 * @version 1.00
 * @since 2019/03/2
 * @author Masatoshi Tsuge
 */
class CameraWorkerChanger : public GgafCore::MainActor {

public:
    class History {
    public:
        CameraWorkerConnection* _apCamWorkerConnection[CAM_WORKER_HISTORY_NUM];
        uint32_t _p;
        History();
        CameraWorkerConnection* getLast();
        void push(CameraWorkerConnection* prm_pCamWorkerCon);
        CameraWorkerConnection* pop();
        void dump();
        ~History();
    };

public:
    /** [r]���݂̃J�����}�� */
    GgafLib::CameraWorker* _pActiveCamWorker;
    /** [r]�J�����}���̃}�l�[�W���[ */
    CameraWorkerManager* _pCamWorkerManager;
    /** [r]�J�����}���̃X�^�b�N */
    History _stack_CamWorkerConnection;
    DefaultCamera* _pCamera;
public:
    CameraWorkerChanger(const char* prm_name, DefaultCamera* prm_pCamera);

    static bool initStatic();

    /**
     * �J�����}�������֐� .
     * �I�[�o�[���C�h���� prm_idstr �ɉ������J�����}���𐶐����鏈�����������Ă��������B
     * @param prm_idstr
     * @param prm_pConnector
     * @return
     */
    virtual CameraWorker* createCameraWorker(const char* prm_idstr, void* prm_pConnector) = 0;

    /**
     * ���݂̃J�����}����Ԃ� .
     * ������Ԃ́A�f�t�H���g�J�����}��(DefaultCamWorker)����l���܂��B
     * @return ���݂̃J�����}��
     */
    GgafLib::CameraWorker* getActiveCamWorker() {
        return _pActiveCamWorker;
    }
    /**
     * �J�����}����؂�ւ��� .
     * �����̃J�����}��ID�����߂ĂȂ�΁A�J�����}���P�l�ǉ����A������ɃJ�����̊������^���؂�ւ��܂��B <br>
     * �����̃J�����}��ID�����݊������̃J�����}���Ɠ���ID���w�肵���ꍇ�A�P�ɖ�������܂��B <br>
     * �����̃J�����}��ID�����݊������̃J�����}���Ƃ͈قȂ邪�A�ȑO�؂�ւ��ς݂�ID���������ꍇ�A�ȑO�̂��̃J�����}���ɐ؂�ւ��܂��B <br>
     * @param prm_pID �V�����J�����}������ID�i����ID�� CameraWorkerManager �Ɏ��O�o�^�v�j
     * @return �J�����}��ID
     */
    GgafLib::CameraWorker* changeCameraWork(const char* prm_pID);
    /**
     * ���݊������̃J�����}���A�؂�ւ��O�̃J�����}���ɖ߂��܂��B .
     * ���O�� changeCameraWork() ���P��ȏ���s���Ă����K�v������܂��B
     * @return ���X�����A�߂������̃J�����}��
     */
    GgafLib::CameraWorker* undoCameraWork();
    /**
     * �J�����}���B��|������B
     * ���� changeCameraWork() ���s���Ă��悤�ƁA�f�t�H���g�J�����}��(DefaultCamWorker)��
     * �P�l�����̏�Ԃɖ߂�܂��B
     */
    void cleanCamWorker();

    virtual void initialize() override;

    virtual void onActive() override {}

    virtual void processBehavior() override;

    virtual void processJudgement() override {}

    virtual void processDraw() override {}

    virtual void processFinal() override {}

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    virtual bool processHitChkLogic(GgafCore::Actor* prm_pOtherActor) override {
        return false;
    }

    virtual ~CameraWorkerChanger(); //�f�X�g���N�^
};

}
#endif /*GGAF_LIB_CAMERAWORKERCHANGER_H_*/
