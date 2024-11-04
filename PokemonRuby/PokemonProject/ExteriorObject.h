#pragma once
class AExteriorObject
{
public:
	// 持失切 社瑚切
	AExteriorObject();
	~AExteriorObject();

	// delete funcion

	AExteriorObject(const AExteriorObject& _Other) = delete;
	AExteriorObject(AExteriorObject&& _Other) noexcept = delete;
	AExteriorObject& operator=(const AExteriorObject& _Other) = delete;
	AExteriorObject& operator=(AExteriorObject&& _Other) noexcept = delete;


protected:

private:

};

