#ifndef GGAFDX9DRAWABLEACTOR_H_
#define GGAFDX9DRAWABLEACTOR_H_
namespace GgafDx9Core {

/**
 * ��ʂɕ`����s���A�N�^�[�̒��ۃN���X .
 * GgafDx9GeometricActor �� ���f���A�G�t�F�N�g�A�}�e���A���Ȃǂ�ێ����A<BR>
 * �`��֘A���\�b�h��ǉ�<BR>
 * @version 1.00
 * @since 2009/06/10
 * @author Masatoshi Tsuge
 */
class GgafDx9DrawableActor : public GgafDx9GeometricActor {

private:

public:
    /** ����`�惌�x���̎��̃A�N�^�[ */
    GgafDx9DrawableActor* _pNext_TheSameDrawDepthLevel;


    /** �� (0.0 <= _fAlpha <= 1.0) */
    float _fAlpha;

    char* _technique;
    char* _technique_temp;
    DWORD _frame_temp_technique;
    unsigned int _hash_technique;
    unsigned int _hash_technique_temp;
    bool _is_temp_technique;

    static unsigned int _hash_technique_last_draw;

    /** �}�e���A���z�� */
    D3DMATERIAL9* _paD3DMaterial9;
    /** ���f�������ڑ� */
    GgafDx9ModelConnection* _pGgafDx9ModelCon;
    /** ���f������ */
    GgafDx9Model* _pGgafDx9Model;
    /** �G�t�F�N�g�����ڑ� */
    GgafDx9EffectConnection* _pGgafDx9EffectCon;
    /** �G�t�F�N�g���� */
    GgafDx9Effect* _pGgafDx9Effect;


    /**
     * �R���X�g���N�^ .
     * @param prm_name ���f�����́i�C�Ӂj
     * @param prm_model ���f�����ʃL�[������
     * @param prm_effect �G�t�F�N�g���ʃL�[������
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����NULL�ł悢�j
     */
    GgafDx9DrawableActor(const char* prm_name,
                         const char* prm_model,
                         const char* prm_effect,
                         const char* prm_technique,
                         GgafDx9Checker* prm_pChecker);

    /**
     * �R���X�g���N�^ .
     * GgafDx9ModelManager::processCreateResource() �y��
     * GgafDx9EffectManager::processCreateResource()
     * �̐������Q�Ƃ��ׂ��B
     * @param prm_name �A�N�^�[���́i�C�Ӂj
     * @param prm_model_id ���f����`��
     * @param prm_model_type ���f���^�C�v
     * @param prm_effect_id �G�t�F�N�g��`��
     * @param prm_effect_type �G�t�F�N�g�^�C�v
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����NULL�ł悢�j
     */
    GgafDx9DrawableActor(const char* prm_name,
                         const char* prm_model_id,
                         const char* prm_model_type,
                         const char* prm_effect_id,
                         const char* prm_effect_type,
                         const char* prm_technique,
                         GgafDx9Checker* prm_pChecker);

    virtual GgafDx9DrawableActor* getPrev() override {
        return (GgafDx9DrawableActor*)GgafActor::getPrev();
    }

    virtual GgafDx9DrawableActor* getNext() override {
        return (GgafDx9DrawableActor*)GgafActor::getNext();
    }

    /**
     * �e�N�j�b�N��ύX���� .
     * �����\�B
     * @param prm_technique �e�N�j�b�N��
     */
    void setTechnique(char* prm_technique) {
        _hash_technique = GgafCore::GgafUtil::easy_hash(prm_technique);
        strcpy(_technique, prm_technique);
    }

    void setTechniqueTemporarily(char* prm_technique, DWORD prm_frame) {
        if (_is_temp_technique == false) { //���łɈꎞ�e�N�j�b�N�g�p���͖���
            //���X�̃e�N�j�b�N��ޔ�
            _hash_technique_temp = _hash_technique;
            strcpy(_technique_temp, _technique);
            //�e�N�j�b�N�ύX
            _frame_temp_technique = _frame_of_active + prm_frame; //�ύX�����t���[��
            _hash_technique = GgafCore::GgafUtil::easy_hash(prm_technique);
            strcpy(_technique, prm_technique);
            _is_temp_technique = true;
        }
    }

    /**
     * ���ʂ̕`�掖�O���� .
     * �i�K�����_�����O���������邽�߂ɁA���g�̐[�x�ɉ�����
     * GgafDx9Universe::_apAlphaActorList_DrawDepthLevel[] �܂���  GgafDx9Universe::_pActors_DrawMaxDrawDepth ��
     * ���g��o�^����B
     * TODO:private virtual �ɂ���ׂ����ۂ��H�Bfainal ���~����
     */
    virtual void processPreDraw() override;

    /**
     * ���ʂ̕`�掖�㏈�� .
     * ���f�o�b�O���[�h (<code>#define MY_DEBUG 1</code>)�̏ꍇ��
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
     * �A�N�^�[�̃A���t�@�ݒ� .
     * @param prm_fAlpha
     */
    virtual void setAlpha(float prm_fAlpha) {
        _fAlpha = prm_fAlpha;
    }

    /**
     * �A�N�^�[�̃A���t�@���Z .
     * @param prm_fAlpha
     */
    virtual void addAlpha(float prm_fAlpha) {
        _fAlpha += prm_fAlpha;
    }

    /**
     * �A�N�^�[�̌��݂̃A���t�@�l .
     * @return
     */
    virtual float getAlpha() {
        return _fAlpha;
    }

    /**
     * �}�e���A���J���[��ݒ�B
     * �L�����N�^�S�̂ɐF���d�˂�B
     * �{���\�b�h�ɂ��}�e���A���J���[�Ƃ́A������uDirectX�̃}�e���A���v�̈Ӗ��Ƃ͔͈͂��قȂ�B
     * @param r
     * @param g
     * @param b
     */
    virtual void setMaterialColor(float r, float g, float b);

    /**
     * �}�e���A���J���[��������ԂɃ��Z�b�g�B
     */
    virtual void resetMaterialColor();

    /** SE�����ڑ� */
    GgafDx9SeConnection** _papSeCon;
    /** SE���� */
    GgafDx9Se** _papSe;

    /** SE�����ڑ� */
    GgafDx9SeConnection* _pSeCon;
    /** SE���� */
    GgafDx9Se* _pSe;
    /** SE�����ڑ� */
    GgafDx9SeConnection* _pSeCon2;
    /** SE���� */
    GgafDx9Se* _pSe2;

    void useSe(int prm_id, char* prm_se_name, int prm_cannel = 1) ;

    void playSe(int prm_id);

    void useSe1(char* prm_se_name, int prm_cannel = 0);

    void playSe1();

    void useSe2(char* prm_se_name, int prm_cannel = 0);

    void playSe2();


    virtual ~GgafDx9DrawableActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9DRAWABLEACTOR_H_*/
