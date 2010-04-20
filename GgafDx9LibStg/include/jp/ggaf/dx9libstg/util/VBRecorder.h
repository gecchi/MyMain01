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
        DWORD _frame;
        VBStateNote(vbsta state, DWORD frame) : _pNext(NULL),_state(state),_frame(frame) {
        }
    };

    VBRecorder();

    void updete();

    void add(vbsta _state, DWORD _frame);

    virtual ~VBRecorder();
};

}
#endif /*FONTSPRITESTRING_H_*/
