DROP DATABASE IF EXISTS company;
CREATE DATABASE IF NOT EXISTS company;
USE company;

CREATE TABLE PEGAWAI (
    NmDepan VARCHAR(20),
    Inisial VARCHAR(1),
    NmBelakang VARCHAR(20),
    NoKTP VARCHAR(10),
    Alamat VARCHAR(50),
    Gaji INT,
    JenisKelamin VARCHAR(1),
    NoKTPKepala VARCHAR(15) NULL,
    DNO INT
);

CREATE TABLE DEPARTEMEN (
    Dname VARCHAR(20),
    Dnomor INT,
    NOKTP_MGR VARCHAR(10),
    TglMulai_MGR DATE
);

CREATE TABLE LOKASI_DEPARTEMEN (
    Dnomor INT,
    Dlokasi VARCHAR(20)
);

CREATE TABLE PROYEK (
    Pnama VARCHAR(20),
    Pnomor INT,
    Plokasi VARCHAR(20),
    Dnum INT
);

CREATE TABLE TANGGUNGAN (
    NoKTP VARCHAR(10),
    Nama_Tanggungan VARCHAR(20),
    JenisKelamin VARCHAR(1),
    TglLahir DATE,
    Hubungan VARCHAR(20)
);

CREATE TABLE BEKERJA_PADA (
    NoKTP VARCHAR(10),
    Pnomor INT,
    LamaJam DECIMAL(5,1) NULL
);

INSERT INTO PEGAWAI (NmDepan, Inisial, NmBelakang, NoKTP, Alamat, Gaji, JenisKelamin, NoKTPKepala, DNO)
VALUES
  ('John', 'B', 'Smith', '123456789', '731 Fondren, Houston, TX', 30000, 'L', '333445555', 5),
  ('Franklin', 'T', 'Wong', '333445555', '638 Voss, Houston, TX', 40000, 'L', '888665555', 5),
  ('Alicia', 'J', 'Zelaya', '999887777', '3321 Castle, Spring, TX', 25000, 'P', '987654321', 4),
  ('Jennifer', 'S', 'Wallace', '987654321', '291 Berry, Bellaire, TX', 43000, 'P', '888665555', 4),
  ('Ramesh', 'K', 'Narayan', '666884444', '975 Fire Oak, Humble, TX', 38000, 'L', '333445555', 5),
  ('Joyce', 'A', 'English', '453453453', '5631 Rice, Houston, TX', 25000, 'P', '333445555', 5),
  ('Ahmad', 'V', 'Jabbar', '987987987', '980 Dallas, Houston, TX', 25000, 'L', '987654321', 4),
  ('James', 'E', 'Borg', '888665555', '450 Stone, Houston, TX', 55000, 'L', NULL, 1);

INSERT INTO DEPARTEMEN (Dname, Dnomor, NOKTP_MGR, TglMulai_MGR)
VALUES
  ('Research', 5, '333445555', '1988-05-22'),
  ('Administration', 4, '987654321', '1995-01-01'),
  ('HeadQuarters', 1, '888665555', '1981-06-19');

INSERT INTO LOKASI_DEPARTEMEN (Dnomor, Dlokasi)
VALUES
  (1, 'Houston'),
  (4, 'Stafford'),
  (5, 'Bellaire'),
  (5, 'Sugarland'),
  (5, 'Houston');

INSERT INTO PROYEK (Pnama, Pnomor, Plokasi, Dnum)
VALUES
  ('ProductX', 1, 'Bellaire', 5),
  ('ProductY', 2, 'Sugarland', 5),
  ('ProductZ', 3, 'Houston', 5),
  ('Computerization', 10, 'Stafford', 4),
  ('Reorganization', 20, 'Houston', 1),
  ('Newbenefits', 30, 'Stafford', 4);

INSERT INTO TANGGUNGAN (NoKTP, Nama_Tanggungan, JenisKelamin, TglLahir, Hubungan)
VALUES
  ('333445555', 'Alice', 'P', '1986-04-05', 'Anak Perempuan'),
  ('333445555', 'Theodore', 'L', '1983-10-25', 'Anak Laki-laki'),
  ('333445555', 'Joy', 'P', '1958-03-05', 'Pasangan'),
  ('987654321', 'Abner', 'L', '1942-02-28', 'Pasangan'),
  ('123456789', 'Michael', 'L', '1988-01-04', 'Anak Laki-laki'),
  ('123456789', 'Alice', 'P', '1988-12-30', 'Anak Perempuan'),
  ('123456789', 'Elizabeth', 'P', '1967-05-05', 'Pasangan');

INSERT INTO BEKERJA_PADA (NoKTP, Pnomor, LamaJam)
VALUES
  ('123456789', 1, 32.5),
  ('123456789', 2, 7.5),
  ('666884444', 3, 40.0),
  ('453453453', 1, 20.0),
  ('453453453', 2, 20.0),
  ('333445555', 2, 10.0),
  ('333445555', 3, 10.0),
  ('333445555', 10, 10.0),
  ('333445555', 20, 10.0),
  ('999887777', 30, 30.0),
  ('999887777', 30, 10.0),
  ('987987987', 10, 35.0),
  ('987987987', 30, 5.0),
  ('987654321', 30, 20.0),
  ('987654321', 20, 15.0),
  ('888665555', 20, NULL);

