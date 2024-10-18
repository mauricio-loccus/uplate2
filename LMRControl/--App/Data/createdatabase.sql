--
-- File generated with SQLiteStudio v3.1.1 on qui mar 9 09:08:47 2017
--
-- Text encoding used: System
--
PRAGMA foreign_keys = off;
BEGIN TRANSACTION;

-- Table: Plates
DROP TABLE IF EXISTS Plates;

CREATE TABLE Plates (
    platenum   INTEGER       NOT NULL,
    Height     INTEGER,
    Width      INTEGER,
    PlateName  VARCHAR (100),
    PlateDescr VARCHAR (200),
    Layout     VARCHAR (1),
    CONSTRAINT Pk_Plates PRIMARY KEY (
        platenum
    )
);


-- Table: SystemUsers
DROP TABLE IF EXISTS SystemUsers;

CREATE TABLE SystemUsers (
    Id         INTEGER         NOT NULL
                               PRIMARY KEY AUTOINCREMENT,
    Login      VARBINARY (20)  NOT NULL,
    Password   VARBINARY (256) NOT NULL,
    UserID     INTEGER         REFERENCES Users (ID) ON DELETE CASCADE
                                                     ON UPDATE RESTRICT,
    CreateDate DATE,
    AlterDate  DATE,
    CONSTRAINT Pk_Users UNIQUE (
        Id
    )
);

INSERT INTO SystemUsers (Id, Login, Password, UserID, CreateDate, AlterDate) VALUES (1, 'Administrator', '&,3(S-#4V', NULL, '2017-03-08', '2017-03-09');

-- Table: Users
DROP TABLE IF EXISTS Users;

CREATE TABLE Users (
    ID         INTEGER      PRIMARY KEY AUTOINCREMENT
                            NOT NULL,
    REGID      VARCHAR (30),
    NAME       VARCHAR (60),
    DEPTNO     VARCHAR (60),
    CREATEDATE DATE,
    ALTERDATE  DATE
);


-- Table: Well
DROP TABLE IF EXISTS Well;

CREATE TABLE Well (
    Platenum  INTEGER     NOT NULL,
    cellid    INTEGER,
    [Row]     VARCHAR (1) NOT NULL,
    Col       INTEGER,
    Type      INTEGER     NOT NULL,
    StdValue  NUMERIC,
    RawValue  NUMERIC,
    PostValue NUMERIC,
    Interpret VARCHAR (1) DEFAULT 'G',
    CONSTRAINT Idx_Well_PlateNumRowCol UNIQUE (
        Platenum,
        [Row],
        Col
    ),
    FOREIGN KEY (
        Platenum
    )
    REFERENCES Plates (platenum) ON DELETE CASCADE,
    FOREIGN KEY (
        Type
    )
    REFERENCES WellType (ID) ON DELETE CASCADE
);


-- Table: WellType
DROP TABLE IF EXISTS WellType;

CREATE TABLE WellType (
    ID    INTEGER      PRIMARY KEY
                       NOT NULL,
    DESCR VARCHAR (60) NOT NULL
);


-- Index: idx_Well
DROP INDEX IF EXISTS idx_Well;

CREATE INDEX idx_Well ON Well (
    "Type"
);


-- Trigger: update_alterdate
DROP TRIGGER IF EXISTS update_alterdate;
CREATE TRIGGER update_alterdate
         AFTER UPDATE OF Password
            ON SystemUsers
BEGIN
    UPDATE SystemUsers
       SET alterdate = date('Now');
END;


-- Trigger: update_createdate
DROP TRIGGER IF EXISTS update_createdate;
CREATE TRIGGER update_createdate
         AFTER INSERT
            ON SystemUsers
BEGIN
    UPDATE SystemUsers
       SET createdate = date('now');
END;


COMMIT TRANSACTION;
PRAGMA foreign_keys = on;
