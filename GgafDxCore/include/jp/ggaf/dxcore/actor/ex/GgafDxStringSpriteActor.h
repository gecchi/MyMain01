#ifndef GGAFDXSTRINGSPRITEACTOR_H_
#define GGAFDXSTRINGSPRITEACTOR_H_
#include "jp/ggaf/dxcore/actor/GgafDxSpriteSetActor.h"

namespace GgafDxCore {

/**
 * �����\���N���X .
 * GgafDxSpriteSetActor ���p�����A�����Z�b�g�e�N�X�`���[����
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
 * TODO:GgafDxStringBoardActor�Ƌ��ʉ��������E�E�E
 * @version 1.00
 * @since 2009/04/09
 * @author Masatoshi Tsuge
 */
class GgafDxStringSpriteActor : public GgafDxSpriteSetActor {

public:
    /** [r/w]�p�^�[���ԍ�0�Ƃ��镶�� */
    int _chr_ptn_zero;
    /** [r]�`�敶���� */
    char* _draw_string;
    /** [r]�����o�b�t�@(1024�Œ�) */
    char* _buf;
    /** [r]������ */
    int _len;
    /** [r/w]�x�[�X�̂P������(px) */
    pixcoord _chr_width_px;
    /** [r/w]�x�[�X�̂P��������(px) */
    pixcoord _chr_height_px;
    /** [r/w]�e�����Ԋu(px) */
    pixcoord _aWidthPx[256];
    /** [r]�����o�b�t�@�̍s�P�ʂ̕�(px) */
    pixcoord _aWidth_line_px[256];
    /** [r]�����o�b�t�@���s�� */
    int _nn;

public:
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
     * @param X X���W
     * @param Y Y���W
     * @param prm_str �`�敶����
     */
    virtual void update(coord X, coord Y, const char* prm_str);
    /**
     * �`�敶�����X�V�ݒ�  .
     * @param X X���W
     * @param Y Y���W
     * @param prm_str �`�敶����
     */
    virtual void update(coord X, coord Y, char* prm_str);

    /**
     * �`�敶�����X�V�ݒ�  .
     * @param X X���W
     * @param Y Y���W
     * @param Z Z���W
     * @param prm_str �`�敶����
     */
    virtual void update(coord X, coord Y, coord Z, const char* prm_str);
    /**
     * �`�敶�����X�V�ݒ�  .
     * @param X X���W
     * @param Y Y���W
     * @param Z Z���W
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
     * @param X X���W
     * @param Y Y���W
     * @param prm_str �`�敶����
     * @param prm_align ALIGN_LEFT:X���W�͍��[���Ӗ�����^ALIGN_CENTER:X���W�͕�����̐^�񒆁^ALIGN_RIGHT:X���W�͉E�[���Ӗ�����
     * @param prm_valign VALIGN_TOP:Y���W�͕����̍����̏�ӂ��Ӗ�����^VALIGN_MIDDLE:Y���W�͕����̍����̐^�񒆂��Ӗ�����^VALIGN_BOTTOM:Y���W�͕����̍����̒�ӂ��Ӗ�����
     */
    virtual void update(coord X, coord Y, const char* prm_str,
                        GgafDxAlign prm_align,
                        GgafDxValign prm_valign);
    /**
     * �`�敶�����X�V�ݒ�  .
     * @param X X���W
     * @param Y Y���W
     * @param prm_str �`�敶����
     * @param prm_align ALIGN_LEFT:X���W�͍��[���Ӗ�����^ALIGN_CENTER:X���W�͕�����̐^�񒆁^ALIGN_RIGHT:X���W�͉E�[���Ӗ�����
     * @param prm_valign VALIGN_TOP:Y���W�͕����̍����̏�ӂ��Ӗ�����^VALIGN_MIDDLE:Y���W�͕����̍����̐^�񒆂��Ӗ�����^VALIGN_BOTTOM:Y���W�͕����̍����̒�ӂ��Ӗ�����
     */
    virtual void update(coord X, coord Y, char* prm_str,
                        GgafDxAlign prm_align,
                        GgafDxValign prm_valign);

    /**
     * �`�敶�����X�V�ݒ�  .
     * @param X X���W
     * @param Y Y���W
     * @param Z Z���W
     * @param prm_str �`�敶����
     * @param prm_align ALIGN_LEFT:X���W�͍��[���Ӗ�����^ALIGN_CENTER:X���W�͕�����̐^�񒆁^ALIGN_RIGHT:X���W�͉E�[���Ӗ�����
     * @param prm_valign VALIGN_TOP:Y���W�͕����̍����̏�ӂ��Ӗ�����^VALIGN_MIDDLE:Y���W�͕����̍����̐^�񒆂��Ӗ�����^VALIGN_BOTTOM:Y���W�͕����̍����̒�ӂ��Ӗ�����
     */
    virtual void update(coord X, coord Y, coord Z, const char* prm_str,
                        GgafDxAlign prm_align,
                        GgafDxValign prm_valign);
    /**
     * �`�敶�����X�V�ݒ�  .
     * @param X X���W
     * @param Y Y���W
     * @param Z Z���W
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

    virtual ~GgafDxStringSpriteActor();

};

}
#endif /*GGAFDXSTRINGSPRITEACTOR_H_*/
