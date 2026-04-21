#pragma once
typedef struct tdf_ST_YiLou
{
	int nBallIndex;//球的号码
	int nCurYiLou;//当期遗漏数
	int nLastYiLou;//上期遗漏数
	int nTotalAppear;//总共出现次数
	bool operator < (tdf_ST_YiLou& yilou)
	{
		if (nCurYiLou == yilou.nCurYiLou)
		{
			return nLastYiLou > yilou.nLastYiLou;
		}
		return nCurYiLou > yilou.nCurYiLou;
	}

}ST_YiLou;

typedef struct tdf_ST_YiLou_BallIdx
{
	int nBallIndex;
	int nCurYiLou;
	int nLastYiLou;
	int nTotalAppear;
	bool operator < (tdf_ST_YiLou_BallIdx& yilou)
	{
		return nBallIndex < yilou.nBallIndex;
	}

}ST_YiLou_BallIdx;

typedef struct tdf_ST_YiLou_BallTotalIdx
{
	int nBallIndex;
	int nCurYiLou;
	int nLastYiLou;
	int nTotalAppear;
	bool operator < (tdf_ST_YiLou_BallTotalIdx& yilou)
	{
		return nTotalAppear < yilou.nTotalAppear;
	}

}ST_YiLou_BallTotalIdx;

typedef struct tdf_ST_DaLeTouBlue
{
	int nSerial;
	int nBlue1;
	int nBlue2;
	bool operator < (tdf_ST_DaLeTouBlue& aa)
	{
		return nSerial > aa.nSerial;
	}

}ST_DaLeTouBlue;

typedef struct tdf_ST_DaLeTouRed
{
	int nSerial;
	int nRed1;
	int nRed2;
	int nRed3;
	int nRed4;
	int nRed5;
	bool operator < (tdf_ST_DaLeTouRed& aa)
	{
		return nSerial > aa.nSerial;
	}
}ST_DaLeTouRed;


typedef struct tdf_ST_RedInfo
{
	wchar_t cSerial[50];
	wchar_t cKaiHao[50];
	wchar_t cChuXianQu[50];
	wchar_t cYiLouQu[50];
	wchar_t cShangQiYiLou[50];
}ST_RedInfo;

typedef struct tdf_ST_DaLeTouRedYiLou
{
	wchar_t cSerial[50];
	wchar_t cYiLouQu[50];
}ST_DaLeTouRedYiLou;
