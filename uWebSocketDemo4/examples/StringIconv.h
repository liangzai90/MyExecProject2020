#pragma once
#include <iconv.h>
#include <iostream>
#include <memory.h>
#include <string>
#include <locale>
#include <codecvt>

/*
 *create by tracy 20160202 �ַ������� utf-8תGBK gbkתutf-8 �ȵ�
 * example:
 IconvConvertString cc = IconvConvertString("gb2312", "utf-8"); 
 char *str_gb2312 = "�������123";
 char outString[m_gOutStringLen] = {0};
 cc2.ConvertCode(str_gb2312, strlen(str_gb2312), outString, m_gOutStringLen); 
 */

using namespace std;

class IconvConvertString
{
public:
	enum
	{
		NOT_CONVERT = 0,
		GBK_2_UTF8 = 1,
		UTF8_2_GBK
	};
	static const int m_gOutStringLen = 255;
	// ����
	IconvConvertString()
	{
		cd = iconv_open("utf-8", "gbk");
	}

	IconvConvertString(const char *from_charset, const char *to_charset)
	{
		cd = iconv_open(to_charset, from_charset);
	}

	// ����
	~IconvConvertString()
	{
		iconv_close(cd);
	}

	// ת�����
	size_t ConvertCode(char *inbuf, int inlen, char *outbuf, int outlen)
	{
		char **pin = &inbuf, **pout = &outbuf;
		size_t inSize = (size_t)inlen, outSize = (size_t)outlen;

		memset(outbuf, 0, outlen);
		return iconv(cd, pin, &inSize, pout, &outSize);
	}

private:
	iconv_t cd;
};



std::wstring s2ws(const std::string& str)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;
 
    return converterX.from_bytes(str);
}
 
std::string ws2s(const std::wstring& wstr)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;
 
    return converterX.to_bytes(wstr);
}
		
