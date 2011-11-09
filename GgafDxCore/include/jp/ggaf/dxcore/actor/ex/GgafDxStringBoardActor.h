#ifndef GGAFDXSTRINGBOARDACTOR_H_
#define GGAFDXSTRINGBOARDACTOR_H_
namespace GgafDxCore {

/**
 * �����\���N���X .
 * GgafDxBoardActor ���p�����A�����Z�b�g�e�N�X�`���[����
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
class GgafDxStringBoardActor : public GgafDxBoardSetActor {

    /**
     * �I�[�o�[���C�h�s�� .
     */
    virtual void processSettlementBehavior() override;

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

    /** [r/w]�x�[�X�̂P������(px) */
    pixcoord _chr_width_px;
    /** [r/w]�x�[�X�̂P��������(px) */
    pixcoord _chr_height_px;
    /** [r/w]�e�����Ԋu(px) */
    pixcoord _aWidthPx[256];


    pixcoord _width_len_px;
    coord _X_offset_align;

    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_model �����Z�b�g�e�N�X�`���̃��f����`ID
     * @return
     */
    GgafDxStringBoardActor(const char* prm_name, const char* prm_model);

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
    virtual void update(coord X, coord Y, const char* prm_str);
    /**
     * �`�敶�����X�V�ݒ�  .
     * @param X �����X���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param Y �����Y���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param prm_str �`�敶����
     */
    virtual void update(coord X, coord Y, char* prm_str);

    /**
     * �`�敶�����X�V�ݒ�  .
     * @param X �����X���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param Y �����Y���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param Z �v���C�I���e�B(�l��������������O)
     * @param prm_str �`�敶����
     */
    virtual void update(coord X, coord Y, coord Z, const char* prm_str);
    /**
     * �`�敶�����X�V�ݒ�  .
     * @param X �����X���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param Y �����Y���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param Z �v���C�I���e�B(�l��������������O)
     * @param prm_str �`�敶����
     */
    virtual void update(coord X, coord Y, coord Z, char* prm_str);
    /**
     * �`�敶�����X�V�ݒ�  .
     * @param prm_str �`�敶����
     */
    virtual void update(const char* prm_str);
    /**
     * �`�敶�����X�V�ݒ�  .
     * @param prm_str �`�敶����
     */
    virtual void update(char* prm_str);
















    /**
     * �`�敶�����X�V�ݒ� .
     * @param X �����X���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param Y �����Y���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param prm_str �`�敶����
     * @param prm_align ALIGN_LEFT:X���W�͍��[���Ӗ�����^ALIGN_CENTER:X���W�͕�����̐^�񒆁^ALIGN_RIGHT:X���W�͉E�[���Ӗ�����
     */
    virtual void update(coord X, coord Y, const char* prm_str,
                        GgafDxAlign prm_align,
                        GgafDxValign prm_valign);
    /**
     * �`�敶�����X�V�ݒ�  .
     * @param X �����X���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param Y �����Y���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param prm_str �`�敶����
     * @param prm_align ALIGN_LEFT:X���W�͍��[���Ӗ�����^ALIGN_CENTER:X���W�͕�����̐^�񒆁^ALIGN_RIGHT:X���W�͉E�[���Ӗ�����
     */
    virtual void update(coord X, coord Y, char* prm_str,
                        GgafDxAlign prm_align,
                        GgafDxValign prm_valign);

    /**
     * �`�敶�����X�V�ݒ�  .
     * @param X �����X���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param Y �����Y���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param Z �v���C�I���e�B(�l��������������O)
     * @param prm_str �`�敶����
     * @param prm_align ALIGN_LEFT:X���W�͍��[���Ӗ�����^ALIGN_CENTER:X���W�͕�����̐^�񒆁^ALIGN_RIGHT:X���W�͉E�[���Ӗ�����
     */
    virtual void update(coord X, coord Y, coord Z, const char* prm_str,
                        GgafDxAlign prm_align,
                        GgafDxValign prm_valign);
    /**
     * �`�敶�����X�V�ݒ�  .
     * @param X �����X���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param Y �����Y���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param Z �v���C�I���e�B(�l��������������O)
     * @param prm_str �`�敶����
     * @param prm_align ALIGN_LEFT:X���W�͍��[���Ӗ�����^ALIGN_CENTER:X���W�͕�����̐^�񒆁^ALIGN_RIGHT:X���W�͉E�[���Ӗ�����
     */
    virtual void update(coord X, coord Y, coord Z, char* prm_str,
                        GgafDxAlign prm_align,
                        GgafDxValign prm_valign);
    /**
     * �`�敶�����X�V�ݒ�  .
     * @param prm_str �`�敶����
     * @param prm_align ALIGN_LEFT:X���W�͍��[���Ӗ�����^ALIGN_CENTER:X���W�͕�����̐^�񒆁^ALIGN_RIGHT:X���W�͉E�[���Ӗ�����
     */
    virtual void update(const char* prm_str,
                        GgafDxAlign prm_align,
                        GgafDxValign prm_valign);
    /**
     * �`�敶�����X�V�ݒ�  .
     * @param prm_str �`�敶����
     * @param prm_align ALIGN_LEFT:X���W�͍��[���Ӗ�����^ALIGN_CENTER:X���W�͕�����̐^�񒆁^ALIGN_RIGHT:X���W�͉E�[���Ӗ�����
     */
    virtual void update(char* prm_str,
                        GgafDxAlign prm_align,
                        GgafDxValign prm_valign);

    virtual void setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign) override;


    virtual ~GgafDxStringBoardActor();

};

}
#endif /*GGAFDXSTRINGBOARDACTOR_H_*/