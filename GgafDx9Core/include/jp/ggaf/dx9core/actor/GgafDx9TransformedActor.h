#ifndef GGAFDX9TRANSFORMEDACTOR_H_
#define GGAFDX9TRANSFORMEDACTOR_H_
namespace GgafDx9Core {

/**
 * �ϊ��ςݍ��W�̃A�N�^�[.
 * �ϊ��ςݍ��W�ix���W�Ay���W�A�[�x�j���������A�N�^�[�ł�<BR>
 */
class GgafDx9TransformedActor : public GgafDx9BaseActor {

private:

    /**
     * ��OverRide �ł���<BR>
     */
    virtual bool isOffscreen() {
        return false;
    }

public:

    /** �}�e���A���z�� */
    D3DMATERIAL9* _paD3DMaterial9;
    /** �� (0.0 <= _fAlpha <= 1.0) */
    float _fAlpha;

    /** �ϊ��ς݉��X���W */
    float _x;
    /** �ϊ��ς݉��X���W */
    float _y;
    /** �[�x (0.0 <= _z < 1.0) */
    float _z;

    GgafDx9TransformedActor(const char* prm_name);

    virtual void setAlpha(float prm_fAlpha) {
        _fAlpha = prm_fAlpha;
    }

    virtual float getAlpha() {
        return _fAlpha;
    }

    virtual void processDrawPrior();


    virtual GgafDx9TransformedActor* getPrev() {
        return (GgafDx9TransformedActor*)GgafActor::getPrev();
    }

    virtual GgafDx9TransformedActor* getNext() {
        return (GgafDx9TransformedActor*)GgafActor::getNext();
    }

    virtual ~GgafDx9TransformedActor(); //�f�X�g���N�^

};

}
#endif /*GGAFDX9TRANSFORMEDACTOR_H_*/
