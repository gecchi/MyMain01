#ifndef LASERCHIP_H_
#define LASERCHIP_H_
namespace GgafDx9LibStg {

/**
 * �|�����C�����[�U�[�̃`�b�v�̊��N���X .
 * @version 1.00
 * @since 2008/11/24
 * @author Masatoshi Tsuge
 */
class LaserChip : public GgafDx9Core::GgafDx9MeshSetActor {
    friend class CurveLaserChip;
    friend class HomingLaserChip;
    friend class RefractionLaserChip;
    friend class StraightLaserChip;
    friend class LaserChipDispatcher;
    friend class LaserChipDispatcherDispatcher;

private:
    D3DXHANDLE _ahKind[16];
    D3DXHANDLE _ah_matWorld_front[16];

    D3DXHANDLE _h_cnt_vertec;

    /** onAcive() �Ń��Z�b�g�����U�镑�����t���[���� */
    frame _frame_of_behaving_from_onActive;

    /** ���g���Ǘ����Ă�A�N�^�[������ */
    LaserChipDispatcher* _pDispatcher;
    /** registHitAreaCube() ���\�b�h�ɂ��o�^����Ă��邩�ǂ����Btrue�Ȃ�΁A���ԓ����蔻�莩�������@�\���g���� */
    bool _is_regist_hitarea;
    /** registHitAreaCube() ���\�b�h�ɂ��o�^���̓����蔻�藧���̂̂P�ӂ̒��� */
    int _hitarea_edge_length;
    /** registHitAreaCube() ���\�b�h�ɂ��o�^���̓����蔻�藧���̂̂P�ӂ̒����̔��� */
    int _harf_hitarea_edge_length;

public:


    CollisionChecker* _pCollisionChecker;

    /** ��O���̃��[�U�[�`�b�v */
    LaserChip* _pChip_front;
    /** �����̃��[�U�[�`�b�v */
    LaserChip* _pChip_behind;
    /** ���[�U�[�e�N�X�`�����  1:���� 2:���� 3:�擪����Q�ԖڂŐ擪�̃e�N�X�`�� �i�������擪�͖������D��j 4:�{���̐擪(�A���`��ł��Ȃ�) */
    int _chip_kind;

    bool _can_chikei_hit;

    LaserChip(const char* prm_name, const char* prm_model);


    virtual void onCreateModel() override {}

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processSettlementBehavior() override;

    virtual void processJudgement() override;

    virtual void processDraw() override;

    virtual void processFinal() override {}

    virtual void onInactive() override;

    virtual void catchEvent(UINT32 prm_no, void* prm_pSource) override {}

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual void drawHitArea() override;

    virtual void registHitAreaCube(int prm_edge_length);

    virtual ~LaserChip();

};

}
#endif /*LASERCHIP_H_*/

