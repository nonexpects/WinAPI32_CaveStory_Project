#include "stdafx.h"
#include "image.h"

// 생성자, 소멸자
image::image() : _imageInfo(NULL), _fileName(NULL), _blendImage(NULL), _scaleImage(NULL), _rotateImage(NULL)
{
}
image::~image()
{
}

// 빈 비트맵 초기화
HRESULT image::init(int width, int height)
{
	// 재초기화 방지용 (이미지 정보의 값이 들어 있다면 릴리즈해서 깨끗하게 초기화 해줄 것)
	if (_imageInfo != NULL) this->release();

	// DC 가져오기
	HDC hdc = GetDC(_hWnd);

	// 이미지 정보 구조체 새로 생성 후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	// 파일 이름
	_fileName = NULL;

	// 투명키 컬러 셋팅
	_isTrans = false;
	_transColor = RGB(0, 0, 0);

	// 리소스 얻는 데에 실패했을 경우 바로 종료
	if (_imageInfo->hBit == NULL)
	{
		this->release();
		return E_FAIL;
	}

	// DC 해제하기
	ReleaseDC(_hWnd, hdc);

	// 초기화 종료
	return S_OK;
}

// 이미지 파일로 초기화
HRESULT image::init(const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	// 재초기화 방지용 (이미지 정보의 값이 들어 있다면 릴리즈해서 깨끗하게 초기화 해줄 것)
	if (_imageInfo != NULL) this->release();

	// DC 가져오기
	HDC hdc = GetDC(_hWnd);

	// 이미지 정보 구조체 새로 생성 후 초기화
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	// 파일 이름
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	// 투명키 컬러 세팅
	_isTrans = isTrans;
	_transColor = transColor;

	// 리소스 얻는 데에 실패했을 경우 바로 종료
	if (_imageInfo->hBit == NULL)
	{
		this->release();
		return E_FAIL;
	}

	// DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}
HRESULT image::init(const char* fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	// 재초기화 방지용 (이미지 정보의 값이 들어 있다면 릴리즈해서 깨끗하게 초기화 해줄 것)
	if (_imageInfo != NULL) this->release();

	// DC 가져오기
	HDC hdc = GetDC(_hWnd);

	// 이미지 정보 구조체 새로 생성 후 초기화
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;

	// 파일 이름
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	// 투명키 컬러 세팅
	_isTrans = isTrans;
	_transColor = transColor;

	// 리소스 얻는 데에 실패했을 경우 바로 종료
	if (_imageInfo->hBit == NULL)
	{
		this->release();
		return E_FAIL;
	}

	// DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}
HRESULT image::init(const char* fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	// 재초기화 방지용 (이미지 정보의 값이 들어 있다면 릴리즈해서 깨끗하게 초기화 해줄 것)
	if (_imageInfo != NULL) this->release();

	// DC 가져오기
	HDC hdc = GetDC(_hWnd);

	// 이미지 정보 구조체 새로 생성 후 초기화
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	// 파일 이름
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	// 투명키 컬러 세팅
	_isTrans = isTrans;
	_transColor = transColor;

	// 리소스 얻는 데에 실패했을 경우 바로 종료
	if (_imageInfo->hBit == NULL)
	{
		this->release();
		return E_FAIL;
	}

	// DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}
HRESULT image::init(const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	// 재초기화 방지용 (이미지 정보의 값이 들어 있다면 릴리즈해서 깨끗하게 초기화 해줄 것)
	if (_imageInfo != NULL) this->release();

	// DC 가져오기
	HDC hdc = GetDC(_hWnd);

	// 이미지 정보 구조체 새로 생성 후 초기화
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	// 파일 이름
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	// 투명키 컬러 세팅
	_isTrans = isTrans;
	_transColor = transColor;

	// 리소스 얻는 데에 실패했을 경우 바로 종료
	if (_imageInfo->hBit == NULL)
	{
		this->release();
		return E_FAIL;
	}

	// DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

// 알파 블렌딩 초기화
HRESULT image::initForAlphaBlend()
{
	// DC 가져오기
	HDC hdc = GetDC(_hWnd);

	// 알파 블렌딩 옵션 초기화
	// BlendOp => 현재는 AC_SRC_OVER만 사용 가능
	// BlendFlags => 사용하지 않는 기능이므로 0 대입
	// AlphaFormat => 24bit 사용시 0, 32bit 사용시 AC_SRC_ALPHA 사용
	// SourceConstantAlpha => 비트맵 투명도 세팅
	_blendFunc.BlendOp = AC_SRC_OVER;
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	//_blendFunc.SourceConstantAlpha = 128; // 0 ~ 255, 255일때 원본색상

	// 이미지 정보 구조체 새로 생성후 초기화
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	// DC 해제하기
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

// 스케일 렌더 초기화
HRESULT image::initForScaleBlt()
{
	// DC 가져오기
	HDC hdc = GetDC(_hWnd);

	// 스케일 이미지 초기화
	_scaleImage = new IMAGE_INFO;
	_scaleImage->loadType = LOAD_EMPTY;
	_scaleImage->hMemDC = CreateCompatibleDC(hdc);
	_scaleImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_scaleImage->hOBit = (HBITMAP)SelectObject(_scaleImage->hMemDC, _scaleImage->hBit);
	_scaleImage->width = WINSIZEX;
	_scaleImage->height = WINSIZEY;

	// DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

// 로테이트 렌더 초기화
HRESULT image::initForRotateImage(bool isFrameImage)
{
	// DC 가져오기
	HDC hdc = GetDC(_hWnd);

	// 로테이트 이미지 초기화
	// 프레임 이미지일 경우
	if (isFrameImage)
	{
		int size;
		(_imageInfo->frameWidth > _imageInfo->frameHeight ? size = _imageInfo->frameWidth : size = _imageInfo->frameHeight);
		_rotateImage = new IMAGE_INFO;
		_rotateImage->loadType = LOAD_EMPTY;
		_rotateImage->hMemDC = CreateCompatibleDC(hdc);
		_rotateImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, size, size);
		_rotateImage->hOBit = (HBITMAP)SelectObject(_rotateImage->hMemDC, _rotateImage->hBit);
		_rotateImage->width = size;
		_rotateImage->height = size;
	}
	// 일반 이미지일 경우
	else
	{
		int size;
		(_imageInfo->width > _imageInfo->height ? size = _imageInfo->width : size = _imageInfo->height);
		_rotateImage = new IMAGE_INFO;
		_rotateImage->loadType = LOAD_EMPTY;
		_rotateImage->hMemDC = CreateCompatibleDC(hdc);
		_rotateImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, size, size);
		_rotateImage->hOBit = (HBITMAP)SelectObject(_rotateImage->hMemDC, _rotateImage->hBit);
		_rotateImage->width = size;
		_rotateImage->height = size;
	}

	// DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

// 이미지 해제
void image::release()
{
	// 이미지 정보가 남아 있다면 해제 시킬 것
	if (_imageInfo)
	{
		// 이미지 삭제
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		// 포인터 삭제
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE_ARRAY(_fileName);

		// 투명 컬러키 초기화
		_isTrans = false;
		_transColor = RGB(0, 0, 0);
	}

	//알파블렌드 이미지 정보가 있다면
	if (_blendImage)
	{
		//이미지 삭제
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		//포인터 삭제
		SAFE_DELETE(_blendImage);
	}

	//스케일 이미지 정보가 있다면
	if (_scaleImage)
	{
		//이미지 삭제
		SelectObject(_scaleImage->hMemDC, _scaleImage->hOBit);
		DeleteObject(_scaleImage->hBit);
		DeleteDC(_scaleImage->hMemDC);

		//포인터 삭제
		SAFE_DELETE(_scaleImage);
	}

	//로테이션 이미지 정보가 있다면
	if (_rotateImage)
	{
		//이미지 삭제
		SelectObject(_rotateImage->hMemDC, _rotateImage->hOBit);
		DeleteObject(_rotateImage->hBit);
		DeleteDC(_rotateImage->hMemDC);

		//포인터 삭제
		SAFE_DELETE(_rotateImage);
	}
}

// 렌더 (내가 원하는 좌표에 출력, 일반적으로 RECT의 LT좌표에 이미지를 붙임)
void image::render(HDC hdc, int destX, int destY)
{
	if (_isTrans)	// 배경색 없애고 출력
	{
		// GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,					// 복사할 장소의 DC
			destX,					// 복사할 좌표 시작X
			destY,					// 복사할 좌표 시작Y
			_imageInfo->width,		// 복사할 이미지 가로크기
			_imageInfo->height,		// 복사할 이미지 세로크기
			_imageInfo->hMemDC,		// 복사될 대상 DC
			0, 0,					// 복사될 대상의 시작지점
			_imageInfo->width,		// 복사 영역 가로크기
			_imageInfo->height,		// 복사 영역 세로크기
			_transColor);			// 복사할 때 제외할 색상 (일반적으로 마젠타색을 지정)
	}
	else	// 원본 이미지 그대로 출력
	{
		// BitBlt : DC간의 영역끼리 고속복사 해주는 함수
		// 메모리DC -> 화면DC로 복사
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

// 렌더 (내가 원하는 좌표에 원하는 크기만큼 잘라서 출력)
void image::render(HDC hdc, int destX, int destY, int sourceX, int sourceY, int sourceWidth, int sourceHeight)
{
	if (_isTrans)	// 배경색 없애고 출력
	{
		// GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,					// 복사할 장소의 DC
			destX,					// 복사할 좌표 시작X
			destY,					// 복사할 좌표 시작Y
			sourceWidth,			// 복사할 이미지 가로크기
			sourceHeight,			// 복사할 이미지 세로크기
			_imageInfo->hMemDC,		// 복사될 대상 DC
			sourceX, sourceY,		// 복사될 대상의 시작지점
			sourceWidth,			// 복사 영역 가로크기
			sourceHeight,			// 복사 영역 세로크기
			_transColor);			// 복사할 때 제외할 색상 (일반적으로 마젠타색을 지정)
	}
	else	// 원본 이미지 그대로 출력
	{
		// BitBlt : DC간의 영역끼리 고속복사 해주는 함수
		// 메모리DC -> 화면DC로 복사
		BitBlt(hdc, destX, destY, sourceWidth, sourceHeight, _imageInfo->hMemDC, sourceX, sourceY, SRCCOPY);
	}
}

// 알파 렌더
void image::alphaRender(HDC hdc, BYTE alpha)
{
	// 알파 블렌딩을 처음 사용하는가?
	// 알파 블렌딩을 사용할 수 있도록 초기화
	if (!_blendImage) this->initForAlphaBlend();

	// 알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)	// 배경색 없애고 출력
	{
		// 1. 현재 화면 DC의 내용을 블렌딩 이미지에 복사
		// 2. 이미지 메모리 DC의 배경색을 없앤 후 블렌딩 이미지에 복사
		// 3. 블렌딩 이미지를 화면 DC에 복사 (알파 블렌딩)

		// 1)
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, hdc, 0, 0, SRCCOPY);

		// 2)
		GdiTransparentBlt(
			_blendImage->hMemDC,	// 복사할 장소의 DC
			0,						// 복사할 좌표 시작X
			0,						// 복사할 좌표 시작Y
			_imageInfo->width,		// 복사할 이미지 가로 크기
			_imageInfo->height,		// 복사할 이미지 세로 크기
			_imageInfo->hMemDC,		// 복사될 대상 DC
			0, 0,					// 복사될 대상의 시작지점
			_imageInfo->width,		// 복사 영역 가로 크기
			_imageInfo->height,		// 복사 영역 세로 크기
			_transColor);			// 복사할때 제외할 색상 (일반적으로 마젠타)

		// 3)
		GdiAlphaBlend(hdc, 0, 0, _imageInfo->width, _imageInfo->height, _blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else	// 원본 이미지 그대로 출력
	{
		GdiAlphaBlend(hdc, 0, 0, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}
void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	// 알파 블렌딩을 처음 사용하는가?
	// 알파 블렌딩을 사용할 수 있도록 초기화
	if (!_blendImage) this->initForAlphaBlend();

	// 알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)	// 배경색 없애고 출력
	{
		// 1. 현재 화면 DC의 내용을 블렌딩 이미지에 복사
		// 2. 이미지 메모리 DC의 배경색을 없앤 후 블렌딩 이미지에 복사
		// 3. 블렌딩 이미지를 화면 DC에 복사 (알파 블렌딩)

		// 1)
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, hdc, destX, destY, SRCCOPY);

		// 2)
		GdiTransparentBlt(
			_blendImage->hMemDC,	// 복사할 장소의 DC
			0,						// 복사할 좌표 시작X
			0,						// 복사할 좌표 시작Y
			_imageInfo->width,		// 복사할 이미지 가로 크기
			_imageInfo->height,		// 복사할 이미지 세로 크기
			_imageInfo->hMemDC,		// 복사될 대상 DC
			0, 0,					// 복사될 대상의 시작지점
			_imageInfo->width,		// 복사 영역 가로 크기
			_imageInfo->height,		// 복사 영역 세로 크기
			_transColor);			// 복사할때 제외할 색상 (일반적으로 마젠타)

		// 3)
		GdiAlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else	// 원본 이미지 그대로 출력
	{
		GdiAlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}
void image::alphaRender(HDC hdc, int destX, int destY, int sourceX, int sourceY, int sourceWidth, int sourceHeight, BYTE alpha)
{
	// 알파 블렌딩을 처음 사용하는가?
	// 알파 블렌딩을 사용할 수 있도록 초기화
	if (!_blendImage) this->initForAlphaBlend();

	// 알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)	// 배경색 없애고 출력
	{
		// 1. 현재 화면 DC의 내용을 블렌딩 이미지에 복사
		// 2. 이미지 메모리 DC의 배경색을 없앤 후 블렌딩 이미지에 복사
		// 3. 블렌딩 이미지를 화면 DC에 복사 (알파 블렌딩)

		// 1)
		BitBlt(_blendImage->hMemDC, sourceX, sourceY, sourceWidth, sourceHeight, hdc, destX, destY, SRCCOPY);

		// 2)
		GdiTransparentBlt(
			_blendImage->hMemDC,	// 복사할 장소의 DC
			0,						// 복사할 좌표 시작X
			0,						// 복사할 좌표 시작Y
			_imageInfo->width,		// 복사할 이미지 가로 크기
			_imageInfo->height,		// 복사할 이미지 세로 크기
			_imageInfo->hMemDC,		// 복사될 대상 DC
			0, 0,					// 복사될 대상의 시작지점
			_imageInfo->width,		// 복사 영역 가로 크기
			_imageInfo->height,		// 복사 영역 세로 크기
			_transColor);			// 복사할때 제외할 색상 (일반적으로 마젠타)

		// 3)
		GdiAlphaBlend(hdc, destX, destY, sourceWidth, sourceHeight, _blendImage->hMemDC, sourceX, sourceY, sourceWidth, sourceHeight, _blendFunc);
	}
	else	// 원본 이미지 그대로 출력
	{
		GdiAlphaBlend(hdc, destX, destY, sourceWidth, sourceHeight, _imageInfo->hMemDC, sourceX, sourceY, sourceWidth, sourceHeight, _blendFunc);
	}
}

// 프레임 렌더
void image::frameRender(HDC hdc, int destX, int destY)
{
	if (_isTrans)	// 배경색 없애고 출력
	{
		// GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,						// 복사할 장소의 DC
			destX,						// 복사할 좌표 시작X
			destY,						// 복사할 좌표 시작Y
			_imageInfo->frameWidth,		// 복사할 이미지 가로 크기
			_imageInfo->frameHeight,	// 복사할 이미지 세로 크기
			_imageInfo->hMemDC,			// 복사될 대상 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,			// 복사될 대상의 시작 지점 X좌표
			_imageInfo->currentFrameY * _imageInfo->frameHeight,		// 복사될 대상의 시작 지점 Y좌표
			_imageInfo->frameWidth,		// 복사 영역 가로 크기
			_imageInfo->frameHeight,	// 복사 영역 세로 크기
			_transColor);				// 복사할때 제외할 색상(일반적으로 마젠타)
	}
	else	//원본 이미지 그대로 출력
	{
		// BitBlt : DC간의 영역끼리 고속복사 해주는 함수
		// 메모리DC -> 화면DC로 복사
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}
void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	// 이미지 예외처리
	// int hp;
	// if(hp < 0) hp = 0;
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	if (_isTrans)	// 배경색 없애고 출력
	{
		// GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,						// 복사할 장소의 DC
			destX,						// 복사할 좌표 시작X
			destY,						// 복사할 좌표 시작Y
			_imageInfo->frameWidth,		// 복사할 이미지 가로 크기
			_imageInfo->frameHeight,	// 복사할 이미지 세로 크기
			_imageInfo->hMemDC,			// 복사될 대상 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,			// 복사될 대상의 시작 지점 X좌표
			_imageInfo->currentFrameY * _imageInfo->frameHeight,		// 복사될 대상의 시작 지점 Y좌표
			_imageInfo->frameWidth,		// 복사 영역 가로 크기
			_imageInfo->frameHeight,	// 복사 영역 세로 크기
			_transColor);				// 복사할때 제외할 색상(일반적으로 마젠타)
	}
	else	//원본 이미지 그대로 출력
	{
		// BitBlt : DC간의 영역끼리 고속복사 해주는 함수
		// 메모리DC -> 화면DC로 복사
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}
void image::frameRender(HDC hdc, int destX, int destY, int sourceX, int sourceY, int sourceWidth, int sourceHeight, int frameX, int frameY)
{
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = _imageInfo->width / frameX;
	_imageInfo->frameHeight = _imageInfo->height / frameY;

	if (_isTrans)	// 배경색 없애고 출력
	{
		// GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,						// 복사할 장소의 DC
			destX,						// 복사할 좌표 시작X
			destY,						// 복사할 좌표 시작Y
			sourceWidth,				// 복사할 이미지 가로 크기
			sourceHeight,				// 복사할 이미지 세로 크기
			_imageInfo->hMemDC,			// 복사될 대상 DC
			sourceX + (_imageInfo->currentFrameX * sourceWidth),			// 복사될 대상의 시작 지점 X좌표
			sourceY + (_imageInfo->currentFrameY * sourceHeight),			// 복사될 대상의 시작 지점 Y좌표
			sourceWidth,				// 복사 영역 가로 크기
			sourceHeight,				// 복사 영역 세로 크기
			_transColor);				// 복사할때 제외할 색상(일반적으로 마젠타)
	}
	else	//원본 이미지 그대로 출력
	{
		// BitBlt : DC간의 영역끼리 고속복사 해주는 함수
		// 메모리DC -> 화면DC로 복사
		BitBlt(hdc, destX, destY, sourceWidth, sourceHeight, _imageInfo->hMemDC,
			sourceX + (_imageInfo->currentFrameX * sourceWidth),
			sourceY + (_imageInfo->currentFrameY * sourceHeight), SRCCOPY);
	}
}
void image::frameRender(HDC hdc, int destX, int destY, int sourceX, int sourceY, int sourceWidth, int sourceHeight, int frameX, int frameY, int currentFrameX, int currentFrameY)
{
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = _imageInfo->width / frameX;
	_imageInfo->frameHeight = _imageInfo->height / frameY;

	// 이미지 예외처리
	// int hp;
	// if(hp < 0) hp = 0;
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	if (_isTrans)	// 배경색 없애고 출력
	{
		// GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,						// 복사할 장소의 DC
			destX,						// 복사할 좌표 시작X
			destY,						// 복사할 좌표 시작Y
			sourceWidth,				// 복사할 이미지 가로 크기
			sourceHeight,				// 복사할 이미지 세로 크기
			_imageInfo->hMemDC,			// 복사될 대상 DC
			sourceX + (_imageInfo->currentFrameX * sourceWidth),			// 복사될 대상의 시작 지점 X좌표
			sourceY + (_imageInfo->currentFrameY * sourceHeight),			// 복사될 대상의 시작 지점 Y좌표
			sourceWidth,				// 복사 영역 가로 크기
			sourceHeight,				// 복사 영역 세로 크기
			_transColor);				// 복사할때 제외할 색상(일반적으로 마젠타)
	}
	else	//원본 이미지 그대로 출력
	{
		// BitBlt : DC간의 영역끼리 고속복사 해주는 함수
		// 메모리DC -> 화면DC로 복사
		BitBlt(hdc, destX, destY, sourceWidth, sourceHeight, _imageInfo->hMemDC,
			sourceX + (_imageInfo->currentFrameX * sourceWidth),
			sourceY + (_imageInfo->currentFrameY * sourceHeight), SRCCOPY);
	}
}
void image::frameAlphaRender(HDC hdc, int destX, int destY, int sourceX, int sourceY, int sourceWidth, int sourceHeight, int frameX, int frameY, BYTE alpha)
{
	// 알파 블렌딩을 처음 사용하는가?
	// 알파 블렌딩을 사용할 수 있도록 초기화
	if (!_blendImage) this->initForAlphaBlend();

	// 알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = _imageInfo->width / frameX;
	_imageInfo->frameHeight = _imageInfo->height / frameY;

	/*
	if (_isTrans)	// 배경색 없애고 출력
	{
		GdiTransparentBlt(
			hdc,						// 복사할 장소의 DC
			destX,						// 복사할 좌표 시작X
			destY,						// 복사할 좌표 시작Y
			sourceWidth,				// 복사할 이미지 가로 크기
			sourceHeight,				// 복사할 이미지 세로 크기
			_imageInfo->hMemDC,			// 복사될 대상 DC
			sourceX + (_imageInfo->currentFrameX * sourceWidth),			// 복사될 대상의 시작 지점 X좌표
			sourceY + (_imageInfo->currentFrameY * sourceHeight),			// 복사될 대상의 시작 지점 Y좌표
			sourceWidth,				// 복사 영역 가로 크기
			sourceHeight,				// 복사 영역 세로 크기
			_transColor);				// 복사할때 제외할 색상(일반적으로 마젠타)
	}
	else	//원본 이미지 그대로 출력
	{
		BitBlt(hdc, destX, destY, sourceWidth, sourceHeight, _imageInfo->hMemDC,
			sourceX + (_imageInfo->currentFrameX * sourceWidth),
			sourceY + (_imageInfo->currentFrameY * sourceHeight), SRCCOPY);
	}
	*/

	if (_isTrans)	// 배경색 없애고 출력
	{
		// 1)
		BitBlt(_blendImage->hMemDC, sourceX, sourceY, sourceWidth, sourceHeight, hdc, destX, destY, SRCCOPY);

		// 2)
		GdiTransparentBlt(
			_blendImage->hMemDC,	// 복사할 장소의 DC
			0,						// 복사할 좌표 시작X
			0,						// 복사할 좌표 시작Y
			_imageInfo->width,		// 복사할 이미지 가로 크기
			_imageInfo->height,		// 복사할 이미지 세로 크기
			_imageInfo->hMemDC,		// 복사될 대상 DC
			0, 0,					// 복사될 대상의 시작지점
			_imageInfo->width,		// 복사 영역 가로 크기
			_imageInfo->height,		// 복사 영역 세로 크기
			_transColor);			// 복사할때 제외할 색상 (일반적으로 마젠타)

		// 3)
		GdiAlphaBlend(hdc, destX, destY, sourceWidth, sourceHeight, _blendImage->hMemDC,
			sourceX + (_imageInfo->currentFrameX * sourceWidth), sourceY + (_imageInfo->currentFrameY * sourceHeight), sourceWidth, sourceHeight, _blendFunc);
	}
	else	// 원본 이미지 그대로 출력
	{
		GdiAlphaBlend(hdc, destX, destY, sourceWidth, sourceHeight, _imageInfo->hMemDC,
			sourceX + (_imageInfo->currentFrameX * sourceWidth), sourceY + (_imageInfo->currentFrameY * sourceHeight), sourceWidth, sourceHeight, _blendFunc);
	}
}

void image::frameAlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	// 알파 블렌딩을 처음 사용하는가?
	// 알파 블렌딩을 사용할 수 있도록 초기화
	if (!_blendImage) this->initForAlphaBlend();

	// 알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	if (_isTrans)	// 배경색 없애고 출력
	{
		// 1)
		BitBlt(_blendImage->hMemDC, _imageInfo->currentFrameX * _imageInfo->frameWidth, _imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight, hdc, destX, destY, SRCCOPY);
		//BitBlt(_blendImage->hMemDC, sourceX, sourceY, sourceWidth, sourceHeight, hdc, destX, destY, SRCCOPY);

		// 2)
		GdiTransparentBlt(
			_blendImage->hMemDC,						// 복사할 장소의 DC
			0,						// 복사할 좌표 시작X
			0,						// 복사할 좌표 시작Y
			_imageInfo->width,		// 복사할 이미지 가로 크기
			_imageInfo->height,		// 복사할 이미지 세로 크기
			_imageInfo->hMemDC,		// 복사될 대상 DC
			0, 0,					// 복사될 대상의 시작지점
			_imageInfo->width,		// 복사 영역 가로 크기
			_imageInfo->height,		// 복사 영역 세로 크기
			_transColor);				// 복사할때 제외할 색상(일반적으로 마젠타)

		// 3)
		GdiAlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight, _blendImage->hMemDC,
			(_imageInfo->currentFrameX * _imageInfo->frameWidth), (_imageInfo->currentFrameY * _imageInfo->frameHeight), _imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
	else	// 원본 이미지 그대로 출력
	{
		GdiAlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight, _imageInfo->hMemDC,
			(_imageInfo->currentFrameX * _imageInfo->frameWidth), (_imageInfo->currentFrameY * _imageInfo->frameHeight), _imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
}

void image::frameAlphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	// 알파 블렌딩을 처음 사용하는가?
	// 알파 블렌딩을 사용할 수 있도록 초기화
	if (!_blendImage) this->initForAlphaBlend();

	// 알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)	// 배경색 없애고 출력
	{
		// 1. 현재 화면 DC의 내용을 블렌딩 이미지에 복사
		// 2. 이미지 메모리 DC의 배경색을 없앤 후 블렌딩 이미지에 복사
		// 3. 블렌딩 이미지를 화면 DC에 복사 (알파 블렌딩)

		// 1)
		BitBlt(_blendImage->hMemDC, _imageInfo->currentFrameX * _imageInfo->frameWidth, _imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight, hdc, destX, destY, SRCCOPY);

		// 2)
		GdiTransparentBlt(
			_blendImage->hMemDC,	// 복사할 장소의 DC
			0,						// 복사할 좌표 시작X
			0,						// 복사할 좌표 시작Y
			_imageInfo->width,		// 복사할 이미지 가로 크기
			_imageInfo->height,		// 복사할 이미지 세로 크기
			_imageInfo->hMemDC,		// 복사될 대상 DC
			0, 0,					// 복사될 대상의 시작지점
			_imageInfo->width,		// 복사 영역 가로 크기
			_imageInfo->height,		// 복사 영역 세로 크기
			_transColor);			// 복사할때 제외할 색상 (일반적으로 마젠타)

		// 3)
		GdiAlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight, _blendImage->hMemDC,
			(_imageInfo->currentFrameX * _imageInfo->frameWidth), (_imageInfo->currentFrameY * _imageInfo->frameHeight), _imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
	else	// 원본 이미지 그대로 출력
	{
		GdiAlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight, _blendImage->hMemDC,
			(_imageInfo->currentFrameX * _imageInfo->frameWidth), (_imageInfo->currentFrameY * _imageInfo->frameHeight), _imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
}

// 루프 렌더
void image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	// 오프셋(offset)은 일반적으로 동일 오브젝트 안에서 오브젝트 처음부터 주어진 요소나 특정 지점까지의 변위차
	// offset은 어떤 특정한 값에서 약간 차이가 나는 값 또는 그 차이 자체를 의미 (차이에 따른 보정값)

	// offset 값이 음수인 경우 보정
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	// 그려지는 영역 세팅
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	// 그려지는 DC 영역 (화면크기)
	RECT rcDest;

	// 그려야 할 전체 영역
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	// 세로 루프 영역
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		// 소스 영역의 높이 계산
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		// 소스 영역이 그리는 화면을 넘어갔을 경우 (화면밖으로 나갔을 때)
		if (y + sourHeight > drawAreaH)
		{
			// 넘어간 그림의 값만큼 BOTTOM값 증가
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		// 그려지는 영역
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		// 가로 루프 영역
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			// 소스 영역의 높이 계산
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			// 소스 영역이 그리는 화면을 넘어갔을 경우 (화면밖으로 나갔을 때)
			if (x + sourWidth > drawAreaW)
			{
				// 넘어간 그림의 값만큼 RIGHT값 증가
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			// 그려지는 영역
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			// 출력 (일반 렌더 - 이미지 잘라 붙이기)
			render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, sourWidth, sourHeight);
		}
	}
}
void image::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	// offset 값이 음수인 경우 보정하기
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	// 그려지는 영역 세팅
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	// 그려지는 DC 영역 (화면크기)
	RECT rcDest;

	// 그려야 할 전체 영역
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	// 세로 루프 영역
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		// 소스 영역의 높이 계산
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		// 소스 영역이 그리는 화면을 넘어갔을 경우 (화면밖으로 나갔을 때)
		if (y + sourHeight > drawAreaH)
		{
			// 넘어간 그림의 값만큼 BOTTOM값 증가
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		// 그려지는 영역
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		// 가로 루프 영역
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			// 소스 영역의 높이 계산
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			// 소스 영역이 그리는 화면을 넘어갔을 경우 (화면밖으로 나갔을 때)
			if (x + sourWidth > drawAreaW)
			{
				// 넘어간 그림의 값만큼 RIGHT값 증가
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			// 그려지는 영역
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			// 출력 (알파 렌더 - 이미지 잘라 붙이기)
			alphaRender(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, sourWidth, sourHeight, alpha);
		}
	}
}

// 스케일 렌더
void image::scaleRender(HDC hdc, int destX, int destY, float scale)
{
	// 스케일 렌더를 처음 사용하는가?
	// 스케일 렌더를 사용할 수 있도록 초기화
	if (_scaleImage == FALSE)
	{
		this->initForScaleBlt();
	}

	_scaleImage->width = _imageInfo->width * scale;
	_scaleImage->height = _imageInfo->height * scale;

	if (_isTrans)		// 배경색 없애고 출력
	{
		// 원본 이미지를 Scale값 만큼 확대/축소 시켜서 그리기
		SetStretchBltMode(getMemDC(), COLORONCOLOR);
		StretchBlt(_scaleImage->hMemDC, 0, 0, _scaleImage->width, _scaleImage->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, SRCCOPY);

		// GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,					// 복사할 장소의 DC
			destX,					// 복사될 좌표 시작점 X
			destY,					// 복사될 좌표 시작점 Y
			_scaleImage->width,		// 복사될 이미지 가로크기
			_scaleImage->height,	// 복사될 이미지 세로크기
			_scaleImage->hMemDC,	// 복사될 대상 DC
			0, 0,					// 복사 시작지점
			_scaleImage->width,		// 복사 영역 가로크기
			_scaleImage->height,	// 복사 영역 세로크기
			_transColor);			// 복사할 때 제외할 색상 (마젠타)

	}
	else		// 원본 이미지 그대로 출력
	{
		// 원본 이미지의 크기를 확대/축소 시켜서 렌더
		StretchBlt(hdc, destX, destY, _scaleImage->width, _scaleImage->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, SRCCOPY);
	}
}
void image::scaleFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float scale)
{
	// 스케일 렌더를 처음 사용하는가?
	// 스케일 렌더를 사용할 수 있도록 초기화
	if (_scaleImage == FALSE)
	{
		this->initForScaleBlt();
	}

	_scaleImage->width = _imageInfo->width * scale;
	_scaleImage->height = _imageInfo->height * scale;
	_scaleImage->frameWidth = _scaleImage->width / (_imageInfo->maxFrameX + 1);
	_scaleImage->frameHeight = _scaleImage->height / (_imageInfo->maxFrameY + 1);

	if (_isTrans)		// 배경색 없애고 출력
	{
		// 원본 이미지를 Scale값 만큼 확대/축소 시켜서 그리기
		SetStretchBltMode(getMemDC(), COLORONCOLOR);
		StretchBlt(_scaleImage->hMemDC, 0, 0, _scaleImage->frameWidth, _scaleImage->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight, SRCCOPY);

		// GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,							// 복사할 장소의 DC
			destX,							// 복사될 좌표 시작점 X
			destY,							// 복사될 좌표 시작점 Y
			_scaleImage->frameWidth,		// 복사될 이미지 가로크기
			_scaleImage->frameHeight,		// 복사될 이미지 세로크기
			_scaleImage->hMemDC,			// 복사될 대상 DC
			0, 0,							// 복사 시작지점
			_scaleImage->frameWidth,		// 복사 영역 가로크기
			_scaleImage->frameHeight,		// 복사 영역 세로크기
			_transColor);					// 복사할 때 제외할 색상 (마젠타)
	}
	else		// 원본 이미지 그대로 출력
	{
		// 원본 이미지의 크기를 확대/축소 시켜서 렌더
		StretchBlt(hdc, destX, destY, _scaleImage->frameWidth, _scaleImage->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight, SRCCOPY);
	}
}

// 로테이트 렌더
void image::rotateRender(HDC hdc, float destX, float destY, float angle)
{
	// 로테이트 렌더를 처음 사용하는가?
	// 로테이트 렌더를 사용할 수 있도록 초기화
	if (_rotateImage == FALSE)
	{
		this->initForRotateImage(FALSE);
	}

	POINT rPoint[3];
	int dist = sqrt((_imageInfo->width / 2) * (_imageInfo->width / 2) + (_imageInfo->height / 2) * (_imageInfo->height / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));
	baseAngle[1] = atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));

	for (int i = 0; i < 3; ++i)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle) * dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle) * dist);
	}

	if (_isTrans)
	{
		BitBlt(_rotateImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc, 0, 0, BLACKNESS);

		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);

		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			0, 0, _imageInfo->width, _imageInfo->height, NULL, 0, 0);

		GdiTransparentBlt(hdc,
			destX - _rotateImage->width / 2,
			destY - _rotateImage->height / 2,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);
	}
	else
	{
		PlgBlt(hdc, rPoint, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, NULL, 0, 0);
	}
}

void image::rotateFrameRender(HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY, float angle)
{
	// 로테이트 렌더를 처음 사용하는가?
	// 로테이트 렌더를 사용할 수 있도록 초기화
	if (_rotateImage == FALSE)
	{
		this->initForRotateImage(TRUE);
	}

	POINT rPoint[3];
	int dist = sqrt((_imageInfo->frameWidth / 2) * (_imageInfo->frameWidth / 2) + (_imageInfo->frameHeight / 2) * (_imageInfo->frameHeight / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[1] = atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));

	for (int i = 0; i < 3; ++i)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle) * dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle) * dist);
	}

	if (_isTrans)
	{
		BitBlt(_rotateImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc, 0, 0, BLACKNESS);

		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);

		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			//_imageInfo->currentFrameX * _imageInfo->frameWidth,
			//_imageInfo->currentFrameY * _imageInfo->frameHeight,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight, NULL, 0, 0);

		GdiTransparentBlt(hdc,
			destX - _rotateImage->width / 2,
			destY - _rotateImage->height / 2,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);
	}
	else
	{
		PlgBlt(hdc, rPoint, _imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight, NULL, 0, 0);
	}
}