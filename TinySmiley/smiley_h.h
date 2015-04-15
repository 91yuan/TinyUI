

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Wed Apr 15 15:58:37 2015
 */
/* Compiler settings for smiley.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __smiley_h_h__
#define __smiley_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ISmileySource_FWD_DEFINED__
#define __ISmileySource_FWD_DEFINED__
typedef interface ISmileySource ISmileySource;

#endif 	/* __ISmileySource_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ISmileySource_INTERFACE_DEFINED__
#define __ISmileySource_INTERFACE_DEFINED__

/* interface ISmileySource */
/* [helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISmileySource;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FE78387F-D150-4089-832C-BBF02402C872")
    ISmileySource : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE LoadStream( 
            /* [in] */ LPSTREAM pStm) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LoadFile( 
            /* [in] */ LPCWSTR pszFilePath) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SaveAs( 
            /* [in] */ LPSTREAM pStm) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFile( 
            /* [out] */ BSTR *bstrFile) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFrameCount( 
            /* [out] */ int *pFrameCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFrameDelay( 
            /* [in] */ int iFrame,
            /* [out] */ int *pFrameDelay) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSize( 
            /* [out] */ LPSIZE pSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Draw( 
            /* [in] */ HDC hdc,
            /* [in] */ LPCRECT pRect,
            /* [in] */ int iFrame) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISmileySourceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISmileySource * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISmileySource * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISmileySource * This);
        
        HRESULT ( STDMETHODCALLTYPE *LoadStream )( 
            ISmileySource * This,
            /* [in] */ LPSTREAM pStm);
        
        HRESULT ( STDMETHODCALLTYPE *LoadFile )( 
            ISmileySource * This,
            /* [in] */ LPCWSTR pszFilePath);
        
        HRESULT ( STDMETHODCALLTYPE *SaveAs )( 
            ISmileySource * This,
            /* [in] */ LPSTREAM pStm);
        
        HRESULT ( STDMETHODCALLTYPE *GetFile )( 
            ISmileySource * This,
            /* [out] */ BSTR *bstrFile);
        
        HRESULT ( STDMETHODCALLTYPE *GetFrameCount )( 
            ISmileySource * This,
            /* [out] */ int *pFrameCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetFrameDelay )( 
            ISmileySource * This,
            /* [in] */ int iFrame,
            /* [out] */ int *pFrameDelay);
        
        HRESULT ( STDMETHODCALLTYPE *GetSize )( 
            ISmileySource * This,
            /* [out] */ LPSIZE pSize);
        
        HRESULT ( STDMETHODCALLTYPE *Draw )( 
            ISmileySource * This,
            /* [in] */ HDC hdc,
            /* [in] */ LPCRECT pRect,
            /* [in] */ int iFrame);
        
        END_INTERFACE
    } ISmileySourceVtbl;

    interface ISmileySource
    {
        CONST_VTBL struct ISmileySourceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISmileySource_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISmileySource_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISmileySource_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISmileySource_LoadStream(This,pStm)	\
    ( (This)->lpVtbl -> LoadStream(This,pStm) ) 

#define ISmileySource_LoadFile(This,pszFilePath)	\
    ( (This)->lpVtbl -> LoadFile(This,pszFilePath) ) 

#define ISmileySource_SaveAs(This,pStm)	\
    ( (This)->lpVtbl -> SaveAs(This,pStm) ) 

#define ISmileySource_GetFile(This,bstrFile)	\
    ( (This)->lpVtbl -> GetFile(This,bstrFile) ) 

#define ISmileySource_GetFrameCount(This,pFrameCount)	\
    ( (This)->lpVtbl -> GetFrameCount(This,pFrameCount) ) 

#define ISmileySource_GetFrameDelay(This,iFrame,pFrameDelay)	\
    ( (This)->lpVtbl -> GetFrameDelay(This,iFrame,pFrameDelay) ) 

#define ISmileySource_GetSize(This,pSize)	\
    ( (This)->lpVtbl -> GetSize(This,pSize) ) 

#define ISmileySource_Draw(This,hdc,pRect,iFrame)	\
    ( (This)->lpVtbl -> Draw(This,hdc,pRect,iFrame) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISmileySource_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  HDC_UserSize(     unsigned long *, unsigned long            , HDC * ); 
unsigned char * __RPC_USER  HDC_UserMarshal(  unsigned long *, unsigned char *, HDC * ); 
unsigned char * __RPC_USER  HDC_UserUnmarshal(unsigned long *, unsigned char *, HDC * ); 
void                      __RPC_USER  HDC_UserFree(     unsigned long *, HDC * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


