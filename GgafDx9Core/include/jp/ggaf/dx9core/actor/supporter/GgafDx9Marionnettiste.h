#ifndef GGAFDX9MARIONNETTISTE_H_
#define GGAFDX9MARIONNETTISTE_H_
namespace GgafDx9Core {

/**
 * �e�N�X�`��UV�t���b�p�[.
 * �e�N�X�`�����p���p���A�j�����@���؂�ւ��鎖���ȒP�ɍs�����߂�
 * �쐬�����N���X�B
 * @version 1.00
 * @since 2010/02/16
 * @author Masatoshi Tsuge
 */
class GgafDx9Marionnettiste : public GgafCore::GgafObject {
private:

public:
    GgafDx9GeometricActor* _pActor;

    GgafDx9Marionnettiste(GgafDx9GeometricActor* prm_pActor);


    virtual ~GgafDx9Marionnettiste();



    /**
     * �A�j���[�V������1�t���[�����i�s������ .
     * �{���\�b�h���AprocessBehavior() ���Ŗ��t���[���Ăяo���K�v������܂��B<BR>
     * �Ăяo�����ƂŁAsetFlipMethod()�Őݒ肵�����@�ɉ�����<BR>
     * �A�N�e�B�u�ȃp�^�[���ԍ�(_pattno_uvflip_now)�������Ő؂�ւ��܂��B<BR>
     */
    virtual void behave();


};

}
#endif /*GGAFDX9SPRITEMESHACTOR_H_*/
