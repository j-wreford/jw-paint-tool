#include "StaticImage.h"

paint_tool::StaticImage::StaticImage(
	const std::string	&id,
	const SIZE			&size,
	const std::wstring	&file_name,
	const int			&transparent
) : Component(id, size),
	file_name(file_name),
	transparent(transparent) {
	//
}

paint_tool::StaticImage::~StaticImage() {
	//
}

void paint_tool::StaticImage::drawComponent(EasyGraphics *ctx) const {

	POINT pos = getAbsolutePosition();
	SIZE size = getSize();

	ctx->drawBitmap(StaticImage::getFullName(file_name).c_str(), pos.x, pos.y, size.cx, size.cy, transparent);
}

bool paint_tool::StaticImage::imageExists(const std::wstring &file_name) {

	HANDLE himage = ::LoadImage(NULL, StaticImage::getFullName(file_name).c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	bool exists = !(himage == NULL);

	::DeleteObject(himage);

	return exists;
}

SIZE paint_tool::StaticImage::getImageSize(const std::wstring &file_name) {

	SIZE size = { -1, -1 };

	HANDLE himage = ::LoadImage(NULL, StaticImage::getFullName(file_name).c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	if (himage != NULL) {

		BITMAP bmpinfo;
		::GetObject((HBITMAP)himage, sizeof(BITMAP), &bmpinfo);

		size.cx = bmpinfo.bmWidth;
		size.cy = bmpinfo.bmHeight;
	}

	::DeleteObject(himage);

	return size;
}

std::wstring paint_tool::StaticImage::getFullName(const std::wstring &file_name) {
	return L"resources\\" + file_name + L".bmp";
}