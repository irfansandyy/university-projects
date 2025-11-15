
/**
 * Write a description of class Bike here.
 *
 * @author (Irfan Sandy)
 * @version (1.0.0)
 */
public class Bike extends Vehicle
{
    private String type;
    private boolean hasCarrier;

    public Bike(String make, String model, int year, String type, boolean hasCarrier) {
        super(make, model, year);
        this.type = type;
        this.hasCarrier = hasCarrier;
    }

    public String getType() {
        return type;
    }

    public boolean hasCarrier() {
        return hasCarrier;
    }

    @Override
    public void showDetail() {
        super.showDetail();
        System.out.println("Type: " + type);
        System.out.println("Has Carrier: " + hasCarrier);
    }
}