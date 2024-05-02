##ELISA 

## [02Mar23] - Reuniao

login e senha: loccus/biotech


experimento
	...
- modo endpoint

modo cinetica
	faz repeticoes


- tem filtro de disco
	- 

- selecao de placa

- ta no modo simulador
	dai ele abre uma tabela pra eu colocar valores manuais, aleatorios eou carregar de planilha
	qdo tem o equipamentre ele le, e ja mostra a leitra nas placas (bolinhas

- calulo qualitativo
    - le valor de referncia
        - ele vai comparar as posicoes desconhecidas

        - Precisa de uma formula pra interpretar

- curva de calibracao
    - colocar referencias
    - dai ele poe as leituras no grafico


1) fazer comunicar com placa nova

2) trazer novas funcionalidades (tudo feito no qt)
    - mais bolinhas
    - melhorar o calculo qualitativo
        - melhorar formula
    - melhorar o desenho do grafico de calibracao 
    - filtros
        filtros programaveis - filtro 1- da um nome
        filtro 2 tem um nome
    - 


----------------
## Codigo


- c++ builder

    TElisaDevice

    Classe unLMR96Device.cpp
            - envia comandos

    sendGetKey
        TLMR96Device::Connect

- reparar q tem um arquivo no dirlocal pra habilitar ou nao o modo similador (ini)

- sendGetKey - primeira funcao q ele chama e manda comando pra maquina, via usb/serial

- no programa do qt, checar o protocoloserial.cpp

## Program em Qt

- programa em QT (feiot por outra empresa)
    - ele se comunica com a versao NOVA do equipamento - protocolo novo
    - mas falta funcionlidades q o prog feito em builder tem
    - entao a ideia eh copiar as coisas do qt pro c++ builder


## protocolo novo

- header: 0xFA, 0xFB, 0xFC, 0xFD 
- 2 ultimos bytes: checksum 16

- getkey - tem no anterior (como uma autenticacao), mas nao tem no novo

