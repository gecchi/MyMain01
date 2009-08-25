#ifndef CUBEEX_H_
#define CUBEEX_H_
namespace GgafDx9LibStg {

/**
 * �����蔻��\���p�L���[�u�N���X
 * DefaultCubeActor ���p�����A�����蔻��̈�\���@�\��ǉ������A�N�^�[�ł��B
 */
class CubeEx : public GgafDx9Core::GgafDx9CubeEx {
    static CubeEx* _pObj;

public:
    static CubeEx* get();
    static void release();

    CubeEx(const char* prm_name);

    //void processDraw() {} //�I�[�o�[���C�h�������ɂ���B


    void drawHitarea(StgChecker* prm_pChecker);

    virtual ~CubeEx();

};

}
#endif /*CUBEEX_H_*/
