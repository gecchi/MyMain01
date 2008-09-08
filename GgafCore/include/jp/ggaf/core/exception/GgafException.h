#ifndef GGAFEXCEPTION_H_
#define GGAFEXCEPTION_H_

class GgafException : public GgafObject {
	string _message;
public:
	GgafException(string prm_message);
	string getMsg();
	virtual ~GgafException();
};

#endif /*GGAFEXCEPTION_H_*/
