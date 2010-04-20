#ifndef SPHEREEX_H_
#define SPHEREEX_H_
namespace GgafDx9LibStg {

/**
 * �����蔻��\���p���N���X
 * DefaultSphereActor ���p�����A�����蔻��̈�\���@�\��ǉ������A�N�^�[�ł��B
 * @version 1.00
 * @since 2010/01/21
 * @author Masatoshi Tsuge
 */
class SphereEx : public GgafDx9Core::GgafDx9SphereEx {
    static SphereEx* _pObj;

public:
    static SphereEx* get();
    static void release();

    SphereEx(const char* prm_name);

    //void processDraw() {} //�I�[�o�[���C�h�������ɂ���B


    void drawHitarea(CollisionChecker* prm_pChecker);

    virtual ~SphereEx();

};

}
#endif /*SPHEREEX_H_*/
