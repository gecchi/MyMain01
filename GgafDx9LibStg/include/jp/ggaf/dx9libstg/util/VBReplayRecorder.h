#ifndef VBREPLAYRECORDER_H_
#define VBREPLAYRECORDER_H_
namespace GgafDx9LibStg {

/**
 * リプレイデータクラス
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class VBReplayRecorder : public GgafCore::GgafObject {
public:


    class VBRecordNote {
    public:
        VBRecordNote* _pNext;

        vbsta _state;
        frame _frame_of_keeping;
        VBRecordNote() : _pNext(NULL),_state(0),_frame_of_keeping(0) {
        }
        VBRecordNote(vbsta state, frame frame_of_keeping) : _pNext(NULL),_state(state),_frame_of_keeping(frame_of_keeping) {
        }
        virtual ~VBRecordNote() {
        }
    };


    VBRecordNote* _pFirstVBNote;
    VBRecordNote* _pRecNote;
    frame _frame_of_the_same_vbsta_reading;


    VBReplayRecorder();

    //void updete();

    void first();

    vbsta read();

    void write(vbsta state);

    void outputFile(const char* prm_filename);


    bool importFile(const char* prm_filename);


    virtual ~VBReplayRecorder();
};

}
#endif /*FONTSPRITESTRING_H_*/
