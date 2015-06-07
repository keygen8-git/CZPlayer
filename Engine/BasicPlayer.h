/***************************************************************************
*   Copyright (C) 2012-2015 Highway-9 Studio.                             *
*   787280310@qq.com									                   *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   CUIT Highway-9 Studio, China.									       *
***************************************************************************/

/*!
* \file   BasicPlayer.h
* \author chengxuan   787280310@qq.com
* \date   2015-02-06
* \brief  ��������ͷ�ļ���
* \version 3.0.0
*
* \verbatim
* ��ʷ
*          3.0.0   ����,
*          2015-02-06    by chengxuan
*
* \endverbatim
*
*/

#ifndef BASICPLAYER_H
#define BASICPLAYER_H

/*! \def BASICPLAYER_VERSION
*  �汾���ƺ꣬��Ӧv3.0.0�汾.
*/
#define BASICPLAYER_VERSION   0x030000

#include "AudioStream.h"
#include "FastFourierTransform.h"
#include "Utils.h"
#include "Thread.h"
#include "signal_slot.h"
#include <vector>
using namespace std;

// pre-defined class
class CCriticalSection;
class CInput;
class CFileInput;
class CWmaInput;
class CMp3Input;
class CWaveInput;
class CVorbisInput;
class CBasicPlayer;
class CSpectrumAnalyser;

#pragma warning(disable : 4244)

/************************************************************************/
/* CSystem                                                              */
/************************************************************************/
typedef __int64				jlong;
typedef unsigned int		juint;
typedef unsigned __int64	julong;
typedef long				jint;
typedef signed char			jbyte;

#define CONST64(x)				(x ## LL)
#define NANOS_PER_SEC			CONST64(1000000000)
#define NANOS_PER_MILLISEC		1000000

jlong as_long(LARGE_INTEGER x);
void set_high(jlong* value, jint high);
void set_low(jlong* value, jint low);

class CSystem
{
private:
    static jlong frequency;
    static int ready;

    static void init()
    {
        LARGE_INTEGER liFrequency = { 0 };
        QueryPerformanceFrequency(&liFrequency);
        frequency = as_long(liFrequency);
        ready = 1;
    }
public:
    static jlong nanoTime()
    {
        if (ready != 1)
            init();

        LARGE_INTEGER liCounter = { 0 };
        QueryPerformanceCounter(&liCounter);
        double current = as_long(liCounter);
        double freq = frequency;
        return (jlong)((current / freq) * NANOS_PER_SEC);
    }
};

/************************************************************************/
/* CPlayThread                                                          */
/************************************************************************/

/*! �����߳�
*/
class CPlayThread : public CThread
{
public:
    CPlayThread(CBasicPlayer* pPlayer);
    ~CPlayThread(void);

protected:
    void Execute();					//ִ��

c_signals:
    Signal sigFinished;			//��������ź�

private:
    CBasicPlayer* m_Player;
    CCriticalSection* m_CriticalSection;
};

/************************************************************************/
/* CSpectrumAnalyserThread                                              */
/************************************************************************/

/*! Ƶ�׷����߳�
*/
class CSpectrumAnalyserThread : public CThread
{
public:
    CSpectrumAnalyserThread(CSpectrumAnalyser* pSpectrumAnalyser);
    ~CSpectrumAnalyserThread(void);

private:
    CBasicPlayer* m_Player;
    CSpectrumAnalyser* m_SpectrumAnalyser;
    CCriticalSection* m_CriticalSection;
    bool m_process;
    jlong m_lfp;
    int m_frameSize;

private:
    int calculateSamplePosition();
    void processSamples(int pPosition);

protected:
    void Execute();
};

/************************************************************************/
/* CSpectrumAnalyser��Ƶ�׷�����                                        */
/************************************************************************/

/*! Ƶ�׷�����
*/
class CSpectrumAnalyser
{
    friend class CSpectrumAnalyserThread;

public:
    CSpectrumAnalyser(CBasicPlayer* pPlayer);
    ~CSpectrumAnalyser(void);

public:
    void Start();
    void Stop();
    void Process(float pFrameRateRatioHint);

    jbyte* GetAudioDataBuffer() { return m_AudioDataBuffer; }

