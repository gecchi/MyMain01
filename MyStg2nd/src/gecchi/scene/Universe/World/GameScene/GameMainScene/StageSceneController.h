#ifndef STAGESCENECONTROLLER_H_
#define STAGESCENECONTROLLER_H_


namespace MyStg2nd {

/**
 * �Q�[�����C���V�[���̃R���g���[���[ .
 * ��Ȏd���̓��C���X�e�[�W�̐؂�ւ��A
 * �����N�A�b�v�V�[���̍����ł��B
 * @version 1.00
 * @since 2011/07/17
 * @author Masatoshi Tsuge
 */
class StageSceneController : public GgafLib::DefaultScene {

public:
//    static StageSceneController* _pStageSceneController;

    char _buf[60];

    StageScene* _pSceneMainCannnel;
    TransitStage* _pTransitStage;
//��������
    int _loop;
    int _stage;
    StageSceneController(const char* prm_name);


    void onReset() override;
    void readyStage(int prm_stage);
    void initialize() override;
    void processBehavior() override;
    void processFinal() override;
    void onCatchEvent(UINT32 prm_no, void* prm_pSource) override;
    virtual ~StageSceneController();

};

}
#endif /*STAGESCENECONTROLLER_H_*/
