#ifndef GGAFDX9DRAWABLEUNTRANSFORMEDACTOR_H_
#define GGAFDX9DRAWABLEUNTRANSFORMEDACTOR_H_
namespace GgafDx9Core {

/**
 * ��ʂɕ`����s�����W���ϊ��A�N�^�[�̒��ۃN���X
 * GgafDx9DrawableUntransformedActor �ɕ`��֘A�� ���f���A�G�t�F�N�g�A�}�e���A���Ȃǂ�ێ�<BR>
 */
class GgafDx9DrawableUntransformedActor : public GgafDx9UntransformedActor {

private:

public:

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
    GgafDx9DrawableUntransformedActor(const char* prm_name,
                                      const char* prm_model,
                                      const char* prm_effect,
                                      const char* prm_technique,
                                      GgafDx9Checker* prm_pChecker);

    virtual GgafDx9DrawableUntransformedActor* getPrev() {
        return (GgafDx9DrawableUntransformedActor*)GgafActor::getPrev();
    }

    virtual GgafDx9DrawableUntransformedActor* getNext() {
        return (GgafDx9DrawableUntransformedActor*)GgafActor::getNext();
    }


    /**
     * _Z�̒l�ɂ��A��܂��Ƀ����_�����O������ݒ肷��B
     * �C�ӂ̗D�揇�ʂŃ����_�����O�������ꍇ�́A���̃��\�b�h���I�[�o�[���C�h��
     * GgafUniverse::_apAlphaActorList_DrawDepthLevel[n] �̍D���� n �� addSubLast(this) ���s���ĉ������B
     * �A�� 0 �� n �� MAX_DRAW_DEPTH_LEVEL
     * TODO:private virtual �ɂ���ׂ����ۂ��H�Bfainal ���~����
     */
    virtual void processDrawPrior();

    virtual void setAlpha(float prm_fAlpha) {
        _fAlpha = prm_fAlpha;
    }

    virtual void addAlpha(float prm_fAlpha) {
        _fAlpha += prm_fAlpha;
    }

    virtual float getAlpha() {
        return _fAlpha;
    }


    virtual ~GgafDx9DrawableUntransformedActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9DRAWABLEUNTRANSFORMEDACTOR_H_*/
