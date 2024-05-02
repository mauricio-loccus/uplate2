object FrmRenamePlate: TFrmRenamePlate
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Renomear Placa'
  ClientHeight = 95
  ClientWidth = 348
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 16
    Width = 58
    Height = 13
    Caption = 'Novo nome:'
  end
  object nameEdit: TEdit
    Left = 72
    Top = 13
    Width = 268
    Height = 21
    MaxLength = 256
    TabOrder = 0
    TextHint = 'Novo nome'
  end
  object btnOk: TButton
    Left = 176
    Top = 62
    Width = 75
    Height = 25
    Caption = 'Renomear'
    Default = True
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Calibri'
    Font.Style = []
    ModalResult = 1
    ParentFont = False
    TabOrder = 1
    OnClick = btnOkClick
  end
  object btnCancel: TButton
    Left = 265
    Top = 62
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancelar'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Calibri'
    Font.Style = []
    ModalResult = 2
    ParentFont = False
    TabOrder = 2
  end
end
