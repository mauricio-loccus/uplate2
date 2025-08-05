object FrmWait: TFrmWait
  Left = 0
  Top = 0
  AutoSize = True
  BorderIcons = []
  BorderStyle = bsToolWindow
  Caption = 'Comunica'#231#227'o em curso...'
  ClientHeight = 62
  ClientWidth = 394
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsStayOnTop
  KeyPreview = True
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnClose = FormClose
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object StatusLabel: TLabel
    AlignWithMargins = True
    Left = 3
    Top = 3
    Width = 388
    Height = 33
    Align = alTop
    Alignment = taCenter
    Caption = 'Aguarde...'
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -27
    Font.Name = 'Calibri'
    Font.Style = [fsBold]
    ParentFont = False
    ExplicitWidth = 115
  end
  object pgrBar: TProgressBar
    AlignWithMargins = True
    Left = 3
    Top = 42
    Width = 388
    Height = 17
    Align = alTop
    Max = 120
    Smooth = True
    Style = pbstMarquee
    TabOrder = 0
  end
  object tmrChrono: TTimer
    Enabled = False
    OnTimer = tmrChronoTimer
    Left = 328
  end
  object tmrTimeout: TTimer
    Enabled = False
    OnTimer = tmrTimeoutTimer
    Left = 8
  end
end
