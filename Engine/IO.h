#ifndef INCLUDE_IO
#define INCLUDE_IO

#include "AudioStream.h"
#include "CriticalSection.h"
#include "Stream.h"
/* libmad support */
#include "mad.h"
/* libogg support */
#include "ogg.h"
/* libvorbis support */
#include "codec.h"
#include "vorbisfile.h"

#include <stdio.h>
#include <iostream>
using namespace std;

/************************************************************************/
/* CInput                                                               */
/************************************************************************/
class CInput
{
public:
    CInput(void);
    ~CInput(void);

public:
    virtual void Reset();										//����
    virtual void Pause();										//��ͣ
    virtual void Resume();										//�ָ������¿�ʼ
    virtual DWORD GetTotalTime();								//�����ʱ��
    virtual LARGE_INTEGER GetTotalSamples();					//����ܵĲ�����

    virtual WORD GetBitsPerSample() = 0;						//���ÿ��Ĳ�����
    virtual WORD GetChannels() = 0;								//���ͨ����
    virtual DWORD GetSampleRate() = 0;							//��ò�����

    LARGE_INTEGER GetSize();									//�õ��ļ���С
    LARGE_INTEGER GetPosition();								//���λ��
    void GetData(void** buffer, DWORD* size);					//�õ�����
    DWORD CopyData(void* buffer, DWORD size);					//��������
    DWORD FillBuffer(void* buffer, DWORD size, bool* eof);		//��仺����
    void Init();												//��ʼ��
    void Flush();												//Flush������
    void Lock();												//����
    void Unlock();												//����

protected:
    LARGE_INTEGER m_Position;									//λ��
    LARGE_INTEGER m_Size;										//��С
    WORD m_SampleSize;											//�����ʴ�С
    bool m_Busy;												//�Ƿ�æ
    DWORD m_BufferStart;										//��������ʼ
    DWORD m_BufferEnd;											//����������
    CCriticalSection* m_DataCS;									//�ٽ���
    bool m_EndOfStream;											//�ļ����Ƿ����

protected:
    virtual void InitInternal() = 0;								//��ʼ���ڲ�����
    virtual void FlushInternal() = 0;								//Flush�ڲ�����
    virtual void GetDataInternal(void** buffer, DWORD* bytes) = 0;	//��ȡ�ڲ�����
};

/************************************************************************/
/* CStreamedInput                                                       */
/************************************************************************/
class CStreamedInput : public CInput
{
public:
    CStreamedInput(void);
    ~CStreamedInput(void);

public:
    void GetData(void** buf, DWORD* Bytes);							//�������
    bool Seek(LARGE_INTEGER* SampleNum);							//��λ
    CStream* GetStream() { return m_pStream; }						//����ļ���

protected:
    CStream* m_pStream;												//�ļ���ָ��
    bool m_StreamAssigned;											//�ļ����Ƿ����
    bool m_Seekable;												//�Ƿ�ɶ�λ
    LARGE_INTEGER m_StartSample;									//������ʼλ��
    LARGE_INTEGER m_EndSample;										//��������λ��
    bool m_Loop;													//�Ƿ�ѭ��
    LARGE_INTEGER m_TotalSamples;									//�ܵĲ�����

protected:
    virtual void SetStream(CStream* pStream);						//�õ���
    virtual bool SeekInternal(LARGE_INTEGER* SampleNum) = 0;		//��λ�ڲ�����
};

/************************************************************************/
/* CFileInput                                                              */
/************************************************************************/
class CFileInput : public CStreamedInput
{
public:
    CFileInput(void);
    ~CFileInput(void);

public:
    virtual void OpenFile() = 0;									//���ļ�
    virtual void CloseFile() = 0;									//�ر��ļ�

    void SetFileName(TCHAR* pszFileName);							//�����ļ�����
    size_t GetFileNameLen();										//����ļ�������
    WORD GetBitsPerSample();										//���ÿ�������
    DWORD GetSampleRate();											//��ò�����
    WORD GetChannels();												//���ͨ����
    int GetOpened();												//�ļ��Ƿ񱻴�

    bool GetValid();												//�ļ��Ƿ��ǿɵõ���
    LARGE_INTEGER GetTotalSamples();								//����ܵĲ�����
    DWORD GetTotalTime();											//�����ʱ��

