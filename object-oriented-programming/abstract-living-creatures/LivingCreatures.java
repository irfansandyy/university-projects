
/**
 * Write a description of class LivingCreatures here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public abstract class LivingCreatures
{
    protected String name;
    public abstract void eat();
    public abstract void sleep();
    public abstract void breathe();
    public void grow() {
        System.out.println(name + " is growing.");
    }
}