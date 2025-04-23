object FrmLabelAssignment: TFrmLabelAssignment
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMaximize]
  BorderStyle = bsSingle
  Caption = 'R'#243'tulos'
  ClientHeight = 475
  ClientWidth = 873
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
  object btnClose: TButton
    Left = 726
    Top = 428
    Width = 131
    Height = 34
    Caption = 'Fechar'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    OnClick = btnCloseClick
  end
  object tsPlates: TTabSet
    AlignWithMargins = True
    Left = 16
    Top = 388
    Width = 841
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = []
    SoftTop = True
    Tabs.Strings = (
      '...   ')
    TabIndex = 0
  end
  object LabelGrid: TStringGrid
    Left = 16
    Top = 16
    Width = 841
    Height = 372
    ColCount = 13
    DefaultRowHeight = 40
    RowCount = 9
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goEditing]
    ScrollBars = ssNone
    TabOrder = 2
    OnDrawCell = LabelGridDrawCell
    OnSelectCell = LabelGridSelectCell
  end
end
