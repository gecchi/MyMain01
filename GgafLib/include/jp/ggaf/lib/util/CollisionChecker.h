#ifndef COLLISIONCHECKER_H_
#define COLLISIONCHECKER_H_
namespace GgafLib {

/**
 * �Փ˃`�F�b�J�[�N���X.
 * �A�N�^�[�ɓ����蔻��`�F�b�N���@�\��ǉ�����N���X�B
 * �P�́u�����蔻��̈�v�́A�����́u�����蔻��̈�v�f�v����`������Ă��܂��B<BR>
 * �e�u�����蔻��̈�v�f�v�́ABOX�^�Ƌ��^�̂Q��ނ̓�����I�ׂ܂��B<BR>
 * �u�����蔻��̈�v�u�����蔻��̈�v�f�v�ƌ��t�̈Ӗ�����ʂ��A���̂悤�ɂȈӖ��ƒ�`����B<BR>
 * �u�����蔻��̈�̗v�f�v�E�E�E�P�L�����N�^�̓����蔻��̈�B���󂩁A���邢��BOX��̕������̗̈�P���w���B<BR>
 * �u�����蔻��̈�v      �E�E�E�P�ȏ�̔���̈�̗v�f�����킳�����A�P�L�����N�^�̓����蔻��S�̂�\���B<BR>
 *
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class CollisionChecker : public GgafDxCore::GgafDxChecker {

public:
    /** ���`�W���؃I�u�W�F�N�g�ւ̃|�C���^ */
    static LinearOctreeForActor* _pLinearOctree; //TODO:�ǂ��Ɏ������悤���Y�ނ��Ƃ肠�����R�R��
    /** �P�t���[���̓����蔻��v�f���m�̔���� */
    static int _num_check;


    /** �����蔻��̈�̋��E�̈�(AABB)���Čv�Z���邩�ǂ����̃t���O */
    bool _need_update_aabb;
    /** ���`�W���ؓo�^�p�v�f */
    LinearOctreeActorElem* _pElem;

    /**
     * �R���X�g���N�^<BR>
     * @param	prm_pActor	�����蔻��@�\��ǉ�����Actor
     */
    CollisionChecker(GgafDxCore::GgafDxGeometricActor* prm_pActor);

    /**
     * �����蔻��̈�BOX�̉�]���s�ړ��ƁA�W���ؓo�^���s���܂� .
     * �����蔻��@�\���g�p����ɂ́A���̃��\�b�h�𖈃t���[�����s����K�v������܂��B<br>
     * �������A�t���[�����[�N�ɑg�ݍ��܂�Ă��邽�߁A�����҂͓��ɋC�ɂ���K�v���Ȃ��B<br>
     * ���݂� GgafDxGeometricActor::processSettlementBehavior ���疈�t���[���R�[������Ă���B<br>
     * ���� processSettlementBehavior() �����ʂŃI�[�o�[���C�h����ꍇ�͋C��t����ׂ��I<br>
     */
    virtual void updateHitArea();

    /**
     * �����蔻��̈���쐬����i�������蔻��̈�v�f�̔z����쐬����j .
     * �����ŗ̈�̔z��𐶐����܂��B
     * �ŏ��ɕK�����s���Ă��������B
     * @param prm_nColliPart �����蔻��̈�̓����蔻��̈�v�f��(1�`n)
     */
    void makeCollision(int prm_nColliPart);

    /**
     * �����蔻��̈�v�f�����Ƃ��Ē�` .
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x �����蔻��̋��̒��S���[�J��X���W
     * @param y �����蔻��̋��̒��S���[�J��Y���W
     * @param z �����蔻��̋��̒��S���[�J��Z���W
     * @param r �����蔻��̋��̔��a
     * @param rotX �����蔻��̋����A�����ɔ����ă��[�J��X���ł̉�]���s�ړ����s���ꍇ true
     * @param rotY �����蔻��̋����A�����ɔ����ă��[�J��Y���ł̉�]���s�ړ����s���ꍇ true
     * @param rotZ �����蔻��̋����A�����ɔ����ă��[�J��Z���ł̉�]���s�ړ����s���ꍇ true
     */
    void setColliSphere(int prm_index, coord x, coord y, coord z, coord r, bool rotX, bool rotY, bool rotZ);

