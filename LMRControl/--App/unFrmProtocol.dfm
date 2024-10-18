object FrmProtocol: TFrmProtocol
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Salvar/Atualizar Protocolo'
  ClientHeight = 162
  ClientWidth = 488
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Calibri'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 15
  object Label1: TLabel
    Left = 32
    Top = 8
    Width = 34
    Height = 15
    Caption = 'Nome:'
  end
  object Label2: TLabel
    Left = 8
    Top = 40
    Width = 58
    Height = 15
    Caption = 'Descri'#231#227'o:'
  end
  object cbProtocolName: TComboBox
    Left = 72
    Top = 5
    Width = 411
    Height = 23
    MaxLength = 200
    Sorted = True
    TabOrder = 0
  end
  object MemoProtocolDescription: TMemo
    Left = 72
    Top = 37
    Width = 411
    Height = 89
    TabOrder = 1
  end
  object btnSave: TButton
    Left = 309
    Top = 132
    Width = 75
    Height = 25
    Caption = 'Gravar'
    Default = True
    ModalResult = 1
    TabOrder = 2
  end
  object Fechar: TButton
    Left = 408
    Top = 132
    Width = 75
    Height = 25
    Caption = 'Fechar'
    ModalResult = 8
    TabOrder = 3
  end
end
