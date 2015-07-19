

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Sat Jul 11 20:14:58 2015
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

#ifndef __ISmiley_FWD_DEFINED__
#define __ISmiley_FWD_DEFINED__
typedef interface ISmiley ISmiley;

#endif 	/* __ISmiley_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ISmiley_INTERFACE_DEFINED__
#define __ISmiley_INTERFACE_DEFINED__

/* interface ISmiley */
/* [helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISmiley;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("767F59D8-A4DD-4659-A6BC-3769D219F902")
    ISmiley : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE LoadStream( 
            /* [in] */ LPSTREAM pStm) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LoadFile( 
            /* [in] */ LPCSTR pszFilePath) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SaveAs( 
            /* [in] */ LPSTREAM pStm) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFrameCount( 
            /* [out] */ int *pFrameCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFrameDelay( 
            /* [in] */ int iFrame,
            /* [out] */ unsigned int *pFrameDelay) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSize( 
            /* [out] */ LPSIZE pSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Draw( 
            /* [in] */ HDC hdc,
            /* [in] */ LPCRECT pRect,
            /* [in] */ int iFrame) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISmileyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISmiley * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISmiley * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISmiley * This);
        
        HRESULT ( STDMETHODCALLTYPE *LoadStream )( 
            ISmiley * This,
            /* [in] */ LPSTREAM pStm);
        
        HRESULT ( STDMETHODCALLTYPE *LoadFile )( 
            ISmiley * This,
            /* [in] */ LPCSTR pszFilePath);
        
        HRESULT ( STDMETHODCALLTYPE *SaveAs )( 
            ISmiley * This,
            /* [in] */ LPSTREAM pStm);
        
        HRESULT ( STDMETHODCALLTYPE *GetFrameCount )( 
            ISmiley * This,
            /* [out] */ int *pFrameCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetFrameDelay )( 
            ISmiley * This,
            /* [in] */ int iFrame,
            /* [out] */ unsigned int *pFrameDelay);
        
        HRESULT ( STDMETHODCALLTYPE *GetSize )( 
            ISmiley * This,
            /* [out] */ LPSIZE pSize);
        
        HRESULT ( STDMETHODCALLTYPE *Draw )( 
            ISmiley * This,
            /* [in] */ HDC hdc,
            /* [in] */ LPCRECT pRect,
            /* [in] */ int iFrame);
        
        END_INTERFACE
    } ISmileyVtbl;

    interface ISmiley
    {
        CONST_VTBL struct ISmileyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISmiley_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISmiley_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISmiley_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISmiley_LoadStream(This,pStm)	\
    ( (This)->lpVtbl -> LoadStream(This,pStm) ) 

#define ISmiley_LoadFile(This,pszFilePath)	\
    ( (This)->lpVtbl -> LoadFile(This,pszFilePath) ) 

#define ISmiley_SaveAs(This,pStm)	\
    ( (This)->lpVtbl -> SaveAs(This,pStm) ) 

#define ISmiley_GetFrameCount(This,pFrameCount)	\
    ( (This)->lpVtbl -> GetFrameCount(This,pFrameCount) ) 

#define ISmiley_GetFrameDelay(This,iFrame,pFrameDelay)	\
    ( (This)->lpVtbl -> GetFrameDelay(This,iFrame,pFrameDelay) ) 

#define ISmiley_GetSize(This,pSize)	\
    ( (This)->lpVtbl -> GetSize(This,pSize) ) 

#define ISmiley_Draw(This,hdc,pRect,iFrame)	\
    ( (This)->lpVtbl -> Draw(This,hdc,pRect,iFrame) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISmiley_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  HDC_UserSize(     unsigned long *, unsigned long            , HDC * ); 
unsigned char * __RPC_USER  HDC_UserMarshal(  unsigned long *, unsigned char *, HDC * ); 
unsigned char * __RPC_USER  HDC_UserUnmarshal(unsigned long *, unsigned char *, HDC * ); 
void                      __RPC_USER  HDC_UserFree(     unsigned long *, HDC * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


