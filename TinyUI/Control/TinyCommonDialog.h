#pragma once
#include <Richedit.h>
#include "TinyDialog.h"

namespace TinyUI
{
	/// <summary>
	/// 字体对话框
	/// </summary>
	class TinyFontDialog :public TinyDialog
	{
		DECLARE_DYNAMIC(TinyFontDialog)
	private:
		CHOOSEFONT m_cf;
		LOGFONT m_lf; 
		TCHAR m_szStyleName[64];
	public:
		TinyFontDialog(LPLOGFONT lplfInitial = NULL,
			DWORD dwFlags = CF_EFFECTS | CF_SCREENFONTS,
			HDC hDCPrinter = NULL,
			HWND pParentWnd = NULL);
		TinyFontDialog(const CHARFORMAT& charformat,
			DWORD dwFlags = CF_SCREENFONTS,
			HDC hDCPrinter = NULL,
			HWND pParentWnd = NULL);
		virtual INT_PTR DoModal(HWND hParent);
		void GetCurrentFont(LPLOGFONT lplf);
		TinyString GetFaceName() const;  
		TinyString GetStyleName() const;
		INT GetSize() const;        
		COLORREF GetColor() const;  
		INT GetWeight() const;        
		BOOL IsStrikeOut() const;   
		BOOL IsUnderline() const;   
		BOOL IsBold() const;         
		BOOL IsItalic() const;      
		void GetCharFormat(CHARFORMAT& cf) const;
		DWORD FillInLogFont(const CHARFORMAT& cf);
	};
	/// <summary>
	/// 文件对话框
	/// </summary>
	class TinyFileDialog :public TinyDialog
	{
		DECLARE_DYNAMIC(TinyFileDialog)
	private:
		BOOL m_bOpenFileDialog;
		TCHAR m_szFileTitle[64*10];    
		TCHAR m_szFileName[_MAX_PATH*10];
	public:
		OPENFILENAME m_ofn;
		explicit TinyFileDialog(BOOL bOpenFileDialog, 
			LPCTSTR lpszDefExt = NULL,
			LPCTSTR lpszFileName = NULL,
			DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			LPCTSTR lpszFilter = NULL,
			DWORD dwSize = 0,
			BOOL bVistaStyle = TRUE);
		virtual ~TinyFileDialog();	
		virtual INT_PTR DoModal(HWND hParent);
		BOOL IsReadOnly() const;
		void SetFilterText(LPCSTR pzFilter);
		TinyString GetPathName() const;
		TinyString GetFileName() const;
		TinyString GetFileExt() const;
		TinyString GetFileTitle() const;
	};
}