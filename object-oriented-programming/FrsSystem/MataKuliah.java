
/**
 * Write a description of class MataKuliah here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class MataKuliah
{
    // instance variables - replace the example below with your own
    private String kodeMk;
    private String namaMk;
    private int sks;
    private int kapasitas;
    
    private Dosen dosenPengampu;

    /**
     * Constructor for objects of class MataKuliah
     */
    public MataKuliah(String kodeMk, String namaMk, int sks, int kapasitas, Dosen dosen)
    {
        this.kodeMk = kodeMk;
        this.namaMk = namaMk;
        this.sks = sks;
        this.kapasitas = kapasitas;
        this.dosenPengampu = dosen;
    }

    public String getNamaMk() 
    {
        return this.namaMk;
    }
    
    public String getKodeMk() 
    {
        return this.kodeMk;
    }
    
    public int getSks() 
    {
        return this.sks;
    }
}