    /**
     * �����蔻��̈�v�f�����Ƃ��Ē�` .
     * �����ɔ����Ă̓����蔻��̋��̉�]���s�ړ��@�\�͖���
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x �����蔻��̋��̒��S���[�J��X���W
     * @param y �����蔻��̋��̒��S���[�J��Y���W
     * @param z �����蔻��̋��̒��S���[�J��Z���W
     * @param r �����蔻��̋��̔��a
     */
    void setColliSphere(int prm_index, coord x, coord y, coord z, coord r) {
        setColliSphere(prm_index, x, y, z, r, false, false, false);
    }

    /**
     * �����蔻��̈�v�f�����Ƃ��Ē�` .
     * �I�u�W�F�N�g�̊�_�����̒��S�Ƃ���B<br>
     * �����ɔ����Ă̓����蔻��̋��̉�]���s�ړ��@�\�͖����B<br>
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param r �����蔻��̋��̔��a
     */
    void setColliSphere(int prm_index, coord r) {
        setColliSphere(prm_index, 0, 0, 0, r, false, false, false);
    }

    /**
     * �����蔻��̈�v�f�������s�����̂Ƃ��Ē�` .
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
    void setColliAAB(int prm_index,
                     coord x1, coord y1, coord z1,
                     coord x2, coord y2, coord z2,
                     bool rotX, bool rotY, bool rotZ);

    /**
     * �����蔻��̈�v�f�������s�����̂Ƃ��Ē�` .
     * �����ɔ����Ă̓����蔻��̋��̉�]���s�ړ��@�\�͖���
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x1 �����OX���W
     * @param y1 �����OY���W
     * @param z1 �����OZ���W
     * @param x2 �E����X���W
     * @param y2 �E����Y���W
     * @param z2 �E����Z���W
     */
    void setColliAAB(int prm_index,
                     coord x1, coord y1, coord z1,
                     coord x2, coord y2, coord z2) {
        setColliAAB(prm_index, x1, y1, z1, x2, y2, z2, false, false, false);
    }

    /**
     * �����蔻��̈�v�f�������s�����̂Ƃ��Ē�` .
     * Z�̌��݂́A1px����
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x1 �����OX���W
     * @param y1 �����OY���W
     * @param x2 �E����X���W
     * @param y2 �E����Y���W
     */
    void setColliAAB(int prm_index, coord x1, coord y1, coord x2, coord y2) {
        setColliAAB(prm_index, x1, y1, -1 * PxC(1) / 2, x2, y2, PxC(1) / 2, false, false,
                      false);
    }

    /**
     * �����蔻��̈�v�f�������s�����̂Ƃ��Ē�` .
     * BOX���S���W�ƁA���A�����A���s�Ŏw��
     * @param prm_index
     * @param x ���SX���W
     * @param y ���SY���W
     * @param z ���SZ���W
     * @param prm_width ��
     * @param prm_height ����
     * @param prm_depth �[���i���s�j
     */
    void setColliAAB_WHD(int prm_index, coord x, coord y, coord z, coord prm_width, coord prm_height, coord prm_depth) {
        int hw = prm_width  / 2;
        int hh = prm_height / 2;
        int hd = prm_depth  / 2;

        setColliAAB(prm_index, x-hw, y-hh, z-hd, x+hw, y+hh, z+hd);
    }

    /**
     * �����蔻��̈�v�f�������s�����̂Ƃ��Ē�` .
     * �I�u�W�F�N�g�̊�_�𒆐S�Ƃ��āA���A�����A���s�Ŏw��
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param prm_width ��
     * @param prm_height ����
     * @param prm_depth �[���i���s�j
     */
    void setColliAAB_WHD(int prm_index, coord prm_width, coord prm_height, coord prm_depth) {
        setColliAAB_WHD(prm_index, 0, 0, 0, prm_width, prm_height, prm_depth);
    }


