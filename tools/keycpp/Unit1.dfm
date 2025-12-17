object WindowList: TWindowList
  Left = 0
  Top = 0
  Caption = 'Window Selection'
  ClientHeight = 319
  ClientWidth = 744
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -15
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu
  OldCreateOrder = False
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 18
  object Panel1: TPanel
    Left = 0
    Top = 258
    Width = 744
    Height = 61
    Align = alBottom
    BevelEdges = []
    TabOrder = 0
    VerticalAlignment = taAlignBottom
    ExplicitTop = 432
    ExplicitWidth = 741
    DesignSize = (
      744
      61)
    object Label1: TLabel
      Left = 207
      Top = 19
      Width = 252
      Height = 18
      Alignment = taCenter
      Anchors = [akLeft, akBottom]
      Caption = 'segundos para atualiza'#231#227'o autom'#225'tica'
    end
    object bUpdate: TButton
      Left = 16
      Top = 16
      Width = 121
      Height = 29
      Anchors = [akLeft, akBottom]
      Caption = 'Atualizar'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
    end
    object seInterval: TSpinEdit
      Left = 143
      Top = 16
      Width = 50
      Height = 29
      Anchors = [akLeft, akBottom]
      Ctl3D = True
      MaxLength = 2
      MaxValue = 90
      MinValue = 0
      ParentCtl3D = False
      TabOrder = 1
      Value = 15
    end
  end
  object pWindowsList: TPanel
    Left = 0
    Top = 0
    Width = 744
    Height = 258
    Align = alClient
    TabOrder = 1
    ExplicitLeft = 40
    ExplicitTop = 48
    ExplicitWidth = 185
    ExplicitHeight = 41
    DesignSize = (
      744
      258)
    object lvWindowsList: TGestureListView
      Left = 16
      Top = 16
      Width = 712
      Height = 225
      Anchors = [akLeft, akTop, akRight, akBottom]
      Columns = <
        item
          AutoSize = True
          Caption = 'Name'
        end>
      ImageSize = 24
      TabOrder = 0
    end
  end
  object Timer: TTimer
    Enabled = False
    OnTimer = TimerTimer
    Left = 552
    Top = 272
  end
  object MainMenu: TMainMenu
    Left = 600
    Top = 272
    object Opes1: TMenuItem
      Caption = '&Op'#231#245'es'
      object mExit: TMenuItem
        Caption = '&Sair'
        ShortCut = 16472
        OnClick = mExitClick
      end
    end
  end
end
