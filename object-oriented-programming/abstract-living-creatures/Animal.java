
/**
 * Write a description of class Animal here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class Animal extends LivingCreatures
{
    public Animal() {
        this.name = "Animal";
    }

    @Override
    public void eat() {
        System.out.println(name + " can be a carnivore, herbivore, or omnivore.");
    }

    @Override
    public void sleep() {
        System.out.println(name + " sleeps variably depending on the species.");
    }

    @Override
    public void breathe() {
        System.out.println(name + " usually breathes using lungs or gills.");
    }
}