    /**
     * �����蔻��̈�v�f�������s�����̂Ƃ��Ē�` .
     * �������W�𒆐S�Ƃ��āA�P�ӂ̒����Ŏw��
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x �����蔻��̗����̂̒��S���[�J��X���W
     * @param y �����蔻��̗����̂̒��S���[�J��Y���W
     * @param z �����蔻��̗����̂̒��S���[�J��Z���W
     * @param prm_edge �P�ӂ̒���
     */
    void setColliAAB_Cube(int prm_index, coord x, coord y, coord z, coord prm_edge) {
        coord h = prm_edge / 2;
        setColliAAB(prm_index, x-h, y-h, z-h, x+h, y+h, z+h);
    }


    /**
     * �����蔻��̈�v�f�������s�����̂Ƃ��Ē�` .
     * �I�u�W�F�N�g�̊�_�𒆐S�Ƃ��āA�P�ӂ̒����Ŏw��
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param prm_edge �P�ӂ̒���
     */
    void setColliAAB_Cube(int prm_index, coord prm_edge) {
        setColliAAB_Cube(prm_index, 0, 0, 0, prm_edge);
    }

    /**
     * �����蔻��̈�v�f�������s�����̂Ƃ��Ē�` .
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
    void setColliAAB_Cube(int prm_index, coord x, coord y, coord z, coord prm_edge, bool rotX, bool rotY, bool rotZ) {
        int h = prm_edge / 2;
        setColliAAB(prm_index, x-h, y-h, z-h, x+h, y+h, z+h, rotX, rotY, rotZ);
    }



    /**
     * �����蔻��̈�v�f�������s�v���Y���^�Ƃ��Ē�` .
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x1 �����OX���W
     * @param y1 �����OY���W
     * @param z1 �����OZ���W
     * @param x2 �E����X���W
     * @param y2 �E����Y���W
     * @param z2 �E����Z���W
     * @param pos_prism �v���Y���ʒu�iPOS_PRISM_**_**)
     * @param rotX �����蔻��̒����̂��A�����ɔ����ă��[�J��X���ł̉�]���s�ړ����s���ꍇ true
     * @param rotY �����蔻��̒����̂��A�����ɔ����ă��[�J��Y���ł̉�]���s�ړ����s���ꍇ true
     * @param rotZ �����蔻��̒����̂��A�����ɔ����ă��[�J��Z���ł̉�]���s�ړ����s���ꍇ true
     */
    void setColliAAPrism(int prm_index, coord x1, coord y1, coord z1, coord x2, coord y2, coord z2, int pos_prism, bool rotX, bool rotY, bool rotZ);

    /**
     * �����蔻��̈�v�f�������s�����̂Ƃ��Ē�` .
     * �����ɔ����Ă̓����蔻��̋��̉�]���s�ړ��@�\�͖���
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x1 �����OX���W
     * @param y1 �����OY���W
     * @param z1 �����OZ���W
     * @param x2 �E����X���W
     * @param y2 �E����Y���W
     * @param z2 �E����Z���W
     * @param pos_prism �v���Y���ʒu�iGgafDxAAPrismActor �� #define ��`�Q��)
     */
    void setColliAAPrism(int prm_index, coord x1, coord y1, coord z1, coord x2, coord y2, coord z2, int pos_prism) {
        setColliAAPrism(prm_index, x1, y1, z1, x2, y2, z2, pos_prism, false, false, false);
    }



    void setColliAAPrism_WHD(int prm_index, coord x, coord y, coord z, coord prm_width, coord prm_height, coord prm_depth, int pos_prism) {
        int hw = prm_width  / 2;
        int hh = prm_height / 2;
        int hd = prm_depth  / 2;
        setColliAAPrism(prm_index, x-hw, y-hh, z-hd, x+hw, y+hh, z+hd, pos_prism);
    }

