#pragma once
class UWindow
{
public:
	// ������ �Ҹ���
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

