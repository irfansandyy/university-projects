import java.util.ArrayList;
import java.util.HashMap;

/**
 * Write a description of class Main here.
 *
 * @author (Irfan Sandy)
 * @version (1.0.0)
 */

public class Main
{
    private ArrayList<Vehicle> vehicleList = new ArrayList<>();
    private HashMap<Vehicle, String> rentor = new HashMap<>();
    private InputReader inputReader = new InputReader();

    public static void main(String[] args) {
        Main app = new Main();

        app.addCar("Toyota", "Camry", 2020, 4, 5, 4, false);
        app.addCar("Tesla", "Model S", 2021, 4, 5, 4, true);
        app.addMotorcycle("Harley-Davidson", "Street 750", 2019, false, 750);
        app.addMotorcycle("Zero Motorcycles", "SR/F", 2022, true, 110);
        app.addBike("Giant", "Escape 3", 2021, "Road Bike", true);
        app.addBike("Trek", "Marlin 7", 2020, "Mountain Bike", false);

        app.Run();
    }

    public void Run(){
        while(true){
            showGreetings();
            String input = inputReader.readString("> ");
            if(input.equals("1")){
                showList();
            }
            else if(input.equals("2")){
                showRentor();
            }
            else if(input.equals("3")){
                System.out.print("Enter the index of the vehicle to rent: ");
                int index = Integer.parseInt(inputReader.readString(""));
                System.out.print("Enter the name of the renter: ");
                String renterName = inputReader.readString("");
                addRentor(index, renterName);
            }
            else if(input.equals("4")){
                inputReader.close();
                return;
            }
        }
    }

    public void addCar(String make, String model, int year, int numberOfDoors, int numberOfSeats, int numberOfWheels, boolean isElectric) {
        Car car = new Car(make, model, year, numberOfDoors, numberOfSeats, numberOfWheels, isElectric);
        vehicleList.add(car);
    }

    public void addMotorcycle(String make, String model, int year, boolean isElectric, int engineCapacity){
        Motorcycle motorcycle = new Motorcycle(make, model, year, isElectric, engineCapacity);
        vehicleList.add(motorcycle);
    }

    public void addBike(String make, String model, int year, String type, boolean hasCarrier){
        Bike bike = new Bike(make, model, year, type, hasCarrier);
        vehicleList.add(bike);
    }

    public void addRentor(int index, String rentorName) {
        if (index >= 0 && index < vehicleList.size()) {
            Vehicle v = vehicleList.get(index);
            if (!rentor.containsKey(v)) {
                rentor.put(v, rentorName);
                System.out.println("Vehicle successfully rented to " + rentorName);
            } else {
                System.out.println("Vehicle is already rented");
            }
        } else {
            System.out.println("Vehicle index out of range");
        }
    }

    public void showList(){
        System.out.println("========= Available Vehicles =========");
        for (Vehicle v : vehicleList) {
            if (!rentor.containsKey(v)) { 
                v.showDetail();
                System.out.println("--------------------");
            }
        }
    }
    
    public void showRentor() {
        System.out.println("========= Rented Vehicles =========");
        for (Vehicle v : rentor.keySet()) {
            v.showDetail();
            System.out.println("Rented by: " + rentor.get(v));
            System.out.println("--------------------");
        }
    }

    public void showGreetings(){
        System.out.println("Welcome to vehicle rental shop");
        System.out.println("Choose an option: ");
        System.out.println("1. Show available vehicles");
        System.out.println("2. Show list of renters");
        System.out.println("3. Rent a vehicle");
        System.out.println("4. Exit");
    }
}


