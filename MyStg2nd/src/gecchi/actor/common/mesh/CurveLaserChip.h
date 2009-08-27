#ifndef CURVELASERCHIP_H_
#define CURVELASERCHIP_H_
namespace MyStg2nd {

class CurveLaserChip : public LaserChip {
    friend class CurveLaserChipDispatcher;
public:
////    D3DXHANDLE _hKind, _hX, _hY, _hZ, _hRevPosZ;
//    D3DXHANDLE _ahKind[8];
////    D3DXHANDLE _ahRevPosZ[8];
//    D3DXHANDLE _ahMatWorld_front[8];
//
//    D3DXHANDLE _h_cnt_vertec;
//
//    /** �`�b�v�̒��_�o�b�t�@���V�F�[�_�[�Ń����_�����O����ۂ�Z���W��-1���悸�邩�ǂ����̃t���O */
//    int _rev_pos_Z;
//    /** �`�b�v�̒��_�o�b�t�@���V�F�[�_�[�Ń����_�����O����ۂ�Z���W��2�Ŋ��邩�ǂ����̃t���O */
//    int _div_pos_Z;
//
////    virtual void processPreDraw() {
////        GgafDx9Core::GgafDx9MeshSetActor::processPreDraw();
////    }
//
//
//
////    void processAfterDraw();
//
//
//
//    GgafDx9LibStg::StgChecker* _pStgChecker;
//
//    /** ��O���̃��[�U�[�`�b�v */
//    CurveLaserChip* _pChip_front;
//    /** �����̃��[�U�[�`�b�v */
//    CurveLaserChip* _pChip_behind;
//    /** ���[�U�[�e�N�X�`�����  1:���� 2:���� 3:�擪 �i�������擪�͖������D��j */
//    int _chip_kind;
//
//    /** ���g��World�ϊ��s�� */
//    D3DXMATRIX _matWorld;
//    /** ��O����World�ϊ��s�� */
//    D3DXMATRIX _matWorld_front;
//    /** ���g���Ǘ����Ă�A�N�^�[������ */
//    CurveLaserChipDispatcher* _pDispatcher;



    CurveLaserChip(const char* prm_name, const char* prm_model);

    virtual void initialize();

    virtual void processBehavior();

    virtual void processJudgement();

    virtual void onActive();

    virtual void onInactive();

    virtual ~CurveLaserChip();

};

}
#endif /*CURVELASERCHIP_H_*/

