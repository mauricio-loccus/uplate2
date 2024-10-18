object FrmAppConfig: TFrmAppConfig
  Left = 0
  Top = 0
  BorderStyle = bsToolWindow
  Caption = 'Prefer'#234'ncias'
  ClientHeight = 431
  ClientWidth = 680
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object btnApply: TLMDMMButton
    Left = 582
    Top = 393
    Width = 90
    Height = 30
    AutoSize = False
    OnClick = btnApplyClick
    AllowMouseOver = False
    ButtonFaceStyle = sbStretch
    ButtonFaceImageList = MyDataModule.pngImageList
    ButtonFaceIndicesNew2 = {
      0000380000003800000039000000390000003800000039000000390000003800
      0000010038000000390000003900000038000000390000003900000038000000
      3800000038000000}
    ButtonFaceTransColNew = {FFFFFF1D}
  end
  object btnCancel: TLMDMMButton
    Left = 481
    Top = 393
    Width = 90
    Height = 30
    AutoSize = False
    OnClick = btnCancelClick
    AllowMouseOver = False
    ButtonFaceStyle = sbStretch
    ButtonFaceImageList = MyDataModule.pngImageList
    ButtonFaceIndicesNew2 = {
      0000360000003600000037000000370000003600000037000000370000003600
      0000010036000000370000003700000036000000370000003700000036000000
      3600000036000000}
    ButtonFaceTransColNew = {FFFFFF1D}
  end
  object pageControl: TLMDPageControl
    AlignWithMargins = True
    Left = 3
    Top = 3
    Width = 674
    Height = 384
    Hint = ''
    Align = alTop
    TabOrder = 0
    Options = [toNoTabIfEmpty, toShowBorder, toShowFocusRect, toShowAccelChar]
    DockOrientation = doNoOrient
    DefaultPage = tabCSVOptions
    ActivePage = tabCSVOptions
    object tabCSVOptions: TLMDTabSheet
      Left = 4
      Top = 27
      Width = 666
      Height = 353
      Hint = ''
      Bevel.Mode = bmCustom
      Caption = 'Op'#231#245'es CSV'
      object Label1: TLabel
        Left = 16
        Top = 16
        Width = 92
        Height = 13
        Caption = 'Separador decimal:'
      end
      object Label2: TLabel
        Left = 16
        Top = 50
        Width = 100
        Height = 13
        Caption = 'Separador de milhar:'
      end
      object teDecimalSeparator: TEdit
        Left = 122
        Top = 13
        Width = 31
        Height = 21
        MaxLength = 1
        TabOrder = 0
        OnKeyPress = teDecimalSeparatorKeyPress
      end
      object teThousandSeparator: TEdit
        Left = 122
        Top = 47
        Width = 31
        Height = 21
        MaxLength = 1
        TabOrder = 1
        OnKeyPress = teThousandSeparatorKeyPress
      end
      object chbHeadersInCsv: TCheckBox
        Left = 16
        Top = 88
        Width = 201
        Height = 17
        Caption = 'Incluir cabe'#231'alho de colunas no CSV.'
        TabOrder = 2
      end
      object chbElisaSimulated: TCheckBox
        Left = 16
        Top = 109
        Width = 257
        Height = 17
        Caption = 'Ativar simulador da leitora LMR-96 via software.'
        TabOrder = 3
      end
    end
    object tabEditUsers: TLMDTabSheet
      Left = 4
      Top = 27
      Width = 666
      Height = 353
      Hint = ''
      Bevel.Mode = bmCustom
      Caption = 'Manuten'#231#227'o dos Usu'#225'rios'
      object UserDBGrid: TDBGrid
        Left = 0
        Top = 0
        Width = 666
        Height = 329
        Align = alTop
        DataSource = DBModule.UserDataSource
        Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgCancelOnExit]
        TabOrder = 0
        TitleFont.Charset = DEFAULT_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -11
        TitleFont.Name = 'Tahoma'
        TitleFont.Style = []
        Columns = <
          item
            Expanded = False
            FieldName = 'login'
            Title.Caption = 'Login'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'name'
            Title.Caption = 'Nome'
            Width = 150
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'surname'
            Title.Caption = 'Sobrenome'
            Width = 200
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'dept'
            Title.Caption = 'Departamento'
            Width = 200
            Visible = True
          end>
      end
      object UserDBNavigator: TDBNavigator
        Left = 0
        Top = 329
        Width = 666
        Height = 25
        DataSource = DBModule.UserDataSource
        VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast, nbInsert, nbDelete, nbEdit, nbRefresh]
        Align = alTop
        ConfirmDelete = False
        TabOrder = 1
        OnClick = UserDBNavigatorClick
      end
    end
    object tabUnities: TLMDTabSheet
      Left = 4
      Top = 27
      Width = 666
      Height = 353
      Hint = ''
      Bevel.Mode = bmCustom
      Caption = 'Unidades de medida'
      object UnitiesDBGrid: TDBGrid
        Left = 0
        Top = 0
        Width = 666
        Height = 329
        Align = alTop
        DataSource = DBModule.UnitiesDataSource
        Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgCancelOnExit]
        TabOrder = 0
        TitleFont.Charset = DEFAULT_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -11
        TitleFont.Name = 'Tahoma'
        TitleFont.Style = []
        Columns = <
          item
            Expanded = False
            FieldName = 'unidade'
            Title.Caption = 'Unidade'
            Width = 150
            Visible = True
          end>
      end
      object UnitiesDBNavigator: TDBNavigator
        Left = 0
        Top = 329
        Width = 666
        Height = 25
        DataSource = DBModule.UnitiesDataSource
        VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast, nbInsert, nbDelete, nbEdit, nbRefresh]
        Align = alTop
        ConfirmDelete = False
        TabOrder = 1
        OnClick = UnitiesDBNavigatorClick
      end
    end
  end
end
