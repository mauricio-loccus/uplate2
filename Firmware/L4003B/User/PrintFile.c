
//2016-01-19 Modify
void CAS112_V10Dlg::PrintFile()
{
    //CFile  stuFile;
    //	CString  str2, strCSV, strDate, strTemp, strTemp2,strTemp1, strDst,StrNo;
    CString  str2, strTemp, strTemp2,strTemp1;
    int val;

    char* pChar = new char[800*1024];
    char* pCharConvert = new char[1024];
    char* pChar2 = new char[1024];

    //bool b1 = MY_Prn->GetWMPrintST();
    //Sleep(2000);
    //b1 = MY_Prn->GetWMPrintST();
    //if(!b1)
    //{
    //	MessageBoxOne(NOT_FIND_PRINTER[sys_para.wcLanguage]);
    //	return;
    //}

    MY_Prn->PrintConvert(0);
    MY_Prn->PrintRowDis(0);
    if(reportReady == 4)
    {
        //2015-3-16
        if(sys_para.wcLanguage == CHINESE)
        {
            // strTemp = _T("????:\n");
            //char *buff={"????:\n"};
            char *buff= {"????:"};
            //    strTemp = _T("?????:\n");
            MY_Prn->Print_CHAR(buff);
            delete [] buff;
        }
        else
        {
            strTemp = _T("Trasmission light intensity:");
            //	strTemp = "Trasmission light intensity:\n";
            UnicodeToAscii2((CStringA)strTemp, pChar);
            //stuFile.Write(pChar,strTemp.GetLength());
            MY_Prn->Print_CHAR(pChar);
        }
        //2015-3-16

        //strTemp = _T(" ");
        strTemp = " ";
        for(int i = 0; i < INT_DATA_MAX; i++)
        {
            strTemp1.Format(_T("%d"), i + 1);
            //strTemp1.Format("%d", i + 1);
            strTemp += strTemp1;
            if(i < INT_DATA_MAX - 1)
            {
                strTemp += _T(" ");
                //strTemp += " ";
            }
            else
            {
                strTemp += _T("\n");
                //	strTemp += "\n";
            }
        }

        for(int j = 0; j < SCAN_CHANNEL_MAX; j++)
        {
            for(int i = 0; i < INT_DATA_MAX + 1; i++) //2014-8-20?
            {
                if(i == 0)
                {
                    strTemp1.Format(_T("%c1"), 'A' + j);
                }
                else
                {
                    strTemp1.Format(_T("%d"), raw_data.nIntensity[i - 1][0][j]);
                }
                strTemp += strTemp1;
                if(i < INT_DATA_MAX)
                {
                    strTemp += _T(" ");
                }
                else
                {
                    strTemp += _T("\n");
                }
            }
        }

        UnicodeToAscii2((CStringA)strTemp, pChar);
        //stuFile.Write(pChar,strTemp.GetLength());
        MY_Prn->Print_CHAR(pChar);
        MY_Prn->Print_NextHx(0x05);   //?9?
        MY_Prn->Print_Enter_Next();
        MY_Prn->Print_Enter_Next();
        MY_Prn->Print_Enter_Next();
        MY_Prn->Print_Enter_Next();
    }
    else if(reportReady == 3)
    {
        if(sys_para.wcLanguage == CHINESE)
        {
            //    strTemp = _T("????:\n");
            char *buff= {"????:"};
            //    strTemp = _T("?????:\n");
            MY_Prn->Print_CHAR(buff);
            delete buff;
            buff = NULL;
        }
        else
        {
            strTemp = _T("Trasmission light intensity:");
            UnicodeToAscii2((CStringA)strTemp, pChar);
            //stuFile.Write(pChar,strTemp.GetLength());
            MY_Prn->Print_CHAR(pChar);
        }

        //	strTemp = _T("Trasmission light intensity:\n");
        //2015-3-16
        // if(sys_para.wcLanguage == CHINESE)
        //{
        //  strTemp = _T("????:\n");
        //}
        //2015-3-16
        strTemp = _T(" ");
        for(int i = 0; i < SCAN_DATA_MAX; i++)
        {
            strTemp1.Format(_T("%d"), i + 1);
            strTemp += strTemp1;
            if(i < SCAN_DATA_MAX - 1)
            {
                strTemp += _T(" ");
            }
            else
            {
                strTemp += _T("\n");
            }
        }

        for(int j = 0; j < SCAN_CHANNEL_MAX; j++)
        {
            for(int i = 0; i < SCAN_DATA_MAX + 1; i++) //2014-8-20?
            {
                if(i == 0)
                {
                    strTemp1.Format(_T("%c1"), 'A' + j);
                    strTemp1 += _T("     ");
                }
                else
                {
                    strTemp1.Format(_T("%d"), raw_data.nIntensity[j][0][i - 1]);
                }
                strTemp += strTemp1;
                if(i < SCAN_DATA_MAX)
                {
                    strTemp += _T(" ");
                }
                else
                {
                    strTemp += _T("\n");
                }
            }
        }

        UnicodeToAscii2((CStringA)strTemp, pChar);
        MY_Prn->Print_CHAR(pChar);
        //stuFile.Write(pChar,strTemp.GetLength());

        strTemp = _T("");
        for(int j = 0; j <SCAN_CHANNEL_MAX; j++)
        {
            for(int i = 0; i < SCAN_DATA_MAX + 1; i++) //2014-8-20?
            {
                if(i == 0)
                {
                    strTemp1.Format(_T("%c12"), 'A' + j);
                    strTemp1 += _T("     ");
                }
                else
                {
                    strTemp1.Format(_T("%d"), raw_data.nIntensity[j][1][i - 1]);
                }
                strTemp += strTemp1;
                if(i < SCAN_DATA_MAX)
                {
                    strTemp += _T(" ");
                }
                else
                {
                    strTemp += _T("\n");
                }
            }
        }

        //nMessageTestInfo = TEST_INFO_SCAN_DATA;
        UnicodeToAscii2((CStringA)strTemp, pChar);
        MY_Prn->Print_CHAR(pChar);
        //stuFile.Write(pChar,strTemp.GetLength());
        //stuFile.Close();
        MY_Prn->Print_NextHx(0x05);   //?5?
        MY_Prn->Print_Enter_Next();
        MY_Prn->Print_Enter_Next();
        MY_Prn->Print_Enter_Next();
        MY_Prn->Print_Enter_Next();
        //    delete [] pChar;
        //	delete [] pChar2;
        //delete [] pCharConvert;

        //delete [] strTemp;
        //delete strTemp;
        //delete strTemp1;
        //delete strTemp2;
        //delete str2;
        //return;
    }
    else if(maintenance_para.bIntensity && board_inf.bHasData)
    {
        if(sys_para.wcLanguage == CHINESE)
        {
            //    strTemp = _T("????:\n");
            char *buff= {"??????:"};
            //    strTemp = _T("?????:\n");
            MY_Prn->Print_CHAR(buff);
        }
        else
        {
            strTemp = _T("Incident light intensity:");
            UnicodeToAscii2((CStringA)strTemp, pChar);
            //stuFile.Write(pChar,strTemp.GetLength());
            MY_Prn->Print_CHAR(pChar);
        }
        //strTemp = _T("Incident light intensity:\n");
        //2015-3-16
        //    if(sys_para.wcLanguage == CHINESE)
        //    {
        //    strTemp = _T("??????:\n");
        //   }
        //2015-3-16
        //	for(int i = 0; i < 8; i++)
        strTemp = _T(" ");
        //for(int i = 0; i < CHANNEL_MAX; i++)//2015-09-08
        for(int i = 0; i < SCAN_CHANNEL_MAX; i++)//2016-2-25
        {
            strTemp1.Format(_T("%d"), raw_data.nInputIntensity[0][i]);
            strTemp += strTemp1;
            if(i < 7)
            {
                strTemp += _T(" ");
            }
            else
            {
                strTemp += _T("\n");
            }
        }
        UnicodeToAscii2((CStringA)strTemp, pChar);
        MY_Prn->Print_CHAR(pChar);

        if(sys_para.wcLanguage == CHINESE)
        {
            //    strTemp = _T("????:\n");
            char *buff= {"??????:"};
            //    strTemp = _T("?????:\n");
            MY_Prn->Print_CHAR(buff);
            delete buff;
        }
        else
        {
            strTemp = _T("Background light intensity:");
            UnicodeToAscii2((CStringA)strTemp, pChar);
            //stuFile.Write(pChar,strTemp.GetLength());
            MY_Prn->Print_CHAR(pChar);
        }
        //strTemp += _T("Background light intensity:\n");
        //2015-3-16
        //   if(sys_para.wcLanguage == CHINESE)
        //  {
        //    strTemp += _T("??????:\n");
        //  }
        //2015-3-16
        strTemp = _T(" ");
        for(int i = 0; i < 8; i++)
        {
            strTemp1.Format(_T("%d"), raw_data.nBackgroundIntensity[0][i]);
            strTemp += strTemp1;
            if(i < 7)
            {
                strTemp += _T(" ");
            }
            else
            {
                strTemp += _T("\n");
            }
        }
        UnicodeToAscii2((CStringA)strTemp, pChar);
        MY_Prn->Print_CHAR(pChar);

        //stuFile.Write(pChar,strTemp.GetLength());
        if(sys_para.wcLanguage == CHINESE)
        {
            //    strTemp = _T("????:\n");
            char *buff= {"????:"};
            //    strTemp = _T("?????:\n");
            MY_Prn->Print_CHAR(buff);
            delete buff;
        }
        else
        {
            strTemp = _T("Trasmission light intensity:");
            UnicodeToAscii2((CStringA)strTemp, pChar);
            //stuFile.Write(pChar,strTemp.GetLength());
            MY_Prn->Print_CHAR(pChar);
        }
        //strTemp = _T("Trasmission light intensity:\n");
        //2015-3-16
        //   if(sys_para.wcLanguage == CHINESE)
        //   {
        //    strTemp = _T("????:\n");
        //  }
        //2015-3-16

        strTemp2 = _T("  ");//"A "
        //2015-2-13
        for(int i = 0; i < 12; i++)
        {
            if(i < 9)
            {
                strTemp2 += _T("  ");
            }
            else// if(i < 11)
            {
                strTemp2 += _T(" ");
            }
            strTemp1.Format(_T("%d"), i + 1);
            strTemp2 += strTemp1;
            strTemp2 += _T("  ");

            if(i < 11)
            {
                strTemp2 += _T(" ");
            }
            //	else
            //	{
            //	strTemp2 += _T(" \n");
            //	}
        }


        for(int j = 0; j < 8; j++)
        {
            for(int i = 0; i < 13; i++) //2014-8-20?
            {
                if(i == 0)
                {
                    strTemp1.Format(_T("%c"), 'A' + j);
                    // strTemp2 += strTemp1;
                    //strTemp2 += _T(" ");
                    //continue;
                }
                else
                {
                    val=raw_data.nIntensity[0][normal_analysis.wcFilterCurrent][j * 12 + i - 1];
                    val=val/100;
                    strTemp1.Format(_T("%5d"), val);
                    //strTemp1.Format(_T("%d5"), raw_data.nIntensity[0][normal_analysis.wcFilterCurrent][j * 12 + i - 1]/100);
                }
                strTemp2 += strTemp1;
                if(i < 12)
                {
                    strTemp2 += _T(" ");
                }

                // else
                //{
                //  strTemp += _T("\n");
                //}
            }
        }
        ConvertRowCol((CStringA)strTemp2, pCharConvert);
        strTemp= _T("");
        for(int i3 = 0; i3 < 73*11; i3++)
        {
            //pChar[i] = (char)(str.GetAt(i));
            strTemp+=pCharConvert[i3];

        }


        MY_Prn->PrintConvert(1);
        MY_Prn->PrintRowDis(1);

        UnicodeToAscii2((CStringA)strTemp, pChar);
        MY_Prn->Print_CHAR(pChar);
        MY_Prn->PrintConvert(0);
        MY_Prn->PrintRowDis(0);

        //	MY_Prn->Print_CHAR(pChar);
        MY_Prn->Print_NextHx(0x05);   //?5?
        MY_Prn->Print_Enter_Next();
        MY_Prn->Print_Enter_Next();
        MY_Prn->Print_Enter_Next();
        MY_Prn->Print_Enter_Next();
        //  delete [] pChar;
        //delete [] pChar2;
        //	delete [] pCharConvert;

        //delete [] strTemp;
        //	delete strTemp;
        //delete strTemp1;
        //delete strTemp2;
        //delete str2;
        //stuFile.Write(pChar,strTemp.GetLength());
        //stuFile.Close();
    }
    else if(normal_analysis.wcMode == ANALYSIS_MODE_RAWDATA && board_inf.bHasData)
    {
        //2015-3-16
        if(sys_para.wcLanguage == CHINESE)
        {
            char *buff= {"????:"};
            //    strTemp = _T("?????:\n");
            MY_Prn->Print_CHAR(buff);
            delete buff;
        }
        else
        {
            //strTemp = _T("Absorbance data:\n");
            strTemp = _T("Raw data:");
            //UnicodeToAscii(strTemp, pChar);
            UnicodeToAscii2((CStringA)strTemp, pChar);
            MY_Prn->Print_CHAR(pChar);
        }
        //2015-3-16
        if(sys_para.wcLanguage == CHINESE)
        {
            //for(i=0;i<2048;i++)MainBuff[i]=0;
            if(normal_analysis.wcFilterCurrent == 0)
            {
                char *buff1= {"???1:"};
                MY_Prn->Print_ZHAdd(buff1,0);	// ??? 0 ???
                CStringA str;
                str =  CStringA(filterLun.filter[board_inf.Filter1_locate]);
                str += "@@";
                //char *buff2;//=str;
                //	buff2=&str[0];
                //={"      "};
                //buff2=str;
                //strTemp += _T("\n");
                UnicodeToAscii2((CStringA)str, pChar2);
                MY_Prn->Print_ZHAdd(pChar2,1);	// ??? 0 ???
                MY_Prn->Print_CHAR(MY_Prn->MainBuff);
                delete buff1;
                // delete buff2;
            }
            else if(normal_analysis.wcFilterCurrent == 1)
            {
                // memset(MainBuff,0x00,2048);
                char *buff1= {"???2:"};
                MY_Prn->Print_ZHAdd(buff1,0);	// ??? 0 ???

                CStringA str;
                str=  CStringA(filterLun.filter[board_inf.Filter2_locate]);
                str += "@@";
                //    char *buff2;//={"      "};
                //    buff2=&str;
                //strTemp += _T("\n");
                UnicodeToAscii2((CStringA)str, pChar2);
                MY_Prn->Print_ZHAdd(pChar2,1);	// ??? 0 ???
                MY_Prn->Print_CHAR(MY_Prn->MainBuff);
                delete buff1;
                // delete buff2;

            }
            else
            {
                char *buff1= {"???1&2:"};
                MY_Prn->Print_ZHAdd(buff1,0);	// ??? 0 ???

                CStringA str;
                str =  CStringA(board_inf.preCalculate);
                str += "@@";
                //	char *buff2;//={"      "};
                //buff2=&str;
                //strTemp += _T("\n");
                UnicodeToAscii2((CStringA)str,pChar2);
                MY_Prn->Print_ZHAdd(pChar2,1);	// ??? 0 ???
                MY_Prn->Print_CHAR(MY_Prn->MainBuff);
                delete buff1;
                // delete buff2;
            }
            // Sleep(200);
        }
        else
        {
            if(normal_analysis.wcFilterCurrent == 0)
            {
                strTemp = (CString(_T("Filter 1: ")) + CString(filterLun.filter[board_inf.Filter1_locate]));
            }
            else if(normal_analysis.wcFilterCurrent == 1)
            {
                strTemp = (CString(_T("Filter 2: ")) + CString(filterLun.filter[board_inf.Filter2_locate]));
            }
            else
            {
                strTemp = (CString(_T("Filter 1&2: ")) + CString(board_inf.preCalculate));
            }
            //strTemp += _T("\n");
            UnicodeToAscii2((CStringA)strTemp, pChar);
            MY_Prn->Print_CHAR(pChar);
        }

        int max_cyc;
        max_cyc=1;
        if(board_inf.curentKinetic[0] == _T('O'))
        {
            //	max_cyc = kinetic_para.kinetic_readings;
            max_cyc=board_inf.kinetic_para.kinetic_readings_practical;
        }

        else if(normal_analysis.wcFilterCurrent == 1)
        {
            // memset(MainBuff,0x00,2048);
            char *buff1= {"???:"};
            MY_Prn->Print_ZHAdd(buff1,0);	// ??? 0 ???

            strTemp1.Format(_T("%d"), (max_cyc));

            UnicodeToAscii2((CStringA)strTemp1, pChar2);
            MY_Prn->Print_ZHAdd(pChar2,1);	// ??? 0 ???
            MY_Prn->Print_CHAR(MY_Prn->MainBuff);
            delete buff1;
            // delete buff2;

        }
        else
        {
            strTemp1.Format(_T("%d"), (max_cyc));
            strTemp =_T("Readings:      ") +strTemp1;
            // strTemp += _T("\n");
            UnicodeToAscii2((CStringA)strTemp, pChar);
            MY_Prn->Print_CHAR(pChar);
        }


        //strTemp= _T("\n");
        strTemp= _T("");
        //max_cyc=1;
        for(int k=0; k<max_cyc; k++)
        {
            /*  if(sys_para.wcLanguage == CHINESE)
            {
            char *buff1={"??: "};
            MY_Prn->Print_ZHAdd(buff1,0);	// ??? 0 ???

            CStringA str;
            str.Format("%d", (k+1));
            //   strTemp1.Format(_T("%d"), (k+1));
            // strTemp = strTemp1;
            char *buff2;
            UnicodeToAscii2((CStringA)str, buff2);
            // buff2=str;
            MY_Prn->Print_ZHAdd(buff2,1);	// ??? 0 ???
            //CStringA str;
            //strTemp += _T("\n");
            //UnicodeToAscii2((CStringA)str, buff2);

            // strTemp += _T("\n");
            //   UnicodeToAscii2((CStringA)strTemp, pChar2);
            //  MY_Prn->Print_ZHAdd(pChar2,1);	// ??? 0 ???
            MY_Prn->Print_CHAR(MY_Prn->MainBuff);
            delete buff1;
            }
            else
            {*/
            //  strTemp1.Format(_T("%d"), (k+1));
            //strTemp +=_T("readings: ") +strTemp1;
            // strTemp += _T("\n");
            //UnicodeToAscii2((CStringA)strTemp, pChar);
            //MY_Prn->Print_CHAR(pChar);
            // }

            // strTemp = _T("");//
            //strTemp="";
            strTemp2 = _T("  ");//"A "
            for(int i = 0; i < 12; i++)
            {
                if(i < 9)
                {
                    strTemp2 += _T("  ");
                }
                else// if(i < 11)
                {
                    strTemp2 += _T(" ");
                }
                strTemp1.Format(_T("%d"), i + 1);
                strTemp2 += strTemp1;
                strTemp2 += _T("  ");

                if(i < 11)
                {
                    strTemp2 += _T(" ");
                }
            }


            for(int j = 0; j < 8; j++)
            {
                for(int i = 0; i < 13; i++) //2014-8-20?
                {
                    if(i == 0)
                    {
                        strTemp1.Format(_T("%c"), 'A' + j);
                        strTemp2 += strTemp1;
                        strTemp2 += _T(" ");
                        continue;
                    }
                    double dTemp;
                    bool bHasResult = true;

                    int nCycle = 0;            //No use
                    if(board_inf.curentKinetic[0] == _T('O'))  //No use
                    {   //No use
                        nCycle = board_inf.kinetic_para.kinetic_reading_current;  //kinetic_para.kinetic_readings  //No use
                    }  //No use

                    if(normal_analysis.wcFilterCurrent < 2)
                    {
                        //   dTemp = dABS[nCycle][normal_analysis.wcFilterCurrent][j * 12 + i - 1];
                        dTemp = dABS[k][normal_analysis.wcFilterCurrent][j * 12 + i - 1];
                    }
                    else if(normal_analysis.bPreCalOK[k][j * 12 + i - 1])
                    {
                        dTemp = normal_analysis.dPreCal[k][j * 12 + i - 1];
                    }
                    else
                    {
                        bHasResult = false;
                    }

                    if(bHasResult)
                    {
                        //2016-02-16
                        if( dTemp<0)strTemp1.Format(_T("%1.2f"), dTemp);
                        else strTemp1.Format(_T("%1.3f"), dTemp);
                    }
                    else
                    {
                        strTemp1 = _T(" N.A.");
                    }

                    CString strType = CString(board_inf.layout[j * 12 + i].Type);
                    strType = strType.Left(2);
                    if(strType != _T("BK") && strType != _T("SD") && strType != _T("QC")
                            && strType != _T("UD") && strType != _T("NC") && strType != _T("PC")) //?????
                    {
                        strTemp1 = _T("   EP");
                    }
                    strTemp2 += strTemp1;
                    if(i < 12)
                    {
                        strTemp2 += _T(" ");
                    }
                }// for(int j = 0; j < 9; j++)
            }//  for(int i = 0; i < 12; i++) //2014-8-20?

            ConvertRowCol((CStringA)strTemp2, pCharConvert);


            for(int i3 = 0; i3 < 73*11; i3++)
            {
                strTemp+=pCharConvert[i3];
            }
            strTemp += _T("\n");
            strTemp += _T("\n");
        }
        MY_Prn->PrintConvert(1);
        MY_Prn->PrintRowDis(1);

        UnicodeToAscii2((CStringA)strTemp, pChar);
        //MY_Prn->PrintConvert(0);
        // MY_Prn->PrintRowDis(0);
        MY_Prn->Print_CHAR(pChar);
        MY_Prn->PrintConvert(0);
        MY_Prn->PrintRowDis(0);

        //MY_Prn->Print_CHAR(pChar);
        MY_Prn->Print_NextHx(0x05);   //?5?
        MY_Prn->Print_Enter_Next();
        MY_Prn->Print_Enter_Next();
        MY_Prn->Print_Enter_Next();
        MY_Prn->Print_Enter_Next();
        //stuFile.Write(pChar,strTemp.GetLength());
        //stuFile.Close();
        //  delete [] pChar;
        //delete [] pChar2;
        //	delete [] pCharConvert;

        //delete [] strTemp;
        //	delete strTemp;
        //	delete strTemp1;
        //delete strTemp2;
        //delete str2;
    }
    else if(normal_analysis.wcMode == ANALYSIS_MODE_ANALYSIS && board_inf.bHasData && board_inf.curentKinetic[0] == _T('O'))
    {
        //char *buff={"?????:\n"};
        //strTemp = CString(KINETIC_ANALYSIS_SELECTION[0][sys_para.wcLanguage][board_inf.kinetic_para.kinetic_analysis_mode]) + _T(" ")
        //+ CString(KINETIC_ANALYSIS_SELECTION[1][sys_para.wcLanguage][board_inf.kinetic_para.kinetic_analysis_mode]) + _T("\n");

        //	char * buff = new char[1024];
        //   memset(buff,0x00,1024);


        //char *buff
        if(sys_para.wcLanguage == CHINESE)
            //	if(sys_para.wcLanguage==1)
        {
            if(board_inf.kinetic_para.kinetic_analysis_mode==0)
            {
                char *buff= {"????"};
                MY_Prn->Print_CHAR(buff);
                delete buff;
            }
            else if(board_inf.kinetic_para.kinetic_analysis_mode==1)
            {
                char *buff= {"????"};
                MY_Prn->Print_CHAR(buff);
                delete buff;
            }
            else if(board_inf.kinetic_para.kinetic_analysis_mode==2)
            {
                char *buff= {"????"};
                MY_Prn->Print_CHAR(buff);
                delete buff;
            }
            else if(board_inf.kinetic_para.kinetic_analysis_mode=3)
            {
                char *buff= {"????"};
                MY_Prn->Print_CHAR(buff);
                delete buff;
            }
            else if(board_inf.kinetic_para.kinetic_analysis_mode==4)
            {
                char *buff= {"?????"};
                MY_Prn->Print_CHAR(buff);
                delete buff;
            }
            else if(board_inf.kinetic_para.kinetic_analysis_mode==5)
            {
                char *buff= {"???????"};
                MY_Prn->Print_CHAR(buff);
                delete buff;
            }

            //     , {_T("??"), _T("??"), _T("????"), _T("??"), _T("??"), _T("?????")}
            //  char *buff= KINETIC_ANALYSIS_SELECTION_CHAR[0][sys_para.wcLanguage][board_inf.kinetic_para.kinetic_analysis_mode];

            //	 +  LPCSTR(" ")+ LPCSTR(KINETIC_ANALYSIS_SELECTION[1][0][board_inf.kinetic_para.kinetic_analysis_mode]) +  LPCSTR("\n")};
            //    MY_Prn->Print_CHAR(buff);
        }
        else
        {
            strTemp = CString(KINETIC_ANALYSIS_SELECTION[0][sys_para.wcLanguage][board_inf.kinetic_para.kinetic_analysis_mode]) + _T(" ")
                      + CString(KINETIC_ANALYSIS_SELECTION[1][sys_para.wcLanguage][board_inf.kinetic_para.kinetic_analysis_mode]) ;
            UnicodeToAscii2((CStringA)strTemp, pChar);
            MY_Prn->Print_CHAR(pChar);
        }
        if(sys_para.wcLanguage == CHINESE)
        {
            if(normal_analysis.wcFilterCurrent == 0)
            {
                char *buff1= {"???1:"};
                MY_Prn->Print_ZHAdd(buff1,0);	// ??? 0 ???
                strTemp =  CString(filterLun.filter[board_inf.Filter1_locate]);
                strTemp += "@@";
                //strTemp += _T("\n");
                UnicodeToAscii2((CStringA)strTemp, pChar2);
                MY_Prn->Print_ZHAdd(pChar2,1);	// ??? 0 ???
                MY_Prn->Print_CHAR(MY_Prn->MainBuff);
                delete buff1;
            }
            else if(normal_analysis.wcFilterCurrent == 1)
            {
                char *buff1= {"???2:"};
                MY_Prn->Print_ZHAdd(buff1,0);	// ??? 0 ???

                strTemp =  CString(filterLun.filter[board_inf.Filter2_locate]);
                strTemp += "@@";
                //  	strTemp += _T("\n");
                UnicodeToAscii2((CStringA)strTemp, pChar2);
                MY_Prn->Print_ZHAdd(pChar2,1);	// ??? 0 ???
                MY_Prn->Print_CHAR(MY_Prn->MainBuff);
                delete buff1;

            }
            else
            {
                char *buff1= {"???1&2:"};
                MY_Prn->Print_ZHAdd(buff1,0);	// ??? 0 ???

                strTemp =  CString(board_inf.preCalculate);
                strTemp += "@@";
                // strTemp += _T("\n");
                UnicodeToAscii2((CStringA)strTemp, pChar2);
                MY_Prn->Print_ZHAdd(pChar2,1);	// ??? 0 ???
                MY_Prn->Print_CHAR(MY_Prn->MainBuff);
                delete buff1;
            }
            //	Sleep(200);
        }
        else
        {
            if(normal_analysis.wcFilterCurrent == 0)
            {
                strTemp = (CString(_T("Filter 1: ")) + CString(filterLun.filter[board_inf.Filter1_locate]));
            }
            else if(normal_analysis.wcFilterCurrent == 1)
            {
                strTemp = (CString(_T("Filter 2: ")) + CString(filterLun.filter[board_inf.Filter2_locate]));
            }
            else
            {
                strTemp = (CString(_T("Filter 1&2: ")) + CString(board_inf.preCalculate));
            }
            //	strTemp += _T("\n");
            UnicodeToAscii2((CStringA)strTemp, pChar);
            MY_Prn->Print_CHAR(pChar);
        }
        //strTemp = CString(KINETIC_ANALYSIS_SELECTION[0][0][board_inf.kinetic_para.kinetic_analysis_mode]) + _T(" ")
        //	+ CString(KINETIC_ANALYSIS_SELECTION[1][0][board_inf.kinetic_para.kinetic_analysis_mode]) + _T("\n");
        //2015-2-13
        //if(normal_analysis.wcFilterCurrent == 0)
        //	{
        //		strTemp += (CString(_T("Filter 1: ")) + CString(filterLun.filter[board_inf.Filter1_locate]));
        ////	}
        //else if(normal_analysis.wcFilterCurrent == 1)
        //{
        //    strTemp += (CString(_T("Filter 2: ")) + CString(filterLun.filter[board_inf.Filter2_locate]));
        //}
        //	else
        //{
        //    strTemp += (CString(_T("Filter 1&2: ")) + CString(board_inf.preCalculate));
        //	}
        //	strTemp += _T("\n");
        /*        strTemp = _T(" ");//
        //2015-2-13

        for(int i = 0; i < 8; i++)
        //for(int i = 0; i < 12; i++)
        {
        strTemp1.Format(_T("%c"), 'A'+ i);
        strTemp += strTemp1;
        if(i < 7)
        {
        strTemp += _T("     ");
        }
        else
        {
        strTemp += _T("\n");
        }
        }


        */


        strTemp2 = _T("  ");//"A "
        //2015-2-13
        for(int i = 0; i < 12; i++)
        {
            if(i < 9)
            {
                strTemp2 += _T("  ");
            }
            else// if(i < 11)
            {
                strTemp2 += _T(" ");
            }
            strTemp1.Format(_T("%d"), i + 1);
            strTemp2 += strTemp1;
            strTemp2 += _T("  ");

            if(i < 11)
            {
                strTemp2 += _T(" ");
            }
            //	else
            //	{
            //	strTemp2 += _T(" \n");
            //	}
        }
        // for(int i = 0; i < 12; i++) //2014-8-20?
        //   {
        //    for(int j = 0; j < 9; j++)
        for(int j = 0; j < 8; j++)
        {
            for(int i = 0; i < 13; i++) //2014-8-20?
            {
                if(i == 0)
                {
                    strTemp1.Format(_T("%c"), 'A' + j);
                    strTemp2 += strTemp1;
                    strTemp2 += _T(" ");
                    continue;
                }
                /*	if(j == 0)
                {
                strTemp1.Format(_T("%d"), (i+1));
                //	strTemp +=_T("readings: ") +strTemp1;
                strTemp +=strTemp1;
                strTemp += _T("\n");
                //   strTemp1.Format(_T("%c"), 'A' + j);
                continue;
                }*/
                //if(j == 0)
                //{
                // strTemp1.Format(_T("%c"), 'A' + j);
                //strTemp += strTemp1;
                //	strTemp += _T(", ");
                //	continue;
                //	}
                double dTemp;
                bool bHasResult = true;
                if(board_inf.kinetic_para.kinetic_analysis_mode == KINETIC_ANALYSIS_AVERAGE_RATE)
                {
                    if(normal_analysis.wcFilterCurrent < 2)
                    {
                        dTemp = board_inf.kinetic_para.kinetic_average_rate[normal_analysis.wcFilterCurrent].dAverageRate[j * 12 + i - 1];
                    }
                    else if(board_inf.kinetic_para.bPreCalOK[j * 12 + i - 1])
                    {
                        dTemp = board_inf.kinetic_para.kinetic_average_rate[normal_analysis.wcFilterCurrent].dAverageRate[j * 12 + i - 1];
                    }
                    else
                    {
                        bHasResult = false;
                    }

                }
                if(board_inf.kinetic_para.kinetic_analysis_mode == KINETIC_ANALYSIS_MAX_RATE)
                {
                    if(normal_analysis.wcFilterCurrent < 2)
                    {
                        dTemp = board_inf.kinetic_para.kinetic_max_rate[normal_analysis.wcFilterCurrent].dMaxRate[j * 12 + i - 1];
                    }
                    else if(board_inf.kinetic_para.bPreCalOK[j * 12 + i - 1])
                    {
                        dTemp = board_inf.kinetic_para.kinetic_max_rate[normal_analysis.wcFilterCurrent].dMaxRate[j * 12 + i - 1];
                    }
                    else
                    {
                        bHasResult = false;
                    }

                }
                if(board_inf.kinetic_para.kinetic_analysis_mode == KINETIC_ANALYSIS_MAX_WELL)
                {
                    if(normal_analysis.wcFilterCurrent < 2)
                    {
                        dTemp = board_inf.kinetic_para.kinetic_max_well[normal_analysis.wcFilterCurrent].dMaxWell[j * 12 + i - 1];
                    }
                    else if(board_inf.kinetic_para.bPreCalOK[j * 12 + i - 1])
                    {
                        dTemp = board_inf.kinetic_para.kinetic_max_well[normal_analysis.wcFilterCurrent].dMaxWell[j * 12 + i - 1];
                    }
                    else
                    {
                        bHasResult = false;
                    }

                }
                if(board_inf.kinetic_para.kinetic_analysis_mode == KINETIC_ANALYSIS_TIME_MAX_RATE)
                {
                    if(normal_analysis.wcFilterCurrent < 2)
                    {
                        dTemp = board_inf.kinetic_para.kinetic_time_max_rate[normal_analysis.wcFilterCurrent].nTime[j * 12 + i - 1];
                    }
                    else if(board_inf.kinetic_para.bPreCalOK[j * 12 + i - 1])
                    {
                        dTemp = board_inf.kinetic_para.kinetic_time_max_rate[normal_analysis.wcFilterCurrent].nTime[j * 12 + i - 1];
                    }
                    else
                    {
                        bHasResult = false;
                    }

                }
                if(board_inf.kinetic_para.kinetic_analysis_mode == KINETIC_ANALYSIS_TIME_MAX)
                {
                    if(normal_analysis.wcFilterCurrent < 2)
                    {
                        dTemp = board_inf.kinetic_para.kinetic_time_max[normal_analysis.wcFilterCurrent].nTime[j * 12 + i - 1];
                    }
                    else if(board_inf.kinetic_para.bPreCalOK[j * 12 + i - 1])
                    {
                        dTemp = board_inf.kinetic_para.kinetic_time_max[normal_analysis.wcFilterCurrent].nTime[j * 12 + i - 1];
                    }
                    else
                    {
                        bHasResult = false;
                    }
                }

                if(board_inf.kinetic_para.kinetic_analysis_mode == KINETIC_ANALYSIS_TIME_CHANGE)
                {
                    if(normal_analysis.wcFilterCurrent < 2)
                    {
                        dTemp = board_inf.kinetic_para.kinetic_time_change[normal_analysis.wcFilterCurrent].nTime[j * 12 + i - 1];
                        bHasResult = board_inf.kinetic_para.kinetic_time_change[normal_analysis.wcFilterCurrent].bOK[j * 12 + i - 1];
                    }
                    else if(board_inf.kinetic_para.bPreCalOK[j * 12 + i - 1])
                    {
                        dTemp = board_inf.kinetic_para.kinetic_time_change[normal_analysis.wcFilterCurrent].nTime[j * 12 + i - 1];
                        bHasResult = board_inf.kinetic_para.kinetic_time_change[normal_analysis.wcFilterCurrent].bOK[j * 12 + i - 1];
                    }
                    else
                    {
                        bHasResult = false;
                    }

                }

                if(bHasResult)
                {
                    //2016-02-16
                    if(dTemp<0)strTemp1.Format(_T("%1.2f"), dTemp);
                    else strTemp1.Format(_T("%1.3f"), dTemp);

                }
                else
                {
                    strTemp1 = _T(" N.A.");
                }
                CString strType = CString(board_inf.layout[j * 12 + i].Type);
                strType = strType.Left(2);
                if(strType != _T("BK") && strType != _T("SD") && strType != _T("QC")
                        && strType != _T("UD") && strType != _T("NC") && strType != _T("PC")) //?????
                {
                    strTemp1 = _T("   EP");
                }
                strTemp2 += strTemp1;
                if(i < 12)
                {
                    strTemp2 += _T(" ");
                }
                //  else
                //	    {
                //   strTemp2 += _T("\n");
                //	    }
            }
        }
        ConvertRowCol((CStringA)strTemp2, pCharConvert);


        strTemp= _T("");
        for(int i3 = 0; i3 < 73*11; i3++)
        {
            //pChar[i] = (char)(str.GetAt(i));
            strTemp+=pCharConvert[i3];

        }


        //   BYTE WMFormat1[3] = {0x1c,0x49,3};
        //int  WMfLen = 3;
        //  PRINT_MY_CMD((char *)WMFormat1,3);
        MY_Prn->PrintConvert(1);
        MY_Prn->PrintRowDis(1);

        UnicodeToAscii2((CStringA)strTemp, pChar);
        MY_Prn->Print_CHAR(pChar);
        MY_Prn->PrintConvert(0);
        MY_Prn->PrintRowDis(0);
        //  WMFormat1[2] =0;
        //  PRINT_MY_CMD((char *)WMFormat1,3);
        // delete[] WMFormat1;

        MY_Prn->Print_NextHx(0x05);   //?5?
        MY_Prn->Print_Enter_Next();
        MY_Prn->Print_Enter_Next();
        MY_Prn->Print_Enter_Next();
        MY_Prn->Print_Enter_Next();

        // delete [] pChar;
        //delete [] pChar2;
        //	stuFile.Write(pChar,strTemp.GetLength());
        //stuFile.Close();
    }
    else if(normal_analysis.wcMode == ANALYSIS_MODE_ANALYSIS && board_inf.bHasData)
    {
        //2015-3-16
        if(sys_para.wcLanguage == CHINESE)
        {
            char *buff= {"????"};
            MY_Prn->Print_CHAR(buff);
            delete buff;
        }
        else
        {
            strTemp = _T("Concentration");
            UnicodeToAscii2((CStringA)strTemp, pChar);
            MY_Prn->Print_CHAR(pChar);
        }
        if(sys_para.wcLanguage == CHINESE)
        {
            if(normal_analysis.wcFilterCurrent == 0)
            {
                char *buff1= {"???1:"};
                MY_Prn->Print_ZHAdd(buff1,0);	// ??? 0 ???
                strTemp =  CString(filterLun.filter[board_inf.Filter1_locate]);
                strTemp += "@@";
                //strTemp += _T("\n");
                UnicodeToAscii2((CStringA)strTemp, pChar2);
                MY_Prn->Print_ZHAdd(pChar2,1);	// ??? 0 ???
                MY_Prn->Print_CHAR(MY_Prn->MainBuff);
                delete buff1;
            }
            else if(normal_analysis.wcFilterCurrent == 1)
            {
                char *buff1= {"???2:"};
                MY_Prn->Print_ZHAdd(buff1,0);	// ??? 0 ???

                strTemp =  CString(filterLun.filter[board_inf.Filter2_locate]);
                strTemp += "@@";
                //	   	strTemp += _T("\n");
                UnicodeToAscii2((CStringA)strTemp, pChar2);
                MY_Prn->Print_ZHAdd(pChar2,1);	// ??? 0 ???
                MY_Prn->Print_CHAR(MY_Prn->MainBuff);
                delete buff1;

            }
            else
            {
                char *buff1= {"???1&2:"};
                MY_Prn->Print_ZHAdd(buff1,0);	// ??? 0 ???

                strTemp =  CString(board_inf.preCalculate);
                strTemp += "@@";
                //	 strTemp += _T("\n");
                UnicodeToAscii2((CStringA)strTemp, pChar2);
                MY_Prn->Print_ZHAdd(pChar2,1);	// ??? 0 ???
                MY_Prn->Print_CHAR(MY_Prn->MainBuff);
                delete buff1;
            }
            //	Sleep(200);
        }
        else
        {
            if(normal_analysis.wcFilterCurrent == 0)
            {
                strTemp = (CString(_T("Filter 1: ")) + CString(filterLun.filter[board_inf.Filter1_locate]));
            }
            else if(normal_analysis.wcFilterCurrent == 1)
            {
                strTemp = (CString(_T("Filter 2: ")) + CString(filterLun.filter[board_inf.Filter2_locate]));
            }
            else
            {
                strTemp = (CString(_T("Filter 1&2: ")) + CString(board_inf.preCalculate));
            }
            //strTemp += _T("\n");
            UnicodeToAscii2((CStringA)strTemp, pChar);
            MY_Prn->Print_CHAR(pChar);

        }
        //2015-3-16
        //2015-2-13
        //if(normal_analysis.wcFilterCurrent == 0)
        //	{
        //	strTemp += (CString(_T("Filter 1: ")) + CString(filterLun.filter[board_inf.Filter1_locate]));
        //	}
        //else if(normal_analysis.wcFilterCurrent == 1)
        //{
        //    strTemp += (CString(_T("Filter 2: ")) + CString(filterLun.filter[board_inf.Filter2_locate]));
        //	}
        //else
        //{
        //   strTemp += (CString(_T("Filter 1&2: ")) + CString(board_inf.preCalculate));
        //	}
        //	strTemp += _T("\n");
        strTemp2 = _T("  ");//"A "
        //2015-2-13
        for(int i = 0; i < 12; i++)
        {
            if(i < 9)
            {
                strTemp2 += _T("  ");
            }
            else// if(i < 11)
            {
                strTemp2 += _T(" ");
            }
            strTemp1.Format(_T("%d"), i + 1);
            strTemp2 += strTemp1;
            strTemp2 += _T("  ");

            if(i < 11)
            {
                strTemp2 += _T(" ");
            }
            //	else
            //	{
            //	strTemp2 += _T(" \n");
            //	}
        }

        //2015-2-13
        /*for(int i = 0; i < 12; i++)
        {
        strTemp1.Format(_T("%d"), i + 1);
        strTemp += strTemp1;
        if(i < 11)
        {
        strTemp += _T(", ");
        }
        else
        {
        strTemp += _T("\n");
        }
        }*/

        for(int j = 0; j < 8; j++)
        {
            for(int i = 0; i < 13; i++) //2014-8-20?
            {
                if(i == 0)
                {
                    strTemp1.Format(_T("%c"), 'A' + j);
                    strTemp2 += strTemp1;
                    strTemp2 += _T(" ");
                    continue;
                }

                double dTemp;
                bool bHasResult = true;
                dTemp = normal_analysis.dConcentration[normal_analysis.wcFilterCurrent][j * 12 + i -1 ];
                if(dTemp < 0.0)
                {
                    bHasResult = false;
                }

                if(bHasResult)
                {
                    //   strTemp1.Format(_T("%1.3f"), dTemp);
                    //2016-02-16
                    if(dTemp>=999)dTemp=999;//2016-02-16
                    else if(dTemp<=-99)dTemp=-99;
                    //	if(dTemp>=1000)strTemp1.Format(_T("%.f"), dTemp);///
                    if(dTemp>=100)strTemp1.Format(_T("%.1f"), dTemp);
                    else if(dTemp>=10)strTemp1.Format(_T("%.2f"), dTemp);
                    //	else if(dTemp<-100)strTemp1.Format(_T("%.f"), dTemp);//
                    else if(dTemp<-10)strTemp1.Format(_T("%.1f"), dTemp);
                    else if(dTemp<0)strTemp1.Format(_T("%.2f"), dTemp);
                    else strTemp1.Format(_T("%.3f"), dTemp);
                }
                else
                {
                    strTemp1 = _T(" N.A.");
                }
                CString strType = CString(board_inf.layout[j* 12 + i].Type);
                strType = strType.Left(2);
                if(strType != _T("BK") && strType != _T("SD") && strType != _T("QC")
                        && strType != _T("UD") && strType != _T("NC") && strType != _T("PC")) //?????
                {
                    strTemp1 =  _T("   EP");
                }
                strTemp2 += strTemp1;
                //  if(i < 12)
                if(i < 12)
                {
                    strTemp2 += _T(" ");
                }

                //  else
                //   {
                //   strTemp += _T("\n");
                //   }
            }
        }
        ConvertRowCol((CStringA)strTemp2, pCharConvert);


        strTemp= _T("");
        for(int i3 = 0; i3 < 73*11; i3++)
        {
            //pChar[i] = (char)(str.GetAt(i));
            strTemp+=pCharConvert[i3];

        }

        MY_Prn->PrintConvert(1);
        MY_Prn->PrintRowDis(1);

        UnicodeToAscii2((CStringA)strTemp, pChar);
        MY_Prn->Print_CHAR(pChar);
        MY_Prn->PrintConvert(0);
        MY_Prn->PrintRowDis(0);
        MY_Prn->Print_NextHx(0x05);   //?5?
        MY_Prn->Print_Enter_Next();
        MY_Prn->Print_Enter_Next();
        MY_Prn->Print_Enter_Next();
        MY_Prn->Print_Enter_Next();
        // delete [] pChar;
        // delete [] pChar2;
        //stuFile.Write(pChar,strTemp.GetLength());
        //	stuFile.Close();
    }
    else if(normal_analysis.wcMode == ANALYSIS_MODE_INTERPRET && board_inf.bHasData)
    {
        if(board_inf.interpret_para.bABS)
        {
            //2015-3-16
            if(sys_para.wcLanguage == CHINESE)
            {
                //      strTemp = _T("???????????:\n");
                char *buff= {"???????????:"};
                MY_Prn->Print_CHAR(buff);
                delete buff;
            }
            else
            {
                strTemp = _T("Interpret(ABS.):");
                //UnicodeToAscii(strTemp, pChar);
                UnicodeToAscii2((CStringA)strTemp, pChar);
                MY_Prn->Print_CHAR(pChar);

            }
            //2015-3-16
        }
        else
        {
            //2015-3-16
            if(sys_para.wcLanguage == CHINESE)
            {
                //    strTemp = _T("??????????:\n");
                char *buff= {"??????????:"};
                MY_Prn->Print_CHAR(buff);
                delete buff;
            }
            else
            {
                strTemp = _T("Interpret(Con.):");
                //strTemp = _T("Conc result:");
                UnicodeToAscii2((CStringA)strTemp, pChar);
                //UnicodeToAscii(strTemp, pChar);
                MY_Prn->Print_CHAR(pChar);
            }
            //2015-3-16
        }
        //2015-3-16
        // if(sys_para.wcLanguage == CHINESE)
        //{
        //char *buff={"????:"};
        //	MY_Prn->Print_CHAR(buff);
        //	delete buff;
        //   }
        //	else
        //{
        //	strTemp = _T("Concentration");
        //	UnicodeToAscii2((CStringA)strTemp, pChar);
        //  MY_Prn->Print_CHAR(pChar);
        //	}
        if(sys_para.wcLanguage == CHINESE)
        {
            if(normal_analysis.wcFilterCurrent == 0)
            {
                char *buff1= {"???1:"};
                MY_Prn->Print_ZHAdd(buff1,0);	// ??? 0 ???
                strTemp =  CString(filterLun.filter[board_inf.Filter1_locate]);
                strTemp += "@@";

                //strTemp += _T("\n");
                UnicodeToAscii2((CStringA)strTemp, pChar2);
                MY_Prn->Print_ZHAdd(pChar2,1);	// ??? 0 ???
                MY_Prn->Print_CHAR(MY_Prn->MainBuff);
                delete buff1;
            }
            else if(normal_analysis.wcFilterCurrent == 1)
            {
                char *buff1= {"???2:"};
                MY_Prn->Print_ZHAdd(buff1,0);	// ??? 0 ???

                strTemp =  CString(filterLun.filter[board_inf.Filter2_locate]);
                strTemp += "@@";
                // 	strTemp += _T("\n");
                UnicodeToAscii2((CStringA)strTemp, pChar2);
                MY_Prn->Print_ZHAdd(pChar2,1);	// ??? 0 ???
                MY_Prn->Print_CHAR(MY_Prn->MainBuff);
                delete buff1;

            }
            else
            {
                char *buff1= {"???1&2:"};
                MY_Prn->Print_ZHAdd(buff1,0);	// ??? 0 ???

                strTemp =  CString(board_inf.preCalculate);
                strTemp += "@@";
                // strTemp += _T("\n");
                UnicodeToAscii2((CStringA)strTemp, pChar2);
                MY_Prn->Print_ZHAdd(pChar2,1);	// ??? 0 ???
                MY_Prn->Print_CHAR(MY_Prn->MainBuff);
                delete buff1;
            }
            //Sleep(200);
        }
        else
        {
            if(normal_analysis.wcFilterCurrent == 0)
            {
                strTemp = (CString(_T("Filter 1:     ")) + CString(filterLun.filter[board_inf.Filter1_locate]));
            }
            else if(normal_analysis.wcFilterCurrent == 1)
            {
                strTemp = (CString(_T("Filter 2:     ")) + CString(filterLun.filter[board_inf.Filter2_locate]));
            }
            else
            {
                strTemp = (CString(_T("Filter 1&2:   ")) + CString(board_inf.preCalculate));
            }
            //	strTemp += _T("\n");
            UnicodeToAscii2((CStringA)strTemp, pChar);
            //UnicodeToAscii(strTemp, pChar);
            MY_Prn->Print_CHAR(pChar);
        }

        //		strTemp = _T("");
        strTemp2 = _T("  ");//"A "
        //2015-2-13
        for(int i = 0; i < 12; i++)
        {
            if(i < 9)
            {
                strTemp2 += _T("  ");
            }
            else// if(i < 11)
            {
                strTemp2 += _T(" ");
            }
            strTemp1.Format(_T("%d"), i + 1);
            strTemp2 += strTemp1;
            strTemp2 += _T("  ");

            if(i < 11)
            {
                strTemp2 += _T(" ");
            }
            //	else
            //	{
            //	strTemp2 += _T(" \n");
            //	}
        }

        //2015-2-13
        /*	for(int i = 0; i < 12; i++)
        {
        strTemp1.Format(_T("%d"), i + 1);
        strTemp += strTemp1;
        if(i < 11)
        {
        strTemp += _T(", ");
        }
        else
        {
        strTemp += _T("\n");
        }
        }*/

        for(int j = 0; j < 8; j++)
        {
            for(int i = 0; i < 13; i++) //2014-8-20?
            {
                if(i == 0)
                {
                    strTemp1.Format(_T("%c"), 'A' + j);
                    strTemp2 += strTemp1;
                    strTemp2 += _T(" ");
                    continue;
                }

                double dTemp;
                bool bHasResult = true;
                if(normal_analysis.wcFilterCurrent < 2)
                {
                    dTemp = dABS[0][normal_analysis.wcFilterCurrent][j * 12 + i-1];
                }
                else if(normal_analysis.bPreCalOK[0][j* 12 + i-1])
                {
                    dTemp = normal_analysis.dPreCal[0][j * 12 + i-1];
                }
                else
                {
                    bHasResult = false;
                }
                if(!board_inf.interpret_para.bABS && bHasResult)
                {
                    dTemp = normal_analysis.dConcentration[normal_analysis.wcFilterCurrent][j * 12 + i-1];
                    if(dTemp < 0.0)
                    {
                        bHasResult = false;
                    }
                }

                if(!bHasResult)
                {
                    strTemp1 = _T(" N.A.");
                }
                else
                {
                    //  strTemp1.Format(_T("%1.3f"), dTemp);
                    //2016-02-16
                    if(dTemp>=999.0)dTemp=999.0;//2016-02-16
                    else if(dTemp<=-99.0)dTemp=-99.0;
                    //	if(dTemp>=1000)strTemp1.Format(_T("%.f"), dTemp);///
                    if(dTemp>=100)strTemp1.Format(_T("%.1f"), dTemp);
                    else if(dTemp>=10)strTemp1.Format(_T("%.2f"), dTemp);
                    //	else if(dTemp<-100)strTemp1.Format(_T("%.f"), dTemp);//
                    else if(dTemp<-10)strTemp1.Format(_T("%.1f"), dTemp);
                    else if(dTemp<0)strTemp1.Format(_T("%.2f"), dTemp);
                    else strTemp1.Format(_T("%.3f"), dTemp);

                    //		if(dTemp<0)strTemp1.Format(_T("%1.2f"), dTemp);
                    //  else strTemp1.Format(_T("%1.3f"), dTemp);
                }

                CString strType = CString(board_inf.layout[j * 12 + i].Type);
                strType = strType.Left(2);
                if(strType != _T("BK") && strType != _T("SD") && strType != _T("QC")
                        && strType != _T("UD") && strType != _T("NC") && strType != _T("PC")) //?????
                {
                    strTemp1 =  _T("   EP");
                }
                CString strPos;
                if(strTemp1 != _T("   EP") && strTemp1 != _T(" N.A."))
                {
                    strPos = _T("");
                    if(board_inf.interpret_para.bPos[normal_analysis.wcFilterCurrent][j * 12 + i-1] && i<12)
                    {
                        //strPos = _T("++");
                        strPos = _T("P");
                    }
                    else if(board_inf.interpret_para.bWeakPos[normal_analysis.wcFilterCurrent][j * 12 + i-1] && i<12)
                    {
                        strPos = _T("+");
                    }
                }
                //strTemp2 += strTemp1 + _T(" ") + strPos;
                strTemp2 += strTemp1 + strPos;
                if(i < 12)
                {
                    if(strPos == _T("P") || strPos == _T("+"))
                    {
                        ;
                    }
                    //		else if(strPos = _T("+"))strTemp2 += _T(" ");
                    else strTemp2 += _T(" ");
                }
                //   else
                //   {
                //    else
                //   {
                //    strTemp += _T("\n");
                //  }
            }
        }
        ConvertRowCol((CStringA)strTemp2, pCharConvert);

        strTemp= _T("");
        for(int i3 = 0; i3 < 73*11; i3++)
        {
            //pChar[i] = (char)(str.GetAt(i));
            strTemp+=pCharConvert[i3];

        }

        MY_Prn->PrintConvert(1);
        MY_Prn->PrintRowDis(1);

        UnicodeToAscii2((CStringA)strTemp, pChar);
        MY_Prn->Print_CHAR(pChar);
        MY_Prn->PrintConvert(0);
        MY_Prn->PrintRowDis(0);

        MY_Prn->Print_NextHx(0x05);   //?5?
        MY_Prn->Print_Enter_Next();
        MY_Prn->Print_Enter_Next();
        MY_Prn->Print_Enter_Next();
        MY_Prn->Print_Enter_Next();

        //delete [] pChar;
        //  delete [] pChar2;
        //stuFile.Write(pChar,strTemp.GetLength());
        //stuFile.Close();
    }
    else if(normal_analysis.wcMode == ANALYSIS_MODE_QC && board_inf.bHasData)
    {
        //2015-3-16
        if(sys_para.wcLanguage == CHINESE)
        {
            //  strTemp = _T("??????:\n");
            char *buff= {"??????:"};
            MY_Prn->Print_CHAR(buff);
            delete buff;
        }
        else
        {
            strTemp = _T("QC result:");
            UnicodeToAscii2((CStringA)strTemp, pChar);
            MY_Prn->Print_CHAR(pChar);
        }
        //2015-3-16
        //2015-2-13
        if(sys_para.wcLanguage == CHINESE)
        {
            if(normal_analysis.wcFilterCurrent == 0)
            {
                char *buff1= {"???1:"};
                MY_Prn->Print_ZHAdd(buff1,0);	// ??? 0 ???
                strTemp =  CString(filterLun.filter[board_inf.Filter1_locate]);
                strTemp += "@@";
                //		strTemp += _T("\n");
                UnicodeToAscii2((CStringA)strTemp, pChar2);
                MY_Prn->Print_ZHAdd(pChar2,1);	// ??? 0 ???
                MY_Prn->Print_CHAR(MY_Prn->MainBuff);
                delete buff1;
            }
            else if(normal_analysis.wcFilterCurrent == 1)
            {
                char *buff1= {"???2:"};
                MY_Prn->Print_ZHAdd(buff1,0);	// ??? 0 ???

                strTemp =  CString(filterLun.filter[board_inf.Filter2_locate]);
                strTemp += "@@";
                //  	strTemp += _T("\n");
                UnicodeToAscii2((CStringA)strTemp, pChar2);
                MY_Prn->Print_ZHAdd(pChar2,1);	// ??? 0 ???
                MY_Prn->Print_CHAR(MY_Prn->MainBuff);
                delete buff1;

            }
            else
            {
                char *buff1= {"???1&2:"};
                MY_Prn->Print_ZHAdd(buff1,0);	// ??? 0 ???

                strTemp =  CString(board_inf.preCalculate);
                strTemp += "@@";
                //	 strTemp += _T("\n");
                UnicodeToAscii2((CStringA)strTemp, pChar2);
                MY_Prn->Print_ZHAdd(pChar2,1);	// ??? 0 ???
                MY_Prn->Print_CHAR(MY_Prn->MainBuff);
                delete buff1;
            }
            //Sleep(200);
        }
        else
        {
            if(normal_analysis.wcFilterCurrent == 0)
            {
                strTemp = (CString(_T("Filter 1: ")) + CString(filterLun.filter[board_inf.Filter1_locate]));
            }
            else if(normal_analysis.wcFilterCurrent == 1)
            {
                strTemp = (CString(_T("Filter 2: ")) + CString(filterLun.filter[board_inf.Filter2_locate]));
            }
            else
            {
                strTemp = (CString(_T("Filter 1&2: ")) + CString(board_inf.preCalculate));
            }
            //strTemp += _T("\n");
            UnicodeToAscii2((CStringA)strTemp, pChar);
            MY_Prn->Print_CHAR(pChar);
        }


        //char *buff2={"NO. "};
        //	 MY_Prn->Print_ZHAdd(buff2,0);	// ??? 0 ???
        //MY_Prn->Print_CHAR(pChar);
        if(sys_para.wcLanguage == CHINESE)
        {
            if(board_inf.quality_para.bABS==0)
            {
                // char *buff3={"?? "};
                char *buff3= {"?? ??  SD   CV   ??  ??  ??"};
                MY_Prn->Print_ZHAdd(buff3,0);	// ??? 0 ???
                MY_Prn->Print_CHAR(MY_Prn->MainBuff);
                delete buff3;
                //  MY_Prn->Print_CHAR(buff);
            }
            else  if(board_inf.quality_para.bABS==1)
            {
                char *buff3= {"?? ??? SD   CV   ??  ??  ??"};
                MY_Prn->Print_ZHAdd(buff3,0);	// ??? 0 ???
                MY_Prn->Print_CHAR(MY_Prn->MainBuff);
                delete buff3;
                //   char *buff={"???"};
                // MY_Prn->Print_CHAR(buff);
            }
        }
        else
        {
            if(board_inf.quality_para.bABS==0)
            {
                // char *buff3={"?? "};
                char *buff3= {"NO. Conc.  SD    CV   Upper Lower Result"};
                MY_Prn->Print_ZHAdd(buff3,0);	// ??? 0 ???
                MY_Prn->Print_CHAR(MY_Prn->MainBuff);
                delete buff3;
                //  MY_Prn->Print_CHAR(buff);
            }
            else  if(board_inf.quality_para.bABS==1)
            {
                char *buff3= {"NO. ABS    SD    CV   Upper Lower Result"};
                MY_Prn->Print_ZHAdd(buff3,0);	// ??? 0 ???
                MY_Prn->Print_CHAR(MY_Prn->MainBuff);
                delete buff3;
                //   char *buff={"???"};
                // MY_Prn->Print_CHAR(buff);
            }

            //   strTemp= CString(REFERENCE_SELECT[sys_para.wcLanguage][board_inf.quality_para.bABS]);
            //strTemp= CString(REFERENCE_SELECT[0][board_inf.quality_para.bABS]);
            //UnicodeToAscii2((CStringA)strTemp, pChar2);
            //MY_Prn->Print_ZHAdd( pChar2,1);	// ??? 0 ???
            // MY_Prn->Print_CHAR(pChar);
        }
        //const wchar_t REFERENCE_SELECT[LANGUAGE_TYPES][2][10] = {{_T("Conc."), _T("ABS")}, {_T("??"), _T("???")}, {_T("Conc."), _T("ABS")}, {_T("Conc."), _T("ABS")}};
        //   char *buffQC=new char[1000];
        //	strTemp = _T(" ");
        //	strTemp += _T("SD ");
        //	strTemp += _T("CV ");
        //    UnicodeToAscii2((CStringA)strTemp, buffQC);
        //		MY_Prn->Print_ZHAdd( buffQC,2);	// ??? 0 ???
        //	MY_Prn->Print_CHAR(pChar);


        //2015-3-16
        //    if(sys_para.wcLanguage == CHINESE)
        //   {
        //strTemp += _T("??, ");
        //	char *buff4={"?? ?? ??"};
        //	 MY_Prn->Print_ZHAdd(buff4,3);	// ??? 0 ???
        // MY_Prn->Print_CHAR(MY_Prn->MainBuff);
        //MY_Prn->Print_CHAR(buff);
        // delete buff4;

        // delete buff2;
        //  }
        //else
        //	{
        //	strTemp = _T("Upper limit ");
        //2015-3-16
        // strTemp += _T("Lower limit ");
        //2015-3-16
        //   if(sys_para.wcLanguage == CHINESE)
        //   {
        //    strTemp += _T("??, ");
        //    }
        //2015-3-16
        //	   strTemp += _T("Result\n");
        //	   char *buffQC2=new char[1000];
        //   UnicodeToAscii2((CStringA)strTemp, buffQC2);
        //   MY_Prn->Print_ZHAdd(buffQC2,3);	// ??? 0 ???
        // MY_Prn->Print_CHAR(MY_Prn->MainBuff);
        //	delete[] buffQC2;
        //	delete buff2;

        //   MY_Prn->Print_CHAR(pChar);
        //}
        //delete[] buffQC;
        //Sleep(200);
        //2015-3-16
        //    if(sys_para.wcLanguage == CHINESE)
        //    {
        //    strTemp += _T("??\n");
        //  }
        //2015-3-16

        //strTemp="";
        int k = 0;

        for (int i = 0; i < QC_MAX; i++)
        {
            strTemp = _T("");///
            if(k + 1 > board_inf.quality_para.nTotal[normal_analysis.wcFilterCurrent]) //???????
            {
                break;
            }

            if(!board_inf.quality_para.nTotalQC[normal_analysis.wcFilterCurrent][i])
            {
                continue;
            }

            k++;
            strTemp1.Format(_T("%2d"), i + 1);
            strTemp += strTemp1;
            strTemp += _T("  ");

            double dTemp = board_inf.quality_para.dReferenceQC[normal_analysis.wcFilterCurrent][i];
            double dTemp1 = dTemp;
            //2016-02-16

            strTemp1.Format(_T("%1.3f"), dTemp);
            strTemp += strTemp1;
            strTemp += _T(" ");

            dTemp = board_inf.quality_para.dSD[normal_analysis.wcFilterCurrent][i];
            strTemp1.Format(_T("%1.3f"), dTemp);
            strTemp += strTemp1;
            strTemp += _T(" ");

            if(dTemp1 < CONCENTRATION_VALUE_MIN && dTemp1 > -CONCENTRATION_VALUE_MIN)
            {
                strTemp1 = _T(" N.A.");
            }
            else
            {
                dTemp = board_inf.quality_para.dSD[normal_analysis.wcFilterCurrent][i] / dTemp1;
                strTemp1.Format(_T("%1.3f"), dTemp);
            }
            strTemp += strTemp1;
            strTemp += _T(" ");

            dTemp = sys_para.quality_para.dUpperLimit[board_inf.quality_para.bABS][i];
            strTemp1.Format(_T("%1.3f"), dTemp);
            strTemp += strTemp1;
            strTemp += _T(" ");

            dTemp = sys_para.quality_para.dLowerLimit[board_inf.quality_para.bABS][i];
            strTemp1.Format(_T("%1.3f"), dTemp);
            strTemp += strTemp1;
            strTemp += _T(" ");
            //strTemp1 = CString(QUALITY_RESULT[sys_para.wcLanguage][board_inf.quality_para.bFailed[normal_analysis.wcFilterCurrent][i]]);
            strTemp1 = CString(QUALITY_RESULT[0][board_inf.quality_para.bFailed[normal_analysis.wcFilterCurrent][i]]);
            strTemp += strTemp1;
            //strTemp += _T("\n");
            UnicodeToAscii2((CStringA)strTemp, pChar);
            MY_Prn->Print_CHAR(pChar);

            // MY_Prn->Print_ZHAdd(pChar,1);	// ??? 0 ???
            //		 MY_Prn->Print_CHAR(MY_Prn->MainBuff);

            //	  UnicodeToAscii2((CStringA)strTemp, pChar2);
            //  MY_Prn->Print_ZHAdd(pChar2,0);	// ??? 0 ???
            //  MY_Prn->Print_CHAR(MY_Prn->MainBuff);
            //   MY_Prn->Print_CHAR(pChar);



            //2015-3-16
            /*	    if(sys_para.wcLanguage == CHINESE)
            {
            if(board_inf.quality_para.bFailed[normal_analysis.wcFilterCurrent][i]==0)
            {
            char *buff={"??"};
            MY_Prn->Print_ZHAdd(buff,1);	// ??? 0 ???
            MY_Prn->Print_CHAR(MY_Prn->MainBuff);
            //MY_Prn->Print_CHAR(buff);
            delete buff;
            }
            else if(board_inf.quality_para.bFailed[normal_analysis.wcFilterCurrent][i]==0)
            {
            char *buff={"??"};
            MY_Prn->Print_ZHAdd(buff,1);	// ??? 0 ???
            MY_Prn->Print_CHAR(MY_Prn->MainBuff);
            // MY_Prn->Print_CHAR(buff);
            delete buff;
            }
            }
            else
            {
            strTemp1 = CString(QUALITY_RESULT[sys_para.wcLanguage][board_inf.quality_para.bFailed[normal_analysis.wcFilterCurrent][i]]);
            strTemp = strTemp1;
            //strTemp += _T("\n");
            UnicodeToAscii2((CStringA)strTemp, pChar);
            MY_Prn->Print_ZHAdd(pChar,1);	// ??? 0 ???
            MY_Prn->Print_CHAR(MY_Prn->MainBuff);
            //  MY_Prn->Print_CHAR(pChar);
            }
            */
            //	const wchar_t QUALITY_RESULT[LANGUAGE_TYPES][2][10] = {{_T("Passed"), _T("Failed")}, {_T("??"), _T("??")}, {_T("Passed"), _T("Failed")}, {_T("Passed"), _T("Failed")}}; //2015-3-16
            //	strTemp += strTemp1;
            //	strTemp += _T("\n");
        }
        //UnicodeToAscii2((CStringA)strTemp, pChar);
        //MY_Prn->Print_CHAR(pChar);
        //Sleep(200);

        MY_Prn->Print_Enter_Next();
        MY_Prn->Print_Enter_Next();
        MY_Prn->Print_Enter_Next();
        MY_Prn->Print_Enter_Next();
        MY_Prn->Print_NextHx(0x05);   //?5?
        //	 delete [] pChar;
        //   delete [] pChar2;

        // delete[] buffQC;
        //	UnicodeToAscii(strTemp, pChar);
        //MY_Prn->Print_CHAR(pChar);
        //	stuFile.Write(pChar,strTemp.GetLength());
        //stuFile.Close();
    }
    //	else if(normal_analysis.wcMode == ANALYSIS_MODE_CURVE && board_inf.bHasData)
    //	{
    ////wenqg add, TODO, 20160816 17:10
    //
    //	}


    delete [] pChar;
    delete [] pChar2;
    delete [] pCharConvert;

    //delete [] strTemp;
    delete strTemp;
    delete strTemp1;
    delete strTemp2;
    delete str2;
    Sleep(1000);

    //2015-3-16
    //strTemp = _T("The current data is exported successfully.");
    //	if(sys_para.wcLanguage == CHINESE)
    //	{
    //	strTemp = _T("?????????");

    //strTemp = _T("??????");
    //	}
    //	strTemp += _T("\n\r");
    //strTemp +=  _T("FileName:")+StrExportFileName;
    //MessageBoxExportFile(strTemp,StrExportFileName);
    //2015-3-16

    // delete [] pChar;
}