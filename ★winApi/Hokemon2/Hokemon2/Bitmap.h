#pragma once
class Bitmap
{
public:
	//std::map<int, HBITMAP> map_Images;

	HBITMAP hBackImage;
	BITMAP bitBack;
	HBITMAP hBackImage2;
	BITMAP bitBack2;

	Bitmap();
	~Bitmap();

	void CreateBitmap();
	void DrawBitmap(HWND hWnd, HDC hdc);
	void DeleteBitmap();
};