    bool SetStartTime(DWORD Minutes, DWORD Seconds);				//���ÿ�ʼʱ��
    bool SetEndTime(DWORD Minutes, DWORD Seconds);					//���ý���ʱ��
    void Reset();													//����
    void Jump(int offset);											//����offsetλ��

protected:
    CCriticalSection* m_OpenCS;										//�ٽ���
    TCHAR m_FileName[MAX_PATH];										//�ļ���
    size_t m_FileNameLen;											//�ļ�������
    int m_Opened;													//�ļ��Ƿ��
    bool m_Valid;													//�ļ����Ƿ�ɻ��
    WORD m_BitsPerSample;											//ÿ�������
    DWORD m_SampleRate;												//������
    WORD m_Channels;												//ͨ����
    DWORD m_Time;													//ʱ��

protected:
    void SetStream(CStream* pStream);								//������
    void FlushInternal();											//Flush�ڲ�����
    void InitInternal();											//��ʼ���ڲ�����
};

/************************************************************************/
/* CWmaInput                                                                */
/************************************************************************/
typedef enum _ChannelsNumber
{
    cnMaxAvailable = 0,
    cnMonoOrStereo,
    cn5dot1,
    cn7dot1
} ChannelsNumber;

const int wmfDefault = -2;

class CWmaInput : public CFileInput
{
private:
    WMA_SYNC_READER* m_Reader;
    DWORD m_Duration;
    bool m_HighPrecision;
    ChannelsNumber m_OutputChannels;
    int m_Format;

    SHORT CNToShortInt();

protected:
    void GetDataInternal(void** buffer, DWORD* bytes);
    bool SeekInternal(LARGE_INTEGER* SampleNum);

public:
    CWmaInput(void);
    ~CWmaInput(void);

    void OpenFile();
    void CloseFile();

    void SetHighPrecision(bool HighPrecision);
    void SetOutputChannels(ChannelsNumber OutputChannels);
    bool GetHasAudio();
    bool GetProtected();
    DWORD GetBitrate();
    bool GetIsVBR();
    DWORD GetFormatsCount();
    void GetFormatSpec(int index, WMAFormatSpec* pFormatSpec);
    void SetFormat(int iFormat);
    int GetFormat();
};

/************************************************************************/
/* CWaveInput                                                           */
/************************************************************************/
#define BUF_SIZE 16000

#define WaveHeaderOffs 44
#define DataSizeOffs 40

//wav�ļ��ṹ��־
#define LookingForRIFF 0
#define LookingForWave 1
#define LookingForFMT 2
#define LookingForFACT 3
#define LookingForDATA 4

#define WAVE_FORMAT_MP3 85

//wav�ļ�������
typedef enum _WaveType
{
    wtUnsupported = 1,
    wtPCM = 2,
    wtDVIADPCM = 3,
    wtMSADPCM = 4,
    wtACM = 5,
    wtIEEEFloat = 6,
    wtExtPCM = 7,
    wtExtIEEEFloat = 8
} WaveType;

////////////////////////////��ʼ����wav�ļ��ṹ��////////////////////////////////
typedef struct _WaveHeader
{
    char RIFF[4]; /* 'RIFF' offset : 0000 */
    DWORD FileSize; /* FileSize - 8 offset : 0004 */
    char RIFFType[4]; /* 'WAVE'  offset : 0008 */
    char FmtChunkId[4]; /* 'fmt '   offset : 0012 */
    DWORD FmtChunkSize; /* 16      offset : 0016 */
    WORD FormatTag; /* One of WAVE_FORMAT_XXX constants    offset : 0020 */
    WORD Channels; /* 1 - mono = 2 - stereo             offset : 0022 */
    DWORD SampleRate; /* offset : 0024 */
    DWORD BytesPerSecond; /* offset : 0028 */
    WORD BlockAlign; /* offset : 0032 */
    WORD BitsPerSample; /* 8, 16 or 32 Bits/sample offset : 0034 */
    char DataChunkId[4]; /* 'data' offset : 0036*/
    DWORD DataSize; /* Data size in bytes offset : 0040 */
} WaveHeader, *LPWaveHeader;

typedef struct _WaveHeaderEx
{
    char RIFF[4];
    DWORD FileSize;
    char RIFFType[4];
    char FmtChunkId[4];
    DWORD FmtChunkSize;
    WAVEFORMATEXTENSIBLE Format;
    char DataChunkId[4];
    DWORD DataSize;
} WaveHeaderEx, *LPWaveHeaderEx;

