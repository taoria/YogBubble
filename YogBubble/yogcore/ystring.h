#pragma once
#include <string>
#include "IYog.h"
class ystring : public std::string,public IYog
{
public:
	YID GetId() override;
	void SetId(YID id) override;
	std::string GetName() override;
	void SetName(std::string) override;
};

inline YID ystring::GetId() { return 0; }
inline void ystring::SetId(YID id){}
inline std::string ystring::GetName() { return "string"; }
inline void ystring::SetName(std::string){}
