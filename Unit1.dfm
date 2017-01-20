object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 461
  ClientWidth = 727
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Memo1: TMemo
    Left = 0
    Top = 240
    Width = 727
    Height = 221
    Align = alBottom
    Lines.Strings = (
      'Memo1')
    TabOrder = 0
  end
  object Button1: TButton
    Left = 616
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Button1'
    TabOrder = 1
    OnClick = Button1Click
  end
  object MonthCalendar1: TMonthCalendar
    Left = 368
    Top = 8
    Width = 225
    Height = 160
    Date = 42755.503822962960000000
    TabOrder = 2
  end
  object ADOConnection1: TADOConnection
    Connected = True
    ConnectionString = 
      'Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security In' +
      'fo=False;Initial Catalog=Despatch;Data Source=FGH-SQL01'
    LoginPrompt = False
    Provider = 'SQLOLEDB.1'
    Left = 72
    Top = 32
  end
  object Q: TADOQuery
    Connection = ADOConnection1
    CursorType = ctStatic
    Parameters = <
      item
        Name = 'DT'
        Attributes = [paNullable]
        DataType = ftString
        NumericScale = 255
        Precision = 255
        Size = 10
        Value = Null
      end>
    SQL.Strings = (
      'SELECT [ID]'
      '      ,[LogTime]'
      '      ,[Message]'
      '      ,[MessageType]'
      '  FROM [Despatch].[dbo].[Log]'
      '  where CONVERT(char(10),logtime,121)= :DT'
      '  and Message like '#39'UNIT%'#39' and message like '#39'%CHILD%'#39
      'order by logtime')
    Left = 192
    Top = 32
    object QID: TLargeintField
      FieldName = 'ID'
      ReadOnly = True
    end
    object QLogTime: TDateTimeField
      FieldName = 'LogTime'
    end
    object QMessage: TWideStringField
      FieldName = 'Message'
      FixedChar = True
      Size = 150
    end
    object QMessageType: TSmallintField
      FieldName = 'MessageType'
    end
  end
  object DataSource1: TDataSource
    DataSet = Q
    Left = 288
    Top = 32
  end
  object D: TADOQuery
    Connection = ADOConnection1
    CursorType = ctStatic
    Parameters = <
      item
        Name = 'DT'
        Attributes = [paNullable]
        DataType = ftString
        NumericScale = 255
        Precision = 255
        Size = 10
        Value = Null
      end>
    SQL.Strings = (
      'SELECT TOP 1000 [ID]'
      '      ,[LogTime]'
      '      ,[Message]'
      '      ,[MessageType]'
      '  FROM [Despatch].[dbo].[Log]'
      '  where CONVERT(char(10),logtime,121)= :DT'
      '  and Message like '#39'UNIT%'#39'  and message like '#39'%DEPOT%'#39)
    Left = 64
    Top = 104
    object DID: TLargeintField
      FieldName = 'ID'
      ReadOnly = True
    end
    object DLogTime: TDateTimeField
      FieldName = 'LogTime'
    end
    object DMessage: TWideStringField
      FieldName = 'Message'
      FixedChar = True
      Size = 150
    end
    object DMessageType: TSmallintField
      FieldName = 'MessageType'
    end
  end
end
