object FrmKineticStatus: TFrmKineticStatus
  AlignWithMargins = True
  Left = 0
  Top = 0
  AutoSize = True
  BorderIcons = []
  BorderStyle = bsToolWindow
  Caption = 'Cin'#233'tica'
  ClientHeight = 134
  ClientWidth = 382
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Calibri'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poMainFormCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 15
  object lbCurrentStatus: TLabel
    AlignWithMargins = True
    Left = 3
    Top = 3
    Width = 376
    Height = 46
    Align = alTop
    Alignment = taCenter
    Caption = 'Leitura 1/99'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -27
    Font.Name = 'Calibri'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
  end
  object lbTimestamp: TLabel
    AlignWithMargins = True
    Left = 3
    Top = 55
    Width = 376
    Height = 35
    Align = alTop
    Alignment = taCenter
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Calibri'
    Font.Style = []
    ParentFont = False
  end
  object btnCancel: TButton
    AlignWithMargins = True
    Left = 136
    Top = 96
    Width = 105
    Height = 35
    Cancel = True
    Caption = 'Cancelar'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Calibri'
    Font.Style = []
    ModalResult = 2
    ParentFont = False
    TabOrder = 0
    OnClick = btnCancelClick
  end
  object tmrKReadInterval: TTimer
    OnTimer = tmrKReadIntervalTimer
    Left = 320
    Top = 16
  end
end
