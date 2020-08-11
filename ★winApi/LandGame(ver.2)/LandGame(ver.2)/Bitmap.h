#pragma once
class Bitmap
{
public:
	HBITMAP hBackImage;
	BITMAP bitBack;

	Bitmap();
	~Bitmap();

	void CreateBitmap();
	void DrawBitmap(HWND hWnd, HDC hdc);
	void DeleteBitmap();
};