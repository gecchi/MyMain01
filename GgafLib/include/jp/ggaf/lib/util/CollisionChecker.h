#ifndef GGAFLIB_COLLISIONCHECKER_H_
#define GGAFLIB_COLLISIONCHECKER_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxChecker.h"

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
    /** �����蔻��̈�̋��E�̈�(AABB)���Čv�Z���邩�ǂ����̃t���O */
    bool _need_update_aabb;
#ifdef MY_DEBUG
    /** �P�t���[���̓����蔻��v�f���m�̔���� */
    static unsigned int _num_check;
#endif
public:
    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pActor  �����蔻��@�\��ǉ�����Actor
     */
    explicit CollisionChecker(GgafDxCore::GgafDxGeometricActor* prm_pActor);

    /**
     * �����蔻��̈�v�f�����Ƃ��Ē�` .
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x �����蔻��̋��̒��SX���W�iActor���[�J�����W�j
     * @param y �����蔻��̋��̒��SY���W�iActor���[�J�����W�j
     * @param z �����蔻��̋��̒��SZ���W�iActor���[�J�����W�j
     * @param r �����蔻��̋��̔��a
     * @param rot_x �����蔻��̋����AActor�̌����ɔ�����Actor���[�J��X���𒆐S�ɉ�]���s�ړ����s���ꍇ true
     * @param rot_y �����蔻��̋����AActor�̌����ɔ�����Actor���[�J��Y���𒆐S�ɉ�]���s�ړ����s���ꍇ true
     * @param rot_z �����蔻��̋����AActor�̌����ɔ�����Actor���[�J��Z���𒆐S�ɉ�]���s�ړ����s���ꍇ true
     */
    void setColliSphere(int prm_index, coord x, coord y, coord z, coord r, bool rot_x, bool rot_y, bool rot_z);

    /**
     * �����蔻��̈�v�f�����Ƃ��Ē�` .
     * Actor�̌����ɔ����ē����蔻��̉�]���s�ړ��@�\�͖���
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x �����蔻��̋��̒��SX���W�iActor���[�J�����W�j
     * @param y �����蔻��̋��̒��SY���W�iActor���[�J�����W�j
     * @param z �����蔻��̋��̒��SZ���W�iActor���[�J�����W�j
     * @param r �����蔻��̋��̔��a
     */
    void setColliSphere(int prm_index, coord x, coord y, coord z, coord r) {
        setColliSphere(prm_index, x, y, z, r, false, false, false);
    }

    /**
     * �����蔻��̈�v�f�����Ƃ��Ē�` .
     * �����蔻��̋��̒��S���W�́AActor���[�J�����W�̌��_�ɐݒ肳���B
     * Actor�̌����ɔ����ē����蔻��̉�]���s�ړ��@�\�͖����B
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param r �����蔻��̋��̔��a
     */
    void setColliSphere(int prm_index, coord r) {
        setColliSphere(prm_index, 0, 0, 0, r, false, false, false);
    }

    /**
     * �����蔻��̈�v�f�������s�����̂Ƃ��Ē�` .
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x1 �����蔻�蒼���̂̍�����OX���W�iActor���[�J�����W�j
     * @param y1 �����蔻�蒼���̂̍�����OY���W�iActor���[�J�����W�j
     * @param z1 �����蔻�蒼���̂̍�����OZ���W�iActor���[�J�����W�j
     * @param x2 �����蔻�蒼���̂̉E�㉜X���W�iActor���[�J�����W�j
     * @param y2 �����蔻�蒼���̂̉E�㉜Y���W�iActor���[�J�����W�j
     * @param z2 �����蔻�蒼���̂̉E�㉜Z���W�iActor���[�J�����W�j
     * @param rot_x �����蔻��̒����̂��AActor�̌����ɔ�����Actor���[�J��X���𒆐S�ɉ�]���s�ړ����s���ꍇ true
     * @param rot_y �����蔻��̒����̂��AActor�̌����ɔ�����Actor���[�J��Y���𒆐S�ɉ�]���s�ړ����s���ꍇ true
     * @param rot_z �����蔻��̒����̂��AActor�̌����ɔ�����Actor���[�J��Z���𒆐S�ɉ�]���s�ړ����s���ꍇ true
     */
    void setColliAABox(int prm_index,
                       coord x1, coord y1, coord z1,
                       coord x2, coord y2, coord z2,
                       bool rot_x, bool rot_y, bool rot_z);

    /**
     * �����蔻��̈�v�f�������s�����̂Ƃ��Ē�` .
     * Actor�̌����ɔ����ē����蔻��̉�]���s�ړ��@�\�͖����B
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x1 �����蔻�蒼���̂̍�����OX���W�iActor���[�J�����W�j
     * @param y1 �����蔻�蒼���̂̍�����OY���W�iActor���[�J�����W�j
     * @param z1 �����蔻�蒼���̂̍�����OZ���W�iActor���[�J�����W�j
     * @param x2 �����蔻�蒼���̂̉E�㉜X���W�iActor���[�J�����W�j
     * @param y2 �����蔻�蒼���̂̉E�㉜Y���W�iActor���[�J�����W�j
     * @param z2 �����蔻�蒼���̂̉E�㉜Z���W�iActor���[�J�����W�j
     */
    void setColliAABox(int prm_index,
                       coord x1, coord y1, coord z1,
                       coord x2, coord y2, coord z2) {
        setColliAABox(prm_index, x1, y1, z1, x2, y2, z2, false, false, false);
    }

    /**
     * �����蔻��̈�v�f�������s�����̂Ƃ��Ē�` .
     * �����蔻�蒼���̂̒��S���W�ƁA���A�����A���s�Ŏw��B
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x �����蔻�蒼���̂̒��SX���W�iActor���[�J�����W�j
     * @param y �����蔻�蒼���̂̒��SY���W�iActor���[�J�����W�j
     * @param z �����蔻�蒼���̂̒��SZ���W�iActor���[�J�����W�j
     * @param prm_width �����蔻�蒼���̂̕��iX�������̒����j
     * @param prm_height �����蔻�蒼���̂̍����iY�������̒����j
     * @param prm_depth �����蔻�蒼���̂̐[���i���s�EZ�������̒����j
     * @param rot_x �����蔻��̒����̂��AActor�̌����ɔ�����Actor���[�J��X���𒆐S�ɉ�]���s�ړ����s���ꍇ true
     * @param rot_y �����蔻��̒����̂��AActor�̌����ɔ�����Actor���[�J��Y���𒆐S�ɉ�]���s�ړ����s���ꍇ true
     * @param rot_z �����蔻��̒����̂��AActor�̌����ɔ�����Actor���[�J��Z���𒆐S�ɉ�]���s�ړ����s���ꍇ true
     */
    void setColliAABox_WHD(int prm_index, coord x, coord y, coord z, coord prm_width, coord prm_height, coord prm_depth, bool rot_x, bool rot_y, bool rot_z) {
        int hw = prm_width  / 2;
        int hh = prm_height / 2;
        int hd = prm_depth  / 2;
        setColliAABox(prm_index, x-hw, y-hh, z-hd, x+hw, y+hh, z+hd, rot_x, rot_y, rot_z);
    }

    /**
     * �����蔻��̈�v�f�������s�����̂Ƃ��Ē�` .
     * �����蔻�蒼���̂̒��S���W�ƁA���A�����A���s�Ŏw��B
     * Actor�̌����ɔ����ē����蔻��̉�]���s�ړ��@�\�͖����B
     * @param prm_index
     * @param x �����蔻�蒼���̂̒��SX���W�iActor���[�J�����W�j
     * @param y �����蔻�蒼���̂̒��SY���W�iActor���[�J�����W�j
     * @param z �����蔻�蒼���̂̒��SZ���W�iActor���[�J�����W�j
     * @param prm_width �����蔻�蒼���̂̕��iX�������̒����j
     * @param prm_height �����蔻�蒼���̂̍����iY�������̒����j
     * @param prm_depth �����蔻�蒼���̂̐[���i���s�EZ�������̒����j
     */
    void setColliAABox_WHD(int prm_index, coord x, coord y, coord z, coord prm_width, coord prm_height, coord prm_depth) {
        setColliAABox_WHD(prm_index, x, y, z, prm_width, prm_height, prm_depth, false, false, false);
    }

    /**
     * �����蔻��̈�v�f�������s�����̂Ƃ��Ē�` .
     * �����蔻�蒼���̂̕��A�����A���s�Ŏw��B
     * �����蔻�蒼���̂̒��S���W�́AActor���[�J�����W�̌��_�ɐݒ肳���B
     * Actor�̌����ɔ����ē����蔻��̉�]���s�ړ��@�\�͖����B
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param prm_width �����蔻�蒼���̂̕��iX�������̒����j
     * @param prm_height �����蔻�蒼���̂̍����iY�������̒����j
     * @param prm_depth �����蔻�蒼���̂̐[���i���s�EZ�������̒����j
     */
    void setColliAABox_WHD(int prm_index, coord prm_width, coord prm_height, coord prm_depth) {
        setColliAABox_WHD(prm_index, 0, 0, 0, prm_width, prm_height, prm_depth);
    }

    /**
     * �����蔻��̈�v�f�������s�����̂Ƃ��Ē�` .
     * �����蔻�藧���̂̒��S���W�ƁA�P�ӂ̒����Ŏw��B
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x �����蔻�藧���̂̒��SX���W�iActor���[�J�����W�j
     * @param y �����蔻�藧���̂̒��SY���W�iActor���[�J�����W�j
     * @param z �����蔻�藧���̂̒��SZ���W�iActor���[�J�����W�j
     * @param prm_edge �����蔻�藧���̂̂P�ӂ̒���
     * @param rot_x �����蔻��̗����̂��AActor�̌����ɔ�����Actor���[�J��X���𒆐S�ɉ�]���s�ړ����s���ꍇ true
     * @param rot_y �����蔻��̗����̂��AActor�̌����ɔ�����Actor���[�J��Y���𒆐S�ɉ�]���s�ړ����s���ꍇ true
     * @param rot_z �����蔻��̗����̂��AActor�̌����ɔ�����Actor���[�J��Z���𒆐S�ɉ�]���s�ړ����s���ꍇ true
     */
    void setColliAACube(int prm_index, coord x, coord y, coord z, coord prm_edge, bool rot_x, bool rot_y, bool rot_z) {
        int h = prm_edge / 2;
        setColliAABox(prm_index, x-h, y-h, z-h, x+h, y+h, z+h, rot_x, rot_y, rot_z);
    }

    /**
     * �����蔻��̈�v�f�������s�����̂Ƃ��Ē�` .
     * �����蔻�藧���̂̒��S���W�ƁA�P�ӂ̒����Ŏw��B
     * Actor�̌����ɔ����ē����蔻��̉�]���s�ړ��@�\�͖����B
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x �����蔻�藧���̂̒��SX���W�iActor���[�J�����W�j
     * @param y �����蔻�藧���̂̒��SY���W�iActor���[�J�����W�j
     * @param z �����蔻�藧���̂̒��SZ���W�iActor���[�J�����W�j
     * @param prm_edge �����蔻�藧���̂̂P�ӂ̒���
     */
    void setColliAACube(int prm_index, coord x, coord y, coord z, coord prm_edge) {
        setColliAACube(prm_index, x, y, z, prm_edge, false, false, false);
    }

    /**
     * �����蔻��̈�v�f�������s�����̂Ƃ��Ē�` .
     * �����蔻�藧���̂̂P�ӂ̒����Ŏw��B
     * �����蔻�藧���̂̒��S���W�́AActor���[�J�����W�̌��_�ɐݒ肳���B
     * Actor�̌����ɔ����ē����蔻��̉�]���s�ړ��@�\�͖����B
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param prm_edge �����蔻�藧���̂̂P�ӂ̒���
     */
    void setColliAACube(int prm_index, coord prm_edge) {
        setColliAACube(prm_index, 0, 0, 0, prm_edge);
    }

    /**
     * �����蔻��̈�v�f�������s�v���Y���^�Ƃ��Ē�` .
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x1 �����蔻��v���Y���^�̋��E�����̂̍�����OX���W�iActor���[�J�����W�j
     * @param y1 �����蔻��v���Y���^�̋��E�����̂̍�����OY���W�iActor���[�J�����W�j
     * @param z1 �����蔻��v���Y���^�̋��E�����̂̍�����OZ���W�iActor���[�J�����W�j
     * @param x2 �����蔻��v���Y���^�̋��E�����̂̉E�㉜X���W�iActor���[�J�����W�j
     * @param y2 �����蔻��v���Y���^�̋��E�����̂̉E�㉜Y���W�iActor���[�J�����W�j
     * @param z2 �����蔻��v���Y���^�̋��E�����̂̉E�㉜Z���W�iActor���[�J�����W�j
     * @param pos_info �v���Y���ʒu�iPOS_PRISM_**_**)
     * @param rot_x �����蔻��̃v���Y���^���AActor�̌����ɔ�����Actor���[�J��X���𒆐S�ɉ�]���s�ړ����s���ꍇ true
     * @param rot_y �����蔻��̃v���Y���^���AActor�̌����ɔ�����Actor���[�J��Y���𒆐S�ɉ�]���s�ړ����s���ꍇ true
     * @param rot_z �����蔻��̃v���Y���^���AActor�̌����ɔ�����Actor���[�J��Z���𒆐S�ɉ�]���s�ړ����s���ꍇ true
     */
    void setColliAAPrism(int prm_index, coord x1, coord y1, coord z1, coord x2, coord y2, coord z2, pos_t pos_info, bool rot_x, bool rot_y, bool rot_z);

    /**
     * �����蔻��̈�v�f�������s�v���Y���^�Ƃ��Ē�` .
     * Actor�̌����ɔ����ē����蔻��̉�]���s�ړ��@�\�͖����B
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x1 �����蔻��v���Y���^�̋��E�����̂̍�����OX���W�iActor���[�J�����W�j
     * @param y1 �����蔻��v���Y���^�̋��E�����̂̍�����OY���W�iActor���[�J�����W�j
     * @param z1 �����蔻��v���Y���^�̋��E�����̂̍�����OZ���W�iActor���[�J�����W�j
     * @param x2 �����蔻��v���Y���^�̋��E�����̂̉E�㉜X���W�iActor���[�J�����W�j
     * @param y2 �����蔻��v���Y���^�̋��E�����̂̉E�㉜Y���W�iActor���[�J�����W�j
     * @param z2 �����蔻��v���Y���^�̋��E�����̂̉E�㉜Z���W�iActor���[�J�����W�j
     * @param pos_info �v���Y���ʒu�iGgafDxAAPrismActor �� #define ��`�Q��)
     */
    void setColliAAPrism(int prm_index, coord x1, coord y1, coord z1, coord x2, coord y2, coord z2, pos_t pos_info) {
        setColliAAPrism(prm_index, x1, y1, z1, x2, y2, z2, pos_info, false, false, false);
    }


    /**
     * �����蔻��̈�v�f�������s�v���Y���^�Ƃ��Ē�` .
     * �����蔻��v���Y���^�̋��E�����̂̒��S���W�ƁA���A�����A���s�Ŏw��B
     * Actor�̌����ɔ����ē����蔻��̉�]���s�ړ��@�\�͖����B
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x �����蔻��v���Y���^�̋��E�����̂̒��SX���W�iActor���[�J�����W�j
     * @param y �����蔻��v���Y���^�̋��E�����̂̒��SY���W�iActor���[�J�����W�j
     * @param z �����蔻��v���Y���^�̋��E�����̂̒��SZ���W�iActor���[�J�����W�j
     * @param prm_width �����蔻��v���Y���^�̋��E�����̂̕��iX�������̒����j
     * @param prm_height �����蔻��v���Y���^�̋��E�����̂̍����iY�������̒����j
     * @param prm_depth �����蔻��v���Y���^�̋��E�����̂̐[���i���s�EZ�������̒����j
     * @param pos_info �v���Y���ʒu�iGgafDxAAPrismActor �� #define ��`�Q��)
     */
    void setColliAAPrism_WHD(int prm_index, coord x, coord y, coord z, coord prm_width, coord prm_height, coord prm_depth, pos_t pos_info) {
        int hw = prm_width  / 2;
        int hh = prm_height / 2;
        int hd = prm_depth  / 2;
        setColliAAPrism(prm_index, x-hw, y-hh, z-hd, x+hw, y+hh, z+hd, pos_info);
    }

    /**
     * �����蔻��̈�v�f�������s�v���Y���^�Ƃ��Ē�` .
     * �����蔻��v���Y���^�̋��E�����̂̕��A�����A���s�Ŏw��B
     * �����蔻��v���Y���^�̋��E�����̂̒��S���W�́AActor���[�J�����W�̌��_�ɐݒ肳���B
     * (�K���Ζʂ�Actor���[�J�����W�̌��_�ɐڂ��邱�ƂɂȂ�)
     * Actor�̌����ɔ����ē����蔻��̉�]���s�ړ��@�\�͖����B
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param prm_width �����蔻��v���Y���^�̋��E�����̂̕��iX�������̒����j
     * @param prm_height �����蔻��v���Y���^�̋��E�����̂̍����iY�������̒����j
     * @param prm_depth �����蔻��v���Y���^�̋��E�����̂̐[���i���s�EZ�������̒����j
     * @param pos_info �v���Y���ʒu�iGgafDxAAPrismActor �� #define ��`�Q��)
     */
    void setColliAAPrism_WHD(int prm_index, coord prm_width, coord prm_height, coord prm_depth, pos_t pos_info) {
        setColliAAPrism_WHD(prm_index, 0, 0, 0, prm_width, prm_height, prm_depth, pos_info);
    }

    /**
     * �����蔻��̈�v�f�������s�v���Y���^�Ƃ��Ē�` .
     * �����蔻��v���Y���^�̋��E�����̂̒��S���W�ƁA�P�ӂ̒����Ŏw��B
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x �����蔻��v���Y���^�̋��E�����̂̒��SX���W�iActor���[�J�����W�j
     * @param y �����蔻��v���Y���^�̋��E�����̂̒��SY���W�iActor���[�J�����W�j
     * @param z �����蔻��v���Y���^�̋��E�����̂̒��SZ���W�iActor���[�J�����W�j
     * @param prm_edge �����蔻��v���Y���^�̋��E�����̂̂P�ӂ̒���
     * @param rot_x �����蔻��̃v���Y���^���AActor�̌����ɔ�����Actor���[�J��X���𒆐S�ɉ�]���s�ړ����s���ꍇ true
     * @param rot_y �����蔻��̃v���Y���^���AActor�̌����ɔ�����Actor���[�J��Y���𒆐S�ɉ�]���s�ړ����s���ꍇ true
     * @param rot_z �����蔻��̃v���Y���^���AActor�̌����ɔ�����Actor���[�J��Z���𒆐S�ɉ�]���s�ړ����s���ꍇ true
     * @param pos_info �v���Y���ʒu�iGgafDxAAPrismActor �� #define ��`�Q��)
     */
    void setColliAAPrism_Cube(int prm_index, coord x, coord y, coord z, coord prm_edge, pos_t pos_info, bool rot_x, bool rot_y, bool rot_z) {
        int h = prm_edge / 2;
        setColliAAPrism(prm_index, x-h, y-h, z-h, x+h, y+h, z+h, pos_info, rot_x, rot_y, rot_z);
    }

    /**
     * �����蔻��̈�v�f�������s�v���Y���^�Ƃ��Ē�` .
     * �����蔻��v���Y���^�̋��E�����̂̒��S���W�ƁA�P�ӂ̒����Ŏw��B
     * Actor�̌����ɔ����ē����蔻��̉�]���s�ړ��@�\�͖����B
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x �����蔻��v���Y���^�̋��E�����̂̒��SX���W�iActor���[�J�����W�j
     * @param y �����蔻��v���Y���^�̋��E�����̂̒��SY���W�iActor���[�J�����W�j
     * @param z �����蔻��v���Y���^�̋��E�����̂̒��SZ���W�iActor���[�J�����W�j
     * @param prm_edge �����蔻��v���Y���^�̋��E�����̂̂P�ӂ̒���
     * @param pos_info �v���Y���ʒu�iGgafDxAAPrismActor �� #define ��`�Q��)
     */
    void setColliAAPrism_Cube(int prm_index, coord x, coord y, coord z, coord prm_edge, pos_t pos_info) {
        setColliAAPrism_Cube(prm_index, x, y, z, prm_edge, pos_info, false, false, false);
    }

    /**
     * �����蔻��̈�v�f�������s�v���Y���^�Ƃ��Ē�` .
     * �����蔻��v���Y���^�̋��E�����̂̂P�ӂ̒����Ŏw��B
     * �����蔻��v���Y���^�̋��E�����̂̒��S���W�́AActor���[�J�����W�̌��_�ɐݒ肳���B
     * (�K���Ζʂ�Actor���[�J�����W�̌��_�ɐڂ��邱�ƂɂȂ�)
     * Actor�̌����ɔ����ē����蔻��̉�]���s�ړ��@�\�͖����B
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param prm_edge �����蔻��v���Y���^�̋��E�����̂̂P�ӂ̒���
     * @param pos_info �v���Y���ʒu�iGgafDxAAPrismActor.h �́A�ߑ��R�����g�Q��)
     */
    void setColliAAPrism_Cube(int prm_index, coord prm_edge, pos_t pos_info) {
        setColliAAPrism_Cube(prm_index, 0, 0, 0, prm_edge, pos_info);
    }

    /**
     * �����蔻��̈�v�f�������s���p�O�p���Ƃ��Ē�` .
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x1 �����蔻�蒼�p�O�p���̋��E�����̂̍�����OX���W�iActor���[�J�����W�j
     * @param y1 �����蔻�蒼�p�O�p���̋��E�����̂̍�����OY���W�iActor���[�J�����W�j
     * @param z1 �����蔻�蒼�p�O�p���̋��E�����̂̍�����OZ���W�iActor���[�J�����W�j
     * @param x2 �����蔻�蒼�p�O�p���̋��E�����̂̉E�㉜X���W�iActor���[�J�����W�j
     * @param y2 �����蔻�蒼�p�O�p���̋��E�����̂̉E�㉜Y���W�iActor���[�J�����W�j
     * @param z2 �����蔻�蒼�p�O�p���̋��E�����̂̉E�㉜Z���W�iActor���[�J�����W�j
     * @param pos_info �s���~�b�h�ʒu�iPOS_PYRAMID_***)
     * @param rot_x �����蔻��̒��p�O�p���̋��E�����̂��AActor�̌����ɔ�����Actor���[�J��X���𒆐S�ɉ�]���s�ړ����s���ꍇ true
     * @param rot_y �����蔻��̒��p�O�p���̋��E�����̂��AActor�̌����ɔ�����Actor���[�J��Y���𒆐S�ɉ�]���s�ړ����s���ꍇ true
     * @param rot_z �����蔻��̒��p�O�p���̋��E�����̂��AActor�̌����ɔ�����Actor���[�J��Z���𒆐S�ɉ�]���s�ړ����s���ꍇ true
     */
    void setColliAAPyramid(int prm_index, coord x1, coord y1, coord z1, coord x2, coord y2, coord z2, pos_t pos_info, bool rot_x, bool rot_y, bool rot_z);

    /**
     * �����蔻��̈�v�f�������s�̎O���p�O�p���Ƃ��Ē�` .
     * Actor�̌����ɔ����ē����蔻��̉�]���s�ړ��@�\�͖����B
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x1 �����蔻�蒼�p�O�p���̋��E�����̂̍�����OX���W�iActor���[�J�����W�j
     * @param y1 �����蔻�蒼�p�O�p���̋��E�����̂̍�����OY���W�iActor���[�J�����W�j
     * @param z1 �����蔻�蒼�p�O�p���̋��E�����̂̍�����OZ���W�iActor���[�J�����W�j
     * @param x2 �����蔻�蒼�p�O�p���̋��E�����̂̉E�㉜X���W�iActor���[�J�����W�j
     * @param y2 �����蔻�蒼�p�O�p���̋��E�����̂̉E�㉜Y���W�iActor���[�J�����W�j
     * @param z2 �����蔻�蒼�p�O�p���̋��E�����̂̉E�㉜Z���W�iActor���[�J�����W�j
     * @param pos_info �s���~�b�h�ʒu�iPOS_PYRAMID_***)
     */
    void setColliAAPyramid(int prm_index, coord x1, coord y1, coord z1, coord x2, coord y2, coord z2, pos_t pos_info) {
        setColliAAPyramid(prm_index, x1, y1, z1, x2, y2, z2, pos_info, false, false, false);
    }

    /**
     * �����蔻��̈�v�f�������s�̎O���p�O�p���Ƃ��Ē�` .
     * �����蔻��O���p�O�p���̋��E�����̂̒��S���W�ƁA���A�����A���s�Ŏw��B
     * Actor�̌����ɔ����ē����蔻��̉�]���s�ړ��@�\�͖����B
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x ������O���p�O�p���̋��E�����̂̒��SX���W�iActor���[�J�����W�j
     * @param y ������O���p�O�p���̋��E�����̂̒��SY���W�iActor���[�J�����W�j
     * @param z ������O���p�O�p���̋��E�����̂̒��SZ���W�iActor���[�J�����W�j
     * @param prm_width ������O���p�O�p���̋��E�����̂̕��iX�������̒����j
     * @param prm_height ������O���p�O�p���̋��E�����̂̍����iY�������̒����j
     * @param prm_depth ������O���p�O�p���̋��E�����̂̐[���i���s�EZ�������̒����j
     * @param pos_info �s���~�b�h�ʒu�iPOS_PYRAMID_***)
     */
    void setColliAAPyramid_WHD(int prm_index, coord x, coord y, coord z, coord prm_width, coord prm_height, coord prm_depth, pos_t pos_info) {
        int hw = prm_width  / 2;
        int hh = prm_height / 2;
        int hd = prm_depth  / 2;
        setColliAAPyramid(prm_index, x-hw, y-hh, z-hd, x+hw, y+hh, z+hd, pos_info);
    }

    /**
     * �����蔻��̈�v�f�������s�̎O���p�O�p���Ƃ��Ē�` .
     * ������O���p�O�p���̋��E�����̂̕��A�����A���s�Ŏw��B
     * ������O���p�O�p���̋��E�����̂̒��S���W�́AActor���[�J�����W�̌��_�ɐݒ肳���B
     * (�K���Ζʂ�Actor���[�J�����W�̌��_�ɐڂ��邱�ƂɂȂ�)
     * Actor�̌����ɔ����ē����蔻��̉�]���s�ړ��@�\�͖����B
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param prm_width ������O���p�O�p���̋��E�����̂̕��iX�������̒����j
     * @param prm_height ������O���p�O�p���̋��E�����̂̍����iY�������̒����j
     * @param prm_depth ������O���p�O�p���̋��E�����̂̐[���i���s�EZ�������̒����j
     * @param pos_info �v���Y���ʒu�iGgafDxAAPrismActor �� #define ��`�Q��)
     */
    void setColliAAPyramid_WHD(int prm_index, coord prm_width, coord prm_height, coord prm_depth, pos_t pos_info) {
        setColliAAPyramid_WHD(prm_index, 0, 0, 0, prm_width, prm_height, prm_depth, pos_info);
    }

    /**
     * �����蔻��̈�v�f�������s�v���Y���^�Ƃ��Ē�` .
     * �����蔻��O���p�O�p���̋��E�����̂̒��S���W�ƁA�P�ӂ̒����Ŏw��B
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x �����蔻��O���p�O�p���̋��E�����̂̒��SX���W�iActor���[�J�����W�j
     * @param y �����蔻��O���p�O�p���̋��E�����̂̒��SY���W�iActor���[�J�����W�j
     * @param z �����蔻��O���p�O�p���̋��E�����̂̒��SZ���W�iActor���[�J�����W�j
     * @param prm_edge �����蔻��O���p�O�p���̋��E�����̂̂P�ӂ̒���
     * @param rot_x �����蔻��̎O���p�O�p�����AActor�̌����ɔ�����Actor���[�J��X���𒆐S�ɉ�]���s�ړ����s���ꍇ true
     * @param rot_y �����蔻��̎O���p�O�p�����AActor�̌����ɔ�����Actor���[�J��Y���𒆐S�ɉ�]���s�ړ����s���ꍇ true
     * @param rot_z �����蔻��̎O���p�O�p�����AActor�̌����ɔ�����Actor���[�J��Z���𒆐S�ɉ�]���s�ړ����s���ꍇ true
     * @param pos_info �s���~�b�h�ʒu�iGgafDxAAPyramidActor �� #define ��`�Q��)
     */
    void setColliAAPyramid_Cube(int prm_index, coord x, coord y, coord z, coord prm_edge, pos_t pos_info, bool rot_x, bool rot_y, bool rot_z) {
        int h = prm_edge / 2;
        setColliAAPyramid(prm_index, x-h, y-h, z-h, x+h, y+h, z+h, pos_info, rot_x, rot_y, rot_z);
    }

    /**
     * �����蔻��̈�v�f�������s�����̂Ƃ��Ē�` .
     * �����蔻��O���p�O�p���̋��E�����̂̒��S���W�ƁA�P�ӂ̒����Ŏw��B
     * Actor�̌����ɔ����ē����蔻��̉�]���s�ړ��@�\�͖����B
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x �����蔻��O���p�O�p���̋��E�����̂̒��SX���W�iActor���[�J�����W�j
     * @param y �����蔻��O���p�O�p���̋��E�����̂̒��SY���W�iActor���[�J�����W�j
     * @param z �����蔻��O���p�O�p���̋��E�����̂̒��SZ���W�iActor���[�J�����W�j
     * @param prm_edge �����蔻��O���p�O�p���̋��E�����̂̂P�ӂ̒���
     * @param pos_info �s���~�b�h�ʒu�iGgafDxAAPyramidActor �� #define ��`�Q��)
     */
    void setColliAAPyramid_Cube(int prm_index, coord x, coord y, coord z, coord prm_edge, pos_t pos_info) {
        setColliAAPyramid_Cube(prm_index, x, y, z, prm_edge, pos_info, false, false, false);
    }

    /**
     * �����蔻��̈�v�f�������s�����̂Ƃ��Ē�` .
     * �����蔻��O���p�O�p���̋��E�����̂̂P�ӂ̒����Ŏw��B
     * �����蔻��O���p�O�p���̋��E�����̂̒��S���W�́AActor���[�J�����W�̌��_�ɐݒ肳���B
     * (�K���Ζʂ�Actor���[�J�����W�̌��_�ɐڂ��邱�ƂɂȂ�)
     * Actor�̌����ɔ����ē����蔻��̉�]���s�ړ��@�\�͖����B
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param prm_edge ������O���p�O�p���^�̋��E�����̂̂P�ӂ̒���
     * @param pos_info �s���~�b�h�ʒu�iGgafDxAAPyramidActor.h �́A�ߑ��R�����g�Q��)
     */
    void setColliAAPyramid_Cube(int prm_index, coord prm_edge, pos_t pos_info) {
        setColliAAPyramid_Cube(prm_index, 0, 0, 0, prm_edge, pos_info);
    }

