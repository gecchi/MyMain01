#ifndef STAGE02PARTCONTROLLER_H_
#define STAGE02PARTCONTROLLER_H_
namespace MyStg2nd {

/**
 * �X�e�[�W�P�R���g���[���[ .
 * @version 1.00
 * @since 2010/08/18
 * @author Masatoshi Tsuge
 */
class Stage02PartController : public GgafLib::DefaultScene {

    GgafDxCore::GgafDxBgm* _bgm_st1;

public:

    frame _frame_prog_fainal;

    Stage02PartController(const char* prm_name);
    /**
     * ��������
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual void processFinal() override;

    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override;

    virtual ~Stage02PartController();
};

}
#endif /*STAGE02PARTCONTROLLER_H_*/