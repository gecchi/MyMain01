#ifndef SPLINEMANUFACTURE_H_
#define SPLINEMANUFACTURE_H_
namespace GgafDx9LibStg {

/**
 * �X�v���C���Ȑ��ړ��̂��߂̏��Z�b�g .
 * �I�u�W�F�N�g�̊֌W
 * SplineSequence     �e�A�N�^�[���ɐ��������B
 *                    �A�N�^�[�ɑ΂���A�X�v���C���Ȑ���̌��݂̕⊮�_�̈ʒu�E���ԁE�������̊Ǘ����s���A
 *                    ���qA(KurokoA)�Ɏw�����o���ăA�N�^�[���ړ�������B
 *                    �P�� SplineManufacture �I�u�W�F�N�g�ɑ΂��� N �� SplineSequence�I�u�W�F�N�g���Q�Ƃ��Ă���B
 *                    �X�v���C���̍��W�_�Ԃ̋����ɉe���̖������̓R�R�ŕێ�����B
 *                    �܂�X�v���C���Ȑ��̍��W�_�̎����s�ړ��I�t�Z�b�g�A
 *                    X,Y,Z�̐�������ւ����B�iTODO:�����́A��]�����R�R�Ɂj
 *
 * SplineManufacture  �X�v���C���Ȑ��̍��W�_�Z�b�g�̊g��k�����A�܂�����ɔ���SplineSequence�̎����N���X�̏���ێ��B
 *                    �g��k���ɂ��A�e�⊮�_���̋������̏���\�ߌv�Z���ĕێ����Ă���B
 *                    �g��k������ύX����ꍇ�́A���̃I�u�W�F�N�g�̃t�B�[���h���Čv�Z���K�v�ƂȂ�B
 *                    �P�� SplineSource �I�u�W�F�N�g�ɑ΂��� N �� SplineSource�I�u�W�F�N�g���Q�Ƃ��Ă���B
 *
 * SplineSource       Spline3D �I�u�W�F�N�g���g���܂킷���߂�Spline3D���b�p�[�N���X�B
 *                    SplineSource �͐����Ɠ����ɁA�����̃t�@�C�����̊O���t�@�C����ǂݍ��݁A
 *                    Spline3D�𐶐����A�����ێ�����B
 *
 * Spline3D           �X�v���C���Ȑ��̍��W�_�Z�b�g�̏���ێ�����I�u�W�F�N�g�B
 *
 * @version 1.00
 * @since 2011/08/05
 * @author Masatoshi Tsuge
 */
class SplineManufacture : public GgafCore::GgafObject {
private:

public:
    SplineSourceConnection* _pSplSrcCon;
    SplineSource* _pSplSrc;
    /** �X�v���C���Ȑ��̕⊮�_�����A�ێ�����N���X */
    Spline3D* _sp;
    /** X�������␳���� */
    float _rate_X;
    /** Y�������␳���� */
    float _rate_Y;
    /** Z�������␳���� */
    float _rate_Z;

    /**
     * �R���X�g���N�^ .
     * @param prm_source_file �X�v���C�����W���t�@�C��
     */
    SplineManufacture(const char* prm_source_file);

    SplineManufacture(SplineSource* prm_pSplSrc);


    /**
     * �e�⊮�_���AX�������AY�������AZ���������ꂼ��Ɋ������悶�A�␳���܂� .
     * �f�t�H���g�� adjustAxisRate(1.0, 1.0, 1.0) �ƂȂ�܂��B<BR>
     * <b>[����]</b><BR>
     * ���̃��\�b�h�����s�����ꍇ�A�_�̓_�̋������ς�邽�߁A<BR>
     * ���ʃN���X�̎����ɂ���ẮA�����ێ��e�[�u�������X�V���邽�߂ɁA<BR>
     * calculate() �����s����K�v�����邩������܂���B
     * @param prm_rate_X X�������␳����
     * @param prm_rate_Y Y�������␳����
     * @param prm_rate_Z Z�������␳����
     */
    virtual void adjustAxisRate(float prm_rate_X, float prm_rate_Y, float prm_rate_Z);

    /**
     * �X�v���C�����W�␳�ɂ��Čv�Z .
     * ���ʂŎ������Ă��������B
     */
    virtual void calculate() = 0;

    /**
     * SplineSequence �I�u�W�F�N�g�̐��� .
     * @param prm_pKurokoA �Ώۂ̃A�N�^�[
     * @return
     */
    virtual SplineSequence* createSplineSequence(GgafDx9Core::GgafDx9KurokoA* prm_pKurokoA) = 0;


    virtual ~SplineManufacture();
};

}
#endif /*SPLINEMANUFACTURE_H_*/
