object FrmFiltersEdit: TFrmFiltersEdit
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'Configura'#231#227'o dos Filtros'
  ClientHeight = 253
  ClientWidth = 288
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Calibri'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 15
  object filtersEditGrid: TLMDGrid
    Left = 8
    Top = 8
    Width = 191
    Height = 237
    Style.EmptyBannerFont.Charset = DEFAULT_CHARSET
    Style.EmptyBannerFont.Color = clWindowText
    Style.EmptyBannerFont.Height = -11
    Style.EmptyBannerFont.Name = 'Tahoma'
    Style.EmptyBannerFont.Style = []
    Options = [opHeaderVertLine, opIndicatorHorzLine, opVertLine, opHorzLine, opDrawFocusSelected, opEditing, opThumbTracking, opShowHeader, opConfirmDeleteRow, opCancelOnExit, opHighlightHeaders, opShowColumnsChooser]
    TabOrder = 0
    object colFilterNumber: TLMDGridTextColumn
      Position = 0
      SortingAllowed = False
      Title.Caption = 'Filtro #'
      ReadOnly = True
    end
    object colFilterValue: TLMDGridFloatColumn
      Width = 135
      Position = 1
      SortingAllowed = False
      Alignment = taCenter
      Title.Caption = 'Comprimento de Onda'
      Precision = 0
      FloatFormat = '####0'
      IsCurrencyMode = False
      OnFormatEdit = colFilterValueFormatPaint
      OnFormatPaint = colFilterValueFormatPaint
      OnParse = colFilterValueParse
      ChooserData = <
        item
          ChooserName = 'CalculatorChooser'
        end>
    end
  end
  object btnSave: TButton
    Left = 205
    Top = 8
    Width = 75
    Height = 25
    Caption = '&Salvar'
    Default = True
    ModalResult = 1
    TabOrder = 1
  end
  object btnCancel: TButton
    Left = 205
    Top = 48
    Width = 75
    Height = 25
    Cancel = True
    Caption = '&Cancelar'
    ModalResult = 2
    TabOrder = 2
  end
end
