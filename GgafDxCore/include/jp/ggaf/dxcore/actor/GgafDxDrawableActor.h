#ifndef GGAFDXDRAWABLEACTOR_H_
#define GGAFDXDRAWABLEACTOR_H_
namespace GgafDxCore {

/**
 * ��ʂɕ`����s���A�N�^�[�̒��ۃN���X .
 * GgafDxGeometricActor �� ���f���A�G�t�F�N�g�A�}�e���A���Ȃǂ�ێ����A<BR>
 * �`��֘A���\�b�h���`<BR>
 * @version 1.00
 * @since 2009/06/10
 * @author Masatoshi Tsuge
 */
class GgafDxDrawableActor : public GgafDxGeometricActor {

private:
    /** [r]�ꎞ�e�N�j�b�N�� */
    char* _temp_technique;
    /** [r]�ꎞ�e�N�j�b�N���n�b�V���l */
    unsigned int _hash_temp_technique;
    /** [r]�ꎞ�e�N�j�b�N�I���t���[�� */
    frame _frame_of_behaving_temp_technique_end;
    /** [r]�ꎞ�e�N�j�b�N�K�p���̏ꍇ true */
    bool _is_temp_technique;
    /** ���f�������ڑ� */
    GgafDxModelConnection* _pModelCon;
    /** �G�t�F�N�g�����ڑ� */
    GgafDxEffectConnection* _pEffectCon;


    /**
     * draw()�̎g�p�֎~ .
     * ���E(GgafDxUniverse)���S�Ă̕`����s���d�g�݂ɂȂ�܂����B
     * GgafDxUniverse::draw() ���Q�Ƃ���B
     * �m�[�h�c���[�p draw ���\�b�h�����ʂŎg���Ȃ��悤�ɂ��邽��private�Ŏ����B
     */
    void draw() override {}

public:
    /** [r/w]�`�掞�AZ�o�b�t�@���l�����ĕ`����s�����ۂ��Btrue:�l������^false:Z�o�b�t�@�𖳎����ĕ`��  */
    bool _zenable;
    /** [r/w]�`�掞�AZ�o�b�t�@�֏������݂��s�����ۂ��Btrue:Z�o�b�t�@�֐[�x���������ށ^false:Z�o�b�t�@�ւ͉����������܂Ȃ� */
    bool _zwriteenable;

    /** ���߂̕`�掞�Ɏg�p���ꂽ�e�N�j�b�N���̃n�b�V���R�[�h */
    static unsigned int _hash_technique_last_draw;

    /** [r]����`�惌�x���̎��̃A�N�^�[ */
    GgafDxDrawableActor* _pNext_TheSameDrawDepthLevel;
    /** [r]���݂̃}�e���A���̃��l (0.0 <= _fAlpha <= 1.0) */
    float _fAlpha;
    /** [r]���ݕ`��Ɏg�p���Ă���V�F�[�_�[�e�N�j�b�N�� */
    char* _technique;
    /** [r]���ݕ`��Ɏg�p���Ă���̃V�F�[�_�[�e�N�j�b�N�̃n�b�V���R�[�h */
    unsigned int _hash_technique;
    /** [r]���݂̃}�e���A���J���[ */
    D3DMATERIAL9* _paMaterial;
    /** [r]���f������ */
    GgafDxModel* _pModel;
    /** [r]�G�t�F�N�g���� */
    GgafDxEffect* _pEffect;
    /** [r]���݂̕`��[�x */
    int _now_drawdepth;
    /** [r]���ʂȌŒ�`��[�x�A-1�łȂ���� _now_drawdepth ���D��ł��̐[�x���K�p����� */
    int _specal_drawdepth;

    GgafDxAlphaFader* _pFader;

