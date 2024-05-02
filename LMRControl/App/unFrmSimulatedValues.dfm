object FrmSimulatedValues: TFrmSimulatedValues
  AlignWithMargins = True
  Left = 0
  Top = 0
  AutoSize = True
  BorderIcons = []
  BorderStyle = bsToolWindow
  Caption = 'Valores'
  ClientHeight = 275
  ClientWidth = 848
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
    Left = 3
    Top = 247
    Width = 131
    Height = 25
    Caption = 'Valores Aleat'#243'rios'
    TabOrder = 0
    OnClick = btnRandomClick
  end
  object btnClearValues: TButton
    Left = 144
    Top = 247
    Width = 131
    Height = 25
    Caption = 'Zerar Valores'
    TabOrder = 1
    OnClick = btnClearValuesClick
  end
  object btnClose: TButton
    Left = 709
    Top = 247
    Width = 131
    Height = 25
    Caption = 'Fechar'
    TabOrder = 2
    OnClick = btnCloseClick
  end
  object btnLoadCSV: TButton
    Left = 281
    Top = 247
    Width = 175
    Height = 25
    Caption = 'Carregar valores via CSV'
    TabOrder = 3
    OnClick = btnLoadCSVClick
  end
  object RawValuesGrid: TStringGrid
    Left = 0
    Top = 0
    Width = 848
    Height = 233
    Align = alTop
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
    Left = 8
    Top = 32
  end
end
