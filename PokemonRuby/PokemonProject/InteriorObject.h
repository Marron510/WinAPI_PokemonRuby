#pragma once
class AInteriorObject
{
public:
	// 持失切 社瑚切
	AInteriorObject();
	~AInteriorObject();

	// delete funcion

	AInteriorObject(const AInteriorObject& _Other) = delete;
	AInteriorObject(AInteriorObject&& _Other) noexcept = delete;
	AInteriorObject& operator=(const AInteriorObject& _Other) = delete;
	AInteriorObject& operator=(AInteriorObject&& _Other) noexcept = delete;


protected:

private:

};