typedef struct _DVIADPCMHeader
{
    char RIFF[4];
    DWORD FileSize;
    char RIFFType[4];
    char FmtChunkId[4];
    DWORD FmtChunkSize;
    WORD FormatTag; //WAVE_FORMAT_DVI_ADPCM
    WORD Channels;
    DWORD SampleRate;
    DWORD BytesPerSecond;
    WORD BlockAlign;
    WORD BitsPerSample;
    WORD cbSize;
    WORD SamplesPerBlock;
    char FactChunkId[4];
    DWORD FactChunkSize;
    DWORD DataLength;
    char DataChunkId[4];
    DWORD DataSize;
} DVIADPCMHeader, *LPDVIADPCMHeader;

typedef struct _DVI_ADPCM_INFO
{
    WORD BlockLength;
    WORD SamplesPerBlock;
    DWORD DataSize;
} DVI_ADPCM_INFO, *LPDVI_ADPCM_INFO;

typedef struct _DVI_ADPCM_STATE_STEREO
{
    SHORT valprev_l; // Previous output value
    BYTE index_l; // Index into stepsize table
    SHORT valprev_r; // Previous output value
    BYTE index_r; // Index into stepsize table
} DVI_ADPCM_STATE_STEREO, *LPDVI_ADPCM_STATE_STEREO;

typedef struct _DVI_ADPCM_ENCODE_STATE_STEREO
{
    SHORT PredSamp_l;
    BYTE Index_l;
    SHORT PredSamp_r;
    BYTE Index_r;
} DVI_ADPCM_ENCODE_STATE_STEREO, *LPDVI_ADPCM_ENCODE_STATE_STEREO;

typedef struct _MS_ADPCM_COEF_SET
{
    SHORT Coef1;
    SHORT Coef2;
} MS_ADPCM_COEF_SET, *LPMS_ADPCM_COEF_SET;

typedef struct _MS_ADPCM_INFO
{
    WORD BlockLength;
    WORD SamplesPerBlock;
    DWORD DataSize;
    WORD NumCoeff;
    MS_ADPCM_COEF_SET CoefSets[32];
} MS_ADPCM_INFO, *LPMS_ADPCM_INFO;

typedef struct _MSADPCMBlockHeaderMono
{
    BYTE predictor;
    SHORT Delta;
    SHORT Samp1;
    SHORT Samp2;
} MSADPCMBlockHeaderMono, *LPMSADPCMBlockHeaderMono;

typedef struct _MSADPCMBlockHeaderStereo
{
    BYTE predictor[2];
    SHORT Delta[2];
    SHORT Samp1[2];
    SHORT Samp2[2];
} MSADPCMBlockHeaderStereo, *LPMSADPCMBlockHeaderStereo;

typedef struct _DVIADPCMBlockHeader
{
    SHORT Samp0;
    BYTE StepTableIndex;
    BYTE Reserved;
} DVIADPCMBlockHeader, *LPDVIADPCMBlockHeader;

////////////////////////////��������wav�ļ��ṹ��////////////////////////////////

//��ȡwav�ļ�����
class CWaveInput : public CFileInput
{
public:
    CWaveInput(void);
    ~CWaveInput(void);

public:
    void OpenFile();																//���ļ�
    void CloseFile();																//�ر��ļ�

protected:
    void GetDataInternal(void** buffer, DWORD* bytes);								//����ڲ�����
    bool SeekInternal(LARGE_INTEGER* SampleNum);									//��λ�ڲ�����

private:
    BYTE m_Buf[BUF_SIZE];															//������
    WaveType m_WavType;																//wav��ʽ����

    //wav��ʽ����
    DVI_ADPCM_INFO m_DVI_ADPCM_INFO;
    DVI_ADPCM_STATE_STEREO m_DVI_ADPCM_STATE;
    MS_ADPCM_INFO m_MS_ADPCM_INFO;
    MSADPCMBlockHeaderStereo m_MS_ADPCM_STATE;