    int GetPosition() { return m_position; }
    void SetPosition(int pPosition) { m_position = pPosition; }

    DWORD GetAudioDataBufferLength() { return m_AudioDataBufferLength; }
    void SetAudioDataBufferLength(DWORD pAudioDataBufferLength) { m_AudioDataBufferLength = pAudioDataBufferLength; }

c_signals:
    Signal1<vector<float>> sigSpectrumChanged;

private:
    CBasicPlayer* m_Player;
    CSpectrumAnalyserThread* m_SpectrumAnalyserThread;	//Ƶ�׷����߳�
    CFastFourierTransform* m_FFT;						//���ٸ���Ҷ�任
    vector<float> m_vecFrequency;						//Ƶ�ʼ���

    /* digital signal process */
    DWORD m_AudioDataBufferLength;
    jbyte* m_AudioDataBuffer;
    int m_SampleSize;
    LONG m_FpsAsNS;
    LONG m_DesiredFpsAsNS;
    float* m_Left;
    float* m_Right;
    int m_position;
    int m_offset;
    int m_sampleType;
    int m_channelMode;

    /* spectrum analyser */
    int m_width;
    int m_height;
    int* m_peaks;
    int* m_peaksDelay;
    float* m_oldFFT;
    int m_saFFTSampleSize;
    int m_saBands;
    float m_saMultiplier;
    float m_saDecay;
    int m_barOffset;
    int m_peakDelay;
    int m_winwidth, m_winheight;
};

/************************************************************************/
/* CBasicPlayer                                                         */
/************************************************************************/

/*! ����������
*/
class CBasicPlayer
{
    //friend class declare
    friend class CPlayThread;
    friend class CSpectrumAnalyser;

public:
    /*! ���캯��
    *  \param fileName �ļ�·��
    */
    CBasicPlayer(TCHAR* fileName);

    /*! ��������.*/
    ~CBasicPlayer(void);

public:
    /*! ���Input�ļ���
    */
    CFileInput* GetInput();

    /*! �Ƿ���Ի�ȡ����Դ
    */
    bool isVaild();

    /*! ��ʼ����
    */
    void Start();

    /*! ֹͣ����
    */
    void Stop();

    /*! ��ͣ
    */
    void Pause();

    /*! �ָ�����
    */
    void Play();

    /*! ��ȡ֡λ��
    */
    jlong GetLongFramePosition();

c_signals:
    Signal1<vector<float>> sigSpectrumChanged;	/*!< Ƶ�׸ı�*/
    Signal sigFinished;							/*!< �������*/

private c_slots:
    /*! Ƶ�׸ı�
     * \param vecFrequency Ƶ������
     */
    void handleSpectrumChanged(vector<float> vecFrequency);

    /*! �������
    */
    void handleFinished();

private:
    CPlayThread* m_PlayThread;				/*!< �����߳�*/
    CSpectrumAnalyser* m_SpectrumAnalyser;	/*!< Ƶ�׷�����*/
    CCriticalSection* m_CriticalSection;	/*!< �ٽ���*/

    CFileInput* m_Input;			/*!< �ļ�IO*/
    CWmaInput* m_WmaInput;			/*!< wma�ļ�IO*/
    CMp3Input* m_Mp3Input;			/*!< mp3�ļ�IO*/
    CWaveInput* m_WavInput;			/*!< wave�ļ�IO*/
    CVorbisInput* m_VorbisInput;	/*!< vorbis�ļ�IO*/

    DS_Info* m_info;				/*!< DirectSound��Ϣ*/
    volatile long m_bytePosition;	/*!< byteλ��*/

    DWORD m_BufferSize;				/*!< ��������С*/
    float m_SampleRate;				/*!< ������*/
    WORD m_FrameSize;				/*!< ֡��*/
    WORD m_BitPerSample;			/*!< ÿ�������*/
    WORD m_Channels;				/*!< ͨ����*/

    /*! ���ָ�ʽ*/
    enum MusicFormat
    {
        mp3 = 1,
        wav = 2,
        wma = 3,
        ogg = 4
    };

    MusicFormat m_musicFormat;	/*!< ���ָ�ʽ*/
};

#endif
