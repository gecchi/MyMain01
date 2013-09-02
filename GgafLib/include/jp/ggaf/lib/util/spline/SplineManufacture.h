#ifndef GGAFLIB_SPLINEMANUFACTURE_H_
#define GGAFLIB_SPLINEMANUFACTURE_H_
#include "jp/ggaf/core/GgafObject.h"

#include <string>

namespace GgafLib {

/**
 * �X�v���C���Ȑ��ړ��̂��߂̏��Z�b�g .
 * �S�ẴA�N�^�[�ɋ��ʂ���X�v���C���̏��͂����ɏW��B<BR>
 * �I�u�W�F�N�g�̊֌W<BR>
 * SplineKurokoLeader �e�A�N�^�[���ɐ��������B
 *                    �A�N�^�[�ɑ΂���A�X�v���C���Ȑ���̌��݂̕⊮�_�̈ʒu�E���ԁE�������̊Ǘ����s���A
 *                    ����A(KurokoA)�Ɏw�����o���ăA�N�^�[���ړ�������B
 *                    �P�� SplineManufacture �I�u�W�F�N�g�ɑ΂��� N �� SplineKurokoLeader�I�u�W�F�N�g���Q�Ƃ��Ă���B
 *                    �X�v���C���̍��W�_�Ԃ̋����ɉe���̖������̓R�R�ŕێ�����B
 *                    �܂�X�v���C���Ȑ��̍��W�_�̎����s�ړ��I�t�Z�b�g�A
 *                    X,Y,Z�̐�������ւ����B�iTODO:�����́A��]�����R�R�Ɂj
 *
 * SplineManufacture  �X�v���C���Ȑ��̍��W�_�Z�b�g�̊g��k�����A�܂�����ɔ���SplineKurokoLeader�̎����N���X�̏���ێ��B
 *                    �g��k���ɂ��A�e�⊮�_���̋������̏���\�ߌv�Z���ĕێ����Ă���B
 *                    �g��k������ύX����ꍇ�́A���̃I�u�W�F�N�g�̃t�B�[���h���Čv�Z���K�v�ƂȂ�B
 *                    �P�� SplineSource �I�u�W�F�N�g�ɑ΂��� N �� SplineSource�I�u�W�F�N�g���Q�Ƃ��Ă���B
 *                    (��spl�t�@�C���̏��ɑ�������B)
 *
 * SplineSource       SplineLine �I�u�W�F�N�g���g���܂킷���߂�SplineLine���b�p�[�N���X�B
 *                    SplineSource �͐����Ɠ����ɁA�����̃t�@�C�����̊O���t�@�C����ǂݍ��݁A
 *                    ���W�̕⊮�_���v�Z���A�����ێ�����B
 *                    (��dat�t�@�C���̏��ɑ�������B)
 *
 * SplineLine         �X�v���C���Ȑ��̍��W�_�Z�b�g�̏���ێ�����I�u�W�F�N�g�B
 *
 * @version 1.00
 * @since 2011/08/05
 * @author Masatoshi Tsuge
 */
class SplineManufacture : public GgafCore::GgafObject {

public:
    SplineSourceConnection* _pSplSrcCon;
    /** [r]���W���(dat�t�@�C�����ɑ���)*/
    SplineSource* _pSplSrc;
    /** [r]�X�v���C�����W���t�@�C����(spl�t�@�C��) */
    std::string _source_file;
    /** �X�v���C���Ȑ��̕⊮�_�����A�ێ�����N���X */
    SplineLine* _sp;
    /** X�������␳���� */
    double _rate_X;
    /** Y�������␳���� */
    double _rate_Y;
    /** Z�������␳���� */
    double _rate_Z;
    /** [r]���̕⊮�_�܂ł̋����̃e�[�u�� */
    coord* _paDistance_to;
    /** [r]�����̍��v _paDistance_to[0] �` _paDistance_to[n]  */
    coord _total_distance;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_source_file �X�v���C�����W���t�@�C��(spl�t�@�C��)
     */
    SplineManufacture(const char* prm_source_file);

    /**
     * �R���X�g���N�^ .
     * @param prm_pSplSrc �X�v���C�����W���I�u�W�F�N�g
     */
    SplineManufacture(SplineSource* prm_pSplSrc);


    /**
     * �e�⊮�_���AX�������AY�������AZ���������ꂼ��Ɋ������悶�A�␳���܂� .
     * �f�t�H���g�� adjustAxisRate(1.0, 1.0, 1.0) �ƂȂ�܂��B<BR>
     * <b>[����]</b><BR>
     * ���̃��\�b�h�����s�����ꍇ�A�_�̓_�̋������ς�邽�߁A<BR>
     * ���ʃN���X�̎����ɂ���ẮA�����ێ��e�[�u�������X�V���邽�߂ɁA<BR>
     * ��calculate() �����s���Ȃ��Ɣ��f���܂���B
     * @param prm_rate_X X�������␳����
     * @param prm_rate_Y Y�������␳����
     * @param prm_rate_Z Z�������␳����
     */
    virtual void adjustAxisRate(double prm_rate_X, double prm_rate_Y, double prm_rate_Z);

    /**
     * �������i�v�Z�j���� .
     * �v���p�e�B��ύX�����ꍇ�A�����e�[�u�������X�V���邽�߂�
     * ��x���s����K�v������܂��B
     * ���ʂŎ������ĉ������B
     */
    virtual void calculate();

    /**
     * SplineKurokoLeader �I�u�W�F�N�g�̐��� .
     * �ݒ肵������A���A���삵�܂��̂Œ��ӂ��ĉ������B<br>
     * �{���\�b�h�ō쐬���� SplineKurokoLeader �́A�Ăь��� delete����K�v������܂��B<br>
     * @param prm_pKurokoA �Ώۂ̃A�N�^�[�̍���A
     * @return
     */
    virtual SplineKurokoLeader* createKurokoLeader(GgafDxCore::GgafDxKurokoA* const prm_pKurokoA) = 0;


    virtual ~SplineManufacture();
};

}
#endif /*GGAFLIB_SPLINEMANUFACTURE_H_*/
