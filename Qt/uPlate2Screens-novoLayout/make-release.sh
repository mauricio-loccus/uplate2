#!/bin/bash
echo Making Release Version
echo ...

git pull 


# TODO - compilar
mkdir -p releases/
rm -r releases/*
cp  ../build-uPlate2Screens-Desktop_Qt_6_3_1_MSVC2019_64bit-Release/release/uPlate2Screens.exe releases/μPlate2.exe
"C:\Qt\6.3.1\msvc2019_64\bin\windeployqt.exe" --qmldir . releases/μPlate2.exe
echo Done
sleep 5
