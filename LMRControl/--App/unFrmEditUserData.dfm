object FrmEditUserData: TFrmEditUserData
  Left = 0
  Top = 0
  BorderStyle = bsSizeToolWin
  Caption = 'Dados do Usu'#225'rio'
  ClientHeight = 219
  ClientWidth = 635
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 32
    Height = 13
    Caption = 'Login: '
  end
  object Label2: TLabel
    Left = 8
    Top = 98
    Width = 34
    Height = 13
    Caption = 'Nome: '
  end
  object Label3: TLabel
    Left = 288
    Top = 98
    Width = 61
    Height = 13
    Caption = 'Sobrenome: '
  end
  object Label4: TLabel
    Left = 8
    Top = 55
    Width = 37
    Height = 13
    Caption = 'Senha: '
  end
  object Label5: TLabel
    Left = 288
    Top = 55
    Width = 67
    Height = 13
    Caption = 'Confirma'#231#227'o: '
  end
  object Label6: TLabel
    Left = 8
    Top = 138
    Width = 76
    Height = 13
    Caption = 'Departamento: '
  end
  object btnApply: TLMDMMButton
    Left = 537
    Top = 184
    Width = 90
    Height = 30
    AutoSize = False
    OnClick = btnApplyClick
    AllowMouseOver = False
    ButtonFaceStyle = sbStretch
    ButtonFaceImageList = MyDataModule.pngImageList
    ButtonFaceIndicesNew2 = {
      0000380000003800000039000000390000003800000039000000390000003800
      0000010038000000390000003900000038000000390000003900000038000000
      3800000038000000}
    ButtonFaceTransColNew = {FFFFFF1D}
  end
  object btnCancel: TLMDMMButton
    Left = 433
    Top = 184
    Width = 90
    Height = 30
    AutoSize = False
    OnClick = btnCancelClick
    AllowMouseOver = False
    ButtonFaceStyle = sbStretch
    ButtonFaceImageList = MyDataModule.pngImageList
    ButtonFaceIndicesNew2 = {
      0000360000003600000035000000370000003600000035000000350000003600
      0000010036000000350000003500000036000000370000003500000036000000
      3600000036000000}
    ButtonFaceTransColNew = {FFFFFF1D}
  end
  object tedUserLogin: TEdit
    Left = 8
    Top = 24
    Width = 171
    Height = 21
    TabOrder = 0
  end
  object chbIsSuperUser: TCheckBox
    Left = 288
    Top = 26
    Width = 97
    Height = 17
    Caption = 'Super Usu'#225'rio'
    TabOrder = 1
  end
  object tedUserName: TEdit
    Left = 8
    Top = 112
    Width = 219
    Height = 21
    CharCase = ecUpperCase
    TabOrder = 4
  end
  object tedUserSurname: TEdit
    Left = 288
    Top = 112
    Width = 339
    Height = 21
    CharCase = ecUpperCase
    TabOrder = 5
  end
  object tedUserPassword: TEdit
    Left = 8
    Top = 71
    Width = 171
    Height = 21
    PasswordChar = #183
    TabOrder = 2
  end
  object tedUserPasswordConfirm: TEdit
    Left = 288
    Top = 71
    Width = 171
    Height = 21
    PasswordChar = #183
    TabOrder = 3
  end
  object tedUserDept: TEdit
    Left = 8
    Top = 152
    Width = 281
    Height = 21
    CharCase = ecUpperCase
    TabOrder = 6
  end
end
