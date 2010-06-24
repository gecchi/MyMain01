#ifndef GGAFDX9STRINGBOARDACTOR_H_
#define GGAFDX9STRINGBOARDACTOR_H_
namespace GgafDx9Core {

/**
 * �����\���N���X(���W�ϊ��ς�).
 * GgafDx9BoardActor ���p�����A�����Z�b�g�e�N�X�`���[���當���\���@�\��ǉ������A�N�^�[�ł��B
 * �����\���ƌ����Ă������e�N�X�`����UV��؂�ւ��邾���ł��B
 * @version 1.00
 * @since 2009/04/09
 * @author Masatoshi Tsuge
 */
class GgafDx9StringBoardActor : public GgafDx9BoardSetActor {
    /** ������50�����܂� */
    char* _buf;
    char* _draw_string;
    int _len;
public:
    /** [rw]�e�����Ԋu(px) */
    static float _aWidthPx[256];


    /**
     *
     * @param prm_name
     * @param prm_model �����Z�b�g�e�N�X�`���̃��f��
     * @return
     */
    GgafDx9StringBoardActor(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override;

    virtual void processDraw() override;

    virtual void processAfterDraw() override {
    }

    virtual bool processHitChkLogic(GgafCore::GgafActor* prm_pOtherActor) {
        return false;
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) {
    }


    virtual void update(float prm_x, float prm_y, const char* prm_str);
    virtual void update(float prm_x, float prm_y, char* prm_str);
    virtual void update(float prm_x, float prm_y, float prm_z, const char* prm_str);
    virtual void update(float prm_x, float prm_y, float prm_z, char* prm_str);
    virtual void update(const char* prm_str);
    virtual void update(char* prm_str);

    virtual ~GgafDx9StringBoardActor();

};

}
#endif /*GGAFDX9STRINGBOARDACTOR_H_*/
