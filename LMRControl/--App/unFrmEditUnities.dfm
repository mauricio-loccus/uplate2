object FrmEditUnities: TFrmEditUnities
  AlignWithMargins = True
  Left = 0
  Top = 0
  Align = alClient
  AutoSize = True
  BorderStyle = bsToolWindow
  Caption = 'Unidade de Medida'
  ClientHeight = 84
  ClientWidth = 201
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
    Left = 7
    Top = 11
    Width = 46
    Height = 13
    Caption = 'Unidade: '
  end
  object btnCancel: TLMDMMButton
    Left = 7
    Top = 45
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
  object btnApply: TLMDMMButton
    Left = 103
    Top = 45
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
  object edUnit: TEdit
    Left = 64
    Top = 8
    Width = 129
    Height = 21
    TabOrder = 0
  end
end
