#pragma once
#include "../IYog.h"
#include "IEvent.h"


template<class T>
class InfoWrapper:public IYog
{
	T data;
public:
	InfoWrapper();
	InfoWrapper(T data);
	~InfoWrapper();
	T GetData();
	UINT GetId() override;
	void SetId(YID id) override;
	std::string GetName() override;
	void SetName(std::string) override;
	InfoWrapper& operator = (T &object);
};

template <class T>
InfoWrapper<T>::InfoWrapper(){}

template <class T>
InfoWrapper<T>::InfoWrapper(T data){
	this->data = data;
}

template <class T>
InfoWrapper<T>::~InfoWrapper(){}

template <class T>
T InfoWrapper<T>::GetData() { return data; }

template <class T>
UINT InfoWrapper<T>::GetId() { return 0; }

template <class T>
void InfoWrapper<T>::SetId(YID id){}

template <class T>
std::string InfoWrapper<T>::GetName(){
	return "wrapper";
}

template <class T>
void InfoWrapper<T>::SetName(std::string){}

template <class T>
InfoWrapper<T>& InfoWrapper<T>::operator=(T& object){
	this->data = object;
	return *this;
}
template<class T>
T GetWrappedInfo(IEvent* iEvent, std::string key){
	InfoWrapper<T>* result = dynamic_cast<InfoWrapper<T>*>(iEvent->GetArg("key code"));
	return result->GetData();
}
template<class T>
void InputWrappedInfo(IEvent* iEvent,std::string key,T data){
	InfoWrapper<T>* result = new InfoWrapper<T>(data);
	iEvent->push(key, result);
}