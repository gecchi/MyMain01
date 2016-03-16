#ifndef GGAFLIB_FONTBOARDACTOR_H_
#define GGAFLIB_FONTBOARDACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxMassBoardActor.h"

namespace GgafLib {

/**
 * ���W�ϊ��ςݔ|�������\�� .
 * @version 1.00
 * @since 2016/02/25
 * @author Masatoshi Tsuge
 */
class FontBoardActor : public GgafDxCore::GgafDxMassBoardActor {

protected:
    struct VERTEX_instancedata {
        float px_x, px_y, depth_z;         // : TEXCOORD1
        float offset_u, offset_v, alpha;   // : TEXCOORD2
    };
    static VERTEX_instancedata _aInstancedata[];
    static void createVertexInstaceData(GgafDxCore::GgafDxMassModel::VertexInstaceDataInfo* out_info);

public:
    /** [r/w]�p�^�[���ԍ�0�Ƃ��镶�� */
    int _chr_ptn_zero;
    /** [r/w]�\���s�v�󔒂Ƃ��镶��(�w�肷��ƕ`�敶��������) */
    int _chr_blank;
    /** [r]�`�敶���� */
    int* _draw_string;
    /** [r]�󂯓���\�ȕ�����(�����o�b�t�@�̒���) */
    int _max_len;
    /** [r]�����o�b�t�@ */
    int* _buf;
    struct InstacePart {
        float px_x;
        float px_y;
        float offset_u;
        float offset_v;
    };
    InstacePart* _paInstacePart;
    /** [r]������ */
    int _len;
    /** [r]�`�敶�����i���s�Ƌ󔒂��������l�j*/
    int _draw_chr_num;
    /** [r/w]�x�[�X�̂P������(px) */
    pixcoord _chr_width_px;
    /** [r/w]�x�[�X�̂P��������(px) */
    pixcoord _chr_height_px;
    /** [r/w]�e�����Ԋu(px) */
    pixcoord _aWidthPx[256];
    /** [r]�����o�b�t�@�̕�����̍s�P�ʂ̕�(px) */
    pixcoord _aWidth_line_px[1024];
    /** [r]�����o�b�t�@�̕�����̍s�� */
    int _nn;

    /**
     * �����o�b�t�@���������̒���8�̔{���̐؂�グ�ɕύX .
     * @param prm_max_len �V�����o�b�t�@��
     */
    void chengeBufferLen(int prm_max_len);

public:
    /**
     * �`�敶�����X�V�ݒ� .
     * @param X X���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param Y Y���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param prm_str �`�敶����
     */
    virtual void update(coord X, coord Y, const char* prm_str);

    /**
     * �`�敶�����X�V�ݒ�  .
     * @param X X���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param Y Y���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param Z �v���C�I���e�B(�l��������������O)
     * @param prm_str �`�敶����
     */
    virtual void update(coord X, coord Y, coord Z, const char* prm_str);
    /**
     * �`�敶�����X�V�ݒ�  .
     * @param prm_str �`�敶����
     */
    virtual void update(const char* prm_str);

    /**
     * �`�敶�����X�V�ݒ� .
     * @param X X���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param Y Y���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param prm_str �`�敶����
     * @param prm_align ALIGN_LEFT:X���W�͕�����̍��[�^ALIGN_CENTER:X���W�͕�����̐^�񒆁^ALIGN_RIGHT:X���W�͉E�[
     * @param prm_valign VALIGN_TOP:Y���W�͕�����̍����̏�Ӂ^VALIGN_MIDDLE:Y���W�͕�����̍����̐^�񒆁^VALIGN_BOTTOM:Y���W�͕�����̍����̒��
     */
    virtual void update(coord X, coord Y, const char* prm_str,
                        GgafDxAlign prm_align,
                        GgafDxValign prm_valign);

    /**
     * �`�敶�����X�V�ݒ�  .
     * @param X X���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param Y Y���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param Z �v���C�I���e�B(�l��������������O)
     * @param prm_str �`�敶����
     * @param prm_align ALIGN_LEFT:X���W�͕�����̍��[�^ALIGN_CENTER:X���W�͕�����̐^�񒆁^ALIGN_RIGHT:X���W�͉E�[
     * @param prm_valign VALIGN_TOP:Y���W�͕�����̍����̏�Ӂ^VALIGN_MIDDLE:Y���W�͕�����̍����̐^�񒆁^VALIGN_BOTTOM:Y���W�͕�����̍����̒��
     */
    virtual void update(coord X, coord Y, coord Z, const char* prm_str,
                        GgafDxAlign prm_align,
                        GgafDxValign prm_valign);
    /**
     * �`�敶�����X�V�ݒ�  .
     * @param prm_str �`�敶����
     * @param prm_align ALIGN_LEFT:X���W�͕�����̍��[�^ALIGN_CENTER:X���W�͕�����̐^�񒆁^ALIGN_RIGHT:X���W�͉E�[
     * @param prm_valign VALIGN_TOP:Y���W�͕�����̍����̏�Ӂ^VALIGN_MIDDLE:Y���W�͕�����̍����̐^�񒆁^VALIGN_BOTTOM:Y���W�͕�����̍����̒��
     */
    virtual void update(const char* prm_str,
                        GgafDxAlign prm_align,
                        GgafDxValign prm_valign);

    virtual void setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign) override;
    virtual void setAlign(GgafDxAlign prm_align) override;
    virtual void setValign(GgafDxValign prm_valign) override;

    virtual void prepare1(const char* prm_str);
    virtual void prepare2();
    /**
     * �`�敶�����X�V���ꂽ���ɌĂяo�����R�[���o�b�N .
     * ���ʂŎ������Ă��������B
     */
    virtual void onUpdate() {
    }

    inline void getDrawString(char* out_paCh) {
        int len = _len;
        for (int i = 0; i < len; i++) {
            out_paCh[i] = _draw_string[i];
        }
        out_paCh[len] = '\0';
    }

    inline std::string getDrawString() {
        int len = _len;
        char* paCh = NEW char[len+1];
        getDrawString(paCh);
        std::string s = paCh;
        GGAF_DELETEARR(paCh);
        return s;
    }


public:
    FontBoardActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat = nullptr);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void onActive() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void processDraw() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void onInactive() override {
    }

    virtual bool processHitChkLogic(GgafCore::GgafActor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(const GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual ~FontBoardActor();

};

}
#endif /*GGAFLIB_FONTBOARDACTOR_H_*/
