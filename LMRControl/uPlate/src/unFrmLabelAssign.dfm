object FrmLabelAssignment: TFrmLabelAssignment
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMaximize]
  BorderStyle = bsSingle
  Caption = 'R'#243'tulos'
  ClientHeight = 457
  ClientWidth = 885
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object RawValuesGrid: TStringGrid
    Left = 16
    Top = 16
    Width = 849
    Height = 233
    ColCount = 13
    RowCount = 9
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goEditing]
    ScrollBars = ssNone
    TabOrder = 0
    OnDrawCell = RawValuesGridDrawCell
    OnSelectCell = RawValuesGridSelectCell
  end
  object btnClose: TButton
    Left = 734
    Top = 263
    Width = 131
    Height = 25
    Caption = 'Fechar'
    TabOrder = 1
    OnClick = btnCloseClick
  end
end
