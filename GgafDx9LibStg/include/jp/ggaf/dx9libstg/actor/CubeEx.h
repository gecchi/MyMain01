#ifndef CUBEEX_H_
#define CUBEEX_H_
namespace GgafDx9LibStg {

/**
 * �����蔻��\���p�L���[�u�N���X
 * DefaultCubeActor ���p�����A�����蔻��̈�\���@�\��ǉ������A�N�^�[�ł��B
 * @version 1.00
 * @since 2009/08/25
 * @author Masatoshi Tsuge
 */
class CubeEx : public GgafDx9Core::GgafDx9CubeEx {
    static CubeEx* _pObj;

public:
    static CubeEx* get();
    static void release();

    CubeEx(const char* prm_name);

    //void processDraw() {} //�I�[�o�[���C�h�������ɂ���B


    void drawHitarea(CollisionChecker* prm_pChecker);

    virtual ~CubeEx();

};

}
#endif /*CUBEEX_H_*/
