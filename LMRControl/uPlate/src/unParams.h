//---------------------------------------------------------------------------

#ifndef unParamsH
#define unParamsH

#include <System.Classes.hpp>

#include "Singleton.h"

enum class TElisaReadType : Integer
{
	Normal = 0,
	Kinetic
};

enum class TElisaShakeIntensity : Integer
{
	LowIntensity = 0,
	ModerateIntensity,
	FastIntensity
};

enum class TElisaShakeMode : Integer
{
	ShakeFirst = 0,
	ShakeEach
};

enum class TElisaReadSpeed : Integer
{
	StandardSpeed = 0,
	FastSpeed
};

enum class TElisaReadMode : Integer
{
	OneWaveLength = 0,
	MultiWaveLength
};

enum class TElisaKineticType : Integer
{
	AverageRate = 0,
	MaximumRage,
	TimeToMaximumRate,
	TimeToChange,
	MaximumOfWell,
	TimeToMaximum
};

enum class TElisaKineticRateType : Integer
{
	Seconds = 0,
	Minutes
};

enum class TElisaKineticWindowType : Integer
{
	Window1 = 0,
	Window2
};

enum class TElisaKineticReactionType : Integer
{
	Undefined = 0,
	Incremental,
	Decremental
};

enum class TElisaKineticChangeTimeType : Integer
{
	Absolute = 0,
	Relative
};

enum class TElisaKineticReadingsFromType : Integer
{
	Begin = 0,
	End
};

class TElisaKineticParams
{
	public:
		__fastcall TElisaKineticParams() : mType(TElisaKineticType::AverageRate),
										   mRateType(TElisaKineticRateType::Seconds),
										   mChangeTimeType(TElisaKineticChangeTimeType::Absolute),
										   mReadingsFromType(TElisaKineticReadingsFromType::Begin) {}

		__fastcall TElisaKineticParams(const TElisaKineticParams& rhs)
		{
			*this = rhs;
		}

		__property TElisaKineticType Type = {read = mType, write = mType};
		__property TElisaKineticRateType RateType = {read = mRateType, write = mRateType};
		__property TElisaKineticWindowType WindowType = {read = mWindowType, write = mWindowType};
		__property TElisaKineticReactionType ReactionType = {read = mReactionType, write = mReactionType};
		__property TElisaKineticReadingsFromType ReadingsFromType = {read = mReadingsFromType, write = mReadingsFromType};
		__property TElisaKineticChangeTimeType ChangeTimeType = {read = mChangeTimeType, write = mChangeTimeType};
		__property Word BaselineReadings = {read = mBaselineReadings, write = mBaselineReadings};
		__property Single ChangeThreshold = {read = mChangeThreshold, write = mChangeThreshold};

		TElisaKineticParams& operator = (const TElisaKineticParams& rhs)
		{
			mType = rhs.mType;
			mRateType = rhs.mRateType;
			mWindowType = rhs.mWindowType;
			mReactionType = rhs.mReactionType;
			mReadingsFromType = rhs.mReadingsFromType;
			mChangeTimeType = rhs.mChangeTimeType;
			mBaselineReadings = rhs.mBaselineReadings;
			mChangeThreshold = rhs.mChangeThreshold;

			return (*this);
		}

		private:
			TElisaKineticType mType;
			TElisaKineticRateType mRateType;
			TElisaKineticWindowType mWindowType;
			TElisaKineticReactionType mReactionType;
			TElisaKineticReadingsFromType mReadingsFromType;
			TElisaKineticChangeTimeType mChangeTimeType;
			Word mBaselineReadings;
			Single mChangeThreshold;
};

class ElisaParams
{
	public:
		__fastcall ElisaParams() : mHasShake(False), mReadType(TElisaReadType::Normal),
								   mReadMode(TElisaReadMode::OneWaveLength),
								   mReadSpeed(TElisaReadSpeed::StandardSpeed),
								   mShakeIntensity(TElisaShakeIntensity::LowIntensity),
								   mShakeMode(TElisaShakeMode::ShakeFirst),
								   mIndexFilter1(-1), mIndexFilter2(-1), mIndexCalcMethod(0),
								   mPlateRows(8), mPlateCols(12) {}
		virtual __fastcall ~ElisaParams() {}

		__property TElisaReadType ReadType = {read = mReadType, write = mReadType};
		__property TElisaReadMode ReadMode = {read = mReadMode, write = mReadMode};
		__property TElisaReadSpeed ReadSpeed = {read = mReadSpeed, write = mReadSpeed};
		__property Boolean Shake = {read = mHasShake, write = mHasShake};
		__property TElisaShakeIntensity ShakeIntensity = {read = mShakeIntensity, write = mShakeIntensity};
		__property TElisaShakeMode ShakeMode = {read = mShakeMode, write = mShakeMode};
		__property TDateTime ShakeDuration = {read = mShakeDuration, write = mShakeDuration};
		__property Integer Filter1 = {read = mIndexFilter1, write = mIndexFilter1};
		__property Integer Filter2 = {read = mIndexFilter2, write = mIndexFilter2};
		__property Integer CalcMethod = {read = mIndexCalcMethod, write = mIndexCalcMethod};
		__property TElisaKineticParams KineticParams = {read = mKineticParams, write = mKineticParams};
		__property Integer PlateRows = {read = mPlateRows, write = mPlateRows};
		__property Integer PlateCols = {read = mPlateCols, write = mPlateCols};
		__property TDateTime WaitDuration = {read = mWaitDuration, write = mWaitDuration};

	private:
		__fastcall ElisaParams(const ElisaParams&) {}
		ElisaParams& operator = (ElisaParams const&) {return *this;}

	private:
		TElisaReadType mReadType;
		Boolean mHasShake;
		TElisaReadMode mReadMode;
		TElisaReadSpeed mReadSpeed;
		TElisaShakeIntensity mShakeIntensity;
		TElisaShakeMode mShakeMode;
		TDateTime mShakeDuration;
		TElisaKineticParams mKineticParams;

		Integer mIndexFilter1;
		Integer mIndexFilter2;
		Integer mIndexCalcMethod;
		Integer mPlateRows, mPlateCols;
		TDateTime mWaitDuration;

};

typedef SingletonPattern<ElisaParams> ElisaParamsSingleton;

//---------------------------------------------------------------------------
#endif
