#pragma once
class UWindow
{
public:
	// 持失切 社瑚切
	UWindow();
	~UWindow();

	// delete funcion

	UWindow(const UWindow& _Other) = delete;
	UWindow(UWindow&& _Other) noexcept = delete;
	UWindow& operator=(const UWindow& _Other) = delete;
	UWindow& operator=(UWindow&& _Other) noexcept = delete;


protected:

private:

};

