import java.util.List;
import java.util.ArrayList;

/**
 * Write a description of class Simulator here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class Simulator
{
    private Field field;
    private List<Animal> animals;

    public static void main(String[] args) {
        Simulator simulator = new Simulator(30, 30);
        simulator.field.printField();
        simulator.simulate(10);
        System.out.println("==============================");
        simulator.field.printField();
    }

    public Simulator(int width, int height) {
        field = new Field(height, width);
        animals = new ArrayList<>();
        populate();
    }

    public void simulate(int steps) {
        for (int step = 0; step < steps; step++) {
            List<Animal> newAnimals = new ArrayList<>();
            for (Animal animal : animals) {
                animal.act(newAnimals);
            }
            animals.addAll(newAnimals);
            animals.removeIf(animal -> !animal.isAlive());
        }
    }

    private void populate() {
        for (int row = 0; row < field.getDepth(); row++) {
            for (int col = 0; col < field.getWidth(); col++) {
                if (Math.random() < 0.1) {
                    Location location = new Location(row, col);
                    Rabbit rabbit = new Rabbit(field, location);
                    animals.add(rabbit);
                } else if (Math.random() < 0.05) {
                    Location location = new Location(row, col);
                    Fox fox = new Fox(field, location);
                    animals.add(fox);
                }
            }
        }
    }
}