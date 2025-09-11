object FrmLabelAssignment: TFrmLabelAssignment
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMaximize]
  Caption = 'R'#243'tulos'
  ClientHeight = 468
  ClientWidth = 880
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnCreate = FormCreate
  OnKeyPress = FormKeyPress
  OnShow = FormShow
  DesignSize = (
    880
    468)
  PixelsPerInch = 96
  TextHeight = 13
  object bApply: TButton
    Left = 741
    Top = 422
    Width = 131
    Height = 38
    Anchors = [akRight, akBottom]
    Caption = 'Aplicar'
    Default = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    OnClick = bApplyClick
  end
  object tsPlates: TTabSet
    AlignWithMargins = True
    Left = 16
    Top = 388
    Width = 848
    Height = 28
    Anchors = [akLeft, akTop, akRight, akBottom]
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = []
    SoftTop = True
    OnChange = tsPlatesChange
  end
  object LabelGrid: TStringGrid
    Left = 16
    Top = 16
    Width = 848
    Height = 372
    Anchors = [akLeft, akTop, akRight, akBottom]
    ColCount = 13
    DefaultRowHeight = 40
    RowCount = 9
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goEditing]
    ParentShowHint = False
    ScrollBars = ssNone
    ShowHint = True
    TabOrder = 0
    OnDrawCell = LabelGridDrawCell
    OnGetEditText = LabelGridGetEditText
    OnMouseMove = LabelGridMouseMove
    OnSelectCell = LabelGridSelectCell
    OnSetEditText = LabelGridSetEditText
  end
  object btnImport: TButton
    Left = 16
    Top = 422
    Width = 131
    Height = 38
    Anchors = [akLeft, akBottom]
    Caption = '&Importar...'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    OnClick = btnImportClick
  end
  object bRevert: TButton
    Left = 597
    Top = 422
    Width = 131
    Height = 38
    Anchors = [akRight, akBottom]
    Caption = 'Reverter'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
    OnClick = bRevertClick
  end
  object FileOpenDialog: TOpenTextFileDialog
    Filter = 
      'Todos os arquivos|*.*|Arquivo Texto (*.txt)|*.txt|Arquivo CSV (*' +
      '.csv)|*.csv'
    Left = 208
    Top = 432
  end
  object TaskDialog: TTaskDialog
    Buttons = <>
    Caption = 'Teste'
    CommonButtons = []
    DefaultButton = tcbNo
    MainIcon = 1
    RadioButtons = <>
    Text = 'Teste'
    Title = 'Importa'#231#227'o de R'#243'tulos'
    Left = 320
    Top = 432
  end
end
