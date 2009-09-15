#ifndef LASERCHIP_H_
#define LASERCHIP_H_
namespace MyStg2nd {

class LaserChip : public GgafDx9Core::GgafDx9MeshSetActor {
    friend class LaserChipDispatcher;
public:
    D3DXHANDLE _ahKind[8];
    D3DXHANDLE _ahMatWorld_front[8];
    D3DXHANDLE _h_cnt_vertec;

    /** �`�b�v�̒��_�o�b�t�@���V�F�[�_�[�Ń����_�����O����ۂ�Z���W��-1���悸�邩�ǂ����̃t���O */
    int _rev_pos_Z;
    /** �`�b�v�̒��_�o�b�t�@���V�F�[�_�[�Ń����_�����O����ۂ�Z���W��2�Ŋ��邩�ǂ����̃t���O */
    int _div_pos_Z;

    GgafDx9LibStg::StgChecker* _pStgChecker;

    /** ��O���̃��[�U�[�`�b�v */
    LaserChip* _pChip_front;
    /** �����̃��[�U�[�`�b�v */
    LaserChip* _pChip_behind;
    /** ���[�U�[�e�N�X�`�����  1:���� 2:���� 3:�擪 �i�������擪�͖������D��j */
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

    virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

    virtual void drawHitArea();

    virtual ~LaserChip();

};

}
#endif /*LASERCHIP_H_*/

