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
    friend class LaserChipDispatcher;
public:
    D3DXHANDLE _ahKind[16];
    D3DXHANDLE _ahMatWorld_front[16];
    D3DXHANDLE _h_cnt_vertec;

    CollisionChecker* _pCollisionChecker;

    /** ��O���̃��[�U�[�`�b�v */
    LaserChip* _pChip_front;
    /** �����̃��[�U�[�`�b�v */
    LaserChip* _pChip_behind;
    /** ���[�U�[�e�N�X�`�����  1:���� 2:���� 3:�擪����Q�ԖڂŐ擪�̃e�N�X�`�� �i�������擪�͖������D��j 4:�{���̐擪(�A���`��ł��Ȃ�) */
    int _chip_kind;
    /** ���g���Ǘ����Ă�A�N�^�[������ */
    LaserChipDispatcher* _pDispatcher;
    /** registHitAreaCube() ���\�b�h�ɂ��o�^����Ă��邩�ǂ����Btrue�Ȃ�΁A���ԓ����蔻�莩������������g���� */
    bool _is_regist_hitarea;
    /** registHitAreaCube() ���\�b�h�ɂ��o�^���̓����蔻�藧���̂̂P�ӂ̒��� */
    int _hitarea_edge_length;
    /** registHitAreaCube() ���\�b�h�ɂ��o�^���̓����蔻�藧���̂̂P�ӂ̒����̔��� */
    int _harf_hitarea_edge_length;
    /** onAcive() �Ń��Z�b�g�����U�镑�����t���[���� */
    DWORD _frame_of_behaving_from_onActive;
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

    virtual void processHappen(int prm_no) override {}

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual void drawHitArea() override;

    virtual void registHitAreaCube(int prm_edge_length);

    virtual ~LaserChip();

};

}
#endif /*LASERCHIP_H_*/