    /**
     * �R���X�g���N�^ .
     * @param prm_name ���f�����́i�C�Ӂj
     * @param prm_model ���f�����ʃL�[������
     * @param prm_effect �G�t�F�N�g���ʃL�[������
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N
     * @param prm_pStat �g�p����X�e�[�^�X�I�u�W�F�N�g(�g�p���Ȃ��� NULL�ł悢)
     * @param prm_pStat �g�p����X�e�[�^�X�I�u�W�F�N�g(�g�p���Ȃ��� NULL�ł悢)
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����NULL�ł悢�j
     */
    GgafDxDrawableActor(const char* prm_name,
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
     * @param prm_pStat �g�p����X�e�[�^�X�I�u�W�F�N�g(�g�p���Ȃ��� NULL�ł悢)
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����NULL�ł悢�j
     */
    GgafDxDrawableActor(const char* prm_name,
                         const char* prm_model_id,
                         const char* prm_model_type,
                         const char* prm_effect_id,
                         const char* prm_effect_type,
                         const char* prm_technique,
                         GgafCore::GgafStatus* prm_pStat,
                         GgafDxChecker* prm_pChecker);

    virtual GgafDxDrawableActor* getPrev() override {
        return (GgafDxDrawableActor*)GgafActor::getPrev();
    }

    virtual GgafDxDrawableActor* getNext() override {
        return (GgafDxDrawableActor*)GgafActor::getNext();
    }

    /**
     * �V�F�[�_�[�̃e�N�j�b�N��ύX���� .
     * �����\�B
     * @param prm_technique �e�N�j�b�N��
     */
    void changeEffectTechnique(const char* prm_technique) {
        _hash_technique = GgafCore::GgafUtil::easy_hash(prm_technique);
        strcpy(_technique, prm_technique);
    }

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
    void changeEffectTechniqueInterim(const char* prm_technique, frame prm_frame) {
        if (_is_temp_technique == false) { //���łɈꎞ�e�N�j�b�N�g�p���͖���
            //���X�̃e�N�j�b�N��ޔ�
            _hash_temp_technique = _hash_technique;
            strcpy(_temp_technique, _technique);
            //�e�N�j�b�N�ύX
            _frame_of_behaving_temp_technique_end = _frame_of_behaving + prm_frame; //�ύX�����t���[��
            _hash_technique = GgafCore::GgafUtil::easy_hash(prm_technique);
            strcpy(_technique, prm_technique);
            _is_temp_technique = true;
        }
    }

    /**
     * ���ʂȕ`��[�x����������B .
     * 0�ȏ�w��ꍇ�A�`��[�x�w��ɂ��̒l���g�p�����B
     * ���̐��̎w��ꍇ�A�����ݒ�ɖ߂�i_specal_drawdepth�̃f�t�H���g��-1)
     * @param prm_drawdepth
     */
    void setSpecialDrawDepth(int prm_drawdepth) {
        if (prm_drawdepth > MAX_DRAW_DEPTH_LEVEL) {
            _specal_drawdepth = MAX_DRAW_DEPTH_LEVEL;
        } else {
            _specal_drawdepth = prm_drawdepth;
        }
    }

    /**
     * ���ʂ̕`�掖�O���� .
     * �`����s���ɂ������Ă̏d�v�Ȏ��O�������s�Ȃ��܂��B
     * �EonCreateModel() �̌Ăяo��
     * �E�i�K�����_�����O�̐[�x�v�Z
     * �E�ꎞ�e�N�j�b�N�l��
     * �I�[�o�[���C�h�񐄏��B
     * �I�[�o�[���C�h����ꍇ�́A
     * GgafDxDrawableActor::processPreDraw() �����\�b�h���ŌĂяo�����A
     * �����͎��O�œ����̏������������邩�A���Ȃ����l�����Ă��������B
     * TODO:private virtual �ɂ���ׂ����ۂ��H�Bfainal ���~����
     */
    virtual void processPreDraw() override;

    /**
     * ���ʂ̕`�掖�㏈�� .
     * ���f�o�b�O���[�h (<pre><code>#define MY_DEBUG 1</code></pre>)�̏ꍇ��
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
     * @param prm_fAlpha �A�N�^�[�̃}�e���A���A���t�@�l
     */
    virtual void setAlpha(float prm_fAlpha) {
        _fAlpha = prm_fAlpha;
    }

    /**
     * �{�A�N�^�[�̕`�掞�̃}�e���A���A���t�@�l�����Z���� .
     * @param prm_fAlpha ���Z����}�e���A���A���t�@�l
     */
    virtual void addAlpha(float prm_fAlpha) {
        _fAlpha += prm_fAlpha;
    }

    /**
     * �{�A�N�^�[�̕`�掞�̃}�e���A���A���t�@�l���擾 .
     * @return �A�N�^�[�̌��݂̃A���t�@�l
     */
    virtual float getAlpha() {
        return _fAlpha;
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

    /**
     * �}�e���A���J���[�����f���ǂݍ��ݎ��̏�ԂɃ��Z�b�g�B
     */
    virtual void resetMaterialColor();

    virtual GgafDxModel* getModel() {
        return _pModel;
    }

    virtual GgafDxEffect* getEffect() {
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

    virtual ~GgafDxDrawableActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDXDRAWABLEACTOR_H_*/
