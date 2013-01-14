#ifndef LASERCHIP_H_
#define LASERCHIP_H_
namespace GgafLib {

/**
 * �|�����C�����[�U�[�̃`�b�v�̊��N���X .
 * �����Ӂ�
 * processSettlementBehavior()���̏����ɂ��A
 * setHitAble(false); �͈Ӗ����Ȃ��܂���B
 * �����蔻����s�������Ȃ��ꍇ�A
 * registHitAreaCube_AutoGenMidColli() ���̓����蔻�莩�̂��쐬���Ȃ��ŉ������B
 * @version 1.00
 * @since 2008/11/24
 * @author Masatoshi Tsuge
 */
class LaserChip : public GgafDxCore::GgafDxMeshSetActor {
    friend class WateringLaserChip;
    friend class HomingLaserChip;
    friend class RefractionLaserChip;
    friend class StraightLaserChip;
    friend class LaserChipDepository;
    friend class LaserChipDepositoryStore;

private:
    D3DXHANDLE _ah_kind[11];
    D3DXHANDLE _ah_force_alpha[11];
    D3DXHANDLE _ah_matWorld_front[11];
    //D3DXHANDLE _h_cnt_vertec;


    /** onAcive() �Ń��Z�b�g�����U�镑�����t���[���� */
    frame _frame_of_behaving_from_onActive;

    /** ���g���Ǘ����Ă�A�N�^�[������ */
    LaserChipDepository* _pDepo;
    /** registHitAreaCube_AutoGenMidColli() ���\�b�h�ɂ��o�^���̓����蔻�藧���̂̂P�ӂ̒��� */
    int _hitarea_edge_length;
    int _hitarea_edge_length_3;
    /** registHitAreaCube_AutoGenMidColli() ���\�b�h�ɂ��o�^���̓����蔻�藧���̂̂P�ӂ̒����̔��� */
    int _harf_hitarea_edge_length;

public:


    CollisionChecker* _pColliChecker;

    /** ��O���̃��[�U�[�`�b�v */
    LaserChip* _pChip_front;
    /** �����̃��[�U�[�`�b�v */
    LaserChip* _pChip_behind;
    /** ���[�U�[�e�N�X�`�����  1:���� 2:���� 3:�擪����Q�ԖڂŐ擪�̃e�N�X�`�� �i�������擪�͖������D��j 4:�{���̐擪(�A���`��ł��Ȃ�) */
    int _chip_kind;
    /** [r]�n�`�q�b�g����`�b�v(10���1��) */
    bool _can_chikei_hit;
    /** [r]���g�����������[�`�b�v */
    LaserChip* _pLeader;
    /** [r]�����㏑���A���t�@�l�B�i�o�����͉����ł����Ă��\�������邽��) */
    float _force_alpha;
    /** [r]rue�Ȃ�΁A�O���`�b�v�Ɨ��ꂷ�����ꍇ�ɒ��ԓ����蔻�莩������ */
    float _middle_colli_able;

    LaserChip(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=nullptr);

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

    /**
     * ���[�U�[�`�b�v�p�����蔻�藧���̂��Z�b�g .
     * ���[�U�[�`�b�v�Ԃ̋���������A�����蔻��̂��蔲����h�~���邽�߁A<BR>
     * �ʏ�̓����蔻��ɉ����A�ڑ����ꂽ�O���`�b�v�Ƃ̋��������ꂽ�ꍇ�ɂ̂݁A<BR>
     * �����I�ɒ��Ԃɓ����蔻���������������@�\���t�^�����B<BR>
     * �����蔻��v�f���͂Q�ɂȂ�B
     * �y���Ӂz<BR>
     * �\�߃��[�U�[�`�b�v�Ԃ̋������J�����A���蔲�����N����Ȃ��Ƃ킩���Ă���ꍇ�́A<BR>
     * �{���\�b�h�Őݒ肹���A�ʏ� _pColliChecker->makeCollision(1);<BR>
     * ���s�����ق����p�t�H�[�}���X���ǂ��B<BR>
     * @param prm_edge_length
     */
    virtual void registHitAreaCube_AutoGenMidColli(int prm_edge_length);


    /**
     * ���ݒ�.
     * @param prm_alpha
     */
    virtual void setAlpha(float prm_alpha) override;

    /**
     * �����Z .
     * @param prm_alpha
     */
    virtual void addAlpha(float prm_alpha) override;


    virtual ~LaserChip();

};

}
#endif /*LASERCHIP_H_*/

