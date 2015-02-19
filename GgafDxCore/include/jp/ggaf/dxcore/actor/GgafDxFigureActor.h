#ifndef GGAFDXCORE_GGAFDXFIGUREACTOR_H_
#define GGAFDXCORE_GGAFDXFIGUREACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"

namespace GgafDxCore {

/**
 * ��ʂɕ`����s���A�N�^�[�̒��ۃN���X .
 * GgafDxGeometricActor �� ���f���A�G�t�F�N�g�A�}�e���A���Ȃǂ�ێ����A<BR>
 * �`��֘A���\�b�h���`<BR>
 * @version 1.00
 * @since 2009/06/10
 * @author Masatoshi Tsuge
 */
class GgafDxFigureActor : public GgafDxGeometricActor {
private:
    /**
     * draw()�̎g�p�֎~ .
     * ���E(GgafDxUniverse)���S�Ă̕`����s���d�g�݂ɂȂ�܂����B
     * GgafDxUniverse::draw() ���Q�Ƃ���B
     * �m�[�h�c���[�p draw ���\�b�h�����ʂŎg���Ȃ��悤�ɂ��邽��private�Ŏ����B
     */
    void draw() override {}

protected:
    /** [r]���f�������ڑ� */
    GgafDxModelConnection* const _pModelCon;
    /** [r]���f������ */
    GgafDxModel* const _pModel;
    /** [r]�G�t�F�N�g�����ڑ� */
    GgafDxEffectConnection* const _pEffectCon;
    /** [r]�G�t�F�N�g���� */
    GgafDxEffect* const _pEffect;
    /** [r]�ꎞ�e�N�j�b�N�� */
    char* _temp_technique;
    /** [r]�ꎞ�e�N�j�b�N���n�b�V���l */
    hashval _hash_temp_technique;
    /** [r]�ꎞ�e�N�j�b�N�I���t���[�� */
    frame _frame_of_behaving_temp_technique_end;

public:
    /** [r/w]�`�掞�AZ�o�b�t�@���l�����ĕ`����s�����ۂ��Btrue:�l������^false:Z�o�b�t�@�𖳎����ĕ`��  */
    bool _zenable;
    /** [r/w]�`�掞�AZ�o�b�t�@�֏������݂��s�����ۂ��Btrue:Z�o�b�t�@�֐[�x���������ށ^false:Z�o�b�t�@�ւ͉����������܂Ȃ� */
    bool _zwriteenable;

    /** [r]���߂̕`�掞�Ɏg�p���ꂽ�e�N�j�b�N���̃n�b�V���R�[�h */
    static hashval _hash_technique_last_draw;

    /** [r]����`�惌�x���̎��̃A�N�^�[ */
    GgafDxFigureActor* _pNextActor_in_draw_depth_level;
    /** [r/w]���݂̃}�e���A���̃��l (0.0 <= _alpha <= 1.0) */
    float _alpha;
    /** [r]���ݕ`��Ɏg�p���Ă���V�F�[�_�[�e�N�j�b�N�� */
    char* _technique;
    /** [r]���ݕ`��Ɏg�p���Ă���̃V�F�[�_�[�e�N�j�b�N�̃n�b�V���R�[�h */
    hashval _hash_technique;
    /** [r/w]���݂̃}�e���A���ʃJ���[ */
    D3DMATERIAL9* _paMaterial;

