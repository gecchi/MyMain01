#ifndef HITAREABOXS_H_
#define HITAREABOXS_H_
namespace GgafDx9LibStg {

/**
 * �����蔻��̈�N���X
 * @version 1.00
 * @since 2008/03/13
 * @author Masatoshi Tsuge
 */
class HitAreaBoxs : public GgafDx9Core::GgafDx9HitArea {
public:
    struct Box {
        int x1; //x���W�̏�������
        int y1; //y���W�̏�������
        int z1; //z���W�̏�������
        int x2; //�Ίp�̒��_�ƂȂ�x���W�傫����
        int y2; //�Ίp�̒��_�ƂȂ�y���W�傫����
        int z2; //�Ίp�̒��_�ƂȂ�z���W�傫����
        int cx; //���S�_x���W
        int cy; //���S�_y���W
        int cz; //���S�_z���W
        int hdx; //x���̔���
        int hdy; //y���̔���
        int hdz; //z���̔���
        bool rotX; //���S�_���A�I�u�W�F�N�g��(0,0)�𒆐S��X����]�̈ړ��������邩�ǂ����i������]����̂ł͂Ȃ��j
        bool rotY; //���S�_���A�I�u�W�F�N�g��(0,0)�𒆐S��Y����]�̈ړ��������邩�ǂ����i������]����̂ł͂Ȃ��j
        bool rotZ; //���S�_���A�I�u�W�F�N�g��(0,0)�𒆐S��Z����]�̈ړ��������邩�ǂ����i������]����̂ł͂Ȃ��j
 //       bool active; //�L���t���O
    };



    Box* _paBase;
    Box* _paHitArea;

    HitAreaBoxs(int prm_iAreaNum);

    void setBox(int prm_iArea, int x1, int y1, int z1, int x2, int y2, int z2, bool rotX, bool rotY, bool rotZ);
//    void enable(int prm_iArea);
//    void disable(int prm_iArea);
//    bool isEnable(int prm_iArea);

    virtual ~HitAreaBoxs();
};

}
#endif /*HITAREABOXS_H_*/