CREATE VIEW Employee_Departement as (
    SELECT pe.`NmDepan`, pe.`Inisial`, pe.`NmBelakang`, pe.`NoKTP`, pe.`Alamat`, pe.`Gaji`, pe.`JenisKelamin`, pe.`NoKTPKepala`, pe.`DNO`, de.`Dname`, de.`NOKTP_MGR`, de.`TglMulai_MGR`
    FROM pegawai pe
    INNER JOIN departemen de ON (pe.`DNO` = de.`Dnomor`)
)

CREATE VIEW Research_Employee as (
    SELECT *
    FROM employee_departement
    WHERE `Dname` = 'Research'
)

CREATE VIEW Hasil_1 as (
    SELECT nmdepan, nmbelakang, alamat, gaji
    FROM research_employee
)

CREATE VIEW NoKTPKepala as (
    SELECT NoKTPKepala FROM pegawai
)

CREATE VIEW Supervisor as (
    SELECT *
    FROM pegawai
    WHERE NoKTP IN  (SELECT NoKTPKepala FROM pegawai)
)

CREATE VIEW Hasil_2 as (
    SELECT nmdepan, nmbelakang, alamat, NoKTP
    FROM supervisor
)

CREATE VIEW tempSupervisor as (
    SELECT `NmDepan` as namadepan, `Inisial` as singkatan, `NmBelakang` as namabelakang, `NoKTP` as NomorKTP, Alamat as Alamat_supervisor, gaji as gaji_supervisor, `JenisKelamin` as JenisKelamin_supervisor, `NoKTPKepala` as NoKTPKepala_supervisor, `DNO` as DNO_supervisor
    FROM pegawai
)

CREATE VIEW Employee_Supervisor as (
    SELECT *
    FROM pegawai as employee
    LEFT OUTER JOIN tempsupervisor as supervisor ON (employee.`NoKTPKepala` = supervisor.`NomorKTP`)
)

CREATE VIEW Hasil_3 as (
    SELECT `NmDepan` as NmDepan_Employee, `NmBelakang` as NmBelakang_Employee, `NoKTP` as NoKTP_Employee, namadepan as NmDepan_Supervisor, namabelakang as NmBelakang_Supervisor, `NomorKTP` as NoKTP_Supervisor
    FROM employee_supervisor
)

CREATE VIEW Hasil_3_v1 as (
    SELECT CONCAT(`NmDepan`, ' ', `NmBelakang`) as Nama_Employee, `NoKTP` as NoKTP_Employee, CONCAT(namadepan, ' ', namabelakang) as Nama_Supervisor, `NomorKTP` as NoKTP_Supervisor
    FROM employee_supervisor
)

CREATE VIEW Departement_Manager as (
    SELECT *
    FROM departemen
    INNER JOIN pegawai ON (departemen.`NOKTP_MGR` = pegawai.`NoKTP`)
)

CREATE VIEW Hasil_4 as (
    SELECT CONCAT(`NmDepan`, ' ', `NmBelakang`) as Nama, `Alamat`, `NoKTP`
    FROM departement_manager
    WHERE `Dnomor`= 4
)

SELECT CONCAT(`NmDepan`, ' ', `NmBelakang`) as Nama, `Alamat`, `Pnama` as nama_proyek
FROM bekerja_pada
INNER JOIN pegawai ON (bekerja_pada.`NoKTP` = pegawai.`NoKTP`)
INNER JOIN proyek ON (bekerja_pada.`Pnomor` = proyek.`Pnomor`)
WHERE `Pnama` = 'ProductZ'

CREATE VIEW Project_Departement as (
    SELECT *
    FROM proyek
    INNER JOIN departemen ON (proyek.`Dnum` = departemen.`Dnomor`)
)

CREATE VIEW Hasil_6 as (
    SELECT `Pnama` as Nama_Proyek
    FROM project_departement
    WHERE `Dname` = 'Research'
)

CREATE VIEW Hasil_7 as (
    SELECT Pnama as Nama_Proyek
    FROM proyek
    WHERE `Plokasi` = 'Houston' or `Plokasi` = 'Stafford'
)

SELECT `Pnama` as Nama_Project, `Plokasi` as `Location`
FROM bekerja_pada
INNER JOIN pegawai ON (bekerja_pada.`NoKTP` = pegawai.`NoKTP`)
INNER JOIN proyek ON (bekerja_pada.`Pnomor` = proyek.`Pnomor`)
WHERE `NmDepan` = 'John'

CREATE VIEW Hasil_9 as (
    SELECT CONCAT(`NmDepan`, ' ', `NmBelakang`) as Nama, Alamat
    FROM pegawai
    WHERE `JenisKelamin` = 'L' AND `Gaji` < 40000
)

CREATE VIEW Hasil_10 as (
    SELECT CONCAT(`NmDepan`, ' ', `NmBelakang`) as Nama, `Gaji`
    FROM departement_manager
    WHERE `Dname` = 'Administration'
)