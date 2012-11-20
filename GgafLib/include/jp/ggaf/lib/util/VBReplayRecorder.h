#ifndef VBREPLAYRECORDER_H_
#define VBREPLAYRECORDER_H_
namespace GgafLib {

/**
 * ���v���C�f�[�^�N���X .
 * ���z�{�^���X�e�[�^�X(VirtualButton �� _state)�́A
 * �������ݓǂݎ��A�t�@�C�������o����荞�݋@�\��񋟁B
 * @version 1.00
 * @since 2010/04/20
 * @author Masatoshi Tsuge
 */
class VBReplayRecorder : public GgafCore::GgafObject {
public:

    /**
     * ���v���C�f�[�^�v�f .
     */
    class VBRecordNote {
    public:
        /** [r]���̃��v���C�f�[�^�v�f */
        VBRecordNote* _pNext;
        /** [r]���z�{�^���X�e�[�^�X */
        vbsta _state;
        /** [r]�X�e�[�^�X�p���t���[���� */
        frame _frame_of_keeping;

        /**
         * �R���X�g���N�^ .
         */
        VBRecordNote() : _pNext(nullptr),_state(0),_frame_of_keeping(0) {
        }

        /**
         * �R���X�g���N�^ .
         * @param state ���z�{�^���X�e�[�^�X
         * @param frame_of_keeping �X�e�[�^�X�p���t���[����
         */
        VBRecordNote(vbsta state, frame frame_of_keeping) : _pNext(nullptr),_state(state),_frame_of_keeping(frame_of_keeping) {
        }

        virtual ~VBRecordNote() {
        }
    };

    /** [r]���v���C�f�[�^�v�f���X�g�̐擪�v�f */
    VBRecordNote* _pFirstVBNote;
    /** [r]���v���C�f�[�^�v�f�J�[�\���|�C���^ */
    VBRecordNote* _pRecNote;
    VBRecordNote* _pRecNote_RreadPrev;
    /** [r]����X�e�[�^�X�p���t���[���J�E���^ */
    frame _frame_of_the_same_vbsta_reading;

    std::ofstream _ofs_realtime;

    bool _write_realtime;
    /**
     * �R���X�g���N�^ .
     */
    VBReplayRecorder();


    /**
     * �����J�[�\����擪�Ɏ����Ă��� .
     */
    void first();

    /**
     * ���z�{�^���X�e�[�^�X�ǂݍ��݁A������Ԃ��A���̏�Ԃ֑J�� .
     * @return ���z�{�^���X�e�[�^�X
     */
    vbsta read();

    /**
     * ���A���^�C���L�q���[�h���I���ɂ���(��Ƀf�o�b�O�p) .
     * write(vbsta) ���s�̓x�ɁA���A���^�C���Ńt�@�C���ɏ����L�q���Ă����܂��B
     * @param prm_filename ���A���^�C���ɏ��������t�@�C����
     * @return
     */
    bool setRealtimeOutputFile(const char* prm_filename);
    /**
     * ���z�{�^���X�e�[�^�X���������݁A������Ԃ��A���̏�Ԃ֑J�� .
     * @param state
     */
    void write(vbsta state);

    /**
     * �t�@�C���Ƀ��v���C�f�[�^�����������B
     * @param prm_filename ���������t�@�C����
     */
    void outputFile(const char* prm_filename);

    /**
     * �t�@�C�����烊�v���C�f�[�^��ǂݍ��ށB
     * @param prm_filename �ǂݍ��ރt�@�C����
     * @return true:����/false:���s
     */
    bool importFile(const char* prm_filename);

    virtual ~VBReplayRecorder();
};

}
#endif /*FONTSPRITESTRING_H_*/
