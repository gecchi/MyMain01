#ifndef GGAF_DX_CURVEMANUFACTURE_H_
#define GGAF_DX_CURVEMANUFACTURE_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include <string>

namespace GgafDx {

/**
 * �X�v���C���Ȑ��ړ��̂��߂̏��Z�b�g .
 * �S�ẴA�N�^�[�ɋ��ʂ���X�v���C���̏��͂����ɏW��B<BR>
 * �I�u�W�F�N�g�̊֌W<BR>
 * DriverLeader       �e�A�N�^�[���ɐ��������B
 *                    �A�N�^�[�ɑ΂���A�X�v���C���Ȑ���̌��݂̕⊮�_�̈ʒu�E���ԁE�������̊Ǘ����s���A
 *                    �͎�(VecDriver)�Ɏw�����o���ăA�N�^�[���ړ�������B
 *                    �P�� CurveManufacture �I�u�W�F�N�g�ɑ΂��� N �� DriverLeader �I�u�W�F�N�g���Q�Ƃ��Ă���B
 *                    �X�v���C���̍��W�_�Ԃ̋����ɉe���̖������̓R�R�ŕێ�����B
 *                    �܂�X�v���C���Ȑ��̍��W�_�̎����s�ړ��I�t�Z�b�g�A
 *                    X,Y,Z�̐�������ւ����B�iTODO:�����́A��]�����R�R�Ɂj
 *
 * CurveManufacture   �X�v���C���Ȑ��̍��W�_�Z�b�g�̊g��k�����A�܂�����ɔ���DriverLeader�̎����N���X�̏���ێ��B
 *                    �g��k���ɂ��A�e�⊮�_���̋������̏���\�ߌv�Z���ĕێ����Ă���B
 *                    �g��k������ύX����ꍇ�́A���̃I�u�W�F�N�g�̃t�B�[���h���Čv�Z���K�v�ƂȂ�B
 *                    �P�� CurveSource �I�u�W�F�N�g�ɑ΂��� N �� CurveSource�I�u�W�F�N�g���Q�Ƃ��Ă���B
 *                    (��ldr�t�@�C���̏��ɑ�������B)
 *
 * CurveSource        �X�v���C���Ȑ��̍��W�_�Z�b�g�̏���ێ�����I�u�W�F�N�g�B
 *                    CurveSource �͐����Ɠ����ɁA�����̃t�@�C�����̊O���t�@�C����ǂݍ��݁A
 *                    ���W�̕⊮�_���v�Z���A�����ێ�����B
 *                    (��dat�t�@�C���̏��ɑ�������B)
 *
 * @version 1.00
 * @since 2011/08/05
 * @author Masatoshi Tsuge
 */
class CurveManufacture : public GgafCore::Object {

public:

    enum MoveMethod {
        FixedVelocity = 1,
        FixedFrame,
        SteppedCoord,
    };

    enum MoveDriver {
        GeoDriver = 1,
        VecDriver,
    };


    CurveSourceConnection* _pCurveSrcCon;
    /** [r]���W���(dat�t�@�C�����ɑ���)*/
    CurveSource* _pCurve;
    /** [r]�X�v���C�����W���t�@�C����(ldr�t�@�C��) */
    std::string _ldr_file;
    /** X�������␳���� */
    double _rate_x;
    /** Y�������␳���� */
    double _rate_y;
    /** Z�������␳���� */
    double _rate_z;
    /** [r]���̕⊮�_�܂ł̋����̃e�[�u�� */
    coord* _paDistance_to;
    /** [r]�����̍��v _paDistance_to[0] �` _paDistance_to[n]  */
    coord _total_distance;
    /** [r]�v�Z�ς݂ł��邩�ǂ��� */
    bool _is_calculated;


    MoveMethod _move_method;
    MoveDriver _move_driver;
public:
    /**
     * �R���X�g���N�^ .
     * @param prm_coord_spl_file �X�v���C�����W���t�@�C��(spl�t�@�C��)
     */
    explicit CurveManufacture(const char* prm_coord_spl_file);
    /**
     * �R���X�g���N�^ .
     * @param prm_pCurveSrc �X�v���C�����W���I�u�W�F�N�g
     */
    CurveManufacture(CurveSource* prm_pCurve);

    /**
     * �e�⊮�_���AX�������AY�������AZ���������ꂼ��Ɋ������悶�A�␳���܂� .
     * �f�t�H���g�� adjustAxisRate(1.0, 1.0, 1.0) �ƂȂ�܂��B<BR>
     * <b>[����]</b><BR>
     * ���̃��\�b�h�����s�����ꍇ�A�_�̓_�̋������ς�邽�߁A<BR>
     * ���ʃN���X�̎����ɂ���ẮA�����ێ��e�[�u�������X�V���邽�߂ɁA<BR>
     * ��calculate() �����s���Ȃ��Ɣ��f���܂���B
     * @param prm_rate_x X�������␳����
     * @param prm_rate_y Y�������␳����
     * @param prm_rate_z Z�������␳����
     */
    virtual void adjustAxisRate(double prm_rate_x, double prm_rate_y, double prm_rate_z);

    /**
     * �������i�v�Z�j���� .
     * _paDistance_to[] �� _total_distance ���v�Z���܂��B<BR>
     * �v���p�e�B��ύX�����ꍇ�A�����e�[�u�������X�V���邽�߂�
     * ��x���s����K�v������܂��B
     * ���ʂŌĂяo�����ĉ������B
     */
    virtual void calculate();


    virtual DriverLeader* createDriverLeader(GgafDx::GeometricActor* prm_pActor);

    /**
     * DriverLeader �I�u�W�F�N�g�̐��� .
     * �ݒ肵���͎Ԃ��A���삵�܂��̂Œ��ӂ��ĉ������B<br>
     * �{���\�b�h�ō쐬���� DriverLeader �́A�Ăь��� delete����K�v������܂��B<br>
     * @param prm_pVecDriver �Ώۂ̃A�N�^�[�̗͎�
     * @return
     */
    virtual DriverLeader* createVecDriverLeader(GgafDx::VecDriver* prm_pVecDriver);

    virtual DriverLeader* createGeoDriverLeader(GgafDx::GeoDriver* prm_pGeoDriver);

    virtual ~CurveManufacture();
};

}
#endif /*GGAF_DX_CURVEMANUFACTURE_H_*/