    /** [r/w]���݂̕`��[�x */
    int _now_drawdepth;
    /** [r/w]���ʂȌŒ�`��[�x�A-1�łȂ���� _now_drawdepth ���D��ł��̐[�x���K�p����� */
    int _specal_drawdepth;
    /** [r]�ꎞ�e�N�j�b�N�K�p���̏ꍇ true */
    bool _is_temp_technique;


public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name ���f�����́i�C�Ӂj
     * @param prm_model ���f�����ʃL�[������
     * @param prm_effect �G�t�F�N�g���ʃL�[������
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N
     * @param prm_pStat �g�p����X�e�[�^�X�I�u�W�F�N�g(�g�p���Ȃ��� nullptr�ł悢)
     * @param prm_pStat �g�p����X�e�[�^�X�I�u�W�F�N�g(�g�p���Ȃ��� nullptr�ł悢)
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����nullptr�ł悢�j
     */
    GgafDxFigureActor(const char* prm_name,
                      const char* prm_model,
                      const char* prm_effect,
                      const char* prm_technique,
                      GgafCore::GgafStatus* prm_pStat,
                      GgafDxChecker* prm_pChecker);

    /**
     * �R���X�g���N�^ .
     * GgafDxModelManager::processCreateResource() �y��
     * GgafDxEffectManager::processCreateResource()
     * �̐������Q�Ƃ��ׂ��B
     * @param prm_name �A�N�^�[���́i�C�Ӂj
     * @param prm_model_id ���f����`��
     * @param prm_model_type ���f���^�C�v
     * @param prm_effect_id �G�t�F�N�g��`��
     * @param prm_effect_type �G�t�F�N�g�^�C�v
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N
     * @param prm_pStat �g�p����X�e�[�^�X�I�u�W�F�N�g(�g�p���Ȃ��� nullptr�ł悢)
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����nullptr�ł悢�j
     */
    GgafDxFigureActor(const char* prm_name,
                      const char* prm_model_id,
                      const char* prm_model_type,
                      const char* prm_effect_id,
                      const char* prm_effect_type,
                      const char* prm_technique,
                      GgafCore::GgafStatus* prm_pStat,
                      GgafDxChecker* prm_pChecker);

    virtual GgafDxFigureActor* getPrev() const override {  //���ς̖߂�l
        return (GgafDxFigureActor*)GgafActor::getPrev();
    }

    virtual GgafDxFigureActor* getNext() const  override {  //���ς̖߂�l
        return (GgafDxFigureActor*)GgafActor::getNext();
    }

    /**
     * �V�F�[�_�[�̃e�N�j�b�N��ύX���� .
     * �����\�B
     * @param prm_technique �e�N�j�b�N��
     */
    void changeEffectTechnique(const char* prm_technique);

    /**
     * �V�F�[�_�[�̃e�N�j�b�N���ꎞ�I�ɕύX���� .
     * ���Ɉꎞ�e�N�j�b�N�g�p���͖��������B�A���A
     * ���Ɉꎞ�e�N�j�b�N�g�p���ɋ����I�Ɉꎞ�e�N�j�b�N��ύX�������ꍇ���̂悤�ɂł���B
     * <code>
     * if (_is_temp_technique == false) {
     *     changeEffectTechnique("�ύX�������e�N�j�b�N��");
     * }
     * </code>
     * @param prm_technique �e�N�j�b�N��
     * @param prm_frame �ύX�e�N�j�b�N�̌p���t���[����
     */
    void changeEffectTechniqueInterim(const char* prm_technique, frame prm_frame);

    /**
     * �s�J���ƌ���B
     * @param prm_frame ���鎞��
     */
    virtual void effectFlush(frame prm_frame = MAX_FRAME);

    /**
     * ���Z�����G�t�F�N�g .
     * @param prm_frame
     */
    virtual void effectBlendOne(frame prm_frame = MAX_FRAME);

    /**
     * �W���G�t�F�N�g�ɖ߂� .
     */
    virtual void effectDefault();

    /**
     * ���ʂȕ`��[�x����������B .
     * 0�ȏ�w��ꍇ�A�`��[�x�w��ɂ��̒l���g�p�����B
     * ���̐��̎w��ꍇ�A�����ݒ�ɖ߂�i_specal_drawdepth�̃f�t�H���g��-1)
     * @param prm_drawdepth
     */
    void setSpecialDrawDepth(int prm_drawdepth);

    /**
     * ���ʂ̕`�掖�O���� .
     * �`����s���ɂ������Ă̏d�v�Ȏ��O�������s�Ȃ��܂��B
     * �EonCreateModel() �̌Ăяo��
     * �E�i�K�����_�����O�̐[�x�v�Z
     * �E�ꎞ�e�N�j�b�N�l��
     * �I�[�o�[���C�h�񐄏��B
     * �I�[�o�[���C�h����ꍇ�́A
     * GgafDxFigureActor::processPreDraw() �����\�b�h���ŌĂяo�����A
     * �����͎��O�œ����̏������������邩�A���Ȃ����l�����Ă��������B
     * TODO:private virtual �ɂ���ׂ����ۂ��H�Bfainal ���~����
     */
    virtual void processPreDraw() override;

    /**
     * ���ʂ̕`�掖�㏈�� .
     * ���f�o�b�O���[�h (MY_DEBUG �� 1)�̏ꍇ��
     * �����蔻��̈��`�悷��B
     * (�Ƃ����Ă� drawHitArea() ���R�[�����邾��)
     */
    virtual void processAfterDraw() override;

    /**
     * �����蔻��̈��`�� .
     * ���ۂ̏����͉��ʃN���X�ɔC����B
     */
    virtual void drawHitArea() {};

    /**
     * �{�A�N�^�[�̕`�掞�̃}�e���A���A���t�@�l�ݒ� .
     * 1.0 �ȏ�̏ꍇ�J�����O��ON�A<br>
     * 1.0 ��菬���ȏꍇ�A�J�����O��OFF�A<br>
     * �Ƃ����@�\�����킹���B<br>
     * @param prm_alpha �A�N�^�[�̃}�e���A���A���t�@�l
     */
    virtual void setAlpha(float prm_alpha) {
        _alpha = prm_alpha;
    }

    /**
     * �{�A�N�^�[�̕`�掞�̃}�e���A���A���t�@�l�����Z���� .
     * @param prm_alpha ���Z����}�e���A���A���t�@�l
     */
    virtual void addAlpha(float prm_alpha) {
        _alpha += prm_alpha;
    }

    /**
     * �{�A�N�^�[�̕`�掞�̃}�e���A���A���t�@�l���擾 .
     * @return �A�N�^�[�̌��݂̃A���t�@�l
     */
    virtual float getAlpha() const {
        return _alpha;
    }

    /**
     * �{�A�N�^�[�̕`�掞�̃}�e���A���J���[��ݒ�B .
     * �L�����N�^�S�̂ɐF���d�˂���ʂ𓾂�B<br>
     * �������@�́A���ʂɈˑ��B<br>
     * ���������Ė{���\�b�h�ɂ��u�}�e���A���J���[�v�̈Ӗ��́A<br>
     * �uDirectX�̃}�e���A���v�̈Ӗ��ƈ�v���Ȃ���������Ȃ��B<br>
     * @param r Red���x(0.0 �` 1.0)
     * @param g Green���x(0.0 �` 1.0)
     * @param b Blue���x(0.0 �` 1.0)
     */
    virtual void setMaterialColor(float r, float g, float b);

    virtual void setMaterialRed(float r);
    virtual void setMaterialGreen(float g);
    virtual void setMaterialBlue(float b);

    /**
     * �{�A�N�^�[�̕`�掞�̃}�e���A���J���[��ݒ�B .
     * @param prm_rgb
     */
    virtual void setMaterialColor(const GgafCore::GgafRgb* prm_rgb);

    /**
     * �}�e���A���J���[�����f���ǂݍ��ݎ��̏�ԂɃ��Z�b�g�B
     */
    virtual void resetMaterialColor();

    inline GgafDxModel* getModel() const {
        return _pModel;
    }

    virtual GgafDxEffect* getEffect() const {
        return _pEffect;
    }

    /**
     * �`�掞Z�o�b�t�@���l�����邩 .
     * @param prm_bool true:�l������(default) / false:��������
     */
    void setZEnable(bool prm_bool) {
        _zenable = prm_bool;
    }

    /**
     * �`�掞Z�o�b�t�@���������ނ� .
     * @param prm_bool true:��������(default) / false:�������܂Ȃ�
     */
    void setZWriteEnable(bool prm_bool) {
        _zwriteenable = prm_bool;
    }

    /**
     * ���f�����������ꂽ���̏��� .
     * ���f���I�u�W�F�N�g�� new ���ꂽ�ꍇ�ɂP�񂾂��Ăяo���܂��B
     * ���f���P�ʂŐݒ肵�����������I�[�o�[���C�h���ĉ������B
     */
    virtual void onCreateModel() = 0;

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
    virtual int isOutOfView() override;

    virtual ~GgafDxFigureActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDXCORE_GGAFDXFIGUREACTOR_H_*/
