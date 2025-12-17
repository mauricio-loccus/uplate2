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
    DesignSize = (
      744
      61)
    object Label1: TLabel
      Left = 207
      Top = 19
      Width = 249
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
      OnClick = bUpdateClick
    end
    object seInterval: TSpinEdit
      Left = 143
      Top = 16
      Width = 50
      Height = 28
      Anchors = [akLeft, akBottom]
      Ctl3D = True
      MaxLength = 2
      MaxValue = 90
      MinValue = 0
      ParentCtl3D = False
      TabOrder = 1
      Value = 15
      OnChange = seIntervalChange
      OnEnter = seIntervalEnter
    end
  end
  object pWindowsList: TPanel
    Left = 0
    Top = 0
    Width = 744
    Height = 258
    Align = alClient
    TabOrder = 1
    object lvWindowsList: TListView
      Left = 16
      Top = 16
      Width = 712
      Height = 225
      Align = alCustom
      Anchors = [akLeft, akTop, akRight, akBottom]
      Columns = <
        item
          Caption = 'Caption'
          Width = 440
        end
        item
          Caption = 'Process'
          Width = 300
        end
        item
          Alignment = taRightJustify
          Caption = 'Timestamp'
          Width = 200
        end
        item
          Alignment = taRightJustify
          Caption = 'Handle'
          Width = 110
        end>
      RowSelect = True
      TabOrder = 0
      ViewStyle = vsReport
      OnAdvancedCustomDrawItem = lvWindowsListAdvancedCustomDrawItem
      OnCustomDrawSubItem = lvWindowsListCustomDrawSubItem
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
