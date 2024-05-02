object frmPasswd: TfrmPasswd
  Left = 507
  Top = 304
  BorderStyle = bsDialog
  Caption = 'Digite a senha'
  ClientHeight = 110
  ClientWidth = 326
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Verdana'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 16
  object btnOk: TLMDMMButton
    Left = 110
    Top = 77
    Width = 90
    Height = 30
    AutoSize = False
    OnClick = btnOKClick
    AllowMouseOver = False
    ButtonFaceStyle = sbStretch
    ButtonFaceIndicesNew2 = {
      0000430000004300000044000000440000004300000044000000440000004300
      0000010043000000440000004400000043000000440000004400000043000000
      4300000043000000}
    ButtonFaceTransColNew = {FFFFFF1D}
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 313
    Height = 65
    Caption = 'Entre com a senha: '
    TabOrder = 0
    object edPasswd: TEdit
      Left = 24
      Top = 24
      Width = 265
      Height = 24
      PasswordChar = '*'
      TabOrder = 0
      OnKeyDown = FormKeyDown
    end
  end
end
