#pragma once
#include "../Common/TinyEvent.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

namespace TinyUI
{
	namespace Media{


#define mmioWAVE    mmioFOURCC('W','A','V','E')
#define mmioFMT     mmioFOURCC('f','m','t',' ')
#define mmioDATA    mmioFOURCC('d','a','t','a')
#define WAVE_READ   0;
#define WAVE_WRITE  1;
#define PI 3.14159265
#define PLAY_QUIT (WM_USER + 0x0123)//�̼߳䷢�Ͳ����˳���Ϣ

#define LoopEmpty() //�յ�ѭ��

#define MAX_AUDIO_BUFFERS	8
#define MIN_AUDIO_BUFFERS	2
#define AUDIO_BUFFER_SIZE	4096
#define DSOUND_BUFFERS		3

		/// <summary>
		/// Wave�ļ�������
		/// </summary>
		class TinyWaveFile
		{
		private:
			WAVEFORMATEX waveEx;
			DWORD dwSize;//���ݴ�С
			DWORD dwLSize;//ʣ�����ݴ�С
			DWORD dwDataOffset;//�������ݵ�ƫ����
			HMMIO hmmio;
		public:
			BOOL Open(LPTSTR pzFile);
			BOOL Open(LPVOID pStream, DWORD bufferSize);
			BOOL Read(BYTE* lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead);
			BOOL Seek(LONG lOffset, INT iOrigin);
			BOOL ResetFile();
			void Close();
			WAVEFORMATEX GetFormat();
			DWORD GetDataSize();
			DWORD GetDataOffset();
		};
		/// <summary>
		/// Wave�����
		/// </summary>
		class TinyWaveOut
		{
		private:
			HWAVEOUT hWaveOut;
		public:
			TinyWaveOut();
			~TinyWaveOut();
			operator HWAVEOUT() const throw();
			MMRESULT QueryFormat(LPWAVEFORMATEX pwfx);
			MMRESULT Open(LPWAVEFORMATEX pwfx, DWORD_PTR dwCallbackInstance);
			MMRESULT Pause();
			MMRESULT Reset();
			MMRESULT Restart();
			MMRESULT Close();
			MMRESULT SetVolume(DWORD dwVolume);
			MMRESULT GetDevCaps(UINT_PTR uDeviceID, LPWAVEOUTCAPS pwoc);
			MMRESULT GetPosition(LPMMTIME pmmt);
			MMRESULT Prepare(LPWAVEHDR pwh);
			MMRESULT Unprepare(LPWAVEHDR pwh);
			MMRESULT BreakLoop();
			MMRESULT Write(LPWAVEHDR pwh);
			MMRESULT SetPlaybackRate(DWORD dwRate);
			void	SendMessage(UINT uMsg, DWORD_PTR dwParam1, DWORD_PTR dwParam2);
			DWORD	GetVolume();
			DWORD	GetNumDevs();
			void	GetErrorText(LPTSTR pzText, MMRESULT hRes);
			static void CALLBACK waveOutProc(HWAVEOUT hwo, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2);
			virtual void OnOpen();
			virtual void OnClose();
			virtual void OnDone(LPWAVEHDR wp, DWORD_PTR dwInstance);
			Event<void(LPWAVEHDR, DWORD_PTR)> WaveDone;
		};
		/// <summary>
		/// Wave������
		/// </summary>
		class TinyWavePlayer
		{
		private:
			TinyWaveFile waveFile;
			TinyWaveOut waveOut;
			LPWAVEHDR  audioBlockPtr[MAX_AUDIO_BUFFERS];
			DWORD dwBlocks;
			DWORD dwBlockOut;
			DWORD dwBlockNext;
			DWORD dwSizeL;//��������
			BOOL bPlaying;
			Delegate<void(LPWAVEHDR, DWORD_PTR)> wavePlayDone;
			void PlayData();
		public:
			TinyWavePlayer();
			~TinyWavePlayer();
			BOOL LoadFile(LPSTR szFilename);
			BOOL LoadStream(LPVOID pStream, DWORD bufferSize);
			BOOL IsPlaying();
			BOOL Play(BOOL bLoop);
			BOOL Seek(DWORD newPos);
			void PlayDone(LPWAVEHDR wp, DWORD_PTR dwInstance);
			BOOL Pause();
			BOOL Restart();
			BOOL Reset();
			DWORD GetDataSize();
		};
	};
}


