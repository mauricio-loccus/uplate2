object CellOptions: TCellOptions
  Left = 0
  Top = 0
  ActiveControl = rgEnumDirection
  BorderStyle = bsToolWindow
  Caption = 'Op'#231#245'es de Preenchimenbto'
  ClientHeight = 158
  ClientWidth = 295
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
  object rgEnumDirection: TRadioGroup
    Left = 8
    Top = 8
    Width = 278
    Height = 69
    Caption = 'Enumera'#231#227'o dos po'#231'os '
    ItemIndex = 0
    Items.Strings = (
      'Topo -> Fundo (modo linha)'
      'Esqueda -> Direita (modo coluna)')
    TabOrder = 0
    TabStop = True
  end
  object StaticText1: TStaticText
    Left = 176
    Top = 87
    Width = 43
    Height = 17
    Caption = 'R'#233'plicas'
    TabOrder = 4
  end
  object spnReplicas: TLMDSpinEdit
    Left = 232
    Top = 83
    Width = 55
    Height = 21
    Hint = ''
    Bevel.Mode = bmWindows
    Caret.BlinkRate = 530
    TabOrder = 1
    AutoSelect = True
    CustomButtons = <>
    MinValue = 1
    MaxValue = 96
    Value = 1
    Value = 1
  end
  object btnOk: TButton
    Left = 125
    Top = 125
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 2
    OnClick = btnOkClick
  end
  object btnCancel: TButton
    Left = 212
    Top = 125
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancelar'
    ModalResult = 2
    TabOrder = 3
  end
end
