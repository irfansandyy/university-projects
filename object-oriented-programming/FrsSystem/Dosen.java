
/**
 * Write a description of class Dosen here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class Dosen
{
    private String nama;
    private String kodeDosen;
    private String nidn;

    /**
     * Constructor for objects of class Dosen
     */
    public Dosen(String nama, String kodeDosen, String nidn)
    {
        this.nama = nama;
        this.kodeDosen = kodeDosen;
        this.nidn = nidn;
    }

    public String getNama() 
    {
        return this.nama;
    }
    
    public String getKodeDosen() 
    {
        return this.kodeDosen;
    }
}