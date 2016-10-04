object Form1: TForm1
  Left = 115
  Top = 0
  Width = 890
  Height = 909
  Caption = 'Fresnel'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 122
  TextHeight = 16
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 882
    Height = 868
    ActivePage = TabPrepare
    Align = alClient
    Style = tsFlatButtons
    TabIndex = 0
    TabOrder = 0
    TabStop = False
    object TabPrepare: TTabSheet
      Caption = #1055#1086#1076#1075#1086#1090#1086#1074#1082#1072
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      object Label27: TLabel
        Left = 133
        Top = 742
        Width = 367
        Height = 14
        Caption = #1047#1072#1084#1077#1095#1072#1085#1080#1077': '#1077#1089#1083#1080' '#1096#1072#1075' '#1080#1079#1084#1077#1088#1077#1085#1080#1081' '#1074#1074#1077#1076#1105#1085' '#1074#1088#1091#1095#1085#1091#1102', '#1090#1086' '#1074#1086' '#1074#1082#1083#1072#1076#1082#1091
      end
      object Label28: TLabel
        Left = 133
        Top = 772
        Width = 312
        Height = 14
        Caption = '"'#1042#1086#1089#1089#1090#1072#1085#1086#1074#1083#1077#1085#1080#1077'" '#1087#1077#1088#1077#1085#1086#1089#1080#1090#1089#1103' '#1080#1084#1077#1085#1085#1086' '#1101#1090#1086' '#1079#1085#1072#1095#1077#1085#1080#1077'.'
      end
      object Label29: TLabel
        Left = 133
        Top = 806
        Width = 434
        Height = 14
        Caption = 
          #1045#1089#1083#1080' '#1096#1072#1075' '#1080#1079#1084#1077#1088#1077#1085#1080#1081' '#1085#1077' '#1074#1074#1077#1076#1105#1085', '#1090#1086' '#1080#1089#1087#1086#1083#1100#1079#1091#1077#1090#1089#1103' '#1088#1072#1089#1095#1105#1090#1085#1086#1077' '#1079#1085#1072#1095#1077#1085#1080#1077 +
          ' '#1096#1072#1075#1072'.'
      end
      object GroupBox1: TGroupBox
        Left = 148
        Top = 49
        Width = 513
        Height = 277
        Caption = #1042#1093#1086#1076#1085#1099#1077' '#1087#1072#1088#1072#1084#1077#1090#1088#1099
        TabOrder = 0
        object Label2: TLabel
          Left = 39
          Top = 39
          Width = 138
          Height = 14
          Caption = #1063#1072#1089#1090#1086#1090#1072' '#1080#1079#1084#1077#1088#1077#1085#1080#1103', '#1043#1043#1094
        end
        object Label3: TLabel
          Left = 39
          Top = 76
          Width = 207
          Height = 14
          Caption = #1042#1077#1088#1090#1080#1082#1072#1083#1100#1085#1099#1081' '#1088#1072#1079#1084#1077#1088' '#1072#1087#1077#1088#1090#1091#1088#1099', '#1084#1084
        end
        object Label4: TLabel
          Left = 39
          Top = 113
          Width = 219
          Height = 14
          Caption = #1043#1086#1088#1080#1079#1086#1085#1090#1072#1083#1100#1085#1099#1081' '#1088#1072#1079#1084#1077#1088' '#1072#1087#1077#1088#1090#1091#1088#1099', '#1084#1084
        end
        object Label5: TLabel
          Left = 39
          Top = 150
          Width = 113
          Height = 14
          Caption = #1057#1077#1082#1090#1086#1088' '#1044#1053', '#1075#1088#1072#1076#1091#1089#1099
        end
        object Label6: TLabel
          Left = 39
          Top = 187
          Width = 143
          Height = 14
          Caption = #1044#1080#1089#1090#1072#1085#1094#1080#1103' '#1080#1079#1084#1077#1088#1077#1085#1080#1103', '#1084
        end
        object EditFreq: TEdit
          Left = 305
          Top = 34
          Width = 149
          Height = 21
          TabOrder = 0
          Text = '6.25'
          OnChange = prepInputChanged
        end
        object EditHVert: TEdit
          Left = 305
          Top = 71
          Width = 149
          Height = 21
          TabOrder = 1
          Text = '2500'
          OnChange = prepInputChanged
        end
        object EditHHor: TEdit
          Left = 305
          Top = 110
          Width = 149
          Height = 21
          TabOrder = 2
          Text = '2500'
          OnChange = prepInputChanged
        end
        object EditResultSector: TEdit
          Left = 305
          Top = 148
          Width = 149
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 3
          Text = '60'
          OnChange = prepInputChanged
        end
        object EditR: TEdit
          Left = 305
          Top = 186
          Width = 149
          Height = 21
          TabOrder = 4
          Text = '76'
          OnChange = prepInputChanged
        end
        object Button1: TButton
          Left = 207
          Top = 231
          Width = 92
          Height = 31
          Caption = #1055#1088#1080#1084#1077#1085#1080#1090#1100
          TabOrder = 5
          OnClick = Button1Click
        end
      end
      object GroupBox2: TGroupBox
        Left = 59
        Top = 399
        Width = 710
        Height = 223
        Caption = #1042#1099#1093#1086#1076#1085#1099#1077' '#1087#1072#1088#1072#1084#1077#1090#1088#1099
        TabOrder = 1
        object Label7: TLabel
          Left = 39
          Top = 69
          Width = 223
          Height = 14
          Caption = #1064#1072#1075' '#1080#1079#1084#1077#1088#1077#1085#1080#1081' '#1087#1086' '#1091#1075#1083#1091' '#1084#1077#1089#1090#1072', '#1075#1088#1072#1076#1091#1089#1099
        end
        object Label8: TLabel
          Left = 39
          Top = 106
          Width = 119
          Height = 14
          Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1089#1077#1095#1077#1085#1080#1081
        end
        object Label9: TLabel
          Left = 39
          Top = 143
          Width = 159
          Height = 14
          Caption = #1057#1077#1082#1090#1086#1088' '#1080#1079#1084#1077#1088#1077#1085#1080#1103', '#1075#1088#1072#1076#1091#1089#1099
        end
        object Label14: TLabel
          Left = 305
          Top = 41
          Width = 61
          Height = 14
          Caption = #1056#1072#1089#1095#1105#1090#1085#1099#1077
        end
        object Label15: TLabel
          Left = 512
          Top = 41
          Width = 79
          Height = 14
          Caption = #1042#1074#1086#1076' '#1074#1088#1091#1095#1085#1091#1102
        end
        object EditStep: TEdit
          Left = 305
          Top = 64
          Width = 149
          Height = 21
          TabStop = False
          ReadOnly = True
          TabOrder = 0
        end
        object EditNOfSec: TEdit
          Left = 305
          Top = 101
          Width = 149
          Height = 21
          TabStop = False
          ReadOnly = True
          TabOrder = 1
        end
        object EditMeasSector: TEdit
          Left = 305
          Top = 139
          Width = 149
          Height = 21
          TabStop = False
          ReadOnly = True
          TabOrder = 2
        end
        object EditStepMan: TEdit
          Left = 512
          Top = 64
          Width = 149
          Height = 21
          TabOrder = 3
          OnChange = prepInputChanged
        end
        object EditNOfSecMan: TEdit
          Left = 512
          Top = 101
          Width = 149
          Height = 21
          TabStop = False
          ReadOnly = True
          TabOrder = 4
        end
        object Button2: TButton
          Left = 542
          Top = 151
          Width = 92
          Height = 31
          Caption = #1055#1088#1086#1074#1077#1088#1080#1090#1100
          TabOrder = 5
          OnClick = Button2Click
        end
      end
      object Button3: TButton
        Left = 217
        Top = 645
        Width = 424
        Height = 31
        Caption = #1055#1077#1088#1077#1081#1090#1080' '#1082' '#1074#1086#1089#1089#1090#1072#1085#1086#1074#1083#1077#1085#1080#1102' '#1089' '#1087#1077#1088#1077#1085#1086#1089#1086#1084' '#1079#1085#1072#1095#1077#1085#1080#1081' '#1087#1072#1088#1072#1084#1077#1090#1088#1086#1074
        TabOrder = 2
        OnClick = Button3Click
      end
    end
    object TabObrDn: TTabSheet
      Caption = 'OBR DN'
      ImageIndex = 1
      object Label1: TLabel
        Left = 59
        Top = 44
        Width = 285
        Height = 16
        Caption = #1042#1099#1073#1077#1088#1080#1090#1077' '#1090#1080#1087' '#1082#1072#1083#1080#1073#1088#1086#1074#1082#1080' '#1074#1093#1086#1076#1085#1099#1093' '#1092#1072#1081#1083#1086#1074':'
      end
      object RadioDAT: TRadioButton
        Left = 59
        Top = 84
        Width = 257
        Height = 21
        Caption = 'DAT ('#1085#1077' '#1082#1072#1083#1080#1073#1088#1086#1074#1072#1085#1085#1099#1077')'
        TabOrder = 0
        OnClick = RadioBLNClick
      end
      object RadioBLN: TRadioButton
        Left = 59
        Top = 122
        Width = 257
        Height = 21
        Caption = 'BLN ('#1082#1072#1083#1080#1073#1088#1086#1074#1072#1085#1085#1099#1077' '#1087#1086#1089#1083#1077' OBR_DN)'
        Checked = True
        TabOrder = 1
        TabStop = True
        OnClick = RadioBLNClick
      end
      object BoxDatBln: TGroupBox
        Left = 148
        Top = 315
        Width = 602
        Height = 218
        Caption = #1050#1072#1083#1080#1073#1088#1086#1074#1086#1095#1085#1099#1077' '#1092#1072#1081#1083#1099
        TabOrder = 2
        Visible = False
        object Label21: TLabel
          Left = 30
          Top = 43
          Width = 219
          Height = 16
          Caption = #1060#1072#1081#1083' '#1072#1084#1087#1083#1080#1090#1091#1076#1085#1086#1081' '#1082#1072#1083#1080#1073#1088#1086#1074#1082#1080':   '
        end
        object Label22: TLabel
          Left = 30
          Top = 112
          Width = 190
          Height = 16
          Caption = #1060#1072#1081#1083' '#1092#1072#1079#1086#1074#1086#1081' '#1082#1072#1083#1080#1073#1088#1086#1074#1082#1080':   '
        end
        object calibrAmpEdit: TEdit
          Left = 30
          Top = 69
          Width = 424
          Height = 21
          ReadOnly = True
          TabOrder = 0
          OnChange = rpInputChanged
        end
        object ButtonAmpCal: TButton
          Left = 482
          Top = 69
          Width = 80
          Height = 31
          Caption = #1054#1073#1079#1086#1088'...'
          TabOrder = 1
          OnClick = ButtonAmpCalClick
        end
        object ButtonPhaseCal: TButton
          Left = 482
          Top = 138
          Width = 80
          Height = 31
          Caption = #1054#1073#1079#1086#1088'...'
          TabOrder = 2
          OnClick = ButtonPhaseCalClick
        end
        object calibrPhaseEdit: TEdit
          Left = 30
          Top = 138
          Width = 424
          Height = 21
          ReadOnly = True
          TabOrder = 3
          OnChange = rpInputChanged
        end
      end
    end
    object TabMain: TTabSheet
      Caption = #1042#1086#1089#1089#1090#1072#1085#1086#1074#1083#1077#1085#1080#1077
      ImageIndex = 2
      DesignSize = (
        874
        834)
      object Label19: TLabel
        Left = 37
        Top = 11
        Width = 225
        Height = 16
        Caption = #1060#1072#1081#1083#1099' '#1089' '#1080#1079#1084#1077#1088#1077#1085#1080#1103#1084#1080' '#1072#1084#1087#1083#1080#1090#1091#1076#1099':'
      end
      object Label20: TLabel
        Left = 37
        Top = 258
        Width = 188
        Height = 16
        Caption = #1060#1072#1081#1083#1099' '#1089' '#1080#1079#1084#1077#1088#1077#1085#1080#1103#1084#1080' '#1092#1072#1079#1099':'
      end
      object Label10: TLabel
        Left = 37
        Top = 519
        Width = 158
        Height = 16
        Caption = #1063#1072#1089#1090#1086#1090#1072' '#1080#1079#1084#1077#1088#1077#1085#1080#1081', '#1043#1043#1094
      end
      object Label11: TLabel
        Left = 37
        Top = 602
        Width = 253
        Height = 16
        Caption = #1043#1086#1088#1080#1079#1086#1085#1090#1072#1083#1100#1085#1099#1081' '#1088#1072#1079#1084#1077#1088' '#1072#1087#1077#1088#1090#1091#1088#1099', '#1084#1084
      end
      object Label12: TLabel
        Left = 37
        Top = 560
        Width = 238
        Height = 16
        Caption = #1042#1077#1088#1090#1080#1082#1072#1083#1100#1085#1099#1081' '#1088#1072#1079#1084#1077#1088' '#1072#1087#1077#1088#1090#1091#1088#1099', '#1084#1084
      end
      object Label13: TLabel
        Left = 37
        Top = 644
        Width = 160
        Height = 16
        Caption = #1044#1080#1089#1090#1072#1085#1094#1080#1103' '#1080#1079#1084#1077#1088#1077#1085#1080#1103', '#1084
      end
      object Label16: TLabel
        Left = 441
        Top = 519
        Width = 276
        Height = 16
        Caption = #1042#1077#1088#1090#1080#1082#1072#1083#1100#1085#1099#1081' '#1089#1076#1074#1080#1075' '#1094#1077#1085#1090#1088#1072' '#1072#1087#1077#1088#1090#1091#1088#1099', '#1084#1084
      end
      object Label17: TLabel
        Left = 441
        Top = 560
        Width = 330
        Height = 16
        Caption = #1055#1086#1083#1086#1074#1080#1085#1072' '#1076#1080#1072#1087'. '#1074#1077#1088#1090'. '#1089#1076#1074#1080#1075#1072' '#1094#1077#1085#1090#1088#1072' '#1072#1087#1077#1088#1090#1091#1088#1099', '#1084#1084
      end
      object Label18: TLabel
        Left = 441
        Top = 726
        Width = 219
        Height = 16
        Caption = #1055#1086#1083#1086#1074#1080#1085#1072' '#1095#1080#1089#1083#1072' '#1082#1086#1101#1092#1092#1080#1094#1080#1077#1085#1090#1086#1074
      end
      object Label23: TLabel
        Left = 37
        Top = 684
        Width = 218
        Height = 16
        Caption = #1064#1072#1075' '#1080#1079#1084#1077#1088#1077#1085#1080#1081' '#1087#1086' '#1072#1079#1080#1084#1091#1090#1091', '#1075#1088#1072#1076'.'
      end
      object Label24: TLabel
        Left = 37
        Top = 726
        Width = 234
        Height = 16
        Caption = #1064#1072#1075' '#1080#1079#1084#1077#1088#1077#1085#1080#1081' '#1087#1086' '#1091#1075#1083#1091' '#1084#1077#1089#1090#1072', '#1075#1088#1072#1076'.'
      end
      object Label25: TLabel
        Left = 37
        Top = 768
        Width = 265
        Height = 16
        Caption = #1064#1072#1075' '#1075#1088#1072#1092#1080#1082#1072' '#1074#1086#1089#1089#1090#1072#1085#1086#1074#1083#1077#1085#1085#1086#1081' '#1044#1053', '#1075#1088#1072#1076'.'
      end
      object Label30: TLabel
        Left = 441
        Top = 642
        Width = 321
        Height = 16
        Caption = #1055#1086#1083#1086#1074#1080#1085#1072' '#1076#1080#1072#1087'. '#1075#1086#1088'. '#1089#1076#1074#1080#1075#1072' '#1094#1077#1085#1090#1088#1072' '#1072#1087#1077#1088#1090#1091#1088#1099', '#1084#1084
      end
      object Label31: TLabel
        Left = 441
        Top = 602
        Width = 291
        Height = 16
        Caption = #1043#1086#1088#1080#1079#1086#1085#1090#1072#1083#1100#1085#1099#1081' '#1089#1076#1074#1080#1075' '#1094#1077#1085#1090#1088#1072' '#1072#1087#1077#1088#1090#1091#1088#1099', '#1084#1084
      end
      object Label32: TLabel
        Left = 441
        Top = 684
        Width = 242
        Height = 16
        Caption = #1064#1072#1075' '#1076#1083#1103' '#1087#1086#1080#1089#1082#1072' '#1092#1072#1079#1086#1074#1086#1075#1086' '#1094#1077#1085#1090#1088#1072', '#1084#1084
      end
      object sg_amp: TStringGrid
        Left = 37
        Top = 34
        Width = 671
        Height = 212
        Anchors = [akLeft, akTop, akRight]
        ColCount = 3
        DefaultRowHeight = 20
        RowCount = 2
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goRowMoving, goEditing]
        TabOrder = 0
        ColWidths = (
          25
          308
          176)
        RowHeights = (
          20
          20)
      end
      object sg_phase: TStringGrid
        Left = 37
        Top = 282
        Width = 671
        Height = 212
        Anchors = [akLeft, akTop, akRight]
        ColCount = 3
        DefaultRowHeight = 20
        RowCount = 2
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goRowMoving, goEditing, goRowSelect]
        TabOrder = 1
        ColWidths = (
          25
          309
          179)
        RowHeights = (
          20
          20)
      end
      object ButtonAddAmp: TButton
        Left = 745
        Top = 34
        Width = 105
        Height = 29
        Anchors = [akTop, akRight]
        Caption = #1044#1086#1073#1072#1074#1080#1090#1100
        TabOrder = 2
        OnClick = ButtonAddAmpClick
      end
      object ButtonDelAmp: TButton
        Left = 745
        Top = 79
        Width = 105
        Height = 28
        Anchors = [akTop, akRight]
        Caption = #1059#1076#1072#1083#1080#1090#1100
        TabOrder = 3
        OnClick = ButtonDelAmpClick
      end
      object ButtonAddPh: TButton
        Left = 745
        Top = 282
        Width = 105
        Height = 29
        Anchors = [akTop, akRight]
        Caption = #1044#1086#1073#1072#1074#1080#1090#1100
        TabOrder = 5
        OnClick = ButtonAddPhClick
      end
      object ButtonDelPh: TButton
        Left = 745
        Top = 327
        Width = 105
        Height = 29
        Anchors = [akTop, akRight]
        Caption = #1059#1076#1072#1083#1080#1090#1100
        TabOrder = 6
        OnClick = ButtonDelPhClick
      end
      object ButtonGo: TButton
        Left = 409
        Top = 809
        Width = 92
        Height = 30
        Caption = #1056#1072#1089#1095#1105#1090
        TabOrder = 8
        OnClick = ButtonGoClick
      end
      object Button4: TButton
        Left = 745
        Top = 123
        Width = 105
        Height = 31
        Anchors = [akTop, akRight]
        Caption = #1057#1086#1088#1090#1080#1088#1086#1074#1072#1090#1100
        TabOrder = 4
        OnClick = Button4Click
      end
      object Button5: TButton
        Left = 745
        Top = 370
        Width = 105
        Height = 31
        Anchors = [akTop, akRight]
        Caption = #1057#1086#1088#1090#1080#1088#1086#1074#1072#1090#1100
        TabOrder = 7
        OnClick = Button5Click
      end
      object Edit2: TEdit
        Left = 332
        Top = 512
        Width = 74
        Height = 21
        TabOrder = 9
        Text = 'Edit2'
        OnChange = rpInputChanged
      end
      object Edit3: TEdit
        Left = 332
        Top = 554
        Width = 74
        Height = 21
        TabOrder = 10
        Text = 'Edit3'
        OnChange = rpInputChanged
      end
      object Edit4: TEdit
        Left = 332
        Top = 597
        Width = 74
        Height = 21
        TabOrder = 11
        Text = 'Edit4'
        OnChange = rpInputChanged
      end
      object Edit5: TEdit
        Left = 332
        Top = 640
        Width = 74
        Height = 21
        TabOrder = 12
        Text = 'Edit5'
        OnChange = rpInputChanged
      end
      object Edit6: TEdit
        Left = 332
        Top = 682
        Width = 74
        Height = 21
        TabOrder = 13
        Text = 'Edit6'
        OnChange = rpInputChanged
      end
      object Edit7: TEdit
        Left = 332
        Top = 725
        Width = 74
        Height = 21
        TabOrder = 14
        Text = 'Edit7'
        OnChange = rpInputChanged
      end
      object Edit8: TEdit
        Left = 332
        Top = 768
        Width = 74
        Height = 21
        TabOrder = 15
        Text = 'Edit8'
        OnChange = rpInputChanged
      end
      object Edit9: TEdit
        Left = 785
        Top = 512
        Width = 74
        Height = 21
        TabOrder = 16
        Text = 'Edit9'
        OnChange = rpInputChanged
      end
      object Edit10: TEdit
        Left = 785
        Top = 554
        Width = 74
        Height = 21
        TabOrder = 17
        Text = 'Edit10'
        OnChange = rpInputChanged
      end
      object Edit11: TEdit
        Left = 785
        Top = 597
        Width = 74
        Height = 21
        TabOrder = 18
        Text = 'Edit11'
        OnChange = rpInputChanged
      end
      object Edit12: TEdit
        Left = 785
        Top = 640
        Width = 74
        Height = 21
        TabOrder = 19
        Text = 'Edit12'
        OnChange = rpInputChanged
      end
      object Edit13: TEdit
        Left = 785
        Top = 682
        Width = 74
        Height = 21
        TabOrder = 20
        Text = 'Edit13'
        OnChange = rpInputChanged
      end
      object Edit14: TEdit
        Left = 785
        Top = 725
        Width = 74
        Height = 21
        TabOrder = 21
        Text = 'Edit14'
        OnChange = rpInputChanged
      end
      object Button6: TButton
        Left = 739
        Top = 463
        Width = 120
        Height = 31
        Anchors = [akTop, akRight]
        Caption = #1059#1076#1072#1083#1080#1090#1100' '#1074#1089#1105
        TabOrder = 22
        OnClick = Button6Click
      end
    end
    object TabResult: TTabSheet
      Caption = #1056#1077#1079#1091#1083#1100#1090#1072#1090
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = []
      ImageIndex = 3
      ParentFont = False
      inline plot1: Tplot
        Left = 0
        Top = 0
        Width = 874
        Height = 834
        Align = alClient
        TabOrder = 0
        inherited chart: TChart
          Top = 208
          Width = 874
          Height = 626
          BottomAxis.ExactDateTime = False
          BottomAxis.Increment = 0.1
          LeftAxis.ExactDateTime = False
          LeftAxis.Increment = 0.1
          RightAxis.LabelsSeparation = 3
        end
        inherited Panel1: TPanel
          Width = 874
          Height = 208
          inherited Label1: TLabel
            Left = 201
            Top = 20
            Width = 112
            Height = 14
            Caption = #1044#1086#1087#1086#1083#1085#1080#1090'. '#1075#1088#1072#1092#1080#1082#1080
          end
          inherited Label2: TLabel
            Left = 363
            Top = 78
            Width = 55
            Height = 14
          end
          inherited Label3: TLabel
            Left = 367
            Top = 112
            Width = 51
            Height = 14
          end
          inherited Label4: TLabel
            Left = 533
            Top = 128
            Width = 203
            Height = 14
          end
          inherited Label5: TLabel
            Left = 533
            Top = 153
            Width = 244
            Height = 14
          end
          inherited Label6: TLabel
            Left = 533
            Top = 177
            Width = 237
            Height = 14
          end
          inherited maxRP: TLabel
            Left = 838
            Top = 128
            Width = 36
            Height = 14
          end
          inherited shiftVert: TLabel
            Left = 838
            Top = 153
            Height = 14
          end
          inherited shiftHor: TLabel
            Left = 838
            Top = 177
            Width = 42
            Height = 14
          end
          inherited rpInputChangeIndicator: TLabel
            Left = 345
            Top = 7
            Width = 171
            Height = 14
          end
          inherited listPhase: TCheckListBox
            Left = 20
            Top = 39
            Width = 149
            Height = 154
            ItemHeight = 14
          end
          inherited listAmp: TCheckListBox
            Left = 20
            Top = 39
            Width = 149
            Height = 154
            ItemHeight = 14
          end
          inherited radioAmp: TRadioButton
            Left = 11
            Top = 16
            Width = 105
            Height = 21
          end
          inherited radioPhase: TRadioButton
            Left = 118
            Top = 16
            Width = 70
            Height = 21
          end
          inherited listExt: TCheckListBox
            Left = 197
            Top = 39
            Width = 149
            Height = 154
            ItemHeight = 14
          end
          inherited colorBox: TColorBox
            Left = 363
            Top = 30
            Width = 149
          end
          inherited lineWidth: TCSpinEdit
            Left = 452
            Top = 71
            Width = 60
          end
          inherited minRP: TCSpinEdit
            Left = 452
            Top = 107
            Width = 60
          end
          inherited phaseStraight: TCheckBox
            Left = 363
            Top = 143
            Width = 169
            Height = 21
          end
          inherited normRP: TCheckBox
            Left = 363
            Top = 174
            Width = 159
            Height = 20
          end
          inherited addExtButton: TButton
            Left = 533
            Top = 30
            Width = 139
            Height = 30
            OnClick = plot1addExtButtonClick
          end
          inherited removeExtButton: TButton
            Left = 533
            Top = 74
            Width = 139
            Height = 31
          end
          inherited saveAmp: TButton
            Left = 690
            Top = 30
            Width = 169
            Height = 30
          end
          inherited savePhase: TButton
            Left = 690
            Top = 74
            Width = 169
            Height = 31
          end
        end
      end
    end
  end
  object Panel2: TPanel
    Left = 527
    Top = 0
    Width = 353
    Height = 32
    BevelOuter = bvNone
    TabOrder = 1
    object SpeedButton1: TSpeedButton
      Left = 0
      Top = 0
      Width = 53
      Height = 31
      Hint = #1053#1086#1074#1099#1081' '#1087#1088#1086#1077#1082#1090
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000130B0000130B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF0033333333B333
        333B33FF33337F3333F73BB3777BB7777BB3377FFFF77FFFF77333B000000000
        0B3333777777777777333330FFFFFFFF07333337F33333337F333330FFFFFFFF
        07333337F33333337F333330FFFFFFFF07333337F33333337F333330FFFFFFFF
        07333FF7F33333337FFFBBB0FFFFFFFF0BB37777F3333333777F3BB0FFFFFFFF
        0BBB3777F3333FFF77773330FFFF000003333337F333777773333330FFFF0FF0
        33333337F3337F37F3333330FFFF0F0B33333337F3337F77FF333330FFFF003B
        B3333337FFFF77377FF333B000000333BB33337777777F3377FF3BB3333BB333
        3BB33773333773333773B333333B3333333B7333333733333337}
      NumGlyphs = 2
      ParentShowHint = False
      ShowHint = True
      OnClick = SpeedButton1Click
    end
    object SpeedButton2: TSpeedButton
      Left = 155
      Top = 0
      Width = 53
      Height = 31
      Hint = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1087#1088#1086#1077#1082#1090' '#1082#1072#1082'...'
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000130B0000130B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333330070
        7700333333337777777733333333008088003333333377F73377333333330088
        88003333333377FFFF7733333333000000003FFFFFFF77777777000000000000
        000077777777777777770FFFFFFF0FFFFFF07F3333337F3333370FFFFFFF0FFF
        FFF07F3FF3FF7FFFFFF70F00F0080CCC9CC07F773773777777770FFFFFFFF039
        99337F3FFFF3F7F777F30F0000F0F09999937F7777373777777F0FFFFFFFF999
        99997F3FF3FFF77777770F00F000003999337F773777773777F30FFFF0FF0339
        99337F3FF7F3733777F30F08F0F0337999337F7737F73F7777330FFFF0039999
        93337FFFF7737777733300000033333333337777773333333333}
      NumGlyphs = 2
      ParentShowHint = False
      ShowHint = True
      OnClick = SpeedButton2Click
    end
    object SpeedButton3: TSpeedButton
      Left = 52
      Top = 0
      Width = 53
      Height = 31
      Hint = #1054#1090#1082#1088#1099#1090#1100' '#1087#1088#1086#1077#1082#1090
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000120B0000120B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00555555555555
        555555FFFFFFFFFF55555000000000055555577777777775FFFF00B8B8B8B8B0
        0000775F5555555777770B0B8B8B8B8B0FF07F75F555555575F70FB0B8B8B8B8
        B0F07F575FFFFFFFF7F70BFB0000000000F07F557777777777570FBFBF0FFFFF
        FFF07F55557F5FFFFFF70BFBFB0F000000F07F55557F777777570FBFBF0FFFFF
        FFF075F5557F5FFFFFF750FBFB0F000000F0575FFF7F777777575700000FFFFF
        FFF05577777F5FF55FF75555550F00FF00005555557F775577775555550FFFFF
        0F055555557F55557F755555550FFFFF00555555557FFFFF7755555555000000
        0555555555777777755555555555555555555555555555555555}
      NumGlyphs = 2
      ParentShowHint = False
      ShowHint = True
      OnClick = SpeedButton3Click
    end
    object SpeedButton4: TSpeedButton
      Left = 103
      Top = 0
      Width = 53
      Height = 31
      Hint = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1090#1077#1082#1091#1097#1080#1081' '#1087#1088#1086#1077#1082#1090
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000120B0000120B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
        333333FFFFFFFFFFFFF33000077777770033377777777777773F000007888888
        00037F3337F3FF37F37F00000780088800037F3337F77F37F37F000007800888
        00037F3337F77FF7F37F00000788888800037F3337777777337F000000000000
        00037F3FFFFFFFFFFF7F00000000000000037F77777777777F7F000FFFFFFFFF
        00037F7F333333337F7F000FFFFFFFFF00037F7F333333337F7F000FFFFFFFFF
        00037F7F333333337F7F000FFFFFFFFF00037F7F333333337F7F000FFFFFFFFF
        00037F7F333333337F7F000FFFFFFFFF07037F7F33333333777F000FFFFFFFFF
        0003737FFFFFFFFF7F7330099999999900333777777777777733}
      NumGlyphs = 2
      ParentShowHint = False
      ShowHint = True
      OnClick = SpeedButton4Click
    end
    object Label26: TLabel
      Left = 226
      Top = 7
      Width = 109
      Height = 16
      Caption = #1042#1077#1088#1089#1080#1103' '#1086#1090' 8.02.11'
    end
  end
  object openCalFiles: TOpenDialog
    Filter = #1060#1072#1081#1083#1099' '#1082#1072#1083#1080#1073#1088#1086#1074#1082#1080' (*.cal)|*.cal|'#1042#1089#1077' '#1092#1072#1081#1083#1099' (*.*)|*.*'
    Options = [ofHideReadOnly, ofFileMustExist, ofEnableSizing]
    Title = #1047#1072#1076#1072#1081#1090#1077' '#1092#1072#1081#1083' '#1082#1072#1083#1080#1073#1088#1086#1074#1082#1080
    Left = 112
    Top = 336
  end
end
