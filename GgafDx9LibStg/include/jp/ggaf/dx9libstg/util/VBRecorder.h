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


    class VBRecordNote {
    public:
        VBRecordNote* _pNext;

        vbsta _state;
        frame _frame_of_keeping;
        VBRecordNote(vbsta state, frame frame_of_keeping) : _pNext(NULL),_state(state),_frame_of_keeping(frame_of_keeping) {
        }
    };


    VirtualButton* _vb;
    VBRecordNote* _pFirstVBNote;
    VBRecordNote* _p;
    frame _nframe;


    VBRecorder(VirtualButton* prm_vb);

    //void updete();

    void write();

    virtual ~VBRecorder();
};

}
#endif /*FONTSPRITESTRING_H_*/
