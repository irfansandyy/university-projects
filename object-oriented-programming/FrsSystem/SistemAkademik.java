import java.util.ArrayList;
import java.util.Scanner;
import java.io.FileWriter;
import java.io.FileReader;
import java.io.IOException;
import java.io.Writer;
import java.io.Reader;
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

public class SistemAkademik {
    private ArrayList<Mahasiswa> daftarMahasiswa;
    private ArrayList<Dosen> daftarDosen;
    private ArrayList<MataKuliah> daftarMataKuliah;

    public SistemAkademik() {
        this.daftarMahasiswa = new ArrayList<>();
        this.daftarDosen = new ArrayList<>();
        this.daftarMataKuliah = new ArrayList<>();
    }

    public void tambahMahasiswa(Mahasiswa m) { daftarMahasiswa.add(m); }
    public void tambahDosen(Dosen d) { daftarDosen.add(d); }
    public void tambahMataKuliah(MataKuliah mk) { daftarMataKuliah.add(mk); }

    public Mahasiswa cariMahasiswa(String nim) {
        for (Mahasiswa m : daftarMahasiswa) {
            if (m.getNim().equals(nim)) { return m; }
        }
        return null;
    }
    
    public Dosen cariDosen(String kodeDosen) {
        for (Dosen d : daftarDosen) {
            if (d.getKodeDosen().equals(kodeDosen)) { return d; }
        }
        return null;
    }
    
    public MataKuliah cariMataKuliah(String kodeMk) {
         for (MataKuliah mk : daftarMataKuliah) {
            if (mk.getKodeMk().equals(kodeMk)) { return mk; }
        }
        return null;
    }
    
    public void tampilkanSemuaMahasiswa() {
        System.out.println("\n--- DAFTAR MAHASISWA ---");
        if (daftarMahasiswa.isEmpty()) {
            System.out.println("Belum ada data mahasiswa.");
            return;
        }
        for (Mahasiswa m : daftarMahasiswa) {
            System.out.println("- NIM: " + m.getNim() + ", Nama: " + m.getNama());
        }
    }
    
    public void tampilkanSemuaDosen() {
        System.out.println("\n--- DAFTAR DOSEN ---");
        if (daftarDosen.isEmpty()) {
            System.out.println("Belum ada data dosen.");
            return;
        }
        for (Dosen d : daftarDosen) {
            System.out.println("- Kode: " + d.getKodeDosen() + ", Nama: " + d.getNama());
        }
    }

    public void tampilkanSemuaMataKuliah() {
        System.out.println("\n--- DAFTAR MATA KULIAH ---");
        if (daftarMataKuliah.isEmpty()) {
            System.out.println("Belum ada data mata kuliah.");
            return;
        }
        for (MataKuliah mk : daftarMataKuliah) {
            System.out.println("- Kode: " + mk.getKodeMk() + ", Nama: " + mk.getNamaMk() + " (" + mk.getSks() + " SKS)");
        }
    }

    public void prosesKrs(String nim, String kodeMk) {
        Mahasiswa mhs = cariMahasiswa(nim);
        MataKuliah mk = cariMataKuliah(kodeMk);
        
        if (mhs != null && mk != null) {
            mhs.tambahMatkulKeKrs(mk);
        } else {
            System.out.println("Gagal proses KRS: Mahasiswa atau Mata Kuliah tidak ditemukan.");
        }
    }
    
    public void simpanDataKeJson(String namaFile) {
        Gson gson = new GsonBuilder().setPrettyPrinting().create();
        try (Writer writer = new FileWriter(namaFile)) {
            gson.toJson(this, writer);
            System.out.println("-> Data berhasil disimpan ke file '" + namaFile + "'");
        } catch (IOException e) {
            System.err.println("Gagal menyimpan data ke JSON: " + e.getMessage());
        }
    }
    
    public static SistemAkademik muatDataDariJson(String namaFile) {
        Gson gson = new Gson();
        try (Reader reader = new FileReader(namaFile)) {
            SistemAkademik sistem = gson.fromJson(reader, SistemAkademik.class);
            System.out.println("-> Data berhasil dimuat dari file '" + namaFile + "'");
            return sistem;
        } catch (IOException e) {
            System.out.println("-> File '" + namaFile + "' tidak ditemukan atau gagal dibaca.");
            return null;
        }
    }
    
