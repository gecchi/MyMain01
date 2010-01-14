#ifndef LASERCHIP_H_
#define LASERCHIP_H_
namespace MyStg2nd {

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

    GgafDx9LibStg::StgChecker* _pStgChecker;

    /** ��O���̃��[�U�[�`�b�v */
    LaserChip* _pChip_front;
    /** �����̃��[�U�[�`�b�v */
    LaserChip* _pChip_behind;
    /** ���[�U�[�e�N�X�`�����  1:���� 2:���� 3:�擪����Q�ԖڂŐ擪�̃e�N�X�`�� �i�������擪�͖������D��j 4:�{���̐擪(�A���`��ł��Ȃ�) */
    int _chip_kind;
    /** ���g��World�ϊ��s�� */
    D3DXMATRIX _matWorld;
    /** ��O����World�ϊ��s�� */
    D3DXMATRIX _matWorld_front;
    /** ���g���Ǘ����Ă�A�N�^�[������ */
    LaserChipDispatcher* _pDispatcher;

    DWORD _dwActiveFrame;

    LaserChip(const char* prm_name, const char* prm_model);

    virtual void initialize();

    virtual void processJudgement();

    virtual void processDraw();

    virtual void processFinal() {}

    virtual void onActive();

    virtual void onInactive();

    virtual void processHappen(int prm_no) {}

    virtual void processOnHit(GgafCore::GgafActor* prm_pOtherActor);

    virtual void drawHitArea();

    virtual ~LaserChip();

};

}
#endif /*LASERCHIP_H_*/

