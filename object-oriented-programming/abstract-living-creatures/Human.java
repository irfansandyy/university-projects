
/**
 * Write a description of class Human here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class Human extends LivingCreatures
{
    public Human() {
        this.name = "Human";
    }

    @Override
    public void eat() {
        System.out.println(name + " eats any type of food, it is a omnivore.");
    }

    @Override
    public void sleep() {
        System.out.println(name + " sleeps for about 7-9 hours a day.");
    }

    @Override
    public void breathe() {
        System.out.println(name + " breathes using lungs, and needs oxygen.");
    }
}