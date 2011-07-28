#ifndef GGAFDX9STRINGBOARDACTOR_H_
#define GGAFDX9STRINGBOARDACTOR_H_
namespace GgafDx9Core {

/**
 * �����\���N���X .
 * GgafDx9BoardActor ���p�����A�����Z�b�g�e�N�X�`���[����
 * �����\���@�\��ǉ������A�N�^�[�ł��B<BR>
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
public:
    /** [r]�`�敶���� */
    char* _draw_string;
    /** [r]�����o�b�t�@(1024�Œ�) */
    char* _buf;
    /** [r]������ */
    int _len;
    /** [r]�`�敶���̃p�b�N���B(1�p�b�N = _pBoardSetModel->_set_num) */
    int _len_pack_num;
    /** [r]�ŏI�̃p�b�N�ŕ\�����Ȃ���΂Ȃ�Ȃ��������B*/
    int _remainder_len;

    /** [r/w]�e�����Ԋu(px) */
    pixcoord _aWidthPx[256];
    /** [r/w]�x�[�X�̂P������(px) */
    pixcoord _chr_width_px;
    GgafDx9StringAlign _align;
    coord _X_offset_align;

    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_model �����Z�b�g�e�N�X�`���̃��f����`ID
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

    /**
     * �`�敶�����X�V�ݒ� .
     * @param X �����X���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param Y �����Y���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param prm_str �`�敶����
     */
    virtual void update(coord X, coord Y, const char* prm_str, GgafDx9StringAlign prm_align = ALIGN_LEFT);

    /**
     * �`�敶�����X�V�ݒ�  .
     * @param X �����X���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param Y �����Y���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param prm_str �`�敶����
     */
    virtual void update(coord X, coord Y, char* prm_str, GgafDx9StringAlign prm_align = ALIGN_LEFT);

    /**
     * �`�敶�����X�V�ݒ�  .
     * @param X �����X���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param Y �����Y���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param Z �v���C�I���e�B(�l��������������O)
     * @param prm_str �`�敶����
     */
    virtual void update(coord X, coord Y, coord Z, const char* prm_str, GgafDx9StringAlign prm_align = ALIGN_LEFT);

    /**
     * �`�敶�����X�V�ݒ�  .
     * @param X �����X���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param Y �����Y���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param Z �v���C�I���e�B(�l��������������O)
     * @param prm_str �`�敶����
     */
    virtual void update(coord X, coord Y, coord Z, char* prm_str, GgafDx9StringAlign prm_align = ALIGN_LEFT);

    /**
     * �`�敶�����X�V�ݒ�  .
     * @param prm_str �`�敶����
     */
    virtual void update(const char* prm_str, GgafDx9StringAlign prm_align = ALIGN_LEFT);

    /**
     * �`�敶�����X�V�ݒ�  .
     * @param prm_str �`�敶����
     */
    virtual void update(char* prm_str, GgafDx9StringAlign prm_align = ALIGN_LEFT);




    virtual void processSettlementBehavior() override;

    virtual ~GgafDx9StringBoardActor();

};

}
#endif /*GGAFDX9STRINGBOARDACTOR_H_*/
