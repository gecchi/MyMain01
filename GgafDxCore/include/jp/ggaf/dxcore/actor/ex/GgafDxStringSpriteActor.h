#ifndef GGAFDXSTRINGSPRITEACTOR_H_
#define GGAFDXSTRINGSPRITEACTOR_H_
namespace GgafDxCore {

/**
 * ���W���ϊ������\���N���X�i���ݍ쐬���ŁA���g�p�I�j
 */
class GgafDxStringSpriteActor : public GgafDxSpriteSetActor {
    /**
     * �I�[�o�[���C�h�s�� .
     */
//    virtual void processSettlementBehavior() override;

public:
    /** [r]�`�敶���� */
    char* _draw_string;
    /** [r]�����o�b�t�@(1024�Œ�) */
    char* _buf;
    /** [r]������ */
    int _len;
    /** [r]�`�敶���̃p�b�N���B(1�p�b�N = _pSpriteSetModel->_set_num) */
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

    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_model �����Z�b�g�e�N�X�`���̃��f����`ID
     * @return
     */
    GgafDxStringSpriteActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat);

    virtual void onCreateModel() override;

    virtual void processDraw() override;

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
     * @param prm_valign VALIGN_TOP:Y���W�͕����̍����̏�ӂ��Ӗ�����^VALIGN_MIDDLE:Y���W�͕����̍����̐^�񒆂��Ӗ�����^VALIGN_BOTTOM:Y���W�͕����̍����̒�ӂ��Ӗ�����
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
     * @param prm_valign VALIGN_TOP:Y���W�͕����̍����̏�ӂ��Ӗ�����^VALIGN_MIDDLE:Y���W�͕����̍����̐^�񒆂��Ӗ�����^VALIGN_BOTTOM:Y���W�͕����̍����̒�ӂ��Ӗ�����
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
     * @param prm_valign VALIGN_TOP:Y���W�͕����̍����̏�ӂ��Ӗ�����^VALIGN_MIDDLE:Y���W�͕����̍����̐^�񒆂��Ӗ�����^VALIGN_BOTTOM:Y���W�͕����̍����̒�ӂ��Ӗ�����
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
     * @param prm_valign VALIGN_TOP:Y���W�͕����̍����̏�ӂ��Ӗ�����^VALIGN_MIDDLE:Y���W�͕����̍����̐^�񒆂��Ӗ�����^VALIGN_BOTTOM:Y���W�͕����̍����̒�ӂ��Ӗ�����
     */
    virtual void update(coord X, coord Y, coord Z, char* prm_str,
                        GgafDxAlign prm_align,
                        GgafDxValign prm_valign);
    /**
     * �`�敶�����X�V�ݒ�  .
     * @param prm_str �`�敶����
     * @param prm_align ALIGN_LEFT:X���W�͍��[���Ӗ�����^ALIGN_CENTER:X���W�͕�����̐^�񒆁^ALIGN_RIGHT:X���W�͉E�[���Ӗ�����
     * @param prm_valign VALIGN_TOP:Y���W�͕����̍����̏�ӂ��Ӗ�����^VALIGN_MIDDLE:Y���W�͕����̍����̐^�񒆂��Ӗ�����^VALIGN_BOTTOM:Y���W�͕����̍����̒�ӂ��Ӗ�����
     */
    virtual void update(const char* prm_str,
                        GgafDxAlign prm_align,
                        GgafDxValign prm_valign);
    /**
     * �`�敶�����X�V�ݒ�  .
     * @param prm_str �`�敶����
     * @param prm_align ALIGN_LEFT:X���W�͍��[���Ӗ�����^ALIGN_CENTER:X���W�͕�����̐^�񒆁^ALIGN_RIGHT:X���W�͉E�[���Ӗ�����
     * @param prm_valign VALIGN_TOP:Y���W�͕����̍����̏�ӂ��Ӗ�����^VALIGN_MIDDLE:Y���W�͕����̍����̐^�񒆂��Ӗ�����^VALIGN_BOTTOM:Y���W�͕����̍����̒�ӂ��Ӗ�����
     */
    virtual void update(char* prm_str,
                        GgafDxAlign prm_align,
                        GgafDxValign prm_valign);

    /**
     * �`�敶���̃A���C�������g��ݒ肷��  .
     * @param prm_align ALIGN_LEFT:X���W�͍��[���Ӗ�����^ALIGN_CENTER:X���W�͕�����̐^�񒆁^ALIGN_RIGHT:X���W�͉E�[���Ӗ�����
     * @param prm_valign VALIGN_TOP:Y���W�͕����̍����̏�ӂ��Ӗ�����^VALIGN_MIDDLE:Y���W�͕����̍����̐^�񒆂��Ӗ�����^VALIGN_BOTTOM:Y���W�͕����̍����̒�ӂ��Ӗ�����
     */
    virtual void setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign) override;

    virtual ~GgafDxStringSpriteActor();

};

}
#endif /*GGAFDXSTRINGSPRITEACTOR_H_*/
