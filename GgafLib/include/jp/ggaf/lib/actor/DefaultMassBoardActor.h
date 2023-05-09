#ifndef GGAF_LIB_DEFAULTMASSBOARDACTOR_H_
#define GGAF_LIB_DEFAULTMASSBOARDACTOR_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/MassBoardActor.h"

namespace GgafLib {

/**
 * ���W�ϊ��ς݃X�v���C�g�A�N�^�[�̋�ۃN���X.
 * GgafDx::MassBoardActor �������������ۃA�N�^�[�ł��B
 * �{�N���X���p�����ĐF�X��ʕ\�����쐬���܂��傤�B<BR>
 * �ȉ��Ɏg�p�\�Ȏx���I�u�W�F�N�g���L���B<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>�I�u�W�F�N�g�ւ̃A�N�Z�X</TH><TH>�T�v</TH><TH>CLASS��</TH></TR>
 * <TR><TD>getPhase()</TD><TD>�t�F�[�Y�Ǘ�</TD><TD>GgafCore::Phase</TD></TR>
 * <TR><TD>getLocoVehicle()</TD><TD>�ړ��ԗ��B�ړ���]�x��</TD><TD>GgafDx::LocoVehicle</TD></TR>
 * <TR><TD>getUvFlipper()</TD><TD>�p���p���A�j���[�V�����x��</TD><TD>GgafDx::UvFlipper</TD></TR>
 * <TR><TD>getSeXmtr()</TD><TD>���ʉ������Ǘ�</TD><TD>GgafDx::SeTransmitter</TD></TR>
 * </TABLE>
 * <B>�y���Ӂz</B>�g��k���x��(GgafDx::Scaler)�͎g�p�o���܂���B
 * @version 1.00
 * @since 2016/02/25
 * @author Masatoshi Tsuge
 */
class DefaultMassBoardActor : public GgafDx::MassBoardActor {
private:
    /**
     * �g�p�֎~ .
     * @return
     */
    GgafDx::Scaler* getScaler();

protected:
    struct VERTEX_instancedata {
        float px_x, px_y, depth_z;    // : TEXCOORD1
        float local_px_x, local_px_y; // : TEXCOORD2
        float r_sx, r_sy, rad_rz;     // : TEXCOORD3
        float offset_u, offset_v;     // : TEXCOORD4
        float r, g, b, a;             // : TEXCOORD5  �}�e���A���J���[
    };
    static VERTEX_instancedata _aInstancedata[];

    static void createVertexInstanceData(void* prm, GgafDx::MassModel::VertexInstanceDataInfo* out_info);

public:
    DefaultMassBoardActor(const char* prm_name, const char* prm_model);

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

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    virtual void onInactive() override {
    }

    virtual bool processHitChkLogic(GgafCore::Actor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(const GgafCore::Actor* prm_pOtherActor) override {
    }

    /**
     * ���f���������P�������Ēǉ�����B .
     * ���߂Ė{���\�b�h�����s����ƁA�������X�g�ɕێ�����A���̃��f���������L���ɂȂ�܂��B
     * �Q��ڈȍ~�̎��s�́A�����������f��������������X�g�̖����ɒǉ����܂��B�i�L���ɂȂ�܂���j
     * @param prm_model ���f����`��
     */
    virtual void addModel(const char* prm_model) override;

    virtual ~DefaultMassBoardActor();

};

}
#endif /*GGAF_LIB_DEFAULTMASSBOARDACTOR_H_*/