/////////////////////////////////////////////////////////

    /**
     * �����蔻��̈�v�f���~�Ƃ��Ē�` .
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x �����蔻��̉~�̒��SX���W�iActor���[�J�����W�j
     * @param y �����蔻��̉~�̒��SY���W�iActor���[�J�����W�j
     * @param r �����蔻��̉~�̔��a
     * @param rot_z �����蔻��̉~���AActor�̌����ɔ�����Actor���[�J��Z���𒆐S�ɉ�]���s�ړ����s���ꍇ true
     */
    void set2DColliCircle(int prm_index, coord x, coord y, coord r, bool rot_z=false) {
        setColliSphere(prm_index, x, y, 0, r, false, false, rot_z);
    }

    /**
     * �����蔻��̈�v�f���~�Ƃ��Ē�` .
     * �����蔻��̉~�̒��S���W�́AActor���[�J�����W�̌��_�ɐݒ肳���B
     * Actor�̌����ɔ����ē����蔻��̉�]���s�ړ��@�\�͖����B
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param r �����蔻��̉~�̔��a
     */
    void set2DColliCircle(int prm_index, coord r) {
        set2DColliCircle(prm_index, 0, 0, r, false);
    }

    /**
     * �����蔻��̈�v�f�������s�����`�Ƃ��Ē�` .
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x1 �����蔻�蒼���̂̍���X���W�iActor���[�J�����W�j
     * @param y1 �����蔻�蒼���̂̍���Y���W�iActor���[�J�����W�j
     * @param x2 �����蔻�蒼���̂̉E��X���W�iActor���[�J�����W�j
     * @param y2 �����蔻�蒼���̂̉E��Y���W�iActor���[�J�����W�j
     * @param rot_z �����蔻��̒����̂��AActor�̌����ɔ�����Actor���[�J�����_�𒆐S�ɉ�]���s�ړ����s���ꍇ true
     */
    void set2DColliRectangle(int prm_index,
                             coord x1, coord y1,
                             coord x2, coord y2,
                             bool rot_z = false) {
        setColliAABox(prm_index,
                      x1, y1, 0,
                      x2, y2, 0,
                      false, false, rot_z);
    }

    /**
     * �����蔻��̈�v�f�������s�����`�Ƃ��Ē�` .
     * �����蔻�萳���`�̒��S���W�ƁA�P�ӂ̒����Ŏw��B
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x �����蔻�萳���`�̒��SX���W�iActor���[�J�����W�j
     * @param y �����蔻�萳���`�̒��SY���W�iActor���[�J�����W�j
     * @param prm_edge �����蔻�萳���`�̂P�ӂ̒���
     * @param rot_z �����蔻��̐����`���AActor�̌����ɔ�����Actor���[�J�����_�𒆐S�ɉ�]���s�ړ����s���ꍇ true
     */
    void set2DColliSquare(int prm_index, coord x, coord y, coord prm_edge, bool rot_z = false) {
        coord h = prm_edge / 2;
        set2DColliRectangle(prm_index, x-h, y-h, x+h, y+h, rot_z);
    }

    /**
     * �����蔻��̈�v�f�������s�����`�Ƃ��Ē�` .
     * �����蔻�萳���`�̂P�ӂ̒����Ŏw��B
     * �����蔻�萳���`�̒��S���W�́AActor���[�J�����W�̌��_�ɐݒ肳���B
     * Actor�̌����ɔ����ē����蔻��̉�]���s�ړ��@�\�͖����B
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param prm_edge �����蔻�萳���`�̂P�ӂ̒���
     */
    void set2DColliSquare(int prm_index, coord prm_edge) {
        set2DColliSquare(prm_index, 0, 0, prm_edge, false);
    }

    /**
     * �����蔻��̈�v�f�������s�����`���Ē�` .
     * �����蔻�蒷���`�̒��S���W�ƁA���A�����Ŏw��B
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x �����蔻�蒷���`�̒��SX���W�iActor���[�J�����W�j
     * @param y �����蔻�蒷���`�̒��SY���W�iActor���[�J�����W�j
     * @param prm_width �����蔻�蒷���`�̕��iX�������̒����j
     * @param prm_height �����蔻�蒷���`�̍����iY�������̒����j
     * @param rot_z �����蔻��̒����`���AActor�̌����ɔ�����Actor���[�J��Z���𒆐S�ɉ�]���s�ړ����s���ꍇ true
     */
    void set2DColliRectangle_WH(int prm_index, coord x, coord y, coord prm_width, coord prm_height, bool rot_z = false) {
        int hw = prm_width  / 2;
        int hh = prm_height / 2;
        set2DColliRectangle(prm_index, x-hw, y-hh, x+hw, y+hh, rot_z);
    }

    /**
     * �����蔻��̈�v�f�������s�����`�Ƃ��Ē�` .
     * �����蔻�蒷���`�̕��A�����A���s�Ŏw��B
     * �����蔻�蒷���`�̒��S���W�́AActor���[�J�����W�̌��_�ɐݒ肳���B
     * Actor�̌����ɔ����ē����蔻��̉�]���s�ړ��@�\�͖����B
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param prm_width �����蔻�蒷���`�̕��iX�������̒����j
     * @param prm_height �����蔻�蒷���`�̍����iY�������̒����j
     */
    void set2DColliRectangle_WH(int prm_index, coord prm_width, coord prm_height) {
        set2DColliRectangle_WH(prm_index, 0, 0, prm_width, prm_height);
    }

    /**
     * �����蔻��̈�v�f�������s���p�O�p�`�Ƃ��Ē�` .
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x1 �����蔻�蒼�p�O�p�`�̋��E�����`�̍���X���W�iActor���[�J�����W�j
     * @param y1 �����蔻�蒼�p�O�p�`�̋��E�����`�̍���Y���W�iActor���[�J�����W�j
     * @param x2 �����蔻�蒼�p�O�p�`�̋��E�����`�̉E��X���W�iActor���[�J�����W�j
     * @param y2 �����蔻�蒼�p�O�p�`�̋��E�����`�̉E��Y���W�iActor���[�J�����W�j
     * @param pos_info ���p�ʒu�iPOS_R_TRIANGLE_**)
     * @param rot_z �����蔻��̒��p�O�p�`���AActor�̌����ɔ�����Actor���[�J��Z���𒆐S�ɉ�]���s�ړ����s���ꍇ true
     */
    void set2DColliRightTriangle(int prm_index, coord x1, coord y1, coord x2, coord y2, pos_t pos_info, bool rot_z=false) {
        setColliAAPrism(prm_index, x1, y1, 0, x2, y2, 0, pos_info, false, false, rot_z);
    }

    /**
     * �����蔻��̈�v�f�������s���p�O�p�`�Ƃ��Ē�` .
     * �����蔻�蒼�p�O�p�`�̋��E�����`�̒��S���W�ƁA���A�����A���s�Ŏw��B
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x �����蔻�蒼�p�O�p�`�̋��E�����`�̒��SX���W�iActor���[�J�����W�j
     * @param y �����蔻�蒼�p�O�p�`�̋��E�����`�̒��SY���W�iActor���[�J�����W�j
     * @param prm_width �����蔻�蒼�p�O�p�`�̋��E�����`�̕��iX�������̒����j
     * @param prm_height �����蔻�蒼�p�O�p�`�̋��E�����`�̍����iY�������̒����j
     * @param pos_info ���p�ʒu�iPOS_R_TRIANGLE_**)
     * @param rot_z �����蔻��̒��p�O�p�`���AActor�̌����ɔ�����Actor���[�J��Z���𒆐S�ɉ�]���s�ړ����s���ꍇ true
     */
    void set2DColliRightTriangle_WH(int prm_index, coord x, coord y, coord prm_width, coord prm_height, pos_t pos_info, bool rot_z=false) {
        int hw = prm_width  / 2;
        int hh = prm_height / 2;
        set2DColliRightTriangle(prm_index, x-hw, y-hh, x+hw, y+hh, pos_info, rot_z);
    }

    /**
     * �����蔻��̈�v�f�������s���p�񓙕ӎO�p�`�Ƃ��Ē�` .
     * �����蔻�蒼�p�O�p�`�̋��E�����`�̒��S���W�ƁA�P�ӂ̒����Ŏw��
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x �����蔻�蒼�p�O�p�`�̋��E�����`�̒��SX���W�iActor���[�J�����W�j
     * @param y �����蔻�蒼�p�O�p�`�̋��E�����`�̒��SY���W�iActor���[�J�����W�j
     * @param prm_width �����蔻�蒼�p�O�p�`�̋��E�����`�̂P�ӂ̒����i�Εӂł͂���܂���j
     * @param pos_info ���p�ʒu�iPOS_R_TRIANGLE_**)
     * @param rot_z �����蔻��̒��p�O�p�`���AActor�̌����ɔ�����Actor���[�J��Z���𒆐S�ɉ�]���s�ړ����s���ꍇ true
     */
    void set2DColliIsoRightTriangle(int prm_index, coord x, coord y, coord prm_edge, pos_t pos_info, bool rot_z=false) {
        int h = prm_edge / 2;
        set2DColliRightTriangle(prm_index, x-h, y-h, x+h, y+h, pos_info, rot_z);
    }

    /**
     * �����蔻��̈�v�f�������s���p�񓙕ӎO�p�`�Ƃ��Ē�` .
     * �����蔻�蒼�p�O�p�`�̋��E�����`�̒��S���W�ƁA�P�ӂ̒����Ŏw��B
     * �����蔻�蒼�p�O�p�`�̋��E�����`�̒��S���W�́AActor���[�J�����W�̌��_�ɐݒ肳���B
     * (�K���Εӂ�Actor���[�J�����W�̌��_�ɐڂ��邱�ƂɂȂ�)
     * Actor�̌����ɔ����ē����蔻��̉�]���s�ړ��@�\�͖����B
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x �����蔻�蒼�p�O�p�`�̋��E�����`�̒��SX���W�iActor���[�J�����W�j
     * @param y �����蔻�蒼�p�O�p�`�̋��E�����`�̒��SY���W�iActor���[�J�����W�j
     * @param prm_width �����蔻�蒼�p�O�p�`�̋��E�����`�̂P�ӂ̒����i�Εӂł͂���܂���j
     * @param pos_info ���p�ʒu�iPOS_R_TRIANGLE_**)
     * @param rot_z �����蔻��̒��p�O�p�`���AActor�̌����ɔ�����Actor���[�J��Z���𒆐S�ɉ�]���s�ړ����s���ꍇ true
     */
    void set2DColliIsoRightTriangle(int prm_index, coord prm_edge, pos_t pos_info) {
        set2DColliIsoRightTriangle(prm_index, 0, 0, prm_edge, pos_info, false);
    }

    virtual ~CollisionChecker();
};

}
#endif /*GGAFLIB_COLLISIONCHECKER_H_*/

