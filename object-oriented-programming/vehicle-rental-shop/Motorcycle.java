
/**
 * Write a description of class Motorcycle here.
 *
 * @author (Irfan Sandy)
 * @version (1.0.0)
 */
public class Motorcycle extends Vehicle
{
    private boolean isElectric;
    private int engineCapacity;

    public Motorcycle(String make, String model, int year, boolean isElectric, int engineCapacity) {
        super(make, model, year);
        this.isElectric = isElectric;
        this.engineCapacity = engineCapacity;
    }

    public boolean isElectric() {
        return isElectric;
    }

    public int getEngineCapacity() {
        return engineCapacity;
    }

    @Override
    public void showDetail() {
        super.showDetail();
        System.out.println("Is Electric: " + isElectric);
        System.out.println("Engine Capacity: " + engineCapacity + " cc");
    }
}