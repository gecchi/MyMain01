#ifndef GGAFDX9DRAWABLEACTOR_H_
#define GGAFDX9DRAWABLEACTOR_H_
namespace GgafDx9Core {

/**
 * ��ʂɕ`����s�����W���ϊ��A�N�^�[�̒��ۃN���X .
 * GgafDx9GeometricActor �� ���f���A�G�t�F�N�g�A�}�e���A���Ȃǂ�ێ����A<BR>
 * �`��֘A���\�b�h��ǉ�<BR>
 */
class GgafDx9DrawableActor : public GgafDx9GeometricActor {

private:

public:
    /** ����`�惌�x���̎��̃A�N�^�[ */
    GgafDx9DrawableActor* _pNext_TheSameDrawDepthLevel;


    /** �� (0.0 <= _fAlpha <= 1.0) */
    float _fAlpha;

    char* _technique;
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
     * �R���X�g���N�^<BR>
     * @param	prm_name ���ʖ�
     */
    GgafDx9DrawableActor(const char* prm_name,
                         const char* prm_model,
                         const char* prm_effect,
                         const char* prm_technique,
                         GgafDx9Checker* prm_pChecker);

    GgafDx9DrawableActor(const char* prm_name,
                         const char* prm_model_id,
                         const char* prm_model_type,
                         const char* prm_effect_id,
                         const char* prm_effect_type,
                         const char* prm_technique,
                         GgafDx9Checker* prm_pChecker);

    virtual GgafDx9DrawableActor* getPrev() {
        return (GgafDx9DrawableActor*)GgafActor::getPrev();
    }

    virtual GgafDx9DrawableActor* getNext() {
        return (GgafDx9DrawableActor*)GgafActor::getNext();
    }


    /**
     * _Z�̒l�ɂ��A��܂��Ƀ����_�����O������ݒ肷��B
     * �C�ӂ̗D�揇�ʂŃ����_�����O�������ꍇ�́A���̃��\�b�h���I�[�o�[���C�h��
     * GgafUniverse::_apAlphaActorList_DrawDepthLevel[n] �̍D���� n �� addSubLast(this) ���s���ĉ������B
     * �A�� 0 �� n �� MAX_DRAW_DEPTH_LEVEL
     * TODO:private virtual �ɂ���ׂ����ۂ��H�Bfainal ���~����
     */
    virtual void processPreDraw();

    virtual void processAfterDraw();


    virtual void drawHitArea() {};

    virtual void setAlpha(float prm_fAlpha) {
        _fAlpha = prm_fAlpha;
    }

    virtual void addAlpha(float prm_fAlpha) {
        _fAlpha += prm_fAlpha;
    }

    virtual float getAlpha() {
        return _fAlpha;
    }

    virtual void setMaterialColor(float r, float g, float b);

    virtual void resetMaterialColor();

    virtual ~GgafDx9DrawableActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9DRAWABLEACTOR_H_*/
