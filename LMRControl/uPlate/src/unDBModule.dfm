object DBModule: TDBModule
  OldCreateOrder = False
  OnCreate = DataModuleCreate
  Height = 454
  Width = 726
  object Lmr96Connection: TSQLConnection
    ConnectionName = 'lrm96'
    DriverName = 'Sqlite'
    LoginPrompt = False
    Params.Strings = (
      'DriverName=Sqlite'
      'DriverUnit=Data.DbxSqlite'
      
        'DriverPackageLoader=TDBXSqliteDriverLoader,DBXSqliteDriver210.bp' +
        'l'
      
        'MetaDataPackageLoader=TDBXSqliteMetaDataCommandFactory,DbxSqlite' +
        'Driver210.bpl'
      'FailIfMissing=True'
      'Database='
      '')
    Left = 37
    Top = 22
  end
  object UnidadesTable: TSQLDataSet
    CommandText = 'unidades'
    CommandType = ctTable
    DbxCommandType = 'Dbx.Table'
    MaxBlobSize = -1
    Params = <>
    SQLConnection = Lmr96Connection
    Left = 158
    Top = 18
    object UnidadesTableunidade: TWideStringField
      FieldName = 'unidade'
      Required = True
    end
    object UnidadesTablevalor: TLargeintField
      FieldName = 'valor'
      Required = True
    end
  end
  object UnitiesDataSetProvider: TDataSetProvider
    DataSet = UnidadesTable
    Left = 266
    Top = 18
  end
  object UnitiesClientDataSet: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'UnitiesDataSetProvider'
    Left = 373
    Top = 18
    object UnitiesClientDataSetunidade: TWideStringField
      FieldName = 'unidade'
      Required = True
    end
    object UnitiesClientDataSetvalor: TLargeintField
      FieldName = 'valor'
      Required = True
    end
  end
  object UnitiesDataSource: TDataSource
    DataSet = UnitiesClientDataSet
    Left = 483
    Top = 18
  end
  object UserDataSource: TDataSource
    DataSet = UserClientDataSet
    Left = 480
    Top = 86
  end
  object UserClientDataSet: TClientDataSet
    Aggregates = <>
    Filter = 'login <> '#39'loccus'#39
    Filtered = True
    Params = <>
    ProviderName = 'UserDataSetProvider'
    Left = 373
    Top = 86
    object UserClientDataSetlogin: TWideStringField
      FieldName = 'login'
      Required = True
      Size = 60
    end
    object UserClientDataSetpassword: TWideStringField
      FieldName = 'password'
      Required = True
      Size = 60
    end
    object UserClientDataSetname: TWideStringField
      FieldName = 'name'
      Required = True
      Size = 60
    end
    object UserClientDataSetsurname: TWideStringField
      FieldName = 'surname'
      Size = 120
    end
    object UserClientDataSetdept: TWideStringField
      FieldName = 'dept'
      Size = 120
    end
    object UserClientDataSetsuperuser: TLargeintField
      FieldName = 'superuser'
    end
    object UserClientDataSetcreation_date: TWideMemoField
      FieldName = 'creation_date'
      BlobType = ftWideMemo
      Size = 1
    end
    object UserClientDataSetalter_date: TWideMemoField
      FieldName = 'alter_date'
      BlobType = ftWideMemo
      Size = 1
    end
  end
  object UserDataSetProvider: TDataSetProvider
    DataSet = UserTable
    Left = 266
    Top = 86
  end
  object UserTable: TSQLDataSet
    CommandText = 'user'
    CommandType = ctTable
    DbxCommandType = 'Dbx.Table'
    MaxBlobSize = 1
    Params = <>
    SQLConnection = Lmr96Connection
    Left = 159
    Top = 86
    object UserTablelogin: TWideStringField
      FieldName = 'login'
      Required = True
      Size = 60
    end
    object UserTablepassword: TWideStringField
      FieldName = 'password'
      Required = True
      Size = 60
    end
    object UserTablename: TWideStringField
      FieldName = 'name'
      Required = True
      Size = 60
    end
    object UserTablesurname: TWideStringField
      FieldName = 'surname'
      Size = 120
    end
    object UserTabledept: TWideStringField
      FieldName = 'dept'
      Size = 120
    end
    object UserTablesuperuser: TLargeintField
      FieldName = 'superuser'
    end
    object UserTablecreation_date: TWideMemoField
      FieldName = 'creation_date'
      BlobType = ftWideMemo
      Size = 1
    end
    object UserTablealter_date: TWideMemoField
      FieldName = 'alter_date'
      BlobType = ftWideMemo
      Size = 1
    end
  end
  object UserQuery: TSQLQuery
    MaxBlobSize = 1
    Params = <
      item
        DataType = ftString
        Name = 'pLogin'
        ParamType = ptInput
      end>
    SQL.Strings = (
      'select ID, LOGIN, PASSWORD, SUPERUSER'
      '   from USER'
      '  where LOGIN = :pLogin')
    SQLConnection = Lmr96Connection
    Left = 156
    Top = 198
  end
  object UserSQLQuery: TSQLQuery
    MaxBlobSize = 1
    Params = <>
    SQL.Strings = (
      
        'select user.login || '#39' '#39' || '#39'('#39' || trim(trim(user.name) || '#39' '#39' |' +
        '| trim(ifnull(user.surname, '#39#39')))  ||'#39')'#39' as completelogin'
      '  from user'
      'where user.login <> '#39'loccus'#39)
    SQLConnection = Lmr96Connection
    Left = 156
    Top = 139
    object UserSQLQueryColumn0: TWideMemoField
      FieldName = 'Column0'
      Required = True
      BlobType = ftWideMemo
      Size = 1
    end
  end
end