    WORD m_HeaderSize;																//wavͷ��С
    CMemoryStream* m_MS;
    CStream* m_OldStream;
    bool m_OldStreamAssigned;
    bool m_ShortIEEEFloat;

private:
    bool ReadDVIADPCMBlock(void* pData);											//��ȡDVIADPCM��
    bool ReadMSADPCMBlock(void* pData);												//��ȡMSADPCM��
    WaveType GetWavType();															//��ȡwav��ʽ����
    void ReadRIFFHeader();															//��ȡRIFFͷ
    void DecodeDVIADPCMMono(BYTE* pInData, SHORT* pOutData, DWORD *len);			//��DVIADPCMMono���ͽ��н���
    void DecodeDVIADPCMStereo(BYTE* pInData, SHORT* pOutData, DWORD* len);			//��DVIADPCMStereo���ͽ��н���
    void DecodeMSADPCMMono(BYTE* pInData, SHORT* pOutData, DWORD* len);				//��MSADPCMMono���ͽ��н���
    void DecodeMSADPCMStereo(BYTE* pInData, SHORT* pOutData, DWORD* len);			//��MSADPCMStereo���н���
};

bool Compare4(CHAR* S1, CHAR* S2);
void ConvertIEEEFloatTo32(int* InOutBuf, int InSize);
void ConvertShortIEEEFloatTo32(int* InOutBuf, int InSize);

/************************************************************************/
/* CMp3Input                                                               */
/************************************************************************/
# define SAMPLE_DEPTH 16
# define scale(x, y) dither((x), (y))

struct xing
{
    long flags;
    unsigned long frames;
    unsigned long bytes;
    unsigned char toc[100];
    long scale;
};

enum
{
    XING_FRAMES = 0x00000001L,
    XING_BYTES  = 0x00000002L,
    XING_TOC    = 0x00000004L,
    XING_SCALE  = 0x00000008L
};

# define XING_MAGIC (('X' << 24) | ('i' << 16) | ('n' << 8) | 'g')

struct dither
{
    mad_fixed_t error[3];
    mad_fixed_t random;
};

typedef struct _ID3Tag
{
    char m_cTAG[3];  // Must equal "TAG"
    char m_cSong[30];
    char m_cArtist[30];
    char m_cAlbum[30];
    char m_cYear[4];
    char m_cComment[30];
    unsigned char m_cGenre;
} ID3Tag;

typedef struct _ID3v2Tag
{
    char m_cTAG[3];  // Must equal ID3
    unsigned char m_cVersion[2]; // Major / Minor
    unsigned char m_cFlags;
    unsigned char m_cSize_Encoded[4];
} ID3v2Tag;

typedef struct _ID3v2Frame
{
    char m_cFrameID[4];
    unsigned char m_cSize_Encoded[4];
    unsigned short m_cFlags;
} ID3v2Frame;

int parse_xing(struct xing *xing, struct mad_bitptr ptr, unsigned int bitlen);
int scan_header(CStream* pStream, struct mad_header *header, struct xing *xing);							//��ȡmp3ͷ��Ϣ
void pack_pcm(unsigned char **pcm, unsigned int nsamples, mad_fixed_t const *ch1, mad_fixed_t const *ch2);

class CMp3Input : public CFileInput
{
public:
    CMp3Input(void);
    ~CMp3Input(void);

public:
    void OpenFile();
    void CloseFile();

private:
    unsigned long m_size;
    unsigned long m_streamsize;
    unsigned int m_samplecount;
    mad_timer_t m_timer;
    mad_timer_t m_length;
    unsigned long m_rate;
    unsigned long m_frames;

    struct mad_stream m_stream;
    struct mad_frame m_frame;
    struct mad_synth m_synth;
    struct xing m_xing;
    bool m_vbr;				//cbr:����λ���ʣ�vbr:�ɱ�λ����

    unsigned char m_buffer[40000];
    unsigned int m_buflen;
    unsigned char m_pcmbuffer[BUF_SIZE];

protected:
    void GetDataInternal(void** buffer, DWORD* bytes);
    bool SeekInternal(LARGE_INTEGER* SampleNum);
};

/************************************************************************/
/* CVorbisInput                                                            */
/************************************************************************/
class CVorbisInput : public CFileInput
{
private:
    OggVorbis_File m_OggVorbisFile;
    int m_CurrentSection;

    unsigned char m_buffer[40000];
    unsigned int m_buflen;
    unsigned char m_pcmbuffer[BUF_SIZE];
protected:
    void GetDataInternal(void** buffer, DWORD* bytes);
    bool SeekInternal(LARGE_INTEGER* SampleNum);
public:
    CVorbisInput(void);
    ~CVorbisInput(void);

    void OpenFile();
    void CloseFile();

};

size_t vorbisRead(void *buffer, size_t size, size_t amount, void *file);
int vorbisSeek(void *file, ogg_int64_t newpos, int set);
int vorbisClose(void *file);
long vorbisTell(void *file);

#endif

