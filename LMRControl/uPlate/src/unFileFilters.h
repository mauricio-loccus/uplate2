//---------------------------------------------------------------------------

#ifndef unFileFiltersH
#define unFileFiltersH

#include <System.Classes.hpp>

#include "Singleton.h"

#define DEF_FILTER1		"401"
#define DEF_FILTER2		"402"
#define DEF_FILTER3		"403"
#define DEF_FILTER4		"404"
#define DEF_FILTER5		""
#define DEF_FILTER6		""
#define DEF_FILTER7		""
#define DEF_FILTER8		""
#define DEF_QTD_FILTERS 4

class FileFilters : public TComponent
{
    public:
        __fastcall FileFilters(TComponent *owner = NULL);
        __fastcall ~FileFilters();

        void __fastcall Load();
        void __fastcall Save();

//		__property Boolean Version2023 = {read = mVersion2023, write = setVersion2023};

		void __fastcall setFilters(TStringList *f);
		void __fastcall getFilters(TStringList *f);

		int qtdFilterSet;

	private:
		String mFilter1;
		String mFilter2;
		String mFilter3;
		String mFilter4;
		String mFilter5;
		String mFilter6;
		String mFilter7;
		String mFilter8;

	private:
		void __fastcall saveConfig(String cfgFName);
        void __fastcall loadConfig(String cfgFName);
};

typedef FileFilters *PFileFilters;
typedef SingletonPattern<FileFilters> FileFiltersSingleton;
//---------------------------------------------------------------------------
#endif
