object FrmSimulatedValues: TFrmSimulatedValues
  AlignWithMargins = True
  Left = 0
  Top = 0
  BorderIcons = []
  BorderStyle = bsSingle
  Caption = 'Valores'
  ClientHeight = 290
  ClientWidth = 872
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
  object btnRandom: TButton
    AlignWithMargins = True
    Left = 16
    Top = 242
    Width = 191
    Height = 33
    Caption = '&Valores Aleat'#243'rios'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Arial'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnClick = btnRandomClick
  end
  object btnClearValues: TButton
    Left = 213
    Top = 242
    Width = 191
    Height = 33
    Caption = '&Zerar Valores'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Arial'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    OnClick = btnClearValuesClick
  end
  object btnClose: TButton
    Left = 665
    Top = 242
    Width = 191
    Height = 33
    Cancel = True
    Caption = '&Fechar'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    OnClick = btnCloseClick
  end
  object btnLoadCSV: TButton
    Left = 410
    Top = 242
    Width = 191
    Height = 33
    Caption = 'Carregar valores via CSV'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Arial'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    OnClick = btnLoadCSVClick
  end
  object RawValuesGrid: TStringGrid
    Left = 16
    Top = 16
    Width = 840
    Height = 217
    ColCount = 13
    RowCount = 9
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goEditing]
    ScrollBars = ssNone
    TabOrder = 4
    OnDrawCell = RawValuesGridDrawCell
    OnEnter = RawValuesGridEnter
    OnExit = RawValuesGridExit
    OnGetEditText = RawValuesGridGetEditText
    OnSelectCell = RawValuesGridSelectCell
    OnSetEditText = RawValuesGridSetEditText
  end
  object RandGen: TRandGen
    HighBorder = 6.000000000000000000
    Resolution = 100
    Left = 616
    Top = 248
  end
end
