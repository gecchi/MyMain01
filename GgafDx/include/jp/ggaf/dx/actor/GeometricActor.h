#ifndef GGAF_DX_GEOMETRICACTOR_H_
#define GGAF_DX_GEOMETRICACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/BaseActor.h"

#include "jp/ggaf/dx/util/curve/CurveManufacture.h"
#include <D3dx9math.h>

namespace GgafDx {

/**
 * ���W�A��]�A�X�P�[�������������A�N�^�[.
 * ���[���h���W�A�����͕ϊ��ςݍ��W�̉��ꂩ�������A<BR>
 * ���W�֘A���\�b�h��������A�N�^�[�ł��B<BR>
 * (��UntranceformedActor ��TranceformedActor �𓝍�)
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class GeometricActor : public BaseActor {

private:
    /**
     * ���ʂŎg�p�֎~ .
     */
    void processFinal() override {
    }

    /** [r]�͎� */
    VecVehicle* _pVecVehicle;
    /** [r]����(���s�ړ��x��) */
    AxisVehicle* _pAxisVehicle;

    GeoVehicle* _pGeoVehicle;

    /** [r]�g��k���x�� */
    Scaler* _pScaler;
    /** [r]���ʉ������Ǘ��I�u�W�F�N�g */
    SeTransmitterForActor* _pSeTransmitter;

    VehicleLeader* _pVehicleLeader;

public:
    /** [r] �ϊ��ςݍ��W�ł��邩(true:�{�A�N�^�[�͕ϊ��ςݍ��W/false:�{�A�N�^�[�̓��[���h���W) */
    bool _is_fix_2D;
    /** [r] ��ʊO��ʁBisOutOfView()�������Ŏg�p�B���v�Z���� -1 */
    int _offscreen_kind;

    /** [r/w]���[���hX���W( _x : DirectX��X���W : �����J�����ʒu�ł̉�ʏ�s�N�Z�� = 1000 : 0.1 : �� 1px  ) */
    coord _x;
    /** [r/w]���[���hY���W( _y : DirectX��Y���W : �����J�����ʒu�ł̉�ʏ�s�N�Z�� = 1000 : 0.1 : �� 1px  ) */
    coord _y;
    /** [r/w]���[���hZ���W( _z : DirectX��Z���W : �����J�����ʒu�ł̉�ʏ�s�N�Z�� = 1000 : 0.1 : �� 1px  ) */
    coord _z;
    /** [r/w]���[���hX����]�p(_rx : Degree = 1000 : 1�x) */
    angle _rx;
    /** [r/w]���[���hY����]�p(_ry : Degree = 1000 : 1�x) */
    angle _ry;
    /** [r/w]���[���hZ����]�p(_rz : Degree = 1000 : 1�x) */
    angle _rz;
    /** [r/w]���[���hX�������X�P�[��(_sx : �{�� = 1000 : 1.0�{) */
    scale _sx;
    /** [r/w]���[���hY�������X�P�[��(_sy : �{�� = 1000 : 1.0�{) */
    scale _sy;
    /** [r/w]���[���hZ�������X�P�[��(_sz : �{�� = 1000 : 1.0�{) */
    scale _sz;
    /** [r]�`�F�b�J�[ */
    CollisionChecker* _pChecker;

    /** [r]���f���̋��E�����a�{�� */
    dxcoord _rate_of_bounding_sphere_radius;
    /** [r]������ _x ����v�Z�����DirectX�̃��[���hX���W(_x : _fX = 1000 : 0.1) */
    dxcoord _fX;
    /** [r]������ _y ����v�Z�����DirectY�̃��[���hY���W(_y : _fY = 1000 : 0.1) */
    dxcoord _fY;
    /** [r]������ _z ����v�Z�����DirectZ�̃��[���hZ���W(_z : _fZ = 1000 : 0.1) */
    dxcoord _fZ;
    /** [r]�������ʂ��王��O�Ɍ������Ă̎��g�̍��W�܂ł�DirectX�̋����A������̋����͕��̒l�ɂȂ� */
    dxcoord _dest_from_vppln_top;
    /** [r]�����䉺�ʂ��王��O�Ɍ������Ă̎��g�̍��W�܂ł�DirectX�̋����A������̋����͕��̒l�ɂȂ� */
    dxcoord _dest_from_vppln_bottom;
    /** [r]�����䍶�ʂ��王��O�Ɍ������Ă̎��g�̍��W�܂ł�DirectX�̋����A������̋����͕��̒l�ɂȂ� */
    dxcoord _dest_from_vppln_left;
    /** [r]������E�ʂ��王��O�Ɍ������Ă̎��g�̍��W�܂ł�DirectX�̋����A������̋����͕��̒l�ɂȂ� */
    dxcoord _dest_from_vppln_right;
    /** [r]�������O�ʂ��王��O�Ɍ������Ă̎��g�̍��W�܂ł�DirectX�̋����A������̋����͕��̒l�ɂȂ� */
    dxcoord _dest_from_vppln_infront;
    /** [r]�����䉜�ʂ��王��O�Ɍ������Ă̎��g�̍��W�܂ł�DirectX�̋����A������̋����͕��̒l�ɂȂ� */
    dxcoord _dest_from_vppln_back;
    /** [r/w]WORLD�ϊ�(��]�~�ړ�)�s��v�Z�֐� */
    void (*_pFunc_calc_rot_mv_world_matrix)(const GeometricActor* const, D3DXMATRIX&);
    /** [r]���g�̌��݂�World�ϊ��s��(�ʏ�́u�g��k���~��]�~�ړ��v)�B�y�䂪����ꍇ�́A���̓y��ƍs��̐ςɂȂ��Ă���B */
    D3DXMATRIX _matWorld;
    /** [r]���g�̌��݂�World�ϊ��s��́u��]�~�ړ��v�̂݁B�y�䂪����ꍇ�́A���̓y��ƍs��̐ςɂȂ��Ă���B */
    D3DXMATRIX _matWorldRotMv;
    /** [r]���g�̌��݂�World�ϊ��s��́u��]�~�ړ��v�̋t�s��(��]�~�ړ��̃C���o�[�X) */
    D3DXMATRIX _matInvWorldRotMv;
    /** [r]�J�����g�t���[���Ŏ��g�̌��݂�World�ϊ��s��̋t�s��(_matInvWorldRotMv)���v�Z���ċ��߂����ǂ����̃t���O�B */
    bool _was_calculated_matInvWorldRotMv;

