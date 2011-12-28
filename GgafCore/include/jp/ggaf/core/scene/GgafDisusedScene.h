#ifndef GGAFDISUSEDSCENE_H_
#define GGAFDISUSEDSCENE_H_
namespace GgafCore {

/**
 * �s�v�ɂȂ����V�[�� .
 * GgafGarbageBox�i�S�~���j�ɏ��������삳��܂��B<BR>
 * ���̃V�[���ɏ��������V�[���́A�x���ꑁ���� delete ����鋰�|�̃V�[���ł��B<BR>
 * �u�x���ꑁ���� delete �����V�[���B�v�c���[�́A�g�b�v�m�[�h�Ɉʒu���܂��B<BR>
 * ���g�͍폜����邱�Ƃ͂���܂���B<BR>
 * @version 1.00
 * @since 2008/12/17
 * @author Masatoshi Tsuge
 */
class GgafDisusedScene : public GgafScene {
public:
    GgafDisusedScene() :
        GgafScene("DisusedScene") {
        _obj_class |= Obj_GgafDisusedScene;
        _class_name = "GgafDisusedScene";
    }
    void initialize() override {
    }
    void processBehavior() override {
    }
    void processJudgement() override {
    }
    void processPreDraw() override {
    }
    void processDraw() override {
    }
    void processAfterDraw() override {
    }
    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }
    void processFinal() override {
    }
    virtual ~GgafDisusedScene() {
    }
};

}
#endif /*GGAFDISUSEDSCENE_H_*/
