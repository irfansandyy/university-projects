
/**
 * Write a description of class Main here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class Main
{   
    public static void main(String[] args) {
        Main main = new Main();
        main.run();
    }

    public void checkLivingCreatures(LivingCreatures creatures) {
        creatures.eat();
        creatures.sleep();
        creatures.breathe();
    }

    public void run() {
        LivingCreatures animal = new Animal();
        LivingCreatures plant = new Plant();
        LivingCreatures human = new Human();

        checkLivingCreatures(animal);
        System.out.println();
        checkLivingCreatures(plant);
        System.out.println();
        checkLivingCreatures(human);
    }
}