// �{�v���O�����́A<BR>
// �u���~�i�܂�؂��j����[�ǂ��ƃR���v http://marupeke296.com/index.html <BR>
// �T�C�g���R���e���c�� �uOgg Vorbis����ҁv http://marupeke296.com/OGG_main.html <BR>
// �̃T���v���v���O�������I���W�i���ł��B<BR>
// �ꕔ�ύX���Ďg�p���Ă��܂��B<BR>
//                                            2009/01/13 Masatoshi Tsuge<BR>

#ifndef IKD_DIX_OGGVORBISMEMORY_H
#define IKD_DIX_OGGVORBISMEMORY_H

namespace Dix {
class OggVorbisMemory : public OggVorbisResource {
public:
    OggVorbisMemory();
    OggVorbisMemory(const char* prm_filepath);
    virtual ~OggVorbisMemory();

    //! Ogg�o�b�t�@���쐬
    bool createBuffer(const char* prm_filepath);

    virtual OggVorbisResource* createClone();

    //! �N���A
    virtual void clear();

protected:
    //! �������ǂݍ���
    static size_t read(void* prm_buffer, size_t prm_size, size_t prm_max_count, void* prm_stream);

    //! �������V�[�N
    static int seek(void* prm_buffer, ogg_int64_t offset, int flag);

    //! �������N���[�Y
    static int close(void* prm_buffer);

    //! �������ʒu�ʒB
    static long tell(void* prm_buffer);

protected:
    char _filepath[256]; // �t�@�C���p�X
    char* _buffer; // Ogg�t�@�C���o�b�t�@
    int _size; // �o�b�t�@�T�C�Y
    long _pos_current; // ���݂̈ʒu
};

}

#endif
