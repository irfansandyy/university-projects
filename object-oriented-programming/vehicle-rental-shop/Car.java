
/**
 * Write a description of class Car here.
 *
 * @author (Irfan Sandy)
 * @version (1.0.0)
 */
public class Car extends Vehicle
{
    private int numberOfDoors;
    private int numberOfSeats;
    private int numberOfWheels;
    private boolean isElectric;

    public Car(String make, String model, int year, int numberOfDoors, int numberOfSeats, int numberOfWheels, boolean isElectric) {
        super(make, model, year);
        this.numberOfDoors = numberOfDoors;
        this.numberOfSeats = numberOfSeats;
        this.numberOfWheels = numberOfWheels;
        this.isElectric = isElectric;
    }

    public int getNumberOfDoors() {
        return numberOfDoors;
    }

    public int getNumberOfSeats() {
        return numberOfSeats;
    }

    public int getNumberOfWheels() {
        return numberOfWheels;
    }

    public boolean isElectric() {
        return isElectric;
    }

    @Override
    public void showDetail() {
        super.showDetail();
        System.out.println("Number of Doors: " + numberOfDoors);
        System.out.println("Number of Seats: " + numberOfSeats);
        System.out.println("Number of Wheels: " + numberOfWheels);
        System.out.println("Is Electric: " + isElectric);
    }
}