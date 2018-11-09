#ifndef GGAFLIB_LASERCHIP_H_
#define GGAFLIB_LASERCHIP_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxMassMeshActor.h"

namespace GgafLib {

/**
 * �|�����C�����[�U�[�̃`�b�v�̊��N���X .
 * �����Ӂ�
 * processSettlementBehavior()���̏����ɂ��A
 * setHitAble(false); �͈Ӗ����Ȃ��܂���B
 * �����蔻����s�������Ȃ��ꍇ�A
 * registerHitAreaCube_AutoGenMidColli() ���̓����蔻�莩�̂��쐬���Ȃ��ŉ������B
 * @version 1.00
 * @since 2008/11/24
 * @author Masatoshi Tsuge
 */
class LaserChip : public GgafDxCore::GgafDxMassMeshActor {
    friend class WateringLaserChip;
    friend class HomingLaserChip;
    friend class RefractionLaserChip;
    friend class StraightLaserChip;
    friend class NomalLaserChip;
    friend class LaserChipDepository;

private:

    /** onAcive() �Ń��Z�b�g�����U�镑�����t���[���� */
    frame _frame_of_behaving_from_onActive;

    /** ���g���Ǘ����Ă�A�N�^�[������ */
    LaserChipDepository* _pDepo;
    /** registerHitAreaCube_AutoGenMidColli() ���\�b�h�ɂ��o�^���̓����蔻�藧���̂̂P�ӂ̒��� */
    coord _hitarea_edge_length;
    ucoord _hitarea_edge_length_2;
    coord _hitarea_edge_length_3;
    ucoord _hitarea_edge_length_3_2;
    coord _hitarea_edge_length_6;
    ucoord _hitarea_edge_length_6_2;
    /** registerHitAreaCube_AutoGenMidColli() ���\�b�h�ɂ��o�^���̓����蔻�藧���̂̂P�ӂ̒����̔��� */
//    int _harf_hitarea_edge_length;

    int _hdx,_hdy,_hdz;


    /** ��O���̃��[�U�[�`�b�v */
    LaserChip* _pChip_infront;
    /** �����̃��[�U�[�`�b�v */
    LaserChip* _pChip_behind;

public:

    struct VERTEX_instancedata {
        float _11, _12, _13, _14;   // : TEXCOORD1  World�ϊ��s��A�P�s��
        float _21, _22, _23, _24;   // : TEXCOORD2  World�ϊ��s��A�Q�s��
        float _31, _32, _33, _34;   // : TEXCOORD3  World�ϊ��s��A�R�s��
        float _41, _42, _43, _44;   // : TEXCOORD4  World�ϊ��s��A�S�s��

        float _f_11, _f_12, _f_13, _f_14;   // : TEXCOORD5  �O���`�b�vWorld�ϊ��s��A�P�s��
        float _f_21, _f_22, _f_23, _f_24;   // : TEXCOORD6  �O���`�b�vWorld�ϊ��s��A�Q�s��
        float _f_31, _f_32, _f_33, _f_34;   // : TEXCOORD7  �O���`�b�vWorld�ϊ��s��A�R�s��
        float _f_41, _f_42, _f_43, _f_44;   // : TEXCOORD8  �O���`�b�vWorld�ϊ��s��A�S�s��

        float _chip_kind, _force_alpha, _power, _infront_chip_power;   // : TEXCOORD9  �`�b�v��ʁA�������A�Η͗��A�O���`�b�v�Η͗�
    };

    static VERTEX_instancedata _aInstancedata[];
    CollisionChecker* _pColliChecker;

    /** ���[�U�[�e�N�X�`�����  0:�s�� 1:���� 2:���� 3:�擪����Q�ԖڂŐ擪�̃e�N�X�`�� �i�������擪�͖������D��j 4:�{���̐擪(�A���`��ł��Ȃ�) */
    int _chip_kind;
    /** [r]�n�`�q�b�g����`�b�v(10���1��) */
    bool _can_chikei_hit;
    /** [r]�����㏑���A���t�@�l�B�i�o�����͉����ł����Ă��\�������邽��) */
    float _force_alpha;
    /** [r]true�Ȃ�΁A�O���`�b�v�Ɨ��ꂷ�����ꍇ�ɒ��ԓ����蔻�莩������ */
    bool _middle_colli_able;

    float _rate_of_length;
    /** [r] �Η͗��A�U���͂ɏ悶����l */
    float _power;
public:
    LaserChip(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=nullptr);

    static bool initStatic(LaserChip* prm_pLaserChip);

    virtual void executeHitChk_MeAnd(GgafActor* prm_pOtherActor) override;

    virtual void onActive() override;
    /**
     * �l�X�Ȏ��O���� .
     * �����Ӂ�
     * setHitAble(true);
     * ������Ŏ��s���Ă��܂��̂ŁA
     * setHitAble(false);
     * �͖��Ӗ��ł��B
     */
    virtual void processSettlementBehavior() override;

    virtual void processPreDraw() override;
    virtual void processDraw() override;

    virtual void onInactive() override;

    virtual void drawHitArea() override;
    virtual int isOutOfView() override;
    /**
     * ���[�U�[�`�b�v�p�����蔻�藧���̂��Z�b�g .
     * ���[�U�[�`�b�v�Ԃ̋���������A�����蔻��̂��蔲����h�~���邽�߁A<BR>
     * �ʏ�̓����蔻��ɉ����A�ڑ����ꂽ�O���`�b�v�Ƃ̋��������ꂽ�ꍇ�ɂ̂݁A<BR>
     * �����I�ɒ��Ԃɓ����蔻���������������@�\���t�^�����B<BR>
     * �����蔻��v�f���͂Q�ɂȂ�B
     * �y���Ӂz<BR>
     * �\�߃��[�U�[�`�b�v�Ԃ̋������J�����A���蔲�����N����Ȃ��Ƃ킩���Ă���ꍇ�́A<BR>
     * �{���\�b�h�Őݒ肹���A�ʏ� getCollisionChecker()->createCollisionArea(1);<BR>
     * ���s�����ق����p�t�H�[�}���X���ǂ��B<BR>
     * @param prm_edge_length
     */
    virtual void registerHitAreaCube_AutoGenMidColli(int prm_edge_length);

    inline CollisionChecker* getCollisionChecker() {
        return _pColliChecker;
    }

    /**
     * ���g�̈�O���̃��[�U�[�`�b�v���擾 .
     * �擾�ł���ꍇ�́A���g�ƘA�����Ă��邱�ƂƂȂ�B
     * �擾�ł��Ȃ��ꍇ(�߂�l=nullptr)�A���g�͐擪�`�b�v�ł���B
     * @return ��O���̃��[�U�[�`�b�v�A���� nullptr
     */
    inline LaserChip* getInfrontChip() {
        return _pChip_infront;
    }

    /**
     * ���g�̈����̃��[�U�[�`�b�v���擾 .
     * �擾�ł���ꍇ�́A���g�ƘA�����Ă��邱�ƂƂȂ�B
     * �擾�ł��Ȃ��ꍇ(�߂�l=nullptr)�A���g�͖����`�b�v�ł���B
     * @return �����̃��[�U�[�`�b�v�A���� nullptr
     */
    inline LaserChip* getBehindChip() {
        return _pChip_behind;
    }

    static void createVertexInstanceData(void* prm, GgafDxCore::GgafDxMassMeshModel::VertexInstanceDataInfo* out_info);

    virtual ~LaserChip();

};

}
#endif /*GGAFLIB_LASERCHIP_H_*/

