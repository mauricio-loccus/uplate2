object InputFloatValue: TInputFloatValue
  Left = 0
  Top = 0
  ActiveControl = inputEdit
  BorderStyle = bsDialog
  ClientHeight = 96
  ClientWidth = 278
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 21
    Width = 62
    Height = 13
    Caption = 'Enter value: '
  end
  object btnOK: TButton
    Left = 112
    Top = 65
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 0
    OnClick = btnOKClick
  end
  object btnCancel: TButton
    Left = 195
    Top = 65
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
  end
  object inputEdit: TLMDMaskEdit
    Left = 112
    Top = 17
    Width = 158
    Height = 21
    Hint = ''
    Bevel.Mode = bmWindows
    Caret.BlinkRate = 530
    TabOrder = 2
    ValidationMsgString = 'Valor fora dos limites permitidos (0 - 9999999.99).'
    Validator = regExprValidator
    MaxLength = 10
    AutoSelect = True
    Alignment = taRightJustify
    CustomButtons = <>
    Decimals = 2
    MaskType = meFloatFixed
    TimeSettings.AMSign = 'am'
    TimeSettings.PMSign = 'pm'
    TimeSettings.MSign = 'm'
    Value = 0.000000000000000000
  end
  object regExprValidator: TLMDRegExpValidator
    ValidateOnFocus = False
    ValidateOnLostFocus = False
    ErrorProvider = hintErrorProvider
    ErrorMessage = 'Valor fora dos limites permitidos (0 - 9999999.99).'
    Expression = '^\(?([0-9]{0,7}(\,?[0-9]{2})*(\.?[0-9]*))\)?$'
    IgnoreCase = True
    Left = 8
    Top = 48
  end
  object hintErrorProvider: TLMDHintErrorProvider
    MessageHint.TitleFont.Charset = DEFAULT_CHARSET
    MessageHint.TitleFont.Color = clInfoText
    MessageHint.TitleFont.Height = -13
    MessageHint.TitleFont.Name = 'Arial'
    MessageHint.TitleFont.Style = []
    MessageHint.AllowMultipleHints = False
    MessageHint.Options = []
    Left = 72
    Top = 16
  end
end
