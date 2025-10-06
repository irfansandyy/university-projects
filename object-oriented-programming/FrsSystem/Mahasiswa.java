import java.util.ArrayList;

/**
 * Write a description of class Mahasiswa here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class Mahasiswa
{
    // instance variables - replace the example below with your own
    private String nama;
    private String nim;
    private String jurusan;
    
    private Dosen dosenWali; 
    private ArrayList<MataKuliah> krs;
    
    /**
     * Constructor for objects of class Mahasiswa
     */
    public Mahasiswa(String nama, String nim, String jurusan)
    {
        this.nama = nama;
        this.nim = nim;
        this.jurusan = jurusan;
        this.krs = new ArrayList<>(); 
    }

    public String getNama() 
    {
        return this.nama;
    }
    
    public String getNim() 
    {
        return this.nim;
    }

    public boolean sudahAmbilMatkul(String kodeMk) 
    {
        for (MataKuliah mkDiKrs : this.krs) 
        {
            if (mkDiKrs.getKodeMk().equals(kodeMk)) 
            {
                return true;
            }
        }
        return false;
    }
    
    public void tambahMatkulKeKrs(MataKuliah matkul) 
    {
        if (!sudahAmbilMatkul(matkul.getKodeMk())) 
        {
            this.krs.add(matkul);
            System.out.println("'" + matkul.getNamaMk() + "' berhasil ditambahkan ke KRS " + this.nama);
        }
        else 
        {
            System.out.println("INFO: '" + matkul.getNamaMk() + "' sudah ada di KRS " + this.nama + ". Penambahan dilewati.");
        }
    }
    
    public void cetakKrs() 
    {
        System.out.println("--- KARTU RENCANA STUDI ---");
        System.out.println("Nama    : " + this.nama);
        System.out.println("NIM     : " + this.nim);
        System.out.println("-----------------------------");
        
        if (krs.isEmpty()) 
        {
            System.out.println("KRS masih kosong.");
        } 
        else 
        {
            for(MataKuliah mk : krs) 
            {
                System.out.println("- " + mk.getKodeMk() + " | " + mk.getNamaMk() + " (" + mk.getSks() + " SKS)");
            }
        }
        System.out.println("-----------------------------");
    }
}