
/**
 * Write a description of class Plant here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class Plant extends LivingCreatures
{
    public Plant() {
        this.name = "Plant";
    }

    @Override
    public void eat() {
        System.out.println(name + " makes its own food through photosynthesis.");
    }

    @Override
    public void sleep() {
        System.out.println(name + " does not sleep but has periods of rest.");
    }

    @Override
    public void breathe() {
        System.out.println(name + " takes in carbon dioxide and releases oxygen.");
    }
}