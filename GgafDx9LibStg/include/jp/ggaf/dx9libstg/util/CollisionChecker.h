#ifndef COLLISIONCHECKER_H_
#define COLLISIONCHECKER_H_
namespace GgafDx9LibStg {

/**
 * �`�F�b�J�[�N���X.
 * �A�N�^�[�ɓ����蔻��`�F�b�N���@�\��ǉ�����N���X�B
 * �P�́u�����蔻��̈�v�́A�����́u�����蔻��̈�v�f�v����`������Ă��܂��B
 * �e�u�����蔻��̈�v�f�v�́ABOX�^�Ƌ��^�̂Q��ނ̓�����I�ׂ܂��B
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class CollisionChecker : public GgafDx9Core::GgafDx9Checker {

public:
    /** ���`�W���؃I�u�W�F�N�g�ւ̃|�C���^ */
    static LinearOctreeForActor* _pLinearOctree; //TODO:�ǂ��Ɏ������悤���Y�ނ��Ƃ肠�����R�R��
    /** �����蔻��̔���� */
    static int _num_check;


    /** �����蔻��̈�̋��E�̈�(AABB)���Čv�Z���邩�ǂ����̃t���O */
    bool _need_update_aabb;
    /** ���`�W���ؓo�^�p�v�f */
    LinearOctreeActorElem* _pElem;


    /**
     * �R���X�g���N�^<BR>
     * @param	prm_pActor	�����蔻��@�\��ǉ�����Actor
     */
    CollisionChecker(GgafDx9Core::GgafDx9GeometricActor* prm_pActor);

    /**
     * �����蔻��̈�BOX�̉�]���s�ړ��ƁA�W���ؓo�^���s���܂� .
     * �����蔻��@�\���g�p����ɂ́A���̃��\�b�h�𖈃t���[�����s����K�v������܂��B<br>
     * �������A�t���[�����[�N�ɑg�ݍ��܂�Ă��邽�߁A�����҂͓��ɋC�ɂ���K�v���Ȃ��B<br>
     * ���݂� GgafDx9GeometricActor::processPreJudgement ���疈�t���[���R�[������Ă���B<br>
     * ���� processPreJudgement() �����ʂŃI�[�o�[���C�h����ꍇ�͋C��t����ׂ��I<br>
     */
    virtual void updateHitArea();

    /**
     * �����蔻��̈���쐬���� .
     * �����ŗ̈�̔z��𐶐����܂��B
     * �ŏ��ɕK�����s���Ă��������B
     * @param prm_nColliPart �����蔻��̈�̗v�f��(1�`n)
     */
    void makeCollision(int prm_nColliPart);

    /**
     * �����蔻��̈�����Ƃ��Ē�` .
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x �����蔻��̋��̒��S���[�J��X���W
     * @param y �����蔻��̋��̒��S���[�J��Y���W
     * @param z �����蔻��̋��̒��S���[�J��Z���W
     * @param r �����蔻��̋��̔��a
     * @param rotX �����蔻��̋����A�����ɔ����ă��[�J��X���ł̉�]���s�ړ����s���ꍇ true
     * @param rotY �����蔻��̋����A�����ɔ����ă��[�J��Y���ł̉�]���s�ړ����s���ꍇ true
     * @param rotZ �����蔻��̋����A�����ɔ����ă��[�J��Z���ł̉�]���s�ړ����s���ꍇ true
     */
    void setColliSphere(int prm_index, int x, int y, int z, int r, bool rotX, bool rotY, bool rotZ);

    /**
     * �����蔻��̈�����Ƃ��Ē�` .
     * �����ɔ����Ă̓����蔻��̋��̉�]���s�ړ��@�\�͖���
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x �����蔻��̋��̒��S���[�J��X���W
     * @param y �����蔻��̋��̒��S���[�J��Y���W
     * @param z �����蔻��̋��̒��S���[�J��Z���W
     * @param r �����蔻��̋��̔��a
     */
    void setColliSphere(int prm_index, int x, int y, int z, int r) {
        setColliSphere(prm_index, x, y, z, r, false, false, false);
    }

    /**
     * �����蔻��̈�����Ƃ��Ē�` .
     * �I�u�W�F�N�g�̊�_�����̒��S�Ƃ���B<br>
     * �����ɔ����Ă̓����蔻��̋��̉�]���s�ړ��@�\�͖����B<br>
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param r �����蔻��̋��̔��a
     */
    void setColliSphere(int prm_index, int r) {
        setColliSphere(prm_index, 0, 0, 0, r, false, false, false);
    }

    /**
     * �����蔻��̈�������s�����̂Ƃ��Ē�` .
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x1 �����OX���W
     * @param y1 �����OY���W
     * @param z1 �����OZ���W
     * @param x2 �E����X���W
     * @param y2 �E����Y���W
     * @param z2 �E����Z���W
     * @param rotX �����蔻��̒����̂��A�����ɔ����ă��[�J��X���ł̉�]���s�ړ����s���ꍇ true
     * @param rotY �����蔻��̒����̂��A�����ɔ����ă��[�J��Y���ł̉�]���s�ړ����s���ꍇ true
     * @param rotZ �����蔻��̒����̂��A�����ɔ����ă��[�J��Z���ł̉�]���s�ړ����s���ꍇ true
     */
    void setColliAAB(int prm_index, int x1, int y1, int z1, int x2, int y2, int z2, bool rotX, bool rotY, bool rotZ);

