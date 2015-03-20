#ifndef GGAFCORE_GGAFREPEATSEQ_H_
#define GGAFCORE_GGAFREPEATSEQ_H_
#include "GgafCommonHeader.h"

#include <map>
#include <string>
#ifndef _MSC_VER
    #include <atomic>
#endif

namespace GgafCore {

/**
 * �����N���X(�P��X���b�h�p�B�X���b�h�Z�[�t�ł͗L��܂���) .
 * �f�[�^�x�[�X�̃V�[�N�G���X�i�����I�u�W�F�N�g�j�̂悤�ɁA�̔Ԃ��܂��B
 * @version 1.00
 * @since 2007/12/11
 * @author Masatoshi Tsuge
 */
class GgafRepeatSeq {
private:
    class Seq {
    public:
        int _value;
        int _min;
        int _max;
    public :
        Seq() : _value(0), _min(0), _max(0)  {}
        inline void init(int min, int max) {
            _min = min;
            _max = max;
            _value = _min;
        }
        inline void setMin() {
            _value = _min;
        }
        inline void setMax() {
            _value = _max;
        }
        inline void set(int val) {
            _value = val;
        }
        inline int nextVal() {
            _value++;
            if (_value > _max) {
                _value = _min;
            }
            return _value;
        }
    };

    static std::map<std::string, GgafRepeatSeq::Seq> mapSeq;

#ifdef _MSC_VER
    //TODO:VC++2005�ȍ~(x86) �� volatile �́A�������o���A���ʂ�����i�Ǝv���j�B
    //gcc(x86)�́A�A�g�~�b�N�ۏ؂͖����� std::atomic ���g����BVC++�� atomic �����������܂ł͂Ƃ肠�����E�E�E�B
    static volatile bool _is_lock;
#else
    static volatile std::atomic<bool> _is_lock;
#endif


public:
    /**
     * �����I�u�W�F�N�g���쐬 .
     * @param ID �R���鏇���I�u�W�F�N�gID�i�C��)
     * @param min �ŏ��l
     * @param max �ő�l
     */
    static void create(std::string ID, int min, int max);
    static void create(const char* ID, int min, int max);
    /**
     * ID�̏����I�u�W�F�N�g���쐬�ς݂����ׂ� .
     * @param ID �����I�u�W�F�N�gID
     * @return true:�����ς݁^false:������
     */
    static bool isExist(std::string& ID);
    static bool isExist(const char* ID);   static void set(std::string& ID, int val);
    static void set(const char* ID, int val);
    static void setMax(std::string& ID);
    static void setMax(const char* ID);
    static void setMin(std::string& ID);
    static void setMin(const char* ID);

    /**
     * �����I�u�W�F�N�g����̔Ԃ��A�����J�E���g�����̒l�ɃZ�b�g���Ă��� .
     * @param ID �쐬���̏����I�u�W�F�N�gID
     * @return ���݂̒l
     */
    static int nextVal(std::string& ID);
    static int nextVal(const char* ID);
};

}
#endif /*GGAFCORE_GGAFREPEATSEQ_H_*/