    /** [r]�y��ƂȂ�A�N�^�[�A�y�䂪�����ꍇ��nullptr�iFK�p�j */
    GeometricActor* _pActor_base;
    /** [r]�y��A�N�^�[��ł̃��[���hX���W */
    coord _x_local;
    /** [r]�y��A�N�^�[��ł̃��[���hY���W */
    coord _y_local;
    /** [r]�y��A�N�^�[��ł̃��[���hZ���W */
    coord _z_local;
    /** [r]�y��A�N�^�[��ł̃��[���hX����]�p */
    angle _rx_local;
    /** [r]�y��A�N�^�[��ł̃��[���hY����]�p */
    angle _ry_local;
    /** [r]�y��A�N�^�[��ł̃��[���hZ����]�p */
    angle _rz_local;

    coord _x_final;
    coord _y_final;
    coord _z_final;
    angle _rx_final;
    angle _ry_final;
    angle _rz_final;

    bool _is_local;

    //�⑫����
    //�y_x, _y, _z �̒P�ʂɂ��āz
    //�{�t���[�����[�N�ł́A�R�̍��W�P��(�X�P�[��)������B
    //dxcoord  �E�E�E DirectX���W�P�ʁB
    //coord    �E�E�E �A�v���P�[�V�����Ǝ��̓������W�P�ʁB�i���ꂪ���C���j
    //pixcoord �E�E�E �J�����������ʒu���Az=0 �� xy���ʂɃL�����������ꍇ�́A��ʏ�ł̃s�N�Z���l�P��
    //���W�l _x, _y, _z �� coord (���ꂪ���C��)�ł���B
    //DirectX���W(float)�n�̒l��1.0�ɑ������� _x, _y, _z ���W�l�́ALEN_UNIT(=1000)�{��PX_UNIT(=10)�{�̐����l�ł���B
    //�܂��ADirectX���W�n�P�ʂ�1.0�́A�Q�[����ʏ��10px�����̑傫���ɂȂ�i�悤�ɃJ�����������Ă���j�B
    //�Ⴆ�΁A_x = 5000 �́A��ʂŏ����J�����ʒu�� 5px �̕��Ɍ����ADirectX���W�ł�0.5�ɂȂ�i�悤�ɐ݌v���Ă���j�B
    //_x,_y,_z     �� �s�N�Z�� �̕ϊ��B    �E�E�E _x,_y,_z �� LEN_UNIT(=1000)�Ŋ���B
    //DirectX���W  �� �s�N�Z�� �̕ϊ��B    �E�E�E DirectX���W���APX_UNIT(=10)���|���Z����B
    //_x,_y,_z     �� DirectX���W �̕ϊ��B �E�E�E _x,_y,_z �� LEN_UNIT*PX_UNIT(=10000)�Ŋ���B
    //���́A�`��̒��O��_x,_y,_z ����͂Ƃ��āA LEN_UNIT*PX_UNIT ���Z���A���[���h�ϊ��s��̒l�Ɏg�p����Ă���B
    //�킴�킴����Ȃ��Ƃ����Ă���̂́A�Q�[�����̍��W�v�Z�͑S�Đ����ōs���A�����ł����x���グ�����������߁B
    //��(�����;)�͂悭�g���Ă�����@�Ǝv���̂����A���݂ł� �œK������Ă��� float �� double �ł����Ȃ葬���̂ŁA
    //�{���ɂ��̐݌v�ł悩�����̂��낤���c�A����A�����Ȃ��Ă�ƐM����B
    //
    //�y_rx, _ry, _rz �̒P�ʂɂ��āz
    //�Ǝ��P�ʂ́u�A���O���l�v���̂�B
    //�u�A���O���l�v�Ƃ� 0~3600000 �̒l�ŁA�����ڂł� �p�x�l(Degree)�� 1000�{�̐��x�̒l�ł���B
    //(�A���A���ۂ͓����ł� Degree �� 10�{�̐��x�ł���B3600�����̒P�ʕ����x�N�g���e�[�u���ƑΉ�������݌v)
    //1�x��1000�A0.5�x��500�B���p�̒l��90000�A������180000�ł���B
    //���S�p�Ɠ�����3���̕�����0�Ƃ��A���̐������������Ĕ����v���ɃA���O���l�͑�������̂Ƃ���B
    //
    //�y_sx, _sy, _sz �̒P�ʂɂ��āz
    //�l1000��1.0�{�̃X�P�[���Ӗ�����B���������ăf�t�H���g��1000�ɂȂ��Ă���B
    //�`��̒��O�� 1000 �ŏ��Z����A�g��k�����ɕϊ����g�p����B

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name �A�N�^�[��
     * @param prm_pChecker �`�F�b�J�[(�g�p���Ȃ��� nullptr)
     * @return
     */
    GeometricActor(const char* prm_name,
                   CollisionChecker* prm_pChecker);

    virtual GeometricActor* getPrev() const override { //���ς̖߂�l
        return (GeometricActor*)GgafCore::Actor::getPrev();
    }

    virtual GeometricActor* getNext() const override { //���ς̖߂�l
        return (GeometricActor*)GgafCore::Actor::getNext();
    }

    void setCollisionChecker(CollisionChecker* prm_pChecker);

    CollisionChecker* getCollisionChecker() {
        return _pChecker;
    }
    /**
     * �{�A�N�^�[�̗͎Ԃ��擾 .
     * @return �͎�
     */
    VecVehicle* getVecVehicle();

    /**
     * �{�A�N�^�[�̉���(���s�ړ��x��)�I�u�W�F�N�g���擾 .
     * @return ����(���s�ړ��x��)�I�u�W�F�N�g
     */
    AxisVehicle* getAxisVehicle();

    GeoVehicle* getGeoVehicle();

    virtual VehicleLeader* createCurveVehicleLeader(CurveManufacture* prm_pCurveManufacture);

    /**
     * VehicleLeader �� FeatureScene �Ɋ֘A�t����B
     * FeatureScene�̉e����VehicleLeader��ݒ肷��B
     * @param prm_pVehicleLeader
     */
    void setVehicleLeader(GgafDx::VehicleLeader* prm_pVehicleLeader) {
        _pVehicleLeader = prm_pVehicleLeader;
    }

    VehicleLeader* getVehicleLeader() {
        return _pVehicleLeader;
    }

    /**
     * �{�A�N�^�[�̊g��k���x���I�u�W�F�N�g���擾 .
     * @return �g��k���x���I�u�W�F�N�g
     */
    Scaler* getScaler();

    /**
     * �{�A�N�^�[�̃T�E���h�G�t�F�N�g�o�͎x���I�u�W�F�N�g���擾 .
     * @return �T�E���h�G�t�F�N�g�o�͎x���I�u�W�F�N�g
     */
    SeTransmitterForActor* getSeTransmitter();

    /**
     * ���菈�����O���� .
     * processBehavior() ��A���W�v�Z���㏈���Ƃ��Ď��̏������s�� <BR>
     * �@ �y�䂪�A�N�^�[������ꍇ�́A�������[���h�ϊ��s������߂�B<BR>
     * �A �g��k������]�����s�ړ��̃��[���h�ϊ��s����\�z�B<BR>
     * �B �y�䂪�A�N�^�[������ꍇ�́A�������[���h�ϊ��s����s��̐�΍��W�����߂�B<BR>
     * �C ���g�̍��W���(_x,_y,_z)����ȉ��̃����o�̍X�V���s���B <BR>
     *     _fX <BR>
     *     _fY <BR>
     *     _fZ <BR>
     * �D ��ʓ��O�𔻒肷�邽�߂́A������̊e�ʂƂ̋������v�Z�ȉ��̃����o�̍X�V���s���B <BR>
     *     _dest_from_vppln_top <BR>
     *     _dest_from_vppln_bottom <BR>
     *     _dest_from_vppln_left <BR>
     *     _dest_from_vppln_right <BR>
     *     _dest_from_vppln_infront <BR>
     *     _dest_from_vppln_back <BR>
     * �{���\�b�h�̓I�[�o�[���C�h�\�Ƃ��邪�A�t���[�����[�N�̕`��┻��Ɋւ��
     * �d�v�Ȏ��O�����̂��߁A�I�[�o�[���C�h�͐����ł��Ȃ��B<BR>
     * �ǂ����Ă��I�[�o�[���C�h���K�v�ȏꍇ�́A�I�[�o�[���C�h��ŁA <BR>
     * GeometricActor::processSettlementBehavior() ���Ăяo�����A <BR>
     * ��L�Ɠ����̏������s���悤�ɂ��ׂ��ł���B
     * �t�Ɍ��ʃG�t�F�N�g�ȂǁA��L�̍l�����s�v�ȃA�N�^�[�̏ꍇ�́A�{���\�b�h���I�[�o�[���C�h���A
     * _fX,_fY,_fZ�̂ݍX�V�����������邱�Ƃɂ��A�p�t�H�[�}���X�����コ���邱�Ƃ��ł���B <BR>
     */
    virtual void processSettlementBehavior() override;

    virtual void processPreJudgement() override;

    /**
     * ���ʂ̕`�掖�㏈�� .
     * ���f�o�b�O���[�h (MY_DEBUG �� 1)�̏ꍇ��
     * �����蔻��̈��`�悷��B
     * (�Ƃ����Ă� drawHitArea() ���R�[�����邾��)
     */
    virtual void processAfterDraw() override;

    /**
     * ��΍��W�v�Z��̏��� .
     * �y��ƂȂ�A�N�^�[(_pActor_base) ������ꍇ�AprocessSettlementBehavior() ����
     * ��΍��W�v�Z��ɍs���ꂽ�ォ��A�����ؓo�^�̒��O�ɃR�[���o�b�N�����B
     * �y��ɏ������A�N�^�[����e�𔭎˂������ꍇ����z��B��΍��W�Ŏw��ł���B
     */
    virtual void processChangeGeoFinal() {
    }

    /**
     * �����蔻�胍�W�b�N .
     * �����蔻�胍�W�b�N���������Ă���B<BR>
     * �`�F�b�J�[�I�u�W�F�N�g������ꍇ�A<BR>
     * CollisionChecker::isHit() �Ŕ��肷��B<BR>
     * �`�F�b�J�[�I�u�W�F�N�g�������ꍇ�A<BR>
     * �q�b�g���Ă��Ȃ����ƂƂ���B<BR>
     * @param prm_pOtherActor ����̃A�N�^�[
     * @return true�F�q�b�g���Ă���^false�F�q�b�g���Ă��Ȃ�
     */
    virtual bool processHitChkLogic(GgafCore::Actor* prm_pOtherActor) override;

    /**
     * �����蔻��̈��`�� .
     * ���ۂ̏����͉��ʃN���X�ɔC����B
     */
    virtual void drawHitArea() {};

    /**
     * ��ʓ��ɕ\������Ă��邩���� .
     * @return 0(false):Viewport�͈͓�
     *         1       :Viewport������̏㕽�ʂ���Ŕ͈͊O
     *         2       :Viewport������̉����ʂ�艺�Ŕ͈͊O
     *         3       :Viewport������̍����ʂ�荶�Ŕ͈͊O
     *         4       :Viewport������̉E���ʂ��E�Ŕ͈͊O
     *         5       :Viewport������̎�O���ʂ���O�Ŕ͈͊O
     *         6       :Viewport������̉����ʂ�艜�Ŕ͈͊O
     *         ������D�揇�ʏ��ɕ���ł��܂��B�i��F1 ���� 4 �� 1 ���Ԃ�܂��j
     */
    virtual int isOutOfView();

    /**
     * ���݂̍��W�����̐��̊O���Ȃ̂��ۂ� .
     * ��ʓ��A��ʊO�Ƃ͖��֌W
     * @return true:���̐��̊O��/false:���̐��̓���
     */
    virtual bool isOutOfSpacetime() const;

    /**
     * ���W��ݒ� .
     * @param x
     * @param y
     * @param z
     */
    virtual void setPosition(coord x, coord y, coord z) {
        _x = x;
        _y = y;
        _z = z;
    }

    /**
     * ���W��ݒ� .
     * z���W�͍X�V���Ȃ��B
     * @param x
     * @param y
     */
    virtual void setPosition(coord x, coord y) {
        _x = x;
        _y = y;
    }

    /**
     * ���W���w����W�t�߂ɓK���ɐݒ� .
     * @param x �͈͒��SX���W
     * @param y �͈͒��SY���W
     * @param z �͈͒��SZ���W
     * @param r �͈͋��̔��a
     */
    virtual void setPositionAround(coord x, coord y, coord z, coord r);

    /**
     * ���W���w����W�t�߂ɓK���ɐݒ� .
     * @param x �͈͒��SX���W
     * @param y �͈͒��SY���W
     * @param r �͈͉~�̔��a
     */
    virtual void setPositionAround(coord x, coord y, coord r);

    /**
     * 3D�A�N�^�[�ɂ��āA�r���[���W�Ŏw��ɂ��A���g��Ή����郏�[���h���W�ɔz�u���� .
     * @param prm_view_x �r���[���WX���v�f
     * @param prm_view_y �r���[���WY���v�f
     * @param prm_depth �J�������_����̋���
     */
    void setPositionByViewCoord(coord prm_view_x, coord prm_view_y, coord prm_depth);

    /**
     * 2D�A�N�^�[�ɂ��āA���g�̃r���[���W���A�Ή����郏�[���h���W���擾���� .
     * @param prm_depth �擾���������[���h���W�̃J�������_����̋������w��
     * @param out_world_x �Ή����郏�[���h���WX���v�f
     * @param out_world_y �Ή����郏�[���h���WY���v�f
     * @param out_world_z �Ή����郏�[���h���WZ���v�f
     */
    void getWorldPosition(coord prm_depth, coord& out_world_x, coord& out_world_y, coord& out_world_z);

    /**
     * 2D�A�N�^�[�ɂ��āA���[���h���W�Ŏw��ɂ��A���g��Ή�����r���[���W�ɔz�u���� .
     * @param prm_world_x ���[���h���WX���v�f
     * @param prm_world_y ���[���h���WY���v�f
     * @param prm_world_z ���[���h���WZ���v�f
     */
    void setPositionByWorldCoord(coord prm_world_x, coord prm_world_y, coord prm_world_z);

    /**
     * 3D�A�N�^�[�ɂ��āA���g�̃��[���h���W���A�Ή�����r���[���W���擾���� .
     * @param out_view_x �Ή�����r���[���WX���v�f
     * @param out_view_y �Ή�����r���[���WY���v�f
     */
    void getViewPosition(coord& out_view_x, coord& out_view_y);
    /**
     * X��Y��Z���e���X�P�[�� _sx, _sy, _sz �𓯂��l�Őݒ� .
     * �y���Ӂz
     * pScaler_->behave(); �����݂���Ə㏑������܂���B
     * @param S �X�P�[���l(1000 �� 1.0�{)
     */
    virtual void setScale(scale s) {
        _sx = s;
        _sy = s;
        _sz = s;
        setBoundingSphereRadiusRate(SC_R(s));
    }

    /**
     * X��Y��Z���X�P�[�� _sx, _sy, _sz �����ꂼ��l�Őݒ� .
     * �y���Ӂz
     * pScaler_->behave(); �����݂���Ə㏑������܂���I�B
     * @param sx X���X�P�[���l(1000 �� 1.0�{)
     * @param sy Y���X�P�[���l(1000 �� 1.0�{)
     * @param sz Z���X�P�[���l(1000 �� 1.0�{)
     */
    virtual void setScale(scale sx, scale sy, scale sz) {
        _sx = sx;
        _sy = sy;
        _sz = sz;
        setBoundingSphereRadiusRate(SC_R(MAX3(_sx,_sy,_sz)));
    }

    /**
     * X��Y���X�P�[��(_sx, _sy)�݂̂�l�Őݒ� .
     * �y���Ӂz
     * pScaler_->behave(); �����݂���Ə㏑������܂���I�B
     * @param sx X���X�P�[���l(1000 �� 1.0�{)
     * @param sy Y���X�P�[���l(1000 �� 1.0�{)
     */
    virtual void setScale(scale sx, scale sy) {
        _sx = sx;
        _sy = sy;
        setBoundingSphereRadiusRate(SC_R(MAX3(_sx,_sy,_sz)));
    }

    /**
     * X��Y��Z���S�Ă̎��X�P�[���������Őݒ� .
     * 1.0 �� ���̃��f���̑傫������1.0�{�B
     * �y���Ӂz
     * pScaler_->behave(); �����݂���Ə㏑������܂���I�B
     * @param prm_rate �{��
     */
    virtual void setScaleR(float prm_rate) {
        _sx = R_SC(prm_rate);
        _sy = R_SC(prm_rate);
        _sz = R_SC(prm_rate);
        setBoundingSphereRadiusRate(prm_rate);
    }

    /**
     * X��Y��Z���e���X�P�[���������Őݒ� .
     * 1.0 �� ���̃��f���̑傫������1.0�{�B
     * �y���Ӂz
     * pScaler_->behave(); �����݂���Ə㏑������܂���I�B
     * @param prm_x_rate X���{��
     * @param prm_y_rate Y���{��
     * @param prm_z_rate Z���{��
     */
    virtual void setScaleR(float prm_x_rate, float prm_y_rate, float prm_z_rate) {
        _sx = R_SC(prm_x_rate);
        _sy = R_SC(prm_y_rate);
        _sz = R_SC(prm_z_rate);
        setBoundingSphereRadiusRate(MAX3(prm_x_rate, prm_y_rate, prm_z_rate));
    }

    /**
     * X��Y���̂݃X�P�[���������Őݒ� .
     * 1.0 �� ���̃��f���̑傫������1.0�{�B
     * �y���Ӂz
     * pScaler_->behave(); �����݂���Ə㏑������܂���I�B
     * @param prm_x_rate X���{��
     * @param prm_y_rate Y���{��
     */
    virtual void setScaleR(float prm_x_rate, float prm_y_rate) {
        _sx = R_SC(prm_x_rate);
        _sy = R_SC(prm_y_rate);
        setBoundingSphereRadiusRate(MAX3(prm_x_rate, prm_y_rate, SC_R(_sz)));
    }

    /**
     * X��Y��Z���e���X�P�[�� _sx, _sy, _sz �𓯂��l�ŉ��Z .
     * �y���Ӂz
     * pScaler_->behave(); �����݂���Ə㏑������܂���I�B
     * @param dS ���Z����X�P�[���l
     */
    virtual void addScale(scale dS) {
        _sx += dS;
        _sy += dS;
        _sz += dS;
        setBoundingSphereRadiusRate(SC_R(MAX3(_sx,_sy,_sz)));
    }

    virtual void addScaleX(scale dsx) {
        _sx += dsx;
        setBoundingSphereRadiusRate(SC_R(MAX3(_sx,_sy,_sz)));
    }
    virtual void addScaleY(scale dsy) {
        _sy += dsy;
        setBoundingSphereRadiusRate(SC_R(MAX3(_sx,_sy,_sz)));
    }
    virtual void addScaleZ(scale dsz) {
        _sz += dsz;
        setBoundingSphereRadiusRate(SC_R(MAX3(_sx,_sy,_sz)));
    }
    /**
     * ���W(_x, _y, _z)���R�s�[���Đݒ� .
     * @param prm_pActor ���W�R�s�[���A�N�^�[
     */
    virtual void setPositionAt(const GeometricActor* prm_pActor) {
        _x = prm_pActor->_x;
        _y = prm_pActor->_y;
        _z = prm_pActor->_z;
    }

    /**
     * �w��̃A�N�^�[�Ǝ�Y��Z���e���X�P�[�� _sx, _sy, _sz ���R�s�[���Đݒ� .
     * @param prm_pActor ���W�R�s�[���A�N�^�[
     */
    virtual void setScaleAt(const GeometricActor* prm_pActor) {
        setScale(prm_pActor->_sx, prm_pActor->_sy, prm_pActor->_sz);
    }

    /**
     * �w��̃A�N�^�[�Ɠ������W(_x, _y, _z)���R�s�[���Đݒ� .
     * @param prm_pGeoElem ���W�I�u�W�F�N�g
     */
    virtual void setPositionAt(const GeoElem* prm_pGeoElem);

    /**
     * �w��̃A�N�^�[�Ɠ������W(_x, _y, _z)�Ƀ����_���ȗV�т����Z���Đݒ� .
     * @param prm_pActor ���W�R�s�[���A�N�^�[
     * @param r �͈͋��̔��a
     */
    virtual void setPositionAroundAt(const GeometricActor* prm_pActor, coord r);

    /**
     * �w��̍��W�I�u�W�F�N�g�Ƀ����_���ȗV�т����Z���Đݒ� .
     * @param prm_pGeoElem  ���W�I�u�W�F�N�g
     * @param r �͈͋��̔��a
     */
    virtual void setPositionAroundAt(const GeoElem* prm_pGeoElem, coord r);

    /**
     * ��]�p�x _rx, _ry, _rz ���R�s�[���Đݒ� .
     * @param prm_pActor �R�s�[���A�N�^�[
     */
    virtual void setFaceAngAs(const GeometricActor* prm_pActor);

    /**
     * ��]�p�x _rx, _ry, _rz ���R�s�[���Đݒ� .
     * @param prm_pGeoElem ���W�I�u�W�F�N�g
     */
    virtual void setFaceAngAs(const GeoElem* prm_pGeoElem);

    /**
     * X�����p�̃A���O���l��ݒ� .
     * @param prm_face �A���O���l(-360,000�`360,000)
     */
    virtual void setRzFaceAng(angle prm_face);

    /**
     * Y�����p�̃A���O���l��ݒ� .
     * @param prm_face �A���O���l(-360,000�`360,000)
     */
    virtual void setRyFaceAng(angle prm_face);

    /**
     * Z�����p�̃A���O���l��ݒ� .
     * @param prm_face �A���O���l(-360,000�`360,000)
     */
    virtual void setRxFaceAng(angle prm_face);

    virtual void setRollFaceAng(angle prm_face) {
        setRxFaceAng(prm_face);
    }

    virtual void setRzRyFaceAng(angle prm_rz_face, angle prm_ry_face);

    virtual void addRzFaceAng(angle prm_rz) {
        setRzFaceAng(_rz + prm_rz);
    }

    virtual void addRyFaceAng(angle prm_ry) {
        setRyFaceAng(_ry + prm_ry);
    }

    virtual void addRxFaceAng(angle prm_ang_rx) {
        setRxFaceAng(_rx + prm_ang_rx);
    }

    virtual void addRollFaceAng(angle prm_ang_rx) {
        setRxFaceAng(prm_ang_rx);
    }

    /**
     * Actor�̐��ʕ��p��ݒ� .
     * @param prm_axis_x_face X�����p�̃A���O���l(-360,000�`360,000)
     * @param prm_axis_z_face Z�����p�̃A���O���l(-360,000�`360,000)
     * @param prm_axis_y_face Y�����p�̃A���O���l(-360,000�`360,000)
     */
    virtual void setRollPitchYawFaceAng(angle prm_axis_x_face,
                                        angle prm_axis_z_face,
                                        angle prm_axis_y_face) {
        setRxFaceAng(prm_axis_x_face);
        setRzFaceAng(prm_axis_z_face);
        setRyFaceAng(prm_axis_y_face);
    }

    inline void setFaceAngZero() {
        _rx = _rz = _ry = 0;
    }

    /**
     * Actor�̎��g�̍��W����Ώۍ��W�_�Ɍ����������ɁAZ����]���p��Y����]���p��ݒ�<BR>
     * @param prm_tx �Ώۓ_X���W
     * @param prm_ty �Ώۓ_Y���W
     * @param prm_tz �Ώۓ_Z���W
     */
    virtual void setFaceAngTwd(coord prm_tx, coord prm_ty, coord prm_tz);

    /**
     * Actor�̎��g�̍��W����ΏۃA�N�^�[�Ɍ����������ɁAZ����]���p��Y����]���p��ݒ�<BR>
     * @param prm_pActor �ΏۃA�N�^�[
     */
    virtual void setFaceAngTwd(const GeometricActor* prm_pActor);

    /**
     * ���g�̓������[���h�ϊ�(_matWorldRotMv) �̋t�s��𖢌v�Z�Ȃ�v�Z���A�v�Z�ς݂Ȃ炻�̂܂ܕԂ� .
     * @return _matInvWorldRotMv
     */
    inline D3DXMATRIX* getInvMatWorldRotMv() {
        if (_was_calculated_matInvWorldRotMv) {
            return &_matInvWorldRotMv;
        } else {
            D3DXMatrixInverse(&_matInvWorldRotMv, nullptr, &_matWorldRotMv);
            _was_calculated_matInvWorldRotMv = true; //processSettlementBehavior()�Ń��Z�b�g�����
            return &_matInvWorldRotMv;
        }
    }

    /**
     * �����̃A�N�^�[���A���g�̎q�A�N�^�[�Ƃ��Ēǉ����A�p�����t�H���[�h�L�l�}�e�B�N�X�Őݒ肷�� .
     * �����̏]���A�N�^�[�́A���̂Q�̃��\�b�h�̎g�p���\�ƂȂ�܂��B <BR>
     * _x,_y,_z,_rx,_ry,_rz �����[�J���ithis����̑��΁j�ɐ؂�ւ���E�E�EchangeGeoLocal()<BR>
     * _x,_y,_z,_rx,_ry,_rz ��΍��W�ɐ؂�ւ���                    �E�E�EchangeGeoFinal()<BR>
     * �y���Ӂz<BR>
     * �͎�(getVecVehicle()) �́A���[�J�����W�n�ł̂ݎg�p�\�ƂȂ�܂��B<BR>
     * �]���A�N�^�[processBehavior() �̏����𔲂���O�ɂ́AchangeGeoFinal() �Ő�΍��W�ɖ߂��Ă����K�v������܂��B<BR>
     * @param prm_kind     ���
     * @param prm_pGeoActor �]��������A�N�^�[
     * @param prm_x_init_local  �]���A�N�^�[�̃��[�J��(this)�ʒu�����X���W�ʒu
     * @param prm_y_init_local  �]���A�N�^�[�̃��[�J��(this)�ʒu�����Y���W�ʒu
     * @param prm_z_init_local  �]���A�N�^�[�̃��[�J��(this)�ʒu�����Z���W�ʒu
     * @param prm_rx_init_local �]���A�N�^�[�̃��[�J��(this)��]�����X����]�l
     * @param prm_ry_init_local �]���A�N�^�[�̃��[�J��(this)��]�����Y����]�l
     * @param prm_rz_init_local �]���A�N�^�[�̃��[�J��(this)��]�����Z����]�l
     * @return ��ʃg�b�v�̒c��
     */
    virtual GgafCore::GroupHead* appendGroupChildAsFk(kind_t prm_kind,
                                                      GeometricActor* prm_pGeoActor,
                                                      int prm_x_init_local,
                                                      int prm_y_init_local,
                                                      int prm_z_init_local,
                                                      int prm_rx_init_local,
                                                      int prm_ry_init_local,
                                                      int prm_rz_init_local);

    /**
     * �����̃A�N�^�[���A���g�̎q�A�N�^�[�Ƃ��Ēǉ����A�p�����t�H���[�h�L�l�}�e�B�N�X�Őݒ肷�� .
     * �����̏]���A�N�^�[�́A���̂Q�̃��\�b�h�̎g�p���\�ƂȂ�܂��B <BR>
     * _x,_y,_z,_rx,_ry,_rz �����[�J���ithis����̑��΁j�ɐ؂�ւ���E�E�EchangeGeoLocal()<BR>
     * _x,_y,_z,_rx,_ry,_rz ��΍��W�ɐ؂�ւ���                    �E�E�EchangeGeoFinal()<BR>
     * �y���Ӂz<BR>
     * �͎�(getVecVehicle()) �́A���[�J�����W�n�ł̂ݎg�p�\�ƂȂ�܂��B<BR>
     * �]���A�N�^�[processBehavior() �̏����𔲂���O�ɂ́AchangeGeoFinal() �Ő�΍��W�ɖ߂��Ă����K�v������܂��B<BR>
     * @param prm_pGeoActor �]��������A�N�^�[
     * @param prm_x_init_local  �]���A�N�^�[�̃��[�J��(this)�ʒu�����X���W�ʒu
     * @param prm_y_init_local  �]���A�N�^�[�̃��[�J��(this)�ʒu�����Y���W�ʒu
     * @param prm_z_init_local  �]���A�N�^�[�̃��[�J��(this)�ʒu�����Z���W�ʒu
     * @param prm_rx_init_local �]���A�N�^�[�̃��[�J��(this)��]�����X����]�l
     * @param prm_ry_init_local �]���A�N�^�[�̃��[�J��(this)��]�����Y����]�l
     * @param prm_rz_init_local �]���A�N�^�[�̃��[�J��(this)��]�����Z����]�l
     * @return ��ʃg�b�v�̒c��
     */
    virtual GgafCore::GroupHead* appendGroupChildAsFk(GeometricActor* prm_pGeoActor,
                                                      int prm_x_init_local,
                                                      int prm_y_init_local,
                                                      int prm_z_init_local,
                                                      int prm_rx_init_local,
                                                      int prm_ry_init_local,
                                                      int prm_rz_init_local);

    /**
     * ���W�Ɖ�] _x,_y,_z,_rx,_ry,_rz ���΍��W�n��ޔ����āA���[�J�����W(�y�䂩��̑��΍��W)�ɒu�������� .
     */
    void changeGeoLocal();

    /**
     * ���W�Ɖ�] _x,_y,_z,_rx,_ry,_rz ��ޔ����Ă�����΍��W�ɖ߂� .
     * ���[�J�����W�̕ύX�ɔ�����΍��W�̍X�V�́AprocessSettlementBehavior()�ōs������ɂȂ��Ă���B<BR>
     * processBehavior() �̏����̍Ō�Ŏ��s���邱�Ƃ�z��B<BR>
     * ���������āAchangeGeoFinal() �ō��W�X�V�����킯�ł͂Ȃ��̂Œ��ӁB<BR>
     */
    void changeGeoFinal();

//    void updateGeoFinalFromLocal();

    /**
     * �{�A�N�^�[��3D�̏ꍇ�A ��]�~�ړ��̃��[���h�ϊ��s����v�Z����֐����` .
     * ���ʏ����i processSettlementBehavior() �j�ŁA�g��k���͂��̃��[���h�ϊ��s��̑O�ɏ悶���A
     * �ŏI�I�ȍs�������������B����āA���[���h�ϊ��̓f�t�H���g�ŁA�g��k���~��]�~�ړ��B<BR>
     * �ʏ�̕`��\�ȃA�N�^�[�́AUtil::setWorldMatrix_RxRzRyMv() �����ݒ�ς݂̂���
     * �Ăяo���K�v���Ȃ��B<BR>
     * �`�悳��Ȃ��A�N�^�[��A�r���{�[�h���s�������ꍇ���̏ꍇ�ɕK�v�Ɩژ_�ށB<BR>
     * @param prm_pFunc ��]�~�ړ��̍s��쐬�֐��ւ̃|�C���^
     */
    void defineRotMvWorldMatrix(void (*prm_pFunc)(const GeometricActor*, D3DXMATRIX&));

    /**
     * ���[���h�ϊ��s��� Billboard �ɐݒ肷�� .
     * �A�� _rz �ω��̉�]���L���B
     */
    void defineRotMvWorldMatrix_Billboard();

    /**
     * ���f���̋��E�����a�̔{���ݒ� .
     * ���E�����a�Ƃ́A���[�J�����W�̌��_����S���_�̋����ōő�̒����ŁA
     * ���̒l�́A��ʊO����ɗ��p����Ă邽�߁A���f���\�����ɓƎ��Ɋg����s�����ꍇ�B
     * ���̒l���X�V���Ȃ��Ɖ�ʊO���肪�������s���Ȃ��B<BR>
     * �Ⴆ�΁A�\�����ɂT�{�̊g��ŕ\�������ꍇ�A�{���\�b�h��<BR>
     * <BR>
     * setBoundingSphereRadiusRate(5.0)<BR>
     * <BR>
     * �Ƃ���ƁA��ʊO���肪�������Ȃ�B<BR>
     * ��ʊO���肪�������Ȃ�Ƃ́A��̓I�ɂ́AisOutOfView() �̔���v�Z���ɉe����^����
     * �Ƃ����Ӗ��ł���B<BR>
     * @param prm_rate �g�嗦
     */
    inline void setBoundingSphereRadiusRate(FLOAT prm_rate) {
        _rate_of_bounding_sphere_radius = prm_rate;
    }


    virtual void onEnd() override;

    /**
     * �y��ƂȂ�A�N�^�[���擾 .
     * �y��Ƃ́AappendGroupChildAsFk() �ɂ���Ēǉ����ꂽ���̃I�u�W�F�N�g���A
     * appendGroupChildAsFk()�����s�����A�N�^�[���w���B
     * @return �y��ƂȂ�A�N�^�[
     */
    inline GeometricActor* getBaseActor() const {
        return _pActor_base;
    }

    /**
     * �f�X�g���N�^
     */
    virtual ~GeometricActor();

    /**
     * �f�o�b�O�p�F�c���[�\����\��<BR>
     */
    virtual void dump();

    /**
     * �f�o�b�O�p�Fdump()����g�p�����<BR>
     */
    virtual void dump(std::string prm_parent);

};

}
#endif /*GGAF_DX_GEOMETRICACTOR_H_*/
