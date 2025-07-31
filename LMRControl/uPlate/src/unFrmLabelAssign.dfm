object FrmLabelAssignment: TFrmLabelAssignment
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMaximize]
  BorderStyle = bsSingle
  Caption = 'R'#243'tulos'
  ClientHeight = 478
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
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object btnClose: TButton
    Left = 726
    Top = 430
    Width = 131
    Height = 34
    Caption = 'Fechar'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
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
    OnChange = tsPlatesChange
  end
  object LabelGrid: TStringGrid
    Left = 16
    Top = 16
    Width = 848
    Height = 372
    ColCount = 13
    DefaultRowHeight = 40
    RowCount = 9
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goEditing]
    ScrollBars = ssNone
    TabOrder = 0
    OnDrawCell = LabelGridDrawCell
    OnGetEditText = LabelGridGetEditText
    OnSelectCell = LabelGridSelectCell
    OnSetEditText = LabelGridSetEditText
  end
  object btnImport: TButton
    Left = 16
    Top = 430
    Width = 131
    Height = 34
    Caption = 'Importar...'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    OnClick = btnImportClick
  end
  object Button1: TButton
    Left = 328
    Top = 440
    Width = 75
    Height = 25
    Caption = 'Button1'
    TabOrder = 4
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
    CommonButtons = [tcbYes]
    DefaultButton = tcbNo
    MainIcon = 1
    RadioButtons = <>
    Text = 'Teste'
    Title = 'Importa'#231#227'o de R'#243'tulos'
    Left = 552
    Top = 432
  end
end
