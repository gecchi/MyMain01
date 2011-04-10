#ifndef GGAFDX9STRINGBOARDACTOR_H_
#define GGAFDX9STRINGBOARDACTOR_H_
namespace GgafDx9Core {

/**
 * �����\���N���X(���W�ϊ��ς�).
 *  * GgafDx9BoardActor ���p�����A�����Z�b�g�e�N�X�`���[����
 *  �����\���@�\��ǉ������A�N�^�[�ł��B<BR>
 * ���̂悤�ȃe�N�X�`���ł��邱�Ƃ��O��B�i�����ۂ̉摜�͌r�������ł��j<BR>
 * <code><pre>
 * ����������������������������������
 * ���@���I���h�������������������f��
 * ����������������������������������
 * ���i���j�������{���C���|���D���^��
 * ����������������������������������
 * ���O���P���Q���R���S���T���U���V��
 * ����������������������������������
 * ���W���X���F���G���������������H��
 * ����������������������������������
 * �������`���a���b���c���d���e���f��
 * ����������������������������������
 * ���g���h���i���j���k���l���m���n��
 * ����������������������������������
 * ���o���p���q���r���s���t���u���v��
 * ����������������������������������
 * ���w���x���y���m���_���n���O���Q��
 * ����������������������������������
 * </pre></code>
 * �����\���ƌ����Ă�UV��؂�ւ��ĘA���\���邾���B
 * @version 1.00
 * @since 2009/04/09
 * @author Masatoshi Tsuge
 */
class GgafDx9StringBoardActor : public GgafDx9BoardSetActor {

    /** �`�敶���� */
    char* _draw_string;
    /** �����o�b�t�@(1024�Œ�) */
    char* _buf;
    /** ������ */
    int _len;

public:
    /** [rw]�e�����Ԋu(px) */
    int _aWidthPx[256];
    /** [r]�x�[�X�̂P������(px) */
    int _chr_width;

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
    virtual void update(float prm_x, float prm_y, float prm_z);
    virtual void update(float prm_x, float prm_y);

    virtual ~GgafDx9StringBoardActor();

};

}
#endif /*GGAFDX9STRINGBOARDACTOR_H_*/