    /**
     * �����蔻��̈�v�f�������s�����̂Ƃ��Ē�` .
     * �I�u�W�F�N�g�̊�_�𒆐S�Ƃ��āA���A�����A���s�Ŏw��
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param prm_width ��(X��������)
     * @param prm_height ����(Y��������)
     * @param prm_depth �[��(Z��������)
     * @param pos_prism �v���Y���ʒu�iGgafDxAAPrismActor �� #define ��`�Q��)
     */
    void setColliAAPrism_WHD(int prm_index, coord prm_width, coord prm_height, coord prm_depth, int pos_prism) {
        setColliAAPrism_WHD(prm_index, 0, 0, 0, prm_width, prm_height, prm_depth, pos_prism);
    }

    /**
     * �����蔻��̈�v�f�������s�����̂Ƃ��Ē�` .
     * �������W�𒆐S�Ƃ��āA�P�ӂ̒����Ŏw��
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x �����蔻��̗����̂̒��S���[�J��X���W
     * @param y �����蔻��̗����̂̒��S���[�J��Y���W
     * @param z �����蔻��̗����̂̒��S���[�J��Z���W
     * @param prm_edge �P�ӂ̒���
     * @param pos_prism �v���Y���ʒu�iGgafDxAAPrismActor �� #define ��`�Q��)
     */
    void setColliAAPrism_Cube(int prm_index, coord x, coord y, coord z, coord prm_edge, int pos_prism) {
        int h = prm_edge / 2;
        setColliAAPrism(prm_index, x-h, y-h, z-h, x+h, y+h, z+h, pos_prism);
    }

    /**
     * �����蔻��̈�v�f�������s�����̂Ƃ��Ē�` .
     * �������W�𒆐S�Ƃ��āA�P�ӂ̒����Ŏw��
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x �����蔻��̗����̂̒��S���[�J��X���W
     * @param y �����蔻��̗����̂̒��S���[�J��Y���W
     * @param z �����蔻��̗����̂̒��S���[�J��Z���W
     * @param prm_edge �P�ӂ̒���
     * @param rotX �����蔻��̗����̂��A�����ɔ����ă��[�J��X���ł̉�]���s�ړ����s���ꍇ true
     * @param rotY �����蔻��̗����̂��A�����ɔ����ă��[�J��Y���ł̉�]���s�ړ����s���ꍇ true
     * @param rotZ �����蔻��̗����̂��A�����ɔ����ă��[�J��Z���ł̉�]���s�ړ����s���ꍇ true
     * @param pos_prism �v���Y���ʒu�iGgafDxAAPrismActor �� #define ��`�Q��)
     */
    void setColliAAPrism_Cube(int prm_index, coord x, coord y, coord z, coord prm_edge, int pos_prism, bool rotX, bool rotY, bool rotZ) {
        int h = prm_edge / 2;
        setColliAAPrism(prm_index, x-h, y-h, z-h, x+h, y+h, z+h, pos_prism, rotX, rotY, rotZ);
    }

    /**
     * �����蔻��̈�v�f�������s�����̂Ƃ��Ē�` .
     * �I�u�W�F�N�g�̊�_�𒆐S�Ƃ��āA�P�ӂ̒����Ŏw��
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param prm_edge �P�ӂ̒���
     * @param pos_prism �v���Y���ʒu�iGgafDxAAPrismActor.h �́A�ߑ��R�����g�Q��)
     */
    void setColliAAPrism_Cube(int prm_index, coord prm_edge, int pos_prism) {
        setColliAAPrism_Cube(prm_index, 0, 0, 0, prm_edge, pos_prism);
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
     * ���g�̔���̈�Ƒ��̓����蔻��̈�ƐڐG���Ă��邩���ׂ�
     * @param prm_pOtherChecker ���̓����蔻��̈�
     * @return true:�������Ă��� / false:�������Ă��Ȃ�
     */
    virtual bool isHit(GgafDxCore::GgafDxChecker* prm_pOtherChecker) override;

    virtual ~CollisionChecker();
};

}
#endif /*COLLISIONCHECKER_H_*/