### connectToPC
    fa fb fc fd 00 00 00 00 00 00 00 00 70 00 - header
                                                00 01 - command
                                                        00 00 00 02 - size in bytes - nesse caso, ele nao tem param nenhum, soh conta 2 bytes to checksum
                                                                        04 x61    - checksum 16 bits (soma tudo)

                         QByteArrayLiteral("\xFA\xFB\xFC\xFD\x00\x00\x00\x00\x00\x00\x00\x00\x70\x00
                                                                                                    \x00\x01
                                                                                                            \x00\x00\x00\x02
                                                                                                                            \x04\x61"); // checksum

Response
fa fb fc fd 00 00 00 00 00 00 00 00 70 00
                                        00 01
                                              00 00 00 39

        00 00 00 00                                     // task_busy = 0 ou 1
        00 00 00 01                                     // MACHINE_BUSY (constant) = 1
        31 31 32 32 30 32 32 30 36 32 32 30 30 33 36   // PN_LENGTH  15  - SystemPrameter.PN[i] (Part number?)

        00 00 01 95 // Filter_Max = 8 consunto de filtros -> 00 00 FilterHigh FilterLow
        00 00 01 c2 
        00 00 01 ec 
        00 00 02 76 
        00 00 00 00 
        00 00 00 00 
        00 00 00 00 
        00 00 00 00

        0a 44  // CRC


------------------

### disconnect
    QByteArray command = QByteArrayLiteral("\xFA\xFB\xFC\xFD\x00\x00\x00\x00\x00\x00\x00\x00\x70\x00
                                                                                                    \x00\x02
                                                                                                            \x00\x00\x00\x02
                                                                                                                            \x04\x62"); // checksum

### plateInOut(){
    QByteArray command = QByteArrayLiteral("\xFA\xFB\xFC\xFD\x00\x00\x00\x00\x00\x00\x00\x00\x70\x00
                                                                                                    \x00\x06
                                                                                                            \x00\x00\x00\x02
                                                                                                                            \x04\x66"); // checksum

------------------------
### setparam e init program

fa fb fc fd 00 00 00 00 00 00 00 00 70 00 
    00 08 
    00 00 00 23 

//[20]
[0]
    00 00 00 01 
[4]
    00 00 00 01 filtro1
[8]
    00 00 00 03 filtro2 ()
[12]
    00 00 00 00 // speed_Read   = 1 = standard; 0 = Fast
[16]
    00 00 00 00 // enable shake[19]  (0 ou 1 acho)
[20]
    00 00 00 00 //velocidade shake[23] - 
[24]
    00 00 00 01 // tempo de shake em segundos  big endian
[28]
    00          // ShakeMode=SHAKE_FIRST =0 ou SHAKE_EACH=1
[29]
    00 00 00 00    // tempo de espera em segundos big endian

    04 8f 


setParam(){
    // 53 bytes
    //QByteArray command = QByteArrayLiteral("\xFA\xFB\xFC\xFD\x00\x00\x00\x00\x00\x00\x00\x00\x70\x00
                                                                                                      \x00\x08
                                                                                                                \x00\x00\x00\x23   // 35 bytes - 33 dados + 2 checksum

                                                                                             \x00\x00\x00\x01
                                                                                             \x00\x00\x00   //[23]
    //                                                                                        \x**\x00\x00\x00   //[27]  // (filtro1_Read+1)
    //                                                                                        \x**\x00\x00\x00   //[31]  // se (filtro2_Read>0) // logica abaixo
    //                                                                                        \x**\x00\x00\x00   //[35]  // speed_Read   = 1 = standard; 0 = Fast
    //                                                                                        \x**\x00\x00\x00   //[39]   // enable shake   (0 ou 1 acho)
    //                                                                                        \x**               //[43]    //velocidade shake - 1=low, 2=medium, 3=high
    //                                                                                            
                                                                                                        \x**\x**\x**   //[44]   // tempo de shake em segundos (3 bytes) 
    //                                                                                        \x01
                                                                                                        \x00\x00\x00   //[48]   // tempo de espera em segu
                                                                                                                        ** ** // checksum

```
    command[15] = 0x8;
    command[19] = 0x23;
    command[23] = 0x1;
    command[27] = (filtro1_Read+1);
    if(filtro2_Read>0){
        if(filtro2_Read >= filtro1_Read){
            command[31] = (filtro2_Read + 1);
        }else{
             command[31] = filtro2_Read;
        }
    }
    command[35] = speed_Read;
    command[47] = 0x1;
```


fa fb fc fd 00 00 00 00 00 00 00 00 70 00 00 03 00 00 00 06 00 00 00 01 04 68

initRead(){
    QByteArray command = QByteArrayLiteral("\xFA\xFB\xFC\xFD\x00\x00\x00\x00\x00\x00\x00\x00\x70\x00
                                                                                                    \x00\x03
                                                                                                            \x00\x00\x00\x06
                                                                                                                            \x00\x00\x00\x01
                                                                                                                                            \x04\x68");  // checksum


-**Ele chama primeiro o setParam e logo depois o initReaed**

#define TUBE_MAX                96
#define TUBE_MAX_PER_ROW        12
#define TUBE_MAX_PER_COL        8

- reposta ( eu peguei na serial)

fa fb fc fd 00 00 00 00 00 00 00 00 70 00

01 00

00 00 03 0e     // qtd bytes -> 030e = 782 (se tem 2 filtros), ou 018e = 398 (se tem 1 filtro)

00 00 00 01    // PlateCurrent+1
00 00 00 01    // kinetic_readings_practical
00 00 00 02    // se tem filter2 = 2, senao = 1


35 98 33 78 00 00 00 00 00 00 00 00 00 00 00 00     // Leituras - 4 bytes -> float, A01, A02...A12, B01, B02...B12, ...H12
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
39 22 39 ad 39 1e 63 a2 39 01 44 23 38 b6 20 3f
38 88 d7 51 38 4a 58 e2 38 2e e4 af 37 d5 98 26
37 8f fb a5 37 82 25 a4 37 aa 5b 8d 37 b2 23 e9
38 92 22 d2 38 aa 21 25 38 96 3e 39 38 9e 22 01
38 38 d6 57 38 0f c3 92 38 0f 54 e4 38 08 69 f5
38 06 77 e1 37 ae ae 6b 37 ee 3d 31 38 08 d8 a4
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 36 a7 c4 2d 37 36 77 5d 37 5b a6 98
37 86 09 d4 37 25 2b cb 34 c1 b5 ea 36 67 c2 94
37 44 4d 68 37 13 e0 38 37 8f 1e 45 37 30 69 b6
00 00 00 00 00 00 00 00 00 00 00 00 37 9a 5c 23
37 b9 0e e4 37 c6 76 27 37 c6 e4 d8 37 b7 c2 d5
37 a8 a0 ce 37 61 b4 3b 37 7d 60 46 37 c1 b4 9c
36 ba ca 8f 38 28 31 1f 38 70 64 92 38 89 ec 01
38 92 75 d4 38 9c 67 50 38 93 c1 d9 38 96 ac e5
38 4b 36 3d 38 45 28 ba 38 49 7b 85 38 16 e5 d7
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00

00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00     // 2nd leitura, mesma coisa
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
37 bb 05 ba 37 c1 27 72 37 d7 0d 91 37 c3 c8 2f
37 97 fb d9 37 c3 c8 2f 37 3b 76 77 37 ec 83 8a
37 d1 5b fb 37 b9 45 3c 37 87 c7 3f 37 87 57 1f
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
37 a9 10 ad 37 89 87 bf 37 87 c7 3f 37 95 cb 3a
37 4c fb 7d 37 6d 64 c3 37 56 9e 40 37 cb 3a 44
37 b0 82 c6 37 ac 21 8a 37 d3 8c 97 37 f5 45 f7
38 f3 d3 5b 38 f7 54 25 38 e0 aa fa 38 dd 9a 44
38 bb 8e 34 38 b5 dc d3 38 96 e1 28 38 9c 76 8f
38 6f 22 46 38 54 33 35 38 49 b0 6c 38 31 99 fb
39 96 6e 98 39 89 5a d9 39 7d 88 96 39 64 be a2
39 44 d7 0a 39 32 3b 84 39 1c c7 37 39 13 87 49
38 e7 20 77 38 cb 19 ed 38 ac c6 9b 38 85 e8 d8
00 00 00 00 00 00 00 00 36 d3 fd e3 37 31 d3 b1
36 d9 3f 6a 37 50 7c 7e 37 6b a4 43 37 a4 3f 51
37 5a ff 81 37 69 e3 c3 37 9d ad 75 37 bf d7 14


        
 -- -- -- -- -- -- -- -- -- -- -- ---------------------------
## inicializacao

 formShow
    Onetimeshot
        actrConnectExecute
            m_elisaDevice->Connect -> envia comando de conectar (muda pra modo PC - desliga o LCD)
            m_elisaDevice->sendGetFilterList() -> acho q nao tem isso na fersao nova  

                FillFiltersComboBox();
                if (!mFiltersControlsAdjusted)
                {
                    grpFilters->Visible = True;
                    lbUnity->Top -= grpWaveLength->Height;
                    cbUnity->Top -= grpWaveLength->Height;
                    lbUnity->Visible = True;
                    cbUnity->Visible = True;
                    mFiltersControlsAdjusted = True;
                }

- FILTRO
    - parece q no antigo dava pra ler...no novo, tem q ter vindo de um arqvuio, nao tem comando pra ler ele

- somente o primeiro comando (disconect) coloquei pra ele nao esperar uma resposta
    - dai todos os outros pegam resposta
    - ele SEMPRE chama um disconect primeiro e depois conect


## firmaware

- parece q tem um firmware da Allsheng

- olhar o codigo CommProcess_PC.h

```
enum
{
    COMMAND_CONNECT_ACK_PC=0x0001,    //Á¬½ÓÓ¦´ð
    COMMAND_UNCONNECT_ACK_PC=0x0002,  //¶Ï¿ªÓ¦´ð
    COMMAND_RUN_ACK_PC=0x0003,
    COMMAND_STOP_ACK_PC=0x0004,
    COMMAND_PLATEIN_ACK_PC=0x0005,
    COMMAND_PLATEOUT_ACK_PC=0x0006,
    COMMAND_NEXT_PLATE_ACK_PC=0x0007,
    COMMAND_MEASURE_PARA_ACK_PC=0x0008,
    COMMAND_KINETIC_ACK_PC=0x0009,
    COMMAND_VIEW_ACK_PC=0x000A,      //²éÑ¯,ÐÄÌø°ü
    COMMAND_SEND_PN_ACK_PC=0x000B,   //ÏÂ·¢PNºÅ

};
//·¢ËÍPCÃüÁî
enum
{
    COMMAND_MEASURE_END_PC=0x0100,    //¼ì²â½áÊø
    COMMAND_CURR_BOARD_END_PC=0x0200, //µ±Ç°°å¼ì²â½áÊø
    COMMAND_ERRCODE_PC=0x0300,        //·¢ËÍ¹ÊÕÏ´úÂë
    COMMAND_UNCONNECT_PC=0x0500,      //¶Ï¿ªÃüÁî
};

```
-----------------

## Filtros

- Antes ele lia do equipamento, tinha um comando

- Ele manda infos de filtro na inicializacao, mas nao sei se ta certo

- dai no qt, ele le de arquivo

01 - 405 nm
02 - 450 nm
03 - 492 nm
04 - 630 nm


- esses params aqui

- eu forcei ele dentro do construtor da classe
    - assim ele ja mostra no combobox certinho 


- funcoes q setam os filtros no combobox
```
acFiltersConfigExecute
    - action lista, nao sei qdo chama isso aqui
        AnsiString filterName = AnsiString(lmr96Device->Filters.filter[i]).UpperCase();

actConnectExecute
    FillFiltersComboBox

        AnsiString filterName = AnsiString(m_elisaDevice->Filters.filter[i]).UpperCase();
            classe ELISAdevice
                __property FILTERLUN Filters = {read = m_Filters, write = m_Filters};



LoadSetupBranch


```

## calcMethod

- o objetivo eh q qdo tem 2 filtros, ele faz 2 leituras de cada poço e uma operacao matematica com os 2 numeros (soma, subtrai etc)

- No programa antigo, ele mandava pro equipamennto
    - e aparetemente ele mesmo calculava la

- No novo, qdo eu seto o filtro2 diferente de zero, ele manda as 2 leituras (2 arrayzao)
    primeiro um e depois o outro
    - dai no prog eu tenho q fazer o calculo conforme o calmethod escolihido

- eu tive q adicionar um parametreo "rawData2" no WellList pra ele guarda essa info
    - e tem um singleton chamado TWellMatrixSingleton - refMatrix
        - Tinha ja um RawValue, e dai adicionei um parametro RawValueFilter2
    - dentro do OnLMR96ReadDone eu fiz ele ler o rawData2 e jogar no RawValueFilter2

- dessa forma as leituras ficam na memoria e chegam ate o frmMain

## apresentacao na tela


actProgramRunExecute (botao)

    // le parametros

    // zera WellList, RawData, RawDataFilter2 etc

    // dai chama um dos dois dependendo do tipo

    DoNormalRead
        laco for - envia isso pra cada placa configurada
            m_elisaDevice->sendSetParams();  // envia comando
            m_elisaDevice->sendRunProgram();

            // se tem mais de 1 placa, manda abrr a porta e esperar o usuario apertar ok pra mandar comando de novo

    ou 
    
    DoKineticRead
        // TODO


    DoProcessResults

        UpdateUi

        DoProcessBlanks
            RawValue

        DoProcessConcentrations

        DoProcessCPnCNs
            accumulated += (*it)->RawValue;


        DoProcessQCs