    /**
     * �����蔻��̈�������s�����̂Ƃ��Ē�` .
     * �����ɔ����Ă̓����蔻��̋��̉�]���s�ړ��@�\�͖���
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x1 �����OX���W
     * @param y1 �����OY���W
     * @param z1 �����OZ���W
     * @param x2 �E����X���W
     * @param y2 �E����Y���W
     * @param z2 �E����Z���W
     */
    void setColliAAB(int prm_index, int x1, int y1, int z1, int x2, int y2, int z2) {
        setColliAAB(prm_index, x1, y1, z1, x2, y2, z2, false, false, false);
    }

    /**
     * �����蔻��̈�������s�����̂Ƃ��Ē�` .
     * Z�̌��݂́A1px����
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x1 �����OX���W
     * @param y1 �����OY���W
     * @param x2 �E����X���W
     * @param y2 �E����Y���W
     */
    void setColliAAB(int prm_index, int x1, int y1, int x2, int y2) {
        setColliAAB(prm_index, x1, y1, -1 * LEN_UNIT / 2, x2, y2, LEN_UNIT / 2, false, false,
                      false);
    }


    void setColliAAB_WHD(int prm_index, int x, int y, int z, int prm_width, int prm_height, int prm_depth) {
        int hw = prm_width  / 2;
        int hh = prm_height / 2;
        int hd = prm_depth  / 2;

        setColliAAB(prm_index, x-hw, y-hh, z-hd, x+hw, y+hh, z+hd);
    }


    /**
     * �����蔻��̈�������s�����̂Ƃ��Ē�` .
     * �I�u�W�F�N�g�̊�_�𒆐S�Ƃ��āA���A�����A���s�Ŏw��
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param prm_width ��
     * @param prm_height ����
     * @param prm_depth �[���i���s�j
     */
    void setColliAAB_WHD(int prm_index, int prm_width, int prm_height, int prm_depth) {
        setColliAAB_WHD(prm_index, 0, 0, 0, prm_width, prm_height, prm_depth);
    }


    /**
     * �����蔻��̈�������s�����̂Ƃ��Ē�` .
     * �������W�𒆐S�Ƃ��āA�P�ӂ̒����Ŏw��
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x �����蔻��̗����̂̒��S���[�J��X���W
     * @param y �����蔻��̗����̂̒��S���[�J��Y���W
     * @param z �����蔻��̗����̂̒��S���[�J��Z���W
     * @param prm_edge �P�ӂ̒���
     */
    void setColliAAB_Cube(int prm_index, int x, int y, int z, int prm_edge) {
        int h = prm_edge / 2;
        setColliAAB(prm_index, x-h, y-h, z-h, x+h, y+h, z+h);
    }

    /**
     * �����蔻��̈�������s�����̂Ƃ��Ē�` .
     * �������W�𒆐S�Ƃ��āA�P�ӂ̒����Ŏw��
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x �����蔻��̗����̂̒��S���[�J��X���W
     * @param y �����蔻��̗����̂̒��S���[�J��Y���W
     * @param z �����蔻��̗����̂̒��S���[�J��Z���W
     * @param prm_edge �P�ӂ̒���
     * @param rotX �����蔻��̗����̂��A�����ɔ����ă��[�J��X���ł̉�]���s�ړ����s���ꍇ true
     * @param rotY �����蔻��̗����̂��A�����ɔ����ă��[�J��Y���ł̉�]���s�ړ����s���ꍇ true
     * @param rotZ �����蔻��̗����̂��A�����ɔ����ă��[�J��Z���ł̉�]���s�ړ����s���ꍇ true
     */
    void setColliAAB_Cube(int prm_index, int x, int y, int z, int prm_edge, bool rotX, bool rotY, bool rotZ) {
        int h = prm_edge / 2;
        setColliAAB(prm_index, x-h, y-h, z-h, x+h, y+h, z+h, rotX, rotY, rotZ);
    }

    /**
     * �����蔻��̈�������s�����̂Ƃ��Ē�` .
     * �I�u�W�F�N�g�̊�_�𒆐S�Ƃ��āA�P�ӂ̒����Ŏw��
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param prm_edge �P�ӂ̒���
     */
    void setColliAAB_Cube(int prm_index, int prm_edge) {
        setColliAAB_Cube(prm_index, 0, 0, 0, prm_edge);
    }

    /**
     * �����蔻��̈�̗v�f��L���ɂ���B
     * �f�t�H���g�͗L����ԂɂȂ��Ă��܂��B
     * @param prm_index �L���ɂ��铖���蔻��̈�̗v�f�ԍ�
     */
    void enable(int prm_index) {
        _pCollisionArea->_papColliPart[prm_index]->_is_valid_flg = true;
    }

    /**
     * �����蔻��̈�̗v�f�𖳌��ɂ���B
     * @param prm_index �����ɂ��铖���蔻��̈�̗v�f�ԍ�
     */
    void disable(int prm_index) {
        _pCollisionArea->_papColliPart[prm_index]->_is_valid_flg = false;
    }

    /**
     * �����蔻��̈�̗v�f���L�������ׂ�B
     * @param prm_index ���ׂ��������蔻��̈�̗v�f�ԍ�
     * @return true:�L�� / false:����
     */
    bool isEnable(int prm_index) {
        return _pCollisionArea->_papColliPart[prm_index]->_is_valid_flg;
    }

    /**
     * ���̓����蔻��̈�ƐڐG���Ă��邩���ׂ�
     * @param prm_pOtherChecker ���̓����蔻��̈�
     * @return true:�������Ă��� / false:�������Ă��Ȃ�
     */
    inline bool isHit(GgafDx9Core::GgafDx9Checker* prm_pOtherChecker);

    virtual ~CollisionChecker();
};

}
#endif /*COLLISIONCHECKER_H_*/

