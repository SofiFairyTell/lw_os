object RecieverForm: TRecieverForm
  Left = 192
  Top = 107
  Width = 112
  Height = 91
  Caption = #1055#1088#1080#1077#1084' '#1092#1072#1081#1083#1086#1074
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object ConnectButton: TButton
    Left = 0
    Top = 32
    Width = 81
    Height = 25
    Caption = #1057#1086#1077#1076#1077#1085#1080#1090#1100#1089#1103
    TabOrder = 0
    OnClick = ConnectButtonClick
  end
  object Client: TClientSocket
    Active = False
    Address = '192.168.107.116'
    ClientType = ctNonBlocking
    Host = '192.168.107.216'
    Port = 1010
    OnRead = ClientRead
  end
  object SaveDialog: TSaveDialog
    Left = 32
  end
end
