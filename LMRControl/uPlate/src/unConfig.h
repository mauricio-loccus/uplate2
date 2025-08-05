//---------------------------------------------------------------------------

#ifndef unConfigH
#define unConfigH

#include <System.Classes.hpp>

#include "Singleton.h"

class AppConfig : public TComponent
{
	public:
		__fastcall AppConfig(TComponent *owner = NULL);
		__fastcall ~AppConfig();

		void __fastcall Load();
		void __fastcall Save();

		__property WideChar ThousandSeparator = {read = mThousandSeparator};
		__property WideChar DecimalSeparator  = {read = mDecimalSeparator};
		__property System::Largeint UserID = {read = mUserID, write = setUserID};
		__property String UserLogin = {read = mUserLogin, write = setUserLogin};
		__property String UserName = {read = mUserName, write = setUserName};
		__property Boolean IsSuperUser = {read = mIsRoot, write = setIsRoot};
		__property String ProtocolUnity = {read = mProtoUnity, write = setProtocolUnity};
		__property Boolean HeadersInCsv = {read = mHeadersInCsv, write = setHeadersInCsv};
		__property Boolean ElisaSimulated = {read = mSimulatorActive, write = setSimulatorActive};
		__property Boolean Version2023 = {read = mVersion2023, write = setVersion2023};
		__property String DataDirectory = { read = mDataDirectory, write = mDataDirectory };


		void __fastcall setThousandSeparator(WideChar separator);
		void __fastcall setDecimalSeparator(WideChar separator);
		void __fastcall setUserID(System::Largeint userID);
		void __fastcall setUserLogin(String userLogin);
		void __fastcall setUserName(String userName);
		void __fastcall setIsRoot(Boolean isRoot);
		void __fastcall setProtocolUnity(const String& unity);
		void __fastcall setHeadersInCsv(Boolean set);
		void __fastcall setSimulatorActive(Boolean set);
		void __fastcall setVersion2023(Boolean set);

	private:
		WideChar mThousandSeparator;
		WideChar mDecimalSeparator;
		System::Largeint mUserID;
		String mUserLogin;
		String mUserName;
		Boolean mIsRoot;
		String mProtoUnity;
		Boolean mHeadersInCsv;
		Boolean mSimulatorActive;
		Boolean mVersion2023;
		String  mDataDirectory;

		String __fastcall GetDataDirectory();
		String __fastcall ExpandEnvironment(String);

		void __fastcall saveConfig(String cfgFName);
		void __fastcall loadConfig(String cfgFName);
};

typedef AppConfig *PAppConfig;
typedef SingletonPattern<AppConfig> AppConfigSingleton;
//---------------------------------------------------------------------------
#endif
