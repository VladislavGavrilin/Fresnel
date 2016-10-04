object plot: Tplot
  Left = 0
  Top = 0
  Width = 710
  Height = 536
  TabOrder = 0
  object chart: TChart
    Left = 0
    Top = 169
    Width = 710
    Height = 367
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Foot.Visible = False
    MarginBottom = 1
    MarginLeft = 1
    MarginRight = 2
    MarginTop = 3
    Title.Text.Strings = (
      'TChart')
    Title.Visible = False
    Legend.LegendStyle = lsSeries
    View3D = False
    Align = alClient
    TabOrder = 0
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 710
    Height = 169
    Align = alTop
    TabOrder = 1
    object Label1: TLabel
      Left = 163
      Top = 16
      Width = 80
      Height = 13
      Caption = #1044#1086#1087#1086#1083#1085#1080#1090#1077#1083#1100#1085#1086
    end
    object Label2: TLabel
      Left = 295
      Top = 63
      Width = 49
      Height = 13
      Caption = #1058#1086#1083#1097#1080#1085#1072':'
    end
    object Label3: TLabel
      Left = 298
      Top = 91
      Width = 47
      Height = 13
      Caption = #1052#1080#1085'. '#1044#1053':'
    end
    object Label4: TLabel
      Left = 433
      Top = 104
      Width = 175
      Height = 13
      Caption = #1054#1090#1085#1086#1089#1080#1090'. '#1091#1088'. '#1074#1086#1089#1089#1090'. '#1089#1077#1095#1077#1085#1080#1103', '#1044#1041':   '
    end
    object Label5: TLabel
      Left = 433
      Top = 124
      Width = 209
      Height = 13
      Caption = #1055#1086#1083#1086#1078#1077#1085#1080#1077' '#1094#1077#1085#1090#1088#1072' '#1072#1087#1077#1088#1090'. '#1087#1086' '#1074#1077#1088#1090'., '#1084#1084':   '
    end
    object Label6: TLabel
      Left = 433
      Top = 144
      Width = 203
      Height = 13
      Caption = #1055#1086#1083#1086#1078#1077#1085#1080#1077' '#1094#1077#1085#1090#1088#1072' '#1072#1087#1077#1088#1090'. '#1087#1086' '#1075#1086#1088'., '#1084#1084':   '
    end
    object maxRP: TLabel
      Left = 649
      Top = 104
      Width = 34
      Height = 13
      Caption = 'maxRP'
    end
    object shiftVert: TLabel
      Left = 649
      Top = 124
      Width = 38
      Height = 13
      Caption = 'shiftVert'
    end
    object shiftHor: TLabel
      Left = 649
      Top = 144
      Width = 36
      Height = 13
      Caption = 'shiftHor'
    end
    object rpInputChangeIndicator: TLabel
      Left = 280
      Top = 6
      Width = 152
      Height = 13
      Caption = #1042#1093#1086#1076#1085#1099#1077' '#1076#1072#1085#1085#1099#1077' '#1080#1079#1084#1077#1085#1077#1085#1099'!   '
    end
    object listPhase: TCheckListBox
      Left = 16
      Top = 32
      Width = 121
      Height = 125
      OnClickCheck = listPhaseClickCheck
      ItemHeight = 13
      TabOrder = 9
      Visible = False
      OnClick = listPhaseClick
    end
    object listAmp: TCheckListBox
      Left = 16
      Top = 32
      Width = 121
      Height = 125
      OnClickCheck = listAmpClickCheck
      ItemHeight = 13
      TabOrder = 0
      OnClick = listAmpClick
    end
    object radioAmp: TRadioButton
      Left = 9
      Top = 13
      Width = 85
      Height = 17
      Caption = #1040#1084#1087#1083#1080#1090#1091#1076#1072
      Checked = True
      TabOrder = 1
      TabStop = True
      OnClick = radioClick
    end
    object radioPhase: TRadioButton
      Left = 96
      Top = 13
      Width = 57
      Height = 17
      Caption = #1060#1072#1079#1072
      TabOrder = 2
      OnClick = radioClick
    end
    object listExt: TCheckListBox
      Left = 160
      Top = 32
      Width = 121
      Height = 125
      OnClickCheck = listExtClickCheck
      ItemHeight = 13
      TabOrder = 3
      OnClick = listExtClick
    end
    object colorBox: TColorBox
      Left = 295
      Top = 24
      Width = 121
      Height = 22
      Style = [cbStandardColors, cbExtendedColors, cbCustomColor, cbPrettyNames]
      ItemHeight = 16
      TabOrder = 4
      OnChange = colorBoxChange
    end
    object lineWidth: TCSpinEdit
      Left = 367
      Top = 58
      Width = 49
      Height = 22
      MaxValue = 10
      MinValue = 1
      TabOrder = 5
      Value = 1
      OnChange = lineWidthChange
    end
    object minRP: TCSpinEdit
      Left = 367
      Top = 87
      Width = 49
      Height = 22
      MaxValue = 10
      MinValue = -100
      TabOrder = 6
      Value = -40
      OnChange = PlotSettingsChange
    end
    object phaseStraight: TCheckBox
      Left = 295
      Top = 116
      Width = 137
      Height = 17
      Caption = #1074#1099#1087#1088#1103#1084#1083#1077#1085#1080#1077' '#1092#1072#1079#1099
      TabOrder = 7
      OnClick = PlotSettingsChange
    end
    object normRP: TCheckBox
      Left = 295
      Top = 141
      Width = 129
      Height = 17
      Caption = #1085#1086#1088#1084#1080#1088#1086#1074#1072#1085#1080#1077' '#1044#1053
      TabOrder = 8
      OnClick = PlotSettingsChange
    end
    object addExtButton: TButton
      Left = 433
      Top = 24
      Width = 113
      Height = 25
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1075#1088#1072#1092#1080#1082
      TabOrder = 10
      OnClick = addExtButtonClick
    end
    object removeExtButton: TButton
      Left = 433
      Top = 60
      Width = 113
      Height = 25
      Caption = #1059#1076#1072#1083#1080#1090#1100' '#1075#1088#1072#1092#1080#1082
      TabOrder = 11
      OnClick = removeExtButtonClick
    end
    object saveAmp: TButton
      Left = 561
      Top = 24
      Width = 137
      Height = 25
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1072#1084#1087#1083#1080#1090#1091#1076#1091
      TabOrder = 12
      OnClick = saveAmpClick
    end
    object savePhase: TButton
      Left = 561
      Top = 60
      Width = 137
      Height = 25
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1092#1072#1079#1091
      TabOrder = 13
      OnClick = savePhaseClick
    end
  end
  object extDataDialog: TOpenDialog
    Filter = #1060#1072#1081#1083#1099' '#1076#1072#1085#1085#1099#1093' (*.dat, *.bln)|*.bln; *.dat|'#1042#1089#1077' '#1092#1072#1081#1083#1099'|*.*'
    Left = 280
    Top = 40
  end
end
