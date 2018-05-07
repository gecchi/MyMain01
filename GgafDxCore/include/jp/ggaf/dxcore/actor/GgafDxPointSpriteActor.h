#ifndef GGAFDXCORE_GGAFDXPOINTSPRITEACTOR_H_
#define GGAFDXCORE_GGAFDXPOINTSPRITEACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxFigureActor.h"

namespace GgafDxCore {

/**
 * �|�C���g�X�v���C�g�A�N�^�[.
 * GgafDxFigureActor ���p�����A�|�C���g�X�v���C�g�\���@�\��������A�N�^�[<BR>
 * ���̗�悤�ȃ|�C���g�X�v���C�g�\���@�\�������B
 * �i��px��������ʏ�px�Ƃقڈ�v�j
 * <pre>
 * ���၄
 *
 * �y�e�N�X�`���z
 * Pattern.png
 *
 * <---256px--->
 *
 * +--+--+--+--+    ^
 * | 0| 1| 3| 4|    |
 * +--+--+--+--+    |
 * | 5| 6| 7| 8|    |
 * +--+--+--+--+    256px (�����`�ł��邱�ƁI
 * | 9|10|11|12|    |      �s�N�Z�����͎��R�B��ł�256*256px)
 * +--+--+--+--+    |
 * |13|14|15|16|    |
 * +--+--+--+--+    v
 *
 *
 * �y�ǂݍ���X�t�@�C���z
 * �|�C���g�X�v���C�g��p�̒�`X�t�@�C��(�g���qpsprx)��ǂݍ��ށB
 *
 * -----------------------------------------
 * xof 0303txt 0032
 * PointSpriteDef Test {
 *   32.0;                                  //�� �|�C���g�ɕ\������X�v���C�g�̂P�ӂ�px�������B�e�N�X�`���̂P�p�^�[���̂P�ӂ̃e�N�Z���ł͂Ȃ��B
 *                                          //   (���32px������ʕ\���ɂ���Ƃ����Ӗ�)
 *   "Pattern.png";                         //�� �e�N�X�`��
 *   4;                                     //�� �e�N�X�`���c���̕������B1�́u���������v�A2�́u�c���Q�������� 4�p�^�[���A�j���[�V�����v
 *                                          //   ��ł́A��L�̂悤�ȃe�N�X�`���Ȃ̂ŁA4���w�肵�ďc���S������4*4��16�p�^�[���ƂȂ�B
 *                                          //   ���������āA���̂Ƃ��e�N�X�`���̂P�p�^�[���̂P�ӂ�px��256/4��64px�ƌ��܂�B
 *   3;                                     //�� ���_���i���X�v���C�g���j��͂R�̒��_���w��B�ȉ��Ƀf�[�^�ő���
 *                                          //   ���_���W�A�I�u�W�F�N�g�J���[�A�����p�^�[���ԍ��A�����{���̃f�[�^����
 *                                          //   �S�Ĉ�v����K�v������B
 *   -20.000000;-21.000000;-22.000000;,     //�� �|�C���g�X�v���C�g���_XYZ���W���BDirectX�̍��W�Ŏw��B
 *   3.000000;2.000000;1.000000;,           //   �f�[�^���͒��_��(���̏ꍇ��3) �Ɉ�v�����邱��
 *   11.000000;12.000000;13.000000;;
 *
 *   1.000000;0.100000;0.100000;1.000000;,  //�� �e�|�C���g�X�v���C�g��RGBA�����J���[�i�e�N�X�`���ƍ��������j
 *   0.100000;1.000000;0.100000;1.000000;,  //   �f�[�^���͒��_��(���̏ꍇ��3) �Ɉ�v�����邱��
 *   0.100000;0.100000;1.000000;1.000000;;
 *
 *   0,                                     //�� �e�|�C���g�X�v���C�g�̏����A�j���[�V�����p�^�[���ԍ��I�t�Z�b�g
 *   5,                                     //   �f�[�^���͒��_��(���̏ꍇ��3) �Ɉ�v�����邱��
 *   15;
 *
 *   1.0,                                   //�� �e�|�C���g�X�v���C�g�̏����X�P�[���{��
 *   2.0,                                   //   �f�[�^���͒��_��(���̏ꍇ��3) �Ɉ�v�����邱��
 *   1.0;
 * }
 * -----------------------------------
 *
 *
 * �y��LX�t�@�C���̏����\����ʃC���[�W�z
 * ������W�n�A��ʒ��S�� (0,0,0) �B
 * �オX���̐��A�E��Y���̐��A����Z���̐�
 *
 * +-----------------------------------------------------------------+
 * |                                                                 |
 * |                                                                 |
 * |                                                                 |
 * |                                     �B                          |
 * |                                      ++                         |
 * |                                      ++                         |
 * |                           �A +----+                             |
 * |                              | 5  |                             |
 * |                              |    |                             |
 * |                              +----+                             |
 * |                                                                 |
 * |                   �@                                            |
 * |                      +----+                                     |
 * |                      | 0  |                                     |
 * |                      |    |                                     |
 * |                      +----+                                     |
 * |                                                                 |
 * +-----------------------------------------------------------------+
 *
 * �@ DirectX�̍��W(-20.000000,-21.000000,-22.000000)
 *    �\���A�j���[�V�����p�^�[���ԍ��O��
 *    �Ԃ��ۂ��\��
 *    -220px�����̋�����O�ɂȂ�̂ŁA�����g�傳��ĕ\�������B
 *    ��O�A���ɂ��g��k���̓��[���h�ϊ���ɃJ�����Ƃ̋����Ȃǂ��玩���v�Z�B
 *    ���̃��b�V���I�u�W�F�N�g�Ƃ̗��͉�ʒ��S�t�߂ň�v����B
 *    �A���A�P���Ɋg��k�����Ă��邽�߉�ʂ̒[�ɍs���قǍ����o��B
 *
 * �A DirectX�̍��W(3.000000,2.000000,1.000000);
 *    �\���A�j���[�V�����p�^�[���ԍ��T��
 *    ��ʏ� (30px,20px)������ŗ΂��ۂ��\���B
 *    �i�u������v�Ƃ����\���̓��[���h�ϊ�����̂ŃY���邽�߁j
 *    �͂��ɉ��̂��߁A�ق�̏����̏k�����s����B
 *    Z���W�� 1.000000 (10px����)�� 0 �ɋ߂����߁A�قڃe�N�X�`����px�����̕��Ō�����B
 *    10px���̕��ق�̏����k���B
 *    �����X�P�[���{����2.0�Ƃ��Ă��邽�� (256/4)*2.0 = 128 ��
 *    128*128px��10px���̕��ق�̏����k���ŉ�ʏ�Ō�����B
 *    ���s�������\����Z=0�̏ꍇ�A�e�N�X�`���̃s�N�Z���̑傫���ɂقڈ�v����悤�ɃJ�����������Ă���B
 *    ���̋����������J����Z�����ƌĂԁB
 *    px�����Ƃ́A�����J����Z�������ꂽ�ʒu�ɃJ������u���ĕ\�������ꍇ��
 *    ��ʂɌ�����I�u�W�F�N�g�̕��̂��Ƃł���B
 *    DirectX���W�́u1�v�͖�10�s�N�Z���ɑ�������悤�ɂȂ��Ă���B
 *
 * �B DirectX�̍��W(11.000000, 12.000000, 13.000000)
 *    �\���A�j���[�V�����p�^�[���ԍ��P�T��
 *    ���ۂ��\��
 *    130px�����̋������̂��߁A���k�����s����B
 *    �A�j���[�V�����p�^�[���ԍ��P�T�Ԃł��邪�A
 *    �A�N�^�[���̃��W�b�N�ŁA�A�j���[�V�����p�^�[�����P�i�߂��
 *    �B�̃A�j���[�V�����p�^�[���ԍ��͂O�Ԃɕς��i���[�v����j
 * </pre>
 * @version 1.00
 * @since 2010/02/26
 * @author Masatoshi Tsuge
 */
class GgafDxPointSpriteActor : public GgafDxFigureActor {

public:
    /** [r]���f������ */
    GgafDxPointSpriteModel* const _pPointSpriteModel;
    /** [r]�G�t�F�N�g���� */
    GgafDxPointSpriteEffect* const _pPointSpriteEffect;
    /** [r]UV�t���b�p�[(�p���p���A�j��) */
    GgafDxUvFlipper* const _pUvFlipper;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name ���f�����́i�f�o�b�O���O�ŕ\���A�Ȃ�ł��ǂ��j
     * @param prm_model_id ���f����`���B������ ".psprx" ������X�t�@�C�����ɂȂ邱�ƁB
     * @param prm_effect_id �G�t�F�N�g��`���B������ ".fx" �����ăG�t�F�N�g�t�@�C�����ɂȂ邱�ƁB
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N��
     * @param prm_pStat �g�p����X�e�[�^�X�I�u�W�F�N�g(�g�p���Ȃ��� nullptr�ł悢)
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����nullptr�ł悢�j
     */
    GgafDxPointSpriteActor(const char* prm_name,
                           const char* prm_model_id,
                           const char* prm_effect_id,
                           const char* prm_technique,
                           GgafCore::GgafStatus* prm_pStat,
                           GgafDxChecker* prm_pChecker );
    /**
     * ���ʌp���p�R���X�g���N�^
     * @param prm_name �A�N�^�[���́i�C�Ӂj
     * @param prm_model_id ���f����`��
     * @param prm_model_type ���f���^�C�v
     * @param prm_effect_id �G�t�F�N�g��`��
     * @param prm_effect_type �G�t�F�N�g�^�C�v
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N
     * @param prm_pStat �g�p����X�e�[�^�X�I�u�W�F�N�g(�g�p���Ȃ��� nullptr�ł悢)
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����nullptr�ł悢�j
     * @return
     */
    GgafDxPointSpriteActor(const char* prm_name,
                           const char* prm_model_id,
                           const char prm_model_type,
                           const char* prm_effect_id,
                           const char prm_effect_type,
                           const char* prm_technique,
                           GgafCore::GgafStatus* prm_pStat,
                           GgafDxChecker* prm_pChecker);

    virtual void processDraw() override;

    inline GgafDxUvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }

    virtual ~GgafDxPointSpriteActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDXCORE_GGAFDXPOINTSPRITEACTOR_H_*/
