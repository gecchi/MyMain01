#ifndef GGAFLIB_DEFAULTMASSBOARDACTOR_H_
#define GGAFLIB_DEFAULTMASSBOARDACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxMassBoardActor.h"

namespace GgafLib {

/**
 * ���W�ϊ��ς݃X�v���C�g�A�N�^�[�̋�ۃN���X.
 * GgafDxCore::GgafDxMassBoardActor �������������ۃA�N�^�[�ł��B
 * �{�N���X���p�����ĐF�X��ʕ\�����쐬���܂��傤�B<BR>
 * �ȉ��Ɏg�p�\�Ȏx���I�u�W�F�N�g���L���B<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>�I�u�W�F�N�g�ւ̃A�N�Z�X</TH><TH>�T�v</TH><TH>CLASS��</TH></TR>
 * <TR><TD>getProgress()</TD><TD>�i���Ǘ�</TD><TD>GgafCore::GgafProgress</TD></TR>
 * <TR><TD>getKuroko()</TD><TD>���߁B�ړ���]�x��</TD><TD>GgafDxCore::GgafDxKuroko</TD></TR>
 * <TR><TD>getUvFlipper()</TD><TD>�p���p���A�j���[�V�����x��</TD><TD>GgafDxCore::GgafDxUvFlipper</TD></TR>
 * <TR><TD>getSeTx()</TD><TD>���ʉ������Ǘ�</TD><TD>GgafDxCore::GgafDxSeTransmitter</TD></TR>
 * </TABLE>
 * <B>�y���Ӂz</B>�g��k���x��(GgafDxCore::GgafDxScaler)�͎g�p�o���܂���B
 * @version 1.00
 * @since 2016/02/25
 * @author Masatoshi Tsuge
 */
class DefaultMassBoardActor : public GgafDxCore::GgafDxMassBoardActor {

protected:
    struct VERTEX_instancedata {
        float px_x, px_y, depth_z;    // : TEXCOORD1
        float local_px_x, local_px_y; // : TEXCOORD2
        float r_sx, r_sy, rad_rz;     // : TEXCOORD3
        float offset_u, offset_v;     // : TEXCOORD4
        float r, g, b, a;             // : TEXCOORD5  �}�e���A���J���[
    };
    static VERTEX_instancedata _aInstancedata[];

    static void createVertexInstaceData(void* prm, GgafDxCore::GgafDxMassModel::VertexInstaceDataInfo* out_info);

public:
    DefaultMassBoardActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat = nullptr);

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

    virtual ~DefaultMassBoardActor();

};

}
#endif /*GGAFLIB_DEFAULTMASSBOARDACTOR_H_*/
