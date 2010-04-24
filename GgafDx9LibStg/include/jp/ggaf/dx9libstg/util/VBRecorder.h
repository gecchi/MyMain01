#ifndef VBRECORD_H_
#define VBRECORD_H_
namespace GgafDx9LibStg {

/**
 * リプレイデータクラス
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class VBRecorder : public GgafCore::GgafObject {
public:


    class VBStateNote {
    public:
        VBStateNote* _pNext;

        vbsta _state;
        DWORD _frame_of_keeping;
        VBStateNote(vbsta state, DWORD frame_of_keeping) : _pNext(NULL),_state(state),_frame_of_keeping(frame_of_keeping) {
        }
    };


    VirtualButton* _vb;
    VBStateNote* _pFirstVBNote;
    VBStateNote* _p;
    DWORD _nframe;


    VBRecorder(VirtualButton* prm_vb);

    //void updete();

    void write();

    virtual ~VBRecorder();
};

}
#endif /*FONTSPRITESTRING_H_*/
