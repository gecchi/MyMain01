#ifndef GGAFEXCEPTION_H_
#define GGAFEXCEPTION_H_
namespace GgafCore {


class GgafException : public GgafObject {

public:
	string _message;
	GgafException(string prm_message);
	virtual string getMsg();
	virtual ~GgafException();
};


}
#endif /*GGAFEXCEPTION_H_*/
