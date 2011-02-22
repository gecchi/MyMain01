#ifndef GGAFDX9PUPPETEER_H_
#define GGAFDX9PUPPETEER_H_
namespace GgafDx9Core {

/**
 * ����l�`���� .
 * @version 1.00
 * @since 2011/02/22
 * @author Masatoshi Tsuge
 */
class GgafDx9Puppeteer : public GgafCore::GgafObject {
private:

public:
    /** ������� */
    GgafDx9DynaD3DXMeshActor* _pPuppet;

    /**
     * �R���X�g���N�^ .
     * @param prm_pActor �������
     * @return
     */
    GgafDx9Puppeteer(GgafDx9DynaD3DXMeshActor* prm_pPuppet);


    virtual ~GgafDx9Puppeteer();



    /**
     * �A�j���[�V������1�t���[�����i�s������ .
     * �{���\�b�h���AprocessBehavior() ���Ŗ��t���[���Ăяo���K�v������܂��B<BR>
     * �Ăяo�����ƂŁAsetFlipMethod()�Őݒ肵�����@�ɉ�����<BR>
     * �A�N�e�B�u�ȃp�^�[���ԍ�(_pattno_uvflip_now)�������Ő؂�ւ��܂��B<BR>
     */
    virtual void behave();


};

}
#endif /*GGAFDX9PUPPETEER_H_*/