    public static void main(String[] args) {
        SistemAkademik sistem = new SistemAkademik();
        Scanner scanner = new Scanner(System.in);
        String namaFile = "akademik.json";
        SistemAkademik sistemDariFile = muatDataDariJson(namaFile);
        if (sistemDariFile != null) 
        {   
            System.out.println("Berhasil memuat data dari akademik.json\n");
            sistem = sistemDariFile;
        } else {
            System.out.println("Gagal memuat data dari akademik.json\n");
        }
        
        boolean berjalan = true;
        
        while (berjalan) {
            System.out.println("\n===== MENU SISTEM AKADEMIK =====");
            System.out.println("1. Tambah Mahasiswa");
            System.out.println("2. Tambah Dosen");
            System.out.println("3. Tambah Mata Kuliah");
            System.out.println("4. Proses Pengisian KRS");
            System.out.println("5. Tampilkan Semua Data");
            System.out.println("6. Cetak KRS Mahasiswa");
            System.out.println("---------------------------------");
            System.out.println("7. Simpan Data ke File (JSON)");
            System.out.println("8. Muat Data dari File (JSON)");
            System.out.println("0. Keluar");
            System.out.print("Pilih menu: ");
            
            int pilihan = scanner.nextInt();
            scanner.nextLine();

            switch (pilihan) {
                case 1:
                    System.out.print("Masukkan Nama Mahasiswa: ");
                    String namaMhs = scanner.nextLine();
                    System.out.print("Masukkan NIM: ");
                    String nim = scanner.nextLine();
                    System.out.print("Masukkan Jurusan: ");
                    String jurusan = scanner.nextLine();
                    sistem.tambahMahasiswa(new Mahasiswa(namaMhs, nim, jurusan));
                    System.out.println("Mahasiswa berhasil ditambahkan.");
                    break;
                case 2:
                    System.out.print("Masukkan Nama Dosen: ");
                    String namaDosen = scanner.nextLine();
                    System.out.print("Masukkan Kode Dosen: ");
                    String kodeDosen = scanner.nextLine();
                    System.out.print("Masukkan NIDN: ");
                    String nidn = scanner.nextLine();
                    sistem.tambahDosen(new Dosen(namaDosen, kodeDosen, nidn));
                    System.out.println("Dosen berhasil ditambahkan.");
                    break;
                case 3:
                    System.out.print("Masukkan Kode Mata Kuliah: ");
                    String kodeMk = scanner.nextLine();
                    System.out.print("Masukkan Nama Mata Kuliah: ");
                    String namaMk = scanner.nextLine();
                    System.out.print("Masukkan SKS: ");
                    int sks = scanner.nextInt();
                    scanner.nextLine();
                    System.out.print("Masukkan Kapasitas: ");
                    int kapasitas = scanner.nextInt();
                    scanner.nextLine();
                    sistem.tampilkanSemuaDosen();
                    System.out.print("Masukkan Kode Dosen Pengampu: ");
                    String kdDosenPengampu = scanner.nextLine();
                    Dosen d = sistem.cariDosen(kdDosenPengampu);
                    if (d != null) {
                        sistem.tambahMataKuliah(new MataKuliah(kodeMk, namaMk, sks, kapasitas, d));
                        System.out.println("Mata Kuliah berhasil ditambahkan.");
                    } else {
                        System.out.println("Dosen tidak ditemukan, mata kuliah gagal ditambahkan.");
                    }
                    break;
                case 4:
                    sistem.tampilkanSemuaMahasiswa();
                    System.out.print("Masukkan NIM Mahasiswa yang akan mengisi KRS: ");
                    String nimKrs = scanner.nextLine();
                    sistem.tampilkanSemuaMataKuliah();
                    System.out.print("Masukkan Kode Mata Kuliah yang akan diambil: ");
                    String kodeMkKrs = scanner.nextLine();
                    sistem.prosesKrs(nimKrs, kodeMkKrs);
                    break;
                case 5:
                    sistem.tampilkanSemuaMahasiswa();
                    sistem.tampilkanSemuaDosen();
                    sistem.tampilkanSemuaMataKuliah();
                    break;
                case 6:
                    sistem.tampilkanSemuaMahasiswa();
                    System.out.print("Masukkan NIM Mahasiswa untuk mencetak KRS: ");
                    String nimCetak = scanner.nextLine();
                    Mahasiswa mhsCetak = sistem.cariMahasiswa(nimCetak);
                    if(mhsCetak != null) {
                        mhsCetak.cetakKrs();
                    } else {
                        System.out.println("Mahasiswa dengan NIM " + nimCetak + " tidak ditemukan.");
                    }
                    break;
                case 7:
                    sistem.simpanDataKeJson(namaFile);
                    break;
                case 8:
                    sistemDariFile = muatDataDariJson(namaFile);
                    if (sistemDariFile != null) {
                        sistem = sistemDariFile;
                    }
                    break;
                case 0:
                    berjalan = false;
                    System.out.println("Menyimpan data terakhir sebelum keluar...");
                    sistem.simpanDataKeJson(namaFile);
                    System.out.println("Terima kasih telah menggunakan program ini.");
                    break;
                default:
                    System.out.println("Pilihan tidak valid. Silakan coba lagi.");
            }
        }
        scanner.close();
    }
}