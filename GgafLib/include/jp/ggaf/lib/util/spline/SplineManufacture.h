#ifndef GGAF_LIB_SPLINEMANUFACTURE_H_
#define GGAF_LIB_SPLINEMANUFACTURE_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include <string>

namespace GgafLib {

/**
 * �X�v���C���Ȑ��ړ��̂��߂̏��Z�b�g .
 * �S�ẴA�N�^�[�ɋ��ʂ���X�v���C���̏��͂����ɏW��B<BR>
 * �I�u�W�F�N�g�̊֌W<BR>
 * SplineLeader �e�A�N�^�[���ɐ��������B
 *                    �A�N�^�[�ɑ΂���A�X�v���C���Ȑ���̌��݂̕⊮�_�̈ʒu�E���ԁE�������̊Ǘ����s���A
 *                    �͎�(Rikisha)�Ɏw�����o���ăA�N�^�[���ړ�������B
 *                    �P�� SplineManufacture �I�u�W�F�N�g�ɑ΂��� N �� SplineLeader �I�u�W�F�N�g���Q�Ƃ��Ă���B
 *                    �X�v���C���̍��W�_�Ԃ̋����ɉe���̖������̓R�R�ŕێ�����B
 *                    �܂�X�v���C���Ȑ��̍��W�_�̎����s�ړ��I�t�Z�b�g�A
 *                    X,Y,Z�̐�������ւ����B�iTODO:�����́A��]�����R�R�Ɂj
 *
 * SplineManufacture  �X�v���C���Ȑ��̍��W�_�Z�b�g�̊g��k�����A�܂�����ɔ���SplineRikishaLeader�̎����N���X�̏���ێ��B
 *                    �g��k���ɂ��A�e�⊮�_���̋������̏���\�ߌv�Z���ĕێ����Ă���B
 *                    �g��k������ύX����ꍇ�́A���̃I�u�W�F�N�g�̃t�B�[���h���Čv�Z���K�v�ƂȂ�B
 *                    �P�� SplineSource �I�u�W�F�N�g�ɑ΂��� N �� SplineSource�I�u�W�F�N�g���Q�Ƃ��Ă���B
 *                    (��spl�t�@�C���̏��ɑ�������B)
 *
 * SplineSource       �X�v���C���Ȑ��̍��W�_�Z�b�g�̏���ێ�����I�u�W�F�N�g�B
 *                    SplineSource �͐����Ɠ����ɁA�����̃t�@�C�����̊O���t�@�C����ǂݍ��݁A
 *                    ���W�̕⊮�_���v�Z���A�����ێ�����B
 *                    (��dat�t�@�C���̏��ɑ�������B)
 *
 * @version 1.00
 * @since 2011/08/05
 * @author Masatoshi Tsuge
 */
class SplineManufacture : public GgafCore::Object {

public:
    SplineSourceConnection* _pSplSrcCon;
    /** [r]���W���(dat�t�@�C�����ɑ���)*/
    SplineSource* _pSpl;
    /** [r]�X�v���C�����W���t�@�C����(spl�t�@�C��) */
    std::string _spl_file;
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
public:
    /**
     * �R���X�g���N�^ .
     * @param prm_coord_data_file �X�v���C�����W���t�@�C��(spl�t�@�C��)
     */
    explicit SplineManufacture(const char* prm_coord_data_file);
    /**
     * �R���X�g���N�^ .
     * @param prm_pSplSrc �X�v���C�����W���I�u�W�F�N�g
     */
    SplineManufacture(SplineSource* prm_pSpl);

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

    /**
     * SplineLeader �I�u�W�F�N�g�̐��� .
     * �ݒ肵���͎Ԃ��A���삵�܂��̂Œ��ӂ��ĉ������B<br>
     * �{���\�b�h�ō쐬���� SplineLeader �́A�Ăь��� delete����K�v������܂��B<br>
     * @param prm_pRikisha �Ώۂ̃A�N�^�[�̗͎�
     * @return
     */
    virtual SplineLeader* createRikishaLeader(GgafDx::Rikisha* prm_pRikisha);

    virtual SplineLeader* createKagoLeader(GgafDx::Kago* prm_pKago);

    virtual ~SplineManufacture();
};

}
#endif /*GGAF_LIB_SPLINEMANUFACTURE_H_*/
